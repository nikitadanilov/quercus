// -*-C++-*- 

/*  src/StringBuffer.cpp  */

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



/* $Id: StringBuffer.cpp,v 1.1.1.1 2000/07/19 16:42:18 philogelos Exp $ */
#if !defined(_INLINE)
static char cvsid[] = "@(#)$Id: StringBuffer.cpp,v 1.1.1.1 2000/07/19 16:42:18 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif

#include "platform/Platform.hpp"
#include "StringBuffer.hpp"
#include "LinkManager.hpp"
#include "String.hpp"
#include "OGuard.hpp"
#include "Debug.hpp"
#include "Char.hpp"

BEGIN_QR_NAMESPACE

StringBuffer::StringBuffer( Index aLength, Index aDelta )
{
  preC_( aLength >= 0 );
  preC_( aDelta > 0 );
  
  init( aLength, aDelta );
}

StringBuffer::~StringBuffer()
{
  preC_( buffer != NULL );
  delete []buffer;
  buffer = NIL;
}

void StringBuffer::add( unichar aChar )
{
  preC_( aChar != ( unichar ) 0 );
  /* preC_( PLAF -> strlen( buffer ) == used ); XXX */
  preC_( used <= length );
  
  if( used == length )
	{
	  unichar *newBuffer;
	  
	  newBuffer = new unichar[ length + delta + 1 ];
	  PLAF -> memcpy( newBuffer, buffer, length * sizeof( unichar ) );
	  length += delta;
	  delete []buffer;
	  buffer = newBuffer;
	}
  test_( used < length );
  buffer[ used++ ] = aChar;
  buffer[ used ] = ( unichar ) 0;

  /* postC_( PLAF -> strlen( buffer ) == used ); */
  postC_( used <= length );
}

void StringBuffer::add( unichar *aChar )
{
  preC_( aChar != ( unichar * ) NULL );
  
  for( ; *aChar ; ++aChar )
	{
	  add( *aChar );
	}
}


void StringBuffer::add( Char *aChar )
{
  preC_( aChar != null );
  
  OGuard _char( aChar, this );
  
  add( aChar -> getUNICODE() );
}

void StringBuffer::add( String aString )
{
  add( aString.getUNIChars() );
}

String StringBuffer::asString() const
{
  return String( buffer, true, true );
}

Index StringBuffer::getLength() const
{
  return used;
}

unichar StringBuffer::getAt( Index anIndex ) const
{
  preC_( ( 0 <= anIndex ) && ( anIndex < getLength() ) );

  return buffer[ anIndex ];
}
  
boolean StringBuffer::equals( const Top *anOther ) const
{
  preC_( anOther != null );
  OGuard _other( anOther, this );
  if( DCAST( anOther, StringBuffer ) == null )
	{
	  return false;
	}
  else
	{
	  StringBuffer *other;
	  
	  other = DCAST( anOther, StringBuffer );
	  test_( other != null );
	  return ( length == other -> length ) &&
		( used == other -> used ) &&
		( delta == other -> delta ) &&
		!( PLAF -> memcmp
		   ( buffer, other -> buffer, used ) );
	}
}

Top *StringBuffer::clone() const
{
  StringBuffer *result;
  
  result = new StringBuffer( length, delta );
  for( Index i = 0 ; i < used ; ++i )
	{
	  result -> add( buffer[ i ] );
	}
  return result;
}

String  StringBuffer::toString() const
{
  return Object::toString() + " buffer: " + buffer;
}

String  StringBuffer::getClassName() const
{
  return "StringBuffer";
}

void StringBuffer::init( Index aLength, Index aDelta )
{
  /* preC_( aSource != ( unichar * ) NULL ); */
  /* preC_( aLength >= PLAF -> strlen( aSource ) ); */
  preC_( aDelta > 0 );
  
  buffer = new unichar[ aLength + 1 ];
  length = aLength;
  delta = aDelta;
  used = 0; /* PLAF -> strlen( aSource ); */
  postC_( used <= length );
}

Index StringBuffer::defaultLength = 10;
Index StringBuffer::defaultDelta = 10;

END_QR_NAMESPACE

#if defined(_INLINE)
#include "../src/Debug.ipp"
#endif


/*
 * $Log: StringBuffer.cpp,v $
 * Revision 1.1.1.1  2000/07/19 16:42:18  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.4  2000/04/30 00:46:22  god
 * getLength() returns ::used
 *
 * Revision 1.3  2000/04/29 23:48:43  god
 * getLength() and getAt() added
 *
 * Revision 1.2  2000/04/09 11:29:39  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:29  god
 * Imported sources
*/
