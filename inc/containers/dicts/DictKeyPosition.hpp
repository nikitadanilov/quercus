// -*-C++-*- 

/*  inc/containers/dicts/DictKeyPosition.hpp */

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


#ifndef __DICTKEYPOSITION_HPP__
#define __DICTKEYPOSITION_HPP__

/* $Id: DictKeyPosition.hpp,v 1.1.1.1 2000/07/19 17:00:16 philogelos Exp $ */

#include "containers/MutablePositionAdapter.hpp"
#include "containers/RemovablePosition.hpp"
#include "containers/dicts/Dictionary.hpp"
#include "defines.h"



BEGIN_QR_NAMESPACE

/**
   Position within Dictionary object, denoting
   slot keyed to some particular key.

   @author Philogelos
   @created
*/
class DictKeyPosition : public MutablePositionAdapter,
						public virtual RemovablePosition
{

  /**
	 Creates position associated with given
	 Dictionary and null key.
   */
public: DictKeyPosition( Dictionary *aDict );

  /**
   */
public: virtual ~DictKeyPosition();

  /**
	 Sets key this object points to.
  */
public: virtual void setKey( DictKey *aKey );

  /**
	 Returns key used by this object.
  */
public: virtual DictKey *getKey() const;

  /**
	 Removes key associated with this position from dictionary.
  */
public: virtual void remove();

  /**
	 Returns dictionary this object works with.
  */
public: virtual Dictionary *getDictionary() const;


  /**
	 Sets value in the dictionary slot keyed to key.

	 @precond isValid()
  */
public: virtual Top *setValue( Top *aNewValue );

  /**
	 True if key exists within dictionary.
  */
public: virtual boolean   isValid () const;

  /**
	 Returns value keyed to key.

	 @precond isValid()
  */
public: virtual Top *getValue() const;

  /**
	 True iff argument conforms to the DictKeyPosition,
	 operates over the same container and either
	 both this object's and argument's key are null, or
	 are equal.
   */
public: virtual boolean equals( const Top *anOther ) const;

  /**
   */
public: virtual Top *clone() const;

  /**
   */
public:  virtual String  getClassName() const;

protected: DictKey *key;
};

END_QR_NAMESPACE

/*
 * $Log: DictKeyPosition.hpp,v $
 * Revision 1.1.1.1  2000/07/19 17:00:16  philogelos
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

/* __DICTKEYPOSITION_HPP__ */
#endif
