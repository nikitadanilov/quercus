// -*-C++-*- 

/*  src/containers/MutablePositionEnumeration.cpp  */


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


/* $Id: MutablePositionEnumeration.cpp,v 1.1.1.1 2000/07/19 16:45:28 philogelos Exp $ */
#if !defined(_INLINE)
static char cvsid[] = "@(#)$Id: MutablePositionEnumeration.cpp,v 1.1.1.1 2000/07/19 16:45:28 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif


#include "containers/MutablePositionEnumeration.hpp"
#include "containers/PositionEnumeration.hpp"
#include "containers/MutablePosition.hpp"
#include "containers/Position.hpp"
#include "String.hpp"
#include "defines.h"
#include "Debug.hpp"
#include "LinkManager.hpp"

BEGIN_QR_NAMESPACE

Position *MutablePositionEnumeration::getNextPosition()
{
  return getNextMutablePosition();
}

MutablePositionEnumeration *MutablePositionEnumeration::createMutableFrom( TypedEnumeration< MutablePosition > *anEnum )
{
  return new MPEFromTyped( anEnum );
}

MPEFromTyped::MPEFromTyped( TypedEnumeration< MutablePosition > *anEnum )
{
  FNNINIT( enumeration, anEnum );
}

MPEFromTyped::~MPEFromTyped()
{
  FDONE( enumeration );
}

MutablePosition *MPEFromTyped::getNextMutablePosition()
{
  return( enumeration -> getNextTypedElement() );
}

boolean MPEFromTyped::hasMoreElements()
{
  return( enumeration -> hasMoreElements() );
}

String  MPEFromTyped::getClassName() const
{
  return "MPEFromTyped";
}

Top    *MPEFromTyped::clone() const
{
  return new MPEFromTyped( enumeration );
}

END_QR_NAMESPACE

#if defined(_INLINE)
#include "../src/Debug.ipp"
#endif

/*
 * $Log: MutablePositionEnumeration.cpp,v $
 * Revision 1.1.1.1  2000/07/19 16:45:28  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:41  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:31  god
 * Imported sources
 *
 * Revision 1.3  1999/03/03 19:09:37  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.2  1999/02/28 16:30:00  philogelos
 * LayeredContainer adde. Tuned for inlines.
 *
 * Revision 1.1.1.1  1998/11/25 20:11:03  philogelos
 * Quercus Robusta
 * */
