// -*-C++-*- 

/*  inc/algorithms/containers/ContainerAlgorithms.hpp  */

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



#ifndef __CONTAINERALGORITHMS_HPP__
#define __CONTAINERALGORITHMS_HPP__

/* $Id: ContainerAlgorithms.hpp,v 1.2 2001/06/23 12:22:51 philogelos Exp $ */

#include "Object.hpp"
#include "algorithms/AlgorithmPackage.hpp"
#include "containers/Container.hpp"
#include "defines.h"
#include "CRef.hpp"

BEGIN_QR_NAMESPACE

#define CALG ContainerAlgorithms::get()

interface Container;
interface PositionFactory;
interface UnaryRelation;
interface ModifiableContainer;

/**
   Algorithms working with containers.

   @see Container
   @author Philogelos
   @created Wed Apr 18 19:55:06 2001
*/
class ContainerAlgorithms : public virtual AlgorithmPackage,
							public virtual Object
{

  /** Returns canonical instance of this class, creating it if necessary. */
public: static ContainerAlgorithms *get();
  /** Returns class name: "ContainerAlgorithms" */
public: virtual String  getClassName() const;

  /** "Flattens" aStructure. aStructure is considered to be a tree:
	  if its element E is container it's sub-tree, otherwise leaf and
	  so on, recursively. Flatten puts into aFactory leafs of this
	  tree in tree order (induced by standard ordering within aStructure
	  and its sub-trees). 
	  
	  If aStructure contains cycles you lose.

	  @param aStructure structure to be flattened
	  @param source of slots where flattened aStructure will be stored.
  */
public: virtual void flatten( Top *aStructure, PositionFactory *aFactory );

  /** Removes first element of aContainer, satisfying aRel.
	  Returns true iff such element was found. 
	  
	  @param aContainer container where to find
	  @param aRel predicate

	  @see ::removeAll
	  @see ::remove
  */
public: virtual boolean removeFirst( ModifiableContainer *aContainer, 
									 UnaryRelation *aRel );

  /** Removes all elements of aContainer, satisfying aRel.
	  Returns number of removed elements. 
	  
	  @param aContainer container where to find
	  @param aRel predicate

	  @see ::removeFirst
	  @see ::remove
  */
public: virtual Index removeAll( ModifiableContainer *aContainer, 
								 UnaryRelation *aRel );

  /** Removes no more than given number of elements of aContainer,
	  satisfying aRel.  
	  Returns number of removed elements.
	  
	  @param aContainer container where to find
	  @param aRel predicate
	  @param aNumber number of elements to remove. If 0, then
	  remove all elements satisfying aRel

	  @see ::removeAll
	  @see ::removeFirst
  */
public: virtual Index remove( ModifiableContainer *aContainer, 
							  UnaryRelation *aRel, Index aNumber );

  /** Hidden constructor. It's used by ::get() to create the only 
	  instance of this class. 
	  
	  @see ::get()
  */
protected: ContainerAlgorithms();
protected: virtual ~ContainerAlgorithms();
protected: static CRef< ContainerAlgorithms > instance;

#if defined( TESTING )
public: virtual boolean tester( int ) const;
#endif
};

END_QR_NAMESPACE

/*
 * $Log: ContainerAlgorithms.hpp,v $
 * Revision 1.2  2001/06/23 12:22:51  philogelos
 *  . ::get(), ::getClassName() and ::flatten() commented
 *  . ::removeFirst(), ::removeAll() and ::remove() added
 *
 * Revision 1.1  2001/06/09 15:35:10  philogelos
 * ContainerAlgorithms added (only ::flatten() is implemented as of now)
 *
 */

/* __CONTAINERALGORITHMS_HPP__ */
#endif
