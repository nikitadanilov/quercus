// -*-C++-*- 

/*  inc/observe/JustCondition.hpp  */

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



#ifndef __JUSTCONDITION_HPP__
#define __JUSTCONDITION_HPP__

/* $Id: JustCondition.hpp,v 1.1.1.1 2000/07/19 17:03:13 philogelos Exp $ */

#include "Condition.hpp"
#include "Object.hpp"
#include "defines.h"



BEGIN_QR_NAMESPACE

/**

   @author Philogelos
   @created
*/
class JustCondition : public virtual Condition,
					  public virtual Object
{
public: JustCondition();

public: virtual ~JustCondition();

public: virtual void announce();

public:  virtual String  getClassName() const;
};


END_QR_NAMESPACE

/*
 * $Log: JustCondition.hpp,v $
 * Revision 1.1.1.1  2000/07/19 17:03:13  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:36  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:47  god
 * Imported sources
*/

/* __JUSTCONDITION_HPP__ */
#endif
