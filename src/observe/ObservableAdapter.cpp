// -*-C++-*- 

/*  src/observe/ObservableAdapter.cpp  */

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



/* $Id: ObservableAdapter.cpp,v 1.1.1.1 2000/07/19 16:50:38 philogelos Exp $ */
#if !defined(_INLINE)
static char cvsid[] = "@(#)$Id: ObservableAdapter.cpp,v 1.1.1.1 2000/07/19 16:50:38 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif

#include "observe/ObservableAdapter.hpp"
#include "observe/PassiveObserver.hpp"
#include "observe/ActiveObserver.hpp"
#include "observe/Observer.hpp"
#include "observe/Observer.hpp"
#include "containers/lists/List.hpp"
#include "LinkManager.hpp"
#include "Condition.hpp"
#include "OGuard.hpp"
#include "Debug.hpp"

#include <stdio.h>

BEGIN_QR_NAMESPACE

ObservableAdapter::ObservableAdapter()
{
  passiveObservers = activeObservers = ( List * ) NIL;
}

ObservableAdapter::~ObservableAdapter()
{
  FCDONE( passiveObservers );
  FCDONE( activeObservers );
}

void ObservableAdapter::addActive( ActiveObserver *anObserver )
{
  preC_( anObserver != ( ActiveObserver * ) NIL );
  OGuard _this( this, this );
  OGuard _observer( anObserver, this );
  getActives() -> append( anObserver );
}

void ObservableAdapter::addPassive( PassiveObserver *anObserver )
{
  preC_( anObserver != ( PassiveObserver * ) NIL );
  OGuard _this( this, this );
  OGuard _observer( anObserver, this );
  getPassives() -> append( anObserver );
}

void ObservableAdapter::removeActive( ActiveObserver *anObserver )
{
  preC_( anObserver != ( ActiveObserver * ) NIL );
  OGuard _this( this, this );
  OGuard _observer( anObserver, this );
  /* XXX need appropriate methods in List */
  strip( getActives(), anObserver );
}

void ObservableAdapter::removePassive( PassiveObserver *anObserver )
{
  preC_( anObserver != ( PassiveObserver * ) NIL );
  OGuard _this( this, this );
  OGuard _observer( anObserver, this );
  /* XXX need appropriate methods in List */
  strip( getPassives(), anObserver );
}

void ObservableAdapter::addClassPassive( PassiveObserver *anObserver )
{
  preC_( anObserver != ( PassiveObserver * ) NIL );
  OGuard _this( this, this );
  OGuard _observer( anObserver, this );
  getClassPassives() -> append( anObserver );
}

void ObservableAdapter::addClassActive( ActiveObserver *anObserver )
{
  preC_( anObserver != ( ActiveObserver * ) NIL );
  OGuard _this( this, this );
  OGuard _observer( anObserver, this );
  getClassActives() -> append( anObserver );
}

void ObservableAdapter::removeClassPassive( PassiveObserver *anObserver )
{
  preC_( anObserver != ( PassiveObserver * ) NIL );
  OGuard _this( this, this );
  OGuard _observer( anObserver, this );
  /* XXX need appropriate methods in List */
  strip( getClassPassives(), anObserver );
}

void ObservableAdapter::removeClassActive( ActiveObserver *anObserver )
{
  preC_( anObserver != ( ActiveObserver * ) NIL );
  OGuard _this( this, this );
  OGuard _observer( anObserver, this );
  /* XXX need appropriate methods in List */
  strip( getClassActives(), anObserver );
}

boolean ObservableAdapter::fire( Condition *aCondition,
								 ObservationContext *aContext )
{
  preC_( aCondition != ( Condition * ) NIL );
  preC_( aContext != ( ObservationContext * ) NIL );
  OGuard _this( this, this );

  OGuard _condition( aCondition, this );
  OGuard _context( aContext, this );

  boolean fail;

  fail = !fireOnList( getPassives(), aCondition, aContext, false );
  fail |= !fireOnList( getClassPassives(), aCondition, aContext, false );
  fail |= !fireOnList( getPassives(), aCondition, aContext, true );
  fail |= !fireOnList( getClassPassives(), aCondition, aContext, true );
  return !fail;
}

boolean ObservableAdapter::fireOnList( List *aList, 
									   Condition *aCondition,
									   ObservationContext *aContext,
									   boolean aPost )
{
  preC_( aList != ( List * ) NIL );
  preC_( aCondition != ( Condition * ) NIL );
  preC_( aContext != ( ObservationContext * ) NIL );

  OGuard _list( aList, this );
  OGuard _condition( aCondition, this );
  OGuard _context( aContext, this );

  boolean done;
  boolean ok;

  /* XXX hard-coded semantics of HandleResult:
	 0:  OK, continue processing
	 1:  OK, stop processing
	 2:  ERROR, continue
	 3:  ERROR, stop
    -1:  restart
  */
  done = false;
  ok   = true;
  while( !done )
	{
	  done = true;
	  for( aList -> toFirst() ;
		   !( aList -> atEnd() ) ;
		   aList -> next() )
		{
		  HandlerResult iterationResult;

		  if( !aPost )
			{
			  iterationResult = 
				TCAST( aList -> getCurrentValue(), PassiveObserver ) -> 
				fire( aCondition, aContext );
			}
		  else
			{
			  iterationResult = 
				TCAST( aList -> getCurrentValue(), PassiveObserver ) -> 
				firePost( aCondition, aContext );
			}

		  if( iterationResult == -1 )
			{
			  done = false;
			  break;
			}
		  if( iterationResult == 0 )
			{
			  continue;
			}
		  if( iterationResult == 1 )
			{
			  break;
			}
		  if( iterationResult == 2 )
			{
			  ok = false;
			  continue;
			}
		  if( iterationResult == 2 )
			{
			  ok = false;
			  break;
			}
		}
	}
  return ok;
}

Index ObservableAdapter::strip( List *aList, Top *anObject )
{
  preC_( aList != ( List * ) NIL );
  Index foundCount;

  OGuard _list( aList, this );
  OGuard _object( anObject, this );

  foundCount = 0;
  for( aList -> toFirst() ; !( aList -> atEnd() ) ; )
	{
	  if( aList -> getCurrentValue() ->
		  equals( anObject ) )
		{
		  aList -> remove();
		  ++foundCount;
		}
	  else
		{
		  aList -> next();
		}
	}
  return foundCount;
}

boolean ObservableAdapter::equals( const Top *anOther ) const
{
  OGuard _this( this, this );
  ObservableAdapter *other;

  other = DCAST( anOther, ObservableAdapter );
  if( other == ( ObservableAdapter * ) NIL )
	{
	  return false;
	}
  else
	{
	  OGuard _other( other, this );
	  ObservableAdapter *pseudoThis;

	  pseudoThis = ( ObservableAdapter * ) this;
	  return( pseudoThis -> getPassives() -> 
			  equals( other -> getPassives() ) && 
			  pseudoThis -> getActives() -> 
			  equals( other -> getActives() ) );
	}
}

Top *ObservableAdapter::clone() const
{
  OGuard _this( this, this );
  ObservableAdapter *result;

  result = new ObservableAdapter();
  OGuard _result( result, this );
  ObservableAdapter *pseudoThis;
  
  pseudoThis = ( ObservableAdapter * ) this;
  for( pseudoThis -> getPassives() -> toFirst() ;
	   !( pseudoThis -> getPassives() -> atEnd() ) ;
	   pseudoThis -> getPassives() -> next() )
	{
	  result -> 
		addPassive( TCAST( pseudoThis -> getPassives() -> getCurrentValue(),
						   PassiveObserver ) );
	}
  for( pseudoThis -> getActives() -> toFirst() ;
	   !( pseudoThis -> getActives() -> atEnd() ) ;
	   pseudoThis -> getActives() -> next() )
	{
	  result -> 
		addActive( TCAST( pseudoThis -> getActives() -> getCurrentValue(), 
						  ActiveObserver ) );
	}
  postC_( equals( result ) );
  return result;
}

String  ObservableAdapter::toString() const
{
  OGuard _this( this, this );
  ObservableAdapter *pseudoThis;
  
  pseudoThis = ( ObservableAdapter * ) this;
  return Object::toString() + " passive: " +
	pseudoThis -> getPassives() -> toString() +
	" active: " +
	pseudoThis -> getActives() -> toString();
}

String  ObservableAdapter::getString() const
{
  OGuard _this( this, this );
  ObservableAdapter *pseudoThis;
  
  pseudoThis = ( ObservableAdapter * ) this;
  return Object::getString() + " passive: " +
	pseudoThis -> getPassives() -> getString() +
	" active: " +
	pseudoThis -> getActives() -> getString();
}

String  ObservableAdapter::getClassName() const
{
  return "ObservableAdapter";
}

List *ObservableAdapter::getPassives()
{
  if( passiveObservers == ( List * ) NIL )
	{
	  FINIT( passiveObservers, new List() );
#if defined( USE_THREADS ) /* XXX it is dirty hack isn't it? */
	  passiveObservers -> setProtector( THR_SYSTEM -> recMutex() );
#endif
	}
  return passiveObservers;
}

List *ObservableAdapter::getActives()
{
  if( activeObservers == ( List * ) NIL )
	{
	  FINIT( activeObservers, new List() );
#if defined( USE_THREADS ) /* XXX it is dirty hack isn't it? */
	  activeObservers -> setProtector( THR_SYSTEM -> recMutex() );
#endif
	}
  return activeObservers;
}


List *ObservableAdapter::getClassPassives()
{
  if( classPassiveObservers == ( List * ) NIL )
	{
	  classPassiveObservers = new List();
	  classPassiveObservers -> dontManage();
#if defined( USE_THREADS ) /* XXX it is dirty hack isn't it? */
	  classPassiveObservers -> setProtector( THR_SYSTEM -> recMutex() );
#endif
	}
  return classPassiveObservers;
}

List *ObservableAdapter::getClassActives()
{
  if( classActiveObservers == ( List * ) NIL )
	{
	  classActiveObservers = new List();
	  classActiveObservers -> dontManage();
#if defined( USE_THREADS ) /* XXX it is dirty hack isn't it? */
	  classActiveObservers -> setProtector( THR_SYSTEM -> recMutex() );
#endif
	}
  return classActiveObservers;
}

List *ObservableAdapter::classPassiveObservers = ( List * ) NIL;
List *ObservableAdapter::classActiveObservers = ( List * ) NIL;

#if defined( TESTING )

END_QR_NAMESPACE
#include "observe/EchoCondition.hpp"
#include "observe/ObservationContext.hpp"
#include "observe/EchoObserver.hpp"
#include "exceptions/OutOfMemory.hpp"
BEGIN_QR_NAMESPACE

boolean ObservableAdapter::tester( int  ) const NOTHROWS
{
  {
	EchoObserver *echo;
	ObservableAdapter *publisher;

	echo = new EchoObserver();
	OGuard _echo( echo, this );

	publisher = new ObservableAdapter();
	OGuard _publisher( publisher, this );

	publisher -> addPassive( echo );
	publisher -> addPassive( echo );
	publisher -> fire( new EchoCondition( "subscribe test" ),
					   new ObservationContext() );
  }
  return true;
}

#endif

#if defined( USE_PER_CLASS_NEW )
INLINE void *ObservableAdapter::operator new( size_t size )
{
  return ::operator new( size );
}
#endif

END_QR_NAMESPACE

#if defined(_INLINE)
#include "../src/Debug.ipp"
#endif


/*
 * $Log: ObservableAdapter.cpp,v $
 * Revision 1.1.1.1  2000/07/19 16:50:38  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:43  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:34  god
 * Imported sources
 *
 * Revision 1.3  1999/05/22 13:00:57  philogelos
 * Merging sources back from SPARC
 *
 * Revision 1.2  1999/03/03 19:09:47  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.1  1999/02/28 16:30:50  philogelos
 * Tuned for inlines.
 * */
