// -*-C++-*- 

/*  src/algorithms/access/HashTable.cpp  */

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



/* $Id: HashTable.cpp,v 1.1 2001/04/16 10:20:01 philogelos Exp $ */
#if !defined( _INLINE )
static char cvsid[] = "@(#)$Id: HashTable.cpp,v 1.1 2001/04/16 10:20:01 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif

#include "algorithms/access/HashTable.hpp"
#include "algorithms/hashes/Hash.hpp"
#include "containers/arrays/CArray.hpp"
#include "containers/dicts/DumbDictionary.hpp"
#include "containers/Pair.hpp"
#include "OGuard.hpp"
#include "Debug.hpp"

#include "exceptions/NoEntity.hpp"
#include "exceptions/AlreadyExists.hpp"

BEGIN_QR_NAMESPACE

HashTable::HashTable( Hash *aHash, Index aSlots )
{
  preC_( aHash != NULL );
  preC_( aSlots > 0 );

  hash = aHash;
  chains = new CArray( 0, aSlots );
  for( Index i = chains -> getLowBound() ; i < chains -> getHighBound() ; ++i )
	{
	  chains -> setAt( i, new DumbDictionary() );
	}
}

HashTable::~HashTable()
{}

void HashTable::insert( Top *aKey, 
						Top *anObject ) THROWS( AlreadyExists * )
{
  preC_( aKey != NULL );
  preC_( anObject != NULL );

  OGuard _this( this, this );
  OGuard _key( aKey, this );
  OGuard _obj( anObject, this );

  if( ! getChain( aKey ) -> isSuchKey( aKey ) )
	{
	  getChain( aKey ) -> addKey( aKey, anObject );
	}
  else
	{
	  throw new AlreadyExists( "Cannot insert into hash-table", null );
	}
}

void HashTable::remove( Top *aKey ) THROWS( NoEntity * )
{
  preC_( aKey != NULL );

  OGuard _this( this, this );
  OGuard _key( aKey, this );

  if( getChain( aKey ) -> isSuchKey( aKey ) )
	{
	  Top *obj;

	  obj = getChain( aKey ) -> removeKey( aKey );
	  OGuard _del( obj, this );
	}
  else
	{
	  throw new NoEntity( "Cannot remove non-existing object from hash-table", 
						  null );
	}
}

Top *HashTable::lookup( Top *aKey ) const
{
  preC_( aKey != NULL );

  OGuard _this( this, this );
  OGuard _key( aKey, this );

  if( getChain( aKey ) -> isSuchKey( aKey ) )
	{
	  return getChain( aKey ) -> getValueAtKey( aKey );
	}
  else
	{
	  return nil;
	}
}


Index HashTable::getHash( Top *aKey ) const
{
  return( hash -> hashObject( hash -> initial(), 
							  aKey ) % chains -> getLength() );
}

Dictionary *HashTable::getChain( Top *aKey ) const
{
  return DCAST( chains -> getAt( getHash( aKey ) ), DumbDictionary );
}

boolean HashTable::equals( const Top *anOther ) const
{
  CRef< HashTable > other;

  other = DCAST( anOther, HashTable );
  return( ( *other != NULL ) && 
		  ( other -> chains -> equals( *chains ) ) &&
		  ( other -> hash -> equals( *hash ) ) );
}

String  HashTable::getString() const
{
  return String( "HashTable: hash: " ) + hash -> getString() +
	" chains: " + chains -> getString();
}

String  HashTable::getClassName() const
{
  return "HashTable";
}

#if defined( TESTING )

END_QR_NAMESPACE

#include "algorithms/hashes/FNV1Hash.hpp"
#include "MemoryMonitor.hpp"

BEGIN_QR_NAMESPACE

boolean HashTable::tester( int ) const
{
  {
	DLOG( "HashTable Testing: constructor" );
	CRef< HashTable > target;
	target = new HashTable( FNV1Hash::getInstance(), 11 );
	DLOGOBJECT( "Created fresh: %s", *target );
  }
  {
	Index i;

	DLOG( "HashTable Testing: populating" );
	CRef< HashTable > target;
	target = new HashTable( FNV1Hash::getInstance(), 11 );
	DLOG( "Allocated: %li", MemoryMonitor::amount() );
	for( i = 0 ; i < 40 ; ++i )
	  {
		target -> insert( new Integer( i ), new String( i, 16 ) );
	  }
	DLOGOBJECT( "Populated: %s", *target );
	DLOG( "Allocated: %li", MemoryMonitor::amount() );
	for( i = 0 ; i < 40 ; ++i )
	  {
		if( target -> lookup( new Integer( i ) ) == NULL )
		  {
			DLOG( "Huh? %li not found", i );
			return false;
		  }
		else if( ! target -> lookup( new Integer( i ) ) 
				 -> equals( new String( i, 16 ) ) )
		  {
			DLOG( "Huh? %li not equal:", i );
			DLOGSTRING( "want: %s", String( i, 16 ) );
			DLOGOBJECT( "got: %s", target -> lookup( new Integer( i ) ) );
			return false;
		  }
	  }
	DLOG( "Allocated: %li", MemoryMonitor::amount() );
	for( i = 0 ; i < 40 ; ++i )
	  {
		target -> remove( new Integer( i ) );
	  }
	DLOGOBJECT( "Cleared: %s", *target );
	DLOG( "Allocated: %li", MemoryMonitor::amount() );
  }
  return true;
}
#endif

END_QR_NAMESPACE

#if defined( _INLINE )
#include "../src/Debug.ipp"
#endif


/*
 * $Log: HashTable.cpp,v $
 * Revision 1.1  2001/04/16 10:20:01  philogelos
 * HashTable access method. Stores each hash-chain as (Dumb)Dictionary
 * keyed by key in table.
 *
 */
