//-*-C++-*-

/*  src/StringImplementation.cpp  */


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



/* $Id: StringImplementation.cpp,v 1.1.1.1 2000/07/19 16:42:20 philogelos Exp $ */
#if !defined(_INLINE)
static char cvsid[] = "@(#)$Id: StringImplementation.cpp,v 1.1.1.1 2000/07/19 16:42:20 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif


#include "defines.h"

#include "StringImplementation.hpp"
#include "Debug.hpp"
#include "String.hpp"

BEGIN_QR_NAMESPACE

StringImplementation *StringImplementation::nilStringImplementation = createNil();

////////////////////////////////////////////////////////////////////////////////

StringImplementation::~StringImplementation()
{
  sure( !isRef(), "deleting of referenced string-implementation" );
  sure( core != ( unichar * ) NIL, "deleting of null string-implementation" );

  if( haveToDelete )
	{
	  delete []core;
	}
  core = ( unichar * ) NIL;
}
////////////////////////////////////////////////////////////////////////////////

StringImplementation *StringImplementation::createNil()
{
  static unichar nilCore[ 1 ];

  nilCore[ 0 ] = ( unichar ) 0;
  return new StringImplementation( nilCore, false, false );
}

String  StringImplementation::toString() const
{
  return Object::toString(); /* + String( core, false, false ); */
}

String  StringImplementation::getString() const
{
  return String( core, false, false );
}

String  StringImplementation::getClassName() const
{
  return "StringImplementation";
}

#if defined( USE_PER_CLASS_NEW )
MemoryAllocator *StringImplementation::allocator = ( MemoryAllocator * ) NIL;
#endif

END_QR_NAMESPACE

#include "../src/StringImplementation.ipp"

#if defined(_INLINE)
#include "../src/Debug.ipp"
#endif


#if defined(_INLINE)
#include "../src/String.ipp"
#endif

/*
 * $Log: StringImplementation.cpp,v $
 * Revision 1.1.1.1  2000/07/19 16:42:20  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:39  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:28  god
 * Imported sources
 *
 * Revision 1.4  1999/05/22 13:00:31  philogelos
 * Merging sources back from SPARC
 *
 * Revision 1.3  1999/03/03 19:09:30  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.2  1999/02/28 15:57:47  philogelos
 * Tuned for inlines. ::toString() calmed down
 *
 * Revision 1.1.1.1  1998/11/25 20:11:01  philogelos
 * Quercus Robusta
 *
 * Revision 1.4  1998/07/09 09:04:46  philogelos
 * custom new/delete added
 *
 * Revision 1.3  1998/07/07 14:30:00  philogelos
 * Memory leak in SUNWspro dynamic_cast fixed.
 *
 * Revision 1.2  1998/06/22 18:13:01  philogelos
 * Enumerations and containers added
 *
 * Revision 1.1.1.1  1998/06/22 08:47:12  philogelos
 * First version under CVS
 *
 * Revision 1.1.1.1  1998/04/01 17:15:29  philogelos
 * first version under CVS
 * */
