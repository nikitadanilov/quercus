// -*-C++-*- 

/*  src/algorithms/parse/Concatenation.cpp  */

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



/* $Id: Concatenation.cpp,v 1.3 2001/06/09 15:02:18 philogelos Exp $ */
#if !defined( _INLINE )
static char cvsid[] = "@(#)$Id: Concatenation.cpp,v 1.3 2001/06/09 15:02:18 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif

#include "iter/enumerations/LookAheadEnumeration.hpp"
#include "iter/iterables/PrettyPrintIterable.hpp"
#include "algorithms/parse/Concatenation.hpp"
#include "algorithms/parse/UnableToParse.hpp"
#include "algorithms/parse/ParseError.hpp"
#include "StringBuffer.hpp"
#include "OGuard.hpp"
#include "Debug.hpp"

BEGIN_QR_NAMESPACE

Concatenation::Concatenation( String aName, Container *aTerms ) :
  GrammarNode( aName )
{
  preC_( aTerms != NULL );

  terms = aTerms;
}

Concatenation::~Concatenation()
{}

void Concatenation::parse( LookAheadEnumeration *aStream ) 
  THROWS( ParseError * )
{
  preC_( aStream != NULL );

  OGuard _stream( aStream, this );

  CRef< List > results;
  CRef< Enumeration > values;

  parseResult = NULL;
  results = new List();
  values = terms -> getValueEnumeration();
  for( ; values -> hasMoreElements() ; )
	{
	  CRef< GrammarNode > term;

	  term = TCAST( values -> getNextElement(), GrammarNode );
	  try
		{
		  //		  DLOGOBJECT( "term: %s", term );
		  term -> parse( aStream );
		  results -> append( term -> getResult() );
		}
	  catch( UnableToParse *error )
		{
		  error -> addTraceBack( this, "doesn't concatenate" );
		  throw error;
		}
	}
  parseResult = *results;
}

String  Concatenation::getString() const
{
  StringBuffer result;
  CRef< PrettyPrintIterable > formatted;

  result.add( getName() );
  result.add( " -> " );

  formatted = new PrettyPrintIterable
	( "", " ", "", "...", 1000, &Top::toString );

  CRef< Iterator >( terms -> getValueIterator() ) -> iterate( *formatted );
  result.add( formatted -> getStringResult() );
  return result.asString();
}

String  Concatenation::getClassName() const
{
  return "Concatenation";
}

END_QR_NAMESPACE

#if defined( _INLINE )
#include "../src/Debug.ipp"
#endif


/*
 * $Log: Concatenation.cpp,v $
 * Revision 1.3  2001/06/09 15:02:18  philogelos
 * GrammarNode::getResult() and ::[gs]etTransformer() added to the
 * interface and implemented in all nodes.
 *
 * Revision 1.2  2001/04/16 13:37:13  philogelos
 * Added ::getStringResult() to PrettyPrintIterable.
 * Clients updated to take advantage of this method.
 *
 * Revision 1.1  2000/09/19 18:20:08  philogelos
 * Lexer and parser redone.
 *
 */
