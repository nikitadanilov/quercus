// -*-C++-*- 

/*  inc/containers/Queue.hpp  */

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



#ifndef __QUEUE_HPP__
#define __QUEUE_HPP__

/* $Id: Queue.hpp,v 1.1.1.1 2000/07/19 16:59:47 philogelos Exp $ */

#include "PuncturedContainer.hpp"
#include "ModifiableContainer.hpp"
#include "ContainerAdapter.hpp"
#include "MutableLayeredContainer.hpp"
#include "EmptyContainer.hpp"
#include "PositionAdapter.hpp"
#include "defines.h"

BEGIN_QR_NAMESPACE

class List;

/**
   Queue (FIFO) container.

   @author Philogelos
   @created
*/
class Queue : virtual public ModifiableContainer,
			  virtual public MutableLayeredContainer,
			  virtual public ContainerAdapter
{

  /**
   */
public: Queue();

  /**
   */
public: virtual ~Queue();

public: virtual Top *get() THROWS( EmptyContainer * );
public: virtual void push( Top *anObject );
  
protected: virtual MutableContainer *getBaseMutableContainer() const;

public: virtual PositionFactory *getDefaultPositionFactory() const;

  /**
	 Returns enumeration of all removable positions.
	 Empty sequence for queue.
  */
public: virtual TypedEnumeration< RemovablePosition > *getRemovable() const;

  /**
   */
public:  virtual String  getClassName() const;

protected: List *elements;

#if defined( TESTING )
public: boolean tester( int ) const;
#endif
};


END_QR_NAMESPACE

/*
 * $Log: Queue.hpp,v $
 * Revision 1.1.1.1  2000/07/19 16:59:47  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:34  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:45  god
 * Imported sources
*/

/* __QUEUE_HPP__ */
#endif
