// -*-C++-*- 

/*  inc/iter/enumerations/LookAheadEnumeration.hpp  */

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



#ifndef __LOOKAHEADENUMERATION_HPP__
#define __LOOKAHEADENUMERATION_HPP__

/* $Id: LookAheadEnumeration.hpp,v 1.1 2000/09/21 18:22:55 philogelos Exp $ */

#include "Enumeration.hpp"
#include "Object.hpp"
#include "defines.h"
#include "CRef.hpp"

BEGIN_QR_NAMESPACE

class List;
class NoEntity;

typedef Top LAAnchor;

/**

   @author Philogelos
   @created Fri Sep  8 19:12:36 2000
*/
class LookAheadEnumeration : public virtual Enumeration,
							 public virtual Object
{

  /**
   */
public: LookAheadEnumeration( Enumeration *aBase );
  
  /**
   */
public: virtual ~LookAheadEnumeration();


public: virtual LAAnchor *push();
public: virtual void pop( LAAnchor *anAnchor ) THROWS( NoEntity * );
public: virtual void rollTo( LAAnchor *anAnchor ) THROWS( NoEntity * );

public: virtual boolean hasMoreElements();
public: virtual Top *getNextElement();

  /**
   */
public:  virtual String  toString() const;

  /**
   */
public:  virtual String  getClassName() const;
public:  virtual boolean invariant() const;

protected: static Index getIndex( LAAnchor *anAnchor );
protected: Index getCarIndex() const;

protected: CRef< Enumeration > base;
  /** List of cached objects.
	  Current element will be returned on the next read.
  */
protected: CRef< List >  buffer;
protected: CRef< List >  anchors;
protected: Index         bufferStartOffset;
};

END_QR_NAMESPACE

/*
 * $Log: LookAheadEnumeration.hpp,v $
 * Revision 1.1  2000/09/21 18:22:55  philogelos
 * Used by recursive parser
 *
 */

/* __LOOKAHEADENUMERATION_HPP__ */
#endif
