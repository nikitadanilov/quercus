// -*-C++-*- 

/*  inc/containers/dict/DumbDictionary.hpp  */


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



#ifndef __DUMBDICTIONARY_HPP__
#define __DUMBDICTIONARY_HPP__

/* $Id: DumbDictionary.hpp,v 1.1.1.1 2000/07/19 17:00:22 philogelos Exp $ */

#include "containers/MutableContainerAdapter.hpp"
#include "Dictionary.hpp"
#include "defines.h"

BEGIN_QR_NAMESPACE

class DictKeyPosition;
class List;
class Pair;

/**
   Default (and stupid) implementation of Dictionary interface.

   @author Philogelos
   @created
*/
class DumbDictionary :  public ContainerAdapter, /* if I put MutableContainerAdapter in stead */
						public Dictionary        /* XXX egcs bails out with 
													``Internal compiler error 369'' */
{
public: DumbDictionary();

public: virtual ~DumbDictionary();

  /**
	 Returns enumeration of keys of this dictionary.
  */
public: virtual Enumeration *getKeys() const;

  /**
	 Returns enumeration of values of this dictionary.
  */
public: virtual Enumeration *getValues() const;

public: virtual boolean isSuchKey( const DictKey *aKey ) const;
public: virtual Enumeration *getKeyEnumeration() const;
public: virtual Top *setValueAtKey( const DictKey *aKey, Top *aValue );
public: virtual Top *getValueAtKey( const DictKey *aKey ) const;
public: virtual void addKey( const DictKey *aKey, Top *aValue );
public: virtual Top *removeKey( const DictKey *aKey );

public: virtual Top *getValue( const Position *aPosition );
public: virtual Top *setValue( MutablePosition *aPosition, Top *aNewValue );

public: virtual Index                getCardinality() const;

public: virtual PositionFactory *getDefaultPositionFactory() const;

public: virtual PositionEnumeration *getEnumeration() const;
public: virtual Enumeration *getValueEnumeration() const;
public: virtual Iterator    *getMutableIterator() const;
public: virtual MutablePositionEnumeration *getMutableEnumeration() const;

  /**
	 Returns sequence containing all removable slots.
	 All positions associated with keys are removable.
  */
public: virtual TypedEnumeration< RemovablePosition > *getRemovable() const;


public:  virtual Top *clone() const;

public:  virtual String  getClassName() const;

#if defined( TESTING )
public:  virtual boolean tester( int aParam ) const;
#endif

protected: DumbDictionary( List *aConses );

protected: List *getConses() const;
protected: Pair *getConsAt( const Index anIndex ) const;
protected: Index getIndexOf( const DictKey *aKey ) const;
protected: Pair *getConsOf( const DictKey *aKey ) const;

protected: List *conses;
};

END_QR_NAMESPACE

/*
 * $Log: DumbDictionary.hpp,v $
 * Revision 1.1.1.1  2000/07/19 17:00:22  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:34  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:45  god
 * Imported sources
 *
 * Revision 1.2  1999/03/03 19:09:14  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.1  1999/02/28 15:35:10  philogelos
 * Dictionaries added and tested
 * */

/* __DUMBDICTIONARY_HPP__ */
#endif


