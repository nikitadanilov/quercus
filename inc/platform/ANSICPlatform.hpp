// -*-C++-*- 

/*  inc/platform/ANSICPlatform.hpp  */

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


#ifndef __ANSICPLATFORM_HPP__
#define __ANSICPLATFORM_HPP__

/* $Id: ANSICPlatform.hpp,v 1.2 2000/08/30 12:20:35 philogelos Exp $ */

#include "platform/Platform.hpp"
#include "defines.h"

/* #define USE_BOEHM_GC */ /**/
#define ASK_USER_MAX_CHOICES 255
#define ASK_USER_USE_READLINE

#if defined( WANT_USE_BOEHM_GC )

/**
   If this defined ANSICPlatform class will
   use GC_malloc and GC_free to allocate/deallocate
   memory. You will need the libgc.a library to use
   these functions.
*/
#define USE_BOEHM_GC
#elif defined( UNWANT_USE_BOEHM_GC )
#if defined( USE_BOEHM_GC )
#undef USE_BOEHM_GC
#endif
#endif

#if defined( WANT_ASK_USER_MAX_CHOICES )
#if defined( ASK_USER_MAX_CHOICES )
#undef ASK_USER_MAX_CHOICES
#endif
#define ASK_USER_MAX_CHOICES WANT_ASK_USER_MAX_CHOICES
#endif

#if defined( WANT_ASK_USER_USE_READLINE )
#define ASK_USER_USE_READLINE
#elif defined( UNWANT_ASK_USER_USE_READLINE )
#if defined( ASK_USER_USE_READLINE )
#undef ASK_USER_USE_READLINE
#endif
#endif


#if defined( __linux__ ) || defined( WIN32 )

/**
   Define this if you system snprintf() function
   returns -1 when buffer is too small. LINUX and
   Win32 are autodetected.
*/
#define SNPRINTF_RETURNS_ERROR
#endif

#if defined( WIN32 )
#define VSNPRINTF _vsnprintf
#else
#define VSNPRINTF vsnprintf
#endif


BEGIN_QR_NAMESPACE

class OutOfMemory;
class InvalidArgument;

/**
   ANSI C platform.
   This is abstract class. Many other platforms
   will inherit from this class and implement the rest of the
   functionality.

   @author Philogelos
   @created
*/
abstract class ANSICPlatform : public Platform
{

  /**
	 Nop.
	*/
public: ANSICPlatform();

  /**
	 Nop.
	*/
public: virtual ~ANSICPlatform();



  /**
	 Calls ANSIC sprintf() function.
  */
public: virtual void sprintf( char *s, const char * format, /* args */ ... ) 
  PRINTF_ALIKE( 3, 4 );

  /**
	 Calls ANSIC vsprintf() function.
  */
public: virtual void vsprintf( char *s, const char *format, va_list raw );

  /**
	 Returns the number of characters that would be output
	 by the call to printf( format, args... ).
  */
public: virtual Index printfLength( const char * format, /* args */ ... ) 
  PRINTF_ALIKE( 2, 3 );

  /**
	 Returns the number of characters that would be output
	 by the call to vprintf( format, raw ).
  */
public: virtual Index vprintfLength( const char * format, va_list raw );

  /**
	 Printfs result to the stderr.
  */
public: virtual void rawErrorPrintf( const char * format, /* args */ ... ) 
  PRINTF_ALIKE( 2, 3 );

  /**
	 Printfs result to the stderr.
  */
public: virtual void rawErrorVPrintf( const char * format, va_list raw );

public: virtual Index askUser( const char *caption,
							  const char *prompt, ... );
  /**
	 Calls ANSIC strcpy() function.
  */
public: virtual char  *strcpy( char *dst, const char *src );

  /**
	 Calls ANSIC strcmp() function.
  */
public: virtual int    strcmp( const char *s1, const char *s2 );

  /**
	 Calls ANSIC strlen() function.
  */
public: virtual Index  strlen( const char *s );

  /**
	 Calls ANSIC strcat() function.
  */
public: virtual char  *strcat( char *dst, const char *src );

  /**
	 Calls ANSIC strchr() function.
  */
public: virtual char  *strchr( const char *s, int c );

  /**
	 Calls ANSIC strtol() function.
	 Throws InvalidArgument if number is beyond of representable
	 range, no conversion can be performed or garbage lies after
	 last converted character.
  */
public: virtual long   strtol( const char *str, char **endptr, int base ) THROWS( InvalidArgument * );



  /**
	 Calls ANSIC memcmp() function.
  */
public: virtual int   memcmp( void *s1, const void *s2, Index n );

  /**
	 Calls ANSIC memchr() function.
  */
public: virtual void *memchr( const void *s, int c, Index n );

  /**
	 Calls ANSIC memcpy() function.
  */
public: virtual void *memcpy( void *s1, const void *s2, Index n );

  /**
	 Calls ANSIC memset() function.
  */
public: virtual void *memset( void *s, int c, Index n );


  /**
	 Calls ANSIC malloc() function or GC_malloc()
	 if USE_BOEHM_GC defined.

	 @see USE_BOEHM_GC
	 @see #deallocateMemory
  */
public: virtual void *allocateMemory( Index aSize ) THROWS( OutOfMemory * );

  /**
	 Calls ANSIC free() function or GC_free()
	 if USE_BOEHM_GC defined.

	 @see USE_BOEHM_GC
	 @see #allocateMemory
  */
public: virtual void  deallocateMemory( void *aPointer );

public: static void *allocateMemoryBootstrapANSI( Index aSize );
public: static void  deallocateMemoryBootstrapANSI( void *aPointer );

public: virtual void **stdargToArrayLength( va_list aList, Index aLength );
public: virtual Index  stdargLengthFence( va_list aList, void *aFenceValue );
public: virtual Index  stdargLengthPredFunc( va_list aList, 
											 boolean ( *aPred )( void * ) );
public: virtual Index  stdargLengthPredMeth( va_list aList, 
											 Top *anObject,
											 boolean ( Top::*aPred )( void* ) );

  /**
	*/
public: virtual boolean equals( const Top *anOther ) const;

  /**
	*/
public:  virtual Top *clone() const;


  /**
	 Returns static instance of OutOfMemory exception.
	 Thrown when allocateMemory() fails.

	 @see #allocateMemory()
	 @see #outOfMemoryException
  */
public:  static OutOfMemory *getOutOfMemory();

  /**
	 Total number of calls to user-visible methods of this 
	 object.
  */
protected: Index callsNum;

  /** Instance of OutOfMemory allocated in advance and thrown when 
	  malloc failes. 
	  
	  Hopefully, we shall have enough memory to allocate static
	  variables.
	  
	  @see #getOutOfMemory()
	  @see #allocateMemory()
  */
protected: static OutOfMemory *outOfMemoryException;
};


/** 
	Macros to convert va_list arg to array of void *s.
*/
#define nullTerminatedVaListToArray( arg, length, array ) \
  do { \
    va_list _nullTerminatedVaListToArray_args; \
    \
    va_start( _nullTerminatedVaListToArray_args, arg ); \
    length = TCAST( PLAF, ANSICPlatform ) -> \
         stdargLengthFence( _nullTerminatedVaListToArray_args, NULL ); \
    va_end( _nullTerminatedVaListToArray_args ); \
    \
    va_start( _nullTerminatedVaListToArray_args, arg ); \
    array = TCAST( PLAF, ANSICPlatform ) -> \
         stdargToArrayLength( _nullTerminatedVaListToArray_args, length ); \
    va_end( _nullTerminatedVaListToArray_args ); \
  } while( false )

END_QR_NAMESPACE

/*
 * $Log: ANSICPlatform.hpp,v $
 * Revision 1.2  2000/08/30 12:20:35  philogelos
 * THROWS clauses updates to correspond to the real throws.
 *
 * Revision 1.1.1.1  2000/07/19 17:12:57  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.4  2000/04/09 12:00:47  god
 * CVS Log keyword correction finished
 *
 * Revision 1.3  2000/04/09 11:29:36  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.2  2000/04/05 16:43:59  god
 * readline-based ::askUser()
 *
 * Revision 1.1.1.1  2000/04/01 14:07:47  god
 * Imported sources
 * */

/* __ANSICPLATFORM_HPP__ */
#endif
