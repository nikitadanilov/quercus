// -*-C++-*- 

/*  src/events/EventAdapter.cpp  */

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



/* $Id: EventAdapter.cpp,v 1.1.1.1 2000/07/19 16:48:51 philogelos Exp $ */
#if !defined(_INLINE)
static char cvsid[] = "@(#)$Id: EventAdapter.cpp,v 1.1.1.1 2000/07/19 16:48:51 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif

#include "containers/lists/List.hpp"
#include "events/EventAdapter.hpp"
#include "LinkManager.hpp"
#include "OGuard.hpp"
#include "Debug.hpp"

BEGIN_QR_NAMESPACE

EventAdapter::EventAdapter( const Top *aSource ) :
  source( aSource )
{
  preC_( source != nil );
  OREG( source );
}

EventAdapter::~EventAdapter()
{
  FDONE( source );
}

const Top *EventAdapter::getSource() const
{
  return source;
}

boolean EventAdapter::selfFire()
{
  ObservationContext *context;
  OGuard _this( this, this );
  
  context = new ObservationContext();
  OGuard _context( context, this );
  return fire( this, context );
}

boolean EventAdapter::fire( Condition *aCondition,
							ObservationContext *aContext )
{
  preC_( aCondition != ( Condition * ) NIL );
  preC_( aContext != ( ObservationContext * ) NIL );
  OGuard _this( this, this );

  OGuard _condition( aCondition, this );
  OGuard _context( aContext, this );
  return( ObservableAdapter::fire( aCondition, aContext ) &
		  fireOnList( ObservableAdapter::getClassPassives(), 
					  aCondition, aContext ) );
}

List *EventAdapter::getClassPassives()
{
  if( eventClassPassives == ( List * ) NIL )
	{
	  eventClassPassives = new List();
	  eventClassPassives -> dontManage();
	}
  return eventClassPassives;
}

boolean EventAdapter::equals( const Top *anOther ) const
{
  EventAdapter *other;
  OGuard _this( this, this );

  other = DCAST( anOther, EventAdapter );
  if( other == ( EventAdapter * ) NIL )
	{
	  return false;
	}
  else
	{
	  OGuard _other( other, this );
	  return( getSource() -> equals( getSource() ) );
	}
}

Top *EventAdapter::clone() const
{
  return new EventAdapter( getSource() );
}

String  EventAdapter::toString() const
{
  return ObservableAdapter::toString() + 
	" source: " + getSource() -> toString();
}

String  EventAdapter::getString() const
{
  return ObservableAdapter::getString() + 
	" source: " + getSource() -> getString();
}

String  EventAdapter::getClassName() const
{
  return "EventAdapter";
}

List *EventAdapter::eventClassPassives = ( List * ) NIL;

END_QR_NAMESPACE

#if defined(_INLINE)
#include "../src/Debug.ipp"
#endif


/*
 * $Log: EventAdapter.cpp,v $
 * Revision 1.1.1.1  2000/07/19 16:48:51  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:42  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:34  god
 * Imported sources
*/
