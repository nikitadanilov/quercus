// -*-C++-*- 

/*  src/containers/dicts/DictKeyPosition.cpp */

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


/* $Id: DictKeyPosition.cpp,v 1.1.1.1 2000/07/19 16:46:11 philogelos Exp $ */
#if !defined(_INLINE)
static char cvsid[] = "@(#)$Id: DictKeyPosition.cpp,v 1.1.1.1 2000/07/19 16:46:11 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif


#include "containers/dicts/DictKeyPosition.hpp"
#include "containers/dicts/Dictionary.hpp"
#include "String.hpp"
#include "LinkManager.hpp"
#include "Debug.hpp"

BEGIN_QR_NAMESPACE

DictKeyPosition::DictKeyPosition( Dictionary *aDict ) :
  MutablePositionAdapter( aDict ),
  PositionAdapter( aDict )
{
  key = ( DictKey * ) nil;
}

DictKeyPosition::~DictKeyPosition()
{
  FCDONE( key );
}

void DictKeyPosition::setKey( DictKey *aKey )
{
  FMOVE( key, aKey );
}

DictKey *DictKeyPosition::getKey() const
{
  return key;
}

void DictKeyPosition::remove()
{
  preC_( isValid() );
  getDictionary() -> removeKey( getKey() );
  postC_( !isValid() );
}

Dictionary *DictKeyPosition::getDictionary() const
{
  return TCAST( getContainer(), Dictionary );
}

Top *DictKeyPosition::setValue( Top *aNewValue )
{
  preC_( isValid() );
  return( getDictionary() -> setValueAtKey( getKey(), aNewValue ) );
}

boolean   DictKeyPosition::isValid() const
{
  return( getDictionary() -> isSuchKey( getKey() ) );
}

Top *DictKeyPosition::getValue() const
{
  preC_( isValid() );
  return( getDictionary() -> getValueAtKey( getKey() ) );
}

boolean DictKeyPosition::equals( const Top *anOther ) const
{
  if( DCAST( anOther, DictKeyPosition ) == NIL )
	{
	  return false;
	}
  return( MutablePositionAdapter::equals( anOther ) &&
		  ( ( ( getKey() == NULL ) && 
			  ( DCAST( anOther, DictKeyPosition ) -> getKey() == NULL ) ) || 
			( getKey() -> equals
			  ( DCAST( anOther, DictKeyPosition ) -> getKey() ) ) ) );
}

Top *DictKeyPosition::clone() const
{
  DictKeyPosition *result;

  result = new DictKeyPosition( getDictionary() );
  result -> setKey( getKey() );
  return result;
}


String  DictKeyPosition::getClassName() const
{
  return "DictKeyPosition";
}

END_QR_NAMESPACE

#if defined(_INLINE)
#include "../src/Debug.ipp"
#endif


/*
 * $Log: DictKeyPosition.cpp,v $
 * Revision 1.1.1.1  2000/07/19 16:46:11  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:41  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:32  god
 * Imported sources
 *
 * Revision 1.3  1999/05/22 13:00:54  philogelos
 * Merging sources back from SPARC
 *
 * Revision 1.2  1999/03/03 19:09:40  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.1  1999/02/28 16:30:24  philogelos
 * Tuned for inlines.
 * */
