#ifndef __REFCOUNTABLE_HPP__

/*  inc/RefCountable.hpp  */


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



#define __REFCOUNTABLE_HPP__
/* $Id: RefCountable.hpp,v 1.1.1.1 2000/07/19 16:57:18 philogelos Exp $ */

#include "defines.h"
#include "Top.hpp"

BEGIN_QR_NAMESPACE



/** 
	Interface for objects supporting garbage collecting
	through reference counting.

	@see Top
	@see RefCounted
	@author Philogelos
	@created «‚“ 18 ∏Ó› 1998 18:10:57
*/
interface RefCountable : public virtual Top
{
public:  virtual void addRef() const = 0;
public:  virtual void delRef() const = 0;
public:  virtual boolean isRef() const = 0;
};
END_QR_NAMESPACE

/*
 * $Log: RefCountable.hpp,v $
 * Revision 1.1.1.1  2000/07/19 16:57:18  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:17  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:38  god
 * Imported sources
 *
 * Revision 1.2  1999/03/03 19:09:04  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.1.1.1  1998/11/25 20:11:04  philogelos
 * Quercus Robusta
 *
 * Revision 1.2  1998/07/07 14:29:48  philogelos
 * Memory leak in SUNWspro dynamic_cast fixed.
 *
 * Revision 1.1.1.1  1998/06/22 08:47:11  philogelos
 * First version under CVS
 *
 * Revision 1.1.1.1  1998/04/01 17:15:30  philogelos
 * first version under CVS
 * */

/* __REFCOUNTABLE_HPP__ */
#endif
