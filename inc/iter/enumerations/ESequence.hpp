// -*-C++-*- 

/*  inc/iter/enumerations/ESequence.hpp  */


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


#ifndef __ESEQUENCE_HPP__
#define __ESEQUENCE_HPP__

/* $Id: ESequence.hpp,v 1.1.1.1 2000/07/19 17:02:15 philogelos Exp $ */

#include "TypedEnumeration.hpp"
#include "ResettableEnumeration.hpp"
#include "defines.h"

BEGIN_QR_NAMESPACE



/**
   Sequence whose elements are sequences.

   @author Philogelos
   @created Втр 29 Сен 1998 20:29:16
*/
abstract class ESequence : public Enumeration //ResettableEnumeration
{
  /**
	 Returns next enumeration in this sequence.

	 @see #getNextElement
  */
public: virtual Enumeration *getNextEnumeration() = 0;

  //public: virtual void reset() = 0;
  /**
	 Returns next element in this sequence.

	 This actually is call to ::getNextEnumeration()

	 @see #getNextEnumeration
  */
protected: virtual Top *getNextElement();

  /**
	 Creates instance from typed enumeration.
  */
public: static ESequence *createFrom( TypedEnumeration< Enumeration > *anEnum );

};

class ESFromTyped : public ESequence, 
					virtual public Object
{
public: ESFromTyped( TypedEnumeration< Enumeration > *anEnum );
public: ~ESFromTyped();

public: Enumeration *getNextEnumeration();
public: virtual boolean hasMoreElements();

public:  virtual String  getClassName() const;
public:  virtual Top    *clone() const;
  
protected: TypedEnumeration< Enumeration > *enumeration;
};

END_QR_NAMESPACE

/*
 * $Log: ESequence.hpp,v $
 * Revision 1.1.1.1  2000/07/19 17:02:15  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:35  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:39  god
 * Imported sources
 *
 * Revision 1.2  1999/03/03 19:09:19  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.1.1.1  1998/11/25 20:11:07  philogelos
 * Quercus Robusta
 * */

/* __ESEQUENCE_HPP__ */
#endif
