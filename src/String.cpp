//-*-C++-*-

/*  src/String.cpp  */


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



/* $Id: String.cpp,v 1.1.1.1 2000/07/19 16:42:12 philogelos Exp $ */
#if !defined(_INLINE)
static char cvsid[] = "@(#)$Id: String.cpp,v 1.1.1.1 2000/07/19 16:42:12 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif


#include "defines.h"
#include "StringBuffer.hpp"
#include "ObjectWrapper.hpp"
#include "String.hpp"
#include "StringImplementation.hpp"
#include "Debug.hpp"
#include "OGuard.hpp"
#include "platform/Platform.hpp"

#include "exceptions/NotImplemented.hpp"

BEGIN_QR_NAMESPACE

//char   String::numBuffer[256];

////////////////////////////////////////////////////////////////////////////////

String::~String()
{
  sure_( core != nil );
  core -> delRef();
  if( !core -> isRef() )
	{
	  delete core;
	}
}

////////////////////////////////////////////////////////////////////////////////

boolean String::equals( const Top *rside ) const
{
  preC_( rside != null );
  OGuard _rside( rside, this );
  if( DCAST( rside, String ) == null )
	{
	  return false;
	}

  return ( ( *this ) == *( DCAST( rside, String ) ) );
}

////////////////////////////////////////////////////////////////////////////////

String String::getString() const
{
  return *this;
}

////////////////////////////////////////////////////////////////////////////////

String String::getClassName() const
{
  return "String";
}

////////////////////////////////////////////////////////////////////////////////

Top *String::clone() const
{
  return new String( ( const String & )*this );
}

String String::clip( const Index from, const Index to ) const
{
  unichar *place;
  int l;

  l = length();
  if( ( from >= 0 ) && ( from < l ) &&
	  ( to >= 0 ) && ( to <= l ) &&
	  ( to > from ) )
	{
	  place = new unichar[ to - from + 1 ];
	  PLAF -> memcpy
		( place, getUNIChars() + from, ( to - from ) * sizeof( unichar ) );
	  place[ to - from ] = ( unichar )0;
	  return String( place, false, true );
	}
  else
	{
	  return String();
	}
}

String String::format( int aDummy, ... )
{
  va_list args;
  
  String result;
  
  va_start( args, aDummy );

  result = vformat( args );

  va_end( args );
  return result;
}

String String::vformat( va_list args )
{
  StringBuffer result( length(), StringBuffer::defaultDelta );

  for( int i = 0 ; i < length() ; ++i )
	{
	  unichar widechar;
	  boolean flagsDone;

	  Format spec;

	  int base;
	  boolean isLong;

	  widechar = getUNIChars()[ i ];
	  if( widechar != ( unichar ) '%' )
		{
		  result.add( widechar );
		  continue;
		}
	  
	  isLong = false;
	  spec = IntFormat;
	  base = 10;
	  do
		{
		  flagsDone = true;
		  ++i;
		  test_( i < length() );
		  switch( ( char ) getUNIChars()[ i ] )
			{
			case 'l':
			  isLong = true;
			  flagsDone = false;
			  break;
			case 's':
			  spec = CStringFormat;
			  break;
			case 'c':
			  spec = CharFormat;
			  break;
			case 'i':
			case 'd':
			  base = 10;
			  break;
			case 'o':
			  base = 8;
			  break;
			case 'x':
			  base = 16;
			  break;
			case 'O':
			  spec = ObjFormat;
			  break;
			case 'S':
			  spec = StringFormat;
			  break;
			case 'B':
			  spec = BooleanFormat;
			  break;
			case '%':
			default:
			  result.add( widechar );
			  spec = OtherFormat;
			  break;
			}
		}
	  while( !flagsDone );

	  switch( spec )
		{
		case IntFormat:
		  test_( base > 0 );

		  if( isLong )
			{
			  result.add( String( va_arg( args, long int ), base ) );
			}
		  else
			{
			  result.add( String( va_arg( args, int ), base ) );
			}
		  break;
		case CharFormat:
		  if( isLong )
			{
			  result.add( va_arg( args, unichar ) );
			}
		  else
			{
			  result.add( ( unichar ) va_arg( args, int ) );
			}
		  break;
		case CStringFormat:
		  {
			char *arg;
			String formatted;

			arg = va_arg( args, char * );
			formatted = ( arg == NULL ) ? nullLiteral : String( arg );
			result.add( formatted );
		  }
		  break;
		case ObjFormat:
		  {
			ObjectWrapper *shrinkWrap;
			
			shrinkWrap = TCAST( va_arg( args, Top * ), ObjectWrapper );
			OGuard _wrap( shrinkWrap, this );
			
			if( shrinkWrap -> getValue() == null )
			  {
				result.add( nullLiteral );
			  }
			else if( isLong )
			  {
				result.add( shrinkWrap -> getValue() -> toString() );
			  }
			else
			  {
				result.add( shrinkWrap -> getValue() -> getString() );
			  }
		  }
		  break;
		case StringFormat:
		  result.add( va_arg( args, String * ) -> getUNIChars() );
		  break;
		case BooleanFormat:
		  {
			String literal;

			literal = ( va_arg( args, int ) != 0 ) ? 
			  String( "true" ) : String( "false" );
			if( isLong )
			  {
				result.add( literal );
			  }
			else
			  {
				result.add( literal.getUNIChars()[ 0 ] );
			  }
		  }
		  break;
		default:
		  break;
		}
	}
  return result.asString();
}


String String::sprintf( int aDummy, ... )
{
  va_list args;
  String result;
  
  va_start( args, aDummy );

  result = vsprintf( args );

  va_end( args );
  return result;
}

String String::vsprintf( va_list args )
{
  char *formatted;
  char *characters;
    
  characters = getChars();
  formatted = new char
	[ PLAF -> vprintfLength( characters, args ) + 1 ];
  PLAF -> vsprintf( formatted, characters, args );
  delete []characters;
  
  return String( formatted, true );
}

String String::strip( String aSpaces )
{
  Index lower;
  Index high;
  
  for( lower = 0 ; aSpaces.contains( getUNIChars()[ lower ] ) ; ++lower )
	{}
  for( high = length() - 1 ; aSpaces.contains( getUNIChars()[ high ] ) ; --high )
	{}
  return clip( lower, high + 1 );
}


////////////////////////////////////////////////////////////////////////////////


#if defined( TESTING )

END_QR_NAMESPACE
#include "containers/lists/List.hpp"
BEGIN_QR_NAMESPACE

boolean String::tester( int aParam ) const
{
  String pad;
  pad.dontManage();
  for( int j = 0 ; j < aParam ; ++j )
	{
	  String add;
	  
	  add = String( j, 0x10 );
	  pad = pad + add;
	  DLOGSTRING( "%s", pad );
	}
  DLOG( "***" );

  if( pad == *( ( String * )( pad + "." ).dontManage() ) )
	{
	  DLOG( "Puff!" );
	}
  else
	{
	  DLOG( "OK!" );
	}
	  
  DLOGSTRING
	( "sprintf: \"%s\"", 
	  String( "test: %x..%i..%o..%c%c%%" ).sprintf
	  ( 1, 100, 100, 100, 'a', 'b' ) );

  String foobar;

  foobar = "foorbar";

  DLOGSTRING
	( "format: \"%s\"", 
	  String( "test: %x..%i..%o..%c%c%%..%lx..%O++%lO**%S##%S!!..%B..%lB..%O..%s..%s" ).
	  format
	  ( 0, 100, 100, 100, 'a', 'b', 0xf0f0f0f0, 
		OW( new List() ), OW( new Object() ), 
		this, &foobar, 1 == 0, 2 + 2 == 4, OW( null ), "blablabla", NULL ) );
  return pad.invariant();
}
#endif

String String::nullLiteral( "(null)" );

END_QR_NAMESPACE

#include "../src/String.ipp"

#if defined(_INLINE)
#include "../src/Debug.ipp"
#endif


#if defined(_INLINE)
#include "../src/StringImplementation.ipp"
#endif

/*
 * $Log: String.cpp,v $
 * Revision 1.1.1.1  2000/07/19 16:42:12  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:39  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:28  god
 * Imported sources
 *
 * Revision 1.5  1999/05/22 13:00:31  philogelos
 * Merging sources back from SPARC
 *
 * Revision 1.4  1999/03/03 19:09:29  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.3  1999/02/28 15:54:47  philogelos
 * Tuned for inlines. ::nullLiteral added. Some arguments guarded.
 *
 * Revision 1.2  1998/12/01 16:18:52  philogelos
 * conditionally compile ::tester()
 *
 * Revision 1.1.1.1  1998/11/25 20:11:01  philogelos
 * Quercus Robusta
 *
 * Revision 1.4  1998/07/09 09:04:45  philogelos
 * custom new/delete added
 *
 * Revision 1.3  1998/07/07 14:29:59  philogelos
 * Memory leak in SUNWspro dynamic_cast fixed.
 *
 * Revision 1.2  1998/06/22 18:13:00  philogelos
 * Enumerations and containers added
 * */
