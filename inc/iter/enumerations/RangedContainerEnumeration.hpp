// -*-C++-*- 

/*  inc/iter/enumerations/RangedContainerEnumeration.hpp  */


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


#ifndef __RANGEDCONTAINERENUMERATION_HPP__
#define __RANGEDCONTAINERENUMERATION_HPP__

/* $Id: RangedContainerEnumeration.hpp,v 1.1.1.1 2000/07/19 17:02:15 philogelos Exp $ */

#include "Enumeration.hpp"
#include "ECursor.hpp"
#include "Object.hpp"
#include "containers/RangedContainer.hpp"
#include "containers/MutablePositionEnumeration.hpp"
#include "defines.h"

BEGIN_QR_NAMESPACE



/**
   Enumeration of elements within RangedContainer

   @author Philogelos
   @created ≤‚‡ 30 ∏Ó› 1998 16:39:00
*/
class RangedContainerEnumeration : public MutablePositionEnumeration,
								   public ECursor,
								   virtual public Object
{

  /**
	*/
public: RangedContainerEnumeration( RangedContainer *aHost );

  /**
	*/
public: virtual ~RangedContainerEnumeration();

public: virtual Top *getPrevElement();
public: virtual void reset();
public: virtual void ff();
public: virtual boolean isAtBeginning();

public: virtual boolean hasMoreElements();
public: virtual Top *getNextElement();

public: virtual MutablePosition *getNextMutablePosition();

  /**
	*/
public:  virtual Top *clone() const;

  /**
	*/
public:  virtual String  getString() const;

  /**
	*/
public:  virtual String  getClassName() const;

protected: RangedContainer *host;

protected: Index position;
};

END_QR_NAMESPACE

/*
 * $Log: RangedContainerEnumeration.hpp,v $
 * Revision 1.1.1.1  2000/07/19 17:02:15  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:35  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:40  god
 * Imported sources
 *
 * Revision 1.2  1999/03/03 19:09:19  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.1.1.1  1998/11/25 20:11:07  philogelos
 * Quercus Robusta
 *
 * Revision 1.1  1998/07/09 09:30:35  philogelos
 * new files added to the repository
 * */

/* __RANGEDCONTAINERENUMERATION_HPP__ */
#endif
