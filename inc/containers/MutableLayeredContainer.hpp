// -*-C++-*- 

/*  inc/containers/MutableLayeredContainer.hpp  */

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



#ifndef __MUTABLELAYEREDCONTAINER_HPP__
#define __MUTABLELAYEREDCONTAINER_HPP__

/* $Id: MutableLayeredContainer.hpp,v 1.1.1.1 2000/07/19 16:59:37 philogelos Exp $ */

#include "MutablePositionEnumeration.hpp"
#include "MutableContainerAdapter.hpp"
#include "LayeredContainer.hpp"
#include "defines.h"

BEGIN_QR_NAMESPACE

class MutableLayeredEnumeration;

/**

   @author Philogelos
   @created
*/
abstract class MutableLayeredContainer : public LayeredContainer,
										 virtual public MutableContainerAdapter
{
  friend MutableLayeredEnumeration;

public: virtual MutablePositionEnumeration *getMutableEnumeration() const;

protected: virtual Container *getBaseContainer() const;
protected: virtual MutableContainer *getBaseMutableContainer() const = 0;
protected: virtual MutablePosition  *createMutableFromBase( MutablePosition *aBasePosition );

public: virtual boolean isEmpty() const;
public: virtual PositionEnumeration *getEnumeration() const;
public: virtual Index getCardinality() const;

};

class MutableLayeredEnumeration : public MutablePositionEnumeration,
								  public virtual Object
{
public: MutableLayeredEnumeration( MutableLayeredContainer *aContainer );
public: virtual ~MutableLayeredEnumeration();

public: virtual MutablePosition *getNextMutablePosition();
public: virtual boolean hasMoreElements();

protected: MutablePositionEnumeration *baseEnum;
protected: MutableLayeredContainer *baseContainer;
};

END_QR_NAMESPACE

/*
 * $Log: MutableLayeredContainer.hpp,v $
 * Revision 1.1.1.1  2000/07/19 16:59:37  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:33  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:44  god
 * Imported sources
 *
 * Revision 1.2  1999/03/03 19:09:10  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.1  1999/02/28 13:04:33  philogelos
 * Added Files:
 * 	EmptyContainer.hpp EmptyStack.hpp LayeredContainer.hpp
 * 	MutableLayeredContainer.hpp PuncturedContainer.hpp Stack.hpp
 * 	TextContainer.hpp ValuePosition.hpp
 * Removed Files:
 * 	Modifier.hpp
 * */

/* __MUTABLELAYEREDCONTAINER_HPP__ */
#endif
