// -*-C++-*- 

/*  src/containers/IndexableContainer.cpp  */


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


/* $Id: IndexableContainer.cpp,v 1.1.1.1 2000/07/19 16:45:03 philogelos Exp $ */
#if !defined(_INLINE)
static char cvsid[] = "@(#)$Id: IndexableContainer.cpp,v 1.1.1.1 2000/07/19 16:45:03 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif


#include "containers/IndexableContainer.hpp"
#include "containers/IndexPosition.hpp"
#include "Debug.hpp"
#include "OGuard.hpp"

BEGIN_QR_NAMESPACE

IndexableContainer::~IndexableContainer()
{}

IndexPosition *IndexableContainer::getPosition( const Index anIndex )
{
  preC_( isValidIndex( anIndex ) );
  return new IndexPosition( anIndex, this );
}

boolean IndexableContainer::isValid( const Position *aPosition ) const
{
  preC_( aPosition != null );

  OGuard _( aPosition, this );

  if( ( ( const Container * ) aPosition -> getContainer() ) != this )
	{
	  return false;
	}
  if( DCAST( aPosition, IndexPosition ) == null )
	{
	  return false;
	}
  return isValidIndex
	( DCAST( aPosition, IndexPosition ) -> getIndex() );
}

IndexableContainer::InvalidIndex::InvalidIndex( String aMessage, 
												const Top *const aSource ) :
  InvalidArgument( aMessage, aSource ),
#if defined( USE_STL )
  logic_error( aMessage.getChars() ),
#endif
  Exception( aMessage, aSource )
{}

String IndexableContainer::InvalidIndex::getDescription() const
{
  return InvalidArgument::getDescription() + 
	String( ": index is beyond the domain of this container", false );
}

String  IndexableContainer::InvalidIndex::getClassName() const
{
  return "InvalidIndex";
}


PiMap::PiMap( const Index aProj )
{
  setProj( aProj );
}

PiMap::~PiMap()
{}

void PiMap::setProj( const Index aProj )
{
  projection = aProj;
}

Top *PiMap::apply( Top *anArgument )
{
  IndexableContainer *tuple;

  tuple = dynamic_cast< IndexableContainer * >( anArgument );
  test_( tuple != ( IndexableContainer * ) NIL );
  test_( tuple -> isValidIndex( projection ) );
  return( tuple -> getAt( projection ) );
}

END_QR_NAMESPACE

#if defined(_INLINE)
#include "../src/Debug.ipp"
#endif


/*
 * $Log: IndexableContainer.cpp,v $
 * Revision 1.1.1.1  2000/07/19 16:45:03  philogelos
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
 * Revision 1.3  1999/03/03 19:09:36  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.2  1999/02/28 16:29:59  philogelos
 * LayeredContainer adde. Tuned for inlines.
 *
 * Revision 1.1.1.1  1998/11/25 20:11:02  philogelos
 * Quercus Robusta
 *
 * Revision 1.1  1998/07/09 09:30:41  philogelos
 * new files added to the repository
 * */
