//-*-C++-*-

/*  src/containers/ContainerAdapter.cpp  */


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


/* $Id: ContainerAdapter.cpp,v 1.2 2001/04/16 13:37:13 philogelos Exp $ */
#if !defined(_INLINE)
static char cvsid[] = "@(#)$Id: ContainerAdapter.cpp,v 1.2 2001/04/16 13:37:13 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif


#include "OGuard.hpp"
#include "PGuard.hpp"
#include "Debug.hpp"
#include "String.hpp"
#include "MethodMap.hpp"
#include "LinkManager.hpp"
#include "containers/ContainerAdapter.hpp"
#include "iter/enumerations/Enumeration.hpp"
#include "iter/enumerations/MappedEnumeration.hpp"
#include "iter/iterators/EnumerationIterator.hpp"
#include "iter/iterables/PrettyPrintIterable.hpp"
#include "algorithms/enumerations/EnumerationAlgorithms.hpp"

#include "exceptions/InvalidArgument.hpp"

BEGIN_QR_NAMESPACE

ContainerAdapter::ContainerAdapter()
{}

ContainerAdapter::~ContainerAdapter()
{}

boolean ContainerAdapter::isEmpty() const
{
  return ( getCardinality() == 0 );
}

Iterator *ContainerAdapter::getIterator() const
{
  return new EnumerationIterator( getEnumeration() );
}

Enumeration *ContainerAdapter::getValueEnumeration() const
{
  return new MappedEnumeration( getEnumeration(), getAsMap() );
//   return new MappedEnumeration
// 	( getEnumeration(), 
// 	  new MethodMap< Position, Top >( ( Top *( Position::* )() )&Position::getValue,
// 									  false, false ) );
}

Iterator    *ContainerAdapter::getValueIterator() const
{
  return new EnumerationIterator( getValueEnumeration() );
}

Index ContainerAdapter::getCardinality() const
{
  return( EALG -> getCardinality( getEnumeration() ) );
}

boolean ContainerAdapter::contains( const Top *anElement ) const
{
  return( EALG -> contains( getValueEnumeration(), anElement ) );
}

Position *ContainerAdapter::find( const Top *anObject ) const
{
  OGuard _this( this, this );
  OGuard _object( anObject, this );
  PositionEnumeration *en;

  en = getEnumeration();
  OGuard _en( en, this );
  
  while( en -> hasMoreElements() )
	{
	  Position *pos;

	  pos = en -> getNextPosition();
	  {
		PGuard _pos( pos, this );
		if( pos -> getValue() -> equals( anObject ) )
		  {
			return pos;
		  }
	  }
	  LinkManager::recycle( pos );
	}
  return NIL;
}

Top   *ContainerAdapter::getValue( const Position *aPosition )
{
  preC_( aPosition != ( const Position * ) NULL );
  preC_( isValid( aPosition ) );

  return aPosition -> getValue();
}

boolean ContainerAdapter::equals( const Top *anOther ) const
{
  preC_( anOther != null );
  Enumeration *my;
  Enumeration *his;

  OGuard _( anOther, this );

  if( DCAST( anOther, ContainerAdapter ) == null )
	{
	  return false;
	}

  my = getValueEnumeration();
  his = DCAST( anOther, ContainerAdapter ) -> getValueEnumeration();

  OGuard _his( his, this );
  OGuard _my( my, this );
  
  while( true )
	{
	  Top *myItem;
	  Top *hisItem;
	  
	  if( ! my -> hasMoreElements() )
		{
		  if( ! his -> hasMoreElements() )
			{
			  return true;
			}
		  else
			{
			  return false;
			}
		}
	  if( ! his -> hasMoreElements() )
		{
		  return false;
		}
	  myItem = my -> getNextElement();
	  hisItem = his -> getNextElement();

	  OGuard _hisItem( hisItem, this );
	  OGuard _myItem( myItem, this );
#if defined( USE_TYPEID )
	  if( typeid( myItem ) != typeid( hisItem ) )
		{
		  return false;
		}
#endif
	  if( ! myItem -> equals( hisItem ) )
		{
		  return false;
		}
	}
}

String  ContainerAdapter::getPrintHeader() const
{
  return "(";
}

String  ContainerAdapter::getPrintSeparator() const
{
  return ", ";
}

String  ContainerAdapter::getPrintFooter() const
{
  return ")";
}

String  ContainerAdapter::getEllipsis() const
{
  return " ... ";
}

Index   ContainerAdapter::getMaxPrintCount() const
{
  return maxPrintCount;
}

String  ContainerAdapter::print( String ( Top::* aMethod )() const ) const
{
  Iterator   *it;
  PrettyPrintIterable  *runner;
  String result;

  it = getValueIterator();
  runner = new PrettyPrintIterable
	( getPrintHeader(), getPrintSeparator(), getPrintFooter(), getEllipsis(), 
	  getMaxPrintCount(), aMethod );

  OGuard _runner( runner, this );
  OGuard _it( it, this );

  it -> iterate( runner );
  result = Object::getString() + runner -> getStringResult();
  
  return result;
}

String  ContainerAdapter::toString() const
{
  return print( &Top::toString );
}

String  ContainerAdapter::getString() const
{
  return print( &Top::getString );
}

String  ContainerAdapter::getClassName() const
{
  return "ContainerAdapter";
}


boolean   ContainerAdapter::isValid ( const Position *aPosition ) const
{
  return( ( aPosition -> getContainer() ) == ( const Container * ) this );
}

// Top   *ContainerAdapter::getValue( const Position * )
// {
//   sure( false, "ContainerAdapter cannot getValue()" );
//   return nil;
// }

Map *ContainerAdapter::getAsMap() const
{
  return new ContainerAdapter::ContainerMap( ( Container * ) this );
}

ContainerAdapter::ContainerMap::ContainerMap( Container *aContainer )
{
  preC_( aContainer != null );
  container = aContainer;
}

Top *ContainerAdapter::ContainerMap::apply( Top *anArg ) THROWS( InvalidArgument * )
{
  Position *position = DCAST( anArg, Position );
  if( position != null )
	{
	  OGuard _( position, this );
	  if( container -> isValid( position ) )
		{
		  return( container -> getValue( position ) );
		}
	  else
		{
		  throw 
			( new InvalidArgument
			  ( "ContainerAdapter::ContainerMap::apply(): argument is invalid Position", 
				nil ) );
		  RET_THROW( NULL );
		}
	}
  else
	{
	  throw 
		( new InvalidArgument
		  ( "ContainerAdapter::ContainerMap::apply(): argument is not Position", 
			nil ) );
	  RET_THROW( NULL );
	}
}

Index ContainerAdapter::maxPrintCount = 100;

END_QR_NAMESPACE

#if defined(_INLINE)
#include "../src/Debug.ipp"
#endif


#if defined(_INLINE)
#include "../src/String.ipp"
#endif

/*
 * $Log: ContainerAdapter.cpp,v $
 * Revision 1.2  2001/04/16 13:37:13  philogelos
 * Added ::getStringResult() to PrettyPrintIterable.
 * Clients updated to take advantage of this method.
 *
 * Revision 1.1.1.1  2000/07/19 16:44:59  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:40  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:32  god
 * Imported sources
 *
 * Revision 1.4  1999/05/22 13:00:33  philogelos
 * Merging sources back from SPARC
 *
 * Revision 1.3  1999/03/03 19:09:34  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.2  1999/02/28 16:29:58  philogelos
 * LayeredContainer adde. Tuned for inlines.
 *
 * Revision 1.1.1.1  1998/11/25 20:11:02  philogelos
 * Quercus Robusta
 *
 * Revision 1.1  1998/07/09 09:30:39  philogelos
 * new files added to the repository
 * */
