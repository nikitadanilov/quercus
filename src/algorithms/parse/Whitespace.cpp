// -*-C++-*- 

/*  src/algorithms/parse/Whitespace.cpp  */

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



/* $Id: Whitespace.cpp,v 1.1.1.1 2000/07/19 16:44:17 philogelos Exp $ */
#if !defined( _INLINE )
static char cvsid[] = "@(#)$Id: Whitespace.cpp,v 1.1.1.1 2000/07/19 16:44:17 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif

#include "algorithms/parse/Whitespace.hpp"
#include "algorithms/parse/TokenAdapter.hpp"
#include "algorithms/parse/ParseStream.hpp"
#include "algorithms/parse/TokenCradle.hpp"
#include "StringBuffer.hpp"
#include "Debug.hpp"
#include "Char.hpp"

BEGIN_QR_NAMESPACE

Whitespace::Whitespace()
{}

Whitespace::~Whitespace()
{}

boolean Whitespace::canStartHere( TokenCradle *aCradle ) const
{
  preC_( aCradle != NULL );

  for( Index i = 0 ; i < aCradle -> getAccepted() ; ++i )
	{
	  if( ! isWhitespace( aCradle -> getBuffer() -> getAt( i ) ) )
		{
		  return false;
		}
	}
  return aCradle -> hasAt( aCradle -> getAccepted() ) && 
	isWhitespace( aCradle -> getAt( aCradle -> getAccepted() ) );
}

void Whitespace::grow( TokenCradle *aCradle )
{
  preC_( aCradle != NULL );

  while( aCradle -> hasAt( aCradle -> getAccepted() ) && 
		 isWhitespace( aCradle -> getAt( aCradle -> getAccepted() ) ) )
	{
	  aCradle -> accept( 1 );
	}
}

Token *Whitespace::graduate( TokenCradle *aCradle )
{
  preC_( aCradle != NULL );

  TokenAdapter *result;
  
  result = new TokenAdapter();
  result -> setTag( new String( "whitespace" ) );
  result -> setCore( aCradle -> getResult().clone() );
  return result;
}

boolean Whitespace::isWhitespace( const unichar aChar )
{
  return whitespaces.contains( aChar );
}

String  Whitespace::getClassName() const
{
  return "Whitespace";
}

String Whitespace::whitespaces = " \n\t\r";

END_QR_NAMESPACE

#if defined( _INLINE )
#include "../src/Debug.ipp"
#endif


/*
 * $Log: Whitespace.cpp,v $
 * Revision 1.1.1.1  2000/07/19 16:44:17  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.1  2000/07/19 08:48:13  god
 * new parse method: ask all factories and accept one with longest match
 *
 */
