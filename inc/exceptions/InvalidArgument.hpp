// -*-C++-*- 

/*  inc/exceptions/InvalidArgument.hpp  */


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


#ifndef __INVALIDARGUMENT_HPP__
#define __INVALIDARGUMENT_HPP__

/* $Id: InvalidArgument.hpp,v 1.1.1.1 2000/07/19 17:01:31 philogelos Exp $ */

#include "InternalError.hpp"
#include "defines.h"

BEGIN_QR_NAMESPACE

/**
   Exception thrown when invalid or incorrect 
   argument was supplied to the function or method.

   @author Philogelos
   @created Пнд 21 Сен 1998 14:11:43
*/
class InvalidArgument : public InternalError
#if defined( USE_STL )
                  ,virtual public std::logic_error
#endif
{
public:  InvalidArgument( String aMessage, const Top *const aSource );
public:  virtual String getDescription() const;

  /**
	*/
public:  virtual String  getClassName() const;
};

END_QR_NAMESPACE

/*
 * $Log: InvalidArgument.hpp,v $
 * Revision 1.1.1.1  2000/07/19 17:01:31  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:35  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:46  god
 * Imported sources
 *
 * Revision 1.3  1999/03/03 19:09:17  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.2  1999/02/28 15:37:29  philogelos
 * *** empty log message ***
 *
 * Revision 1.1.1.1  1998/11/25 20:11:06  philogelos
 * Quercus Robusta
 * */

/* __INVALIDARGUMENT_HPP__ */
#endif
