// -*-C++-*-

/*  inc/exceptions/Throwable.hpp  */


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


#ifndef __THROWABLE_HPP__
#define __THROWABLE_HPP__

/* $Id: Throwable.hpp,v 1.1.1.1 2000/07/19 17:02:15 philogelos Exp $ */

#include "Object.hpp"
#include "Condition.hpp"

BEGIN_QR_NAMESPACE



/** 
	Interface for anything that can be thrown
	by throw statement (by convention of course).

	@see Exception
	@author Philogelos
	@created «‚“ 18 ∏Ó› 1998 20:12:27
*/
class Throwable : virtual public Object
{
  /** Default constructor.*/
protected:  Throwable();
public: virtual void announce();
};

END_QR_NAMESPACE

/*
 * $Log: Throwable.hpp,v $
 * Revision 1.1.1.1  2000/07/19 17:02:15  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:35  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:46  god
 * Imported sources
 *
 * Revision 1.3  1999/03/03 19:09:18  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.2  1999/02/28 15:37:29  philogelos
 * *** empty log message ***
 *
 * Revision 1.1.1.1  1998/11/25 20:11:06  philogelos
 * Quercus Robusta
 *
 * Revision 1.2  1998/07/07 14:29:54  philogelos
 * Memory leak in SUNWspro dynamic_cast fixed.
 *
 * Revision 1.1.1.1  1998/06/22 08:47:11  philogelos
 * First version under CVS
 *
 * Revision 1.1.1.1  1998/04/01 17:15:30  philogelos
 * first version under CVS
 * */

/* __THROWABLE_HPP__ */
#endif
