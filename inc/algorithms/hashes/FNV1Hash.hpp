// -*-C++-*- 

/*  inc/algorithms/hashes/FNV1Hash.hpp  */

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



#ifndef __FNV1HASH_HPP__
#define __FNV1HASH_HPP__

/* $Id: FNV1Hash.hpp,v 1.1 2001/04/16 10:25:54 philogelos Exp $ */

#include "Hash.hpp"
#include "defines.h"
#include "Object.hpp"

BEGIN_QR_NAMESPACE

/**
   FNV1 Hash: http://www.isthe.com/chongo/tech/comp/fnv/index.html

   @author Philogelos
   @created Wed Mar 21 18:40:09 2001
*/
class FNV1Hash : public virtual Hash,
				 public virtual Object
{
public: FNV1Hash( HashValue anInitialValue, HashValue aMagicPrime );
public: virtual ~FNV1Hash();

public: static FNV1Hash *getInstance();


public: virtual HashValue initial() const;
public: virtual HashValue hashChars( const HashValue startFrom, 
									 const unichar *aChar, 
									 const Index aLength ) const;
public: virtual HashValue hashUChar( const HashValue startFrom,
									 const unsigned char aChar ) const;

protected: static FNV1Hash *instance;

public:  virtual boolean equals( const Top *anOther) const;
public:  virtual Top *clone() const;
public:  virtual String  getString() const;
public:  virtual String  getClassName() const;

protected: HashValue initalValue;
protected: HashValue magicPrime;
};

END_QR_NAMESPACE

/*
 * $Log: FNV1Hash.hpp,v $
 * Revision 1.1  2001/04/16 10:25:54  philogelos
 * textbook FNV1 hash added
 *
 */

/* __FNV1HASH_HPP__ */
#endif
