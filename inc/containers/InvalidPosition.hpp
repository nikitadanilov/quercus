// -*-C++-*- 

/*  inc/containers/InvalidPosition.hpp  */

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



#ifndef __INVALIDPOSITION_HPP__
#define __INVALIDPOSITION_HPP__

/* $Id: InvalidPosition.hpp,v 1.1.1.1 2000/07/19 16:59:23 philogelos Exp $ */

#include "PositionAdapter.hpp"
#include "defines.h"



BEGIN_QR_NAMESPACE

class InvalidArgument;

/**
   Invalid position. This position never correspond
   to slot in any container. For the sake of 
   completness.

   @author Philogelos
   @created
*/
class InvalidPosition : public PositionAdapter
{

  /**
   */
public: InvalidPosition( Container *aHost );

  /**
   */
public: virtual ~InvalidPosition();

  /**
	 Always false.
  */
public:  virtual boolean isValid() const;

  /**
	 Throws exception.
  */
public:  virtual Top *getValue() const THROWS( InvalidArgument * );

  /**
   */
public:  virtual Top *clone() const;

  /**
   */
public:  virtual boolean equals( const Top *anOther ) const;

  /**
   */
public:  virtual String  getClassName() const;
};

END_QR_NAMESPACE

/*
 * $Log: InvalidPosition.hpp,v $
 * Revision 1.1.1.1  2000/07/19 16:59:23  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:33  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:45  god
 * Imported sources
*/

/* __INVALIDPOSITION_HPP__ */
#endif
