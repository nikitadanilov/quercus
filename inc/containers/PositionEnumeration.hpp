// -*-C++-*- 

/*  inc/containers/PositionEnumeration.hpp  */


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


#ifndef __POSITIONENUMERATION_HPP__
#define __POSITIONENUMERATION_HPP__

/* $Id: PositionEnumeration.hpp,v 1.1.1.1 2000/07/19 16:59:43 philogelos Exp $ */

#include "iter/enumerations/TypedEnumeration.hpp"
#include "iter/enumerations/ResettableEnumeration.hpp"
#include "containers/Position.hpp"

BEGIN_QR_NAMESPACE

interface Position;

/**
   Sequences of positions (within container).

   @see Position
   #see Container

   @author Philogelos
   @created Чтв 10 Сен 1998 18:55:46
*/
abstract class PositionEnumeration : virtual public Enumeration
{
  /**
	 No-op destructor.
  */
public: virtual ~PositionEnumeration();

  /**
	 Returns next position in this sequence.

	 @see #getNextElement
  */
public:    virtual Position *getNextPosition() = 0;

  /**
	 Returns next element in this sequence.
	 
	 If all C++ implementations were provide for
	 covariant return type adjustment one would
	 just override this to return Position.

	 This actually is call to ::getNextPosition()

	 @see #getNextPosition
  */
protected: virtual Top *getNextElement();

public: static PositionEnumeration *createFrom( TypedEnumeration< Position > *anEnum );

};

class PEFromTyped : public PositionEnumeration, virtual public Object
{
public: PEFromTyped( TypedEnumeration< Position > *anEnum );
public: ~PEFromTyped();
public: Position *getNextPosition();
public: virtual boolean hasMoreElements();

public:  virtual String  getClassName() const;
public:  virtual Top    *clone() const;
  
protected: TypedEnumeration< Position > *enumeration;
};

END_QR_NAMESPACE

/*
 * $Log: PositionEnumeration.hpp,v $
 * Revision 1.1.1.1  2000/07/19 16:59:43  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:33  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:45  god
 * Imported sources
 *
 * Revision 1.3  1999/03/03 19:09:11  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.2  1999/02/28 13:00:16  philogelos
 * Inheritance virtualised
 *
 * Revision 1.1.1.1  1998/11/25 20:11:05  philogelos
 * Quercus Robusta
 * */

/* __POSITIONENUMERATION_HPP__ */
#endif
