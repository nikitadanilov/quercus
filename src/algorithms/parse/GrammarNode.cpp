// -*-C++-*- 

/*  src/algorithms/parse/GrammarNode.cpp  */

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



/* $Id: GrammarNode.cpp,v 1.4 2001/06/23 12:30:21 philogelos Exp $ */
#if !defined( _INLINE )
static char cvsid[] = "@(#)$Id: GrammarNode.cpp,v 1.4 2001/06/23 12:30:21 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif

#include "iter/enumerations/LookAheadEnumeration.hpp"
#include "algorithms/parse/GrammarNode.hpp"
#include "algorithms/parse/ParseError.hpp"
#include "containers/lists/List.hpp"
#include "PGuard.hpp"
#include "OGuard.hpp"
#include "Debug.hpp"

BEGIN_QR_NAMESPACE

GrammarNode::GrammarNode( String aName, Map *aTransformer ) : name( aName )
{
  parseResult = NULL;
  transformer = aTransformer;
}

String GrammarNode::toString() const
{
  return Object::toString() + "name: " + getName();
}

String GrammarNode::getString() const
{
  return getName() + " -> ...";
}

String GrammarNode::getName() const
{
  return name;
}

Map *GrammarNode::getTransformer() const
{
  return *transformer;
}

void GrammarNode::setTransformer( Map *aMap )
{
  transformer = aMap;
  
}

Top *GrammarNode::getResult() const
{
  if( getTransformer() != NULL )
	{
	  return getTransformer() -> apply( *parseResult );
	}
  else
	{
	  return *parseResult;
	}
}

#if defined( TESTING )

END_QR_NAMESPACE
#include "containers/Singleton.hpp"
#include "containers/Pair.hpp"

#include "algorithms/parse/Concatenation.hpp"
#include "algorithms/parse/ParseStream.hpp"
#include "algorithms/parse/Alternative.hpp"
#include "algorithms/parse/Terminal.hpp"
#include "algorithms/parse/Lexer.hpp"
#include "algorithms/parse/StockLexer.hpp"

#include "algorithms/parse/ListOf.hpp"
#include "algorithms/parse/Repeat.hpp"
#include "algorithms/parse/Whitespace.hpp"
#include "algorithms/parse/Identifier.hpp"
#include "algorithms/parse/Constant.hpp"
#include "algorithms/parse/Comment.hpp"
#include "algorithms/parse/NumericLiteral.hpp"
#include "StringEnumeration.hpp"
#include "ObjectWrapper.hpp"
#include "KOI8RConverter.hpp"
BEGIN_QR_NAMESPACE

boolean GrammarNode::testerGrammarNode( int )
{
  {
	DLOG( "GrammarNode: creation" );

	CRef< Alternative > fooOrBar;
	CRef< StockLexer > lexer;
	CRef< ParseStream > stream;
	CRef< LookAheadEnumeration > lae;
	
	lexer = new StockLexer
	  ( new ParseStream( new StringEnumeration
						 ( "(i1,{(**)},i2,{(* *).(***)})" ) ) );
	
	lexer -> getCommentToken() -> setStart( "(*" );
	lexer -> getCommentToken() -> setEnd( "*)" );
	fooOrBar = new Alternative
	  ( "fooOrBar", new List
		( 1, 
		  OW( lexer -> addTerminal( "keyword_foo", "foo", StockLexer::head ) ),
		  OW( new Concatenation
			  ( "barNo",
				new List( 2,
						  OW( lexer -> addTerminal( "keyword_bar", "bar", 
													StockLexer::head ) ),
						  OW( new Terminal( "' '", new Whitespace() ) ),
						  OW( lexer -> getNumber() ), 
						  NULL ) ) ),
		  OW( new ListOf( String( "ИдентСписок", new KOI8RConverter() ),
						  true,
						  lexer -> getLParen(),
						  new Alternative
						  ( "id-or-braces",
							new Pair( lexer -> getId(),
						  new ListOf( "innerlist",
									  false,
									  lexer -> getLBrace(),
									  lexer -> getComment(),
									  lexer -> getDot(),
												  lexer -> getRBrace() ) ) ),
						  lexer -> getComma(),
						  lexer -> getRParen() ) ),
		  NULL ) );

	lae = new LookAheadEnumeration( *lexer );
	try
	  {
		CRef< Top > result;

		fooOrBar -> parse( *lae );
		result = fooOrBar -> getResult();
		DLOGOBJECT( "parsing result: %s", *result, &Top::getString );
	  }
	catch( ParseError *error )
	  {
		OGuard _error( error, error );

		throw new Exception( String( "parse error: " ) + error -> getMessage() +
							 "\n" + error -> getDescription(), null );
	  }
  }
  return true;
}

#endif

END_QR_NAMESPACE

#if defined( _INLINE )
#include "../src/Debug.ipp"
#endif


/*
 * $Log: GrammarNode.cpp,v $
 * Revision 1.4  2001/06/23 12:30:21  philogelos
 * duplicate declaration of ::toString() removed
 *
 * Revision 1.3  2001/06/09 15:02:18  philogelos
 * GrammarNode::getResult() and ::[gs]etTransformer() added to the
 * interface and implemented in all nodes.
 *
 * Revision 1.2  2000/10/12 21:33:07  philogelos
 * Tests updated
 *
 * Revision 1.1  2000/09/19 18:20:08  philogelos
 * Lexer and parser redone.
 *
 */
