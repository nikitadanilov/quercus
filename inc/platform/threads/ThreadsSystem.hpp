// -*-C++-*- 

/*  inc/platform/threads/ThreadsSystem.hpp  */

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



#ifndef __THREADSSYSTEM_HPP__
#define __THREADSSYSTEM_HPP__

/* $Id: ThreadsSystem.hpp,v 1.1.1.1 2000/07/19 17:14:38 philogelos Exp $ */

#include "Top.hpp"
#include "defines.h"

BEGIN_QR_NAMESPACE

interface Mutex;
interface CondVar;
interface Thread;
interface Semaphore;
interface RWLock;

/**
   Interface to thread platform.

   @author Philogelos
   @created
*/
interface ThreadsSystem : public virtual Top
{
  /**
	 Executes
	 <pre>
	 ( anObject ->* aMethod )()
	 </pre>
	 exactly once.
  */
 public: virtual void onceMethod( Top *anObject, void ( Top::*aMethod )() );

  /**
	 Executes given function exactly once.
  */
 public: virtual void onceFunc( void ( *aFunct )() ) = 0;


 /**
	Creates instance of mutex implementation for this
	platform.
 */
 public: virtual Mutex *mutex() = 0;

 /**
	Creates instance of recursive mutex implementation for this
	platform.
 */
 public: virtual Mutex *recMutex() = 0;

 /**
	Creates instance of conditional variable 
	implementation for this	platform.
 */
 public: virtual CondVar *condition() = 0;

 /**
	Creates instance of semaphore implementation for 
	this platform with given initial count.
 */
 public: virtual Semaphore *semaphore( Index anInitialCount ) = 0;

 /**
	Creates instance of read-write lock implementation for 
	this platform.
 */
 public: virtual RWLock *rwLock() = 0;

 /**
	Returns thread object for the calling thread.
 */
 public: virtual Thread *getSelf() = 0;

 /**
	Cancels given thread.
 */
 public: virtual void cancel( Thread *aVictim ) = 0;

 /**
	Puts calling thread to sleep for given number of
	seconds and nanoseconds.
 */
 public: virtual void sleep( Index aSecond, Index aNanoseconds ) = 0;

 /**
	Makes calling thread to exit.
 */
 public: virtual void exitCurrent( void *aStatus ) = 0;
};

END_QR_NAMESPACE

/*
 * $Log: ThreadsSystem.hpp,v $
 * Revision 1.1.1.1  2000/07/19 17:14:38  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.3  2000/04/29 15:28:51  god
 * ::rwLock() added
 *
 * Revision 1.2  2000/04/09 11:29:36  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:48  god
 * Imported sources
*/

/* __THREADSSYSTEM_HPP__ */
#endif
