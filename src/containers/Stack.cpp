// -*-C++-*- 

/*  src/containers/Stack.cpp  */

/*
 * Author: Philogelos A. <Philogelos@yahoo.com>
 * Maintainer: Philogelos A.
 * Keywords: C++, library, containers
 *
 * Copyright (C) 1998, 1999 Philogelos A.
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



/* $Id: Stack.cpp,v 1.1.1.1 2000/07/19 16:45:50 philogelos Exp $ */
#if !defined(_INLINE)
static char cvsid[] = "@(#)$Id: Stack.cpp,v 1.1.1.1 2000/07/19 16:45:50 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif

#include "iter/enumerations/EmptyEnumeration.hpp"
#include "containers/lists/List.hpp"
#include "containers/EmptyStack.hpp"
#include "containers/Stack.hpp"
#include "LinkManager.hpp"
#include "PGuard.hpp"
#include "OGuard.hpp"
#include "Debug.hpp"

BEGIN_QR_NAMESPACE

Stack::Stack()
{
  init();
}

Stack::Stack( Stack &aSource )
{
  PGuard _this( this, this );
  OGuard _source( &aSource, this );

  init();
  for( aSource.elements -> toFirst() ; 
	   !( aSource.elements -> atEnd() ) ;
	   aSource.elements -> next() )
	{
	  push( aSource.elements -> getCurrentValue() );
	}
  postC_( getCardinality() == aSource.getCardinality() );
  postC_( equals( &aSource ) );
}

Stack::~Stack()
{
  preC_( elements != ( List * ) NULL );
  FDONE( elements );
}

void Stack::push( Top *anElement )
{
  elements -> append( anElement );
}

Top *Stack::pop() THROWS( EmptyStack * )
{
  OGuard _this( this, this );
  if( isEmpty() )
	{
	  throw new EmptyStack( "Stack::pop()", null );
	}
  return( elements -> betail() );
}

void Stack::dup()
{
  OGuard _this( this, this );
  push( top() );
}

void Stack::swap() THROWS( EmptyStack * )
{
  Top *first;
  Top *second;

  OGuard _this( this, this );
  if( isEmpty() )
	{
	  throw new EmptyStack( "Stack::swap()", null );
	}
  first = pop();
  if( isEmpty() )
	{
	  throw new EmptyStack( "Stack::swap()-2", null );
	}
  second = pop();

  push( first );
  push( second );
}

Top *Stack::exchange( Top *anElement ) THROWS( EmptyStack * )
{
  OGuard _this( this, this );
  OGuard _element( anElement, this );

  Top *element;

  if( isEmpty() )
	{
	  throw new EmptyStack( "Stack::exchange()", null );
	}
  element = pop();
  push( anElement );
  return element;
}

Top *Stack::top() const THROWS( EmptyStack * )
{
  OGuard _this( this, this );
  /* well, this implementation
	 is particularly brain-damaged from
	 efficiency point of view,
	 but it is to clarify that minimal 
	 Stack interface consists of push/pop. */
  Top *element;
  if( isEmpty() )
	{
	  throw new EmptyStack( "Stack::top()", null );
	}
  element = ( ( Stack * ) this ) -> pop();
  ( ( Stack * ) this ) -> push( element );
  return element;
}

PositionFactory *Stack::getDefaultPositionFactory() const
{
  return ( PositionFactory * ) NIL;
}


TypedEnumeration< RemovablePosition > *Stack::getRemovable() const
{
  return TypedEnumeration< RemovablePosition >::upcast
	( new EmptyEnumeration() );
}

boolean Stack::isEmpty() const
{
  return( elements -> isEmpty() );
}

Index Stack::getCardinality() const
{
  return( elements -> getCardinality() );
}

boolean Stack::isValid( const Position *aPosition ) const
{
  OGuard _position( aPosition, this );

  preC_( aPosition != ( const Position * ) NIL );
  return( aPosition -> isValid() );
}

PositionEnumeration *Stack::getEnumeration() const
{
  return LayeredContainer::getEnumeration();
}

MutablePositionEnumeration *Stack::getMutableEnumeration() const
{
  return MutableLayeredContainer::getMutableEnumeration();
}

Position *Stack::getCurrentPunct() const
{
  return new FromBottomOfStackPosition
	( this, elements -> getCardinality() - 1 );
}

Position *Stack::getAlwaysPunct() const
{
  return new FromTopOfStackPosition( this, 0 );
}

Top *Stack::clone() const
{
  return new Stack( ( Stack & ) *this );
}

String  Stack::getClassName() const
{
  return "Stack";
}

void Stack::init()
{
  FINIT( elements, new List() );
}

MutableContainer *Stack::getBaseMutableContainer() const
{
  return elements;
}

StackPosition::StackPosition( const Stack *aHost, const Index anOffset ) :
  PositionAdapter( ( Container * ) aHost ),
  offset( anOffset )
{
  stack = aHost;
  postC_( isValid() );
}

Stack *StackPosition::getStack() const
{
  return ( Stack * ) stack;
}

boolean StackPosition::isValid() const
{
  return( ( 0 <= offset ) &&
		  ( offset < ( getStack() -> getCardinality() ) ) );
}

FromTopOfStackPosition::FromTopOfStackPosition( const Stack *aHost, const Index anOffset ) :
  StackPosition( aHost, anOffset ),
  PositionAdapter( ( Container * ) aHost )
{}

Top *FromTopOfStackPosition::getValue() const
{
  preC_( isValid() );
  return( getStack() -> elements -> 
		  getAt( getStack() -> getCardinality() - offset - 1 ) );
}


FromBottomOfStackPosition::FromBottomOfStackPosition( const Stack *aHost, const Index anOffset ) :
  StackPosition( aHost, anOffset ),
  PositionAdapter( ( Container * ) aHost )
{}

Top *FromBottomOfStackPosition::getValue() const
{
  preC_( isValid() );
  return( getStack() -> elements -> getAt( offset ) );
}

#if defined( TESTING )

boolean Stack::tester( int ) const
{
  {
	DLOG( "Stack Testing: constructor" );
	Stack *target;
	target = new Stack();
	OGuard _target( target, this );
	DLOGOBJECT( "Created fresh: %s", target );
  }
  {
	DLOG( "Stack Testing: push" );
	Stack *target;
	target = new Stack();
	OGuard _target( target, this );
	DLOGOBJECT( "Created fresh: %s", target );
	target -> push( new String( "1" ) );
	target -> push( new String( "2" ) );
	target -> push( new String( "3" ) );
	DLOGOBJECT( "filled: %s", target );
  }
  {
	DLOG( "Stack Testing: copy" );
	Stack *target;
	Stack *copy;
	Top *raw;
	target = new Stack();
	OGuard _target( target, this );
	DLOGOBJECT( "Created fresh: %s", target );
	target -> push( new String( "1" ) );
	target -> push( new String( "2" ) );
	target -> push( new String( "3" ) );
	DLOGOBJECT( "filled: %s", target );
	raw = target -> clone();
	copy = TCAST( raw, Stack );
	OGuard _copy( copy, this );
	DLOGOBJECT( "copy: %s", target );
  }
  return true;
}

#endif

END_QR_NAMESPACE

#if defined(_INLINE)
#include "../src/Debug.ipp"
#endif

/*
 * $Log: Stack.cpp,v $
 * Revision 1.1.1.1  2000/07/19 16:45:50  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:41  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:31  god
 * Imported sources
 *
 * Revision 1.2  1999/03/03 19:09:39  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.1  1999/02/28 16:30:02  philogelos
 * LayeredContainer added. Tuned for inlines.
 * */

