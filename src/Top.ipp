// -*- C++ -*-

/* $Id: Top.ipp,v 1.1.1.1 2000/07/19 16:42:48 philogelos Exp $ */

/*  src/Top.ipp  */


/*
 * Author: Philogelos A. <Philogelos@yahoo.com>
 * Maintainer: Philogelos A.
 * Keywords: C++, library, containers
 *
 * Copyright (C) 1998 Philogelos A.
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


#if !defined(__TOP_IPP__)
#define __TOP_IPP__

#include "Top.hpp"
#include "Debug.hpp"
#include "PGuard.hpp"
#include "platform/threads/ThreadFactory.hpp"
#include "platform/threads/Mutex.hpp"
#include "platform/threads/MGuard.hpp"

BEGIN_QR_NAMESPACE

INLINE Top::Top()
{
#if defined(MEMORY_LEAK_TEST)

#if defined( USE_THREADS )
  if( topLock != NULL )
	{
	  topLock -> enter( this );
	}
#endif

  prevInAllocatedChain = lastInAllocatedChain;
  nextInAllocatedChain = nil;
  if( prevInAllocatedChain != null )
	{
	  prevInAllocatedChain -> nextInAllocatedChain = this;
	}

  if( firstInAllocatedChain == null )
	{
	  firstInAllocatedChain = this;
	}
  lastInAllocatedChain = this;

#if defined( USE_THREADS )
  if( topLock != NULL )
	{
	  topLock -> leave( this );
	}
#endif

#endif
#if defined( TRACK_BACKPOINTERS )
  for( Index i = 0 ; i < BACKPOINTERS_LIST_LEN ; ++i )
	{
	  backpointers[ i ] = nil;
	}
#endif
}

#if defined(MEMORY_LEAK_TEST)

END_QR_NAMESPACE
#include "MemoryMonitor.hpp"
BEGIN_QR_NAMESPACE

INLINE void Top::dumpAllocated()
{
  Top *end;
  Top *point;
  Index count;
  
#if defined( USE_THREADS )
  test_( topLock != NULL );
  topLock -> enter( topLock );
#endif

  end = lastInAllocatedChain;
  point = firstInAllocatedChain;

  
  for( count = 0 ; ( point != nil ) && ( point != end ) ; 
	   point = point -> nextInAllocatedChain, ++count )
	{
#if defined( USE_THREADS )
	  topLock -> leave( topLock );
#endif
	  {
		PGuard _point( point, point );
		DLOGOBJECT( "dump: %s", point, &Top::toString );
	  }
#if defined( USE_THREADS )
	  topLock -> enter( topLock );
#endif
	}
#if defined( USE_THREADS )
  topLock -> leave( topLock );
#endif
  DLOG( "*** Totally allocated: %li, in %li objects", 
		MemoryMonitor::amount(), count );
}
#if defined(_INLINE)
#include "../src/MemoryMonitor.ipp"
#endif

#endif

#if defined( TRACK_BACKPOINTERS ) && defined( MEMORY_LEAK_TEST )

END_QR_NAMESPACE
#include "StringBuffer.hpp"
BEGIN_QR_NAMESPACE

INLINE void Top::dumpBackpointers()
{
  Top *end;
  Top *point;
  Index count;
  
  end = lastInAllocatedChain;
  point = firstInAllocatedChain;

  DLOG( "*** Backpointers" );
  
  for( count = 0 ; ( point != nil ) && ( point != end ) ; 
	   point = point -> nextInAllocatedChain, ++count )
	{
	  StringBuffer buffer( StringBuffer::defaultLength, 
						   StringBuffer::defaultDelta );
	  
	  PGuard _point( point, point );
	  buffer.add( String( "%p: (%li) [ " ).sprintf
				  ( 1, 
					DCAST( point, Object ), 
					point -> getRefCount() ).getUNIChars() );
	  for( Index i = 0 ; i < BACKPOINTERS_LIST_LEN ; ++i )
		{
		  if( point -> backpointers[ i ] != nil )
			{
			  buffer.add( String( "%li: %p " ).sprintf
						  ( 1, 
							i, 
							DCAST( point -> backpointers[ i ], 
								   Object ) ).getUNIChars() );
			  buffer.add( point -> backpointers[ i ] -> 
						  toString().getUNIChars() );
			  buffer.add( String( " " ).getUNIChars() );
			}
		}
	  if( point -> getRefCount() > BACKPOINTERS_LIST_LEN )
		{
		  buffer.add( String( "... " ).getUNIChars() );
		}
	  buffer.add( String( "]" ).getUNIChars() );
	  
	  DLOGSTRING( "%s", buffer.asString() );
	}
  DLOG( "*** End of backpointers" );
}
#endif


#if defined( USE_THREADS )
void Top::initThreads()
{
#if defined( MEMORY_LEAK_TEST )
  Mutex *tmpLock;

  tmpLock = THR_SYSTEM -> mutex();
  TCAST( tmpLock, Object ) -> dontManage();
  topLock = tmpLock;
#endif
}
#endif

END_QR_NAMESPACE

/* __TOP_IPP__ */
#endif

/*
 * $Log: Top.ipp,v $
 * Revision 1.1.1.1  2000/07/19 16:42:48  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:39  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:28  god
 * Imported sources
 *
 * Revision 1.3  1999/03/03 19:09:30  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.2  1999/02/28 15:59:17  philogelos
 * Tuned for inlines. Static definitions moved out to .cpp
 *
 * Revision 1.1.1.1  1998/11/25 20:11:01  philogelos
 * Quercus Robusta
 *
 * Revision 1.1.1.1  1998/06/22 08:47:12  philogelos
 * First version under CVS
 *
 * Revision 1.1.1.1  1998/04/01 17:15:29  philogelos
 * first version under CVS
 * */
