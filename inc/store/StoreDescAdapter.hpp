// -*-C++-*- 

/*  inc/store/StoreDescAdapter.hpp  */

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



#ifndef __STOREDESCADAPTER_HPP__
#define __STOREDESCADAPTER_HPP__

/* $Id: StoreDescAdapter.hpp,v 1.1 2000/09/21 16:46:01 philogelos Exp $ */

#include "StorableDesc.hpp"
#include "Object.hpp"
#include "defines.h"
#include "CRef.hpp"

BEGIN_QR_NAMESPACE

class Container;

/**

   @author Philogelos
   @created Fri Sep 15 18:00:56 2000
*/
class StoreDescAdapter : public virtual StorableDesc,
						 public virtual Object
{
public: StoreDescAdapter( String aVersion, Container *aFields );
public: virtual ~StoreDescAdapter();

public: virtual TypedEnumeration< Field > *getFields() const;
public: virtual String getVersion() const;

public:  virtual String  getClassName() const;

protected: CRef< Container > fields;
protected: String version;
};

END_QR_NAMESPACE

/*
 * $Log: StoreDescAdapter.hpp,v $
 * Revision 1.1  2000/09/21 16:46:01  philogelos
 * Persistency sub-system (first draft). Store only.
 *
 */

/* __STOREDESCADAPTER_HPP__ */
#endif
