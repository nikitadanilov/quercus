//-*-C++-*-

/*  src/String.ipp  */


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



/* $Id: String.ipp,v 1.1.1.1 2000/07/19 16:42:17 philogelos Exp $ */

#if !defined(__STRING_IPP__)
#define __STRING_IPP__

#include "Char.hpp"
#include "String.hpp"
#include "StringImplementation.hpp"
#include "UTF8Converter.hpp"
#include "OGuard.hpp"
#include "Debug.hpp"
#include "platform/Platform.hpp"

BEGIN_QR_NAMESPACE

INLINE String::String()
{
  ( core = StringImplementation::getNil() ) -> addRef();
  postC_( core != null );
  postC_( length() == 0 );
}

INLINE String::String( const String &src ) : Object()
  /* Got strange gcc-2.95 warning here: base class `class Object' should be 
	 explicitly initialized in the copy constructor.
  */
{
  ( core = src.getCore() ) -> addRef();
  postC_( length() == src.length() );
}

INLINE String::String( const unichar *s, boolean shouldCopy, boolean shouldDelete )
{
  preC_( s != ( unichar * )NULL );
  init( s, shouldCopy, shouldDelete );
  /* postC_( length() == PLAF -> strlen( s ) ); */
}

INLINE String::String( const char *s, 
					   CodesetConverter *aConverter,
					   boolean shouldDelete )
{
  preC_( s != NULL );
  preC_( aConverter != ( CodesetConverter * ) NULL );
  init( codeToUCS( s, aConverter ), false, true );
  if( shouldDelete )
	{
	  delete [] ( char * ) s;
	}
  /* postC_( length() == PLAF -> strlen( s ) ); */
}


INLINE String::String( const char *s, boolean shouldDelete )
{
  preC_( s != NULL );
  init( utf8ToUCS( s ), false, true );
  if( shouldDelete )
	{
	  delete [] ( char * ) s;
	}
}

INLINE String::String( const char *s )
{
  preC_( s != NULL );
  init( utf8ToUCS( s ), false, true );
}

INLINE String::String( const Index i )
{
  char convBuffer[ 64 ];
  PLAF -> sprintf( convBuffer, "%li", i );
  init( utf8ToUCS( convBuffer ), false, true );
}

INLINE String::String( const Index i, const int base )
{
  char convBuffer[ 64 ];
  if( base == 10 )
	{
	  PLAF -> sprintf( convBuffer, "%li", i );
	}
  else
	{
	  if( base == 8 )
		{
		  PLAF -> sprintf( convBuffer, "%lo", i );
		}
	  else
		{
		  sure( base == 16, "unsupported radix" );
		  PLAF -> sprintf(convBuffer,"%lx",i);
		}
	}
  init( utf8ToUCS( convBuffer ), false, true );
  /*  postC_( toNum( base ) == i ); -- sign can be lost */
}

INLINE String::String( const Char *aChar )
{
  OGuard _src( aChar, this );

  unichar *characters;

  characters = new unichar[ 2 ];
  characters[ 0 ] = aChar -> getUNICODE();
  characters[ 1 ] = ( unichar ) 0;
  
  init( characters, false, true );
}

INLINE String String::operator =( String src )
{
  if( this != &src )
	{
	  sure_( core != null );
	  core -> delRef();
	  if( !core -> isRef() )
		{
		  delete core;
		}
	  ( core = src.getCore() ) -> addRef();
	}
  postC_( length() == src.length() );
  return *this;
}

INLINE String String::operator +( const String src ) const
{
  /*  String chunk( ( char * ) *this, true, true );

  chunk += src;
  return chunk; */

  
  unichar *place;

  place = new unichar[ length() + src.length() + 1 ];
  PLAF -> memcpy
	( place, getUNIChars(), length() * sizeof( unichar ) );
  PLAF -> memcpy
	( place + length(), src.getUNIChars(), src.length() * sizeof( unichar ) );
  return String( place, false, true );
}

INLINE String &String::operator +=( const String src )
{
  /* XXX this doesn't work */
  unichar *place;

  place = new unichar[ length() + src.length() + 1 ];

  PLAF -> memcpy
	( place, getUNIChars(), length() * sizeof( unichar ) );
  PLAF -> memcpy
	( place + length(), src.getUNIChars(), src.length() * sizeof( unichar ) );

  if( core -> haveToDelete )
	{
	  delete []getUNIChars();
	}
  core -> core = place;
  core -> haveToDelete = true;
  core -> len += src.length();
  return *this;
}

INLINE String &String::operator +=( const Char *src )
{
  OGuard _src( src, this );

  String term;

  term = src;
  ( * this ) += term;
  return *this;
}

INLINE boolean String::operator ==( const String &rside ) const
{
  return ( length() == rside.length() ) &&
	!PLAF -> 
	memcmp( getUNIChars(), rside.getUNIChars(), length() * sizeof( unichar ) );
}

INLINE unichar *String::getUNIChars() const
{
  return *core;
}

INLINE char *String::getChars() const
{
  return ucsToUTF8( getUNIChars() );
}

INLINE String::operator char *() const
{
  return getChars();
}

// INLINE String::operator StringImplementation *(void ) const
// {
//   return core;
// }

INLINE Index String::length() const
{
  return core -> length();
}

INLINE Index String::lindex( const unichar what ) const
{
  const unichar *chr = ( const unichar * ) getUNIChars();
  const unichar *pos = ( unichar * ) PLAF -> 
	memchr( chr, what, length() * sizeof( unichar ) );
  
  if( pos == ( unichar * ) NULL )
	{
	  return length();
	}
  else
	{
	  return pos - chr;
	}
}

INLINE Index String::lindex( const String what ) const
{
  int l = length();
  int k = what.length();
  unichar *me = getUNIChars();
  unichar *he = what.getUNIChars();
  for( int i = 0 ; i < l - k + 1 ; ++i )
	{
	  boolean done = true;
	  for( int j = 0 ; ( j < k ) && ( done ) ; ++j )
		{
		  if( me[ i + j ] != he[ j ] )
			{
			  j = k;
			  done = false;
			}
		}
	  if( done )
		{
		  return i;
		}
	}
  return l;
}

INLINE boolean String::contains( const unichar aChar ) const
{
  return ( lindex( aChar ) < length() );
}

INLINE Index String::toNum( int aRadix ) const
{
  Index result;
  char *utf8;
  
  utf8 = getChars();
  result = PLAF -> strtol( utf8, (char ** )0L, aRadix );
  delete []utf8;
  return result;
}

INLINE boolean String::consistsOf( const String aPattern ) const
{
  for( unichar *s = getUNIChars(); *s ; ++s )
	{
	  if( ! aPattern.contains( *s ) )
		{
		  return false;
		}
	}
  return true;
}

INLINE boolean String::isBlank() const
{
  return consistsOf( " " );
}

INLINE void String::init( const unichar *s, boolean shouldCopy, boolean shouldDelete )
{
  sure_( s != ( unichar * ) NULL );

  core = new StringImplementation( ( unichar * ) s, shouldCopy, shouldDelete );
  postC_( core != null );
}

INLINE StringImplementation *String::getCore() const
{
  return core;
}

INLINE unichar *String::codeToUCS( const char *aCodeChars, CodesetConverter *aConverter )
{
  preC_( aCodeChars != NULL );
  preC_( aConverter != ( CodesetConverter * ) NULL );

  OGuard _conv( aConverter, aConverter );
  
  unichar *result;
  const char *read;
  unichar *write;
  Index delta;
  Index len;
  
  result = new unichar[ ( len = getUCSLength( aCodeChars, aConverter ) ) + 1 ];
  read = aCodeChars;
  write = result;
  for( ; *read ; read += delta )
	{
	  test_( write < result + len );
	  *write = aConverter -> fromBits( read, &delta );
	  write++;
	}
  test_( write == result + len );
  result[ len ] = ( unichar ) 0;
  return result;
}

INLINE char *String::ucsToCode( const unichar *anUCSChars, 
								CodesetConverter *aConverter )
{
  preC_( anUCSChars != ( unichar * ) NULL );
  preC_( aConverter != ( CodesetConverter * ) NULL );

  OGuard _conv( aConverter, aConverter );

  char *result;
  const unichar *read;
  char *write;
  Index delta;
  Index len;
 
  result = new char[ ( len = getLength( anUCSChars, aConverter ) ) + 1 ];
  read = anUCSChars;
  write = result;
  for( ; *read ; ++read )
	{
	  test_( write < result + len );
	  aConverter -> toBits( *read, write, &delta );
	  write +=delta;
	}
  test_( write == result + len );
  result[ len ] = ( char ) 0;
  return result;
}

INLINE unichar *String::utf8ToUCS( const char *anUTF8Chars )
{
  preC_( anUTF8Chars != NULL );

  return codeToUCS
	( anUTF8Chars, 
	  UTF8Converter::getDefaultUTF8Converter() );
}

INLINE char *String::ucsToUTF8( const unichar *anUCSChars )
{
  preC_( anUCSChars != ( unichar * ) NULL );
  
  return ucsToCode
	( anUCSChars,
	  UTF8Converter::getDefaultUTF8Converter() );
}

 
INLINE Index String::getUCSLength( const char *anUTF8Chars, 
								   CodesetConverter *aConv )
{
  preC_( anUTF8Chars != NULL );
  preC_( aConv != ( CodesetConverter * ) NULL );

  OGuard _conv( aConv, aConv );
  
  Index result;
  Index delta;
  
  for( result = 0 ; *anUTF8Chars ; ++result )
	{
	  aConv -> fromBits( anUTF8Chars, &delta );
	  anUTF8Chars +=delta;
	}
  return result;
}
 
INLINE Index String::getLength( const unichar *anUCSChars, 
								CodesetConverter *aConv )
{
  preC_( anUCSChars != ( unichar * ) NULL );
  preC_( aConv != ( CodesetConverter * ) NULL );

  OGuard _conv( aConv, aConv );
  
  char buffer[ 30 ]; /* XXX */
  Index result;
  Index delta;
  
  for( result = 0 ; *anUCSChars ; result += delta )
	{
	  aConv -> toBits( *anUCSChars, buffer, &delta );
	  ++anUCSChars;
	}
  return result;
}

END_QR_NAMESPACE

#if defined(_INLINE)
#include "../src/StringImplementation.ipp"
#endif

/* __STRING_IPP__ */
#endif

/*
 * $Log: String.ipp,v $
 * Revision 1.1.1.1  2000/07/19 16:42:17  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:39  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:28  god
 * Imported sources
 *
 * Revision 1.4  1999/05/22 13:00:31  philogelos
 * Merging sources back from SPARC
 *
 * Revision 1.3  1999/03/03 19:09:30  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.2  1999/02/28 15:56:26  philogelos
 * Tuned for inlines. += operator added. Constructor from Char added.
 *
 * Revision 1.1.1.1  1998/11/25 20:11:01  philogelos
 * Quercus Robusta
 *
 * Revision 1.3  1998/07/09 09:04:45  philogelos
 * custom new/delete added
 *
 * Revision 1.2  1998/07/07 14:29:59  philogelos
 * Memory leak in SUNWspro dynamic_cast fixed.
 *
 * Revision 1.1.1.1  1998/06/22 08:47:12  philogelos
 * First version under CVS
 *
 * Revision 1.1.1.1  1998/04/01 17:15:29  philogelos
 * first version under CVS
 * */
