// -*-C++-*- 

/*  src/containers/RangedContainer.cpp  */


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


/* $Id: RangedContainer.cpp,v 1.1.1.1 2000/07/19 16:45:35 philogelos Exp $ */
#if !defined(_INLINE)
static char cvsid[] = "@(#)$Id: RangedContainer.cpp,v 1.1.1.1 2000/07/19 16:45:35 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif


#include "containers/IndexPosition.hpp"
#include "containers/RangedContainer.hpp"
#include "iter/enumerations/RangedContainerEnumeration.hpp"
#include "Debug.hpp"
#include "OGuard.hpp"
#include "algorithms/enumerations/EnumerationAlgorithms.hpp"

BEGIN_QR_NAMESPACE

boolean RangedContainer::isValidIndex( const Index anIndex ) const
{
  return ( ( getLowBound() <= anIndex ) && 
		   ( anIndex < getHighBound() ) );
}

RangedContainerEnumeration *RangedContainer::getRangedEnumeration() const
{
  return new RangedContainerEnumeration( ( RangedContainer * ) this );
}

PositionEnumeration *RangedContainer::getEnumeration() const
{
  return getMutableEnumeration();
}

MutablePositionEnumeration *RangedContainer::getMutableEnumeration() const
{
  return getRangedEnumeration();
}

Index RangedContainer::findIndex( const Top *anObject ) const
{
  preC_( contains( anObject ) );
  return( EAlg::get() ->
		  findIndex( getEnumeration(), anObject,
					 getCardinality() ) );
}

Index RangedContainer::getCardinality() const
{
  return ( getHighBound() - getLowBound() );
}


IndexPosition *RangedContainer::getFirstPosition() const
{
  return new IndexPosition( getLowBound(), 
							( IndexableContainer * ) this );
}

IndexPosition *RangedContainer::getLastPosition() const
{
  return new IndexPosition( getHighBound() - 1, 
							( IndexableContainer * ) this );
}

MutablePosition *RangedContainer::getAlwaysFirstPosition() const
{
  return new RangedContainer::RContainerFirstPosition( this );
}

MutablePosition *RangedContainer::getAlwaysLastPosition() const
{
  return new RangedContainer::RContainerLastPosition( this );
}



RangedContainer::BeyondRange::BeyondRange( String aMessage, 
										   const Top *const aSource ) :
  InvalidIndex( aMessage, aSource ),
#if defined( USE_STL )
  logic_error( aMessage.getChars() ),
#endif
  Exception( aMessage, aSource )
{}

String RangedContainer::BeyondRange::getDescription() const
{
  return InvalidIndex::getDescription() + 
	String( ": Index is beyond the valid range", false );
}

String  RangedContainer::BeyondRange::getClassName() const
{
  return "BeyondRange";
}

RangedContainer::AfterLast::AfterLast( String aMessage, 
									   const Top *const aSource ) :
  BeyondRange( aMessage, aSource ),
#if defined( USE_STL )
  logic_error( aMessage.getChars() ),
#endif
  Exception( aMessage, aSource )
{}

String RangedContainer::AfterLast::getDescription() const
{
  return BeyondRange::getDescription() + 
	String( ": index is after the last valid index", false );
}

String  RangedContainer::AfterLast::getClassName() const
{
  return "AfterLast";
}

RangedContainer::BeforeFirst::BeforeFirst( String aMessage, 
										   const Top *const aSource ) :
  BeyondRange( aMessage, aSource ),
#if defined( USE_STL )
  logic_error( aMessage.getChars() ),
#endif
  Exception( aMessage, aSource )
{}

String RangedContainer::BeforeFirst::getDescription() const
{
  return BeyondRange::getDescription() + 
	String( ": index is before the first valid index", false );
}

String  RangedContainer::BeforeFirst::getClassName() const
{
  return "BeforeFirst";
}

RangedContainer::RContainerFirstPosition::RContainerFirstPosition( const RangedContainer *aContainer ) :
  MutablePositionAdapter( ( MutableContainer * ) aContainer ),
  PositionAdapter( ( Container * ) aContainer )
{}

RangedContainer::RContainerFirstPosition::~RContainerFirstPosition()
{}

Top *RangedContainer::RContainerFirstPosition::setValue( Top *aNewValue )
{
  preC_( isValid() );
  OGuard _container( getContainer(), this );
  return DCAST( getContainer(), RangedContainer ) -> 
	setAt( DCAST( getContainer(), RangedContainer ) -> getLowBound(),
		   aNewValue );
}

boolean RangedContainer::RContainerFirstPosition::isValid() const
{
  return( ( dynamic_cast< RangedContainer * >( getContainer() ) ) -> isEmpty() ); 
}

Top *RangedContainer::RContainerFirstPosition::getValue() const
{
  preC_( isValid() );
  OGuard _container( getContainer(), this );
  return ( dynamic_cast< RangedContainer * >( getContainer() ) ) 
	-> getAt( ( dynamic_cast< RangedContainer * >( getContainer() ) ) -> getLowBound() );
}



RangedContainer::RContainerLastPosition::RContainerLastPosition( const RangedContainer *aContainer ) :
  MutablePositionAdapter( ( MutableContainer * ) aContainer ),
  PositionAdapter( ( Container * ) aContainer )
{}

RangedContainer::RContainerLastPosition::~RContainerLastPosition()
{}

Top *RangedContainer::RContainerLastPosition::setValue( Top *aNewValue )
{
  preC_( isValid() );
  OGuard _container( getContainer(), this );
  return ( dynamic_cast< RangedContainer * >( getContainer() ) ) 
	-> setAt( ( dynamic_cast< RangedContainer * >( getContainer() ) ) -> getHighBound(),
			  aNewValue );
}

boolean RangedContainer::RContainerLastPosition::isValid() const
{
  return( ( dynamic_cast< RangedContainer * >( getContainer() ) ) -> isEmpty() ); 
}

Top *RangedContainer::RContainerLastPosition::getValue() const
{
  preC_( isValid() );
  OGuard _container( getContainer(), this );
  return ( dynamic_cast< RangedContainer * >( getContainer() ) ) 
	-> getAt( ( dynamic_cast< RangedContainer * >( getContainer() ) ) -> getHighBound() );
}

END_QR_NAMESPACE

#if defined(_INLINE)
#include "../src/Debug.ipp"
#endif


/*
 * $Log: RangedContainer.cpp,v $
 * Revision 1.1.1.1  2000/07/19 16:45:35  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:41  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:31  god
 * Imported sources
 *
 * Revision 1.4  1999/05/22 13:00:34  philogelos
 * Merging sources back from SPARC
 *
 * Revision 1.3  1999/03/03 19:09:38  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.2  1999/02/28 16:30:01  philogelos
 * LayeredContainer adde. Tuned for inlines.
 *
 * Revision 1.1.1.1  1998/11/25 20:11:02  philogelos
 * Quercus Robusta
 *
 * Revision 1.1  1998/07/09 09:30:41  philogelos
 * new files added to the repository
 * */
