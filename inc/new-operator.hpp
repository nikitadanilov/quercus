//-*-C++-*-

/*  inc/new-operator.hpp  */


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


#ifndef __NEW_OPERATOR_HPP__

#define __NEW_OPERATOR_HPP__

/* $Id: new-operator.hpp,v 1.2 2000/10/20 20:29:19 philogelos Exp $ */

#if !defined(__SUNPRO_CC)
#include <new>
#else
#include <new.h>
#endif

#include <sys/types.h>
#include "defines.h"

#define DECORATE_ALLOCATIONS
#define CHECK_DELETES
#define USE_ALLOC_CHAIN

#if defined( WANT_DECORATE_ALLOCATIONS )
#define DECORATE_ALLOCATIONS
#elif defined( UNWANT_DECORATE_ALLOCATIONS )
#if defined( DECORATE_ALLOCATIONS )
#undef DECORATE_ALLOCATIONS
#endif
#endif

#if defined( WANT_CHECK_DELETES )
#define CHECK_DELETES
#elif defined( UNWANT_CHECK_DELETES )
#if defined( CHECK_DELETES )
#undef CHECK_DELETES
#endif
#endif

#if defined( WANT_USE_ALLOC_CHAIN )
#define USE_ALLOC_CHAIN
#elif defined( UNWANT_USE_ALLOC_CHAIN )
#if defined( USE_ALLOC_CHAIN )
#undef USE_ALLOC_CHAIN
#endif
#endif


/** New operator.*/
#if !defined(__SUNPRO_CC) || ( defined(__SUNPRO_CC) && (__SUNPRO_CC >= 0x510) )
#define OP_THROW( exc ) throw( exc )
#define NOTHROW()       throw()
#else
#define OP_THROW( exc )
#define NOTHROW()
#endif

#if defined( __GNUC__ )
#if ( __GNUC__ < 2 ) || ( ( __GNUC__ == 2 ) && ( __GNUC_MINOR__ < 9 ) )
#define STD_THROW( exc )
#else
#define STD_THROW( exc ) OP_THROW( exc )
#endif
#elif defined( __BORLANDC__ )
#define STD_THROW( exc )
#else
#define STD_THROW( exc ) OP_THROW( exc )
#endif

#if !defined(__SUNPRO_CC) || ( defined(__SUNPRO_CC) && (__SUNPRO_CC >= 0x510) )
INLINE void *operator new ( size_t ) STD_THROW( std::bad_alloc );
INLINE void *operator new[] ( size_t ) STD_THROW( std::bad_alloc );
INLINE void operator delete ( void * ) NOTHROW();
INLINE void operator delete[] ( void * ) NOTHROW();
#if !defined( __BORLANDC__ )
INLINE void *operator new( size_t, const std::nothrow_t& ) NOTHROW( );
INLINE void *operator new[] ( size_t, const std::nothrow_t& ) NOTHROW( );
#endif
#if defined( __GNUC__ )
#if ( __GNUC__ > 2 ) || ( ( __GNUC__ == 2 ) && ( __GNUC_MINOR__ >= 9 ) )
INLINE void operator delete ( void *, const std::nothrow_t& ) throw();
INLINE void operator delete[] ( void *, const std::nothrow_t& ) throw();
#endif
#endif

/* XXX they don't throw ints of course, but Borland
	makes wrong number of macro args an _error_ */
INLINE void *newOp( size_t ) OP_THROW( int );
INLINE void deleteOp( void * ) OP_THROW( int );

/* old __SUNPRO_CC */
#else
/* KISS */
void *operator new( size_t );
void operator delete( void * );

INLINE void *newOp( size_t );
INLINE void deleteOp( void * );

#endif

BEGIN_QR_NAMESPACE

INLINE boolean checkForDelete( const void *aPointer );

extern long  magicStart;
extern long  magicEnd;
extern long  magicDeleted;

#if defined( USE_ALLOC_CHAIN )
void dumpAllocatedByNew();
/* USE_ALLOC_CHAIN */
#endif

void operatorNewInitThreads();

END_QR_NAMESPACE

/* __NEW_OPERATOR_HPP__ */
#endif
