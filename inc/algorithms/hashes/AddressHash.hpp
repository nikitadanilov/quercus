// -*-C++-*- 

/*  inc/algorithms/hashes/AddressHash.hpp  */

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



#ifndef __ADDRESSHASH_HPP__
#define __ADDRESSHASH_HPP__

/* $Id: AddressHash.hpp,v 1.1 2001/04/16 10:25:01 philogelos Exp $ */

#include "Hash.hpp"
#include "CRef.hpp"
#include "defines.h"

BEGIN_QR_NAMESPACE

/**
   Hash object to its memory address.

   @author Philogelos
   @created Thu Apr 12 20:58:01 2001
*/
class AddressHash : public virtual Hash,
					public virtual Object
{

  /**
	 @param aFallBack hash used to hash strings and chars.
   */
public: AddressHash( Hash *aFallBack );

  /**
   */
public: virtual ~AddressHash();

public: virtual HashValue initial() const;
public: virtual HashValue final( HashValue aHash ) const;
public: virtual HashValue hashObject( const HashValue startFrom, 
									  const Top *anObject ) const;
public: virtual HashValue hashChars( const HashValue startFrom, 
									 const unichar *aChar, 
									 const Index aLength ) const;
  /**
   */
public:  virtual String  getClassName() const;

protected: CRef< Hash > fallback;
};

END_QR_NAMESPACE

/*
 * $Log: AddressHash.hpp,v $
 * Revision 1.1  2001/04/16 10:25:01  philogelos
 * Address hash, hashing object to its memory address added
 *
 */

/* __ADDRESSHASH_HPP__ */
#endif
