//-*-C++-*-

/*  src/StringImplementation.ipp  */


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


#ifndef __STRINGIMPLEMENTATION_IPP__
#define __STRINGIMPLEMENTATION_IPP__
/* $Id: StringImplementation.ipp,v 1.1.1.1 2000/07/19 16:42:36 philogelos Exp $ */

#include "platform/Platform.hpp"
#include "Debug.hpp"
  
BEGIN_QR_NAMESPACE

INLINE StringImplementation::StringImplementation( unichar *s, 
												   boolean shouldCopy,
												   boolean shouldDelete )
{
  for( len = 0 ; s[ len ] ; ++len )
	{}
  haveToCopy = shouldCopy;
  haveToDelete = shouldDelete;

  if( shouldCopy )
	{
	  core = new unichar[ len + 1 ];
	  PLAF -> 
		memcpy( core, s, len * sizeof( unichar ) );
	}
  else
	{
	  core = s;
	}
  addRef();
}


////////////////////////////////////////////////////////////////////////////////

INLINE StringImplementation::operator unichar *( void ) const
{
  return core;
}

////////////////////////////////////////////////////////////////////////////////

INLINE unichar &StringImplementation::operator []( const Index i ) const
{
  sure( core != ( unichar * ) NIL, "dereferencing null string-implementation" );
  sure( ( i >= 0 ) && ( i < length() ), "index out of range" );
  return core[ i ];
}

////////////////////////////////////////////////////////////////////////////////

INLINE const Index StringImplementation::length(void ) const
{
  return len;
}

////////////////////////////////////////////////////////////////////////////////

INLINE StringImplementation *StringImplementation::getNil(void )
{
  if( nilStringImplementation == null )
	{
	  nilStringImplementation = createNil();
	}
  return nilStringImplementation;
}

#if defined( USE_PER_CLASS_NEW )

END_QR_NAMESPACE
#include "FixedSizeAllocator.hpp"
BEGIN_QR_NAMESPACE

INLINE void *StringImplementation::operator new( size_t size )
{
  return getAllocator() -> allocate( ( Index ) size );
}

INLINE void StringImplementation::operator delete( void *anAddress )
{
  getAllocator() -> deallocate( anAddress );
}

MemoryAllocator *StringImplementation::getAllocator()
{
  if( allocator == ( MemoryAllocator * ) NIL )
	{
	  allocator = new FixedSizeAllocator( sizeof( StringImplementation ), 
										  20,
										  "StringImplementation" );
	}
  return allocator;
}
#endif

END_QR_NAMESPACE

/*
 * $Log: StringImplementation.ipp,v $
 * Revision 1.1.1.1  2000/07/19 16:42:36  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:39  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:28  god
 * Imported sources
 *
 * Revision 1.3  1999/05/22 13:00:31  philogelos
 * Merging sources back from SPARC
 *
 * Revision 1.2  1999/03/03 19:09:30  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.1.1.1  1998/11/25 20:11:01  philogelos
 * Quercus Robusta
 *
 * Revision 1.3  1998/07/09 09:04:46  philogelos
 * custom new/delete added
 *
 * Revision 1.2  1998/07/07 14:30:01  philogelos
 * Memory leak in SUNWspro dynamic_cast fixed.
 *
 * Revision 1.1.1.1  1998/06/22 08:47:12  philogelos
 * First version under CVS
 *
 * Revision 1.1.1.1  1998/04/01 17:15:29  philogelos
 * first version under CVS
 * */

/* __STRINGIMPLEMENTATION_IPP__ */
#endif
