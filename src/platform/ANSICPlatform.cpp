// -*-C++-*- 

/*  src/platform/ANSICPlatform.cpp  */

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



/* $Id: ANSICPlatform.cpp,v 1.4 2002/03/09 15:26:08 philogelos Exp $ */
#if !defined(_INLINE)
static char cvsid[] = "@(#)$Id: ANSICPlatform.cpp,v 1.4 2002/03/09 15:26:08 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif

#include "platform/ANSICPlatform.hpp"
#include "exceptions/OutOfMemory.hpp"
#include "String.hpp"
#include "Debug.hpp"

#include "exceptions/InvalidArgument.hpp"

#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdarg.h>

#if defined( USE_BOEHM_GC )
#include <gc.h>
#endif

#if defined( ASK_USER_USE_READLINE )

#include "platform/threads/MGuard.hpp"

extern "C"
{
#include <readline/readline.h>
#include <readline/history.h>

/* for strncasecmp */
#define _XPG4_2
#include <strings.h>
#include <string.h>
}
#endif

#if defined( __GNUC__ ) && !defined( __linux__ )
extern "C" 
int vsnprintf( char *str, size_t n, const char *format, va_list ap );
#endif

// extern int errno;

#if defined( USE_BOEHM_GC ) && ( defined( MEMORY_LEAK_TEST ) || defined( USE_ALLOC_CHAIN ) )
#warning "There is no much sense in using GC along with MEMORY_LEAK_TEST or USE_ALLOC_CHAIN"
#endif

extern "C"
{
#if !defined( __linux__ )
  int sprintf( char *s, const char * format, /* args */ ...) 
	PRINTF_ALIKE( 2, 3 );
  int fprintf( FILE *strm, const char *format, /* args */ ... ) 
	PRINTF_ALIKE( 2, 3 );

  char  *strcpy( char *dst, const char *src );
  int    strcmp( const char *s1, const char *s2 );
  size_t strlen( const char *s );
  char  *strcat( char *dst, const char *src );
#if !defined( __BORLANDC__ ) && ( !defined(__SUNPRO_CC) || ( defined(__SUNPRO_CC) && (__SUNPRO_CC < 0x510) ) )
  char  *strchr( const char *s, int c );
#endif
  long   strtol( const char *str, char **endptr, int base );

  void *memcpy( void *s1, const void *s2, size_t n );
  void *memset( void *s, int c, size_t n );

/* __linux__ */
#endif

#if defined( USE_BOEHM_GC )

  void *GC_malloc( size_t size_in_bytes );
  void GC_free( void *object_addr );

#endif
}

BEGIN_QR_NAMESPACE

ANSICPlatform::ANSICPlatform()
{
  callsNum = 0;
}

ANSICPlatform::~ANSICPlatform()
{}

void ANSICPlatform::sprintf( char *s, const char * format, /* args */ ... ) 
{
  preC_( format != NULL );
  preC_( s != NULL );

  va_list args;

  va_start( args, format );
  this -> vsprintf( s, format, args );
  va_end(args);
  ++callsNum;
}

void ANSICPlatform::vsprintf( char *s, const char *format, va_list raw )
{
  preC_( format != NULL );
  preC_( s != NULL );

  ::vsprintf( s, format, raw );
  ++callsNum;
}

Index ANSICPlatform::printfLength( const char * format, /* args */ ... )
{
  preC_( format != NULL );

  va_list args;
  Index result;
  
  va_start( args, format );

  result = this -> vprintfLength( format, args );
  va_end(args);
  ++callsNum;
  return result;
}

Index ANSICPlatform::vprintfLength( const char * format, va_list raw )
{
  preC_( format != NULL );

/* Borland has no vsnprintf */
#if defined( __BORLANDC__ )
  static FILE *devNull = NULL;

  if( devNull == NULL )
	{
   	devNull = fopen( "NUL", "r+" );
   }
   test_( devNull != NULL );
   return vfprintf( devNull, format, raw );
/* __BORLANDC__ */
#else
  int result;
#if defined( SNPRINTF_RETURNS_ERROR )
  static char *dummyBuf = NIL;
  static long int size = 2;
#else
  char dummyBuf[ 2 ];
#endif

#if defined( SNPRINTF_RETURNS_ERROR )
  if( dummyBuf == NULL )
	{
	  dummyBuf = new char[ size ];
	}
  while( true )
	{
	  result = ::VSNPRINTF( dummyBuf, size, format, raw );
	  if( result == -1 )
		{
		  delete []dummyBuf;
		  size *= 2;
		  dummyBuf = new char[ size ];
		}
	  else
		{
		  break;
		}
	}
#else
  result = ::VSNPRINTF( dummyBuf, 2, format, raw );
#endif
  postC_( result >= 0 );
  return result;
/* !__BORLANDC__ */
#endif
}

void ANSICPlatform::rawErrorPrintf( const char * format, /* args */ ... ) 
{
  preC_( format != NULL );

  va_list raw;

  va_start( raw, format );
  this -> rawErrorVPrintf( format, raw );
  va_end( raw );
  ++callsNum;
}

void ANSICPlatform::rawErrorVPrintf( const char * format, va_list raw ) 
{
  preC_( format != NULL );

  vfprintf( stderr, format, raw );
  ++callsNum;
}

static Index maxOffset;

#if defined( ASK_USER_USE_READLINE )
static Mutex *readlineSerializer = NULL;
static char *labels[ ASK_USER_MAX_CHOICES ];
static Index offset;
static char *completer( const char *text, int state )
{
  if( state == 0 )
	{
	  offset = -1;
	}
  for( ++offset ; offset <= maxOffset ; ++offset )
	{
	  if( labels[ offset ] != NULL )
		{
		  if( strncasecmp( labels[ offset ], text, strlen( text ) ) == 0 )
			{
			  return strcpy( ( char * ) 
							 malloc( strlen( labels[ offset ] ) + 1 ),
							 labels[ offset ] );
			}
		}
	}
  return NULL;
}
#endif

Index ANSICPlatform::askUser( const char *caption,
							  const char *prompt, ... )
{
  va_list args;
  Index i;
  Index ind[ ASK_USER_MAX_CHOICES ];
  char  buffer[ 255 ];
  Index answer;

  while( true )
	{
	  rawErrorPrintf( "\n%s\n", caption );

	  va_start( args, prompt );
	  for( i = 0 ; i < ASK_USER_MAX_CHOICES ; ++i )
		{
		  Index choice;
		  char *label;
		  char *text;

		  choice = va_arg( args, Index );
		  label  = va_arg( args, char * );
		  text   = va_arg( args, char * );
		  if( label == NULL )
			{
			  break;
			}
		  test_( label != NULL );
		  ind[ i ] = choice;
#if defined( ASK_USER_USE_READLINE )
		  labels[ i ] = label;
		  rawErrorPrintf( "[%s] %s\n", label, text );
#else
		  rawErrorPrintf( "%3li: [%s] %s\n", i + 1, label, text );
#endif
		  maxOffset = i;
		}
	  va_end( args );
  
#if defined( ASK_USER_USE_READLINE )
	  {
		if( readlineSerializer == NULL )
		  {
			readlineSerializer = THR_SYSTEM -> mutex();
			TCAST( readlineSerializer, Object ) -> dontManage();
		  }
		MGuard _( readlineSerializer, this );
		char *line;

		char * ( * oldCompleter )( const char *, int );
		int oldAppendChar;

		oldCompleter = rl_completion_entry_function;
		oldAppendChar = rl_completion_append_character;

		rl_completion_entry_function = completer;
		rl_completion_append_character = 0;
		do
		  {
			line = ( ( char *(*)( const char * ) ) readline )( prompt );
		  }
		while( ( line == NULL ) || ( line[ 0 ] == 0 ) );
		( ( void (*)( const char * ) ) add_history )( line );
		strncpy( buffer, line, sizeof buffer );
		answer = -1;
		for( i = 0 ; i <= maxOffset ; ++i )
		  {
			test_( labels[ i ] != NULL );
			if( strcmp( labels[ i ], line ) == 0 )
			  {
				answer = i;
				break;
			  }
		  }
		free( line );

		rl_completion_entry_function = oldCompleter;
		rl_completion_append_character = oldAppendChar;
	  }
#else
	  do
		{
		  rawErrorPrintf( "%s", prompt );
		  fgets( buffer, sizeof buffer, stdin );
		}
	  while( ( buffer[ 0 ] == '\n' ) || ( buffer[ 0 ] == '\r' ) );
	  answer = String( buffer ).toNum( 10 ) - 1;
#endif
	  if( strcmp( buffer, "frobnicate" ) == 0 )
		{
		  rawErrorPrintf( "\nfrobnicate what?!\n" );
		  continue;
		}
	  if( strcmp( buffer, "foo" ) == 0 )
		{
		  rawErrorPrintf( "\nBAR\n" );
		  continue;
		}
	  if( ( answer < 0 ) || ( answer > maxOffset ) )
		{
		  rawErrorPrintf( "\n`%.*s' --- huh?", ( int ) sizeof buffer, buffer );
		}
	  else
		{
		  break;
		}
	}
  ++callsNum;
  return ind[ answer ];
}

char  *ANSICPlatform::strcpy( char *dst, const char *src )
{
  preC_( dst != NULL );
  preC_( src != NULL );

  ++callsNum;
  return ::strcpy( dst, src );
}

int    ANSICPlatform::strcmp( const char *s1, const char *s2 )
{
  preC_( s1 != NULL );
  preC_( s2 != NULL );

  ++callsNum;
  return ::strcmp( s1, s2 );
}

Index ANSICPlatform::strlen( const char *s )
{
  preC_( s != NULL );

  ++callsNum;
  return ::strlen( s );
}

char  *ANSICPlatform::strcat( char *dst, const char *src )
{
  preC_( dst != NULL );
  preC_( src != NULL );

  ++callsNum;
  return ::strcat( dst, src );
}

char  *ANSICPlatform::strchr( const char *s, int c )
{
  preC_( s != NULL );

  ++callsNum;
  return ( char * ) ::strchr( s, c );
}

long ANSICPlatform::strtol( const char *str, char **endptr, int base ) THROWS( InvalidArgument * )
{
  preC_( str != NULL );

  long result;

  ++callsNum;
  result = ::strtol( str, endptr, base );
  if( errno == ERANGE )
	{
	  throw new 
		InvalidArgument( "strtol: value is outside the range of representable values", 
						 ( Top * ) nil );
	}
  if( ( errno == EINVAL ) && ( result == 0 ) )
	{
	  throw new 
		InvalidArgument( "strtol: no conversion could be performed", 
						 ( Top * ) nil );
	}
  if( ( endptr != ( char ** ) NULL ) && ( ( ** endptr ) != ( char ) 0 ) )
	{
	  throw new 
		InvalidArgument( "strtol: garbage detected", 
						 ( Top * ) nil );
	}
  return result;
}

int ANSICPlatform::memcmp( void *s1, const void *s2, Index n )
{
  preC_( s1 != NULL );
  preC_( s2 != NULL );

  ++callsNum;
  return ::memcmp( s1, s2, n );
}

void *ANSICPlatform::memchr( const void *s, int c, Index n )
{
  preC_( s != NULL );
  preC_( n >= 0 );

  ++callsNum;
  return ( void * ) ::memchr( s, c, n );
}

void *ANSICPlatform::memcpy( void *s1, const void *s2, Index n )
{
  preC_( s1 != NULL );
  preC_( s2 != NULL );

  ++callsNum;
  return ::memcpy( s1, s2, n );
}

void *ANSICPlatform::memset( void *s, int c, Index n )
{
  preC_( s != NULL );

  ++callsNum;
  return ::memset( s, c, n );
}

void *ANSICPlatform::allocateMemory( Index aSize ) THROWS( OutOfMemory * )
{
  char *arena;

#if defined( USE_BOEHM_GC )
  arena = ( char * ) GC_malloc( aSize );
#else
  arena = ( char * ) malloc( aSize );
#endif
  if( arena == NULL )
	{
	  throw getOutOfMemory();
	}
  this -> memset( arena, 0, aSize );
  return arena;
}

void  ANSICPlatform::deallocateMemory( void *aPointer )
{
  if( aPointer != NIL )
	{
#if defined( USE_BOEHM_GC )
	  GC_free( aPointer );
#else
	  ::free( aPointer );
#endif
	}
}

void *ANSICPlatform::allocateMemoryBootstrapANSI( Index aSize )
{
  char *arena;

#if defined( USE_BOEHM_GC )
  arena = ( char * ) GC_malloc( aSize );
#else
  arena = ( char * ) malloc( aSize );
#endif
  ::memset( arena, 0, aSize );
  return arena;
}

void  ANSICPlatform::deallocateMemoryBootstrapANSI( void *aPointer )
{
  if( aPointer != NIL )
	{
#if defined( USE_BOEHM_GC )
	  GC_free( aPointer );
#else
	  ::free( aPointer );
#endif
	}
}


void **ANSICPlatform::stdargToArrayLength( va_list aList, Index aLength )
{
  void **result;

  result = new void *[ aLength ];
  for( Index i = 0 ; i < aLength ; ++i )
	{
	  result[ i ] = va_arg( aList, void * );
	}
  return result;
}

Index  ANSICPlatform::stdargLengthFence( va_list aList, void *aFenceValue )
{
  Index i;

  for( i = 1 ; va_arg( aList, void * ) != aFenceValue ; ++i )
	{}
  return i;
}

Index  ANSICPlatform::stdargLengthPredFunc( va_list aList, 
											boolean ( *aPred )( void * ) )
{
  preC_( aPred != NULL );
  Index i;

  for( i = 1 ; aPred( va_arg( aList, void * ) ) ; ++i )
	{}
  return i;
}

Index  ANSICPlatform::stdargLengthPredMeth( va_list aList, 
											Top *anObject,
											boolean ( Top::*aPred )( void* ) )
{
  preC_( anObject != NULL );
  preC_( aPred != ( boolean ( Top::* )( void* ) ) NULL );
  Index i;

  for( i = 1 ; ( anObject ->* aPred )( va_arg( aList, void * ) ) ; ++i )
	{}
  return i;
}


boolean ANSICPlatform::equals( const Top *anOther ) const
{
  return( DCAST( anOther, ANSICPlatform ) == this );
}

Top *ANSICPlatform::clone() const
{
  return ( Top * ) this;
}

OutOfMemory *ANSICPlatform::getOutOfMemory()
{
  return outOfMemoryException;
}

OutOfMemory *ANSICPlatform::outOfMemoryException = new OutOfMemory( "malloc in ANSICPlatform::allocateMemory failed", null );

END_QR_NAMESPACE

#if defined(_INLINE)
#include "../src/Debug.ipp"
#include "../src/String.ipp"
#endif


/*
 * $Log: ANSICPlatform.cpp,v $
 * Revision 1.4  2002/03/09 15:26:08  philogelos
 * fight bit rot
 *
 * Revision 1.3  2000/10/20 20:29:20  philogelos
 * Simplifications through using of NopThreads
 *
 * Revision 1.2  2000/08/30 12:33:22  philogelos
 * update THROWS to correspond to the actual throws
 *
 * Revision 1.1.1.1  2000/07/19 16:51:16  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.7  2000/04/29 15:02:10  god
 * explicit vsnprintf prototype removed on __linux__
 *
 * Revision 1.6  2000/04/09 12:00:49  god
 * CVS Log keyword correction finished
 *
 * Revision 1.5  2000/04/09 11:29:43  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.4  2000/04/07 17:15:39  god
 * readline completion made case-insensitive
 *
 * Revision 1.3  2000/04/05 17:19:43  god
 * Dynamic modules, askUser (+readline) dlsym/dladdr-based Backtrace
 *
 * Revision 1.2  2000/04/05 16:44:11  god
 * readline-based ::askUser()
 *
 * Revision 1.1.1.1  2000/04/01 14:07:34  god
 * Imported sources
 * */
