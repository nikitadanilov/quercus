// -*-C++-*- 

/*  src/platform/threads/Win32Thread.cpp  */

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



/* $Id: Win32Thread.cpp,v 1.2 2000/08/30 12:33:23 philogelos Exp $ */
#include "platform/threads/Win32Thread.hpp"

#if defined( USE_WIN32THREADS )

#if !defined(_INLINE)
static char cvsid[] = "@(#)$Id: Win32Thread.cpp,v 1.2 2000/08/30 12:33:23 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif

#include "containers/lists/List.hpp"
#include "exceptions/NotImplemented.hpp"
#include "platform/Platform.hpp"
#include "platform/threads/RecMutex.hpp"
#include "platform/threads/MGuard.hpp"
#include "platform/threads/ThreadDeath.hpp"
#include "exceptions/Errno.hpp"
#include "LinkManager.hpp"
#include "PGuard.hpp"
#include "Debug.hpp"
#include "Backtrace.hpp"

#include "exceptions/NotImplemented.hpp"

#include <errno.h>
#include <time.h>
#include <process.h>

BEGIN_QR_NAMESPACE

extern "C"
{
static unsigned __stdcall win32ThreadStartupTrampoline( void *anArg )
{
  preC_( anArg != NULL );

  CFuncCall *call;
  void *result;
  void *object;
  void *( *func )( void *arg );
  void *arg;
  WCondVar *startup;
  WCondVar *condition;
  WCondVar *back;

  Backtrace::initThreadBacktrace();

  call = ( CFuncCall * ) anArg;

  func = call -> func;
  test_( func != ( void * (*)( void * ) ) NULL );

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
	test_( object != ( Thread * ) NULL );
  }

  if( TlsSetValue( Win32ThreadFactory::backRefKey, object ) == 0 )
	{
	  Win32ThreadFactory::reportError
		  ( "TlsSetValue() in win32ThreadStartupTrampoline()" );
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
	  OGuard _killer( aBanshee, aBanshee );
	  DLOG( "Cancel intercepted" );
	}
  catch( Exception *aSomeJunk )
	{
	  OGuard _page( aSomeJunk, aSomeJunk );
	  DLOG( "Uncatched exception in thread" );
	  Debug::getLogger() -> exception( aSomeJunk );
	}
  catch( ... )
	{
	  DLOG( "Uncatched something catched by ellipsis" );
	}
#if defined( DEBUG_THREADS )
	  DLOG( "Thread ends." );
#endif	  
  return ( unsigned ) result;
}
}
 
Win32ThreadFactory::Win32ThreadFactory()
{
  FINIT( threadsSystem, new Win32ThreadsSystem() );
  if( !initClassOnce )
  {
	  initClassOnce = true;
	  initClass();
  }
}

Win32ThreadFactory::~Win32ThreadFactory()
{
  FDONE( threadsSystem );
}

Thread *Win32ThreadFactory::createFromFunc( void * ( *aStartFunc )( void *anArg ), 
											void *anArg )
{
  unsigned id;
  Thread *thread;
  CFuncCall call;
  WCondVar startup( new WMutex() );
  WCondVar condition( new WMutex() );
  WCondVar backCond( new WMutex() );
  HANDLE handle;

  call.func = aStartFunc;
  call.arg = anArg;
  call.object = &thread;

  call.startup = &startup;
  call.condition = &condition;
  call.back = &backCond;

  thread = ( Thread * ) NULL;

  {
	MGuard _startup( startup.getMutex(), this );
	handle = ( HANDLE ) _beginthreadex
		( NULL, 0, win32ThreadStartupTrampoline, &call, 0, &id );
	if( handle == NULL )
	{
	  Win32ThreadFactory::reportError
		  ( "CreateThread() in Win32ThreadFactory::createFromFunc()" );
	}
	startup.wait();
  }
  thread = new Win32Thread( handle, ( DWORD ) id );
  {
	MGuard _back( backCond.getMutex(), this );
	{
	  MGuard _signal( condition.getMutex(), this );
	  condition.signal();
	}
	backCond.wait();
  }
  PGuard _thread( thread, this );
  /* XXX Need method to remove threads from list otherwise they remain 
	 referenced	forever */
  //  threads -> append( thread ); 
  return thread;
}

ThreadsSystem *Win32ThreadFactory::getThreadSystem()
{
  return threadsSystem;
}

void Win32ThreadFactory::initClass()
{
   backRefKey = TlsAlloc();
   if( backRefKey == 0xffffffffU )
   {
	  Win32ThreadFactory::reportError
		  ( "TlsAlloc() in Win32ThreadFactory::initClass()" );
   }
}

void Win32ThreadFactory::reportError( String aMessage ) THROWS( Errno * )
{
	DWORD error;
	String message;

	error = GetLastError();
	message = String( "Error in Win32Thread module:" ) + aMessage +
		String( " Error description: %s, code: %li" ).
			sprintf( 1, PLAF -> getErrorDescription( error ), error );
	throw new Errno( message, nil, error );
}

Index Win32ThreadFactory::backRefKey = 0;
boolean Win32ThreadFactory::initClassOnce = false;

Win32ThreadsSystem::Win32ThreadsSystem()
{}

Win32ThreadsSystem::~Win32ThreadsSystem()
{}

void Win32ThreadsSystem::onceFunc( void ( * )() )
{
  throw new NotImplemented( "Win32ThreadsSystem::onceFunc()", null );
}

Mutex *Win32ThreadsSystem::mutex()
{
  return new WMutex();
}

Mutex *Win32ThreadsSystem::recMutex()
{
  return new WMutex();
}

CondVar *Win32ThreadsSystem::condition()
{
  return new WCondVar( new WMutex() );
}

Semaphore *Win32ThreadsSystem::semaphore( Index anInitialCount )
{
  return new WSemaphore( anInitialCount );
}


Thread *Win32ThreadsSystem::getSelf()
{
  void *result;

  result = TlsGetValue( Win32ThreadFactory::backRefKey );
  if( result == NULL ) 
	{
	  if( GetLastError() == NO_ERROR )
	  {
		return mainThread;
	  }
	  else
	  {
		  Win32ThreadFactory::reportError
			  ( "TlsGetValue() in Win32ThreadsSystem::getSelf()" );
		  return NULL;
	  }
	}
  else
	{
	  return ( Thread * ) result;
	}
}

void Win32ThreadsSystem::cancel( Thread * )
{
  throw new NotImplemented( "Win32ThreadsSystem::cancel()", null );
}

void Win32ThreadsSystem::sleep( Index aSecond, Index aNanoseconds )
{
  Sleep( aSecond * 1000 + aNanoseconds / 1000000 );
}

void Win32ThreadsSystem::exitCurrent( void *aStatus )
{
	_endthreadex( ( unsigned ) aStatus );
}

Thread *Win32ThreadsSystem::getById( DWORD )
{
  throw new NotImplemented( "Win32ThreadsSystem::getById()", null );
  RET_THROW( NULL );
}

Win32Thread *Win32ThreadsSystem::mainThread = new Win32Thread( 0x0, -1 );

Win32Thread::Win32Thread( HANDLE aHandle, DWORD anId ) :
	Win32Object( aHandle )
{
  id = anId;
  name = String( "id: %i" ).sprintf( 1, id );
}

Win32Thread::~Win32Thread()
{}

Index Win32Thread::getId() const
{
  return ( Index ) id;
}

void Win32Thread::setId( DWORD anId )
{
  id = anId;
}

boolean Win32Thread::isSystemThread() const
{
  return( this == Win32ThreadsSystem::mainThread );
}

void Win32Thread::join()
{
  if( WaitForSingleObject( getHandle(), INFINITE ) == WAIT_FAILED )
  {
	  Win32ThreadFactory::reportError
		  ( "WaitForSingleObject() in Win32Thread::join()" );
  }
}

void Win32Thread::setName( String aName )
{
  name = aName;
}

String Win32Thread::getName() const
{
  return name;
}

String  Win32Thread::toString() const
{
  return Object::toString() + " " + getName() +
	String( " id: " ) + String( getId(), 10 );
}

String  Win32Thread::getClassName() const
{
  return "Win32Thread";
}

#if defined( TESTING )
#include "OGuard.hpp"
#include "Backtrace.hpp"

#include <time.h>

void *t( void *arg )
{
  for( int i = 0 ; i < 10 ; ++i )
	{
	  DLOG( "t: %i %s", i, ( char * ) arg );
	  THR_SYSTEM -> sleep( 0, 100 );
	}
//  throw new Errno( "test", null );
  
  return NULL;
}

boolean Win32Thread::tester( int ) const
{
  Thread *t1;
  Thread *t2;

  DLOG( "Win32Thread::tester()" );
  t1 = THR_FACTORY -> createFromFunc( t, ( void * ) "foo bar baz ..." );
  OGuard _t1( t1, this );
  t2 = THR_FACTORY -> createFromFunc( t, ( void * ) "bla bla bla ..." );
  OGuard _t2( t2, this );
  THR_SYSTEM -> sleep( 1, 0 );
  DLOG( "Hop!" );
  DLOGOBJECT( "t1: %s", t1 );
  DLOGOBJECT( "t2: %s", t2 );
  t1 -> join();
  t2 -> join();
  return true;
}
#endif

WMutex::WMutex()
{
  InitializeCriticalSection( &criticalSection );
}

WMutex::~WMutex()
{
  DeleteCriticalSection( &criticalSection );
}

void WMutex::enter( const Top * )
{
  EnterCriticalSection( &criticalSection );
}

void WMutex::leave( const Top * )
{
  LeaveCriticalSection( &criticalSection );
}

boolean WMutex::tryEnter( const Top * )
{
#if _WIN32_WINNT >= 0x0400
  return ( boolean ) TryEnterCriticalSection( &criticalSection );
#else
  throw new NotImplemented
	( "WMutex::tryEnter() is absent on elder Win32 implementations", nil );
  RET_THROW( false );
#endif
}

WCondVar::WCondVar( WMutex *aMutex ) : Win32Object( NULL )
{
  setHandle( CreateEvent( NULL, false, false, NULL ) );
  if( getHandle() == NULL )
  {
    Win32ThreadFactory::reportError( "CreateEvent() in WCondVar::WCondVar()" );
  }

  FINIT( mutex, aMutex );
  waiters = 0;
}

WCondVar::~WCondVar()
{
  FDONE( mutex );
}

Mutex *WCondVar::getMutex() const
{
  return mutex;
}

void WCondVar::wait()
{
  ++waiters;
  /* XXX Is there some faithfull equivalent of conditional vars. under Win32?*/
  getMutex() -> leave(); 
  if( WaitForSingleObject( handle, INFINITE ) == WAIT_FAILED )
  {
    Win32ThreadFactory::reportError( "WaitForSingleObject() in WCondVar::wait()" );
  }
  --waiters;
}

void WCondVar::signal()
{
  if( !SetEvent( handle ) )
  {
    Win32ThreadFactory::reportError( "SetEvent() in WCondVar::signal()" );
  }
}

void WCondVar::broadcast()
{
  while( waiters > 0 )
  {
    signal();
  }
}

WSemaphore::WSemaphore( Index anInitialCount ) : Win32Object( NULL )
{
	preC_( anInitialCount >= 0 );
	preC_( anInitialCount <= maxWSemaphoreCount );

	setHandle( CreateSemaphore
		( NULL, anInitialCount, maxWSemaphoreCount, NULL ) );
	if( getHandle() == NULL )
	{
		Win32ThreadFactory::reportError
			( "CreateSemaphore() in WSemaphore::WSemaphore()" );
	}
}

WSemaphore::~WSemaphore()
{}

void WSemaphore::inc()
{
	if( !ReleaseSemaphore( handle, 1, NULL ) )
	{
		Win32ThreadFactory::reportError
			( "ReleaseSemaphore() in WSemaphore::inc()" );
	}
}

void WSemaphore::dec()
{
	if( WaitForSingleObject( handle, INFINITE ) == WAIT_FAILED )
	{
		Win32ThreadFactory::reportError
			( "WaitForSingleObject() in WSemaphore::dec()" );
	}
}

boolean WSemaphore::tryDec()
{
	DWORD retCode;

	retCode = WaitForSingleObject( handle, 0 );
	if( ( retCode == WAIT_OBJECT_0 ) )
	{
		return true;
	}
	else if( retCode == WAIT_TIMEOUT )
	{
		return false;
	}
	impossible_;
	return false;
}

Index WSemaphore::maxWSemaphoreCount = 100000;

END_QR_NAMESPACE

#if defined(_INLINE)
#include "../src/Debug.ipp"
#endif

/* USE_WIN32THREADS */
#endif

/*
 * $Log: Win32Thread.cpp,v $
 * Revision 1.2  2000/08/30 12:33:23  philogelos
 * update THROWS to correspond to the actual throws
 *
 * Revision 1.1.1.1  2000/07/19 16:52:03  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:44  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:35  god
 * Imported sources
*/
