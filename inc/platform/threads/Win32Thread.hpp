// -*-C++-*- 

/*  inc/platform/threads/Win32Thread.hpp  */

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



#ifndef __WIN32Thread_HPP__
#define __WIN32Thread_HPP__

/* $Id: Win32Thread.hpp,v 1.2 2000/08/30 12:20:35 philogelos Exp $ */

/* #define USE_WIN32THREADS */



#if defined( WANT_USE_WIN32THREADS )
#define USE_WIN32THREADS
#elif defined( UNWANT_USE_WIN32THREADS )
#if defined( USE_WIN32THREADS )
#undef USE_WIN32THREADS
#endif
#endif

#if defined( USE_WIN32THREADS )

#include "platform/Win32Platform.hpp"
#include "ThreadFactory.hpp"
#include "ThreadsSystem.hpp"
#include "Thread.hpp"
#include "Object.hpp"
#include "defines.h"
#include "Mutex.hpp"
#include "CondVar.hpp"
#include "String.hpp"
#include "Semaphore.hpp"

BEGIN_QR_NAMESPACE

class Win32ThreadFactory;
class Win32Thread;
class Win32ThreadsSystem;
class WCondVar;
class WMutex;
class WSemaphore;

/**
   Factory object for WIN32 threads.

   @see Win32ThreadFactory
   @see Win32Thread
   @see Win32ThreadsSystem
   @see WCondVar
   @see WMutex
   @see WSemaphore
*/
class Win32ThreadFactory : public virtual ThreadFactory,
						   public virtual Object
{
public: Win32ThreadFactory();
public: virtual ~Win32ThreadFactory();

public: virtual Thread *createFromFunc( void * ( *aStartFunc )( void *anArg ), void *anArg );
public: virtual ThreadsSystem *getThreadSystem();

protected: Win32ThreadsSystem *threadsSystem;

public: static Index backRefKey;

public: static void reportError( String aMessage ) THROWS( Errno * );

protected: static void initClass();
protected: static boolean initClassOnce;
};

/**
   Interface to Win32 thread-related functions.

   @see Win32ThreadFactory
   @see Win32Thread
   @see Win32ThreadsSystem
   @see WCondVar
   @see WMutex
   @see WSemaphore
*/
class Win32ThreadsSystem : public virtual ThreadsSystem,
					   public virtual Object
{
  friend class Win32Thread;

public: Win32ThreadsSystem();
public: virtual ~Win32ThreadsSystem();

  /**
	 Executes aFunct only once. Not implemented.
  */
public: virtual void onceFunc( void ( *aFunct )() );

  /**
	 Returns new Win32 mutex. (It will be recursive.)

	 @see WMutex
  */
public: virtual Mutex *mutex();

  /**
	 Returns new recursive Win32 mutex.
	 
	 @see WMutex
  */
public: virtual Mutex *recMutex();

  /**
	 Returns new Win32 conditional variable.

	 @see WCondVar
  */
public: virtual CondVar *condition();

  /**
	 Returns new recursive Win32 semaphore.

	 @see WSemaphore
  */
public: virtual Semaphore *semaphore( Index anInitialCount );

public: virtual Thread *getSelf();

  /**
	 Not implemented on this platform.
  */
public: virtual void cancel( Thread *aVictim );

  /**
	 Suspends execution of the calling thread.
	 Works with millisecond presition. Wrapper around
	 Sleep function.
  */
public: virtual void sleep( Index aSecond, Index aNanoseconds );

  /**
	 Finishes calling thread. Wrapper around _endthreadex.
  */
public: virtual void exitCurrent( void *aStatus );

  /**
	 Not implemented.
  */
public: static Thread *getById( DWORD anId );

protected: static Win32Thread *mainThread;
};

class ThreadDeath;

/**
   Win32 thread.

   @see Win32ThreadFactory
   @see Win32Thread
   @see Win32ThreadsSystem
   @see WCondVar
   @see WMutex
   @see WSemaphore

   @author Philogelos
*/
class Win32Thread : public virtual Thread,
				public virtual Win32Object
{
  friend Win32ThreadFactory;

  /**
	 Creates object associated with existing thread
	 with given handle and id.
   */
public: Win32Thread( HANDLE aHandle, DWORD anId );

  /**
	 Nop.
   */
public: virtual ~Win32Thread();

public: virtual Index getId() const;
public: virtual boolean isSystemThread() const;
public: virtual void join();

public:  virtual String  toString() const;
public:  virtual String  getClassName() const;

public: virtual void setName( String aName );
public: virtual String getName() const;

protected: void setId( DWORD anId );
protected: DWORD id;
protected: ThreadDeath *death;

protected: String name;
  
#if defined( TESTING )
public:  virtual boolean tester( int ) const;
#endif
};

/**
   Win32 mutex implemented as CriticalSection.
   See documentation on 
   InitializeCriticalSection,
   DeleteCriticalSection,
   EnterCriticalSection,
   LeaveCriticalSection and
   TryEnterCriticalSection functions for more info.

   @see Win32ThreadFactory
   @see Win32Thread
   @see Win32ThreadsSystem
   @see WCondVar
   @see WMutex
   @see WSemaphore

   @author Philogelos
*/
class WMutex : public Mutex,
			   public Object
{
  friend WCondVar;

public: WMutex();
public: virtual ~WMutex();

public: virtual void enter( const Top * = null );
public: virtual void leave( const Top * = null );
public: virtual boolean tryEnter( const Top * = null );

protected: CRITICAL_SECTION criticalSection;
};

typedef struct
{
  void *( *func )( void *anArg );
  void *arg;
  Thread **object;
  WCondVar *startup;
  WCondVar *condition;
  WCondVar *back;
} CFuncCall;

/**
   Win32 conditional variable. Implemented
   as Win32 Event + Mutex.

   @see Win32ThreadFactory
   @see Win32Thread
   @see Win32ThreadsSystem
   @see WCondVar
   @see WMutex
   @see WSemaphore

   @author Philogelos
*/
class WCondVar : public virtual CondVar,
				 public virtual Win32Object
{
public: WCondVar( WMutex *aMutex );
public: virtual ~WCondVar();

public: virtual Mutex *getMutex() const;
public: virtual void wait();
public: virtual void signal();
public: virtual void broadcast();

protected: Mutex *mutex;
protected: Index waiters;
};

/**
   Win32 semaphore. See documentation on 
   CreateSemaphore,
   ReleaseSemaphore and
   WaitForSingleObject for more info.
   
   @see Win32ThreadFactory
   @see Win32Thread
   @see Win32ThreadsSystem
   @see WCondVar
   @see WMutex
   @see WSemaphore

   @author Philogelos
*/
class WSemaphore : public virtual Semaphore,
					public virtual Win32Object
{
public: WSemaphore( Index anInitialCount );
public: virtual ~WSemaphore();

public: virtual void inc();
public: virtual void dec();
public: virtual boolean tryDec();

protected: static Index maxWSemaphoreCount;
};

END_QR_NAMESPACE

/* USE_WIN32THREADS */
#endif


/*
 * $Log: Win32Thread.hpp,v $
 * Revision 1.2  2000/08/30 12:20:35  philogelos
 * THROWS clauses updates to correspond to the real throws.
 *
 * Revision 1.1.1.1  2000/07/19 17:14:40  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:36  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:48  god
 * Imported sources
*/

/* __WIN32Thread_HPP__ */
#endif
