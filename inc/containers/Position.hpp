// -*-C++-*- 

/*  inc/containers/Position.hpp  */


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


#ifndef __POSITION_HPP__
#define __POSITION_HPP__

/* $Id: Position.hpp,v 1.1.1.1 2000/07/19 16:59:43 philogelos Exp $ */

#include "Object.hpp"
#include "defines.h"

BEGIN_QR_NAMESPACE

interface Container;
interface MutablePosition;


/**
   Interface for positions within containers.
   Position is link between slot in given container
   to value of this slot.
   
   Positions can be either mutable or immutable (normal).
   Mutable positions provide for modification of the
   value of their slot.

   @see Container

   @author Philogelos
   @created ≤‚‡ 23 ∏Ó› 1998 17:47:55
*/
interface Position : virtual public Top
{
  /**
	 Checks that position is still valid
	 within host container.
  */
 public:  virtual boolean   isValid () const = 0;

  /**
	 Returns value located at this position in
	 the host container.
	*/
 public:  virtual Top *getValue() const = 0;

 /**
	Returns host container.
 */
 public:  virtual Container *getContainer() const = 0;

};

END_QR_NAMESPACE

/*
 * $Log: Position.hpp,v $
 * Revision 1.1.1.1  2000/07/19 16:59:43  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:33  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:44  god
 * Imported sources
 *
 * Revision 1.3  1999/03/03 19:09:11  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.2  1999/02/28 12:58:42  philogelos
 * Sub-typed from Top
 *
 * Revision 1.1.1.1  1998/11/25 20:11:05  philogelos
 * Quercus Robusta
 *
 * Revision 1.1  1998/07/07 14:29:52  philogelos
 * Memory leak in SUNWspro dynamic_cast fixed.
 * */

/* __POSITION_HPP__ */
#endif
