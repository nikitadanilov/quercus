// -*-C++-*- 

/*  inc/containers/Set.hpp  */


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


#ifndef __SET_HPP__
#define __SET_HPP__

/* $Id: Set.hpp,v 1.1.1.1 2000/07/19 17:00:10 philogelos Exp $ */

#include "containers/RemovablePosition.hpp"
#include "containers/EmptyContainer.hpp"
#include "MutableContainer.hpp"
#include "MutableContainerAdapter.hpp"
#include "ModifiableContainer.hpp"
#include "PositionFactory.hpp"
#include "Map.hpp"
#include "defines.h"

BEGIN_QR_NAMESPACE

class List;
class SetPosition;
class SetPositionFactory;

/**
   Set: collection of object (elements)
   different w.r.t. ::equal()

   @author Philogelos
   @created ¡‡‘ 07 æ⁄‚ 1998 12:56:41 // THAT Day
*/
class Set : public virtual MutableContainerAdapter,
			public ModifiableContainer
{

  friend SetPositionFactory;
  friend SetPosition;

  /**
	 Creates empty set.
  */
public: Set();

  /**
	 Destroys this object,
	 freeing all elements.
  */
public: virtual ~Set();

  /**
	 Returns sequence containing all removable slots.
	 All positions are removable.
  */
public: virtual TypedEnumeration< RemovablePosition > *getRemovable() const;
public: virtual MutablePositionEnumeration *getMutableEnumeration() const;
public: virtual Top   *setValue( MutablePosition *aPosition, Top *aNewValue );
public: virtual Top   *getValue( const Position *aPosition );

public: virtual PositionFactory *getDefaultPositionFactory() const;

public: virtual void add( const Top *anObject );
public: virtual Top *getAny() const THROWS( EmptyContainer * );
public: virtual Top *getAndRemove() const;

public: virtual boolean isEmpty() const;
public: virtual Index   getCardinality() const;

  /**
	*/
public:  virtual Top *clone() const;

  /**
	*/
public:  virtual String  getClassName() const;

protected: Set( List *aCore );
protected: Position  *unify( const Top *anObject ) const;
protected: MutablePosition  *getNew( const Top *anObject ) const;
protected: List *getCore() const;

#if defined( TESTING )
public: virtual boolean tester( int aParam ) const;
#endif

protected: List *core;
};

class SetPositionFactory : public PositionFactory,
						   public virtual Object
{
public: SetPositionFactory( Set *aSet );
public: ~SetPositionFactory();
public: virtual MutablePosition *createPosition();

protected: Set *set;
};

class SetPosition : public MutablePosition, 
					public virtual RemovablePosition,
					public virtual PositionAdapter
{
public: SetPosition( Set *aContainer );
public: virtual ~SetPosition();
public: void setCore( MutablePosition *aCorePosition );
public: virtual boolean   isValid () const;
public: virtual Top *setValue( Top *aNewValue );
public: virtual Top *getValue() const;
public: virtual String  getClassName() const;
public: Set *getSet() const;

public: virtual void remove();

protected: MutablePosition *corePosition;
};

class SetPositionMap : public Map,
					   virtual public Object
{
public: SetPositionMap( Set *aSet );
public: virtual ~SetPositionMap();

public: virtual Top *apply( Top *anArg );

protected: Set *set;
};

END_QR_NAMESPACE

/*
 * $Log: Set.hpp,v $
 * Revision 1.1.1.1  2000/07/19 17:00:10  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:34  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:44  god
 * Imported sources
 *
 * Revision 1.3  1999/03/03 19:09:12  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.2  1999/02/28 13:03:32  philogelos
 * Finished and tested
 *
 * Revision 1.1.1.1  1998/11/25 20:11:06  philogelos
 * Quercus Robusta
 * */

/* __SET_HPP__ */
#endif
