// -*-C++-*- 

/*  inc/algorithms/access/AccessMethod.hpp  */

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



#ifndef __ACCESSMETHOD_HPP__
#define __ACCESSMETHOD_HPP__

/* $Id: AccessMethod.hpp,v 1.1 2001/04/13 19:41:26 philogelos Exp $ */

#include "Top.hpp"
#include "defines.h"

BEGIN_QR_NAMESPACE

class AlreadyExists;
class NoEntity;
/**
   Interface to various access methods: balanced trees, hash tables,
   skip-lists etc.

   @author Philogelos 
   @created Wed Mar 21 20:14:30 2001
*/
interface AccessMethod : public virtual Top
{
 public: virtual void insert( Top *aKey, 
							  Top *anObject ) THROWS( AlreadyExists * ) = 0;
 public: virtual void remove( Top *aKey ) THROWS( NoEntity * ) = 0;
 public: virtual Top *lookup( Top *aKey ) const = 0;
};

END_QR_NAMESPACE

/*
 * $Log: AccessMethod.hpp,v $
 * Revision 1.1  2001/04/13 19:41:26  philogelos
 * AccessMethod: interface for things like hash-tables, balanced-trees, skip-lists etc.
 *
 */

/* __ACCESSMETHOD_HPP__ */
#endif
