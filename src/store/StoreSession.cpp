// -*-C++-*- 

/*  src/store/StoreSession.cpp  */

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



/* $Id: StoreSession.cpp,v 1.1 2000/09/21 16:46:04 philogelos Exp $ */
#if !defined( _INLINE )
static char cvsid[] = "@(#)$Id: StoreSession.cpp,v 1.1 2000/09/21 16:46:04 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif

#include "store/StorePlatform.hpp"
#include "store/StoreSession.hpp"
#include "store/StorableDesc.hpp"
#include "store/FieldWriter.hpp"
#include "store/StoreError.hpp"
#include "store/Storable.hpp"
#include "store/Field.hpp"
#include "iter/enumerations/TypedEnumeration.hpp"
#include "containers/dicts/DumbDictionary.hpp"
#include "containers/arrays/CArray.hpp"
#include "exceptions/NoEntity.hpp"
#include "containers/Stack.hpp"
#include "containers/Pair.hpp"
#include "Integer.hpp"
#include "Debug.hpp"

BEGIN_QR_NAMESPACE

StoreSession::StoreSession( String aName,
							Storable *aRoot, StorePlatform *aPlatform )
{
  /* preC_( aRoot != NULL ); why? storing NULL is ok */
  preC_( aPlatform != NULL );

  root = aRoot;
  platform = aPlatform;
  storedObjects = new DumbDictionary();
  path = new Stack();
  name = aName;
  backRefs = 0;
}

StoreSession::~StoreSession()
{}

void StoreSession::store() THROWS( StoreError * )
{
  preC_( path -> isEmpty() );

  CRef< FieldWriter > writer;

  path -> push( new Pair( NULL, getPlatform() -> init( this ) ) );
  writer = getPlatform() -> getWriter( this );
  writer -> storeSubobject( this, getName(), getRoot() );
  path -> pop();
  postC_( path -> isEmpty() );
}

void StoreSession::pushObject( String aName, Storable *anObject ) 
  THROWS( StoreError * )
{
  path -> push
	( new Pair( anObject, 
				getPlatform() -> getState( aName, this, anObject ) ) );
}

void StoreSession::popObject() THROWS( NoEntity * )
{
  path -> pop();
}
														
RefId StoreSession::addReference( Storable *anObject,
								  String aName ) THROWS( StoreError * )
{
  CRef< CArray > tag;

  if( storedObjects -> isSuchKey( anObject ) )
	{
	  CRef< Integer > refNo;

	  tag = TCAST( storedObjects -> getValueAtKey( anObject ), CArray );
	  refNo =  TCAST( tag -> getAt( 0 ), Integer );

	  if( refNo -> getInt() == -1 )
		{
		  CRef< StoringState > state;
		  String oName;

		  state =  TCAST( tag -> getAt( 1 ), StoringState );
		  oName = *TCAST( tag -> getAt( 2 ), String );

		  refNo -> setInt( ++backRefs );
		  getPlatform() -> storeRef( this, backRefs, *state, anObject, oName );
		}
	  return refNo -> getInt();
	}
  else
	{
	  tag = new CArray( 0, 3 );
	  tag -> setAt( 0, new Integer( -1 ) );
	  tag -> setAt( 1, getCurrentState() );
	  tag -> setAt( 2, aName.clone() );
	  storedObjects -> addKey( anObject, *tag );
	  return -1;
	}
}

StorePlatform *StoreSession::getPlatform() const
{
  return *platform;
}

Storable *StoreSession::getRoot() const
{
  return *root;
}

Storable *StoreSession::getCurrentObject() const
{
  preC_( ! path -> isEmpty() );

  return( TCAST( TCAST( path -> top(), Pair ) -> getAt( 1 ), Storable ) );
}

StoringState *StoreSession::getCurrentState() const
{
  preC_( ! path -> isEmpty() );

  return( TCAST( TCAST( path -> top(), Pair ) -> getAt( 2 ), StoringState ) );
}

String StoreSession::getName() const
{
  return name;
}

String StoreSession::getClassName() const
{
  return "StoreSession";
}

END_QR_NAMESPACE

#if defined( _INLINE )
#include "../src/Debug.ipp"
#endif


/*
 * $Log: StoreSession.cpp,v $
 * Revision 1.1  2000/09/21 16:46:04  philogelos
 * Persistency sub-system (first draft). Store only.
 *
 */
