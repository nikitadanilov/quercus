// -*-C++-*- 

/*  inc/platform/store/POSIXStore.hpp  */

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



#ifndef __POSIXSTORE_HPP__
#define __POSIXSTORE_HPP__

/* $Id: POSIXStore.hpp,v 1.1 2000/09/21 16:46:04 philogelos Exp $ */

#include "store/StorePlatform.hpp"
#include "store/FieldWriter.hpp"
#include "store/StoreError.hpp"
#include "exceptions/Errno.hpp"
#include "String.hpp"
#include "Object.hpp"
#include "defines.h"
#include "CRef.hpp"

BEGIN_QR_NAMESPACE

class POSIXFieldWriter;
class POSIXFieldReader;
class StoreError;

/**

   @author Philogelos
   @created Fri Sep 15 15:55:25 2000
*/
class POSIXStore : public virtual StorePlatform,
				   public virtual Object
{
public: POSIXStore( String aStartPath );
public: virtual ~POSIXStore();

public: virtual StoringState *init( StoreSession *aSession ) 
  THROWS( StoreError * );
public: virtual FieldWriter  *getWriter( StoreSession *aSession );
public: virtual StoringState *getState( String aName, 
										StoreSession *aSession,
										Storable *anObject )
  THROWS( StoreError * );
public: virtual void storeRef( StoreSession *aSession,
							   RefId anId, StoringState *aState, 
							   Storable *anObject,
							   String aName ) THROWS( StoreError * );

public: virtual String getStartPath() const;
public: virtual String getClassName() const;

public: virtual int open( String aName ) THROWS( StoreError * );
public: virtual int write( int fd, String aValue ) THROWS( StoreError * );
public: virtual void mkdir( String aPath ) THROWS( StoreError * );

public: virtual String getTypeTag() const;
public: virtual String getRefTag() const;
public: virtual String getVerTag() const;

public: virtual String getSubobjPrefix() const;
public: virtual String getStringPrefix() const;
public: virtual String getIndexPrefix() const;
public: virtual String getBooleanPrefix() const;
public: virtual String getRefPrefix() const;

public: virtual String getPath( StoreSession *aSession );
public: virtual String getFullPath( StoreSession *aSession, String aName );

protected: String startPath;
protected: CRef< FieldWriter > writer;
  // protected: CRef< FieldReader > reader;
};

class POSIXFieldWriter : public virtual FieldWriter,
						 public virtual Object
{
public: POSIXFieldWriter( POSIXStore *aStore );

public: virtual void storeString( StoreSession *aSession, String aName, 
								  String aValue ) THROWS( StoreError * );
public: virtual void storeIndex( StoreSession *aSession, String aName, 
								 Index aValue ) THROWS( StoreError * );
public: virtual void storeBoolean( StoreSession *aSession, String aName, 
								   boolean aValue ) THROWS( StoreError * );
public: virtual void storeRef( StoreSession *aSession, String aName, 
							   RefId anId ) THROWS( StoreError * );

protected: CRef< POSIXStore > store;
};

class POSIXStoreError : public virtual StoreError,
						public virtual Errno
{
public: POSIXStoreError( String aMessage, const Top *const aSource );
public: virtual String getClassName() const;
public: virtual String getDescription() const;
};

END_QR_NAMESPACE

/*
 * $Log: POSIXStore.hpp,v $
 * Revision 1.1  2000/09/21 16:46:04  philogelos
 * Persistency sub-system (first draft). Store only.
 *
 */

/* __POSIXSTORE_HPP__ */
#endif
