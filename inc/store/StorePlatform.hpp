// -*-C++-*- 

/*  inc/store/StorePlatform.hpp  */

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



#ifndef __STOREPLATFORM_HPP__
#define __STOREPLATFORM_HPP__

/* $Id: StorePlatform.hpp,v 1.1 2000/09/21 16:46:01 philogelos Exp $ */

#include "Top.hpp"
#include "defines.h"
#include "StoreSession.hpp"

BEGIN_QR_NAMESPACE

class StoreSession;
class FieldWriter;
class FieldReader;
class StoreError;

/**

   @author Philogelos
   @created Thu Sep 14 22:37:07 2000
*/
interface StorePlatform : public virtual Top
{
 public: virtual StoringState *init( StoreSession *aSession ) 
		   THROWS( StoreError * ) = 0;
 public: virtual FieldWriter  *getWriter( StoreSession *aSession ) = 0;
 public: virtual StoringState *getState( String aName, 
										 StoreSession *aSession,
										 Storable *anObject ) 
		   THROWS( StoreError * ) = 0;
 public: virtual void storeRef( StoreSession *aSession,
								RefId anId, StoringState *aState, 
								Storable *anObject,
								String aName ) THROWS( StoreError * ) = 0;
};

END_QR_NAMESPACE

/*
 * $Log: StorePlatform.hpp,v $
 * Revision 1.1  2000/09/21 16:46:01  philogelos
 * Persistency sub-system (first draft). Store only.
 *
 */

/* __STOREPLATFORM_HPP__ */
#endif

