// -*-C++-*- 

/*  inc/MemoryAllocator.hpp  */

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



#ifndef __MEMORYALLOCATOR_HPP__
#define __MEMORYALLOCATOR_HPP__

/* $Id: MemoryAllocator.hpp,v 1.1.1.1 2000/07/19 16:56:54 philogelos Exp $ */

#include "Top.hpp"
#include "defines.h"

BEGIN_QR_NAMESPACE

#if defined( PROFILE_MEM_ALLOC )
class List;
#endif

/**
   Interface for customized memory allocators.

   Current memory allocation scheme is follows: 

   <PR>
   [malloc|you_malloc()] - [ Platform::allocateMemory() ] - [ operator new() ] - 
     - [ MemoryAllocator::allocate() ] - [ class Foo::operator new() ]
   </PRE>

   @author Philogelos
   @created
*/
abstract class MemoryAllocator : public virtual Top
{
public: virtual void *allocate( Index aNumberOfBytes ) = 0;
public: virtual void  deallocate( void *anAddress ) = 0;
  
#if defined( PROFILE_MEM_ALLOC )
public: static void dumpStatistics();
protected: static void addToDump( const MemoryAllocator *anElement );

protected: static List *dumpList;
#endif
};

END_QR_NAMESPACE

/*
 * $Log: MemoryAllocator.hpp,v $
 * Revision 1.1.1.1  2000/07/19 16:56:54  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:16  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:39  god
 * Imported sources
*/

/* __MEMORYALLOCATOR_HPP__ */
#endif
