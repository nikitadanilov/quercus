// -*-C++-*- 

/*  inc/algorithms/string/StringFilter.hpp  */

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



#ifndef __STRINGFILTER_HPP__
#define __STRINGFILTER_HPP__

/* $Id: StringFilter.hpp,v 1.1.1.1 2000/07/19 16:58:53 philogelos Exp $ */

#include "iter/enumerations/TypedEnumeration.hpp"
#include "Char.hpp"
#include "String.hpp"
#include "Top.hpp"
#include "defines.h"



BEGIN_QR_NAMESPACE

/**

   @author Philogelos
   @created
*/
interface StringFilter : public virtual Top
{
 public: virtual void setBase( StringFilter *aBase ) = 0;
 public: virtual StringFilter *getBase() = 0;
 public: virtual String asString() = 0;
 public: virtual String restAsString() = 0;
 public: virtual Index length() = 0;
 public: virtual Index rest() = 0;
 public: virtual unichar getNext() = 0;
 public: virtual void reset() = 0;
 public: virtual Index getPosition() = 0;
};


END_QR_NAMESPACE

/*
 * $Log: StringFilter.hpp,v $
 * Revision 1.1.1.1  2000/07/19 16:58:53  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:17  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:43  god
 * Imported sources
*/

/* __STRINGFILTER_HPP__ */
#endif
