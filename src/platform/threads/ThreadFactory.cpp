// -*-C++-*- 

/*  src/platform/threads/ThreadFactory.cpp  */

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



/* $Id: ThreadFactory.cpp,v 1.2 2000/10/20 20:29:20 philogelos Exp $ */
#if !defined(_INLINE)
static char cvsid[] = "@(#)$Id: ThreadFactory.cpp,v 1.2 2000/10/20 20:29:20 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif

#include "platform/threads/Win32Thread.hpp"
#include "platform/threads/ThreadFactory.hpp"
#include "platform/threads/Runnable.hpp"
#include "platform/threads/PThread.hpp"
#include "platform/threads/NopThread.hpp"
#include "containers/lists/List.hpp"
#include "LinkManager.hpp"
#include "Debug.hpp"

BEGIN_QR_NAMESPACE

static void *runnableStub( void *anArg )
{
  preC_( anArg != NULL );

  return ( ( Runnable * ) anArg ) -> run();
}

static void *methodStub( void *anArg )
{
  preC_( anArg != NULL );

  MethodCall *call;

  call = ( MethodCall * ) anArg;
  return ( ( call -> object ) ->* ( call -> arity.nilaryMethod ) )();
}

ThreadFactory::ThreadFactory()
{
  FINIT( threads, new List() );
}

ThreadFactory::~ThreadFactory()
{
  FDONE( threads );
}

List *ThreadFactory::listThreads() const
{
  return threads;
}

Thread *ThreadFactory::createFromRunner( Runnable *aRunner )
{
  Thread *result;

  result = createFromFunc( runnableStub, aRunner );
  test_( result != NULL );
  result -> setName( String( "Runnable: " ) + 
					 aRunner -> getClassName() + 
					 " #" + String( result -> getId(), 10 ) );
  return result;
}

Thread *ThreadFactory::createFromMethod( Top *anObject, 
										 void *( Top::*aMethod )(), char )
{
  MethodCall call;
  Thread *result;

  call.object = anObject;
  call.arity.nilaryMethod = aMethod;

  result = createFromFunc( methodStub, &call );
  result -> setName( String( "Method of: " ) + 
					 anObject -> getClassName() + 
					 " #" + String( result -> getId(), 10 ) );
  return result;
}

ThreadFactory *ThreadFactory::getDefaultFactory()
{
  if( instance == ( ThreadFactory * ) NIL )
	{
	  ThreadFactory *newInstance;
	  
	  newInstance = new DEF_THREAD_FACTORY();
	  TCAST( newInstance, Object ) -> dontManage();
	  instance = newInstance;
	}
  return instance;
}

ThreadFactory *ThreadFactory::instance = ( ThreadFactory * ) NIL;

END_QR_NAMESPACE

#if defined(_INLINE)
#include "../src/Debug.ipp"
#endif


/*
 * $Log: ThreadFactory.cpp,v $
 * Revision 1.2  2000/10/20 20:29:20  philogelos
 * Simplifications through using of NopThreads
 *
 * Revision 1.1.1.1  2000/07/19 16:52:02  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:44  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:35  god
 * Imported sources
*/
