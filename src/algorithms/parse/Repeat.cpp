// -*-C++-*- 

/*  src/algorithms/parse/Repeat.cpp  */

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



/* $Id: Repeat.cpp,v 1.3 2001/06/09 15:02:18 philogelos Exp $ */
#if !defined( _INLINE )
static char cvsid[] = "@(#)$Id: Repeat.cpp,v 1.3 2001/06/09 15:02:18 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif

#include "algorithms/parse/Repeat.hpp"
#include "iter/enumerations/LookAheadEnumeration.hpp"
#include "algorithms/parse/ParseError.hpp"
#include "OGuard.hpp"
#include "Debug.hpp"

BEGIN_QR_NAMESPACE

Repeat::Repeat( String aName, 
				Index aMin, Index aMax, 
				GrammarNode *aBody ) :
  GrammarNode( aName )
{
  preC_( aMin >= 0 );
  preC_( ( aMax == infinity ) || ( aMax >= aMin ) );
  preC_( aBody != NULL );

  min = aMin;
  max = aMax;
  body = aBody;
}

Repeat::~Repeat()
{}

void Repeat::parse( LookAheadEnumeration *aStream ) 
  THROWS( ParseError * )
{
  preC_( aStream != NULL );

  Index i;
  CRef< List > results;

  // DLOG( "repeat: min: %li, max: %li", min, max );

  parseResult = NULL;
  results = new List();

  for( i = 0 ; i < min ; ++i )
	{
	  // DLOG( "repeat: %li", i );
	  try
		{
		  body -> parse( aStream );
		  results -> append( body -> getResult() );
		}
	  catch( ParseError *error )
		{
		  error -> addTraceBack( this, "too few" );
		  throw error;
		}
	}
  for( ; ( max == infinity ) || ( i < max ) ; ++i )
	{
	  CRef< LAAnchor > anchor;

	  anchor = aStream -> push();
	  // DLOG( "repeat: %li", i );
	  try
		{
		  body -> parse( aStream );
		  results -> append( body -> getResult() );
		}
	  catch( ParseError *noWay )
		{
		  OGuard _enough( noWay, this );
		  //		  DLOGOBJECT( "repeat: anchor: %s", *anchor );
		  aStream -> rollTo( *anchor );
		  aStream -> pop( *anchor );
		  break;
		}
	  aStream -> pop( *anchor );
	}
  parseResult = *results;
}

String  Repeat::getString() const
{
  return getName() + " -> " + body -> getName() + "*";
}

String  Repeat::getClassName() const
{
  return "Repeat";
}

const Index Repeat::infinity = -1;

END_QR_NAMESPACE

#if defined( _INLINE )
#include "../src/Debug.ipp"
#endif


/*
 * $Log: Repeat.cpp,v $
 * Revision 1.3  2001/06/09 15:02:18  philogelos
 * GrammarNode::getResult() and ::[gs]etTransformer() added to the
 * interface and implemented in all nodes.
 *
 * Revision 1.2  2000/10/12 21:33:28  philogelos
 * Excessive logging removed
 *
 * Revision 1.1  2000/09/19 18:20:08  philogelos
 * Lexer and parser redone.
 *
 */
