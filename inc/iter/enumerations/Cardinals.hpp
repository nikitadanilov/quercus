// -*- C++ -*-

/*  inc/iter/enumerations/Cardinals.hpp  */


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



#ifndef __CARDINALS_HPP__
#define __CARDINALS_HPP__

/* $Id: Cardinals.hpp,v 1.1.1.1 2000/07/19 17:02:15 philogelos Exp $ */

#include "Enumeration.hpp"
#include "ResettableEnumeration.hpp"

#include "Object.hpp"

BEGIN_QR_NAMESPACE



/**
   Enumeration whose elements are all natural
   (cardinal) numbers. As a whole it exists 
   only in potentia.

   @author Philogelos
   @created
*/
class Cardinals : public ResettableEnumeration,
						 virtual public Object
{
public: Cardinals();
public: virtual ~Cardinals();

  /**
	 Always returns true.
  */
public: virtual boolean hasMoreElements();
  
  /**
	 Returns next number wrapped into Integer object.

	 @see Integer
  */
public: virtual Top *getNextElement();

  /**
	 Resets sequence back to 0.
  */
public: virtual void reset();

public: virtual Top *clone() const;

protected: Index counter;
};

END_QR_NAMESPACE

/*
 * $Log: Cardinals.hpp,v $
 * Revision 1.1.1.1  2000/07/19 17:02:15  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:35  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:39  god
 * Imported sources
 *
 * Revision 1.2  1999/03/03 19:09:18  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.1  1999/02/28 16:28:42  philogelos
 * Tuned for inlines.
 * */

/* __CARDINALS_HPP__ */
#endif
