// -*-C++-*- 

/*  src/MemoryAllocator.cpp  */

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



/* $Id: MemoryAllocator.cpp,v 1.3 2001/06/23 12:28:41 philogelos Exp $ */
#if !defined(_INLINE)
static char cvsid[] = "@(#)$Id: MemoryAllocator.cpp,v 1.3 2001/06/23 12:28:41 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif

#include "containers/lists/List.hpp"
#include "MemoryAllocator.hpp"
#include "String.hpp"
#include "OGuard.hpp"
#include "Debug.hpp"

BEGIN_QR_NAMESPACE

#if defined( PROFILE_MEM_ALLOC )

void MemoryAllocator::dumpStatistics()
{
  if( dumpList == ( List * ) NIL )
	{
	  DLOG( "No memory allocators registered" );
	}
  else
	{
	  for( dumpList -> toFirst() ; 
		   ! ( dumpList -> atEnd() ) ; 
		   dumpList -> next() )
		{
		  Debug::getLogger() -> 
			logObject( TCAST( dumpList -> getCurrentValue(), 
							  MemoryAllocator ) );
		}
	}
}

void MemoryAllocator::addToDump( const MemoryAllocator *anElement )
{
  //  OGuard _element( anElement, this );
  if( dumpList == NIL )
	{
	  dumpList = new List();
	  dumpList -> dontManage();
	}
  dumpList -> append( const_cast< MemoryAllocator * >( anElement ) );
}

List *MemoryAllocator::dumpList = NIL;

#endif

END_QR_NAMESPACE

#if defined(_INLINE)
#include "../src/Debug.ipp"
#endif


/* 
 * $Log: MemoryAllocator.cpp,v $
 * Revision 1.3  2001/06/23 12:28:41  philogelos
 * casts of NULL removed. const_cast<> used in stead of C-style cast
 *
 * Revision 1.2  2000/09/21 18:03:49  philogelos
 * redundant cast removed
 *
 * Revision 1.1.1.1  2000/07/19 16:41:06  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.3  2000/04/09 12:00:48  god
 * CVS Log keyword correction finished
 *
 * Revision 1.2  2000/04/09 11:29:39  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:29  god
 * Imported sources
*/
