// -*-C++-*- 

/*  src/algorithms/access/SkipList.cpp  */

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



/* $Id: SkipList.cpp,v 1.1 2001/04/16 10:21:40 philogelos Exp $ */
#if !defined( _INLINE )
static char cvsid[] = "@(#)$Id: SkipList.cpp,v 1.1 2001/04/16 10:21:40 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif

#include "algorithms/access/SkipList.hpp"
#include "algorithms/arrays/CArray.hpp"
#include "containers/list/List.hpp"
#include "Comparator.hpp"
#include "OGuard.hpp"
#include "Debug.hpp"

#include "exceptions/NoEntity.hpp"
#include "exceptions/AlreadyExists.hpp"

BEGIN_QR_NAMESPACE

SkipList::SkipList( Comparator *aComparator, Index anInitialHeight )
{
  preC_( aComparator != NULL );
  preC_( anInitialHeight >= 0 );

  minusInfinity = new Pair( null, new String( "$-\infty$" ) );
  plusInfinity = new Pair( null, new String( "$+\infty$" ) );

  comp = aComparator;
  list = new CArray( 0, anInitialHeight + 1 );
  for( Index i = 0 ; i < list -> getHighBound() ; ++i )
	{
	  list -> setAt( i, new List() );
	  getListAt( i ) -> append( minusInfinity );
	  getListAt( i ) -> append( plusInfinity );
	}
}

SkipList::~SkipList()
{}

void SkipList::insert( Top *aKey, 
					   Top *anObject ) THROWS( AlreadyExists * )
{
  preC_( aKey != NULL );
  preC_( anObject != NULL );
  
  OGuard _self( this, this );
  OGuard _key( key, this );
  OGuard _obj( anObject, this );

  if( !findPos( aKey ) )
	{
	  CRef< Pair > item;

	  item = new Pair( aKey, anObject );
	  for( Index height = list -> getHighBound() - 1 ; height >= 0 ; --height )
		{
		  getListAt( height ) -> insert( item );
		}
	}
  else
	{
	  throw new AlreadyExists( "", null );
	}
}

void SkipList::remove( Top *aKey ) THROWS( NoEntity * )
{
  preC_( aKey != NULL );
  preC_( anObject != NULL );
  
  OGuard _self( this, this );
  OGuard _key( key, this );
  OGuard _obj( anObject, this );

  if( findPos( aKey ) )
	{
	  CRef< Pair > item;

	  item = new Pair( aKey, anObject );
	  for( Index height = list -> getHighBound() - 1 ; height >= 0 ; --height )
		{
		  OGuard _del( getListAt( height ) -> remove() );
		}
	}
  else
	{
	  throw new NoEntity( "", null );
	}
}

Top *SkipList::lookup( Top *aKey ) const
{
  preC_( aKey != NULL );
  preC_( anObject != NULL );
  
  OGuard _self( this, this );
  OGuard _key( key, this );
  OGuard _obj( anObject, this );

  if( findPos( aKey ) )
	{
	  return getAt( 0 ) -> getAt( 1 );
	}
  else
	{
	  return NULL;
	}
}

boolean SkipList::findPos( Top *aKey ) const
{
  OGuard _key( key, this );

  CRef< Position > scan;

  for( Index height = list -> getHighBound() - 1 ; height >= 0 ; --height )
	{
	  List *hlist;

	  hlist = getListAt( height );
	  for( hlist -> toHead() ; ( ! hlist -> isLast() ) ; )
		{
		  hlist -> next();
		  if( compareWith( aKey, getAt( height ) ) == less_than )
			{
			  hlist -> prev();
			  break;
			}
		}
	}
  return compareWith( aKey, getAt( 0 ) ) == equal_to;
}

ComparisonResult SkipList::compareWith( Top *aKey, Pair *aPair ) const
{
  preC_( aKey != NULL );
  preC_( aPair != NULL );

  OGuard _key( key, this );
  OGuard _pair( aPair, this );
  
  if( aPair == minusInfinity )
	{
	  return less_than;
	}
  else if( aPair == plusInfinity )
	{
	  return greater_than;
	}
  else
	{
	  return comp -> compare( aKey, aPair -> getAt( 0 ) );
	}
}

List *SkipList::getListAt( Index anIndex ) const
{
  return DCAST( list -> getAt( anIndex ), List );
}

Pair *SkipList::getAt( Index anIndex ) const
{
  return DCAST( getListAt( anIndex ) -> getCurrentValue(), Pair );
}

String  SkipList::getString() const
{
  return String( "Skip list: " ) + getListAt( 0 ) -> getString();
}

String  SkipList::getClassName() const
{
  return "SkipList";
}

SkipList::Node::Node( Top *aKey, Top *aValue, Index aHeight )
{
  preC_( aKey != NULL );
  preC_( aValue != NULL );
  preC_( aHeight > 0 );

  key = aKey;
  value = aValue;
  tower = new List();
}

SkipList::Node::~Node();

Position *SkipList::Node::getAt( Index height );

END_QR_NAMESPACE

#if defined( _INLINE )
#include "../src/Debug.ipp"
#endif


/*
 * $Log: SkipList.cpp,v $
 * Revision 1.1  2001/04/16 10:21:40  philogelos
 * Skip-list access method added (not done yet).
 *
 */
