// -*-C++-*- 

/*  inc/algorithms/hashes/Hash.hpp  */

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



#ifndef __HASH_HPP__
#define __HASH_HPP__

/* $Id: Hash.hpp,v 1.1 2001/04/16 10:27:20 philogelos Exp $ */

#include "Top.hpp"
#include "defines.h"

BEGIN_QR_NAMESPACE

typedef unsigned long HashValue;

/**
   Interface to hashing functions.

   @author Philogelos
   @created Wed Mar 21 18:20:49 2001
*/
interface Hash : public virtual Top
{
 public: virtual HashValue initial() const;
 public: virtual HashValue final( HashValue aHash ) const;
 public: virtual HashValue hashString( const HashValue startFrom, 
									   const String aString ) const;
 public: virtual HashValue hashObject( const HashValue startFrom, 
									   const Top *anObject ) const;
 public: virtual HashValue hashChars( const HashValue startFrom, 
									  const unichar *aChar, 
									  const Index aLength ) const = 0;
};

END_QR_NAMESPACE

/*
 * $Log: Hash.hpp,v $
 * Revision 1.1  2001/04/16 10:27:20  philogelos
 * Interface to hash functions added
 *
 */

/* __HASH_HPP__ */
#endif
