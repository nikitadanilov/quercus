// -*-C++-*- 

/*  src/algorithms/hashes/Hash.cpp  */

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



/* $Id: Hash.cpp,v 1.1 2001/04/16 10:27:20 philogelos Exp $ */
#if !defined( _INLINE )
static char cvsid[] = "@(#)$Id: Hash.cpp,v 1.1 2001/04/16 10:27:20 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif

#include "algorithms/hashes/Hash.hpp"
#include "OGuard.hpp"
#include "String.hpp"
#include "Debug.hpp"

BEGIN_QR_NAMESPACE

HashValue Hash::initial() const
{
  return 0;
}

HashValue Hash::final( HashValue aHash ) const
{
  return aHash;
}

HashValue Hash::hashString( const HashValue startFrom, 
							const String aString ) const
{
  return hashChars( startFrom, aString.getUNIChars(), aString.length() );
}

HashValue Hash::hashObject( const HashValue startFrom, 
							const Top *anObject ) const
{
  preC_( anObject != NULL );

  OGuard _object( anObject, this );

  return hashString( startFrom, anObject -> getString() );
}

END_QR_NAMESPACE

#if defined( _INLINE )
#include "../src/Debug.ipp"
#endif


/*
 * $Log: Hash.cpp,v $
 * Revision 1.1  2001/04/16 10:27:20  philogelos
 * Interface to hash functions added
 *
 */
