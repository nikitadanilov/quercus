// -*-C++-*- 

/*  src/algorithms/hashes/AddressHash.cpp  */

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



/* $Id: AddressHash.cpp,v 1.1 2001/04/16 10:25:01 philogelos Exp $ */
#if !defined( _INLINE )
static char cvsid[] = "@(#)$Id: AddressHash.cpp,v 1.1 2001/04/16 10:25:01 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif

#include "algorithms/hashes/AddressHash.hpp"
#include "String.hpp"
#include "Debug.hpp"

BEGIN_QR_NAMESPACE

AddressHash::AddressHash( Hash *aFallBack )
{
  preC_( aFallBack != NULL );

  fallback = aFallBack;
}

AddressHash::~AddressHash()
{}

HashValue AddressHash::initial() const
{
  return fallback -> initial();
}

HashValue AddressHash::final( HashValue aHash ) const
{
  return fallback -> final( aHash );
}

HashValue AddressHash::hashObject( const HashValue startFrom, 
								   const Top *anObject ) const
{
  return startFrom + ( HashValue ) ( void * ) anObject;
}

HashValue AddressHash::hashChars( const HashValue startFrom, 
								  const unichar *aChar, 
								  const Index aLength ) const
{
  return fallback -> hashChars( startFrom, aChar, aLength );
}

String  AddressHash::getClassName() const
{
  return "AddressHash";
}

END_QR_NAMESPACE

#if defined( _INLINE )
#include "../src/Debug.ipp"
#endif


/*
 * $Log: AddressHash.cpp,v $
 * Revision 1.1  2001/04/16 10:25:01  philogelos
 * Address hash, hashing object to its memory address added
 *
 */
