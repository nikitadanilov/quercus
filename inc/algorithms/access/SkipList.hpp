// -*-C++-*- 

/*  inc/algorithms/access/SkipList.hpp  */

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



#ifndef __SKIPLIST_HPP__
#define __SKIPLIST_HPP__

/* $Id: SkipList.hpp,v 1.1 2001/04/16 10:21:40 philogelos Exp $ */

#include "Object.hpp"
#include "Comparator.hpp"
#include "AccessMethod.hpp"
#include "CRef.hpp"
#include "defines.h"

BEGIN_QR_NAMESPACE

class CArray;
class List;

/**
   Skip list.

   @author Philogelos
   @created Wed Mar 21 22:25:28 2001
*/
class SkipList : public virtual AccessMethod,
				 public virtual Object
{
  class Node;

public: SkipList( Comparator *aComparator, Index anInitialHeight );
public: virtual ~SkipList();

public: virtual void insert( Top *aKey, 
							 Top *anObject ) THROWS( AlreadyExists * );
public: virtual void remove( Top *aKey ) THROWS( NoEntity * );
public: virtual Top *lookup( Top *aKey ) const;

public:  virtual String  getString() const;
public:  virtual String  getClassName() const;

protected: virtual boolean findPos( Top *aKey ) const;
protected: virtual List *getListAt( Index anIndex ) const;
protected: virtual Pair *getAt( Index anIndex ) const;
protected: virtual Pair *getAt( Index anIndex ) const;
protected: virtual ComparisonResult compareWith( Top *aKey, 
												 Index aHeight ) const;

protected: CRef< Comparator > comp;
protected: CRef< CArray > list;
protected: CRef< Pair > minusInfinity;
protected: CRef< Pair > plusInfinity;

protected: class Node : public virtual Object
{
public: Node( Top *aKey, Top *aValue, Index aHeight );
public: virtual ~Node();

public: Position *getAt( Index height );

public: CRef< Top > value;
public: CRef< Top > key;
public: CRef< List > tower;
public: Index height;
};

};

END_QR_NAMESPACE

/*
 * $Log: SkipList.hpp,v $
 * Revision 1.1  2001/04/16 10:21:40  philogelos
 * Skip-list access method added (not done yet).
 *
 */

/* __SKIPLIST_HPP__ */
#endif
