// -*-C++-*- 

/*  inc/store/FieldWriter.hpp  */

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



#ifndef __FIELDWRITER_HPP__
#define __FIELDWRITER_HPP__

/* $Id: FieldWriter.hpp,v 1.1 2000/09/21 16:46:01 philogelos Exp $ */

#include "StoreSession.hpp"
#include "String.hpp"
#include "Top.hpp"
#include "defines.h"

BEGIN_QR_NAMESPACE

class StoreError;

/**

   @author Philogelos
   @created Thu Sep 14 19:24:10 2000
*/
interface FieldWriter : public virtual Top
{
 public: virtual void storeSubobject( StoreSession *aSession, String aName, 
									  Storable *aValue ) THROWS( StoreError * );
 public: virtual void storeString( StoreSession *aSession, String aName, 
								   String aValue ) THROWS( StoreError * ) = 0;
 public: virtual void storeIndex( StoreSession *aSession, String aName, 
								  Index aValue ) THROWS( StoreError * ) = 0;
 public: virtual void storeBoolean( StoreSession *aSession, String aName, 
									boolean aValue ) THROWS( StoreError * ) = 0;
 public: virtual void storeRef( StoreSession *aSession, String aName, 
								RefId anId ) THROWS( StoreError * ) = 0;
};

END_QR_NAMESPACE

/*
 * $Log: FieldWriter.hpp,v $
 * Revision 1.1  2000/09/21 16:46:01  philogelos
 * Persistency sub-system (first draft). Store only.
 *
 */

/* __FIELDWRITER_HPP__ */
#endif
