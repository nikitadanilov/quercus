// -*-C++-*- 

/*  src/algorithms/parse/TokenAdapter.cpp  */

/*
 * Author: Philogelos A. <Philogelos@yahoo.com>
 * Maintainer: Philogelos A.
 * Keywords: C++, library, containers
 *
 * Copyright (C) 1998, 1999 Philogelos A.
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



/* $Id: TokenAdapter.cpp,v 1.1.1.1 2000/07/19 16:44:07 philogelos Exp $ */
#if !defined(_INLINE)
static char cvsid[] = "@(#)$Id: TokenAdapter.cpp,v 1.1.1.1 2000/07/19 16:44:07 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif

#include "algorithms/parse/TokenAdapter.hpp"
#include "OGuard.hpp"
#include "PGuard.hpp"
#include "Debug.hpp"
#include "LinkManager.hpp"

BEGIN_QR_NAMESPACE

TokenAdapter::TokenAdapter()
{
}

TokenAdapter::~TokenAdapter()
{}

void TokenAdapter::setCore( Top *aValue )
{
  setAt( 1, aValue );
}

Top *TokenAdapter::getCore() const
{
  return( getAt( 1 ) );
}

void TokenAdapter::setTag( ParseTag *aTag )
{
  setAt( 2, aTag );
}

ParseTag *TokenAdapter::getTag() const
{
  return( getAt( 2 ) );
}

boolean TokenAdapter::equals( const Top *anOther ) const
{
  TokenAdapter *other;

  other = DCAST( anOther, TokenAdapter );
  if( other == ( TokenAdapter * ) NULL )
	{
	  return false;
	}
  OGuard _other( ( Object * ) other, ( Object * ) this );
  return( ( other -> getTag() -> equals( getTag() ) ) &&
		  ( other -> getCore() -> equals( getCore() ) ) );
}

Token *TokenAdapter::cloneToken() const
{
  TokenAdapter *result;

  result = new TokenAdapter();
  PGuard _result( result, this );
  result -> setCore( getCore() );
  result -> setTag( getTag() );
  return result;
}

Top *TokenAdapter::clone() const
{
  return cloneToken();
}

String  TokenAdapter::getString() const
{
  String result;
  
  result = String( "Tag: " );
  result += ( ( getTag() == null ) ? String::nullLiteral : ( getTag() -> getString() ) );
  result += String( " value: " ); 
  result += ( ( getCore() == null ) ? String::nullLiteral : ( getCore() -> getString() ) );
  return result;
}

String  TokenAdapter::getClassName() const
{
  return "TokenAdapter";
}


END_QR_NAMESPACE

#if defined(_INLINE)
#include "../src/Debug.ipp"
#endif

/*
 * $Log: TokenAdapter.cpp,v $
 * Revision 1.1.1.1  2000/07/19 16:44:07  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.3  2000/05/06 08:36:28  god
 * committed
 *
 * Revision 1.2  2000/04/09 11:29:40  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:30  god
 * Imported sources
 *
 * Revision 1.3  1999/05/22 13:00:33  philogelos
 * Merging sources back from SPARC
 *
 * Revision 1.2  1999/03/03 19:09:32  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.1  1999/02/28 16:29:17  philogelos
 * Parser added
 * */
