// -*-C++-*- 

/*  src/algorithms/parse/TokenFactory.cpp  */

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



/* $Id: TokenFactory.cpp,v 1.1 2000/08/26 13:26:55 philogelos Exp $ */
#if !defined( _INLINE )
static char cvsid[] = "@(#)$Id: TokenFactory.cpp,v 1.1 2000/08/26 13:26:55 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif

#include "algorithms/parse/TokenFactory.hpp"
#include "algorithms/parse/TokenAdapter.hpp"
#include "algorithms/parse/TokenCradle.hpp"
#include "PGuard.hpp"

BEGIN_QR_NAMESPACE

Token *TokenFactory::graduate( TokenCradle *aCradle, Index aLength )
{
  preC_( aCradle != NULL );
  preC_( aLength >= 0 );

  Token *result;

  result = getMatrix();
  test_( result != NULL );
  PGuard _result( result, this );

  result -> setCore( aCradle -> pop( aLength ).clone() );
  return result;
}

Token *TokenFactory::getMatrix() const
{
  TokenAdapter *result;
  
  result = new TokenAdapter();
  PGuard _result( result, this );

  result -> setTag( new String( getClassName() ) );
  return result;
}

END_QR_NAMESPACE

#if defined( _INLINE )
#include "../src/Debug.ipp"
#endif


/*
 * $Log: TokenFactory.cpp,v $
 * Revision 1.1  2000/08/26 13:26:55  philogelos
 * New simple parser framework done. Compiles and passes Parser::tester()
 *
 *
 */
