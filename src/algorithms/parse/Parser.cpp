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



/* $Id: Parser.cpp,v 1.5 2000/09/21 18:21:59 philogelos Exp $ */
#if !defined( _INLINE )
static char cvsid[] = "@(#)$Id: Parser.cpp,v 1.5 2000/09/21 18:21:59 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif

#include "iter/enumerations/LookAheadEnumeration.hpp"
#include "algorithms/parse/GrammarNode.hpp"
#include "algorithms/parse/ParseError.hpp"
#include "algorithms/parse/Lexer.hpp"
#include "algorithms/parse/Parser.hpp"
#include "Debug.hpp"

BEGIN_QR_NAMESPACE

Parser::Parser( GrammarNode *aRoot, Lexer *aLexer )
{
  setRoot( aRoot );
  setLexer( aLexer );
}

Parser::~Parser()
{}

void Parser::parse()
{
  preC_( getRoot() != NULL );
  preC_( getLexer() != NULL );

  try
	{
	  getRoot() -> parse( new LookAheadEnumeration( getLexer() ) );
	}
  catch( ParseError *error )
	{
	  OGuard _error( error, this );
	  
	  throw new Exception( String( "unable to parse: " ) + 
						   error -> getMessage() +
						   "\nat: " + error -> getDescription(), null );
	}
}

void Parser::setRoot( GrammarNode *aRoot )
{
  root = aRoot;
}

GrammarNode *Parser::getRoot() const
{
  return *root;
}

void Parser::setLexer( Lexer *aLexer )
{
  lexer = aLexer;
}

Lexer *Parser::getLexer() const
{
  return *lexer;
}

Top *Parser::clone() const
{
  return new Parser( getRoot(), getLexer() );
}

String  Parser::toString() const
{
  return "";
}

String  Parser::getString() const
{
  return "";
}

String  Parser::getClassName() const
{
  return "Parser";
}

END_QR_NAMESPACE

#if defined( _INLINE )
#include "../src/Debug.ipp"
#endif


/*
 * $Log: Parser.cpp,v $
 * Revision 1.5  2000/09/21 18:21:59  philogelos
 * wrapper around parsing classes
 *
 */
