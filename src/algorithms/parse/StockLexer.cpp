// -*-C++-*- 

/*  src/algorithms/parse/StockLexer.cpp  */

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



/* $Id: StockLexer.cpp,v 1.1 2000/09/19 18:20:08 philogelos Exp $ */
#if !defined( _INLINE )
static char cvsid[] = "@(#)$Id: StockLexer.cpp,v 1.1 2000/09/19 18:20:08 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif

#include "algorithms/parse/Constant.hpp"
#include "algorithms/parse/NumericLiteral.hpp"
#include "algorithms/parse/TokenFactory.hpp"
#include "algorithms/parse/Identifier.hpp"
#include "algorithms/parse/Terminal.hpp"
#include "algorithms/parse/StockLexer.hpp"
#include "containers/lists/List.hpp"
#include "PGuard.hpp"
#include "OGuard.hpp"
#include "Debug.hpp"

BEGIN_QR_NAMESPACE

StockLexer::StockLexer( ParseStream *aStream ) :
  Lexer( aStream )
{
  if( ! init )
	{
	  comma     = getTerminal( "COMMA", "," );
	  dot       = getTerminal( "DOT", "." );
	  colon     = getTerminal( "COLON", ":" );
	  semicolon = getTerminal( "SEMICOLON", ";" );
	  lparen    = getTerminal( "LPAREN", "(" );
	  rparen    = getTerminal( "RPAREN", ")" );
	  lbrace    = getTerminal( "LBRACE", "{" );
	  rbrace    = getTerminal( "RBRACE", "}" );
	  lbracket  = getTerminal( "LBRACKET", "[" );
	  rbracket  = getTerminal( "RBRACKET", "]" );

	  id     = new Terminal( "id", new Identifier() );
	  number = new Terminal( "number", new NumericLiteral() );

	  getComma()     -> dontManage();
	  getDot()       -> dontManage();
	  getColon()     -> dontManage();
	  getSemicolon() -> dontManage();
	  getLParen()    -> dontManage();
	  getRParen()    -> dontManage();
	  getLBrace()    -> dontManage();
	  getRBrace()    -> dontManage();
	  getLBracket()  -> dontManage();
	  getRBracket()  -> dontManage();

	  id     -> dontManage();
	  number -> dontManage();

	  init = true;
	}

  addAt( TCAST( getComma() -> getRecognizer(), TokenFactory ), tail );
  addAt( TCAST( getDot() -> getRecognizer(), TokenFactory ), tail );
  addAt( TCAST( getColon() -> getRecognizer(), TokenFactory ), tail );
  addAt( TCAST( getSemicolon() -> getRecognizer(), TokenFactory ), tail );
  addAt( TCAST( getLParen() -> getRecognizer(), TokenFactory ), tail );
  addAt( TCAST( getRParen() -> getRecognizer(), TokenFactory ), tail );
  addAt( TCAST( getLBrace() -> getRecognizer(), TokenFactory ), tail );
  addAt( TCAST( getRBrace() -> getRecognizer(), TokenFactory ), tail );
  addAt( TCAST( getLBracket() -> getRecognizer(), TokenFactory ), tail );
  addAt( TCAST( getRBracket() -> getRecognizer(), TokenFactory ), tail );

  addAt( TCAST( getId() -> getRecognizer(), TokenFactory ), tail );
  addAt( TCAST( getNumber() -> getRecognizer(), TokenFactory ), tail );
}

StockLexer::~StockLexer()
{}

void StockLexer::addAt( TokenFactory *aFactory, Place aPlace )
{
  switch( aPlace )
	{
	case head:
	  factory -> prepend( aFactory );
	  break;
	case tail:
	  factory -> append( aFactory );
	  break;
	default:
	  test( false, "Wrong aPlace in StockLexer::addAt" );
	  break;
	}
}

Terminal *StockLexer::addTerminal( String aName, String aValue, 
								   Place aPlace )
{
  Terminal *term;

  term = getTerminal( aName, aValue );
  PGuard _term( term, this );
  addAt( TCAST( term -> getRecognizer(), TokenFactory ), aPlace );
  return term;
}

Terminal *StockLexer::getTerminal( String aName, String aValue )
{
  return new Terminal( aName, new Constant( aValue, aName.clone() ) );
}

Terminal *StockLexer::getComma() const
{
  return comma;
}

Terminal *StockLexer::getDot() const
{
  return dot;
}

Terminal *StockLexer::getColon() const
{
  return colon;
}

Terminal *StockLexer::getSemicolon() const
{
  return semicolon;
}

Terminal *StockLexer::getLParen() const
{
  return lparen;
}

Terminal *StockLexer::getRParen() const
{
  return rparen;
}

Terminal *StockLexer::getLBrace() const
{
  return lbrace;
}

Terminal *StockLexer::getRBrace() const
{
  return rbrace;
}

Terminal *StockLexer::getLBracket() const
{
  return lbracket;
}

Terminal *StockLexer::getRBracket() const
{
  return rbracket;
}

Terminal *StockLexer::getId() const
{
  return id;
}

Terminal *StockLexer::getNumber() const
{
  return number;
}

String  StockLexer::getClassName() const
{
  return "StockLexer";
}


boolean   StockLexer::init = false;
Terminal *StockLexer::comma = NULL;
Terminal *StockLexer::dot = NULL;
Terminal *StockLexer::colon = NULL;
Terminal *StockLexer::semicolon = NULL;
Terminal *StockLexer::lparen = NULL;
Terminal *StockLexer::rparen = NULL;
Terminal *StockLexer::lbrace = NULL;
Terminal *StockLexer::rbrace = NULL;
Terminal *StockLexer::lbracket = NULL;
Terminal *StockLexer::rbracket = NULL;
Terminal *StockLexer::id = NULL;
Terminal *StockLexer::number = NULL;

END_QR_NAMESPACE

#if defined( _INLINE )
#include "../src/Debug.ipp"
#endif


/*
 * $Log: StockLexer.cpp,v $
 * Revision 1.1  2000/09/19 18:20:08  philogelos
 * Lexer and parser redone.
 *
 */
