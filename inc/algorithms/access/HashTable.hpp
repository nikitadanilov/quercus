// -*-C++-*- 

/*  inc/algorithms/access/HashTable.hpp  */

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



#ifndef __HASHTABLE_HPP__
#define __HASHTABLE_HPP__

/* $Id: HashTable.hpp,v 1.1 2001/04/16 10:20:01 philogelos Exp $ */

#include "AccessMethod.hpp"
#include "Object.hpp"
#include "defines.h"
#include "CRef.hpp"

BEGIN_QR_NAMESPACE

class Hash;
class CArray;
class List;
class Dictionary;

/**
   Hash table.

   @author Philogelos
   @created Wed Mar 21 20:28:32 2001
*/
class HashTable : public virtual AccessMethod,
				  public virtual Object
{
public: HashTable( Hash *aHash, Index aSlots );
public: virtual ~HashTable();

public: virtual void insert( Top *aKey, 
							 Top *anObject ) THROWS( AlreadyExists * );
public: virtual void remove( Top *aKey ) THROWS( NoEntity * );
public: virtual Top *lookup( Top *aKey ) const;

public: virtual boolean equals( const Top *anOther) const;

public: virtual String  getString() const;
public: virtual String  getClassName() const;

protected: virtual Index getHash( Top *aKey ) const;
protected: virtual Dictionary *getChain( Top *aKey ) const;

protected: CRef< Hash > hash;
protected: CRef< CArray > chains;
#if defined( TESTING )
public:  virtual boolean tester( int aParam ) const;
#endif
};

END_QR_NAMESPACE

/*
 * $Log: HashTable.hpp,v $
 * Revision 1.1  2001/04/16 10:20:01  philogelos
 * HashTable access method. Stores each hash-chain as (Dumb)Dictionary
 * keyed by key in table.
 *
 */

/* __HASHTABLE_HPP__ */
#endif
