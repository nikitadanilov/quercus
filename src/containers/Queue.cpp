// -*-C++-*- 

/*  src/containers/Queue.cpp  */

/*
 * Author: Philogelos A. <Philogelos@yahoo.com>
 * Maintainer: Philogelos A.
 * Keywords: C++, library, containers
 *
 * Copyright (C) 1999 Philogelos A.
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



/* $Id: Queue.cpp,v 1.1.1.1 2000/07/19 16:45:32 philogelos Exp $ */
#if !defined(_INLINE)
static char cvsid[] = "@(#)$Id: Queue.cpp,v 1.1.1.1 2000/07/19 16:45:32 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif

#include "iter/enumerations/EmptyEnumeration.hpp"
#include "containers/lists/List.hpp"
#include "containers/Queue.hpp"
#include "LinkManager.hpp"
#include "PGuard.hpp"
#include "OGuard.hpp"
#include "Debug.hpp"

BEGIN_QR_NAMESPACE

Queue::Queue()
{
  FINIT( elements, new List() );
}

Queue::~Queue()
{
  FDONE( elements );
}

Top *Queue::get() THROWS( EmptyContainer * )
{
  if( elements -> isEmpty() )
	{
	  throw new EmptyContainer( "get() from empty queue", null );
	  RET_THROW( NULL );
	}
  else
	{
	  return elements -> behead();
	}
}

void Queue::push( Top *anObject )
{
  elements -> append( anObject );
}
  
MutableContainer *Queue::getBaseMutableContainer() const
{
  return elements;
}

TypedEnumeration< RemovablePosition > *Queue::getRemovable() const
{
  return TypedEnumeration< RemovablePosition >::upcast
	( new EmptyEnumeration() );
}

PositionFactory *Queue::getDefaultPositionFactory() const
{
  return ( PositionFactory * ) NIL;
}

String  Queue::getClassName() const
{
  return "Queue";
}

#if defined( TESTING )

boolean Queue::tester( int ) const
{
  {
	DLOG( "Queue Testing: constructor" );
	Queue *target;
	target = new Queue();
	OGuard _target( target, this );
	DLOGOBJECT( "Created fresh: %s", target );
  }
  {
	DLOG( "Queue Testing: push" );
	Queue *target;
	target = new Queue();
	OGuard _target( target, this );
	DLOGOBJECT( "Created fresh: %s", target );
	target -> push( new String( "1" ) );
	target -> push( new String( "2" ) );
	target -> push( new String( "3" ) );
	DLOGOBJECT( "filled: %s", target );
  }
  {
	DLOG( "Queue Testing: pop" );
	Queue *target;
	target = new Queue();
	OGuard _target( target, this );
	DLOGOBJECT( "Created fresh: %s", target );
	for( int i = 0 ; i < 200 ; ++i )
	  {
		target -> push( new String( i, 10 ) );
	  }
	DLOGOBJECT( "filled: %s", target );
	for( int j = 0 ; j < 200 ; ++j )
	  {
		Top *item;
		
		item = target -> get();
		OGuard _item( item, this );
		DLOGOBJECT( "popped: %s", item );
	  }
	if( !target -> isEmpty() )
	  {
		DLOG( "not empty!!!" );
		return false;
	  }
  }
  return true;
}

#endif

END_QR_NAMESPACE

#if defined(_INLINE)
#include "../src/Debug.ipp"
#endif


/*
 * $Log: Queue.cpp,v $
 * Revision 1.1.1.1  2000/07/19 16:45:32  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:41  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:32  god
 * Imported sources
*/
