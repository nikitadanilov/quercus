// -*-C++-*- 

/*  src/containers/lists/List.cpp  */


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


/* $Id: List.cpp,v 1.4 2001/06/09 14:52:37 philogelos Exp $ */
#if !defined(_INLINE)
static char cvsid[] = "@(#)$Id: List.cpp,v 1.4 2001/06/09 14:52:37 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif


#include "CRef.hpp"
#include "Debug.hpp"
#include "ObjectWrapper.hpp"
#include "StringBuffer.hpp"
#include "LinkManager.hpp"
#include "OGuard.hpp"
#include "PGuard.hpp"
#include "containers/lists/List.hpp"
#include "platform/threads/Thread.hpp"
#include "containers/lists/ListNode.hpp"
#include "containers/lists/ListNodeFactory.hpp"
#include "containers/lists/DefaultListNodeFactory.hpp"
#include "containers/MutablePositionEnumeration.hpp"
#include "iter/enumerations/TypedEnumeration.hpp"
#include "iter/enumerations/EmptyEnumeration.hpp"

#include "containers/EmptyContainer.hpp"

BEGIN_QR_NAMESPACE

List::List()
{
  init();
  setNodeFactory( new DefaultListNodeFactory() );
}

List::List( List &aSource ) : 
  RangedContainer(),
  ModifiableContainer(),
  PuncturedContainer()
{
  Enumeration *en;
  PGuard _self( this, this );

  LGuard _source( ( const List * )&aSource, this );
  init();
  setNodeFactory( aSource.getNodeFactory() );

  en = aSource.getValueEnumeration();
  OGuard _en( en, this );

  while( en -> hasMoreElements() )
	{
	  append( en -> getNextElement() );
	}
  postC_( this -> equals( &aSource ) );
}

List::List( int aDummy, ... )
{
  va_list args;
  
  PGuard _self( this, this );

  init();
  setNodeFactory( new DefaultListNodeFactory() );
  
  va_start( args, aDummy );
  for( Top *element = va_arg( args, Top * ) ; element != NULL ;
	   element = va_arg( args, Top * ) )
	{
	  ObjectWrapper *shrinkWrap;

	  shrinkWrap = TCAST( element, ObjectWrapper );
	  OGuard _wrap( shrinkWrap, this, true );

	  append( shrinkWrap -> getValue() );
    }
  va_end( args );
}

List::~List()
{
  OGuard _this( this, this );
  clearAll();

  setCurrent( NIL );
  setTail( NIL );
  setHead( NIL );
  setNodeFactory( NIL );
}

Position *List::getCurrentPunct() const
{
  return getCurrentPosition();
}

Position *List::getAlwaysPunct() const
{
  return getPositionToCurrent();
}

void List::clearAll()
{
  OGuard _this( this, this );
  while( !isEmpty() )
	{
	  Top *king;

	  king = behead();
	  if( king != NULL )
		{
		  LinkManager::recycle( king );
		}
	}
}

TypedEnumeration< ListNode > *List::getNodeEnumeration() const
{
  if( isEmpty() )
	{
	  return TypedEnumeration< ListNode >::upcast( new EmptyEnumeration() );
	}
  else
	{
	  return new ListNodeEnumeration( getHead(), getTail() );
	}
}

TypedEnumeration< RemovablePosition > *List::getRemovable() const
{
  return TypedEnumeration< RemovablePosition >::upcast( getEnumeration() );
}

boolean List::isFirst() const
{
  return( getCurrent() == getHead() );
}

boolean List::isLast() const
{
  return( getCurrent() == getTail() );
}

boolean List::atEnd() const
{
  return( getCurrent() == NIL );
}

void List::next() THROWS( RangedContainer::AfterLast * )
{
  OGuard _( this, this );
  if( atEnd() )
	{
	  throw 
		new RangedContainer::AfterLast
		( "List::next() advances beyond the end of the list", null );
	}
  if( ! isLast() )
	{
	  setCurrent( getCurrent() -> getNext() );
	}
  else
	{
	  setCurrent( NIL );
	}
}

void List::prev() THROWS( RangedContainer::BeforeFirst * )
{
  OGuard _( this, this );
  if( isFirst() )
	{
	  throw 
		new RangedContainer::BeforeFirst
		( "List::prev() moves beyond the beginning of the list", 
						 null );
	}
  setCurrent( getCurrent() -> getPrev() );
}

Top *List::getCurrentValue() THROWS( RangedContainer::AfterLast * )
{
  OGuard _( this, this, true );
  if( atEnd() )
	{
	  throw new RangedContainer::AfterLast
		( "List::getCurrentValue() requests value after the end of the list", 
		  null );
	}
  return getCurrent() -> getValue();
}

Top *List::setCurrentValue( Top *aNewValue ) 
  THROWS( RangedContainer::AfterLast * )
{
  OGuard _( this, this );
  Top *oldValue;

  if( atEnd() )
	{
	  throw new RangedContainer::AfterLast
		( "List::setCurrentValue() requests value after the end of the list", 
		  null );
	}
  oldValue = getCurrentValue();
  OGuard _oldValue( oldValue, this );
  getCurrent() -> setValue( aNewValue );
  return oldValue;
}

void List::toFirst()
{
  OGuard _( this, this );
  setCurrent( getHead() );
  postC_( isFirst() );
}

void List::toLast()
{
  OGuard _( this, this );
  setCurrent( getTail() );
  postC_( isLast() );
}

Index List::length() const
{
  OGuard _( this, this, true );
  Index len;

  if( isEmpty() )
	{
	  return 0;
	}
  len = 1;
  for( ListNode *spot = getHead() ; 
	   spot != getTail() ;
	   spot = spot -> getNext() )
	{
	  ++len;
	}
  return len;
}

Top *List::car() const THROWS( EmptyContainer * )
{
  OGuard _( this, this, true );
  if( isEmpty() )
	{
	  throw 
		new EmptyContainer( "List::car() of empty list", 
							 null );
	  RET_THROW( NULL );
	}
  else
	{
	  test_( getHead() != nil );
	  return( getHead() -> getValue() );
	}
}

List *List::cdr() THROWS( EmptyContainer * )
{
  OGuard _( this, this, true );
  if( isEmpty() )
	{
	  throw 
		new EmptyContainer( "List::cdr() of empty list", 
							 null );
	  RET_THROW( NULL );
	}
  else
	{
	  List *cdrCopy;
	  Enumeration *en;
	  boolean firstElement;

	  cdrCopy = new List();
	  PGuard _cdrCopy( cdrCopy, this );

	  en = getValueEnumeration();
	  OGuard _en( en, this );
	  
	  firstElement = true;
	  while( en -> hasMoreElements() )
		{
		  Top *value;
		  
		  value = en -> getNextElement();
		  OGuard _value( value, this );

		  if( ! firstElement )
			{
			  cdrCopy -> append( value );
			}
		  else
			{
			  firstElement = false;
			}
		}
	  cdrCopy -> toFirst();
	  return cdrCopy;
	}
}

List *List::map( Map *aMap )
{
  OGuard _this( this, this, true );
  OGuard _aMap( ( Top * ) aMap, ( Top * ) this );

  List *mapped;
  Enumeration *en;

  mapped = new List();
  PGuard _mapped( mapped, this );

  en = getValueEnumeration();
  OGuard _en( en, this );

  while( en -> hasMoreElements() )
	{
	  Top *value;

	  value = en -> getNextElement();
	  OGuard _value( value, this );
	  mapped -> append( aMap -> apply( value ) );
	}
  mapped -> toFirst();
  return mapped;
}

List *List::append( Top *aValue )
{
  appendNode( getNewNode( aValue ) );
  return this;
}

List *List::prepend( Top *aValue )
{
  prependNode( getNewNode( aValue ) );
  return this;
}

void List::insert( Top *aValue )
{
  insertNode( getNewNode( aValue ) );
}

Top *List::behead() THROWS( EmptyContainer * )
{
  OGuard _( this, this );
  if( isEmpty() )
	{
	  throw 
		new EmptyContainer( "List::behead() of empty list", 
							null );
	}
  Top *headValue;

  headValue = car();
  PGuard _headValue( headValue, this );

  if( getHead() == getTail() )
	{
	  setCurrent( NIL );
	  setTail( NIL );
	  setHead( NIL );
	}
  else
	{
	  if( isFirst() )
		{
		  next();
		}

	  OGuard _head( getHead(), this );
	  
	  setHead( getHead() -> getNext() );
	  getHead() -> getPrev() -> setNext( NIL );
	  getHead() -> setPrev( NIL );
	}
  return headValue;
}

Top *List::betail() THROWS( EmptyContainer * )
{
  OGuard _( this, this );
  if( isEmpty() )
	{
	  throw 
		new EmptyContainer( "List::betail() of empty list", 
							null );
	}
  Top *tailValue;

  tailValue = getTail() -> getValue();
  PGuard _tailValue( tailValue, this );

  if( isLast() && isFirst() )
	{
	  setCurrent( NIL );
	  setTail( NIL );
	  setHead( NIL );
	}
  else
	{
	  if( isLast() )
		{
		  prev();
		}

	  OGuard _tail( getTail(), this );
	  
	  setTail( getTail() -> getPrev() );
	  getTail() -> getNext() -> setPrev( NIL );
	  getTail() -> setNext( NIL );
	}
  return tailValue;
}

Top *List::remove() THROWS( RangedContainer::AfterLast * )
{
  Top *value;

  OGuard _( this, this );
  if( atEnd() )
	{
	  throw 
		new RangedContainer::AfterLast
		( "List::remove() after the last element of the list", null );
	}

  if( isFirst() )
	{
	  return( behead() );
	}
  if( isLast() )
	{
	  return( betail() );
	}
  else
	{
	  ListNode *oldCurrent;
	  value = getCurrentValue();
	  PGuard _value( value, this );

	  oldCurrent = getCurrent();
	  OGuard _current( oldCurrent, this );

	  next();
	  oldCurrent -> getPrev() -> setNext( oldCurrent -> getNext() );
	  oldCurrent -> getNext() -> setPrev( oldCurrent -> getPrev() );
	  oldCurrent -> setPrev( NIL );
	  oldCurrent -> setNext( NIL );
	  return value;
	}
}

ListNodeFactory *List::getNodeFactory() const
{
  return factory;
}

void List::setNodeFactory( ListNodeFactory *aFactory )
{
  FMOVE( factory, aFactory );
}

boolean List::isValidNode( const ListNode *aNode ) const
{
  //  List *self;

  //  self = ( List * ) this;
  //  LGuard _this( self, this );
  OGuard _this( this, this, true );
  if( isEmpty() )
	{
	  return( aNode == null );
	}

  ListNode *spot = getHead(); 
  while( true )
	{
	  if( spot == aNode )
		{
		  return true;
		}
	  if( spot == getTail() )
		{
		  break;
		}
	  test_( spot != ( ListNode * ) NIL );
	  spot = spot -> getNext();
	}

  //   for( self -> toFirst() ; !( self -> atEnd() ) ; self -> next() )
  // 	{
  // 	  if( ( self -> getCurrent() ) == aNode )
  // 		{
  // 		  return true;
  // 		}
  // 	}
  return false;
}

Index List::getLowBound() const
{
  return 0;
}

Index List::getHighBound() const
{
  return( length() );
}

void List::setCurrentAt( const Index anIndex )
{
  OGuard _this( this, this );
  preC_( isValidIndex( anIndex ) || ( anIndex == length() ) );

  Index i;

  for( toFirst(), i = 0 ; !atEnd() ; next(), ++i )
	{
	  if( i == anIndex )
		{
		  return;
		}
	}
  test_( anIndex == length() );
  test_( atEnd() );
}

Index List::getCurrentIndex() const
{
  LGuard _this( this, this );
  Index i;
  ListNode *oldCurrent;

  oldCurrent = getCurrent();
  for( ( ( List * ) this ) -> toFirst(), i = 0 ; 
	   !atEnd() ; 
	   ( ( List * ) this ) -> next(), ++i )
	{
	  if( oldCurrent == getCurrent() )
		{
		  return i;
		}
	}
  return getCardinality();
}

MutablePositionEnumeration *List::getMutableEnumeration() const
{
  return new ListEnumeration( ( List * ) this );
}

Top *List::getAt( const Index anIndex ) const
{
  preC_( ( getLowBound() <= anIndex ) && 
		 ( anIndex < getHighBound() ) );

  LGuard _this( this, this );
  List *pseudoThis;

  Index i;

  pseudoThis = ( List * ) this;
  for( pseudoThis -> toFirst(), i = 0 ; 
	   !( pseudoThis -> atEnd() ) ; 
	   pseudoThis -> next(), ++i )
	{
	  if( i == anIndex )
		{
		  return pseudoThis -> getCurrentValue();
		}
	}
  impossible_;
  return nil;
}

Top *List::setAt( const Index anIndex, Top *aNewValue )
{
  preC_( ( getLowBound() <= anIndex ) && 
		 ( anIndex < getHighBound() ) );

  LGuard _this( this, this );

  Index i;

  for( toFirst(), i = 0 ; !atEnd() ; next(), ++i )
	{
	  if( i == anIndex )
		{
		  return setCurrentValue( aNewValue );
		}
	}
  impossible_;
  return ( Top * ) nil;
}


PositionEnumeration *List::getEnumeration() const
{
  return( getMutableEnumeration() );
}

Index List::getCardinality() const
{
  return RangedContainer::getCardinality();
}

boolean List::isValid( const Position *aPosition ) const
{
  preC_( aPosition != ( Position * ) NULL );
  return( aPosition -> isValid() );
}


boolean List::isEmpty() const
{
  return( getHead() == nil );
}


ListPosition *List::getCurrentPosition() const 
  THROWS( RangedContainer::AfterLast * )
{
  if( atEnd() )
	{
	  throw new RangedContainer::AfterLast( "List::getCurrentPosition()", 
						   null );
	  RET_THROW( NULL );
	}
  else
	{
	  return new ListPosition( ( List * ) this, 
							   getCurrent() );
	}
}

ListCurrentPosition *List::getPositionToCurrent() const
{
  return new ListCurrentPosition( this );
}


PositionFactory *List::getDefaultPositionFactory() const
{
  return new ListCurrentFactory( this );
}

ListTailFactory *List::getTailFactory() const
{
  return new ListTailFactory( this );
}

ListHeadFactory *List::getHeadFactory() const
{
  return new ListHeadFactory( this );
}

ListCurrentFactory *List::getCurrentFactory() const
{
  return new ListCurrentFactory( this );
}

boolean List::equals( const Top *anOther ) const
{
  List *other;
  List *self;

  self = ( List * ) this;
  other = DCAST( anOther, List );
  if( other == nil )
	{
	  return false;
	}

  LGuard _we( self, this );
  LGuard _they( other, this );

  for( self -> toFirst(), other -> toFirst() ; 
	   ( ( !( self -> atEnd() ) ) && 
		 ( !( other -> atEnd() ) ) ) ; 
	   ( self -> next(), other -> next() ) )
	{
	  if( !( self -> getCurrentValue() 
			 -> equals( other -> getCurrentValue() ) ) )
		{
		  return false;
		}
	}
  return( ( self -> atEnd() ) && 
		  ( other -> atEnd() ) );
}

Top *List::clone() const
{
  return new List( * ( List * ) this );
}

String List::toString() const
{
  List *self;
  Index count;
  
  self = ( List * ) this;
  LGuard _( self, this );
  StringBuffer result( StringBuffer::defaultLength,
					   StringBuffer::defaultDelta );
  ListNode *savedCurrent;

  result.add( Object::toString().getUNIChars() );
  result.add( String( "( " ).getUNIChars() );

  savedCurrent = self -> getCurrent();
  count = 0;
  for( self -> toFirst() ; ! ( self -> atEnd() ) ; self -> next() )
	{
	  CRef< Top > item;

	  if( count > maxPrintCount )
		{
		  break;
		}
	  else if( count == maxPrintCount )
		{
		  result.add( String( " ... " ).getUNIChars() );
		  ++count;
		  break;
		}
	  else if( ( self -> getCurrent() ) != getHead() )
		{
		  result.add( String( ", " ).getUNIChars() );
		}
	  if( ( self -> getCurrent() ) == savedCurrent )
		{
		  result.add( String( "*" ).getUNIChars() );
		}
	  item = self -> getCurrentValue();
	  if( *item != NULL )
		{
		  result.add( item -> toString() );
		}
	  else
		{
		  result.add( String::nullLiteral );
		}
	  ++count;
	}
  result.add( String( ") " ).getUNIChars() );
  return result.asString();
}

boolean List::invariant() const
{
  return( Object::invariant() &&
		  ( equiv( getHead() == nil, getTail() == nil ) &&
			ergo( getHead() == nil, getCurrent() == nil ) &&
			isValidNode( getHead() ) &&
			isValidNode( getTail() ) &&
			ergo( !atEnd(), isValidNode( getCurrent() ) ) ) );
}

List::List( ListNode *aHead, ListNode *aTail, ListNode *aCurrent )
{
  init();
  setHead( aHead );
  setTail( aTail );
  setCurrent( aCurrent );
}

void List::init()
{
  head = ( ListNode * ) NIL;
  tail = ( ListNode * ) NIL;
  current = ( ListNode * ) NIL;
}

String List::getClassName() const
{
  return "List";
}

ListNode *List::getHead() const
{
  return head;
}

ListNode *List::getTail() const
{
  return tail;
}

ListNode *List::getCurrent() const
{
  return current;
}


void List::setHead( ListNode *aNode )
{
  FMOVE( head, aNode );
}

void List::setTail( ListNode *aNode )
{
  FMOVE( tail, aNode );
}

void List::setCurrent( ListNode *aNode )
{
  FMOVE( current, aNode );
}

ListNode *List::getNewNode( Top *aValue ) const
{
  preC_( getNodeFactory() != nil );
  ListNode *newNode;

  newNode = getNodeFactory() -> createListNode();
  test_( newNode != nil );
  // OGuard _newNode( newNode, this );

  newNode -> setValue( aValue );
  return newNode;
}


void List::appendNode( ListNode *aNode )
{
  preC_( aNode != nil );
  OGuard _node( aNode, this );

  preC_( ! isValidNode( aNode ) );
  OGuard _( this, this );

  if( isEmpty() )
	{
	  setHead( aNode );
	  setTail( aNode );
	  setCurrent( aNode );
	}
  else
	{
	  getTail() -> setNext( aNode );
	  aNode -> setPrev( getTail() );
	  setTail( aNode );
	  // 	  if( atEnd() )
	  // 		{
	  // 		  toLast();
	  // 		}
	}
}

void List::prependNode( ListNode *aNode )
{
  preC_( aNode != nil );
  preC_( ! isValidNode( aNode ) );
  OGuard _( this, this );
  OGuard _node( aNode, this );

  if( isEmpty() )
	{
	  setHead( aNode );
	  setTail( aNode );
	  setCurrent( aNode );
	}
  else
	{
	  getHead() -> setPrev( aNode );
	  aNode -> setNext( getHead() );
	  setHead( aNode );
	}
}

void List::insertNode( ListNode *aNode ) THROWS( RangedContainer::AfterLast * )
{
  OGuard _( this, this );
  OGuard _node( aNode, this );

  preC_( aNode != nil );
  preC_( ! isValidNode( aNode ) );

  if( atEnd() )
	{
	  throw new 
		RangedContainer::AfterLast
		( "List::insertNode after the last element of the list", null );
	}

  if( isLast() )
	{
	  appendNode( aNode );
	  return;
	}
  
  test_( getCurrent() -> getNext() != nil );

  OGuard _current( getCurrent(), this );
  OGuard _next( getCurrent() -> getNext(), this );

  aNode -> setNext( getCurrent() -> getNext() );
  aNode -> setPrev( getCurrent() );

  getCurrent() -> getNext() -> setPrev( aNode );
  getCurrent() -> setNext( aNode );

}

#if defined( TESTING )

END_QR_NAMESPACE

#include "IdentityMap.hpp"
#include "containers/Stack.hpp"

BEGIN_QR_NAMESPACE

boolean List::tester( int ) const
{
  {
	DLOG( "List Testing: constructor" );
	List *target;
	target = new List();
	OGuard _target( target, this );
	DLOGOBJECT( "Created fresh: %s", target );
  }
  {
	DLOG( "List Testing: append" );
	List *target;
	target = new List();
	OGuard _target( target, this );
	DLOGOBJECT( "Created fresh: %s", target );
	target -> append( new String( "item" ) );
	DLOGOBJECT( "Appended item: %s", target );
  }
  {
	DLOG( "List Testing: car" );
	List *target;
	target = new List();
	OGuard _target( target, this );
	DLOGOBJECT( "Created fresh: %s", target );
	target -> append( new String( "item" ) );
	DLOGOBJECT( "Appended item: %s", target );
	DLOGOBJECT( "car: %s", target -> car() );
  }
  {
	DLOG( "List Testing: behead" );
	List *target;
	Top  *hd;

	target = new List();
	OGuard _target( target, this );
	DLOGOBJECT( "Created fresh: %s", target );
	target -> append( new String( "item" ) );
	DLOGOBJECT( "Appended item: %s", target );
	hd = target -> behead();
	OGuard _head( hd, this );
	DLOGOBJECT( "Behead: %s", hd );
	DLOGOBJECT( "Result: %s", target );
	if( !( target -> isEmpty() ) )
	  {
		DLOG( "cdr( e ) != nil" );
		return false;
	  }
  }
  {
	DLOG( "List Testing: car cdr" );
	List *target;
	Top  *hd;
	List *rest;

	target = new List();
	OGuard _target( target, this );
	DLOGOBJECT( "Created fresh: %s", target );
	target -> append( new String( "item" ) );
	DLOGOBJECT( "Appended item: %s", target );

	hd = target -> car();
	OGuard _head( hd, this );

	DLOGOBJECT( "car: %s", hd );

	rest = target -> cdr();
	OGuard _rest( rest, this );
	DLOGOBJECT( "cdr: %s", rest );

	rest -> prepend( hd );
	if( !( target -> equals( rest ) ) )
		{
		  DLOG( "this != car + cdr" );
		  return false;
		}
  }
  {
	DLOG( "List Testing: cdr misc" );
	List *target;
	List *cdred;

	target = new List();
	OGuard _target( target, this );
  
	target -> append( new Object() );
	DLOGOBJECT( target );
  
	target -> append( new String( "#" ) );
	DLOGOBJECT( target );
  
	target -> prepend( new String( "!" ) );
	DLOGOBJECT( target );
  
	FINIT( cdred, target );
	while( ! cdred -> isEmpty() )
	  {
		List *newCdr;
		
		newCdr = cdred -> cdr();
		FDONE( cdred );
		FINIT( cdred, newCdr );
		DLOGOBJECT( cdred );
	  }
	FDONE( cdred );
	
	Enumeration *en;

	en = target -> getValueEnumeration();
	OGuard _en( en, this );
	while( en -> hasMoreElements() )
	  {
		target -> prepend( en -> getNextElement() );
	  }
	DLOGOBJECT( target );
  }
  {
	DLOG( "List Testing: copy remove append" );
	List *target;
	List *copy;
	target = new List();
	OGuard _target( target, this );
	
	DLOGOBJECT( "Created fresh: %s", target );
	for( int i = 0 ; i < 10 ; ++i )
	  {
		target -> append( new String( i, 10 ) );
	  }
	DLOGOBJECT( "Filled: %s", target );

	copy = new List( *target );
	OGuard _copy( copy, this );
	DLOGOBJECT( "Copy: %s", copy );

	target -> toFirst();
	for( int j = 0 ; j < 10 ; ++j )
	  {
		target -> append( target -> remove() );
	  }
	DLOGOBJECT( "Mixed: %s", target );
	if( !( copy -> equals( target ) ) )
	  {
		DLOG( "Mixed != original" );
		return false;
	  }
  }
  {
	DLOG( "List Testing: insert" );
	List *target;

	target = new List();
	OGuard _target( target, this );
	
	DLOGOBJECT( "Created fresh: %s", target );
	for( int i = 0 ; i < 10 ; ++i )
	  {
		target -> append( new String( i, 10 ) );
	  }
	DLOGOBJECT( "Filled: %s", target );

	target -> toFirst();
	target -> insert( new String( "inserted at head" ) );
	DLOGOBJECT( "Result: %s", target );

	target -> toLast();
	target -> insert( new String( "inserted at last" ) );
	DLOGOBJECT( "Result: %s", target );
  }
  {
	DLOG( "List Testing: map" );
	List *target;

	target = new List();
	OGuard _target( target, this );

	DLOGOBJECT( "Created fresh: %s", target );

	for( int i = 0 ; i < 10 ; ++i )
	  {
		target -> append( new String( i, 10 ) );
	  }
	DLOGOBJECT( "Filled: %s", target );
	if( !( target -> equals( target -> map( new IdentityMap() ) ) ) )
	  {
		DLOG( "map(id) != this" );
		return false;
	  }
  }
  {
	DLOG( "List Testing: getAt length" );
	List *target;

	target = new List();
	OGuard _target( target, this );

	DLOGOBJECT( "Created fresh: %s", target );

	int i;
	for( i = 0 ; i < 10 ; ++i )
	  {
		target -> append( new String( i, 10 ) );
	  }
	DLOGOBJECT( "Filled: %s", target );
	i = 0;
	target -> toFirst(); 
	while( !( target -> atEnd() ) )
	  {
		if( !( target -> getAt( i ) -> equals( target -> getCurrentValue() ) ) )
		  {
			DLOG( "Current != list[ i ]" );
			return false;
		  }
		++i;
		target -> next();
	  }
	if( i != target -> length() )
	  {
		DLOG( "Wrong length!" );
		return false;
	  }
  }
  {
	DLOG( "List Testing: setAt" );
	List *matrix;
	List *target;

	matrix = new List();
	OGuard _matrix( matrix, this );

	target = new List();
	OGuard _target( target, this );

	int i;
	for( i = 0 ; i < 10 ; ++i )
	  {
		String *item = new String( i, 10 );
		target -> append( item );
		matrix -> prepend( item );
	  }
	DLOGOBJECT( "target Filled: %s", target );
	DLOGOBJECT( "matrix Filled: %s", matrix );

	for( i = 0 ; i < ( matrix -> length() ) ; ++i )
	  {
		target -> setAt( i, matrix -> getAt( i ) );
	  }
	DLOGOBJECT( "result: %s", target );
	if( !( matrix -> equals( target ) ) )
	  {
		DLOG( "Wrong setAt behavior!" );
		return false;
	  }
  }
  {
	DLOG( "List Testing: isValidNode" );
	List *target;

	target = new List();
	OGuard _target( target, this );

	DLOGOBJECT( "Created fresh: %s", target );

	for( int i = 0 ; i < 10 ; ++i )
	  {
		target -> append( new String( i, 10 ) );
	  }
	DLOGOBJECT( "Filled: %s", target );
	for( target -> toFirst() ; !( target -> atEnd() ) ; target -> next() )
	  {
		if( !( target -> isValidNode( target -> getCurrent() ) ) )
		  {
			DLOG( "Current is invalid!" );
			return false;
		  }
	  }
  }
  {
	DLOG( "List Testing: ... constructor" );
	List *target;

	target = new List( 1, 
					   OW( new Object() ), 
					   OW( new String( "string" ) ), 
					   OW( new List() ), OW( new Stack() ), 
					   OW( new String( "end" ) ), 
					   nil );
	OGuard _target( target, this );

	DLOGOBJECT( "Created: %s", target );
	} 
  return true;
}
#endif

ListNodeEnumeration::ListNodeEnumeration( ListNode *aFrom, ListNode *aTo )
{
  OGuard _( this, this );

  FNNINIT( first, aFrom );
  FNNINIT( last, aTo );

  reset();
}

ListNodeEnumeration::~ListNodeEnumeration()
{
  FDONE( first );
  FDONE( last );
}

ListNode *ListNodeEnumeration::getNextTypedElement()
{
  OGuard _( this, this );

  ListNode *value;

  value = current;
  current = current -> getNext();
  postC_( current != nil );
  return value;
}

Top *ListNodeEnumeration::getNextElement()
{
  return TypedEnumeration< ListNode >::getNextElement();
}

boolean ListNodeEnumeration::hasMoreElements()
{
  return( current -> getNext() != nil );
}

void ListNodeEnumeration::reset()
{
  OGuard _( this, this );

  while( !isAtBeginning() )
	{
	  current = current -> getPrev();
	}
  postC_( isAtBeginning() );
}

Top *ListNodeEnumeration::getPrevElement()
{
  preC_( !isAtBeginning() );

  current = current -> getPrev();
  return current;
}
  
boolean ListNodeEnumeration::isAtBeginning()
{
  return( current -> getPrev() == nil );
}

void ListNodeEnumeration::ff()
{
  OGuard _( this, this );

  while( hasMoreElements() )
	{
	  current = current -> getNext();
	}
  postC_( !hasMoreElements() );
}

LGuard::LGuard( const List *aTarget, const Top *anOwner ) :
  OGuard( aTarget, anOwner ),
  list( ( List * ) aTarget ),
  savedCurrent( aTarget -> getCurrent() )
{}

LGuard::~LGuard()
{
  if( list -> isValidNode( savedCurrent ) )
	{
	  list -> setCurrent( savedCurrent );
	}
}


ListPosition::ListPosition( List *aContainer, ListNode *aNode ) :
  PositionAdapter( aContainer )
{
  FNNINIT( node, aNode );
}

ListPosition::~ListPosition()
{
  FDONE( node );
}

Top *ListPosition::setValue( Top *aNewValue )
{
  OGuard _( this, this );

  preC_( isValid() );
  Top *oldValue;

  oldValue = node -> getValue();

  PGuard _oldValue( oldValue, this );
  node -> setValue( aNewValue );
  return oldValue;
}

boolean   ListPosition::isValid() const
{
  OGuard _( this, this );

  preC_( DCAST( getContainer(), List ) != nil );
  return( DCAST( getContainer(), List ) -> isValidNode( node ) );
}

Top *ListPosition::getValue() const
{
  OGuard _( this, this );

  preC_( isValid() );
  return( node -> getValue() );
}

void ListPosition::remove()
{
  OGuard _self( this, this );
  OGuard _container( getContainer(), this );

  preC_( isValid() );

  List *list;

  list = DCAST( getContainer(), List );
  OGuard _list( list, this );

  if( node == list -> getCurrent() )
	{
	  list -> remove();
	}
  else
	{
	  LGuard _listSetBack( list, this );
	  list -> setCurrent( node );
	  list -> remove();
	}
  postC_( !isValid() );
}

ListEnumeration::ListEnumeration( List *aList )
{
  FNNINIT( list, aList );

  current = list -> getHead();
  if( current != NIL )
	{
	  OREG( current );
	}
}

ListEnumeration::~ListEnumeration()
{
  FCDONE( current );
  FDONE( list );
}

MutablePosition *ListEnumeration::getNextMutablePosition() THROWS( InvalidArgument * )
{
  OGuard _( this, this );
  LGuard( list, this );

  if( ! ( list -> isValidNode( current ) ) )
	{
	  throw new InvalidArgument( madeInvalid, null );
	  RET_THROW( NULL );
	}
  else
	{
	  ListNode *oldCurrent;

	  oldCurrent = current;

	  list -> setCurrent( current );
	  test_( ! ( list -> atEnd() ) );
	  list -> next();
	  current = list -> getCurrent();
	  LinkManager::move( this, oldCurrent, current );
	  return new ListPosition( list, oldCurrent );
	}
}

boolean ListEnumeration::hasMoreElements() THROWS( InvalidArgument * )
{
  OGuard _( this, this );
  LGuard _list( list, this );

  if( current == ( ListNode * ) NIL )
	{
	  return false;
	}

  if( ! ( list -> isValidNode( current ) ) )
	{
	  throw new InvalidArgument( madeInvalid, null );
	  RET_THROW( NULL );
	}
  else
	{
	  list -> setCurrent( current );
	  return( ! ( list -> atEnd() ) );
	}
}

String ListEnumeration::madeInvalid( "List was modified and made this enumeration invalid", 
									 false );

ListCurrentPosition::ListCurrentPosition( const List *aContainer ) :
  PositionAdapter( ( Container * ) aContainer )
{}

ListCurrentPosition::~ListCurrentPosition()
{}

Top *ListCurrentPosition::setValue( Top *aNewValue )
{
  OGuard _( this, this );

  preC_( isValid() );
  return DCAST( getContainer(), List ) -> setCurrentValue( aNewValue );
}

boolean ListCurrentPosition::isValid () const
{
  return ! ( DCAST( getContainer(), List ) -> atEnd() );
}

Top *ListCurrentPosition::getValue() const
{
  OGuard _( this, this );

  preC_( isValid() );
  return DCAST( getContainer(), List ) -> getCurrentValue();
}


ListPositionFactory::ListPositionFactory( const List *aList )
{
  FNNINIT( list, ( List * ) aList );
}

ListPositionFactory::~ListPositionFactory()
{
  FDONE( list );
}

MutablePosition *ListPositionFactory::createPosition()
{
  return createListPosition();
}

ListTailFactory::ListTailFactory( const List *aList ) :
  ListPositionFactory( aList )
{}

ListPosition *ListTailFactory::createListPosition()
{
  LGuard _list( list, ( Top * ) this );
  ListPosition *lastPosition;

  list -> append( nil );
  list -> toLast();

  lastPosition = list -> getCurrentPosition();
  return lastPosition;
}

ListHeadFactory::ListHeadFactory( const List *aList ) :
  ListPositionFactory( aList )
{}

ListPosition *ListHeadFactory::createListPosition()
{
  LGuard _list( list, this );
  ListPosition *firstPosition;

  list -> prepend( nil );
  list -> toFirst();

  firstPosition = list -> getCurrentPosition();
  return firstPosition;
}


ListCurrentFactory::ListCurrentFactory( const List *aList ) :
  ListPositionFactory( aList )
{}

ListPosition *ListCurrentFactory::createListPosition()
{
  OGuard _list( list, this );
  ListPosition *currentPosition;

  if( ( list -> isEmpty() ) ||
	  ( list -> atEnd() ) )
	{
	  list -> append( nil );
	  list -> toLast();
	}
  else
	{
	  list -> insert( nil );
	  list -> next();
	}

  currentPosition = list -> getCurrentPosition();
  return currentPosition;
}

#if defined( USE_PER_CLASS_NEW )

END_QR_NAMESPACE
#include "FixedSizeAllocator.hpp"
BEGIN_QR_NAMESPACE

INLINE void *ListPosition::operator new( size_t size )
{
  return getAllocator() -> allocate( ( Index ) size );
}

INLINE void ListPosition::operator delete( void *anAddress )
{
  getAllocator() -> deallocate( anAddress );
}

MemoryAllocator *ListPosition::getAllocator()
{
  if( allocator == ( MemoryAllocator * ) NIL )
	{
	  allocator = new FixedSizeAllocator( sizeof( ListPosition ), 10, 
										  "ListPosition" );
	}
  return allocator;
}

MemoryAllocator *ListPosition::allocator = ( MemoryAllocator * ) NIL;

#endif

END_QR_NAMESPACE

#if defined(_INLINE)
#include "../src/Debug.ipp"
#endif

/*
 * $Log: List.cpp,v $
 * Revision 1.4  2001/06/09 14:52:37  philogelos
 * detect null element in List::toString()
 *
 * Revision 1.3  2001/04/16 10:43:38  philogelos
 * Excessive casts of NULL/NIL removed
 *
 * Revision 1.2  2000/09/21 18:05:09  philogelos
 * error in clearAll() corrected (can cope with NULL elements now)
 *
 * Revision 1.1.1.1  2000/07/19 16:46:50  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.3  2000/04/29 15:27:35  god
 * read-only locking where possible
 *
 * Revision 1.2  2000/04/09 11:29:42  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:33  god
 * Imported sources
 *
 * Revision 1.5  1999/05/22 13:00:54  philogelos
 * Merging sources back from SPARC
 *
 * Revision 1.4  1999/03/03 19:09:41  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.3  1999/02/28 16:30:36  philogelos
 * Tuned for inlines.
 *
 * Revision 1.2  1998/12/01 16:23:59  philogelos
 * (getHighBound): corrected to return length(), copy constructor added, (equals): rewind other list to head, (List::List): locks this through PGuard, (behead): lock retrieved head during method execution, (betail): lock retrieved tail during method execution, (behead): lock head trough PGuard, (clearAll): memory leak corrected: recycle heads, remove): lock result through PGuard (rather than OGuard), (invariant): refined: getCurrent() have to be valid only if we are not at the end,	(tester): new tests added
 *
 * Revision 1.1.1.1  1998/11/25 20:11:03  philogelos
 * Quercus Robusta
 * */
