// -*- C++ -*-

/*  inc/containers/EnumeratedContainer.hpp  */


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



#ifndef __ENUMERATEDCONTAINER_HPP__
#define __ENUMERATEDCONTAINER_HPP__

/* $Id: EnumeratedContainer.hpp,v 1.1.1.1 2000/07/19 16:59:21 philogelos Exp $ */

#include "Object.hpp"
#include "containers/ContainerAdapter.hpp"

BEGIN_QR_NAMESPACE

interface Enumeration;
interface ResettableEnumeration;
interface PositionEnumeration;

/**
   Container containing elements from the
   given enumeration.

   @author Philogelos
   @created ø›‘ 22 ∏Ó› 1998 20:58:58
*/
class EnumeratedContainer : public ContainerAdapter
{
protected: EnumeratedContainer( PositionEnumeration *anEn );
protected: ~EnumeratedContainer();

  /**
	 Returns the clone of the given enumeration.
  */
public:    virtual PositionEnumeration *getEnumeration() const;
public:    virtual String       getClassName() const;

public:    virtual Top   *getValue( const Position *getPosition );

protected: PositionEnumeration *en;
};

END_QR_NAMESPACE

/*
 * $Log: EnumeratedContainer.hpp,v $
 * Revision 1.1.1.1  2000/07/19 16:59:21  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:33  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:44  god
 * Imported sources
 *
 * Revision 1.2  1999/03/03 19:09:09  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.1.1.1  1998/11/25 20:11:05  philogelos
 * Quercus Robusta
 *
 * Revision 1.1  1998/07/09 09:30:28  philogelos
 * new files added to the repository
 * */

/* __ENUMERATEDCONTAINER_HPP__ */
#endif
