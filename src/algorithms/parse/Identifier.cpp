// -*-C++-*- 

/*  src/algorithms/parse/Identifier.cpp  */

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



/* $Id: Identifier.cpp,v 1.1.1.1 2000/07/19 16:44:32 philogelos Exp $ */
#if !defined( _INLINE )
static char cvsid[] = "@(#)$Id: Identifier.cpp,v 1.1.1.1 2000/07/19 16:44:32 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif

#include "algorithms/parse/TokenAdapter.hpp"
#include "algorithms/parse/ParseStream.hpp"
#include "algorithms/parse/TokenCradle.hpp"
#include "algorithms/parse/Identifier.hpp"
#include "StringBuffer.hpp"
#include "Debug.hpp"
#include "Char.hpp"

BEGIN_QR_NAMESPACE

Identifier::Identifier()
{}

Identifier::~Identifier()
{}

boolean Identifier::canStartHere( TokenCradle *aCradle ) const
{
  preC_( aCradle != NULL );

  return( doInternal( aCradle ) > aCradle -> getAccepted() );
}

void Identifier::grow( TokenCradle *aCradle )
{
  preC_( aCradle != NULL );

  aCradle -> acceptTo( doInternal( aCradle ) );
}

Token *Identifier::graduate( TokenCradle *aCradle )
{
  preC_( aCradle != NULL );

  TokenAdapter *result;
  
  result = new TokenAdapter();
  result -> setTag( new String( "identifier" ) );
  result -> setCore( aCradle -> getResult().clone() );
  return result;
}

Index Identifier::doInternal( TokenCradle *aCradle ) const
{
  preC_( aCradle != NULL );

  if( ! aCradle -> hasAt( 0 ) ||
	  ! canStartIdentifier( aCradle -> getAt( 0 ) ) )
	{
	  return 0;
	}
  else
	{
	  for( Index i = 1 ; 
		   aCradle -> hasAt( i ) && 
			 canContinueIdentifier( aCradle -> getAt( i ) ) ; ++i )
		{}
	  return i;
	}
}

boolean Identifier::canStartIdentifier( const unichar aChar )
{
  return isLetter( aChar );
}

boolean Identifier::canContinueIdentifier( const unichar aChar )
{
  return isLetter( aChar ) || isDigit( aChar );
}

boolean Identifier::isLetter( const unichar aChar )
{
  return letters.contains( aChar );
}

boolean Identifier::isDigit( const unichar aChar )
{
  return digits.contains( aChar );
}

String  Identifier::getClassName() const
{
  return "Identifier";
}

String Identifier::letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
String Identifier::digits = "0123456789";

END_QR_NAMESPACE

#if defined( _INLINE )
#include "../src/Debug.ipp"
#endif


/*
 * $Log: Identifier.cpp,v $
 * Revision 1.1.1.1  2000/07/19 16:44:32  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.1  2000/07/19 08:48:13  god
 * new parse method: ask all factories and accept one with longest match
 *
 */
