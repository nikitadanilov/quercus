// -*-C++-*- 

/*  inc/containers/LayeredPosition.hpp  */

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



#ifndef __LAYEREDPOSITION_HPP__
#define __LAYEREDPOSITION_HPP__

/* $Id: LayeredPosition.hpp,v 1.1.1.1 2000/07/19 16:59:29 philogelos Exp $ */

#include "PositionAdapter.hpp"
#include "defines.h"

BEGIN_QR_NAMESPACE

class Container;

/**

   @author Philogelos
   @created
*/
class LayeredPosition : virtual public PositionAdapter
{

  /**
   */
public: LayeredPosition( Container *aHost, Position *aBasePosition );

  /**
   */
public: virtual ~LayeredPosition();

public: virtual boolean isValid() const;
public:  virtual Top *getValue() const;

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
public:  virtual String  getClassName() const;

protected: Container *host;
protected: Position  *position;
};

END_QR_NAMESPACE

/*
 * $Log: LayeredPosition.hpp,v $
 * Revision 1.1.1.1  2000/07/19 16:59:29  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:33  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:45  god
 * Imported sources
*/

/* __LAYEREDPOSITION_HPP__ */
#endif
