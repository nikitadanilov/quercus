// -*-C++-*- 

/*  inc/containers/MutableContainer.hpp  */


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


#ifndef __MUTABLECONTAINER_HPP__
#define __MUTABLECONTAINER_HPP__

/* $Id: MutableContainer.hpp,v 1.1.1.1 2000/07/19 16:59:37 philogelos Exp $ */

#include "Container.hpp"
#include "defines.h"

BEGIN_QR_NAMESPACE

interface MutablePosition;
interface MutablePositionEnumeration;

/**

   @author Philogelos
   @created Срд 23 Сен 1998 19:40:56
*/
interface MutableContainer : public virtual Container
{

 /**
	Returns enumeration of all mutable positions within this
	container.

	@see Position
 */
 public: virtual MutablePositionEnumeration *getMutableEnumeration() const = 0;

 /**
	Returns iterator of all mutable positions within this
	container. I.e. container contents.

	@see Position
 */
 public:    virtual Iterator    *getMutableIterator() const = 0;

 /**
	Sets value in slot of given mutable position.
	@precond ( isValid( aPosition ) )
 */
 public:    virtual Top   *setValue( MutablePosition *aPosition, Top *aNewValue ) = 0;
};

END_QR_NAMESPACE

/*
 * $Log: MutableContainer.hpp,v $
 * Revision 1.1.1.1  2000/07/19 16:59:37  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:33  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:44  god
 * Imported sources
 *
 * Revision 1.3  1999/03/03 19:09:10  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.2  1999/02/28 12:56:51  philogelos
 * *** empty log message ***
 *
 * Revision 1.1.1.1  1998/11/25 20:11:06  philogelos
 * Quercus Robusta
 * */

/* __MUTABLECONTAINER_HPP__ */
#endif
