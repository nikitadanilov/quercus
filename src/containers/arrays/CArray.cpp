// -*-C++-*- 

/*  src/containers/arrays/CArray.cpp  */


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


/* $Id: CArray.cpp,v 1.1.1.1 2000/07/19 16:46:03 philogelos Exp $ */
#if !defined(_INLINE)
static char cvsid[] = "@(#)$Id: CArray.cpp,v 1.1.1.1 2000/07/19 16:46:03 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif


#include "containers/arrays/CArray.hpp"
#include "String.hpp"
#include "Debug.hpp"
#include "OGuard.hpp"
#include "LinkManager.hpp"

#include "containers/Empty.hpp"
#include "containers/Singleton.hpp"
#include "containers/MutablePositionEnumeration.hpp"
#include "containers/MutablePosition.hpp"

BEGIN_QR_NAMESPACE

CArray::CArray( Index aBase, Index aLength )
{
  preC_( aLength >= 0 );
  //  preC_( ergo( aLength > 0, ( void * )aCore != NULL ) );

  base = aBase;
  length = aLength;
  core = new const Top * [ length ];
}

CArray::~CArray()
{
  clearAll();
  delete []core;
}

void CArray::clearAll()
{
  for( Index i = getLowBound() ; i < getHighBound() ; ++i )
	{
	  if( getAt( i ) != nil )
		{
		  OFREE( getAt( i ) );
		  core[ i - base ] = nil;
		}
	}
}

String  CArray::getClassName() const
{
  return "CArray";
}

Index CArray::getLowBound() const
{
  return getBase();
}

Index CArray::getHighBound() const
{
  return ( getBase() + getLength() );
}

Index CArray::getBase() const
{
  return base;
}

Index CArray::getLength() const
{
  return length;
}

Top *CArray::getAt( const Index anIndex ) const
{
  preC_( isValidIndex( anIndex ) );
  return( ( Top * ) core[ anIndex - base ] );
}

Top *CArray::setAt( const Index anIndex, Top *aNewValue )
{
  preC_( isValidIndex( anIndex ) );

  Top *oldValue = getAt( anIndex );
  core[ anIndex - base ] = aNewValue;
  LinkManager::move( this, oldValue, aNewValue );
  return oldValue;
}

PositionEnumeration *CArray::getEnumeration() const
{
  return RangedContainer::getEnumeration();
}

MutablePositionEnumeration *CArray::getMutableEnumeration() const
{
  return RangedContainer::getMutableEnumeration();
}

Index CArray::getCardinality() const
{
  return RangedContainer::getCardinality();
}

boolean CArray::isValid( const Position *aPosition ) const
{
  return IndexableContainer::isValid( aPosition );
}

#if defined( TESTING )
boolean CArray::tester( int ) const
{
  CArray *array;
  array = new CArray( 0, 4 );
  OGuard _( array, this );
		
  array -> setAt( 0, new String( "0" ) );
  array -> setAt( 1, new String( "1" ) );
  array -> setAt( 2, new Empty() );
  array -> setAt( 3, new Singleton( new String( "3" ) ) );

  DLOGOBJECT( array, &Top::getString );
  array -> setAt( 0, new String( "!" ) );
  DLOGOBJECT( array, &Top::getString );
		
  MutablePositionEnumeration *en = array -> getMutableEnumeration();
  int k = 100;
  OGuard __( en, this );
  while( en -> hasMoreElements() )
	{
	  MutablePosition *pos;

	  pos = en -> getNextMutablePosition();
	  OGuard _pos( pos, this );
	  pos -> setValue( new String( k++, 0x10 ) );
	}
  DLOGOBJECT( array, &Top::getString );
  return array -> invariant();
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
 * $Log: CArray.cpp,v $
 * Revision 1.1.1.1  2000/07/19 16:46:03  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:41  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:32  god
 * Imported sources
 *
 * Revision 1.4  1999/03/03 19:09:40  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.3  1999/02/28 16:30:14  philogelos
 * Tuned for inlines.
 *
 * Revision 1.2  1998/12/01 16:21:03  philogelos
 * conditionally compile ::tester()
 *
 * Revision 1.1.1.1  1998/11/25 20:11:03  philogelos
 * Quercus Robusta
 *
 * Revision 1.1  1998/07/09 09:30:43  philogelos
 * new files added to the repository
 * */
