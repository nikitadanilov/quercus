// -*-C++-*- 

/*  inc/events/EventAdapter.hpp  */

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



#ifndef __EVENTADAPTER_HPP__
#define __EVENTADAPTER_HPP__

/* $Id: EventAdapter.hpp,v 1.1.1.1 2000/07/19 17:01:31 philogelos Exp $ */

#include "observe/ObservableAdapter.hpp"
#include "Event.hpp"
#include "defines.h"



BEGIN_QR_NAMESPACE

/**

   @author Philogelos
   @created
*/
class EventAdapter : public Event,
					 public virtual ObservableAdapter
{

  /**
   */
public: EventAdapter( const Top *aSource );

  /**
   */
public: virtual ~EventAdapter();

public: virtual const Top *getSource() const;

public: virtual boolean selfFire();

public: virtual boolean fire( Condition *aCondition,
							  ObservationContext *aContext );
protected: virtual List *getClassPassives();
  /**
   */
public:  virtual boolean equals( const Top *anOther ) const;

  /**
   */
public:  virtual Top *clone() const;

  /**
   */
public:  virtual String  toString() const;

  /**
   */
public:  virtual String  getString() const;

  /**
   */
public:  virtual String  getClassName() const;

protected: const Top *source;
protected: static List *eventClassPassives;
};


END_QR_NAMESPACE

/*
 * $Log: EventAdapter.hpp,v $
 * Revision 1.1.1.1  2000/07/19 17:01:31  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:35  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:47  god
 * Imported sources
*/

/* __EVENTADAPTER_HPP__ */
#endif
