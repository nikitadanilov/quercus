// -*-C++-*- 

/*  inc/containers/RangedContainer.hpp  */


/*
 * Author: Philogelos A. <Philogelos@yahoo.com>
 * Maintainer: Philogelos A.
 * Keywords: C++, library, containers
 *
 * Copyright (C) 1998, 1999 Philogelos A.
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


#ifndef __RANGEDCONTAINER_HPP__
#define __RANGEDCONTAINER_HPP__

/* $Id: RangedContainer.hpp,v 1.1.1.1 2000/07/19 16:59:52 philogelos Exp $ */

#include "IndexableContainer.hpp"
#include "MutablePosition.hpp"
#include "PositionAdapter.hpp"
#include "MutablePositionAdapter.hpp"
#include "Map.hpp"
#include "defines.h"



BEGIN_QR_NAMESPACE

class RangedContainerEnumeration;

/**
   Flavour of IndexableContainer
   with the range [ n .. m ) as 
   the domain of the mapping.

   @author Philogelos
   @created ≤‚‡ 30 ∏Ó› 1998 15:58:13
*/
abstract class RangedContainer : public virtual IndexableContainer
{
public: virtual Index getLowBound() const = 0;
public: virtual Index getHighBound() const = 0;

public: virtual boolean isValidIndex( const Index anIndex ) const;

public: virtual RangedContainerEnumeration *getRangedEnumeration() const;

public: virtual Index findIndex( const Top *anObject ) const;

public: virtual IndexPosition *getFirstPosition() const;
public: virtual IndexPosition *getLastPosition() const;
public: virtual MutablePosition *getAlwaysFirstPosition() const;
public: virtual MutablePosition *getAlwaysLastPosition() const;

public: virtual PositionEnumeration *getEnumeration() const;
public: virtual MutablePositionEnumeration *getMutableEnumeration() const;
public: virtual Index getCardinality() const;

public: class BeyondRange : public IndexableContainer::InvalidIndex
{
public:  BeyondRange( String aMessage, const Top *const aSource );
public:  virtual String  getDescription() const;
public:  virtual String  getClassName() const;
};

public: class AfterLast : public BeyondRange
{
public:  AfterLast( String aMessage, const Top *const aSource );
public:  virtual String  getDescription() const;
public:  virtual String  getClassName() const;
};

public: class BeforeFirst : public BeyondRange
{
public:  BeforeFirst( String aMessage, const Top *const aSource );
public:  virtual String  getDescription() const;
public:  virtual String  getClassName() const;
};

public: abstract class RContainerFirstPosition : public MutablePositionAdapter,
		public virtual Object
{
public: RContainerFirstPosition( const RangedContainer *aContainer );
public: ~RContainerFirstPosition();

public: virtual Top *setValue( Top *aNewValue );

public:  virtual boolean isValid () const;
public:  virtual Top *getValue() const;

};

public: abstract class RContainerLastPosition : public MutablePositionAdapter,
		public virtual Object
{
public: RContainerLastPosition( const RangedContainer *aContainer );
public: ~RContainerLastPosition();

public: virtual Top *setValue( Top *aNewValue );

public:  virtual boolean isValid () const;
public:  virtual Top *getValue() const;
};

};

END_QR_NAMESPACE

/*
 * $Log: RangedContainer.hpp,v $
 * Revision 1.1.1.1  2000/07/19 16:59:52  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:34  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:45  god
 * Imported sources
 *
 * Revision 1.3  1999/03/03 19:09:12  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.2  1999/02/28 13:01:39  philogelos
 * Inheritance from Object
 *
 * Revision 1.1.1.1  1998/11/25 20:11:05  philogelos
 * Quercus Robusta
 *
 * Revision 1.1  1998/07/09 09:30:31  philogelos
 * new files added to the repository
 * */

/* __RANGEDCONTAINER_HPP__ */
#endif
