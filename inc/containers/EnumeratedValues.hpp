// -*-C++-*- 

/*  inc/containers/EnumeratedValues.hpp  */


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


#ifndef __ENUMERATEDVALUES_HPP__
#define __ENUMERATEDVALUES_HPP__

/* $Id: EnumeratedValues.hpp,v 1.1.1.1 2000/07/19 16:59:21 philogelos Exp $ */

#include "PositionEnumeration.hpp"
#include "ContainerAdapter.hpp"
#include "Object.hpp"
#include "defines.h"
#include "CRef.hpp"

BEGIN_QR_NAMESPACE

interface Enumeration;
interface ResettableEnumeration;

/**
   Container whose values are elements of given 
   resettable sequence.

   @author Philogelos
   @created Птн 25 Сен 1998 12:23:59
*/
class EnumeratedValues : public ContainerAdapter
{

  /**
	 Creates instance with elements of the given sequence as
	 values.
  */
public: EnumeratedValues( ResettableEnumeration *anEnum );

  /**
	*/
public: virtual ~EnumeratedValues();

public: virtual PositionEnumeration *getEnumeration() const;

  /**
	 Returns clone of the base sequence.
  */
public: virtual Enumeration *getValueEnumeration() const;

public: virtual Top *getValue( const Position * aPosition );

  /**
	*/
public:  virtual Top *clone() const;

  /**
	*/
public:  virtual String  getClassName() const;

protected: CRef< ResettableEnumeration > valuesEnumeration;

public: class FrozenValues : public PositionEnumeration,
  virtual public Object
  {
    public: FrozenValues( Container *aContainer, Enumeration *anEnum );
    public: ~FrozenValues();
    public: virtual Position *getNextPosition();
    public: virtual boolean hasMoreElements();
    public: virtual String  getClassName() const;

    protected:  CRef< Container >  container;
    protected:  CRef< Enumeration > enumeration;
  };
};

END_QR_NAMESPACE

/*
 * $Log: EnumeratedValues.hpp,v $
 * Revision 1.1.1.1  2000/07/19 16:59:21  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.4  2000/04/09 12:00:47  god
 * CVS Log keyword correction finished
 *
 * Revision 1.3  2000/04/09 11:29:33  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.2  2000/04/06 13:25:20  god
 * converted to CRefs<>
 *
 * Revision 1.1.1.1  2000/04/01 14:07:44  god
 * Imported sources
 *
 * Revision 1.3  1999/03/03 19:09:09  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.2  1999/02/28 12:53:17  philogelos
 * *** empty log message ***
 *
 * Revision 1.1.1.1  1998/11/25 20:11:06  philogelos
 * Quercus Robusta
 * */

/* __ENUMERATEDVALUES_HPP__ */
#endif
