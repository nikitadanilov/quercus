// -*-C++-*- 

/*  inc/UnaryRelation.hpp  */

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

#ifndef __UNARYRELATION_HPP__
#define __UNARYRELATION_HPP__

/*
   Reconstructed in 2026: this header was never committed to CVS. The
   declarations below follow the DWARF debug information of the 2002
   build (obj/UnaryRelation.o) and src/UnaryRelation.cpp.
*/

#include "Relation.hpp"
#include "Object.hpp"
#include "CRef.hpp"
#include "defines.h"

BEGIN_QR_NAMESPACE

interface BinaryRelation;

/**
   Interface for unary relations (predicates).

   @author Philogelos
   @created Sat Jun 23 2001
*/
abstract class UnaryRelation : public virtual Relation
{
  /** Returns true iff the single element of given enumeration is 
	  in this relation. */
 public: virtual boolean areIn( Enumeration *anElements ) const;
 public: virtual boolean is( const Top *anObj ) const = 0;

  /** Returns unary relation obtained from aRel by fixing its
	  argument at position aPlace (0 or 1) to anObj. */
 public: static UnaryRelation *getProjection( BinaryRelation *aRel, 
											  const Top *anObj, 
											  Index aPlace );
};

class ProjectedRel : public virtual UnaryRelation, public virtual Object
{
 public: ProjectedRel( BinaryRelation *aRel, 
					   const Top *anObj, Index aPlace );
 public: virtual boolean is( const Top *anObj ) const;

 protected: CRef< BinaryRelation > rel;
 protected: CRef< Top > object;
 protected: Index place;
};

END_QR_NAMESPACE

/* __UNARYRELATION_HPP__ */
#endif
