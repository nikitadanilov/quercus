// -*-C++-*- 

/*  inc/iter/enumerations/ResettableEnumeration.hpp  */


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


#ifndef __RESETTABLEENUMERATION_HPP__
#define __RESETTABLEENUMERATION_HPP__

/* $Id: ResettableEnumeration.hpp,v 1.1.1.1 2000/07/19 17:02:16 philogelos Exp $ */

#include "Enumeration.hpp"
#include "defines.h"

BEGIN_QR_NAMESPACE



/**
   Advances enumeration. This interface allows
   enumerations to be reset back.

   @author Philogelos
   @created Чтв 24 Сен 1998 18:48:26
*/
interface ResettableEnumeration : public virtual Enumeration
{
  /**
	 Rewinds enumeration back to the very beginning.
  */
 public: virtual void reset() = 0;
};

END_QR_NAMESPACE

/*
 * $Log: ResettableEnumeration.hpp,v $
 * Revision 1.1.1.1  2000/07/19 17:02:16  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:35  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:40  god
 * Imported sources
 *
 * Revision 1.2  1999/03/03 19:09:20  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.1.1.1  1998/11/25 20:11:07  philogelos
 * Quercus Robusta
 * */

/* __RESETTABLEENUMERATION_HPP__ */
#endif
