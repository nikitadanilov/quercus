// -*-C++-*- 

/*  src/store/FieldWriter.cpp  */

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



/* $Id: FieldWriter.cpp,v 1.1 2000/09/21 16:46:04 philogelos Exp $ */
#if !defined( _INLINE )
static char cvsid[] = "@(#)$Id: FieldWriter.cpp,v 1.1 2000/09/21 16:46:04 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif

#include "iter/enumerations/TypedEnumeration.hpp"
#include "store/StorePlatform.hpp"
#include "store/StorableDesc.hpp"
#include "store/FieldWriter.hpp"
#include "store/Storable.hpp"
#include "store/Field.hpp"
#include "Debug.hpp"

BEGIN_QR_NAMESPACE

void FieldWriter::storeSubobject( StoreSession *aSession, String aName, 
								  Storable *aValue ) THROWS( StoreError * )
{
  preC_( aSession != NULL );

  if( aValue != NULL )
	{
	  RefId id;

	  id = aSession -> addReference( aValue, aName );
	  if( id == -1 )
		{
		  CRef< TypedEnumeration< Field > > fields;

		  aSession -> pushObject( aName, aValue );
		  for( fields = aSession -> getCurrentObject() -> getStorableDesc() 
				 -> getFields() ; fields -> hasMoreElements() ; )
			{
			  CRef< Field > field;
			  CRef< FieldWriter > writer;

			  field = fields -> getNextTypedElement();
			  writer = aSession -> getPlatform() -> getWriter( aSession );
			  /* may be field -> store( aSession, this ), but no,
				 every problem can be solved by another level of indirection. */
			  field -> store( aSession, *writer );
			}
		  aSession -> popObject();
		}
	  else
		{
		  storeRef( aSession, aName, id );
		}
	}
}

END_QR_NAMESPACE

#if defined( _INLINE )
#include "../src/Debug.ipp"
#endif


/*
 * $Log: FieldWriter.cpp,v $
 * Revision 1.1  2000/09/21 16:46:04  philogelos
 * Persistency sub-system (first draft). Store only.
 *
 */
