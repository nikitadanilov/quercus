// -*-C++-*- 

/*  inc/store/StoreSession.hpp  */

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



#ifndef __STORESESSION_HPP__
#define __STORESESSION_HPP__

/* $Id: StoreSession.hpp,v 1.1 2000/09/21 16:46:01 philogelos Exp $ */

#include "CRef.hpp"
#include "Object.hpp"
#include "defines.h"
#include "String.hpp"

BEGIN_QR_NAMESPACE

class StorePlatform;
class StoreError;
class NoEntity;
class Storable;
class Stack;
class Dictionary;

typedef Index RefId;

/* for now, may be something should be added. */
typedef Top StoringState;

/**

   @author Philogelos
   @created Thu Sep 14 19:30:49 2000
*/
class StoreSession : public virtual Object
{

  /**
   */
public: StoreSession( String aName,
					  Storable *aRoot, StorePlatform *aPlatform );

  /**
   */
public: virtual ~StoreSession();

public: virtual void store() THROWS( StoreError * );

public: virtual void pushObject( String aName, Storable *anObject ) 
  THROWS( StoreError * );
public: virtual void popObject() THROWS( NoEntity * );
														
public: virtual RefId addReference( Storable *anObject, 
									String aName ) THROWS( StoreError * );
public: virtual StorePlatform *getPlatform() const;
public: virtual StoringState *getCurrentState() const;
public: virtual Storable *getCurrentObject() const;
public: virtual Storable *getRoot() const;
public: virtual String getName() const;

  /**
   */
public: virtual String  getClassName() const;

protected: CRef< Storable > root;
protected: CRef< StorePlatform > platform;
protected: CRef< Stack > path;
protected: CRef< Dictionary > storedObjects;
protected: String name;
protected: Index backRefs;
};

END_QR_NAMESPACE

/*
 * $Log: StoreSession.hpp,v $
 * Revision 1.1  2000/09/21 16:46:01  philogelos
 * Persistency sub-system (first draft). Store only.
 *
 */

/* __STORESESSION_HPP__ */
#endif
