// -*-C++-*- 

/*  src/algorithms/parse/TokenCradle.cpp  */

/*
 * Author: Philogelos A. <Philogelos@yahoo.com>
 * Maintainer: Philogelos A.
 * Keywords: C++, library, containers
 *
 * Copyright (C) 1999, 2000 Philogelos A.
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



/* $Id: TokenCradle.cpp,v 1.2 2000/08/26 13:26:55 philogelos Exp $ */
#if !defined( _INLINE )
static char cvsid[] = "@(#)$Id: TokenCradle.cpp,v 1.2 2000/08/26 13:26:55 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif

#include "containers/dicts/DumbDictionary.hpp"
#include "algorithms/parse/TokenCradle.hpp"
#include "algorithms/parse/ParseStream.hpp"
#include "containers/Position.hpp"
#include "StringBuffer.hpp"
#include "String.hpp"
#include "OGuard.hpp"
#include "Debug.hpp"
#include "Char.hpp"

BEGIN_QR_NAMESPACE

TokenCradle::TokenCradle( ParseStream *aStream )
{
  preC_( aStream != NULL );

  stream = aStream;
  buffer = new StringBuffer( StringBuffer::defaultLength,
							 StringBuffer::defaultDelta );
  attributes = new DumbDictionary();
}

TokenCradle::~TokenCradle()
{}

unichar TokenCradle::getAt( Index anIndex )
{
  preC_( anIndex >= 0 );
  
  if( hasAt( anIndex ) )
	{
	  return getBuffer() -> getAt( anIndex );
	}
  else
	{
	  throw new InternalError( "getAt() beyond the end of the stream", null );
	}
}

boolean TokenCradle::hasAt( Index anIndex )
{
  preC_( anIndex >= 0 );
  
  while( getBuffer() -> getLength() < anIndex + 1 )
	{
	  if( getStream() -> isEOF() )
		{
		  return false;
		}
	  else
		{
		  Char *ch;

		  ch = getStream() -> getChar();
		  OGuard _ch( ch, this );
		  getBuffer() -> add( ch );
		}
	}
  return true;
}

void TokenCradle::markStart()
{
  start = stream -> getCurrentMark();
}

void TokenCradle::markEnd()
{
  end = stream -> getCurrentMark();
}

Dictionary *TokenCradle::getAttributes() const
{
  return *attributes;
}

ParseStream *TokenCradle::getStream() const
{
  return *stream;
}

StringBuffer *TokenCradle::getBuffer() const
{
  return *buffer;
}

String TokenCradle::pop( Index aLength )
{
  preC_( aLength >= 0 );

  if( aLength > 0 )
	{
	  String content;

	  if( !hasAt( aLength - 1 ) )
		{
		  throw new InternalError
			( String( "pop( " ) +String( aLength ) + 
			  " ) beyond the end of the stream", null );
		}
	  content = getBuffer() -> asString();
	  buffer = new StringBuffer( content.length() - aLength,
								 StringBuffer::defaultDelta );
	  buffer -> add( content.clip( aLength, content.length() ) );
	  return content.clip( 0, aLength );
	}
  else
	{
	  return "";
	}
}

Top *TokenCradle::clone() const
{
  TokenCradle *result;

  result = new TokenCradle( getStream() );
  result -> getBuffer() -> add( getBuffer() -> asString() );
  return result;
}

String  TokenCradle::toString() const
{
  return Object::toString() +
	" buffer: " + getBuffer() -> asString() +
	( getStream() -> isEOF() ? String( " <empty>" ) : 
	  ( String( " top: '" ) + getStream() -> getTop() -> toUTF8() + "'") );
}

String  TokenCradle::getClassName() const
{
  return "TokenCradle";
}

END_QR_NAMESPACE

#if defined( _INLINE )
#include "../src/Debug.ipp"
#endif


/*
 * $Log: TokenCradle.cpp,v $
 * Revision 1.2  2000/08/26 13:26:55  philogelos
 * New simple parser framework done. Compiles and passes Parser::tester()
 *
 * Revision 1.1.1.1  2000/07/19 16:44:14  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.1  2000/05/06 08:36:28  god
 * committed
 *
 */
