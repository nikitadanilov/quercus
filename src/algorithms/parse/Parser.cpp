// -*-C++-*- 

/*  src/algorithms/parse/Parser.cpp  */

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



/* $Id: Parser.cpp,v 1.3 2000/08/30 12:20:36 philogelos Exp $ */
#if !defined( _INLINE )
static char cvsid[] = "@(#)$Id: Parser.cpp,v 1.3 2000/08/30 12:20:36 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif

#include "Debug.hpp"
#include "containers/lists/List.hpp"
#include "algorithms/parse/Parser.hpp"
#include "algorithms/parse/ParseError.hpp"
#include "algorithms/parse/ParseStream.hpp"
#include "algorithms/parse/TokenCradle.hpp"
#include "algorithms/parse/TokenFactory.hpp"
#include "StringBuffer.hpp"

BEGIN_QR_NAMESPACE

Parser::Parser( ParseStream *aStream )
{
  preC_( aStream != NULL );

  cradle = new TokenCradle( aStream );
  factory = new List();
}

Parser::~Parser()
{}

void Parser::add( TokenFactory *aFactory )
{
  preC_( aFactory != NULL );

  factory -> append( aFactory );
}

Token *Parser::getNextToken() THROWS( ParseError * )
{
  CRef< TokenFactory > school;
  Index acceptedLength;
  Position *startPosition;

  school = NULL;
  acceptedLength = 0;
  startPosition = cradle -> getStream() -> getCurrentMark();
  /* maximum-munch parse */
  for( factory -> toFirst() ; ! factory -> atEnd() ; factory -> next() )
	{
	  Index acceptedByFactory;
	  TokenFactory *item;

	  item = TCAST( factory -> getCurrentValue(), TokenFactory );
	  acceptedByFactory = item -> accept( *cradle );
	  if( acceptedByFactory > acceptedLength )
		{
		  acceptedLength = acceptedByFactory;
		  if( *school == NULL )
			{
			  cradle -> markStart();
			}
		  school = item;
		}
	}
  if( ( *school != NULL ) && ( acceptedLength > 0 ) )
	{
	  cradle -> markEnd();
	  return school -> graduate( *cradle, acceptedLength );
	}
  else
	{
	  throw new ParseError( String( "unable to parse at " ) + 
							startPosition -> getString(), null );
	}
}

Token *Parser::getNextTypedElement()
{
  return getNextToken();
}

boolean Parser::hasMoreElements()
{
  return( cradle -> hasAt( 0 ) );
}

String  Parser::getClassName() const
{
  return "Parser";
}

#if defined( TESTING )

END_QR_NAMESPACE
#include "algorithms/parse/Whitespace.hpp"
#include "algorithms/parse/Identifier.hpp"
#include "algorithms/parse/Constant.hpp"
#include "algorithms/parse/NumericLiteral.hpp"
#include "StringEnumeration.hpp"

#include "iter/iterables/PrettyPrintIterable.hpp"
#include "iter/iterables/EchoIterable.hpp"
#include "iter/iterables/NOPIterable.hpp"
BEGIN_QR_NAMESPACE

boolean Parser::tester( int ) const
{
  CRef< Parser > parser;

  Iterator *it;
  PrettyPrintIterable *runner;
  String result;

  parser = new Parser
	( new ParseStream( new StringEnumeration
					   ( "s1 keyword (.,) 0 10 20 0xa 0o7" ) ) );

  parser -> add( new Constant( "keyword", new String( "keyword_KEYWORD" ) ) );
  parser -> add( new Whitespace() );
  parser -> add( new Identifier() );
  parser -> add( new Constant( "(", new String( "LEFT_PAREN" ) ) );
  parser -> add( new Constant( ")", new String( "RIGHT_PAREN" ) ) );
  parser -> add( new Constant( ",", new String( "COMMA" ) ) );
  parser -> add( new Constant( ".", new String( "DOT" ) ) );
  parser -> add( new NumericLiteral() );

  it = parser -> getIterator();
  runner = new PrettyPrintIterable( "(", ", ", ")", " ... ", 1000, &Top::getString );

  OGuard _runner( runner, this );
  OGuard _it( it, this );
  
  it -> iterate( runner );
  /* it -> iterate( new EchoIterable() ); */
  result = String( *( String * )( runner -> getResult() ) );
  
  DLOGSTRING( "Parsed: %s", result );

//   try
// 	{
// 	  while( true )
// 		{
// 		  DLOGOBJECT( "Token: %s", parser -> getNextToken() );
// 		}
// 	}
//   catch( ParseError *aChoke )
// 	{
// 	  OGuard _choke( aChoke, this );
// 	  Debug::getLogger() -> exception( aChoke );
// 	}
  return true;
}

#endif

END_QR_NAMESPACE

#if defined( _INLINE )
#include "../src/Debug.ipp"
#endif


/*
 * $Log: Parser.cpp,v $
 * Revision 1.3  2000/08/30 12:20:36  philogelos
 * THROWS clauses updates to correspond to the real throws.
 *
 * Revision 1.2  2000/08/26 13:26:55  philogelos
 * New simple parser framework done. Compiles and passes Parser::tester()
 *
 * Revision 1.1.1.1  2000/07/19 16:44:18  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.1  2000/07/19 08:48:13  god
 * new parse method: ask all factories and accept one with longest match
 *
 */
