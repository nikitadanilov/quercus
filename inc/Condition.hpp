// -*-C++-*- 

/*  inc/Condition.hpp  */


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


#ifndef __CONDITION_HPP__
#define __CONDITION_HPP__

/* $Id: Condition.hpp,v 1.1.1.1 2000/07/19 16:55:12 philogelos Exp $ */

#include "defines.h"
#include "Top.hpp"
#include "observe/Observable.hpp"

BEGIN_QR_NAMESPACE

/**
   Condition is an interesting sutiation 
   detected and announced.

   Most notable, conditions are used in the
   implementation of Publish/Subscribe pattern.

   @author Philogelos
   @created ø‚› 10 ∏Ó€ 1998 13:10:12
*/
interface Condition : virtual public Top
{
 public: virtual void announce() = 0;
};

END_QR_NAMESPACE

/*
 * $Log: Condition.hpp,v $
 * Revision 1.1.1.1  2000/07/19 16:55:12  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:16  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:37  god
 * Imported sources
 *
 * Revision 1.3  1999/03/03 19:09:01  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.2  1999/02/28 12:42:48  philogelos
 * *** empty log message ***
 *
 * Revision 1.1.1.1  1998/11/25 20:11:05  philogelos
 * Quercus Robusta
 *
 * Revision 1.1  1998/07/10 10:39:22  philogelos
 * Publish-subscribe sub-system initialised
 * */

/* __CONDITION_HPP__ */
#endif
