// -*-C++-*- 

/*  src/algorithms/parse/Alternative.cpp  */

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



/* $Id: Alternative.cpp,v 1.3 2001/04/16 13:37:13 philogelos Exp $ */
#if !defined( _INLINE )
static char cvsid[] = "@(#)$Id: Alternative.cpp,v 1.3 2001/04/16 13:37:13 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif

#include "iter/enumerations/LookAheadEnumeration.hpp"
#include "iter/iterables/PrettyPrintIterable.hpp"
#include "algorithms/parse/Alternative.hpp"
#include "algorithms/parse/ParseError.hpp"
#include "StringBuffer.hpp"
#include "OGuard.hpp"
#include "Debug.hpp"

BEGIN_QR_NAMESPACE

Alternative::Alternative( String aName, Container *aBranch ) :
  GrammarNode( aName )
{
  preC_( aBranch != NULL );

  branches = aBranch;
}

Alternative::~Alternative()
{}

void Alternative::parse( LookAheadEnumeration *aStream ) 
  THROWS( ParseError * )
{
  preC_( aStream != NULL );

  OGuard _stream( aStream, this );

  CRef< LAAnchor > anchor;
  
  anchor = aStream -> push();

  for( CRef< Enumeration > values = branches -> getValueEnumeration() ;
	   values -> hasMoreElements() ; )
	{
	  try
		{
		  // DLOGOBJECT( "parse-1: %s", aStream );
		  TCAST( values -> getNextElement(), GrammarNode ) -> parse( aStream );
		  aStream -> pop( *anchor );
		  // DLOGOBJECT( "parse-2: %s", aStream );
		  return;
		}
	  catch( UnableToParse *oops )
		{
		  OGuard _error( oops, this );

		  // DLOGOBJECT( "parse-3: %s", aStream );
		  // DLOGOBJECT( "anchor: %s", *anchor );
		  aStream -> rollTo( *anchor );
		  // DLOGOBJECT( "parse-4: %s", aStream );
		  continue;
		}
	  /* LexError etc. */
	  catch( ParseError *whatTheHell )
		{
		  // DLOGOBJECT( "parse-5: %s", aStream );
		  // DLOGOBJECT( "anchor: %s", *anchor );
		  whatTheHell -> addTraceBack( this, "" );
		  throw whatTheHell;
		}
	}
  
  /* XXX I don't know why, but this throw cannot be catched by 
	 catch( Exception * ). Moreover, direct dynamic_cast< Exception * > 
	 fails. Have to surround outermost parse() method with catch(). */
  aStream -> pop( *anchor );
  throw new AlternativesExhausted( "", this );
}

String  Alternative::getString() const
{
  StringBuffer result;
  CRef< PrettyPrintIterable > formatted;

  result.add( getName() );
  result.add( " -> " );

  formatted = new PrettyPrintIterable
	( "", " | ", "", "...", 1000, 
	  /* Who is afraid of C++? */
	  &Top::toString );

  CRef< Iterator >( branches -> getValueIterator() ) -> iterate( *formatted );
  result.add( formatted -> getStringResult() );
  return result.asString();
}

String  Alternative::getClassName() const
{
  return "Alternative";
}

AlternativesExhausted::AlternativesExhausted( String aMessage, 
											  const Top *const aSource ) :
  UnableToParse( aMessage, aSource ),
  ParseError( aMessage, aSource ),
  ExternalError( aMessage, aSource ),
  Exception( aMessage, aSource )
{}

String AlternativesExhausted::getClassName() const
{
  return "AlternativesExhausted";
}

String AlternativesExhausted::getDescription() const
{
  return UnableToParse::getDescription() +
	": all alternatives in production are exhausted";
}

END_QR_NAMESPACE

#if defined( _INLINE )
#include "../src/Debug.ipp"
#endif


/*
 * $Log: Alternative.cpp,v $
 * Revision 1.3  2001/04/16 13:37:13  philogelos
 * Added ::getStringResult() to PrettyPrintIterable.
 * Clients updated to take advantage of this method.
 *
 * Revision 1.2  2000/10/12 21:32:32  philogelos
 * Excessive logging removed
 *
 * Revision 1.1  2000/09/19 18:20:08  philogelos
 * Lexer and parser redone.
 *
 */
