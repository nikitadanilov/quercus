// -*-C++-*- 

/*  src/algorithms/parse/ParseStream.cpp  */

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



/* $Id: ParseStream.cpp,v 1.2 2000/09/19 18:20:08 philogelos Exp $ */
#if !defined( _INLINE )
static char cvsid[] = "@(#)$Id: ParseStream.cpp,v 1.2 2000/09/19 18:20:08 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif

#include "algorithms/parse/ParseStream.hpp"
#include "algorithms/parse/WordParser.hpp"
#include "containers/IndexPosition.hpp"
#include "containers/lists/List.hpp"
#include "containers/Stack.hpp"
#include "StringBuffer.hpp"
#include "UCSChar.hpp"
#include "OGuard.hpp"
#include "Debug.hpp"

BEGIN_QR_NAMESPACE

ParseStream::ParseStream( CharEnumeration *aChars )
{
  preC_( aChars != NULL );

  chars = aChars;
  pushBack = new Stack();
  mark = 0;
}

ParseStream::~ParseStream()
{}

Char *ParseStream::getCharFast()
{
  preC_( ! isEOF() );

  ++mark;
  if( pushBack -> isEmpty() )
	{
	  return getChars() -> getNextCharFast();
	}
  else
	{
	  return TCAST( pushBack -> pop(), Char );
	}
}

Char *ParseStream::getChar()
{
  preC_( ! isEOF() );

  ++mark;
  if( pushBack -> isEmpty() )
	{
	  return getChars() -> getNextTypedElement();
	}
  else
	{
	  return TCAST( pushBack -> pop(), Char );
	}
}

Char *ParseStream::getTop()
{
  Char *top;

  top = getCharFast();
  ungetChar( top );
  return top;
}

void  ParseStream::ungetChar( Char *aChar )
{
  preC_( aChar != NULL );

  pushBack -> push( aChar );
}

boolean ParseStream::startWithChar( Char *aChar )
{
  preC_( aChar != NULL );

  return( ( ! isEOF() ) && ( getTop() -> equals( aChar ) ) );
}

boolean ParseStream::startWithString( String aString )
{
  StringBuffer lookAhead( StringBuffer::defaultLength,
						  StringBuffer::defaultDelta );
  Index taken;
  boolean failure;
  
  failure = false;
  OGuard _chars( *chars, this, true );
  for( taken = 0 ; taken < aString.length() ; )
	{
	  Char *next;

	  if( isEOF() )
		{
		  break;
		}
	  next = getChar();
	  OGuard _next( next, this );
	  ++taken;

	  lookAhead.add( next );
	  if( next -> getUNICODE() != aString.getUNIChars()[ taken - 1 ] )
		{
		  failure = true;
		  break;
		}
	}
  for( Index i = taken - 1 ; i >= 0 ; --i )
	{
	  ungetChar( new UCSChar( lookAhead.getAt( i ) ) );
	}
  return !failure;
}

boolean ParseStream::isEOF() const
{
  return( ( pushBack -> isEmpty() ) && !( getChars() -> hasMoreElements() ) );
}

Position *ParseStream::getCurrentMark() const
{
  /* XXX oh, what a shame */
  return new IndexPosition( mark, new List() );
}

CharEnumeration *ParseStream::getChars() const
{
  return *chars;
}

Char *ParseStream::getNextCharFast()
{
  return getCharFast();
}

boolean ParseStream::hasMoreElements()
{
  return !isEOF();
}

String  ParseStream::getClassName() const
{
  return "ParseStream";
}

END_QR_NAMESPACE

#if defined( _INLINE )
#include "../src/Debug.ipp"
#endif


/*
 * $Log: ParseStream.cpp,v $
 * Revision 1.2  2000/09/19 18:20:08  philogelos
 * Lexer and parser redone.
 *
 * Revision 1.1.1.1  2000/07/19 16:44:14  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.1  2000/05/06 08:36:27  god
 * committed
 *
 */
