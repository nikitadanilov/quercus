// -*-C++-*- 

/*  src/algorithms/string/StringFilterAdapter.cpp  */

/*
 * Author: Philogelos A. <Philogelos@yahoo.com>
 * Maintainer: Philogelos A.
 * Keywords: C++, library, containers
 *
 * Copyright (C) 1999 Philogelos A.
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



/* $Id: StringFilterAdapter.cpp,v 1.1.1.1 2000/07/19 16:44:59 philogelos Exp $ */
#if !defined(_INLINE)
static char cvsid[] = "@(#)$Id: StringFilterAdapter.cpp,v 1.1.1.1 2000/07/19 16:44:59 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif

#include "algorithms/string/StringFilterAdapter.hpp"
#include "StringBuffer.hpp"
#include "LinkManager.hpp"
#include "OGuard.hpp"
#include "UCSChar.hpp"
#include "Debug.hpp"

BEGIN_QR_NAMESPACE

StringFilterAdapter::StringFilterAdapter() :
  base( ( StringFilter * ) NIL ), counter( 0 ), position( -1 )
{}

StringFilterAdapter::StringFilterAdapter( StringFilter *aBase ) :
  base( aBase ), counter( 0 ), position( -1 )
{
  if( aBase != ( StringFilter * ) NIL )
	{
	  OREG( aBase );
	}
}

StringFilterAdapter::~StringFilterAdapter()
{
  FCDONE( base );
}

void StringFilterAdapter::setBase( StringFilter *aBase )
{
  LinkManager::move( this, base, aBase );
  base = aBase;
}

StringFilter *StringFilterAdapter::getBase()
{
  return base;
}

void StringFilterAdapter::reset()
{
  counter = 0;
  position = -1;
  if( getBase() != ( StringFilter * ) NIL )
	{
	  getBase() -> reset();
	}
}

Index StringFilterAdapter::getCounter() const
{
  return counter;
}

Index StringFilterAdapter::getPosition()
{
  return position;
}

String StringFilterAdapter::asString()
{
  reset();
  return restAsString();
}

Index StringFilterAdapter::length()
{
  reset();
  return rest();
}

Index StringFilterAdapter::rest()
{
  Index result;
  
  for( result = 0 ; getNext() != ( unichar ) 0 ; ++result )
	{}
  
  return result;
}

String StringFilterAdapter::restAsString()
{
  StringBuffer result( StringBuffer::defaultLength, 
					   StringBuffer::defaultDelta );
  unichar c;
  
  while( ( c = getNext() ) != ( unichar ) 0 )
	{
	  result.add( c );
	}
  return result.asString();
}


END_QR_NAMESPACE

#if defined(_INLINE)
#include "../src/Debug.ipp"
#endif


/*
 * $Log: StringFilterAdapter.cpp,v $
 * Revision 1.1.1.1  2000/07/19 16:44:59  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:40  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:30  god
 * Imported sources
*/
