// -*-C++-*- 

/*  src/containers/EnumeratedValues.cpp  */


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


/* $Id: EnumeratedValues.cpp,v 1.1.1.1 2000/07/19 16:45:00 philogelos Exp $ */
#if !defined(_INLINE)
static char cvsid[] = "@(#)$Id: EnumeratedValues.cpp,v 1.1.1.1 2000/07/19 16:45:00 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif


#include "containers/EnumeratedValues.hpp"
#include "containers/FrozenValue.hpp"
#include "String.hpp"
#include "Debug.hpp"
#include "LinkManager.hpp"

BEGIN_QR_NAMESPACE

EnumeratedValues::EnumeratedValues( ResettableEnumeration *anEnum )
{
  preC_( anEnum != NULL );
  valuesEnumeration = anEnum;
}

EnumeratedValues::~EnumeratedValues()
{}

PositionEnumeration *EnumeratedValues::getEnumeration() const
{
  return new EnumeratedValues::FrozenValues
	( ( Container * ) this, getValueEnumeration() );
}

Enumeration *EnumeratedValues::getValueEnumeration() const
{
  ResettableEnumeration *copy;

  copy = TCAST( valuesEnumeration -> clone(), ResettableEnumeration );
  copy -> reset();
  return copy;
}

Top *EnumeratedValues::clone() const
{
  return new EnumeratedValues( *valuesEnumeration );
}

Top *EnumeratedValues::getValue( const Position * aPosition )
{
  preC_( aPosition != null );
  return( aPosition -> getValue() );
}


String  EnumeratedValues::getClassName() const
{
  return "EnumeratedValues";
}

EnumeratedValues::FrozenValues::FrozenValues( Container *aContainer, 
											  Enumeration *anEnum )
{
  preC_( anEnum != NULL );
  preC_( aContainer != NULL );

  enumeration = anEnum;
  container = aContainer;
}

EnumeratedValues::FrozenValues::~FrozenValues()
{}

Position *EnumeratedValues::FrozenValues::getNextPosition()
{
  return new FrozenValue( *container, enumeration -> getNextElement() );
}

boolean EnumeratedValues::FrozenValues::hasMoreElements()
{
  return ( enumeration -> hasMoreElements() );
}

String  EnumeratedValues::FrozenValues::getClassName() const
{
  return "FrozenValues";
}

END_QR_NAMESPACE

#if defined(_INLINE)
#include "../src/Debug.ipp"
#endif

/*
 * $Log: EnumeratedValues.cpp,v $
 * Revision 1.1.1.1  2000/07/19 16:45:00  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.4  2000/04/09 12:00:48  god
 * CVS Log keyword correction finished
 *
 * Revision 1.3  2000/04/09 11:29:40  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.2  2000/04/06 13:25:06  god
 * converted to CRefs<>
 *
 * Revision 1.1.1.1  2000/04/01 14:07:31  god
 * Imported sources
 *
 * Revision 1.4  1999/05/22 13:00:33  philogelos
 * Merging sources back from SPARC
 *
 * Revision 1.3  1999/03/03 19:09:35  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.2  1999/02/28 16:29:59  philogelos
 * LayeredContainer adde. Tuned for inlines.
 *
 * Revision 1.1.1.1  1998/11/25 20:11:03  philogelos
 * Quercus Robusta
 * */
