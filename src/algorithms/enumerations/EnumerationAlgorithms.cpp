// -*-C++-*- 

/*  src/algorithms/enumerations/EnumerationAlgorithms.cpp  */


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


/* $Id: EnumerationAlgorithms.cpp,v 1.2 2000/08/30 12:20:35 philogelos Exp $ */
#if !defined(_INLINE)
static char cvsid[] = "@(#)$Id: EnumerationAlgorithms.cpp,v 1.2 2000/08/30 12:20:35 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif


#include "algorithms/enumerations/EnumerationAlgorithms.hpp"
#include "Debug.hpp"
#include "OGuard.hpp"
#include "LinkManager.hpp"
#include "AeternalLifeController.hpp"

#include "iter/enumerations/Enumeration.hpp"
#include "iter/enumerations/ResettableEnumeration.hpp"
#include "iter/enumerations/ECursor.hpp"
#include "containers/MutablePosition.hpp"
#include "containers/PositionFactory.hpp"
#include "containers/ModifiableContainer.hpp"
#include "containers/Container.hpp"
#include "containers/EnumeratedValues.hpp"
#include "containers/Pair.hpp"

#include "exceptions/InternalError.hpp"
#include "exceptions/NoEntity.hpp"

BEGIN_QR_NAMESPACE

EnumerationAlgorithms::EnumerationAlgorithms()
{
  Object::setLifeTimeController( new AeternalLifeController() );
}

EnumerationAlgorithms::~EnumerationAlgorithms()
{}

Index EnumerationAlgorithms::findIndex( Enumeration *anEnum, 
										const Top *anObject, 
										const Index aMaxSearch ) const
  THROWS( NoEntity * )
{
  OGuard _enum( anEnum, ( Top * ) this );
  OGuard _object( anObject, ( Top * ) this );

  for( Index ind = 0; ind < aMaxSearch ; ++ind )
	{
	  Top *element;

	  if( !( anEnum -> hasMoreElements() ) )
		{
		  /* XXX should create new exception class in stead. */
		  throw new NoEntity
			( "EnumerationAlgorithms::findIndex(): not enough elements",
			  null );
		}
	  element = anEnum -> getNextElement();
	  if( anObject == nil )
		{
		  if( element == nil )
			{
			  return ind;
			}
		}
	  else
		{
		  if( element -> equals( anObject ) )
			{
			  return ind;
			}
		}
	}
  /* XXX should create new exception class in stead. */
  throw new NoEntity
	( "EnumerationAlgorithms::findIndex(): index not found", null );
  RET_THROW( NULL );
}

Index EnumerationAlgorithms::getCardinality( Enumeration *anEnum )
{
  preC_( anEnum != NIL );
  Index card;

  OGuard _enum( anEnum, ( Top * ) this );
  for( card = 0 ; anEnum -> hasMoreElements() ; ++card )
	{
	  OGuard _item( anEnum -> getNextElement(), this );
	}
  return card;
}

boolean EnumerationAlgorithms::contains( Enumeration *anEnum, const Top *anElement, const boolean same )
{
  preC_( anEnum != NIL );
  //  preC_( anElement != nil );

  OGuard _element( anElement, ( Top * ) this );
  OGuard _enum( anEnum, ( Top * ) this );

  for( ; anEnum -> hasMoreElements() ; )
	{
	  const Top *item;

	  item = anEnum -> getNextElement();
	  if( anElement == nil )
		{
		  if( item == nil )
			{
			  return true;
			}
		}
	  else
		{
		  if( ( !same && ( anElement -> equals( item ) ) ) ||
			  ( same && ( anElement == item ) ) )
			{
			  return true;
			}
		}
	}
  return false;
}

Container *EnumerationAlgorithms::getAsContainer( ResettableEnumeration *anEnum )
{
  preC_( anEnum != NIL );
  return new EnumeratedValues( anEnum );
}

boolean EnumerationAlgorithms::add( ModifiableContainer *aContainer, 
									Enumeration *anEnum )
{
  preC_( aContainer != NIL );
  preC_( anEnum != NIL );
  return addAt( aContainer -> getDefaultPositionFactory(), anEnum );
}

boolean EnumerationAlgorithms::addAt( PositionFactory *aFactory, 
									  Enumeration *anEnum )
{
  preC_( aFactory != NIL );
  preC_( anEnum != NIL );

  OGuard _factory( aFactory, ( Top * ) this );
  OGuard _enum( anEnum, ( Top * ) this );

  while( ( aFactory -> hasMoreElements() ) &&
		 ( anEnum -> hasMoreElements() ) )
	{
	  Top *objectToAdd;
	  MutablePosition *freshPosition;

	  objectToAdd = anEnum -> getNextElement();
	  freshPosition = aFactory -> createPosition();

	  OGuard _object( objectToAdd, ( Top * ) this );
	  OGuard _position( freshPosition, ( Top * ) this );

	  test_( freshPosition != ( MutablePosition * ) NIL );
	  freshPosition -> setValue( objectToAdd );
	}
  return( ! ( anEnum -> hasMoreElements() ) );
}

ResettableEnumeration *EnumerationAlgorithms::getFromContainer( Container *aContainer )
{
  return new ContainerEnumeration( aContainer );
}

ResettableEnumeration *EnumerationAlgorithms::getSum( ResettableEnumeration *aFirst, ResettableEnumeration *aSecond )
{
  preC_( aFirst  != NIL );
  preC_( aSecond != NIL );
  return new SumEnumeration( aFirst, aSecond );
}

ResettableEnumeration *EnumerationAlgorithms::getUnion( ResettableEnumeration *aFirst, ResettableEnumeration *aSecond )
{
  preC_( aFirst  != NIL );
  preC_( aSecond != NIL );
  return new UnionEnumeration( aFirst, aSecond );
}

ResettableEnumeration *EnumerationAlgorithms::getIntersection( ResettableEnumeration *aFirst, ResettableEnumeration *aSecond )
{
  preC_( aFirst  != NIL );
  preC_( aSecond != NIL );
  return new IntersectionEnumeration( aFirst, aSecond );
}


ResettableEnumeration *EnumerationAlgorithms::getProd( ResettableEnumeration *aFirst, ResettableEnumeration *aSecond )
{
  preC_( aFirst  != NIL );
  preC_( aSecond != NIL );
  return new ProdEnumeration( aFirst, aSecond );
}

/*
ResettableEnumeration *EnumerationAlgorithms::getBeta( ResettableEnumeration *anEnum )
{
  preC_( anEnum  != NIL );
  return new BetaEnumeration( anEnum );
}

ResettableEnumeration *EnumerationAlgorithms::getBetaOfN( ResettableEnumeration *anEnum, Index aCardinality )
{
  preC_( anEnum  != NIL );
  return new BetaOfNEnumeration( anEnum, aCardinality );
}


ResettableEnumeration *EnumerationAlgorithms::getOrdBeta( ResettableEnumeration *anEnum )
{
  preC_( anEnum  != NIL );
  return new OrdBetaEnumeration( anEnum );
}

ResettableEnumeration *EnumerationAlgorithms::getOrdBetaOfN( ResettableEnumeration *anEnum, 
															 Index aCardinality )
{
  preC_( anEnum  != NIL );
  return new OrdBetaOfNEnumeration( anEnum, aCardinality );
}

*/

ResettableEnumeration *EnumerationAlgorithms::getInterleaved( ResettableEnumeration *aFirst, 
															  ResettableEnumeration *aSecond )
{
  preC_( aFirst  != NIL );
  preC_( aSecond != NIL );
  return new InterleavedEnumeration( aFirst, aSecond );
}

#if defined( USE_THREADS )
Enumeration *EnumerationAlgorithms::convertIterator( Iterator *anIterator )
{
  preC_( anIterator != NULL );
  return new EnumerationOverIterator( anIterator );
}
#endif

EnumerationAlgorithms *EnumerationAlgorithms::get()
{
  if( instance == ( EnumerationAlgorithms * ) NIL )
	{
	  instance = new EnumerationAlgorithms();
	}
  return instance;
}

Top *EnumerationAlgorithms::clone() const
{
  return ( Top * ) this;
}

String  EnumerationAlgorithms::getClassName() const
{
  return "EnumerationAlgorithms";
}

EnumerationAlgorithms *EnumerationAlgorithms::instance = NIL;

EnumUnaryOp::EnumUnaryOp( ResettableEnumeration *aFirst )
{
  preC_( aFirst != NULL );

  firstArg = aFirst;
}

EnumUnaryOp::~EnumUnaryOp()
{}

void EnumUnaryOp::reset()
{
  firstArg -> reset();
}

EnumBinaryOp::EnumBinaryOp( ResettableEnumeration *aFirst, 
							ResettableEnumeration *aSecond ) :
  EnumUnaryOp( aFirst )
{
  preC_( aSecond != NULL );

  secondArg = aSecond;
}

EnumBinaryOp::~EnumBinaryOp()
{}

void EnumBinaryOp::reset()
{
  secondArg -> reset();
  EnumUnaryOp::reset();
}


SumEnumeration::SumEnumeration( ResettableEnumeration *aFirst, 
								ResettableEnumeration *aSecond ) :
  EnumBinaryOp( aFirst, aSecond )
{
  firstDone = false;
}

SumEnumeration::~SumEnumeration()
{}

Top *SumEnumeration::getNextElement()
{
  if( ! firstDone )
	{
	  return( firstArg -> getNextElement() );
	}
  else
	{
	  return( secondArg -> getNextElement() );
	}
}

boolean SumEnumeration::hasMoreElements()
{
  if( ! firstDone )
	{
	  if( firstArg -> hasMoreElements() )
		{
		  return true;
		}
	  else
		{
		  firstDone = true;
		  return hasMoreElements();
		}
	}
  else
	{
	  return( secondArg -> hasMoreElements() );
	}
}

void SumEnumeration::reset()
{
  firstDone = false;
  EnumBinaryOp::reset();
}

Top *SumEnumeration::clone() const
{
  return new SumEnumeration( *firstArg, *secondArg );
}

UnionEnumeration::UnionEnumeration( ResettableEnumeration *aFirst, 
									ResettableEnumeration *aSecond ) :
  EnumBinaryOp( aFirst, aSecond )
{
  firstDone = false;
  cacheValid = false;
  hasMore = true;
  cachedObject = nil;
}

UnionEnumeration::~UnionEnumeration()
{
  if( cachedObject != nil )
	{
	  FDONE( cachedObject );
	}
}

Top *UnionEnumeration::getNextElement()
{
  if( ! firstDone )
	{
	  return( firstArg -> getNextElement() );
	}
  else
	{
	  if( cacheValid )
		{
		  test_( hasMore );
		  cacheValid = false;
		  LinkManager::unreg( this, cachedObject );
		  return cachedObject;
		}
	  else
		{
		  hasMore = getNextElementInternal();
		  return getNextElement();
		}
	}
}

boolean UnionEnumeration::hasMoreElements()
{
  if( ! firstDone )
	{
	  if( firstArg -> hasMoreElements() )
		{
		  return true;
		}
	  else
		{
		  firstDone = true;
		  return hasMoreElements();
		}
	}
  else
	{
	  if( cacheValid )
		{
		  return hasMore;
		}
	  else
		{
		  hasMore = getNextElementInternal();
		  return hasMoreElements();
		}
	}
}

void UnionEnumeration::reset()
{
  firstDone = false;
  cacheValid = false;
  hasMore = true;

  EnumBinaryOp::reset();
}

Top *UnionEnumeration::clone() const
{
  return new UnionEnumeration( firstArg.getValue(), secondArg.getValue() );
}

boolean UnionEnumeration::getNextElementInternal()
{
  preC_( firstDone );

  cacheValid = true;
  while( true )
	{
	  if( ! ( secondArg -> hasMoreElements() ) )
		{
		  FCDONE( cachedObject );
		  return false;
		}
	  else
		{
		  Top *nextObject;

		  nextObject = secondArg -> getNextElement();
		  OGuard _next( nextObject, ( Top * ) this );

		  firstArg -> reset();
		  if( ! ( EAlg::get() 
				  -> contains( *firstArg, nextObject ) ) )
			{
			  FMOVE( cachedObject, nextObject );
			  return true;
			}
		}
	}
}


IntersectionEnumeration::IntersectionEnumeration( ResettableEnumeration *aFirst, 
												  ResettableEnumeration *aSecond ) :
  EnumBinaryOp( aFirst, aSecond )
{
  cacheValid = false;
  hasMore = true;
  cachedObject = nil;
}

IntersectionEnumeration::~IntersectionEnumeration()
{
  FCDONE( cachedObject );
}

Top *IntersectionEnumeration::getNextElement()
{
  if( cacheValid )
	{
	  test_( hasMore );
	  cacheValid = false;
	  LinkManager::unreg( this, cachedObject );
	  return cachedObject;
	}
  else
	{
	  hasMore = getNextElementInternal();
	  return getNextElement();
	}
}

boolean IntersectionEnumeration::hasMoreElements()
{
  if( cacheValid )
	{
	  return hasMore;
	}
  else
	{
	  hasMore = getNextElementInternal();
	  return hasMoreElements();
	}
}

void IntersectionEnumeration::reset()
{
  cacheValid = false;
  hasMore = true;

  EnumBinaryOp::reset();
}

Top *IntersectionEnumeration::clone() const
{
  return new IntersectionEnumeration( firstArg.getValue(), 
									  secondArg.getValue() );
}

boolean IntersectionEnumeration::getNextElementInternal()
{
  cacheValid = true;
  while( true )
	{
	  if( ! ( firstArg -> hasMoreElements() ) )
		{
		  //		  LinkManager::move( this, cachedObject, nil );
		  cachedObject = nil;
		  return false;
		}
	  else
		{
		  Top *nextObject;

		  nextObject = firstArg -> getNextElement();
		  OGuard _next( nextObject, ( Top * ) this );

		  secondArg -> reset();
		  if( EAlg::get()
			  -> contains( secondArg.getValue(), nextObject ) )
			{
			  FINIT( cachedObject, nextObject );
			  return true;
			}
		}
	}
}


ContainerEnumeration::ContainerEnumeration( Container *aContainer )
{
  preC_( aContainer != NULL );

  container = aContainer;
  en = container -> getValueEnumeration();
}

ContainerEnumeration::~ContainerEnumeration()
{}

Top *ContainerEnumeration::getNextElement()
{
  preC_( en -> hasMoreElements() );
  return( en -> getNextElement() );
}

boolean ContainerEnumeration::hasMoreElements()
{
  return( en -> hasMoreElements() );
}

void ContainerEnumeration::reset()
{
  en = container -> getValueEnumeration();
}

Top *ContainerEnumeration::clone() const
{
  return new ContainerEnumeration( *container );
}

ProdEnumeration::ProdEnumeration( ResettableEnumeration *aFirst, ResettableEnumeration *aSecond ) :
  EnumBinaryOp( aFirst, aSecond ),
  isEmpty( ( !( aFirst  -> hasMoreElements() ) ) ||
		   ( !( aSecond -> hasMoreElements() ) ) )
{
  /* product is empty iff one set is empty (axiom of choice :-)) */
  if( !isEmpty )
	{
	  rowObject = firstArg -> getNextElement();
	  if( rowObject != nil )
		{
		  LinkManager::reg( this, rowObject );
		}
	}
  else
	{
	  rowObject = nil;
	}
}

ProdEnumeration::~ProdEnumeration()
{
  if( !isEmpty )
	{
	  if( rowObject != nil )
		{
		  LinkManager::free( this, rowObject );
		}
	}
}

Top *ProdEnumeration::getNextElement()
{
  preC_( hasMoreElements() );
  if( ! secondArg -> hasMoreElements() )
	{
	  Top *newRowObject;

	  secondArg -> reset();
	  test_( secondArg -> hasMoreElements() );

	  newRowObject = firstArg -> getNextElement();
	  LinkManager::move( this, rowObject, 
						 newRowObject );
	  rowObject = newRowObject;
	}
  test_( secondArg -> hasMoreElements() );
  return new Pair( rowObject, secondArg -> getNextElement() );
}

boolean ProdEnumeration::hasMoreElements()
{
  return ( ( !isEmpty ) &&
		   ( ( firstArg  -> hasMoreElements() ) || 
			 ( secondArg -> hasMoreElements() ) ) );
}

void ProdEnumeration::reset()
{
  EnumBinaryOp::reset();
  if( !isEmpty )
	{
	  Top *newRowObject;

	  newRowObject = firstArg -> getNextElement();
	  LinkManager::move( this, rowObject, newRowObject );
	  rowObject = newRowObject;
	}
  else
	{
	  rowObject = nil;
	}
}

Top *ProdEnumeration::clone() const
{
  return new ProdEnumeration( firstArg.getValue(), secondArg.getValue() );
}



InterleavedEnumeration::InterleavedEnumeration( ResettableEnumeration *aFirst, 
												ResettableEnumeration *aSecond ) :
  EnumBinaryOp( aFirst, aSecond )
{
  current = firstArg.getValue();
}

InterleavedEnumeration::~InterleavedEnumeration()
{}

Top *InterleavedEnumeration::getNextElement()
{
  Top *result;

  result = current -> getNextElement();
  if( current == firstArg.getValue() )
	{
	  current = secondArg.getValue();
	}
  else
	{
	  current = firstArg.getValue();
	}
  return result;
}

boolean InterleavedEnumeration::hasMoreElements()
{
  return( current -> hasMoreElements() );
}

void InterleavedEnumeration::reset()
{
  EnumBinaryOp::reset();
  current = firstArg.getValue();
}

Top *InterleavedEnumeration::clone() const
{
  return new InterleavedEnumeration( firstArg.getValue(), 
									 secondArg.getValue() );
}

#if defined( USE_THREADS )

END_QR_NAMESPACE

#include "platform/threads/Mutex.hpp"
#include "platform/threads/MGuard.hpp"

BEGIN_QR_NAMESPACE

EnumerationOverIterator::EnumerationOverIterator( Iterator *anIterator ) :
  iterator( anIterator ),
  thread( NULL, true ),
  condition( THR_SYSTEM -> condition() )
{
  done = false;
  filled = true;
  queue = nil;
  thread.setValue( THR_FACTORY -> createFromRunner( this ) );
}

boolean EnumerationOverIterator::hasMoreElements()
{
  return !done;
}

Top *EnumerationOverIterator::getNextElement()
{
  MGuard _lock( condition -> getMutex(), this );
  filled = false;
  condition -> signal();

  while( !filled && !done )
	{
	  condition -> wait();
	}
  if( filled )
	{
	  return queue;
	}
  else
	{
	  test_( done );
	  return nil;
	}
  
}


void *EnumerationOverIterator::run()
{
  iterator -> iterate( this );
  return NULL;
}

void EnumerationOverIterator::initIterations()
{
  MGuard _lock( condition -> getMutex(), this );
  done = false;
}

void EnumerationOverIterator::fireOn( Top *anElement )
{
  MGuard _lock( condition -> getMutex(), this );
  while( filled )
	{
	  condition -> wait();
	}
  queue = anElement;
  filled = true;
  condition -> signal();
}

boolean EnumerationOverIterator::isMore()
{
  MGuard _lock( condition -> getMutex(), this );
  return true;
}

void EnumerationOverIterator::doneIterations()
{
  MGuard _lock( condition -> getMutex(), this );
  done = true;
}

/* USE_THREADS */
#endif

#if defined( TESTING )

END_QR_NAMESPACE

#include "containers/lists/List.hpp"
#include "containers/arrays/CArray.hpp"
#include "String.hpp"
#include "Debug.hpp"
#include "OGuard.hpp"
#include "LinkManager.hpp"
#include "ObjectWrapper.hpp"

#include "containers/Empty.hpp"
#include "containers/Stack.hpp"
#include "containers/Singleton.hpp"
#include "containers/MutablePositionEnumeration.hpp"
#include "containers/MutablePosition.hpp"

BEGIN_QR_NAMESPACE

boolean EnumerationAlgorithms::tester( int ) const
{
  //   DLOG( "convertIterator" );
  //   CRef< Enumeration > en
  // 	( EALG -> convertIterator
  // 	  ( ( new List
  // 		  ( 0, 
  // 			OW( new Object() ), 
  // 			OW( new Stack() ), 
  // 			OW( new String( "foo!" ) ), NULL ) ) -> getValueIterator() ) );
  
//   while( en -> hasMoreElements() )
// 	{
// 	  DLOGOBJECT( "item: %s", en -> getNextElement() );
// 	}
  
  CRef< CArray > array;
  CRef< List > list;

  array = new CArray( 0, 4 );
  list = new List();
		
  array -> setAt( 0, new String( "0" ) );
  array -> setAt( 1, new String( "1" ) );
  array -> setAt( 2, new Empty() );
  array -> setAt( 3, new Singleton( new String( "3" ) ) );

  EALG -> add( *list, array -> getValueEnumeration() );
  DLOGOBJECT( *list );
  
  test_( list -> getCardinality() == 4 );

  list -> behead();
  DLOGOBJECT( *list );
  test_( list -> getCardinality() == 3 );

  CRef< Container > sum;

  sum = EALG 
  	-> getAsContainer( EALG -> getSum
					   ( EALG -> getFromContainer( *array ),
						 EALG -> getFromContainer( *list ) ) );
  DLOGOBJECT( "sum: %s", *sum );
  test_( sum -> getCardinality() == 
 		 array -> getCardinality() + list -> getCardinality() );
  test_( sum -> getCardinality() == 7 );
  
  CRef< Container > un;
  
  un = EALG 
 	-> getAsContainer( EALG -> getUnion
					   ( EALG -> getFromContainer( *array ),
						 EALG ->	getFromContainer( *list ) ) );
  DLOGOBJECT( "union: %s", *un );
  test_( un -> getCardinality() == array -> getCardinality() );
  test_( un -> getCardinality() == 4 );

  CRef< Container > in;

  in = EALG 
 	-> getAsContainer( EALG -> getIntersection
					   ( EALG -> getFromContainer( *array ),
						 EALG -> getFromContainer( *list ) ) );
  DLOGOBJECT( "intersection: %s", *in );
  test_( in -> getCardinality() == list -> getCardinality() );
  test_( in -> getCardinality() == 3 );
  // DLOGOBJECT( array );

  CRef< Container > prod;

  prod = EALG 
	-> getAsContainer( EALG -> getProd
					   ( EALG -> getFromContainer( *array ),
						 EALG -> getFromContainer( *list ) ) );
  
  DLOGOBJECT( "product: %s", *prod );
  test_( prod -> getCardinality() == 
		 list -> getCardinality() * array -> getCardinality() );
  test_( prod -> getCardinality() == 12 );

  CRef< Container > intr;
   
  intr = EALG 
	-> getAsContainer( EALG -> getInterleaved
					   ( EALG -> getFromContainer( *array ),
						 EALG -> getFromContainer( *list ) ) );
  
  DLOGOBJECT( "interleaving: %s", *intr );
  test_( intr -> getCardinality() == sum -> getCardinality() );
  
  return true;
}
#endif

END_QR_NAMESPACE

#if defined(_INLINE)
#include "../src/Debug.ipp"
#endif


#if defined(_INLINE)
#include "../src/String.ipp"
#endif

/*
 * $Log: EnumerationAlgorithms.cpp,v $
 * Revision 1.2  2000/08/30 12:20:35  philogelos
 * THROWS clauses updates to correspond to the real throws.
 *
 * Revision 1.1.1.1  2000/07/19 16:44:04  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.5  2000/04/09 12:00:48  god
 * CVS Log keyword correction finished
 *
 * Revision 1.4  2000/04/09 11:29:40  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.3  2000/04/07 17:14:09  god
 * Memory leak in ::getCradinality() corrected, CRefs<> added, assertions in ::tester()
 *
 * Revision 1.2  2000/04/06 11:57:36  god
 * converted to CRefs<> tests added to ::tester()
 *
 * Revision 1.1.1.1  2000/04/01 14:07:30  god
 * Imported sources
 *
 * Revision 1.4  1999/03/03 19:09:32  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.3  1999/02/28 16:29:04  philogelos
 * Tuned for inlines. ::findIndex() added
 *
 * Revision 1.2  1998/12/01 16:20:02  philogelos
 * conditionally compile ::tester()
 *
 * Revision 1.1.1.1  1998/11/25 20:11:02  philogelos
 * Quercus Robusta
 * */
