// -*-C++-*- 

/*  inc/algorithms/parse/ParseError.hpp  */

/*
 * Author: Philogelos A. <Philogelos@yahoo.com>
 * Maintainer: Philogelos A.
 * Keywords: C++, library, containers
 *
 * Copyright (C) 1999, 2000 Philogelos A.
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



#ifndef __PARSEERROR_HPP__
#define __PARSEERROR_HPP__

/* $Id: ParseError.hpp,v 1.1.1.1 2000/07/19 16:58:45 philogelos Exp $ */

#include "exceptions/ExternalError.hpp"
#include "defines.h"

BEGIN_QR_NAMESPACE

/**

   @author Philogelos
   @created Sun Apr 30 03:19:31 2000
*/
class ParseError : public virtual ExternalError
{
public:  ParseError( String aMessage, const Top *const aSource );
public:  virtual String  getClassName() const;
public:  virtual String getDescription() const;
};

END_QR_NAMESPACE

/*
 * $Log: ParseError.hpp,v $
 * Revision 1.1.1.1  2000/07/19 16:58:45  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.1  2000/07/19 08:48:03  god
 * new parse method: ask all factories and accept one with longest match
 *
 */

/* __PARSEERROR_HPP__ */
#endif
