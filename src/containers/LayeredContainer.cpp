// -*-C++-*- 

/*  src/containers/LayeredContainer.cpp  */

/*
 * Author: Philogelos A. <Philogelos@yahoo.com>
 * Maintainer: Philogelos A.
 * Keywords: C++, library, containers
 *
 * Copyright (C) 1998, 1999 Philogelos A.
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



/* $Id: LayeredContainer.cpp,v 1.1.1.1 2000/07/19 16:45:06 philogelos Exp $ */
#if !defined(_INLINE)
static char cvsid[] = "@(#)$Id: LayeredContainer.cpp,v 1.1.1.1 2000/07/19 16:45:06 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif


#include "containers/LayeredContainer.hpp"
#include "containers/LayeredPosition.hpp"
#include "LinkManager.hpp"
#include "OGuard.hpp"
#include "Debug.hpp"

BEGIN_QR_NAMESPACE

PositionEnumeration *LayeredContainer::getEnumeration() const
{
  return new LayeredEnumeration( ( LayeredContainer * ) this );
}

boolean LayeredContainer::isEmpty() const
{
  preC_( getBaseContainer() != ( Container * ) NIL );
  return( getBaseContainer() -> isEmpty() );
}

Index LayeredContainer::getCardinality() const
{
  preC_( getBaseContainer() != ( Container * ) NIL );
  return( getBaseContainer() -> getCardinality() );
}

Position  *LayeredContainer::createFromBase( Position *aBasePosition )
{
  OGuard _position( aBasePosition, this );

  preC_( aBasePosition != ( const Position * ) NULL );
  preC_( getBaseContainer() -> isValid( aBasePosition ) );
  return new LayeredPosition( this, aBasePosition );
}

LayeredEnumeration::LayeredEnumeration( LayeredContainer *aContainer )
{
  FNNINIT( baseContainer, aContainer );

  FINIT( baseEnum, aContainer -> getBaseContainer() -> getEnumeration() );
  test_( baseEnum != NIL );
}

LayeredEnumeration::~LayeredEnumeration()
{
  FDONE( baseEnum );
  FDONE( baseContainer );
}


Position *LayeredEnumeration::getNextPosition()
{
  return( baseContainer -> createFromBase
		  ( baseEnum -> getNextPosition() ) );
}

boolean LayeredEnumeration::hasMoreElements()
{
  return( baseEnum -> hasMoreElements() );
}

END_QR_NAMESPACE

#if defined(_INLINE)
#include "../src/Debug.ipp"
#endif

/*
 * $Log: LayeredContainer.cpp,v $
 * Revision 1.1.1.1  2000/07/19 16:45:06  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:41  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:31  god
 * Imported sources
 *
 * Revision 1.3  1999/05/22 13:00:34  philogelos
 * Merging sources back from SPARC
 *
 * Revision 1.2  1999/03/03 19:09:36  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.1  1999/02/28 16:29:59  philogelos
 * LayeredContainer adde. Tuned for inlines.
 * */

