// -*-C++-*- 

/*  inc/FixedSizeAllocator.hpp  */

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



#ifndef __FIXEDSIZEALLOCATOR_HPP__
#define __FIXEDSIZEALLOCATOR_HPP__

/* $Id: FixedSizeAllocator.hpp,v 1.1.1.1 2000/07/19 16:55:41 philogelos Exp $ */

#include "MemoryAllocator.hpp"
#include "Object.hpp"
#include "defines.h"

BEGIN_QR_NAMESPACE

/**
   This sub-class of MemoryAllocator implements fast
   allocation of equally-sized memory blocks.

   It allocates memory segment with size multiple of required and keeps
   (it these very segments) free list. Then in most cases allocation,
   is just returning of the head of free list.

   It never returns memory back to the system (XXX and this is not very good).
   It keeps various allocation statistics if PROFILE_MEM_ALLOC defined.

   @see PROFILE_MEM_ALLOC
   @author Philogelos
   @created
*/
class FixedSizeAllocator : public MemoryAllocator,
						   public virtual Object
{

  /**
	 Creates instance that will allocate blocks of size aDefaultSize bytes
	 within segments of size aSegmentSize * aDefaultSize bytes. 
	 If PROFILE_MEM_ALLOC defined,
	 instance is registered in global list under name aName.

	 @precond ( aDefaultSize > 0 )
	 @precond ( aSegmentSize > 0 )
	 @see PROFILE_MEM_ALLOC
   */
public: FixedSizeAllocator( const Index aDefaultSize, const Index aSegmentSize,
							const char *aName );

  /**
   */
public: virtual ~FixedSizeAllocator();

  /**
	 Allocate memory. If free list is not empty, just return its head
	 (removing it from the list) otherwise,
	 allocate new segment, initialise free list in it; the rest as above.

	 @precond ( aNumberOfBytes == defaultSize )
  */
public: virtual void *allocate( Index aNumberOfBytes );

  /**
	 Add address to the head of free list. (No checks.)
  */
public: virtual void  deallocate( void *anAddress );

  /**
   */
public:  virtual Top *clone() const;

  /**
   */
public:  virtual String  toString() const;

  /**
   */
public:  virtual String  getClassName() const;

  /**
	 Segment data type.
  */
protected: struct Segment
{
  /**
	 Next segment in chain.
  */
  Segment *nextInChain;

  /**
	 Segment data. Here blocks are allocated.
  */
  char    *area;
};

protected: const Index defaultSize;
protected: const Index segmentSize;
protected: Segment    *segmentChain;
protected: char       *headOfFreeList;

#if defined( PROFILE_MEM_ALLOC )
protected: Index  totalAllocated;
protected: Index  actualAllocated;
protected: Index  maxAllocated;
protected: double averageAllocated;

protected: Index  totalSegments;
protected: Index  actualSegments;
protected: Index  maxSegments;
protected: double averageSegments;
#endif
protected: const char *name;
};

END_QR_NAMESPACE

/*
 * $Log: FixedSizeAllocator.hpp,v $
 * Revision 1.1.1.1  2000/07/19 16:55:41  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:16  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:39  god
 * Imported sources
*/

/* __FIXEDSIZEALLOCATOR_HPP__ */
#endif
