// -*- C++ -*-

/*  inc/containers/Container.hpp  */


/*
 * Author: Philogelos A. <Philogelos@yahoo.com>
 * Maintainer: Philogelos A.
 * Keywords: C++, library, containers
 *
 * Copyright (C) 1998 Philogelos A.
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



#ifndef __CONTAINER_HPP__
#define __CONTAINER_HPP__

/* $Id: Container.hpp,v 1.1.1.1 2000/07/19 16:58:54 philogelos Exp $ */

#include "Object.hpp"
#include "containers/Position.hpp"
#include "containers/PositionEnumeration.hpp"
#include "iter/enumerations/Enumeration.hpp"
#include "iter/iterators/Iterator.hpp"
#include "defines.h"

BEGIN_QR_NAMESPACE

interface Modifier;
interface PositionEnumeration;
interface Map;

/**
   Interface for containers.
   Containers are objects containing other objects and
   providing access, search and modification methods.

   Container aggregates two concepts: structrure and
   contents.

   Structure is collection of ``slots'' with some additional
   structure, e.g, structure of set (no duplicates allowed),
   structure of graph or binary tree.

   Contents is binding from slots to (possibly null) values.
   Position is an address of the slot within given container,
   that is, position is a way to point to some slot 
   (e.g., ``first slot'', ``current slot'',
   ``i-th slot'' etc.).

   If container allows to change it's structure dynamically
   it is said to be ``modifiable''. If it allows to change
   it's contents dynamically it is said to be ``mutable''.

   @see Position

   @author Philogelos
   @created ø‚› 19 ∏Ó› 1998 13:22:23
*/
interface Container : virtual public Top
{
 public:    virtual boolean isEmpty() const = 0;

 /**
	Returns enumeration of all positions within this
	container. I.e. container contents.

	@see Position
 */
 public:    virtual PositionEnumeration *getEnumeration() const = 0;

 /**
	Returns iterator of all positions within this
	container. I.e. container contents.

	@see Position
 */
 public:    virtual Iterator    *getIterator() const = 0;

 /**
	Returns enumeration of all values within container.
 */
 public:    virtual Enumeration *getValueEnumeration() const = 0;

 /**
	Returns iterator of all values within container.
 */
 public:    virtual Iterator    *getValueIterator() const = 0;

 /**
	Returns number of slots within container.

	NOTE: This is not the same as number of values
	when null values allowed by structure. E.g., array
	with uninitialised elements.
 */
 public:    virtual Index        getCardinality() const = 0;

 /**
	Checks this container for presence of element equal
	(in sense of Top::equals()) to given object.
 */
 public:    virtual boolean contains( const Top *anElement ) const = 0;

 /**
	Searches this container for the given object
	and returns position of the corresponding slot.

	Returns nil if no object found.
 */
 public:    virtual Position *find( const Top *anObject ) const = 0;

 /**
	Checks that given position belongs to this container
	and is valid (i.e., slot was not deleted etc.)
 */
 public:    virtual boolean   isValid ( const Position *aPosition ) const = 0;
 
 /**
	Returns value in slot of given position.
	@precond ( isValid( aPosition ) )
 */
 public:    virtual Top   *getValue( const Position *aPosition ) = 0;

 /**
	Returns this container as map from
	positions to values.
 */
 public:    virtual Map *getAsMap() const = 0;
};

END_QR_NAMESPACE

/*
 * $Log: Container.hpp,v $
 * Revision 1.1.1.1  2000/07/19 16:58:54  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:33  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:44  god
 * Imported sources
 *
 * Revision 1.3  1999/03/03 19:09:08  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.2  1999/02/28 12:51:59  philogelos
 * Comments cleared and sub-typed from Top
 *
 * Revision 1.1.1.1  1998/11/25 20:11:05  philogelos
 * Quercus Robusta
 *
 * Revision 1.4  1998/07/09 09:04:43  philogelos
 * custom new/delete added
 *
 * Revision 1.3  1998/07/07 14:29:51  philogelos
 * Memory leak in SUNWspro dynamic_cast fixed.
 *
 * Revision 1.2  1998/06/22 18:12:57  philogelos
 * Enumerations and containers added
 *
 * Revision 1.1.1.1  1998/06/22 08:47:11  philogelos
 * First version under CVS
 *
 * Revision 1.1.1.1  1998/04/01 17:15:30  philogelos
 * first version under CVS
 * */

/* __CONTAINER_HPP__ */
#endif
