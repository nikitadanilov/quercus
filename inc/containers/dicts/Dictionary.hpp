// -*-C++-*- 

/*  inc/containers/Dictionary.hpp  */


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



#ifndef __DICTIONARY_HPP__
#define __DICTIONARY_HPP__

/* $Id: Dictionary.hpp,v 1.1.1.1 2000/07/19 17:00:18 philogelos Exp $ */

#include "containers/ModifiableContainer.hpp"
#include "containers/MutableContainer.hpp"
#include "containers/PositionFactory.hpp"
#include "Integer.hpp"
#include "Map.hpp"
#include "defines.h"

BEGIN_QR_NAMESPACE

typedef Top DictKey;

/**
   Container storing values associated with keys.

   @author Philogelos
   @created
*/
abstract class Dictionary : public ModifiableContainer,
							public MutableContainer
{
  /**
	 True is there is such key in this container.
   */
public: virtual boolean isSuchKey( const DictKey *aKey ) const = 0;

  /**
	 Returns enumeration of all keys in this
	 dictionary.
  */
public: virtual Enumeration *getKeyEnumeration() const = 0;

  /**
	 Associates given value with given key and
	 returns old value.

	 @precond isSuchKey( aKey )
  */
public: virtual Top *setValueAtKey( const DictKey *aKey, Top *aValue ) = 0;

  /**
	 Returns value associated with given key.

	 @precond isSuchKey( aKey )
  */
public: virtual Top *getValueAtKey( const DictKey *aKey ) const = 0;

  /**
	 Adds given key to this container and associates
	 given value with it.

	 @precond !isSuchKey( aKey )
  */
public: virtual void addKey( const DictKey *aKey, Top *aValue ) = 0;

  /**
	 Removes given key from this dictionary.

	 @precond isSuchKey( aKey )
  */
public: virtual Top *removeKey( const DictKey *aKey ) = 0;
};


/**
   Helper class converting object conforming
   to Dictionary interface to Map.
*/
class DictPositionMap : public Map,
						virtual public Object
{
  /**
	 Creates map object mapping keys to values
	 as defined by given dictionary.
  */
public: DictPositionMap( Dictionary *aDict );
public: virtual ~DictPositionMap();

  /**
	 Returns object conforming to the
	 MutablePosition interface (actually DictKeyPosition).
	 It is position within dictionary associated with this
	 object and pointing to the slot keyed to anArg.
	 This will not throw exception if key is invalid.
	 Rather exception will be thrown later on attempt
	 to call ::getValue() or ::setValue() on result.

	 @see MutablePosition
	 @see DictKeyPosition
	 @see Position::getValue()
	 @see MutablePosition::setValue()
  */
public: virtual Top *apply( Top *anArg );

protected: Dictionary *dict;
};

class DictPositionFactory : public PositionFactory,
							virtual public Object
{
public: DictPositionFactory( Dictionary *aDict );
public: virtual ~DictPositionFactory();

public: virtual MutablePosition *createPosition();

protected: Dictionary *dict;
protected: Integer *count;
};

END_QR_NAMESPACE

/*
 * $Log: Dictionary.hpp,v $
 * Revision 1.1.1.1  2000/07/19 17:00:18  philogelos
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
 * Revision 1.1  1999/02/28 15:35:09  philogelos
 * Dictionaries added and tested
 * */

/* __DICTIONARY_HPP__ */
#endif
