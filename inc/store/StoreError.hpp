// -*-C++-*- 

/*  inc/store/StoreError.hpp  */

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



#ifndef __STOREERROR_HPP__
#define __STOREERROR_HPP__

/* $Id: StoreError.hpp,v 1.1 2000/09/21 16:46:01 philogelos Exp $ */

#include "exceptions/ExternalError.hpp"
#include "String.hpp"
#include "defines.h"

BEGIN_QR_NAMESPACE

/**

   @author Philogelos
   @created Thu Sep 14 22:32:44 2000
*/
class StoreError : public virtual ExternalError
{
public: StoreError( String aMessage, const Top *const aSource );
public: virtual String getClassName() const;
public: virtual String getDescription() const;
};

END_QR_NAMESPACE

/*
 * $Log: StoreError.hpp,v $
 * Revision 1.1  2000/09/21 16:46:01  philogelos
 * Persistency sub-system (first draft). Store only.
 *
 */

/* __STOREERROR_HPP__ */
#endif
