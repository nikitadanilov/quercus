// -*-C++-*- 

/*  src/algorithms/parse/ParseError.cpp  */

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



/* $Id: ParseError.cpp,v 1.2 2000/09/19 18:20:08 philogelos Exp $ */
#if !defined( _INLINE )
static char cvsid[] = "@(#)$Id: ParseError.cpp,v 1.2 2000/09/19 18:20:08 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif

#include "algorithms/parse/GrammarNode.hpp"
#include "algorithms/parse/ParseError.hpp"
#include "StringBuffer.hpp"
#include "Debug.hpp"

BEGIN_QR_NAMESPACE

ParseError::ParseError( String aMessage, const Top *const aSource ) :
  ExternalError( aMessage, aSource ),
  Exception( aMessage, aSource )
{
  traceback = new List();
  notes = new List();
  addTraceBack( const_cast< Top * >( aSource ), "source of error" );
}

String ParseError::getDescription() const
{
  StringBuffer result;

  result.add( ExternalError::getDescription() );
  result.add( ": \nparse error at: \n" );

  for( getTraceBack() -> toFirst() ; ! getTraceBack() -> atEnd() ;
	   getTraceBack() -> next(), notes -> next() )
	{
	  CRef< Top > frame;

	  frame = getTraceBack() -> getCurrentValue();
	  if( *frame == NULL )
		{
		  result.add( String::nullLiteral );
		}
	  else
		{
		  result.add( frame -> getString() );
		}
	  result.add( ": " );
	  result.add( notes -> getCurrentValue() -> getString() );
	  result.add( "\n" );
	}
  return result.asString();
}

String  ParseError::getClassName() const
{
  return "ParseError";
}

void ParseError::addTraceBack( Top *aNode, String aNote )
{
  traceback -> append( aNode );
  notes -> append( aNote.clone() );
}

List *ParseError::getTraceBack() const
{
  return *traceback;
}

END_QR_NAMESPACE

#if defined( _INLINE )
#include "../src/Debug.ipp"
#endif


/*
 * $Log: ParseError.cpp,v $
 * Revision 1.2  2000/09/19 18:20:08  philogelos
 * Lexer and parser redone.
 *
 * Revision 1.1.1.1  2000/07/19 16:44:18  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.1  2000/07/19 08:48:13  god
 * new parse method: ask all factories and accept one with longest match
 *
 */
