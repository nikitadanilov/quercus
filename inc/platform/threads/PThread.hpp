// -*-C++-*- 

/*  inc/platform/threads/PThread.hpp  */

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



#ifndef __PTHREAD_HPP__
#define __PTHREAD_HPP__

/* $Id: PThread.hpp,v 1.2 2000/08/30 12:20:35 philogelos Exp $ */

#define USE_PTHREADS

#if defined( WANT_USE_PTHREADS )
#define USE_PTHREADS
#elif defined( UNWANT_USE_PTHREADS )
#if defined( USE_PTHREADS )
#undef USE_PTHREADS
#endif
#endif


#if defined( USE_PTHREADS )

/* for pthread_mutexattr_settype */
#define _XOPEN_SOURCE 500

#include "ThreadFactory.hpp"
#include "ThreadsSystem.hpp"
#include "Thread.hpp"
#include "Object.hpp"
#include "defines.h"
#include "Mutex.hpp"
#include "CondVar.hpp"
#include "Semaphore.hpp"
#include "RWLock.hpp"
#include "String.hpp"

#include <pthread.h>
#include <semaphore.h>

BEGIN_QR_NAMESPACE

class PThreadFactory;
class PThread;
class PThreadsSystem;
class PCondVar;
class PMutex;
class PSemaphore;

class Errno;

/**
   Factory class for POSIX threads.

   @see PThread
   @see PThreadsSystem
   @see PCondVar
   @see PMutex
   @see PSemaphore
   @see PRWLock
*/
class PThreadFactory : public virtual ThreadFactory,
					   public virtual Object
{
public: PThreadFactory();
public: virtual ~PThreadFactory();

  /**
	 Creates thread executing aStartFunc.
	 This is wrapper around pthred_create() call.
  */
public: virtual Thread *createFromFunc( void * ( *aStartFunc )( void *anArg ), 
										void *anArg );
  /**
	 Returns ThreadsSystem object associated with this factory.
  */
public: virtual ThreadsSystem *getThreadSystem();

protected: PThreadsSystem *pthreadsSystem;

public: static pthread_key_t backRefKey;

protected: static void initClass();
protected: static pthread_once_t initClassOnce;
};

/**
   Interface to POSIX threads.

   @see PThreadFactory
   @see PThread
   @see PCondVar
   @see PMutex
   @see PSemaphore
   @see PRWLock
*/
class PThreadsSystem : public virtual ThreadsSystem,
					   public virtual Object
{
  friend PThread;

public: PThreadsSystem();
public: virtual ~PThreadsSystem();

  /**
	 Executes aFunct exactly once no matter how many times
	 and from how many threads this call was made.
	 (Not implemented.)
  */
public: virtual void onceFunc( void ( *aFunct )() );

  /**
	 Returns new POSIX mutex.

	 @see PMutex
  */
public: virtual Mutex *mutex() THROWS( Errno * );

  /**
	 Returns new recursive mutex. On LINUX
	 result is POSIX mutex onto which
	 pthread_mutexattr_setkind_np( PTHREAD_MUTEX_RECURSIVE_NP )
	 was called. On other platforms result is RecMutex.

	 @see PMutex
	 @see RecMutex
  */
public: virtual Mutex *recMutex() THROWS( Errno * );

  /**
	 Returns new POSIX conditional variable.

	 @see PCondVar
  */
public: virtual CondVar *condition() THROWS( Errno * );

  /**
	 Returns new POSIX semaphore.

	 @see PSemaphore
  */
public: virtual Semaphore *semaphore( Index anInitialCount ) THROWS( Errno * );

public: virtual RWLock *rwLock() THROWS( Errno * );
  
  /**
	 Returns object corresponding to the calling thread.
  */
public: virtual Thread *getSelf();

  /**
	 Cancels given thread. Wrapper around pthread_cancel.
  */
public: virtual void cancel( Thread *aVictim ) THROWS( Errno * );

  /**
	 Suspends execution of the calling thread.
  */
public: virtual void sleep( Index aSecond, Index aNanoseconds ) THROWS( Errno * );

  /**
	 Finishes calling thread.
  */
public: virtual void exitCurrent( void *aStatus );


  /**
	 Helper method.
  */
public: static int pthrCall( const char *callName, int retCode ) THROWS( Errno * );

  /**
	 Searches thread with given id.
	 Not implemented.
  */
public: static Thread *getById( pthread_t anId );
};

class ThreadDeath;

/**
   POSIX thread.

   @see PThreadFactory
   @see PThreadsSystem
   @see PCondVar
   @see PMutex
   @see PSemaphore
   @see PRWLock

   @author Philogelos
   @created
*/
class PThread : public virtual Thread,
				public virtual Object
{
  friend PThreadFactory;

  /**
	 Create thread with given thread id.
   */
public: PThread( pthread_t anId );

  /**
   */
public: virtual ~PThread();

  /**
	 Returns id of this thread.
  */
public: virtual Index getId() const;

  /**
	 True iff this thread is system thread.
	 For example, main thread or threads created on behalf
	 of thread library.

	 @see #isUserThread
  */
public: virtual boolean isSystemThread() const;

  /**
	 True iff this thread was created through
	 library calls (that is the main thread or a
	 thread created by thread library implementation or
	 some other external source.

	 @see #isSystemThread
  */
public: boolean isUserThread() const;

  /**
	 Blocks calling thread until this thread completes
	 execution. Wrapper around pthread_join.
  */
public: virtual void join() THROWS( Errno * );

public:  virtual String  toString() const;
public:  virtual String  getClassName() const;

public: virtual void setName( String aName );
public: virtual String getName() const;

protected: void setId( pthread_t anId );
protected: void setUserThread( boolean aFlag );
protected: pthread_t id;
protected: ThreadDeath *death;
protected: boolean userThread;

protected: String name;
  
#if defined( TESTING )
public:  virtual boolean tester( int ) const;
#endif
};

/**
   POSIX mutex.

   @see PThreadFactory
   @see PThread
   @see PThreadsSystem
   @see PCondVar
   @see PSemaphore
   @see PRWLock
*/
class PMutex : public virtual Mutex,
			   public virtual Object
{
  friend PCondVar;

  /**
	 Creates default mutex. Wrapper around pthread_mutex_init.
  */
public: PMutex() THROWS( Errno * );

  /**
	 Creates mutex with given attribute. 
	 Wrapper around pthread_mutex_init.
  */
public: PMutex( pthread_mutexattr_t *anAttribute ) THROWS( Errno * );

  /**
	 Destroys this mutex.
	 Wrapper around pthread_mutex_destroy.
  */
public: virtual ~PMutex() THROWS( Errno * );


  /**
	 Locks this mutex.
	 Wrapper around pthread_mutex_lock.
  */
public: virtual void enter( const Top * = null ) THROWS( Errno * );

  /**
	 Unlocks this mutex.
	 Wrapper around pthread_mutex_unlock.
  */
public: virtual void leave( const Top * = null ) THROWS( Errno * );

  /**
	 Tries to lock this mutex.
	 Wrapper around pthread_mutex_trylock.
  */
public: virtual boolean tryEnter( const Top * = null ) THROWS( Errno * );

public:  virtual String  toString() const;

protected: pthread_mutex_t core;
};

typedef struct
{
  void *( *func )( void *anArg );
  void *arg;
  Thread **object;
  CondVar *startup;
  CondVar *condition;
  CondVar *back;
} CFuncCall;

/**
   POSIX conditional variable.
   
   @see PThreadFactory
   @see PThread
   @see PThreadsSystem
   @see PMutex
   @see PSemaphore
   @see PRWLock
*/
class PCondVar : public virtual CondVar,
				 public virtual Object
{
public: PCondVar( PMutex *aMutex ) THROWS( Errno * );
public: virtual ~PCondVar() THROWS( Errno * );

public: virtual Mutex *getMutex() const;
public: virtual void wait() THROWS( Errno * );
public: virtual void signal() THROWS( Errno * );
public: virtual void broadcast() THROWS( Errno * );

public:  virtual String  toString() const;

protected: PMutex *mutex;
protected: pthread_cond_t core;
};

/**
   POSIX semaphore.
   See man pages for
   sem_init, sem_wait, sem_trywait, sem_post and sem_destroy
   for more info.

   @see PThreadFactory
   @see PThread
   @see PThreadsSystem
   @see PCondVar
   @see PMutex
   @see PRWLock
 */
class PSemaphore : public virtual Semaphore,
				   public virtual Object
{
public: PSemaphore( boolean aShared, Index anInitialCount ) THROWS( Errno * );
public: virtual ~PSemaphore() THROWS( Errno * );

public: void inc() THROWS( Errno * );
public: void dec() THROWS( Errno * );
public: boolean tryDec() THROWS( Errno * );

protected: sem_t core;
};

/**
   POSIX read/write lock.
   See man pages for
   pthread_rwlock_init, pthread_rwlock_destroy, 
   pthread_rwlock_rdlock, pthread_rwlock_tryrdlock, 
   pthread_rwlock_wrlock, pthread_rwlock_trywrlock, 
   pthread_rwlock_unlock
   for more info.

   @see PThreadFactory
   @see PThread
   @see PThreadsSystem
   @see PCondVar
   @see PMutex
   @see PSemaphore
 */
class PRWLock : public virtual RWLock,
				public virtual Object
{
public: PRWLock() THROWS( Errno * );
public: virtual ~PRWLock() THROWS( Errno * );

public: virtual void enterRead( const Top * = null ) THROWS( Errno * );
public: virtual void enterWrite( const Top * = null ) THROWS( Errno * );
public: virtual void leave( const Top * = null ) THROWS( Errno * );
public: virtual boolean tryEnterRead() THROWS( Errno * );
public: virtual boolean tryEnterWrite() THROWS( Errno * );

protected: pthread_rwlock_t core;
};

END_QR_NAMESPACE

/* USE_PTHREADS */
#endif

/*
 * $Log: PThread.hpp,v $
 * Revision 1.2  2000/08/30 12:20:35  philogelos
 * THROWS clauses updates to correspond to the real throws.
 *
 * Revision 1.1.1.1  2000/07/19 17:14:06  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.7  2000/05/06 08:36:26  god
 * committed
 *
 * Revision 1.6  2000/04/29 14:59:44  god
 * PRWLock and RWLock signatures changed to conform to Protector without hiding
 *
 * Revision 1.5  2000/04/29 13:53:07  god
 * Class PRWLock declared
 *
 * Revision 1.4  2000/04/22 20:36:20  god
 * commited
 *
 * Revision 1.3  2000/04/22 20:23:26  god
 * typos corrected
 *
 * Revision 1.2  2000/04/09 11:29:36  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:48  god
 * Imported sources
*/

/* __PTHREAD_HPP__ */
#endif
