//-*-C++-*-

/*  src/new-operator.ipp  */


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



/* $Id: new-operator.ipp,v 1.1.1.1 2000/07/19 16:43:00 philogelos Exp $ */

#if !defined(__NEW_OPERATOR_IPP__)
#define __NEW_OPERATOR_IPP__

#include "new-operator.hpp"
#include "MemoryMonitor.hpp"
#include "Top.hpp"
#include "Debug.hpp"
#include "defines.h"
#include "platform/Platform.hpp"
#include "platform/threads/ThreadFactory.hpp"
#include "platform/threads/Mutex.hpp"
#include "platform/threads/MGuard.hpp"

#if ( defined( PROFILE_MEM_ALLOC ) || defined( USE_ALLOC_CHAIN ) || defined( CHECK_DELETES ) ) && !defined( DECORATE_ALLOCATIONS )
#error USE_ALLOC_CHAIN, PROFILE_MEM_ALLOC and CHECK_DELETES implies DECORATE_ALLOCATIONS
#endif

BEGIN_QR_NAMESPACE

#if defined( USE_THREADS )
static Mutex *newDeleteLock = NULL;
/* USE_THREADS */
#endif

long magicStart   = 0xa1efc0fe;
long magicEnd     = 0xc001deaf;
long magicDeleted = 0xb100ded7;

static const size_t shift = sizeof magicStart;
static const size_t doubleShift = 2 * shift;

#if defined( USE_ALLOC_CHAIN )
static  long *firstInAllocatedChain = ( long * ) NULL;
static  long *lastInAllocatedChain = ( long * ) NULL;

void dumpAllocatedByNew();
/* USE_ALLOC_CHAIN */
#endif

INLINE void *newOp( size_t aSize ) 
#if !defined(__SUNPRO_CC)
  OP_THROW( int )
#endif
{
#if defined( USE_ALLOC_CHAIN )
  aSize += doubleShift;
#endif
#if defined( DECORATE_ALLOCATIONS )
  const size_t rSize = ( ( aSize - 1 ) / shift + 1 );
#endif
  
  char *arena;
  Platform *platform;

  platform = Platform::getInstanceNow();
  if( platform != ( Platform * ) NIL )
	{
	  arena = ( char * ) platform -> allocateMemory
#if defined( DECORATE_ALLOCATIONS )
		( ( rSize  + 3 ) * shift )
#else
		( aSize )
#endif
		;
	}
  else
	{
	  arena = ( char * ) platform -> allocateMemoryBootstrap
#if defined( DECORATE_ALLOCATIONS )
		( ( rSize  + 3 ) * shift )
#else
		( aSize )
#endif
		;
	}

#if defined( PROFILE_MEM_ALLOC )
  MemoryMonitor::inc( aSize, arena + doubleShift );
#endif

  if( arena == NIL )
	{
	  MemoryMonitor::release();
	  DLOG("Failed to allocate %i bytes. "
								"(Totally allocated: %lu.) Cleaning up",
								aSize, MemoryMonitor::amount() );
	}

#if defined( DECORATE_ALLOCATIONS )
  ( ( long * ) arena )[ 0 ] = ( long ) aSize;
  ( ( long * ) arena )[ 1 ] = magicStart;
  ( ( long * ) arena )[ rSize + 2 ] = magicEnd;
#endif

#if defined( USE_ALLOC_CHAIN )

#if defined( USE_THREADS )
  if( newDeleteLock != NULL )
	{
	  newDeleteLock -> enter( nil );
	}
#endif


  ( ( long * ) arena )[ 2 ] = ( long ) lastInAllocatedChain;
  ( ( long * ) arena )[ 3 ] = ( long ) NULL;
  if( ( ( long * ) arena )[ 2 ] != ( long ) NULL )
	{
	  ( ( long * )( ( ( long * ) arena )[ 2 ] ) )[ 1 ] = 
		( long ) &( ( long * ) arena )[ 2 ];
	}
  if( firstInAllocatedChain == ( long * ) NULL )
	{
	  firstInAllocatedChain = &( ( long * ) arena )[ 2 ];
	}
  lastInAllocatedChain = &( ( long * ) arena )[ 2 ];


#if defined( USE_THREADS )
  if( newDeleteLock != NULL )
	{
	  newDeleteLock -> leave( nil );
	}
#endif

  return ( void * )( arena + doubleShift + doubleShift );

  /*                                                            */
  /*                                  +-- returned              */
  /*                                  |                         */
  /*    aSize a1efc0fe   o        o   V  data      c001deaf     */
  /*  +-------+-------+--|----+---|---+----....----+-------+    */
  /*  ^                  |        |                             */
  /*  |     prev <--...--+        +--...--> next                */
  /*  +-- arena                                                 */
  /*                                                            */

/* USE_ALLOC_CHAIN */
#endif
  //  PLAF -> memset( arena + doubleShift, 0, aSize );
  //  fprintf( stderr, "\nnew at %lx", ( long unsigned int ) arena + doubleShift );
#if defined( DECORATE_ALLOCATIONS )
  return ( void * )( arena + doubleShift );
#else
  return ( void * ) arena;
#endif
}

INLINE boolean checkForDelete( const void *aPointer )
{
  if( aPointer == null )
	{
	  PLAF -> rawErrorPrintf( "delete null" );
	  return false;
	}
  else
	{
	  long *arena = ( long * ) aPointer;
	  if( arena[ -1 ] != magicStart )
		{
		  if( arena[ -1 ] == magicDeleted )
			{
			  PLAF -> rawErrorPrintf
				( "double delete at %lx", ( long unsigned int ) aPointer );
			}
		  else
			{
			  PLAF -> 
				rawErrorPrintf( "wrong delete at %lx", ( long unsigned int ) aPointer );
			}
		  return false;
		}
	  else
		{
		  size_t len = ( size_t ) arena[ -2 ];
		  size_t rLen = ( len - 1 ) / shift + 1;
		  if( arena[ rLen ] != magicEnd )
			{
			  PLAF -> 
				rawErrorPrintf( "corrupted heap at %lx", 
								( long unsigned int ) aPointer );
			  return false;
			}
		}
	}
  return true;
}

INLINE void deleteOp( void *aPointer )
#if !defined(__SUNPRO_CC)
  OP_THROW( int )
#endif
{
#if defined( USE_THREADS )
  if( newDeleteLock != NULL )
	{
	  newDeleteLock -> enter( nil );
	}
#endif
  long *arena = ( long * ) aPointer;
#if defined( USE_ALLOC_CHAIN )
  arena -= 2;
  if( arena[ 1 ] != ( long ) NULL )
	{
	  ( ( long * )arena[ 1 ] )[ 0 ] = arena[ 0 ];
	}
  else
	{
	  lastInAllocatedChain = ( long * ) arena[ 0 ];
	}
  
  if( arena[ 0 ] != ( long ) NULL )
	{
	  ( ( long * )arena[ 0 ] )[ 1 ] = arena[ 1 ];
	}
  else
	{
	  firstInAllocatedChain = ( long * ) arena[ 1 ];
	}
  aPointer = ( void * ) arena;
#endif
  
#if defined( CHECK_DELETES )
  if( checkForDelete( aPointer ) )
	{
#endif
	  Platform *platform;

#if defined( PROFILE_MEM_ALLOC )
	  MemoryMonitor::dec( ( size_t ) arena[ -2 ], arena );
#endif
#if defined( DECORATE_ALLOCATIONS )
	  arena[ -1 ] = magicDeleted;
#endif
	  platform = Platform::getInstanceNow();
	  if( platform != ( Platform * ) NIL )
		{
		  platform -> deallocateMemory( arena 
#if defined( DECORATE_ALLOCATIONS )
										- 2
#endif
										 );
		}
	  else
		{
		  platform -> deallocateMemoryBootstrap( arena 
#if defined( DECORATE_ALLOCATIONS )
												 - 2
#endif
												  );
		}

	  //	  free( arena - 2 );
	  //	  fprintf( stderr, "\ndel at %lx", ( long unsigned int ) aPointer );
#if defined( CHECK_DELETES )
	}
#endif

#if defined( USE_THREADS )
  if( newDeleteLock != NULL )
	{
	  newDeleteLock -> leave( nil );
	}
#endif
}

#if defined( USE_ALLOC_CHAIN )
void dumpAllocatedByNew()
{
  long *end;
  long *point;
  Index count;
  
#if defined( USE_THREADS )
  test_( newDeleteLock != NULL );
  MGuard _lock( newDeleteLock, newDeleteLock );
#endif

  end = lastInAllocatedChain;
  point = firstInAllocatedChain;

  for( count = 0 ; ( point != ( long * ) NULL ) && ( point != end ) ; 
	   point = ( long * ) ( point[ 1 ] ), ++count )
	{
#if defined( USE_THREADS )
	  newDeleteLock -> leave( newDeleteLock );
#endif
	  DLOG( "Allocated: 0x%p", point );
#if defined( USE_THREADS )
	  newDeleteLock -> enter( newDeleteLock );
#endif
	}
  DLOG( "*** Totally allocated: %li, in %li chunks", 
							 MemoryMonitor::amount(), count );
}

#endif

#if defined( USE_THREADS )
void operatorNewInitThreads()
{
  Mutex *tmpLock;

  tmpLock = THR_SYSTEM -> mutex();
  TCAST( tmpLock, Object ) -> dontManage();
  newDeleteLock = tmpLock;
}
#endif

END_QR_NAMESPACE

#if !defined(__SUNPRO_CC) || ( defined(__SUNPRO_CC) && (__SUNPRO_CC >= 0x510) )
INLINE void *operator new ( size_t aSize ) STD_THROW( std::bad_alloc )
{
  return NS_PREFIX newOp( aSize );
}

INLINE void *operator new[] ( size_t aSize ) STD_THROW( std::bad_alloc )
{
  return NS_PREFIX newOp( aSize );
}

INLINE void operator delete ( void *aPtr ) throw()
{
  NS_PREFIX deleteOp( aPtr );
}

INLINE void operator delete[] ( void *aPtr ) throw()
{
  NS_PREFIX deleteOp( aPtr );
}

#if !defined( __BORLANDC__ )
INLINE void *operator new( size_t aSize, const std::nothrow_t& ) NOTHROW( )
{
  return NS_PREFIX newOp( aSize );
}

INLINE void *operator new[] ( size_t aSize, const std::nothrow_t& ) NOTHROW( )
{
  return NS_PREFIX newOp( aSize );
}
#endif

#if defined( __GNUC__ )
#if ( __GNUC__ > 2 ) || ( ( __GNUC__ == 2 ) && ( __GNUC_MINOR__ >= 9 ) )

INLINE void operator delete ( void *aPtr, const std::nothrow_t& ) OP_THROW( )
{
  NS_PREFIX deleteOp( aPtr );
}

INLINE void operator delete[] ( void *aPtr, const std::nothrow_t& ) OP_THROW( )
{
  NS_PREFIX deleteOp( aPtr );
}
#endif
#endif

/* __SUNPRO_CC */
#else
/* KISS */
INLINE void *operator new( size_t aSize )
{
  return NS_PREFIX newOp( aSize );
}

INLINE void operator delete( void *aPtr )
{
  NS_PREFIX deleteOp( aPtr );
}
#endif

#if defined(_INLINE)
#include "../src/Debug.ipp"
#endif


#if defined(_INLINE)
#include "../src/Top.ipp"
#endif

/* __NEW_OPERATOR_IPP__ */
#endif

/*
 * $Log: new-operator.ipp,v $
 * Revision 1.1.1.1  2000/07/19 16:43:00  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.4  2000/04/09 12:00:48  god
 * CVS Log keyword correction finished
 *
 * Revision 1.3  2000/04/09 11:29:40  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.2  2000/04/05 17:19:42  god
 * Dynamic modules, askUser (+readline) dlsym/dladdr-based Backtrace
 *
 * Revision 1.1.1.1  2000/04/01 14:07:28  god
 * Imported sources
 *
 * Revision 1.3  1999/05/22 13:00:32  philogelos
 * Merging sources back from SPARC
 *
 * Revision 1.2  1999/03/03 19:09:31  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.1  1999/02/28 16:01:18  philogelos
 * Created from .cpp
 *
 * Revision 1.1.1.1  1998/11/25 20:11:01  philogelos
 * Quercus Robusta
 *
 * Revision 1.1  1998/07/09 09:30:38  philogelos
 * new files added to the repository
 * */
