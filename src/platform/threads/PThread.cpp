// -*-C++-*- 

/*  src/platform/threads/PThread.cpp  */

/*
 * Author: Philogelos A. <Philogelos@yahoo.com>
 * Maintainer: Philogelos A.
 * Keywords: C++, library, containers
 *
 * Copyright (C) 1999 Philogelos A.
 *
 * This file is part of Quercus Robusta.
 *
 * Quercus Robusta is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Library General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this software; see the file COPYING.LIB.  If not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 */



/* $Id: PThread.cpp,v 1.5 2000/10/20 20:29:20 philogelos Exp $ */
#if !defined(_INLINE)
static char cvsid[] = "@(#)$Id: PThread.cpp,v 1.5 2000/10/20 20:29:20 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif

#include "platform/threads/PThread.hpp"

#if defined( USE_PTHREADS )

#include "AeternalLifeController.hpp"
#include "containers/lists/List.hpp"
#include "exceptions/NotImplemented.hpp"
#include "platform/threads/RecMutex.hpp"
#include "platform/threads/MGuard.hpp"
#include "platform/threads/ThreadDeath.hpp"
#include "exceptions/Errno.hpp"
#include "LinkManager.hpp"
#include "PGuard.hpp"
#include "Debug.hpp"
#include "Backtrace.hpp"

#include <errno.h>
#include <time.h>

extern "C" int nanosleep( const struct timespec *rqtp,
						  struct timespec *rmtp );

#define PTHCR( message, call ) PThreadsSystem::pthrCall( message, call )
#define PTHC( call ) PTHCR( #call, call )

#define PTRYCALL( call, arg, busyErrno ) \
{ \
  int retCode; \
\
  retCode = call( arg ); \
  if( retCode == 0 ) \
	{ \
	  return true; \
	} \
  else if( retCode == busyErrno ) \
	{ \
	  return false; \
	} \
  PTHCR( #call, retCode ); \
  impossible_; \
  return true; \
}

BEGIN_QR_NAMESPACE

static void pthreadCleanupHandler( void *aKiller ) THROWS( ThreadDeath * )
{
  DLOGOBJECT
   	( "pthreadCleanupHandler(): %s", ( ThreadDeath * ) aKiller );
  throw ( ThreadDeath * ) aKiller;
}

static void *pthreadStartupTrampoline( void *anArg )
{
  preC_( anArg != NULL );

  CFuncCall *call;
  void *result;
  void *object;
  void *( *func )( void *arg );
  void *arg;
  CondVar *startup;
  CondVar *condition;
  CondVar *back;
  ThreadDeath *death;

#if defined( USE_THREADS )
  Backtrace::initThreadBacktrace();
#endif

  if( pthread_setcanceltype( PTHREAD_CANCEL_DEFERRED, ( int * ) NULL ) != 0 )
	{
	  DLOG
		( "Error in pthread_setcanceltype() in pthreadStartupTrampoline()" );
	  return ( void * ) NULL;
	}
  result = NULL;

  call = ( CFuncCall * ) anArg;
  func = call -> func;
  test_( func != NULL );

  arg = call -> arg;

  condition = call -> condition;
  test_( condition != NIL );

  back = call -> back;
  test_( back != NIL );

  startup = call -> startup;
  test_( startup != NIL );

  {
	MGuard _waitForCreation( condition -> getMutex(), nil );
	{
	  MGuard _notifyAboutCreation( startup -> getMutex(), nil );
	  startup -> signal();
	}

	condition -> wait();

	object = *( call -> object );
	test_( object != NULL );
  }

  /* XXX need method to destroy this later */
  // death = new ThreadDeath( ( Thread * ) object, "cancellation", null );
  death = NULL;

  pthread_cleanup_push( pthreadCleanupHandler, death );
  if( pthread_setspecific( PThreadFactory::backRefKey, object ) != 0 )
	{
	  DLOG
		( "Error in pthread_setspecific() in pthreadStartupTrampoline()" );
	  return NULL;
	}
  {
	MGuard _signalReadiness( back -> getMutex(), nil );
	back -> signal();
  }
  try
	{
#if defined( DEBUG_THREADS )
	  DLOG( "Thread starts." );
#endif	  
	  result = ( *func )( arg );
	}
  catch( ThreadDeath *aBanshee )
	{
	  DLOG( "Cancel intercepted" );
	}
  catch( Exception *aSomeJunk )
	{
	  DLOG( "Uncatched exception in thread" );
	  Debug::getLogger() -> exception( aSomeJunk );
	}
  catch( ... )
	{
	  DLOG( "Uncatched something catched by ellipsis" );
	}
  pthread_cleanup_pop( 0 );
#if defined( DEBUG_THREADS )
	  DLOG( "Thread ends." );
#endif	  
  return result;
}

PThreadFactory::PThreadFactory()
{
  FINIT( pthreadsSystem, new PThreadsSystem() );
  pthread_once( &initClassOnce, initClass );
}

PThreadFactory::~PThreadFactory()
{
  FDONE( pthreadsSystem );
}

Thread *PThreadFactory::createFromFunc( void * ( *aStartFunc )( void *anArg ), 
 										void *anArg )
{
  pthread_attr_t attribute;
  pthread_t id;
  Thread *thread;
  CFuncCall call;
  PCondVar startup( new PMutex() );
  PCondVar condition( new PMutex() );
  PCondVar backCond( new PMutex() );
  
  PTHC( pthread_attr_init( &attribute ) );
  
  /* do _not_ create threads detached by default */
  //   PTHC( 
  //	pthread_attr_setdetachstate( &attribute, PTHREAD_CREATE_DETACHED ) );
  
  call.func = aStartFunc;
  call.arg = anArg;
  call.object = &thread;

  call.startup = &startup;
  call.condition = &condition;
  call.back = &backCond;

  thread = NULL;

  {
 	MGuard _startup( startup.getMutex(), this );
	PTHC( pthread_create( &id, &attribute, pthreadStartupTrampoline, &call ) );
 	PTHC( pthread_attr_destroy( &attribute ) );
 	startup.wait();
  }
  thread = new PThread( id );
  TCAST( thread, PThread ) -> setUserThread( true );
  {
 	MGuard _back( backCond.getMutex(), this );
 	{
 	  MGuard _signal( condition.getMutex(), this );
 	  condition.signal();
 	}
 	backCond.wait();
  }
  PGuard _thread( thread, this );
  threads -> append( thread );
  return thread;
}

ThreadsSystem *PThreadFactory::getThreadSystem()
{
  return pthreadsSystem;
}

void PThreadFactory::initClass()
{
  pthread_key_create( &backRefKey, ( void (*)( void * ) ) NULL );
}

pthread_key_t PThreadFactory::backRefKey;
/* PTHREAD_ONCE_INIT is broken on Solaris. It expands to 
   { 0, 0, 0, 0 }, but each member of pthread_once_t struct is itself
   union! (u_pad64) */
pthread_once_t PThreadFactory::initClassOnce = PTHREAD_ONCE_INIT;

int PThreadsSystem::pthrCall( const char *callName, int retCode ) 
  THROWS( Errno * )
{
  if( ( retCode != 0 ) && ( retCode != EINTR ) )
	{
	  DLOG
		( "PThreadsSystem::pthrCall(): %s: %i", callName, retCode );
	  throw new Errno
		( String( "Error in call to POSIX threads: " ) + callName, 
		  null, retCode );
	}
  return retCode;
}

PThreadsSystem::PThreadsSystem()
{}

PThreadsSystem::~PThreadsSystem()
{}

void PThreadsSystem::onceFunc( void ( * )() )
{
  throw new NotImplemented( "PThreadsSystem::onceFunc()", null );
}

Mutex *PThreadsSystem::mutex() THROWS( Errno * )
{
  return new PMutex();
}

Mutex *PThreadsSystem::recMutex() THROWS( Errno * )
{
#if defined( __linux__ )
  pthread_mutexattr_t attribute;
  PMutex *result;

  PTHC( pthread_mutexattr_init( &attribute ) );

  PTHC( pthread_mutexattr_settype( &attribute, PTHREAD_MUTEX_RECURSIVE ) );
  /* Old(?) non-portable LINUXThreads interface */
//   PTHC( 
// 		pthread_mutexattr_setkind_np( &attribute, 
// 									  PTHREAD_MUTEX_RECURSIVE_NP ) );
  result = new PMutex( &attribute );
  PTHC( pthread_mutexattr_destroy( &attribute ) );
  return result;
#else
  return new RecMutex();
#endif
}

CondVar *PThreadsSystem::condition() THROWS( Errno * )
{
  return new PCondVar( new PMutex() );
}

Semaphore *PThreadsSystem::semaphore( Index anInitialCount ) THROWS( Errno * )
{
  preC_( anInitialCount >= 0 );
  return new PSemaphore( false, anInitialCount );
}

RWLock *PThreadsSystem::rwLock() THROWS( Errno * )
{
  return new PRWLock();
}

Thread *PThreadsSystem::getSelf()
{
  void *result;

  result = pthread_getspecific( PThreadFactory::backRefKey );
  if( result == NULL )
	{
	  result = ( Thread * ) new PThread( pthread_self() );
	  test_( pthread_setspecific( PThreadFactory::backRefKey, result ) == 0 );
	}
  test_( result != NULL );
  return ( Thread * ) result;
}

void PThreadsSystem::cancel( Thread *aVictim ) THROWS( Errno * )
{
  preC_( aVictim != ( Thread * ) NULL );
  preC_( DCAST( aVictim, PThread ) != ( PThread * ) NULL );

  //  DLOGOBJECT( "cancelling: %s", aVictim );
  PTHC( pthread_cancel( aVictim -> getId() ) );
}

void PThreadsSystem::sleep( Index aSecond, Index aNanoseconds ) 
  THROWS( Errno * )
{
  struct timespec delay;

  delay.tv_sec = aSecond;
  delay.tv_nsec = aNanoseconds;

  if( ::nanosleep( &delay, ( timespec * ) NULL ) == -1 )
	{
	  if( errno != EINTR )
		{
		  throw new Errno( "nanosleep() in PThreadsSystem::sleep()", null );
		}
	}
}

Thread *PThreadsSystem::getById( pthread_t )
{
  throw new NotImplemented( "PThreadsSystem::getById()", null );
}

void PThreadsSystem::exitCurrent( void *aStatus )
{
  pthread_exit( aStatus );
}

PThread::PThread( pthread_t anId )
{
  id = anId;
  name = String( "id: %i" ).sprintf( 1, id );
  setUserThread( false );
}

PThread::~PThread()
{}

Index PThread::getId() const
{
  return id;
}

void PThread::setId( pthread_t anId )
{
  id = anId;
}

boolean PThread::isSystemThread() const
{
  return !isUserThread();
}

boolean PThread::isUserThread() const
{
  return userThread;
}

void PThread::setUserThread( boolean aFlag )
{
  userThread = aFlag;
}

void PThread::join() THROWS( Errno * )
{
  void *status;

  PTHC( pthread_join( getId(), &status ) );
}

void PThread::setName( String aName )
{
  name = aName;
}

String PThread::getName() const
{
  return name;
}

String  PThread::toString() const
{
  return Object::toString() + " " + getName() +
	String( " id: " ) + String( getId(), 10 );
}

String  PThread::getClassName() const
{
  return "PThread";
}

#if defined( TESTING )
#include "OGuard.hpp"
#include "Backtrace.hpp"

#include <time.h>
#include <unistd.h>

void *t( void *arg )
{
  for( int i = 0 ; i < 100 ; ++i )
	{
	  DLOG( "t: %s", ( char * ) arg );
	  sleep( 1 );
	}
  throw new Errno( "test", null );
  
  return NULL;
}

boolean PThread::tester( int ) const
{
  while( true )
	{
	  Thread *t2;

	  ThreadFactory::getDefaultFactory() -> 
		createFromFunc( t, ( void * ) "foo bar baz ..." );
	  t2 = ThreadFactory::getDefaultFactory() -> 
		createFromFunc( t, ( void * ) "bla bla bla ..." );
	  sleep( 1 );
	  DLOG( "Hop!" );

	  DLOG( "t2: %p", t2 );
	  DLOGOBJECT( "t2: %s", t2 );
	  //	  ThreadFactory::getDefaultFactory() -> getThreadSystem()
	  //		-> cancel( t2 );
	  sleep( 1000 );
	  return true;
	}
}
#endif

PMutex::PMutex() THROWS( Errno * )
{
  PTHC( pthread_mutex_init( &core, NULL ) );
}

PMutex::PMutex( pthread_mutexattr_t *anAttribute ) THROWS( Errno * )
{
  PTHC( pthread_mutex_init( &core, anAttribute ) );
}

PMutex::~PMutex() THROWS( Errno * )
{
  PTHC( pthread_mutex_destroy( &core ) );
}

void PMutex::enter( const Top * ) THROWS( Errno * )
{
  //   DLOGOBJECT( "PMutex::enter: %s", this );
  PTHC( pthread_mutex_lock( &core ) );
}

void PMutex::leave( const Top * ) THROWS( Errno * )
{
  PTHC( pthread_mutex_unlock( &core ) );
  //   DLOGOBJECT( "PMutex::leave: %s", this );
}

boolean PMutex::tryEnter( const Top * ) THROWS( Errno * )
{
  PTRYCALL( pthread_mutex_trylock, &core, EBUSY );
}

String  PMutex::toString() const
{
  return Object::toString() +
 	" pthread_mutex_t: " + String( ( long int ) &core, 16 );
}


PCondVar::PCondVar( PMutex *aMutex ) THROWS( Errno * )
{
  FNNINIT( mutex, aMutex );

  PTHC( pthread_cond_init( &core, NULL ) );
}

PCondVar::~PCondVar() THROWS( Errno * )
{
  PTHC( pthread_cond_destroy( &core ) );
  FDONE( mutex );
}

Mutex *PCondVar::getMutex() const
{
  return mutex;
}

void PCondVar::wait() THROWS( Errno * )
{
  PTHC( pthread_cond_wait( &core, &( mutex -> core ) ) );
}

void PCondVar::signal() THROWS( Errno * )
{
  PTHC( pthread_cond_signal( &core ) );
}

void PCondVar::broadcast() THROWS( Errno * )
{
  PTHC( pthread_cond_broadcast( &core ) );
}

String  PCondVar::toString() const
{
  return Object::toString() +
	" mutex: " + mutex -> toString() + 
	" pthread_cond_t: " + String( ( long int ) &core, 16 );
}


PSemaphore::PSemaphore( boolean aShared, Index anInitialCount ) 
  THROWS( Errno * )
{
  if( sem_init( &core, aShared, anInitialCount ) == -1 )
	{
	  PTHCR( "sem_init", errno );
	}
}

PSemaphore::~PSemaphore() THROWS( Errno * )
{
  if( sem_destroy( &core ) == -1 )
	{
	  PTHCR( "sem_destroy", errno );
	}
}

void PSemaphore::inc() THROWS( Errno * )
{
  if( sem_post( &core ) == -1 )
	{
	  PTHCR( "sem_post", errno );
	}
}

void PSemaphore::dec() THROWS( Errno * )
{
  if( sem_wait( &core ) == -1 )
	{
	  PTHCR( "sem_dec", errno );
	}
}

boolean PSemaphore::tryDec() THROWS( Errno * )
{
  PTRYCALL( sem_trywait, &core, EAGAIN );
}


PRWLock::PRWLock() THROWS( Errno * )
{
  PTHC( pthread_rwlock_init( &core, NULL ) );
}

PRWLock::~PRWLock() THROWS( Errno * )
{
  PTHC( pthread_rwlock_destroy( &core ) );
}

void PRWLock::enterRead( const Top * ) THROWS( Errno * )
{
  PTHC( pthread_rwlock_rdlock( &core ) );
}

void PRWLock::enterWrite( const Top * ) THROWS( Errno * )
{
  PTHC( pthread_rwlock_wrlock( &core ) );
}

void PRWLock::leave( const Top * ) THROWS( Errno * )
{
  PTHC( pthread_rwlock_unlock( &core ) );
}

boolean PRWLock::tryEnterRead() THROWS( Errno * )
{
  PTRYCALL( pthread_rwlock_tryrdlock, &core, EBUSY );
}

boolean PRWLock::tryEnterWrite() THROWS( Errno * )
{
  PTRYCALL( pthread_rwlock_trywrlock, &core, EBUSY );
}

END_QR_NAMESPACE


#if defined(_INLINE)
#include "../src/Debug.ipp"
#endif

/* USE_PTHREADS */
#endif

/*
 * $Log: PThread.cpp,v $
 * Revision 1.5  2000/10/20 20:29:20  philogelos
 * Simplifications through using of NopThreads
 *
 * Revision 1.4  2000/10/12 21:34:57  philogelos
 * Correct handling of errors in sem_* calls
 *
 * Revision 1.3  2000/09/21 18:07:24  philogelos
 * updated throws clauses
 *
 * Revision 1.2  2000/08/30 12:33:23  philogelos
 * update THROWS to correspond to the actual throws
 *
 * Revision 1.1.1.1  2000/07/19 16:52:02  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.11  2000/05/06 08:36:28  god
 * committed
 *
 * Revision 1.10  2000/04/29 15:04:18  god
 * signatures of [P]RWLock changed to conform to Protector
 *
 * Revision 1.9  2000/04/29 13:52:56  god
 * Class PRWLock implemented
 *
 * Revision 1.8  2000/04/22 20:22:24  god
 * make use of #arg syntax of the preprecessor to simplify calls to PTHC macro
 *
 * Revision 1.7  2000/04/22 20:10:57  god
 * set/getUserThread() and .userThread field added in stead of mainThread kludge
 *
 * Revision 1.6  2000/04/22 19:55:40  god
 * getMainThread() and friends removed
 *
 * Revision 1.5  2000/04/22 19:51:21  god
 * create new PThread object on call to PThread::getSelf()
 *
 * Revision 1.4  2000/04/09 13:04:28  god
 * (getMainThread): call dontManage() on mainThread
 *
 * Revision 1.3  2000/04/09 13:02:35  god
 * typo in log message corrected
 *
 * Revision 1.2  2000/04/09 11:29:44  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:35  god
 * Imported sources
*/
