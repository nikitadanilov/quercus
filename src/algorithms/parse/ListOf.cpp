// -*-C++-*- 

/*  src/algorithms/parse/ListOf.cpp  */

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



/* $Id: ListOf.cpp,v 1.2 2001/06/09 14:50:28 philogelos Exp $ */
#if !defined( _INLINE )
static char cvsid[] = "@(#)$Id: ListOf.cpp,v 1.2 2001/06/09 14:50:28 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif

#include "algorithms/parse/ListOf.hpp"
#include "algorithms/parse/Repeat.hpp"
#include "algorithms/containers/ContainerAlgorithms.hpp"
#include "iter/enumerations/LookAheadEnumeration.hpp"
#include "iter/iterables/PrettyPrintIterable.hpp"
#include "algorithms/parse/Alternative.hpp"
#include "algorithms/parse/ParseError.hpp"
#include "containers/lists/List.hpp"
#include "ObjectWrapper.hpp"
#include "StringBuffer.hpp"
#include "PGuard.hpp"
#include "OGuard.hpp"
#include "Debug.hpp"
#include "MemoryMonitor.hpp"

BEGIN_QR_NAMESPACE

ListOf::ListOf( String aName, 
				boolean canBeEmpty,
				GrammarNode *aStart, 
				GrammarNode *aItem,
				GrammarNode *aDelimiter,
				GrammarNode *anEnd ) : GrammarNode( aName )
  /* 
	         ListOf( S, I, D, E ) :==
	    S [ I (D I)* ] E    e.g. '(' [ id (',' id)* ] ')'
	 NonEmptyListOf( S, I, D, E ) :==
	    S I (D I)* E        e.g. '(' id (',' id)* ')'
  */
  /*
	this was nice as fast implementation of list parsing,
	but getting parseResult out of there is too complex. 

  Concatenation( aName + "-repr", 
				 new List
				 ( 0,
				   OW( aStart ),
				   OW( new Repeat
					   ( aName + "-repr-out",
						 canBeEmpty ? 0 : 1,
						 1,
						 new Concatenation
						 ( aName + "-repr-out-in",
						   new List
						   ( 2,
							 OW( aItem ),
							 OW( new Repeat
								 ( aName + "-repr-cont",
								   0, Repeat::infinity,
								   new Concatenation
								   ( aName + "-repr-cont-core",
									 new List( 1,
											   OW( aDelimiter ),
											   OW( aItem ), NULL ) ) ) ),
							 NULL ) ) ) ),
				   OW( anEnd ), NULL ) )
  */
{
  preC_( aStart != NULL );
  preC_( aItem != NULL );
  preC_( aDelimiter != NULL );
  preC_( anEnd != NULL );

  start = aStart;
  item = aItem;
  delimiter = aDelimiter;
  end = anEnd;
  emptyable = canBeEmpty;
}

ListOf::~ListOf()
{}

void ListOf::parse( LookAheadEnumeration *aStream ) THROWS( ParseError * )
{
  preC_( aStream != NULL );

  OGuard _stream( aStream, this );

  CRef< List > results;

  parseResult = NULL;
  results = new List();

  isHere( aStream, *start, *results, true );
  for( boolean required = !emptyable ;
	   isHere( aStream, *item, *results, required ) &&
		 isHere( aStream, *delimiter, *results, false ) ; required = false )
	   
	{}
  isHere( aStream, *end, *results, true );
  parseResult = *results;
}

boolean ListOf::isHere( LookAheadEnumeration *aStream,
						GrammarNode *aNode, List *aResults, boolean aFatal )
{
  preC_( aStream != NULL );
  preC_( aNode != NULL );
  preC_( aResults != NULL );

  CRef< LAAnchor > anchor;

  anchor = aStream -> push();
  try
	{
	  aNode -> parse( aStream );
	  aResults -> append( aNode -> getResult() );
	}
  catch( UnableToParse *huh )
	{
	  aStream -> rollTo( *anchor );
	  if( aFatal )
		{
		  huh -> addTraceBack( this, 
							   String( "Expected " ) + aNode -> getName() );
		  throw huh;
		}
	  else
		{
		  OGuard _huh( huh, this );
		  return false;
		}
	}
  aStream -> pop( *anchor );
  return true;
}

String  ListOf::getClassName() const
{
  return "ListOf";
}

END_QR_NAMESPACE

#if defined( _INLINE )
#include "../src/Debug.ipp"
#endif


/*
 * $Log: ListOf.cpp,v $
 * Revision 1.2  2001/06/09 14:50:28  philogelos
 * ListOf made special GrammarNode like Alternative rather than
 * sub-class of Concatenation.
 *
 * Revision 1.1  2000/09/19 18:20:08  philogelos
 * Lexer and parser redone.
 *
 */
