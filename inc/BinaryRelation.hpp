// -*-C++-*- 

/*  inc/BinaryRelation.hpp  */

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



#ifndef __BINARYRELATION_HPP__
#define __BINARYRELATION_HPP__

/* $Id: BinaryRelation.hpp,v 1.1 2001/04/13 19:29:45 philogelos Exp $ */

#include "Relation.hpp"
#include "defines.h"

BEGIN_QR_NAMESPACE

/**
   Interface for binary relations.

   @author Philogelos
   @created Fri Apr 13 19:49:42 2001
*/
abstract class BinaryRelation : public virtual Relation
{
  /** Returns true iff first two elements of given enumeration are 
	  in this relation. */
 public: virtual boolean areIn( Enumeration *anElements ) const;
 public: virtual boolean in( const Top *anObj1, const Top *anObj2 ) const = 0;
};

END_QR_NAMESPACE

/*
 * $Log: BinaryRelation.hpp,v $
 * Revision 1.1  2001/04/13 19:29:45  philogelos
 * Relations added
 *
 */

/* __BINARYRELATION_HPP__ */
#endif
