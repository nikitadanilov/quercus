// -*-C++-*- 

/*  inc/ObjectWrapper.hpp  */

/*
 * Author: Philogelos A. <Philogelos@yahoo.com>
 * Maintainer: Philogelos A.
 * Keywords: C++, library, containers
 *
 * Copyright (C) 1999 Philogelos A.
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



#ifndef __OBJECTWRAPPER_HPP__
#define __OBJECTWRAPPER_HPP__

/* $Id: ObjectWrapper.hpp,v 1.1.1.1 2000/07/19 16:57:03 philogelos Exp $ */

#include "Object.hpp"
#include "defines.h"

#define OW( obj ) ( ( Top * ) new ObjectWrapper( ( Top * ) ( obj ) ) )

BEGIN_QR_NAMESPACE

/**

   @author Philogelos
   @created
*/
class ObjectWrapper : public virtual Object
{

  /**
   */
public: ObjectWrapper( Top *aValue );

  /**
   */
public: virtual ~ObjectWrapper();

public: Top *getValue() const;
public: void setValue( Top *aValue );

  /**
   */
public:  virtual boolean equals( const Top *anOther ) const;

  /**
   */
public:  virtual Top *clone() const;

  /**
   */
public:  virtual String  toString() const;

  /**
   */
public:  virtual String  getString() const;

  /**
   */
public:  virtual String  getClassName() const;

protected: Top *value;
};

END_QR_NAMESPACE

/*
 * $Log: ObjectWrapper.hpp,v $
 * Revision 1.1.1.1  2000/07/19 16:57:03  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:17  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:39  god
 * Imported sources
*/

/* __OBJECTWRAPPER_HPP__ */
#endif
