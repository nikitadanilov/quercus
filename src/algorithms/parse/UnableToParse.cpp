// -*-C++-*- 

/*  src/algorithms/parse/UnableToParse.cpp  */

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



/* $Id: UnableToParse.cpp,v 1.1 2000/09/19 18:20:08 philogelos Exp $ */
#if !defined( _INLINE )
static char cvsid[] = "@(#)$Id: UnableToParse.cpp,v 1.1 2000/09/19 18:20:08 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif

#include "algorithms/parse/UnableToParse.hpp"
#include "Debug.hpp"

BEGIN_QR_NAMESPACE

UnableToParse::UnableToParse( String aMessage, const Top *const aSource ) :
  ParseError( aMessage, aSource ),
  ExternalError( aMessage, aSource ),
  Exception( aMessage, aSource )
{}

String UnableToParse::getDescription() const
{
  return ParseError::getDescription() + ": unable to parse";
}

String  UnableToParse::getClassName() const
{
  return "UnableToParse";
}

END_QR_NAMESPACE

#if defined( _INLINE )
#include "../src/Debug.ipp"
#endif


/*
 * $Log: UnableToParse.cpp,v $
 * Revision 1.1  2000/09/19 18:20:08  philogelos
 * Lexer and parser redone.
 *
 */
