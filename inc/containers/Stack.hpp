// -*-C++-*- 

/*  inc/containers/Stack.hpp  */

/*
 * Author: Philogelos A. <Philogelos@yahoo.com>
 * Maintainer: Philogelos A.
 * Keywords: C++, library, containers
 *
 * Copyright (C) 1998 Philogelos A.
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



#ifndef __STACK_HPP__
#define __STACK_HPP__

/* $Id: Stack.hpp,v 1.1.1.1 2000/07/19 17:00:10 philogelos Exp $ */

#include "PuncturedContainer.hpp"
#include "ModifiableContainer.hpp"
#include "ContainerAdapter.hpp"
#include "MutableLayeredContainer.hpp"
#include "EmptyStack.hpp"
#include "PositionAdapter.hpp"
#include "defines.h"

BEGIN_QR_NAMESPACE

class List;
class FromTopOfStackPosition;
class FromBottomOfStackPosition;

/**
   Stack aka PDL aka LIFO.

   @author Philogelos
   @created
*/
class Stack : virtual public ModifiableContainer,
			  virtual public PuncturedContainer,
			  virtual public MutableLayeredContainer,
			  virtual public ContainerAdapter
{

friend FromTopOfStackPosition;
friend FromBottomOfStackPosition;

  /**
	 Creates empty stack.
   */
public: Stack();

  /**
	 Creates (shallow) copy of given stack.
   */
public: Stack( Stack &aSource );

  /**
	 Destroys this stack.
   */
public: virtual ~Stack();


public: virtual void push( Top *anElement );
public: virtual Top *pop() THROWS( EmptyStack * );
public: virtual void dup();
public: virtual void swap() THROWS( EmptyStack * );
public: virtual Top *exchange( Top *anElement ) THROWS( EmptyStack * );
public: virtual Top *top() const THROWS( EmptyStack * );

public: virtual PositionFactory *getDefaultPositionFactory() const;

public: virtual boolean isEmpty() const;
public: virtual PositionEnumeration *getEnumeration() const;
public: virtual MutablePositionEnumeration *getMutableEnumeration() const;
public: virtual Index getCardinality() const;
public: virtual boolean isValid( const Position *aPosition ) const;

  /**
	 Returns sequence containing all removable slots.
	 Empty sequence.
  */
public: virtual TypedEnumeration< RemovablePosition > *getRemovable() const;

public: virtual Position *getCurrentPunct() const;
public: virtual Position *getAlwaysPunct() const;

protected: virtual MutableContainer *getBaseMutableContainer() const;

  /**
	 Creates (shallow) copy of this stack.
   */
public:  virtual Top *clone() const;

  /**
   */
public:  virtual String  getClassName() const;

#if defined( TESTING )
boolean tester( int ) const;
#endif

protected: void init();
protected: List *elements;
};

abstract class StackPosition : virtual public PositionAdapter
{
public: StackPosition( const Stack *aHost, const Index anOffset );

public: Stack *getStack() const;
public: virtual boolean isValid () const;

protected: const Stack *stack;
protected: const Index offset;
};

class FromTopOfStackPosition : public StackPosition
{
public: FromTopOfStackPosition( const Stack *aHost, const Index anOffset );

public:  virtual Top *getValue() const;
};

class FromBottomOfStackPosition : public StackPosition
{
public: FromBottomOfStackPosition( const Stack *aHost, const Index anOffset );

public:  virtual Top *getValue() const;
};

END_QR_NAMESPACE

/*
 * $Log: Stack.hpp,v $
 * Revision 1.1.1.1  2000/07/19 17:00:10  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:34  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:45  god
 * Imported sources
 *
 * Revision 1.2  1999/03/03 19:09:13  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.1  1999/02/28 13:04:33  philogelos
 * Added Files:
 * 	EmptyContainer.hpp EmptyStack.hpp LayeredContainer.hpp
 * 	MutableLayeredContainer.hpp PuncturedContainer.hpp Stack.hpp
 * 	TextContainer.hpp ValuePosition.hpp
 * Removed Files:
 * 	Modifier.hpp
 * */

/* __STACK_HPP__ */
#endif
