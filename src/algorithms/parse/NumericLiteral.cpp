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



/* $Id: NumericLiteral.cpp,v 1.2 2000/08/26 13:26:55 philogelos Exp $ */
#if !defined( _INLINE )
static char cvsid[] = "@(#)$Id: NumericLiteral.cpp,v 1.2 2000/08/26 13:26:55 philogelos Exp $";
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

Index NumericLiteral::accept( TokenCradle *aCradle ) const
{
  preC_( aCradle != NULL );

  Index base;
  Index len;

  base = 10;
  for( len = 0 ; aCradle -> hasAt( len ) ; ++len )
	{
	  unichar element;

	  element = aCradle -> getAt( len );
	  if( !isDigitInBase( element, base ) )
		{
		  if( ( len != 1 ) ||
			  ( aCradle -> getAt( 0 ) != ( unichar ) '0' ) )
			{
			  break;
			}
		  else
			{
			  base = getBase( element );
			  if( base < 0 )
				{
				  break;
				}
			}
		}
	}
  return len;
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
	  return -1;
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
 * Revision 1.2  2000/08/26 13:26:55  philogelos
 * New simple parser framework done. Compiles and passes Parser::tester()
 *
 * Revision 1.1.1.1  2000/07/19 16:44:27  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.1  2000/07/19 08:48:13  god
 * new parse method: ask all factories and accept one with longest match
 *
 */
