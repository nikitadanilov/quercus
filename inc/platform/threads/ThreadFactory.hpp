// -*-C++-*- 

/*  inc/platform/threads/ThreadFactory.hpp  */

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



#ifndef __THREADFACTORY_HPP__
#define __THREADFACTORY_HPP__

/* $Id: ThreadFactory.hpp,v 1.1.1.1 2000/07/19 17:14:11 philogelos Exp $ */

#include "Top.hpp"
#include "defines.h"

/* #define DEF_THREAD_FACTORY Win32ThreadFactory */

/**
   Name of default thread factory class.
   @see Win32ThreadFactory
   @see PThreadFactory
   @see ThreadFactory::getDefaultFactory()
*/
#define DEF_THREAD_FACTORY PThreadFactory


#if defined( WANT_DEF_THREAD_FACTORY )
#if defined( DEF_THREAD_FACTORY )
#undef DEF_THREAD_FACTORY
#endif
#define DEF_THREAD_FACTORY WANT_DEF_THREAD_FACTORY
#endif


#define THR_FACTORY ThreadFactory::getDefaultFactory()
#define THR_SYSTEM  THR_FACTORY -> getThreadSystem()

BEGIN_QR_NAMESPACE

interface Thread;
interface Runnable;
interface ThreadsSystem;
class List;

/**
   Factory object for threads. Specific per-platform
   sub-classes of this interface create threads on user 
   requests.

   @see Win32ThreadFactory
   @see PThreadFactory
   @author Philogelos
   @created
*/
abstract class ThreadFactory : public virtual Top
{
  /**
	 Create new thread beginning execution of given function
	 anArg. When function finishes thread dies and reports
	 function return value in system-dependent manner.
  */
public: virtual Thread *createFromFunc( void * ( *aStartFunc )( void *anArg ), 
										void *anArg ) = 0;
  /**
	 Create new thread beginning execution of 
	 method 
	 <pre>
	 aRunner -> run( anArg ).
	 </pre>
	 When method finishes thread dies 
	 and reports method return value in system-dependent manner.
  */
public: virtual Thread *createFromRunner( Runnable *aRunner );

  /**
	 Create new thread beginning execution of given
	 method ( anObject ->* aMethod )(). When method finishes thread dies 
	 and reports method return value in system-dependent manner.
  */
public: virtual Thread *createFromMethod( Top *anObject, 
										  void *( Top::*aMethod )(), char );

/**
   Returns ThreadsSystem object associated with this factory.

   ThreadsSystem used to create mutexes, semaphores etc.
*/
public: virtual ThreadsSystem *getThreadSystem() = 0;

/**
   Returns list of all threads created by this factory and
   still running.
*/
public: virtual List *listThreads() const;

/**
   Returns default factory object. To change behavior
   of this method, set DEF_THREAD_FACTORY macro to the name
   of class derived from ThreadFactory.

   @see DEF_THREAD_FACTORY
*/
public: static ThreadFactory *getDefaultFactory();

protected: ThreadFactory();
protected: virtual ~ThreadFactory();

protected: List *threads;
protected: static ThreadFactory *instance;
};

typedef struct
{
  Top *object;
  union
  {
	void *( Top::*nilaryMethod )();
	void *( Top::*unaryMethod )( Top *anArg );
	void *( Top::*binaryMethod )( Top *anArg1, Top *anArg2 );
  } arity;
  void *arg;
} MethodCall;

END_QR_NAMESPACE

/*
 * $Log: ThreadFactory.hpp,v $
 * Revision 1.1.1.1  2000/07/19 17:14:11  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:36  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:48  god
 * Imported sources
*/

/* __THREADFACTORY_HPP__ */
#endif
