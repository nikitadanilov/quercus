// -*-C++-*- 

/*  inc/platform/threads/NopThread.hpp  */

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



#ifndef __NOPTHREAD_HPP__
#define __NOPTHREAD_HPP__

/* $Id: NopThread.hpp,v 1.1 2000/10/20 20:28:35 philogelos Exp $ */

#include "defines.h"

/* #define USE_NOPTHREADS */

#if defined( WANT_USE_NOPTHREADS )
#define USE_NOPTHREADS
#elif defined( UNWANT_USE_NOPTHREADS )
#if defined( USE_NOPTHREADS )
#undef USE_NOPTHREADS
#endif
#endif


#if defined( USE_NOPTHREADS )

#include "ThreadFactory.hpp"
#include "ThreadsSystem.hpp"
#include "Thread.hpp"
#include "Object.hpp"
#include "Mutex.hpp"
#include "CondVar.hpp"
#include "Semaphore.hpp"
#include "RWLock.hpp"
#include "String.hpp"
#include "CRef.hpp"

BEGIN_QR_NAMESPACE

class NopThreadFactory;
class NopThread;
class NopThreadsSystem;
class NopCondVar;
class NopMutex;
class NopSemaphore;

/**
   Factory class for Nop threads.

   @see NopThread
   @see NopThreadsSystem
   @see NopCondVar
   @see NopMutex
   @see NopSemaphore
   @see NopRWLock
*/
class NopThreadFactory : public virtual ThreadFactory,
						 public virtual Object
{
  friend NopThreadsSystem;
  friend NopThread;

public: typedef enum { run, forget, bail } ThreadCreationPolicy;
public: NopThreadFactory( ThreadCreationPolicy aPolicy = run );
public: virtual ~NopThreadFactory();

public: virtual Thread *createFromFunc( void * ( *aStartFunc )( void *anArg ), 
										void *anArg );
  /**
	 Returns ThreadsSystem object associated with this factory.
  */
public: virtual ThreadsSystem *getThreadSystem();

protected: CRef< NopThreadsSystem > nopthreadsSystem;

protected: ThreadCreationPolicy policy;
protected: static Index threadDepth;
protected: static NopThread *currentThread;
};

/**
   Interface to Nop threads.

   @see NopThreadFactory
   @see NopThread
   @see NopCondVar
   @see NopMutex
   @see NopSemaphore
   @see NopRWLock
*/
class NopThreadsSystem : public virtual ThreadsSystem,
						 public virtual Object
{
  friend NopThread;

public: NopThreadsSystem();
public: virtual ~NopThreadsSystem();

  /**
	 Executes aFunct exactly once no matter how many times
	 and from how many threads this call was made.
	 (Not implemented.)
  */
public: virtual void onceFunc( void ( *aFunct )() );

  /**
	 Returns new Nop mutex.

	 @see NopMutex
  */
public: virtual Mutex *mutex();

  /**
	 Returns new recursive mutex. On LINUX
	 result is Nop mutex onto which
	 pthread_mutexattr_setkind_np( PTHREAD_MUTEX_RECURSIVE_NP )
	 was called. On other platforms result is RecMutex.

	 @see NopMutex
	 @see RecMutex
  */
public: virtual Mutex *recMutex();

  /**
	 Returns new Nop conditional variable.

	 @see NopCondVar
  */
public: virtual CondVar *condition();

  /**
	 Returns new Nop semaphore.

	 @see NopSemaphore
  */
public: virtual Semaphore *semaphore( Index anInitialCount );

public: virtual RWLock *rwLock();
  
  /**
	 Returns object corresponding to the calling thread.
  */
public: virtual Thread *getSelf();

  /**
	 Cancels given thread.
  */
public: virtual void cancel( Thread *aVictim );

  /**
	 Suspends execution of the calling thread.
  */
public: virtual void sleep( Index aSecond, Index aNanoseconds );

  /**
	 Finishes calling thread.
  */
public: virtual void exitCurrent( void *aStatus );
};

/**
   Nop thread.

   @see NopThreadFactory
   @see NopThreadsSystem
   @see NopCondVar
   @see NopMutex
   @see NopSemaphore
   @see NopRWLock

   @author Philogelos
   @created
*/
class NopThread : public virtual Thread,
				  public virtual Object
{
  friend NopThreadFactory;

public: NopThread();
public: virtual ~NopThread();
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
	 execution.
  */
public: virtual void join();

public:  virtual String  toString() const;
public:  virtual String  getClassName() const;

public: virtual void setName( String aName );
public: virtual String getName() const;

protected: String name;
  
#if defined( TESTING )
public:  virtual boolean tester( int ) const;
#endif
};

/**
   Nop mutex.

   @see NopThreadFactory
   @see NopThread
   @see NopThreadsSystem
   @see NopCondVar
   @see NopSemaphore
   @see NopRWLock
*/
class NopMutex : public virtual Mutex,
				 public virtual Object
{
  friend NopCondVar;

  /**
	 Creates default mutex. Wrapper around pthread_mutex_init.
  */
public: NopMutex();

  /**
	 Destroys this mutex.
  */
public: virtual ~NopMutex();

  /**
	 Locks this mutex.
	 Wrapper around pthread_mutex_lock.
  */
public: virtual void enter( const Top * = null );

  /**
	 Unlocks this mutex.
	 Wrapper around pthread_mutex_unlock.
  */
public: virtual void leave( const Top * = null );

  /**
	 Tries to lock this mutex.
	 Wrapper around pthread_mutex_trylock.
  */
public: virtual boolean tryEnter( const Top * = null );
};

/**
   Nop conditional variable.
   
   @see NopThreadFactory
   @see NopThread
   @see NopThreadsSystem
   @see NopMutex
   @see NopSemaphore
   @see NopRWLock
*/
class NopCondVar : public virtual CondVar,
				   public virtual Object
{
public: NopCondVar( NopMutex *aMutex );
public: virtual ~NopCondVar();

public: virtual Mutex *getMutex() const;
public: virtual void wait();
public: virtual void signal();
public: virtual void broadcast();

protected: CRef< NopMutex > mutex;
};

/**
   Nop semaphore.

   @see NopThreadFactory
   @see NopThread
   @see NopThreadsSystem
   @see NopCondVar
   @see NopMutex
   @see NopRWLock
 */
class NopSemaphore : public virtual Semaphore,
					 public virtual Object
{
public: NopSemaphore();
public: virtual ~NopSemaphore();

public: void inc();
public: void dec();
public: boolean tryDec();
};

/**
   Nop read/write lock.

   @see NopThreadFactory
   @see NopThread
   @see NopThreadsSystem
   @see NopCondVar
   @see NopMutex
   @see NopSemaphore
 */
class NopRWLock : public virtual RWLock,
				  public virtual Object
{
public: NopRWLock();
public: virtual ~NopRWLock();

public: virtual void enterRead( const Top * = null );
public: virtual void enterWrite( const Top * = null );
public: virtual void leave( const Top * = null );
public: virtual boolean tryEnterRead();
public: virtual boolean tryEnterWrite();
};

END_QR_NAMESPACE

/* USE_PTHREADS */
#endif

/*
 * $Log: NopThread.hpp,v $
 * Revision 1.1  2000/10/20 20:28:35  philogelos
 * No-op thread implementation added
 *
*/

/* __NOPTHREAD_HPP__ */
#endif
