// -*-C++-*- 

/*  inc/containers/lists/List.hpp  */


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


#ifndef __LIST_HPP__
#define __LIST_HPP__

/* $Id: List.hpp,v 1.1.1.1 2000/07/19 17:00:34 philogelos Exp $ */

#include "OGuard.hpp"
#include "containers/PuncturedContainer.hpp"
#include "containers/RangedContainer.hpp"
#include "containers/PositionAdapter.hpp"
#include "containers/PositionFactory.hpp"
#include "containers/MutablePosition.hpp"
#include "containers/RemovablePosition.hpp"
#include "containers/MutablePositionEnumeration.hpp"
#include "containers/MutableContainerAdapter.hpp"
#include "containers/ModifiableContainer.hpp"
#include "VersionedObject.hpp"
#include "iter/enumerations/TypedEnumeration.hpp"
#include "iter/enumerations/ECursor.hpp"
#include "defines.h"

#if defined( USE_PER_CLASS_NEW )
#include "MemoryAllocator.hpp"
#endif

#include <stdarg.h>

BEGIN_QR_NAMESPACE

class LGuard;
class ListEnumeration;
class ListPosition;
class ListCurrentPosition;

class EmptyContainer;

interface Top;
interface ListNode;
interface ListNodeFactory;
interface ListTailFactory;
interface ListHeadFactory;
interface ListCurrentFactory;

/**
   Double linked list.

   @author Philogelos
   @created Птн 25 Сен 1998 17:15:46
*/
class List : public RangedContainer,
			 public ModifiableContainer,
			 public PuncturedContainer,
			 public virtual MutableContainerAdapter,
			 public virtual Object
{

friend LGuard;
friend ListEnumeration;
friend ListPosition;

  /**
	 Creates empty list with
	 default node factory.

	 @see DefaultListNodeFactory
	*/
public: List();

  /**
	 Creates copy of given list.
  */
public: List( List &aSource );

public: List( int aDummy, ... );
  
  /**
	 Destroys this list
	 freeing all its elements.
  */
public: virtual ~List();

public: virtual Position *getCurrentPunct() const;
public: virtual Position *getAlwaysPunct() const;

  /**
	 Frees all elements, 
	 making this list empty.
  */
public: virtual void clearAll();


  /**
	 Returns enumeration of all nodes of this list.
  */
public: virtual TypedEnumeration< ListNode > *getNodeEnumeration() const;


  /**
	 Returns enumeration of all removable positions.
  */
public: virtual TypedEnumeration< RemovablePosition > *getRemovable() const;

  /**
	 True iff current slot is the first slot
	 in the list.
  */
public: virtual boolean isFirst() const;

  /**
	 True iff current slot is the last slot
	 in the list.
  */
public: virtual boolean isLast() const;

  /**
	 True iff current slot is just after the
	 last slot in the list.
  */
public: virtual boolean atEnd() const;

  /**
	 Moves current slot to next node.

	 @precond( !atEnd() )
  */
public: virtual void next() THROWS( RangedContainer::AfterLast * );

  /**
	 Moves current slot one
	 node backward.

	 @precond( !isFirst() )
  */
public: virtual void prev() THROWS( RangedContainer::BeforeFirst * );

  /**
	 Returns value of the current
	 slot.

	 @precond( !atEnd() )
  */
public: virtual Top *getCurrentValue() THROWS( RangedContainer::AfterLast * );

  /**
	 Installs value in the current slot

	 @precond( !atEnd() )
  */
public: virtual Top *setCurrentValue( Top *aNewValue ) 
  THROWS( RangedContainer::AfterLast * );


  /**
	 Moves current slot to the first
	 node.

	 @postcond( isFirst() )
  */
public: virtual void toFirst();

  /**
	 Moves current slot to the last
	 node.

	 @postcond( isLast() )
  */
public: virtual void toLast();


  /**
	 Returns length (number of elements)
	 of this list.
  */
public: virtual Index length() const;


  /**
	 Returns value of the first
	 slot in list.
  */
public: virtual Top  *car() const THROWS( EmptyContainer * );

  /**
	 Creates and returns new list
	 containing all but the first
	 elements of this list.
  */
public: virtual List *cdr() THROWS( EmptyContainer * );

  /**
	 Creates and returns new list
	 with elements produced by
	 ::apply()ing given map
	 to this list.
  */
public: virtual List *map( Map *aMap );

  /**
	 Appends new slot filled with
	 given value to the end of the list.
	 
	 Current slot is not changed.
  */
public: virtual List *append( Top *aValue );

  /**
	 Prepends new slot filled with
	 given value to the beginning of the list.
	 
	 Current slot is not changed.
  */
public: virtual List *prepend( Top *aValue );

  /**
	 Inserts new slot filled with
	 given value just after the 
	 current slot.
	 
	 Current slot is not changed.
  */
public: virtual void insert( Top *aValue );

  /**
	 Cuts and returns first element
	 of this list.

	 @precond( !isEmpty() );
  */
public: virtual Top *behead() THROWS( EmptyContainer * );

  /**
	 Cuts and returns last element
	 of this list.

	 @precond( !isEmpty() );
  */
public: virtual Top *betail() THROWS( EmptyContainer * );

  /**
	 Removes current slot.
	 Current is moved to the next slot
	 (possibly to the `end' position).
  */
public: virtual Top *remove() THROWS( RangedContainer::AfterLast * );


  /**
	 Returns true iff aNode belongs to
	 this list. If list is empty,
	 the only valid node is nil.
  */
public: virtual boolean isValidNode( const ListNode *aNode ) const;


  /**
	 Returns node factory, associated with 
	 this list. Node factory used to create
	 new nodes during insert/append/prepend
	 operations.
  */
public: virtual ListNodeFactory *getNodeFactory() const;

  /**
	 Installs node factory to create
	 new nodes during insert/append/prepend
	 operations.
  */
public: virtual void setNodeFactory( ListNodeFactory *aFactory );


  /**
	 Returns 0 as Lists are zero-based.
  */
public: virtual Index getLowBound() const;

  /**
	 Returns ( length() - 1 ) as Lists are 
	 zero-based.
  */
public: virtual Index getHighBound() const;

public: virtual void setCurrentAt( const Index anIndex );
public: virtual Index getCurrentIndex() const;

  /**
	 Returns enumeration of mutable positions
	 within this list.
  */
public: virtual MutablePositionEnumeration *getMutableEnumeration() const;


  /**
	 Returns an element at given zero-based offset.

	 @precond( ( getLowBound() <= anIndex ) && 
               ( anIndex < getHighBound() ) )
  */
public: virtual Top *getAt( const Index anIndex ) const;

  /**
	 Installs the value of slot at given zero-based offset.
	 Old value returned.

	 @precond( ( getLowBound() <= anIndex ) && 
               ( anIndex < getHighBound() ) )
  */
public: virtual Top *setAt( const Index anIndex, Top *aNewValue );


  /**
	 Returns true iff list is empty, i.e.,
	 contains no elements.
  */
public: virtual boolean isEmpty() const;


  /**
	 Returns enumeration of positions
	 within this list.
  */
public: virtual PositionEnumeration *getEnumeration() const;


  /**
	 Returns number of elements in this list.
  */
public: virtual Index getCardinality() const;

  /**
	 Checks that given position is in fact 
	 valid position within this list.
  */
public: virtual boolean isValid( const Position *aPosition ) const;


  /**
	 Returns position denoting
	 current slot of this list at the
	 moment of the call.
  */
public: virtual ListPosition *getCurrentPosition() const 
  THROWS( RangedContainer::AfterLast * );

  /**
	 Returns special position always denoting 
	 the current slot in this list.
  */
public: virtual ListCurrentPosition *getPositionToCurrent() const;


  /**
	 Returns position factory object for this
	 list.
  */
public: virtual PositionFactory *getDefaultPositionFactory() const;

  /**
	 Creates and returns position factory object
	 that produces positions denoting new slots
	 at the very end of this list.
  */
public: virtual ListTailFactory *getTailFactory() const;

  /**
	 Creates and returns position factory object
	 that produces positions denoting new slots
	 at the very beginning of this list.
  */
public: virtual ListHeadFactory *getHeadFactory() const;

  /**
	 Creates and returns position factory object
	 that produces positions denoting new slots
	 just after current slot and makes them
	 current.
  */
public: virtual ListCurrentFactory *getCurrentFactory() const;


  /**
	 Compares two lists element-by-element,
	 uses ::equals() to compare each pair of 
	 elements.
  */
public: virtual boolean equals( const Top *anOther ) const;

  /**
	 Creates and returns (shallow) copy of this list.
  */
public: virtual Top *clone() const;

  /**
	 Returns string representation of this
	 list in the form: 
	 ( element_0, ... , *current_element, ... , last_element )
	 where ::toString() used to render each element.
  */
public: virtual String  toString() const;

  /**
	 Returns ``List''
  */
public: virtual String  getClassName() const;
public: virtual boolean invariant() const;

#if defined( TESTING )
public: virtual boolean tester( int aParam ) const;
#endif


  /**
	 Initializes new object by given values
  */
protected: List( ListNode *head, ListNode *tail, ListNode *current );

  /**
	 Sets head, tail and current to nil.
  */
protected: void init();

  
  /**
	 Returns first node.
  */
protected: ListNode *getHead() const;
  
  /**
	 Returns last node.
  */
protected: ListNode *getTail() const;
  
  /**
	 Returns current node.
  */
protected: ListNode *getCurrent() const;


  /**
	 Installs given node as first
	 node of this list.
  */
protected: void setHead( ListNode *aNode );

  /**
	 Installs given node as last
	 node of this list.
  */
protected: void setTail( ListNode *aNode );

  /**
	 Installs given node as current
	 node of this list.
  */
protected: void setCurrent( ListNode *aNode );


  /**
	 Creates new node (using node factory)
	 and initializes it with given value.

	 @see #getNodeFactory
  */
protected: ListNode *getNewNode( Top *aValue ) const;


  /**
	 Appends given node to the end of the list.

	 @see #append
  */
protected: void appendNode( ListNode *aNode );

  /**
	 Prepends given node to the beginning of the list.

	 @see #prepend
  */
protected: void prependNode( ListNode *aNode );

  /**
	 Inserts given node just after the current
	 node.

	 @see #insert
  */
protected: void insertNode( ListNode *aNode ) 
  THROWS( RangedContainer::AfterLast * );


  /**
	 Returns current node (slot)
	 
	 @see #getCurrent
  */
protected: ListNode *current;


  /**
	 Returns first node (slot)
	 
	 @see #getHead
  */
protected: ListNode *head;

  /**
	 Returns last node (slot)
	 
	 @see #getTail
  */
protected: ListNode *tail;


  /**
	 Returns node factory object
	 
	 @see #getNodeFactory
  */
protected: ListNodeFactory *factory;

};

/**
   Subclass of OGuard tailored to work with
   lists. In addition to normal OGuard locking
   scheme it also restores initial 
   ``current slot'' of the list in destructor.
*/
class LGuard : public OGuard
{
public: LGuard( const List *aTarget, const Top *anOwner );
public: virtual ~LGuard();
  
protected: List *list;
protected: ListNode *savedCurrent;
};

class ListPosition : public MutablePosition, 
					 public RemovablePosition,
					 public virtual PositionAdapter
{
public: ListPosition( List *aContainer, ListNode *aNode );
public: virtual ~ListPosition();

public: virtual Top *setValue( Top *aNewValue );

public: virtual boolean   isValid () const;
public: virtual Top *getValue() const;

public: virtual void remove();

protected: ListNode *node;

#if defined( USE_PER_CLASS_NEW )
public: void *operator new( size_t size );
public: void  operator delete( void *anAddress );
protected: static MemoryAllocator *getAllocator();
protected: static MemoryAllocator *allocator;
#endif
};

class ListNodeEnumeration : public ECursor, 
							public TypedEnumeration< ListNode >,
							public virtual Object
{
public: ListNodeEnumeration( ListNode *aFrom, ListNode *aTo );
public: virtual ~ListNodeEnumeration();
public: virtual ListNode *getNextTypedElement();
public: virtual Top *getNextElement();
public: virtual boolean hasMoreElements();
public: virtual void reset();
public: virtual Top *getPrevElement();
public: virtual boolean isAtBeginning();
public: virtual void ff();

protected: ListNode *first;
protected: ListNode *last;
protected: ListNode *current;
};

class ListEnumeration : public MutablePositionEnumeration,
						public virtual Object
{
public: ListEnumeration( List *aList );
public: virtual ~ListEnumeration();

public: virtual MutablePosition *getNextMutablePosition() THROWS( InvalidArgument * );
public: virtual boolean hasMoreElements() THROWS( InvalidArgument * );

protected: List *list;
protected: ListNode *current;

protected: static String madeInvalid;
};

class ListCurrentPosition : public MutablePosition, 
							public virtual PositionAdapter
{
public: ListCurrentPosition( const List *aContainer );
public: virtual ~ListCurrentPosition();

public: virtual Top *setValue( Top *aNewValue );

public:  virtual boolean isValid () const;
public:  virtual Top *getValue() const;
};

abstract class ListPositionFactory : public PositionFactory,
  public virtual Object
{
public: ListPositionFactory( const List *aList );
public: virtual ~ListPositionFactory();
public: virtual MutablePosition *createPosition();
public: virtual ListPosition    *createListPosition() = 0;

protected: List *list;
};

class ListTailFactory : public ListPositionFactory
{
public: ListTailFactory( const List *aList );
public: virtual ListPosition *createListPosition();
};

class ListHeadFactory : public ListPositionFactory
{
public: ListHeadFactory( const List *aList );
public: virtual ListPosition *createListPosition();
};

class ListCurrentFactory : public ListPositionFactory
{
public: ListCurrentFactory( const List *aList );
public: virtual ListPosition *createListPosition();
};


END_QR_NAMESPACE

/*
 * $Log: List.hpp,v $
 * Revision 1.1.1.1  2000/07/19 17:00:34  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:34  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:45  god
 * Imported sources
 *
 * Revision 1.5  1999/05/22 13:00:25  philogelos
 * Merging sources back from SPARC
 *
 * Revision 1.4  1999/03/03 19:09:15  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.3  1999/02/28 15:36:38  philogelos
 * Implements PuncturedCOntainer interface. Slightly changed some prototypes
 *
 * Revision 1.2  1998/12/01 16:17:40  philogelos
 * xomments added, tester compiled conditionally
 *
 * Revision 1.1.1.1  1998/11/25 20:11:06  philogelos
 * Quercus Robusta
 * */

/* __LIST_HPP__ */
#endif
