// -*-C++-*- 

/*  src/ContextAdapter.cpp  */

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



/* $Id: ContextAdapter.cpp,v 1.1.1.1 2000/07/19 16:40:29 philogelos Exp $ */
#if !defined(_INLINE)
static char cvsid[] = "@(#)$Id: ContextAdapter.cpp,v 1.1.1.1 2000/07/19 16:40:29 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif

#include "containers/dicts/DumbDictionary.hpp"
#include "algorithms/enumerations/EnumerationAlgorithms.hpp"
#include "ContextAdapter.hpp"
#include "LinkManager.hpp"
#include "OGuard.hpp"
#include "PGuard.hpp"
#include "Debug.hpp"
#include "String.hpp"

BEGIN_QR_NAMESPACE

ContextAdapter::ContextAdapter()
{
  FINIT( attributes, new DumbDictionary() );
}

ContextAdapter::~ContextAdapter()
{
  FDONE( attributes );
}

Top *ContextAdapter::getBy( Top *aKey ) const
{
  OGuard _key( aKey, this );
  return( attributes -> getValueAtKey( aKey ) );
}

Top *ContextAdapter::setBy( Top *aKey, Top *aValue )
{
  OGuard _key( aKey, this );
  OGuard _value( aValue, this );
  if( isAt( aKey ) )
	{
	  return( attributes -> setValueAtKey( aKey, aValue ) );
	}
  else
	{
	  attributes -> addKey( aKey, aValue );
	  return nil;
	}
}

boolean ContextAdapter::isAt( Top *aKey ) const
{
  OGuard _key( aKey, this );
  return( attributes -> isSuchKey( aKey ) );
}

boolean ContextAdapter::equals( const Top *anOther ) const
{
  ContextAdapter *other;

  other = DCAST( anOther, ContextAdapter );
  OGuard _other( other, this );
  if( other == ( ContextAdapter * ) NIL )
	{
	  return false;
	}
  else
	{
	  return( attributes -> equals( other -> attributes ) );
	}
}

Top *ContextAdapter::clone() const
{
  ContextAdapter *result;

  result = new ContextAdapter();
  PGuard _result( result, this );
  EAlg::get() -> 
	add( result -> attributes, attributes -> getValueEnumeration() );
  return result;
}

String ContextAdapter::toString() const
{
  return Object::toString() + " attributes: " +
	attributes -> toString();
}

String  ContextAdapter::getString() const
{
  return Object::getString() + " attributes: " +
	attributes -> getString();
}

String  ContextAdapter::getClassName() const
{
  return "ContextAdapter";
}

END_QR_NAMESPACE

#if defined(_INLINE)
#include "../src/Debug.ipp"
#endif

/*
 * $Log: ContextAdapter.cpp,v $
 * Revision 1.1.1.1  2000/07/19 16:40:29  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:38  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:28  god
 * Imported sources
 *
 * Revision 1.3  1999/05/22 13:00:28  philogelos
 * Merging sources back from SPARC
 *
 * Revision 1.2  1999/03/03 19:09:25  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.1  1999/02/28 15:44:52  philogelos
 * Added
 * */
