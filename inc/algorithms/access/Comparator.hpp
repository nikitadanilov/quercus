// -*-C++-*- 

/*  inc/algorithms/access/Comparator.hpp  */

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



#ifndef __COMPARATOR_HPP__
#define __COMPARATOR_HPP__

/* $Id: Comparator.hpp,v 1.1 2001/04/16 10:18:20 philogelos Exp $ */

#include "BinaryRelation.hpp"
#include "Object.hpp"
#include "Top.hpp"
#include "defines.h"

BEGIN_QR_NAMESPACE

typedef enum 
{ 
  lessThan = -1, 
  equalTo = 0, 
  greaterThan = +1 
} ComparisonResult;

typedef enum 
{
  less,
  lessOrEqual,
  equal,
  greater,
  greaterOrEqual
} ComparisonRelation;

interface Relation;

/**
   Interface for total orders.

   @author Philogelos
   @created Wed Mar 21 22:42:13 2001
*/
interface Comparator : public virtual Top
{
 public: virtual ComparisonResult compare( Top *aLeft, Top *aRight ) const = 0;
 public: virtual BinaryRelation *getAsRelation( ComparisonRelation aRelation ) const;

 protected: class ComparatorAsRelation : public virtual BinaryRelation,
			public virtual Object
 {
 public: ComparatorAsRelation( Comparator *aComparator, 
							   ComparisonRelation aRelation );
 public: virtual boolean in( const Top *anObj1, const Top *anObj2 ) const;
 protected: CRef< Comparator > comparator;
 protected: ComparisonRelation relation;
 };
};

END_QR_NAMESPACE

/*
 * $Log: Comparator.hpp,v $
 * Revision 1.1  2001/04/16 10:18:20  philogelos
 * ::getAsRelation() method to represent Comparator as order relation.
 * Now Comparators can be used (for example) by Container::contains()
 * method.
 *
 */

/* __COMPARATOR_HPP__ */
#endif
