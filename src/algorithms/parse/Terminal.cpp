// -*-C++-*- 

/*  src/algorithms/parse/Terminal.cpp  */

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



/* $Id: Terminal.cpp,v 1.1 2000/09/19 18:20:08 philogelos Exp $ */
#if !defined( _INLINE )
static char cvsid[] = "@(#)$Id: Terminal.cpp,v 1.1 2000/09/19 18:20:08 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif

#include "iter/enumerations/LookAheadEnumeration.hpp"
#include "algorithms/parse/ParseError.hpp"
#include "algorithms/parse/Terminal.hpp"
#include "algorithms/parse/TokenFactory.hpp"
#include "algorithms/parse/Token.hpp"
#include "Recognizer.hpp"
#include "OGuard.hpp"
#include "Debug.hpp"

BEGIN_QR_NAMESPACE

Terminal::Terminal( String aName, Recognizer *aToken ) :
  GrammarNode( aName ), token( aToken )
{}

Terminal::~Terminal()
{}

Recognizer *Terminal::getRecognizer() const
{
  return *token;
}

void Terminal::parse( LookAheadEnumeration *aStream ) THROWS( ParseError * )
{
  preC_( aStream != NULL );
  OGuard _stream( aStream, this );

  if( aStream -> hasMoreElements() )
	{
	  CRef< Top > onWire;

	  onWire = aStream -> getNextElement();
	  // DLOGOBJECT( "onwire: %s", *onWire );
	  // DLOGOBJECT( "recognizer: %s", getRecognizer() );
	  if( !getRecognizer() -> accepts( *onWire ) )
		{
// 		  DLOG( String( "want: ,," ) + tag -> getString() + "``" +
// 				String( "got: ,," ) + tagInStream -> getString() + "``" );
		  throw new WrongToken
			( String( "want: ,," ) + getRecognizer() -> getString() + "``" +
			  String( "got: ,," ) + onWire -> getString() + "``", null );
		}
	}
  else
	{
	  throw new EOSDuringParse
		( String( "Unexpected end of stream while looking for: " ) +
		  ",," + getRecognizer() -> getString() + "``", null );
	}
}

String  Terminal::getString() const
{
  return getName() + " -> " + getRecognizer() -> getString();
}

String  Terminal::getClassName() const
{
  return "Terminal";
}

WrongToken::WrongToken( String aMessage, const Top *const aSource ) :
  UnableToParse( aMessage, aSource ),
  ParseError( aMessage, aSource ),
  ExternalError( aMessage, aSource ),
  Exception( aMessage, aSource )
{}

String WrongToken::getClassName() const
{
  return "WrongToken";
}

String WrongToken::getDescription() const
{
  return UnableToParse::getDescription() +
	": expected token not found";
}

EOSDuringParse::EOSDuringParse( String aMessage, const Top *const aSource ) :
  UnableToParse( aMessage, aSource ),
  ParseError( aMessage, aSource ),
  ExternalError( aMessage, aSource ),
  Exception( aMessage, aSource )
{}

String EOSDuringParse::getClassName() const
{
  return "EOSDuringParse";
}

String EOSDuringParse::getDescription() const
{
  return UnableToParse::getDescription() +
	": end of stream during parse";
}

END_QR_NAMESPACE

#if defined( _INLINE )
#include "../src/Debug.ipp"
#endif


/*
 * $Log: Terminal.cpp,v $
 * Revision 1.1  2000/09/19 18:20:08  philogelos
 * Lexer and parser redone.
 *
 */
