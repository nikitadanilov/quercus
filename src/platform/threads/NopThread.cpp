// -*-C++-*- 

/*  src/platform/threads/NopThread.cpp  */

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

/* $Id: NopThread.cpp,v 1.1 2000/10/20 20:28:36 philogelos Exp $ */
#if !defined(_INLINE)
static char cvsid[] = "@(#)$Id: NopThread.cpp,v 1.1 2000/10/20 20:28:36 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif

#include "platform/threads/NopThread.hpp"

#if defined( USE_NOPTHREADS )

#include "AeternalLifeController.hpp"
#include "containers/lists/List.hpp"
#include "exceptions/NotImplemented.hpp"
#include "platform/threads/RecMutex.hpp"
#include "platform/threads/MGuard.hpp"
#include "platform/threads/ThreadDeath.hpp"
#include "exceptions/Errno.hpp"
#include "exceptions/NotImplemented.hpp"
#include "LinkManager.hpp"
#include "PGuard.hpp"
#include "Debug.hpp"
#include "Backtrace.hpp"

BEGIN_QR_NAMESPACE

Index NopThreadFactory::threadDepth = 0;
NopThread *NopThreadFactory::currentThread = NULL;

NopThreadFactory::NopThreadFactory( ThreadCreationPolicy aPolicy )
{
  nopthreadsSystem = new NopThreadsSystem();
  policy = aPolicy;
}

NopThreadFactory::~NopThreadFactory()
{}

Thread *NopThreadFactory::createFromFunc( void * ( *aStartFunc )( void *anArg ), 
										  void *anArg )
{
  NopThread *thread;

  thread = new NopThread();
  PGuard _thread( thread, this );

  switch( policy )
	{
	case run:
	  {
		NopThread *parent;

		parent = currentThread;
		++threadDepth;
		currentThread = thread;
		aStartFunc( anArg );
		threadDepth--;
		currentThread = parent;
	  }
	  break;
	case forget:
	  {}
	  break;
	case bail:
	  {
		throw new NotImplemented( "Thread creation in no-thread env.", null );
	  }
	  break;
	}
  return thread;
}

ThreadsSystem *NopThreadFactory::getThreadSystem()
{
  return *nopthreadsSystem;
}

NopThreadsSystem::NopThreadsSystem()
{}

NopThreadsSystem::~NopThreadsSystem()
{}

void NopThreadsSystem::onceFunc( void ( * )() )
{
  throw new NotImplemented( "NopThreadsSystem::onceFunc()", null );
}

Mutex *NopThreadsSystem::mutex()
{
  return new NopMutex();
}

Mutex *NopThreadsSystem::recMutex()
{
  return mutex();
}

CondVar *NopThreadsSystem::condition()
{
  return new NopCondVar( new NopMutex() );
}

Semaphore *NopThreadsSystem::semaphore( Index )
{
  return new NopSemaphore();
}

RWLock *NopThreadsSystem::rwLock()
{
  return new NopRWLock();
}

Thread *NopThreadsSystem::getSelf()
{
  if( NopThreadFactory::currentThread == NULL )
	{
	  NopThreadFactory::currentThread = new NopThread();
	}
  return NopThreadFactory::currentThread;
}

void NopThreadsSystem::cancel( Thread * )
{}

void NopThreadsSystem::sleep( Index , Index  ) 
 
{
  /* insert some stupid busy loop here XXX */
}

void NopThreadsSystem::exitCurrent( void * )
{
  /* play longjmp() games here XXX */
  throw new NotImplemented( "NopThreadsSystem::exitCurrent()", null );
}

NopThread::NopThread()
{
  name = String( "id: %i" ).sprintf( 1, NopThreadFactory::threadDepth );
}

NopThread::~NopThread()
{}

Index NopThread::getId() const
{
  return NopThreadFactory::threadDepth;
}

boolean NopThread::isSystemThread() const
{
  return( NopThreadFactory::threadDepth == 0 );
}

boolean NopThread::isUserThread() const
{
  return !isSystemThread();
}

void NopThread::join()
{
  throw new NotImplemented( "NopThread::join()", null );
}

void NopThread::setName( String aName )
{
  name = aName;
}

String NopThread::getName() const
{
  return name;
}

String  NopThread::toString() const
{
  return Object::toString() + " " + getName() +
	String( " id: " ) + String( getId(), 10 );
}

String  NopThread::getClassName() const
{
  return "NopThread";
}

#if defined( TESTING )
#include "OGuard.hpp"
#include "Backtrace.hpp"

#include <time.h>
#include <unistd.h>

void *nopt( void *arg )
{
  for( int i = 0 ; i < 100 ; ++i )
	{
	  DLOG( "t: %s", ( char * ) arg );
	}
  
  return NULL;
}

boolean NopThread::tester( int ) const
{
  while( true )
	{
	  Thread *t2;

	  ThreadFactory::getDefaultFactory() -> 
		createFromFunc( nopt, ( void * ) "foo bar baz ..." );
	  t2 = ThreadFactory::getDefaultFactory() -> 
		createFromFunc( nopt, ( void * ) "bla bla bla ..." );
	  sleep( 1 );
	  DLOG( "Hop!" );

	  DLOG( "t2: %p", t2 );
	  DLOGOBJECT( "t2: %s", t2 );
	  //	  ThreadFactory::getDefaultFactory() -> getThreadSystem()
	  //		-> cancel( t2 );
	  sleep( 1 );
	  return true;
	}
}
#endif

NopMutex::NopMutex()
{}

NopMutex::~NopMutex()
{}

void NopMutex::enter( const Top * )
{}

void NopMutex::leave( const Top * )
{}

boolean NopMutex::tryEnter( const Top * )
{
  return true;
}

NopCondVar::NopCondVar( NopMutex *aMutex )
{
  mutex = aMutex;
}

NopCondVar::~NopCondVar()
{}

Mutex *NopCondVar::getMutex() const
{
  return *mutex;
}

void NopCondVar::wait()
{}

void NopCondVar::signal()
{}

void NopCondVar::broadcast()
{}

NopSemaphore::NopSemaphore() 
{}

NopSemaphore::~NopSemaphore()
{}

void NopSemaphore::inc()
{}

void NopSemaphore::dec()
{}

boolean NopSemaphore::tryDec()
{
  return true;
}


NopRWLock::NopRWLock()
{}

NopRWLock::~NopRWLock()
{}

void NopRWLock::enterRead( const Top * )
{}

void NopRWLock::enterWrite( const Top * )
{}

void NopRWLock::leave( const Top * )
{}

boolean NopRWLock::tryEnterRead()
{
  return true;
}

boolean NopRWLock::tryEnterWrite()
{
  return true;
}

END_QR_NAMESPACE


#if defined(_INLINE)
#include "../src/Debug.ipp"
#endif

/* USE_NOPTHREADS */
#endif

/*
 * $Log: NopThread.cpp,v $
 * Revision 1.1  2000/10/20 20:28:36  philogelos
 * No-op thread implementation added
 *
*/
