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



/* $Id: ListOf.cpp,v 1.1 2000/09/19 18:20:08 philogelos Exp $ */
#if !defined( _INLINE )
static char cvsid[] = "@(#)$Id: ListOf.cpp,v 1.1 2000/09/19 18:20:08 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif

#include "algorithms/parse/ListOf.hpp"
#include "algorithms/parse/Repeat.hpp"
#include "iter/enumerations/LookAheadEnumeration.hpp"
#include "iter/iterables/PrettyPrintIterable.hpp"
#include "algorithms/parse/Alternative.hpp"
#include "algorithms/parse/ParseError.hpp"
#include "containers/lists/List.hpp"
#include "ObjectWrapper.hpp"
#include "StringBuffer.hpp"
#include "OGuard.hpp"
#include "Debug.hpp"

BEGIN_QR_NAMESPACE

ListOf::ListOf( String aName, 
				boolean canBeEmpty,
				GrammarNode *aStart, 
				GrammarNode *aItem,
				GrammarNode *aDelimiter,
				GrammarNode *anEnd ) :


  /* 
	         ListOf( S, I, D, E ) :==
	    S [ I (D I)* ] E    e.g. '(' [ id (',' id)* ] ')'
	 NonEmptyListOf( S, I, D, E ) :==
	    S I (D I)* E        e.g. '(' id (',' id)* ')'
  */
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
{
  preC_( aStart != NULL );
  preC_( aItem != NULL );
  preC_( aDelimiter != NULL );
  preC_( anEnd != NULL );
}

ListOf::~ListOf()
{}

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
 * Revision 1.1  2000/09/19 18:20:08  philogelos
 * Lexer and parser redone.
 *
 */
