// -*-C++-*- 

/*  src/platform/MinimalPlatform.cpp  */

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

/* strtol from FreeBSD */
/*-
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */


/* $Id: MinimalPlatform.cpp,v 1.1.1.1 2000/07/19 16:51:21 philogelos Exp $ */
#if !defined(_INLINE)
static char cvsid[] = "@(#)$Id: MinimalPlatform.cpp,v 1.1.1.1 2000/07/19 16:51:21 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif

#include <errno.h> /* ERANGE in strtol */
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <limits.h> /* LONG_MAX, LONG_MIN */

// extern int errno;

#include "platform/MinimalPlatform.hpp"
#include "platform/ANSICPlatform.hpp"
#include "String.hpp"
#include "Debug.hpp"

#include "exceptions/OutOfMemory.hpp"
#include "exceptions/InvalidArgument.hpp"

BEGIN_QR_NAMESPACE

MinimalPlatform::MinimalPlatform()
{}

MinimalPlatform::~MinimalPlatform()
{}

char *MinimalPlatform::getErrorDescription( int )
{
  return ( char * ) "Error";
}

void MinimalPlatform::sprintf( char *s, const char * format, /* args */ ...) 
{
  va_list args;

  va_start( args, format );
  this -> vsprintf( s, format, args );
  va_end(args);
}

void MinimalPlatform::vsprintf( char *s, const char *format, va_list raw )
{
  ::vsprintf( s, format, raw );
}

void MinimalPlatform::rawErrorPrintf( const char * format, /* args */ ... ) 
{
  va_list args;

  va_start( args, format );
  this -> rawErrorVPrintf( format, args );
  va_end(args);
}

void MinimalPlatform::rawErrorVPrintf( const char * format, va_list raw ) 
{
  vfprintf( stderr, format, raw );
}


void MinimalPlatform::exitImmediate( long status )
{
  this -> rawErrorPrintf
	( "Program exits with status %li. Terminate it by OS means.", status );
  while( true )
	{}
}
  
void MinimalPlatform::suicide()
{
  this -> rawErrorPrintf
	( "Program abnormally exits. Terminate it by OS means." );
  while( true )
	{}
}

void MinimalPlatform::attachDebugger()
{
  this -> rawErrorPrintf
	( "Please, attach debugger to this image." );
  while( true )
	{}
}

void MinimalPlatform::setImageName( const char *aName )
{
  imageName = aName;
  
}

const char *MinimalPlatform::getImageName() const
{
  return imageName;
}

char *MinimalPlatform::getTimeStampString()
{
  return ( char * ) "YYYY/MM/DD hh:mm:ss";
}

char  *MinimalPlatform::strcpy( char *dst, const char *src )
{
  char *point;

  point = dst;
  for( ; ( * ( point++ ) = * ( src++ ) ) ; )
	{}
  return dst;
}

int    MinimalPlatform::strcmp( const char *s1, const char *s2 )
{
  for( ; *s1 == *s2 ; ++s1, ++s2 )
	{
		if( *s1 == 0 )
		  {
			return 0;
		  }
	}
  return( ( * ( const unsigned char * ) s1 ) -
		   ( * ( const unsigned char * ) s2 ) );
}

Index MinimalPlatform::strlen( const char *s )
{
  char *point;

  for( point = ( char * ) s ; *point ; ++point )
	{}
  return( point - s );
}

char  *MinimalPlatform::strcat( char *dst, const char *src )
{
  return this -> strcpy( dst + this -> strlen( dst ), src );
}

char  *MinimalPlatform::strchr( const char *s, int c )
{
  for( ; *s ; ++s )
	{
	  if( *s == c )
		{
		  return ( char * ) s;
		}
	}
  return NIL;
}

/* adapted from from FreeBSD:/usr/src/lib/libc/stdlib/strtol.c */
long   MinimalPlatform::strtol( const char *nptr, char **endptr, int base )
{
  const char *s = nptr;
  unsigned long acc;
  unsigned char c;
  unsigned long cutoff;
  int neg = 0, any, cutlim;

  /*
   * Skip white space and pick up leading +/- sign if any.
   * If base is 0, allow 0x for hex and 0 for octal, else
   * assume decimal; if base is already 16, allow 0x.
   */
  do 
	{
	  c = *s++;
	} 
  while ( ( c == ' ' ) || ( c == '\t' ) || ( c == '\n' ) || ( c == '\r' ) );
  if (c == '-') 
	{
	  neg = 1;
	  c = *s++;
	} 
  else 
	{
	  if (c == '+')
		{
		  c = *s++;
		}
	}
  if ( ( base == 0 || base == 16) &&
	   c == '0' && (*s == 'x' || *s == 'X' ) ) 
	{
	  c = s[1];
	  s += 2;
	  base = 16;
	}
  if (base == 0)
	{
	  base = c == '0' ? 8 : 10;
	}

  /*
   * Compute the cutoff value between legal numbers and illegal
   * numbers.  That is the largest legal value, divided by the
   * base.  An input number that is greater than this value, if
   * followed by a legal input character, is too big.  One that
   * is equal to this value may be valid or not; the limit
   * between valid and invalid numbers is then based on the last
   * digit.  For instance, if the range for longs is
   * [-2147483648..2147483647] and the input base is 10,
   * cutoff will be set to 214748364 and cutlim to either
   * 7 (neg==0) or 8 (neg==1), meaning that if we have accumulated
   * a value > 214748364, or equal but the next digit is > 7 (or 8),
   * the number is too big, and we will return a range error.
   *
   * Set any if any `digits' consumed; make it negative to indicate
   * overflow.
   */
  cutoff = neg ? - ( unsigned long ) LONG_MIN : LONG_MAX;
  cutlim = cutoff % ( unsigned long ) base;
  cutoff /= ( unsigned long ) base;
  for( acc = 0, any = 0 ; ; c = *s++ ) 
	{
	  if( c > 0177 )
		{
		  break;
		}
	  if( ( c >= '0' ) && ( c <= '9' ) )
		{
		  c -= '0';
		}
	  else 
		{
		  if( ( ( c >= 'a' ) && ( c <= 'z' ) ) || 
			  ( ( c >= 'A' ) && ( c <= 'Z' ) ) )
			{
			  c -= ( ( c >= 'A' ) && ( c <= 'Z' ) ) ? 'A' - 10 : 'a' - 10;
			}
		  else
			{
			  break;
			}
		}
	  if(c >= base)
		{
		  break;
		}
	  if(any < 0 || acc > cutoff || ( acc == cutoff && c > cutlim ) )
		{
		  any = -1;
		}
	  else 
		{
		  any = 1;
		  acc *= base;
		  acc += c;
		}
	}
  if( any < 0 ) 
	{
	  acc = neg ? LONG_MIN : LONG_MAX;
	  errno = ERANGE;
	} 
  else 
	{
	  if( neg )
		{
		  acc = -acc;
		}
	}
  if( endptr != 0 )
	{
	  *endptr = ( char * )( any ? s - 1 : nptr );
	  if( **endptr != ( char ) 0 )
		{
		  throw new 
			InvalidArgument( "strtol: garbage detected", 
							 ( Top * ) nil );
		}
	}
  if( errno == ERANGE )
	{
	  throw new 
		InvalidArgument( "strtol: value is outside the range of representable values", 
						 ( Top * ) nil );
	}
  return acc;
}

int MinimalPlatform::memcmp( void *s1, const void *s2, Index n )
{
  char *c1 = ( char * ) s1;
  char *c2 = ( char * ) s2;
  
  for( Index scan = 0 ; 
	   ( scan < n ) && ( *c1 == *c2 ) ; 
	   ++c1, ++c2, ++scan )
	{}
  return( ( * ( const unsigned char * ) c1 ) -
		  ( * ( const unsigned char * ) c2 ) );
}

void *MinimalPlatform::memchr( const void *s, int c, Index n )
{
  char *cc = ( char * ) s;
  for( Index scan = 0 ; scan < n ; ++cc )
	{
	  if( *cc == c )
		{
		  return ( void * ) cc;
		}
	}
  return NIL;
}


void *MinimalPlatform::memcpy( void *s1, const void *s2, Index n )
{
  for( Index scan = 0 ; scan < n ; ++scan )
	{
	  ( ( unsigned char * ) s1 )[ scan ] = ( ( unsigned char * ) s2 )[ scan ];
	}
  return s1;
}

void *MinimalPlatform::memset( void *s, int c, Index n )
{
  for( Index scan = 0 ; scan < n ; ++scan )
	{
	  ( ( unsigned char * ) s )[ scan ] = ( unsigned char ) c;
	}
  return s;
}


void *MinimalPlatform::allocateMemory( Index aSize )
{
  char *arena;

  arena = ( char * ) malloc( aSize );
  if( arena == NULL )
	{
	  throw ANSICPlatform::getOutOfMemory();
	}
  this -> memset( arena, 0, aSize );
  return arena;
}

void  MinimalPlatform::deallocateMemory( void *aPointer )
{
  if( aPointer != NIL )
	{
	  free( aPointer );
	}
}

boolean MinimalPlatform::equals( const Top *anOther ) const
{
  return( DCAST( anOther, MinimalPlatform ) == this );
}

Top *MinimalPlatform::clone() const
{
  return ( Top * ) this;
}

String  MinimalPlatform::getClassName() const
{
  return "MinimalPlatform";
}

END_QR_NAMESPACE

#if defined(_INLINE)
#include "../src/Debug.ipp"
#endif


/*
 * $Log: MinimalPlatform.cpp,v $
 * Revision 1.1.1.1  2000/07/19 16:51:21  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.3  2000/04/09 12:00:49  god
 * CVS Log keyword correction finished
 *
 * Revision 1.2  2000/04/09 11:29:43  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:34  god
 * Imported sources
*/
