// -*-C++-*- 

/*  src/iter/enumerations/LookAheadEnumeration.cpp  */

/*
 * Author: Philogelos A. <Philogelos@yahoo.com>
 * Maintainer: Philogelos A.
 * Keywords: C++, library, containers
 *
 * Copyright (C) 1999, 2000 Philogelos A.
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



/* $Id: LookAheadEnumeration.cpp,v 1.1 2000/09/21 18:22:55 philogelos Exp $ */
#if !defined( _INLINE )
static char cvsid[] = "@(#)$Id: LookAheadEnumeration.cpp,v 1.1 2000/09/21 18:22:55 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif

#include "iter/enumerations/LookAheadEnumeration.hpp"
#include "inc/containers/lists/List.hpp"
#include "StringBuffer.hpp"
#include "Integer.hpp"
#include "Debug.hpp"

#include "exceptions/NoEntity.hpp"

BEGIN_QR_NAMESPACE

LookAheadEnumeration::LookAheadEnumeration( Enumeration *aBase )
{
  preC_( aBase != NULL );

  base = aBase;
  buffer = new List();
  anchors = new List();
  bufferStartOffset = 0;
}

LookAheadEnumeration::~LookAheadEnumeration()
{}

LAAnchor *LookAheadEnumeration::push()
{
  Index offset;
  LAAnchor *result;

  offset = bufferStartOffset;
  if( ! buffer -> isEmpty() )
	{
	  offset += buffer -> getCurrentIndex();
	}
  result = new Integer( offset );
  anchors -> append( result );

  postC_( result != NULL );
  return result;
}

void LookAheadEnumeration::pop( LAAnchor *anAnchor ) THROWS( NoEntity * )
{
  preC_( anAnchor != NULL );
  preC_( !anchors -> isEmpty() );
  preC_( anchors -> contains( anAnchor ) );

  OGuard _anchor( anAnchor, this );

  if( anAnchor == anchors -> car() )
	{
	  anchors -> behead();
	  if( anchors -> isEmpty() )
		{
		  bufferStartOffset += buffer -> getCardinality();
		  buffer = new List();
		}
	  else
		{
		  for( Index newHead = getCarIndex() ; bufferStartOffset < newHead ; 
			   ++bufferStartOffset )
			{
			  OGuard _item( buffer -> behead(), this );
			}
		}
	}
  else
	{
	  for( anchors -> toFirst() ; !anchors -> atEnd() ; anchors -> next() )
		{
		  if( anAnchor == anchors -> getCurrentValue() )
			{
			  anchors -> remove();
			  test_( !anchors -> isEmpty() );
			  return;
			}
		}
	  throw new NoEntity( "Unexistent anchor", null );
	}
}

void LookAheadEnumeration::rollTo( LAAnchor *anAnchor ) THROWS( NoEntity * )
{
  preC_( anAnchor != NULL );
  preC_( anchors -> contains( anAnchor ) );
  preC_( getIndex( anAnchor ) - bufferStartOffset <= buffer -> length() );
  preC_( getIndex( anAnchor ) - bufferStartOffset >= 0 );

  OGuard _anchor( anAnchor, this );

  if( ! buffer -> isEmpty() )
	{
	  buffer -> setCurrentAt( getIndex( anAnchor ) - bufferStartOffset );
	}
}

boolean LookAheadEnumeration::hasMoreElements()
{ 
  return !buffer -> isEmpty() || base -> hasMoreElements();
}

Top *LookAheadEnumeration::getNextElement()
{
  preC_( hasMoreElements() );

  Top *result;

  //  DLOGOBJECT( "getNextElement(): %s", this );

  if( buffer -> atEnd() )
	{
	  result = base -> getNextElement();
	  if( !anchors -> isEmpty() )
		{
		  test_( getCarIndex() <= bufferStartOffset );
		  buffer -> append( result );
		}
	  else
		{
		  test_( buffer -> isEmpty() );
		  ++bufferStartOffset;
		}
	}
  else
	{
	  result = buffer -> getCurrentValue();
	  buffer -> next();
	}
  return result;
}

String  LookAheadEnumeration::toString() const
{
  return Object::toString() + " in LA-buffer: " +
	buffer -> toString() + " anchors: " + anchors -> toString() +
	" looking at: " + 
	( buffer -> isEmpty() ? String( "<empty>" ) : 
	  ( buffer -> atEnd() ? String( "<end>" ) :
		buffer -> getCurrentValue() -> getString() ) );
}

String  LookAheadEnumeration::getClassName() const
{
  return "LookAheadEnumeration";
}

boolean LookAheadEnumeration::invariant() const
{
  return( ergo( anchors -> isEmpty(), buffer -> isEmpty() ) &&
		  ( bufferStartOffset >= 0 ) &&
		  ergo( !anchors -> isEmpty(), getCarIndex() == bufferStartOffset ) );
}

Index LookAheadEnumeration::getIndex( LAAnchor *anAnchor )
{
  preC_( anAnchor != NULL );

  OGuard _anchor( anAnchor, anAnchor );

  return( TCAST( anAnchor, Integer ) -> getInt() );
}

Index LookAheadEnumeration::getCarIndex() const
{
  preC_( !anchors -> isEmpty() );

  return getIndex( anchors -> car() );
}

END_QR_NAMESPACE

#if defined( _INLINE )
#include "../src/Debug.ipp"
#endif


/*
 * $Log: LookAheadEnumeration.cpp,v $
 * Revision 1.1  2000/09/21 18:22:55  philogelos
 * Used by recursive parser
 *
 */
