// -*-C++-*- 

/*  inc/exceptions/RuntimeError.hpp  */

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



#ifndef __RUNTIMEERROR_HPP__
#define __RUNTIMEERROR_HPP__

/* $Id: RuntimeError.hpp,v 1.1.1.1 2000/07/19 17:01:39 philogelos Exp $ */

#include "Exception.hpp"
#include "defines.h"

BEGIN_QR_NAMESPACE



/**
   Base-class for run-time errors (modelled after JDK).
   Whenever method has THROWS clause RuntimeError *
   is added to list of thrown exceptions, and you need not
   mention it explicitly.

   WARNING: this should not be sub-classed virtually!
   Otherwise, your exceptions will call ``terminate''
   (at least in egcs)(?)

   @author Philogelos
   @created
*/
class RuntimeError : public virtual Exception
{
public:  RuntimeError( String aMessage, const Top *const aSource );
public:  virtual String getDescription() const;
};

END_QR_NAMESPACE

/*
 * $Log: RuntimeError.hpp,v $
 * Revision 1.1.1.1  2000/07/19 17:01:39  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:35  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:47  god
 * Imported sources
*/

/* __RUNTIMEERROR_HPP__ */
#endif
