// -*-C++-*- 

/*  src/algorithms/parse/NumericLiteral.cpp  */

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



/* $Id: NumericLiteral.cpp,v 1.1.1.1 2000/07/19 16:44:27 philogelos Exp $ */
#if !defined( _INLINE )
static char cvsid[] = "@(#)$Id: NumericLiteral.cpp,v 1.1.1.1 2000/07/19 16:44:27 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif

#include "algorithms/parse/NumericLiteral.hpp"
#include "algorithms/parse/TokenAdapter.hpp"
#include "algorithms/parse/ParseStream.hpp"
#include "algorithms/parse/TokenCradle.hpp"
#include "algorithms/parse/ParseError.hpp"
#include "StringBuffer.hpp"
#include "Integer.hpp"
#include "Debug.hpp"
#include "Char.hpp"

BEGIN_QR_NAMESPACE

NumericLiteral::NumericLiteral()
{}

NumericLiteral::~NumericLiteral()
{}

boolean NumericLiteral::canStartHere( TokenCradle *aCradle ) const
{
  preC_( aCradle != NULL );

  // DLOG( "NumericLiteral::canStartHere: accepted: %li", aCradle -> getAccepted() );
  return( doInternal( aCradle ) > aCradle -> getAccepted() );
}

void NumericLiteral::grow( TokenCradle *aCradle )
{
  preC_( aCradle != NULL );

  aCradle -> acceptTo( doInternal( aCradle ) );
}

Index NumericLiteral::doInternal( TokenCradle *aCradle ) const
{
  preC_( aCradle != NULL );

  Index base;
  Index len;

  base = 10;
  for( len = 0 ; aCradle -> hasAt( len ) ; ++len )
	{
	  unichar element;

	  element = aCradle -> getAt( len );
	  // DLOG( "NumericLiteral::doInternal: loop: %li, %c", len, ( char ) element );
	  if( ( ( len != 1 ) || ( aCradle -> getAt( 0 ) != ( unichar ) '0' ) ) &&
		  ! isDigitInBase( element, base ) )
		{
		  // DLOG( "NumericLiteral::doInternal: break1" );
		  break;
		}
	  else if( len == 1 )
		{
		  base = getBase( element );
		  if( base < 0 )
			{
			  // DLOG( "NumericLiteral::doInternal: break2" );
			  break;
			}
		}
	}
  // DLOG( "NumericLiteral::doInternal: len: %li", len );
  return len;
}

Token *NumericLiteral::graduate( TokenCradle *aCradle )
{
  preC_( aCradle != NULL );

  TokenAdapter *result;
  
  result = new TokenAdapter();
  result -> setTag( new String( "number" ) );
  result -> setCore( aCradle -> getResult().clone() );
  return result;
}

boolean NumericLiteral::isDigitInBase( unichar aChar, Index aBase )
{
  preC_( aBase > 1 );

  if( aBase <= 10 )
	{
	  return( ( aChar - ( unichar ) '0' < aBase ) &&
			  ( aChar - ( unichar ) '0' >= 0 ) );
	}
  else
	{
	  return( isDigitInBase( aChar, 10 ) || 
			  ( ( aChar - ( unichar ) 'a' < aBase ) &&
				( aChar - ( unichar ) 'a' >= 0 ) ) ||
			  ( ( aChar - ( unichar ) 'A' < aBase ) &&
				( aChar - ( unichar ) 'A' >= 0 ) ) );
	}
}

Index NumericLiteral::getBase( unichar aChar )
{
  switch( aChar )
	{
	case 'x':
	  return 16;
	case 'o':
	  return 8;
	case 'b':
	  return 2;
	default:
	  if( ! isDigitInBase( aChar, 10 ) )
		{
		  return -1;
		}
	  else
		{
		  return 10;
		}
	}
}

String  NumericLiteral::getClassName() const
{
  return "NumericLiteral";
}

END_QR_NAMESPACE

#if defined( _INLINE )
#include "../src/Debug.ipp"
#endif


/*
 * $Log: NumericLiteral.cpp,v $
 * Revision 1.1.1.1  2000/07/19 16:44:27  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.1  2000/07/19 08:48:13  god
 * new parse method: ask all factories and accept one with longest match
 *
 */
