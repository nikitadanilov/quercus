// -*-C++-*- 

/*  src/iter/enumerations/TypedEnumeration.tpp  */


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


/* $Id: TypedEnumeration.tpp,v 1.1.1.1 2000/07/19 16:50:15 philogelos Exp $ */
#if !defined(_INLINE) && !defined(INCLUDE_TEMPLATES)
static char cvsid[] = "@(#)$Id: TypedEnumeration.tpp,v 1.1.1.1 2000/07/19 16:50:15 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif

#include "iter/enumerations/TypedEnumeration.hpp"
#include "exceptions/InvalidArgument.hpp"
#include "Debug.hpp"
#include "LinkManager.hpp"

BEGIN_QR_NAMESPACE

template< class X > Top *TypedEnumeration< X >::getNextElement()
{
  return TCAST( getNextTypedElement(), Top );
}

template< class X > TypedEnumeration< X > *TypedEnumeration< X >::upcast( Enumeration *aBase )
{
  return new EnumerationUpcaster< X >( aBase );
}

template< class X > EnumerationUpcaster< X >::EnumerationUpcaster( Enumeration *aBase )
{
  preCF_( aBase != nil );
  FINIT( base, aBase );
}

template< class X > EnumerationUpcaster< X >::~EnumerationUpcaster()
{
  FDONE( base );
}

template< class X > X *EnumerationUpcaster< X >::getNextTypedElement() THROWS( InvalidArgument * )
{
  Top *nextObject;

  nextObject = base -> getNextElement();
  if( DCAST( nextObject, X ) != nil )
	{
	  return DCAST( nextObject, X );
	}
  else
	{
	  throw ( new InvalidArgument
			  ( "EnumerationUpcaster: element of the base cannot be casted",
				null ) );
	  RET_THROW( NULL );
	}
}

template< class X > boolean EnumerationUpcaster< X >::hasMoreElements()
{
  return( base -> hasMoreElements() );
}

template< class X > String  EnumerationUpcaster< X >::getClassName() const
{
  return "EnumerationUpcaster";
}


END_QR_NAMESPACE

#if defined(_INLINE)
#include "../src/Debug.ipp"
#endif

/*
 * $Log: TypedEnumeration.tpp,v $
 * Revision 1.1.1.1  2000/07/19 16:50:15  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:43  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:29  god
 * Imported sources
 *
 * Revision 1.4  1999/05/22 13:00:56  philogelos
 * Merging sources back from SPARC
 *
 * Revision 1.3  1999/03/03 19:09:45  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.2  1999/02/28 16:30:48  philogelos
 * Tuned for inlines.
 *
 * Revision 1.1.1.1  1998/11/25 20:11:03  philogelos
 * Quercus Robusta
 * */
