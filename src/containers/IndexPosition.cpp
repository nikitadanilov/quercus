// -*-C++-*- 

/*  src/containers/IndexPosition.cpp  */


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


/* $Id: IndexPosition.cpp,v 1.1.1.1 2000/07/19 16:45:02 philogelos Exp $ */
#if !defined(_INLINE)
static char cvsid[] = "@(#)$Id: IndexPosition.cpp,v 1.1.1.1 2000/07/19 16:45:02 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif


#include "containers/IndexPosition.hpp"
#include "containers/IndexableContainer.hpp"
#include "String.hpp"
#include "Debug.hpp"
#include "OGuard.hpp"

BEGIN_QR_NAMESPACE

IndexPosition::IndexPosition( const Index anIndex, 
							  IndexableContainer *aHost ) :
  MutablePositionAdapter( aHost ),
  PositionAdapter( aHost ),
  index_( anIndex )
{}

IndexPosition::~IndexPosition()
{}

Index IndexPosition::getIndex() const
{
  return index_;
}

boolean IndexPosition::isValid () const
{
  Container *hostContainer;

  hostContainer = getContainer();
  return DCAST( hostContainer, IndexableContainer ) -> 
	isValidIndex( getIndex() );
}

Top *IndexPosition::getValue() const
{
  Container *hostContainer;

  hostContainer = getContainer();
  return DCAST( hostContainer, IndexableContainer ) -> 
	getAt( getIndex() );
}

Top *IndexPosition::setValue( Top *aNewValue )
{
  Container *hostContainer;

  hostContainer = getContainer();
  return DCAST( hostContainer, IndexableContainer ) -> 
	setAt( getIndex(), aNewValue );
}

boolean IndexPosition::equals( const Top *anOther ) const
{
  OGuard _( anOther, this );

  if( DCAST( anOther, IndexPosition ) == null )
	{
	  return false;
	}

  IndexPosition *other = 
	DCAST( anOther, IndexPosition );
  return ( ( getContainer() == other -> getContainer() ) && 
		   ( getIndex() == other -> getIndex() ) );
}

Top *IndexPosition::clone() const
{
  Container *hostContainer;

  hostContainer = getContainer();
  return new 
	IndexPosition( getIndex(), 
				   DCAST( hostContainer, IndexableContainer ) );
}

String  IndexPosition::getString() const
{
  return PositionAdapter::getString() + 
	" index: " + String( getIndex(), 10 );
}

String  IndexPosition::getClassName() const
{
  return "IndexPosition";
}

END_QR_NAMESPACE

#if defined(_INLINE)
#include "../src/Debug.ipp"
#endif


#if defined(_INLINE)
#include "../src/String.ipp"
#endif

/*
 * $Log: IndexPosition.cpp,v $
 * Revision 1.1.1.1  2000/07/19 16:45:02  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:41  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:31  god
 * Imported sources
 *
 * Revision 1.4  1999/05/22 13:00:33  philogelos
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
 * Revision 1.1  1998/07/09 09:30:40  philogelos
 * new files added to the repository
 * */
