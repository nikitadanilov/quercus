// -*-C++-*- 

/*  src/algorithms/parse/Constant.cpp  */

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



/* $Id: Constant.cpp,v 1.2 2000/08/26 13:26:55 philogelos Exp $ */
#if !defined( _INLINE )
static char cvsid[] = "@(#)$Id: Constant.cpp,v 1.2 2000/08/26 13:26:55 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif

#include "algorithms/parse/TokenAdapter.hpp"
#include "algorithms/parse/ParseStream.hpp"
#include "algorithms/parse/TokenCradle.hpp"
#include "algorithms/parse/Constant.hpp"
#include "StringBuffer.hpp"
#include "Debug.hpp"
#include "Char.hpp"
#include "Debug.hpp"

BEGIN_QR_NAMESPACE

Constant::Constant( String aString, Top *aTokenCore )
{
  string = aString;
  core = aTokenCore;
}

Constant::~Constant()
{}

Index Constant::accept( TokenCradle *aCradle ) const
{
  preC_( aCradle != NULL );

  if( aCradle -> hasAt( string.length() - 1 ) )
	{
	  for( Index i = 0 ; i < string.length() ; ++i )
		{
		  if( aCradle -> getAt( i ) != string.getUNIChars()[ i ] )
			{
			  return 0;
			}
		}
	  return string.length();
	}
  else
	{
	  return 0;
	}
}

Token *Constant::getMatrix() const
{
  TokenAdapter *result;
  
  result = new TokenAdapter();
  result -> setTag( *core );
  return result;
}

String  Constant::getClassName() const
{
  return "Constant";
}

END_QR_NAMESPACE

#if defined( _INLINE )
#include "../src/Debug.ipp"
#endif


/*
 * $Log: Constant.cpp,v $
 * Revision 1.2  2000/08/26 13:26:55  philogelos
 * New simple parser framework done. Compiles and passes Parser::tester()
 *
 * Revision 1.1.1.1  2000/07/19 16:44:34  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.1  2000/07/19 08:48:13  god
 * new parse method: ask all factories and accept one with longest match
 *
 */
