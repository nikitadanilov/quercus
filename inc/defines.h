//-*-C++-*-

/*  inc/defines.h  */

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

#ifndef __DEFINES_H__

#define __DEFINES_H__

#include "platform/platform-specific.h"
#include "config.h"
#include "build.h"

/** If defined, some classes define <em>int tester( int )</em> or
	<em>static int tester( int )</em> method.
*/
#define TESTING

/** If defined, optional inlining will be turned on and .cpp
	files will include .ipp
*/
/* #define _INLINE */

/** 
	If defined some classes will define (and use) void operator new()
*/
#define USE_PER_CLASS_NEW

/**
   If defined, each memory allocation by operator new 
   (cf. new-operator.hpp) will be logged to MemoryMonitor.

   @see MemoryMonitor
*/
#define PROFILE_MEM_ALLOC

/** Define this if you want template implementations 
	(.tpp files) to be included wherever template declarations
	(.hpp files) are. */
#define INCLUDE_TEMPLATES

/** Define this is your compiler properly supports
	C++ throw clause in method declarations/definitions 
	(egcs does).
*/
#define USE_THROWS

/** If defined, some classes (notable exceptions) are derived from
	standard C++ library classes (located in namespace std::)
*/
/* #define USE_STL */

#define USE_TYPEID

/** 
	If defined, thread support will be compiled in.
*/
#define USE_THREADS

/** Define this if your compiler wrongly assumes you 
	have to return value in control flow path with throw in it */
/* #define RET_AFTER_THROW */

#define USE_NAMESPACE

#if defined( WANT_TESTING )
#define TESTING
#elif defined( UNWANT_TESTING )
#if defined( TESTING )
#undef TESTING
#endif
#endif

#if defined( WANT__INLINE )
#define _INLINE
#elif defined( UNWANT__INLINE )
#if defined( _INLINE )
#undef _INLINE
#endif
#endif

#if defined( WANT_USE_PER_CLASS_NEW )
#define USE_PER_CLASS_NEW
#elif defined( UNWANT_USE_PER_CLASS_NEW )
#if defined( USE_PER_CLASS_NEW )
#undef USE_PER_CLASS_NEW
#endif
#endif

#if defined( WANT_PROFILE_MEM_ALLOC )
#define PROFILE_MEM_ALLOC
#elif defined( UNWANT_PROFILE_MEM_ALLOC )
#if defined( PROFILE_MEM_ALLOC )
#undef PROFILE_MEM_ALLOC
#endif
#endif

#if defined( WANT_INCLUDE_TEMPLATES )
#define INCLUDE_TEMPLATES
#elif defined( UNWANT_INCLUDE_TEMPLATES )
#if defined( INCLUDE_TEMPLATES )
#undef INCLUDE_TEMPLATES
#endif
#endif

#if defined( WANT_USE_THROWS )
#define USE_THROWS
#elif defined( UNWANT_USE_THROWS )
#if defined( USE_THROWS )
#undef USE_THROWS
#endif
#endif

#if defined( WANT_USE_STL )
#define USE_STL
#elif defined( UNWANT_USE_STL )
#if defined( USE_STL )
#undef USE_STL
#endif
#endif

#if defined( WANT_USE_TYPEID )
#define USE_TYPEID
#elif defined( UNWANT_USE_TYPEID )
#if defined( USE_TYPEID )
#undef USE_TYPEID
#endif
#endif

#if defined( WANT_USE_THREADS )
#define USE_THREADS
#elif defined( UNWANT_USE_THREADS )
#if defined( USE_THREADS )
#undef USE_THREADS
#endif
#endif

#if defined( WANT_RET_AFTER_THROW )
#define RET_AFTER_THROW
#elif defined( UNWANT_RET_AFTER_THROW )
#if defined( RET_AFTER_THROW )
#undef RET_AFTER_THROW
#endif
#endif

#if defined( WANT_mutable )
#elif defined( UNWANT_mutable )
/** Define ``mutable'' to be void if your compiler
	doesn't support this keyword correctly. */
#define mutable
#endif

#if defined( WANT_USE_NAMESPACE )
#define USE_NAMESPACE
#elif defined( UNWANT_USE_NAMESPACE )
#if defined( USE_NAMESPACE )
#undef USE_NAMESPACE
#endif
#endif

/** Needed for size_t in ::operator new() declarations */
#include <sys/types.h>

/**************************************************************************/
/**                                                                      **/
/**************************************************************************/

#if defined( WIN32 )
/** Boolean type. */
typedef unsigned char boolean;
#else
/** Boolean type. */
typedef int boolean;
#endif

/** Type for indices within strings, arrays etc. */
typedef long Index; 

/** 16-bit values. (Used only in UNICODE handling) */
typedef unsigned short int int16;
/* typedef u_int16_t int16; */

typedef int16 unichar;

/** true truth value. */
#define true ( ( boolean ) 1 )

/** false truth value. */
#define false ( ( boolean ) 0 )

/** Null object. */
#define null ( ( const Top * ) 0L )

#define nil  ( ( Top * ) 0L )

#ifdef NULL
#undef NULL
#endif

/** Null pointer. */
#define NULL 0L

#define NIL  0L


/** Implication. */
#define ergo( a, b )     ( !( a ) || ( b ) )

/** Equivalence. */
#define equiv( a, b )     ( ergo( a, b ) && ergo( b, a ) )

/** Marks interface (ie, type). */
#define interface    class

/** Marks class containing abstract methods. */
#define abstract 

#if defined( _INLINE )
#define INLINE inline
#else
#define INLINE
#endif

#if !defined(__SUNPRO_CC)
#include <typeinfo>
#else
#include <typeinfo.h>
#include <exception.h>
#endif

#if defined( mutable )
// if compiler doesn't support mutable keyword
#define MUTATE_MEMBER( MEMBER, TYPE ) ( ( ( TYPE * ) this ) -> MEMBER )
#else
// if compiler does support mutable keyword
#define MUTATE_MEMBER( MEMBER, TYPE ) MEMBER
#endif

#if defined( USE_NAMESPACE )
#define BEGIN_QR_NAMESPACE namespace QR {
#define   END_QR_NAMESPACE }
#define NS_PREFIX QR::
#else
#define BEGIN_QR_NAMESPACE 
#define   END_QR_NAMESPACE 
#define NS_PREFIX
#endif

/* XXX move all code from here to special file */
extern char debugFileId[];
extern char cvsid[];

/**
   Dummy function to fool compiler.
*/
static char *cheatCompiler()
{
  cheatCompiler();
  debugFileId[ 0 ] = ' ';
  return cvsid;
}

#if defined( USE_THROWS )

BEGIN_QR_NAMESPACE
class RuntimeError;
END_QR_NAMESPACE

/* will be not required when compilers will support ... 
   and __VA_ARGS__ in macros */
#define _tand ,
#define DEF_THROW RuntimeError *
#define NOTHROWS throw ( DEF_THROW )
#define THROWS( A ) throw ( DEF_THROW, A )

#else

#define _tand
#define DEF_THROWS
#define NOTHROWS
#define THROWS( A )

#endif

#if defined(__GNUC__)
#define NORETURN __attribute__ ( ( noreturn ) )
#define PRINTF_ALIKE( FORMAT, FIRST_ARG ) __attribute__ ( ( format ( printf, FORMAT, FIRST_ARG ) ) ) 
#else
#define NORETURN
#define PRINTF_ALIKE( FORMAT, FIRST_ARG )
#endif

/** this is ,,horrible kludge'' against preprocessor. Following
	macros take TYPE as the second argument, but type can contain 
	commas it it!
	e.g. FOO< BAR, BAZ > */
#define commaForCpp ,

#if defined(__SUNPRO_CC) && (__SUNPRO_CC < 0x510)

#define DCAST( EXPR, TYPE ) brainDamagedDynamicCast( ( Top * ) ( EXPR ), ( TYPE * ) NIL )

#if defined(INCLUDE_TEMPLATES)

#define __COMMON_FROM_DEFINES__
#include "src/common.cpp"
#undef __COMMON_FROM_DEFINES__

#else

interface Top;
template< class X > X *brainDamagedDynamicCast( Top *aValue, X * );

#endif

#else

#define DCAST( EXPR, TYPE ) dynamic_cast< TYPE * >( ( Top * ) ( EXPR ) )

#endif

#define TCAST( EXPR, TYPE ) castOrThrow( ( Top * ) ( EXPR ), ( TYPE * ) NIL )

#if defined(INCLUDE_TEMPLATES)

#define __COMMON_FROM_DEFINES__
#include "src/common.cpp"
#undef __COMMON_FROM_DEFINES__

#else

class Top;
class Debug;
template< class X > X *castOrThrow( Top *aValue, X * );

#endif

#if defined( RET_AFTER_THROW )
#define RET_THROW( E ) return( E )
#else
#define RET_THROW( E ) 
#endif

/* __DEFINES_H__ */
#endif
