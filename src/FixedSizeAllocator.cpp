// -*-C++-*- 

/*  src/FixedSizeAllocator.cpp  */

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



/* $Id: FixedSizeAllocator.cpp,v 1.1.1.1 2000/07/19 16:40:43 philogelos Exp $ */
#if !defined(_INLINE)
static char cvsid[] = "@(#)$Id: FixedSizeAllocator.cpp,v 1.1.1.1 2000/07/19 16:40:43 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif

#include "FixedSizeAllocator.hpp"
#include "String.hpp"
#include "Debug.hpp"

BEGIN_QR_NAMESPACE

FixedSizeAllocator::FixedSizeAllocator( const Index aDefaultSize, 
										const Index aSegmentSize,
										const char *aName ) :
  defaultSize( aDefaultSize ),
  segmentSize( aSegmentSize ),
  name( aName )
{
  preC_( defaultSize > 0 );
  preC_( segmentSize > 0 );

  headOfFreeList = NIL;
  segmentChain = ( Segment * ) NIL;

#if defined( PROFILE_MEM_ALLOC )
  totalAllocated = 0;
  actualAllocated = 0;
  maxAllocated = 0;
  averageAllocated = 0;

  totalSegments = 0;
  actualSegments = 0;
  maxSegments = 0;
  averageSegments = 0;

  addToDump( this );
#endif
}

FixedSizeAllocator::~FixedSizeAllocator()
{
  Segment *current;

  current = segmentChain;
  while( current != ( Segment * ) NIL )
	{
	  current = current -> nextInChain;
	  delete []current;
	}
}

void *FixedSizeAllocator::allocate( Index aNumberOfBytes )
{
  preC_( aNumberOfBytes == defaultSize );

#if defined( PROFILE_MEM_ALLOC )
  Index total;

  total = ++totalAllocated;
  ++actualAllocated;
  if( actualAllocated > maxAllocated )
	{
	  maxAllocated = actualAllocated;
	}
  averageAllocated = ( ( averageAllocated * ( total - 1 ) ) + actualAllocated ) / total;
  averageSegments = ( ( averageSegments * ( total - 1 ) ) + actualSegments ) / total;
#endif

  if( headOfFreeList != NIL )
	{
	  char *result;

	  result = headOfFreeList;
	  headOfFreeList = * ( char ** ) headOfFreeList;
	  return result;
	}
  /* no free space in chunks. Allocate afresh */
  char    *shuttle;
  Segment *newSegment;

#if defined( PROFILE_MEM_ALLOC )
  ++totalSegments;
  ++actualSegments;
  if( actualSegments > maxSegments )
	{
	  maxSegments = actualSegments;
	}
#endif

  newSegment = new Segment();
  newSegment -> nextInChain = segmentChain;
  segmentChain = newSegment;

  newSegment -> area = new char[ segmentSize * defaultSize ];
  shuttle = ( newSegment -> area ) + defaultSize;
  for( Index i = 1 ; i < ( segmentSize - 1 ) ; ++i )
	{
	  *( ( char ** ) shuttle ) = shuttle + defaultSize;
	  shuttle += defaultSize;
	}
  *( char ** )shuttle = headOfFreeList;
  headOfFreeList = ( newSegment -> area ) + defaultSize;
  return ( void * ) ( newSegment -> area );
}

void  FixedSizeAllocator::deallocate( void *anAddress )
{
  if( anAddress == NULL )
	{
	  return;
	}
  ( *( char ** ) anAddress )= headOfFreeList;
  headOfFreeList = ( char * ) anAddress;

#if defined( PROFILE_MEM_ALLOC )
  --actualAllocated;
#endif
}

Top *FixedSizeAllocator::clone() const
{
  return ( Top * ) new FixedSizeAllocator( defaultSize, segmentSize, name );
}

String  FixedSizeAllocator::toString() const
{
  return Object::toString() + " defaultSize: " + String( defaultSize ) +
	" segmentSize: " + String( segmentSize ) + " cells" 
#if defined( PROFILE_MEM_ALLOC )
	+ 
	" name: " + String( name, false ) +
	" total calls: " + String( totalAllocated ) +
	" actually allocated: " + String( actualAllocated ) +
	" maximum allocated: " + String( maxAllocated ) +
	" average allocated: ( " + String( ( Index ) ( averageAllocated * 1000 ) ) + 
	" / 1000 )" +
	" total segments: " + String( totalSegments ) +
	" actual segments: " +  String( actualSegments ) +
	" average segments: " + String( ( Index ) ( averageSegments * 1000 ) ) +
	" / 1000 )"
#endif	
	;
}

String  FixedSizeAllocator::getClassName() const
{
  return "FixedSizeAllocator";
}

END_QR_NAMESPACE

#if defined(_INLINE)
#include "../src/Debug.ipp"
#endif


/*
 * $Log: FixedSizeAllocator.cpp,v $
 * Revision 1.1.1.1  2000/07/19 16:40:43  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:38  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:29  god
 * Imported sources
*/
