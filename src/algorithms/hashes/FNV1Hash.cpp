// -*-C++-*- 

/*  src/algorithms/hashes/FNV1Hash.cpp  */

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



/* $Id: FNV1Hash.cpp,v 1.1 2001/04/16 10:25:54 philogelos Exp $ */
#if !defined( _INLINE )
static char cvsid[] = "@(#)$Id: FNV1Hash.cpp,v 1.1 2001/04/16 10:25:54 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif

#include "algorithms/hashes/FNV1Hash.hpp"
#include "String.hpp"
#include "Debug.hpp"

BEGIN_QR_NAMESPACE

FNV1Hash::FNV1Hash( HashValue anInitialValue, HashValue aMagicPrime )
{
  initalValue = anInitialValue;
  magicPrime = aMagicPrime;
}

FNV1Hash::~FNV1Hash()
{}

FNV1Hash *FNV1Hash::getInstance()
{
  if( instance == NULL )
	{
	  instance = new FNV1Hash( 0x811c9dc5, 0x01000193 );
	  instance -> dontManage();
	}
  return instance;
}


HashValue FNV1Hash::initial() const
{
  return initalValue;
}

HashValue FNV1Hash::hashChars( const HashValue startFrom, 
							   const unichar *aChar, 
							   const Index aLength ) const
{
  HashValue hash;
  Index i;

  for( hash = startFrom, i = 0 ; i < aLength ; ++i )
	{
	  hash = hashUChar( hash, aChar[ i ] >> 8 );
	  hash = hashUChar( hash, aChar[ i ] & 0xff );
	  /* DLOG( "hashChars: %lx: %c", hash, message[ i ] ); */
	}
  return hash;
}

HashValue FNV1Hash::hashUChar( const HashValue startFrom,
							   const unsigned char aChar ) const
{
  return ( startFrom * magicPrime ) ^ aChar;
}

boolean FNV1Hash::equals( const Top *anOther ) const
{
  return( DCAST( anOther, FNV1Hash ) != NULL );
}

Top *FNV1Hash::clone() const
{
  return new FNV1Hash( initalValue, magicPrime );
}

String  FNV1Hash::getString() const
{
  return String( "fnv-1 hash: init: %lx, prime: %lx" ).format
	( 0, initalValue, magicPrime );
}

String  FNV1Hash::getClassName() const
{
  return "FNV1Hash";
}

FNV1Hash *FNV1Hash::instance = NULL;

END_QR_NAMESPACE

#if defined( _INLINE )
#include "../src/Debug.ipp"
#endif


/*
 * $Log: FNV1Hash.cpp,v $
 * Revision 1.1  2001/04/16 10:25:54  philogelos
 * textbook FNV1 hash added
 *
 */
