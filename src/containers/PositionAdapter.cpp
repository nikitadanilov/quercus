// -*-C++-*- 

/*  src/containers/PositionAdapter.cpp  */


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


/* $Id: PositionAdapter.cpp,v 1.1.1.1 2000/07/19 16:45:28 philogelos Exp $ */
#if !defined(_INLINE)
static char cvsid[] = "@(#)$Id: PositionAdapter.cpp,v 1.1.1.1 2000/07/19 16:45:28 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif


#include "containers/PositionAdapter.hpp"
#include "containers/Container.hpp"
#include "exceptions/NotImplemented.hpp"
#include "LinkManager.hpp"
#include "String.hpp"
#include "Debug.hpp"

BEGIN_QR_NAMESPACE

PositionAdapter::PositionAdapter( Container *aHost )
{
  FNNINIT( host, aHost );
  postC_( getContainer() == aHost );
}

PositionAdapter::~PositionAdapter()
{
  FDONE( getContainer() );
}

Container *PositionAdapter::getContainer() const
{
  return host;
}

String  PositionAdapter::getString() const
{
  return ( Object::getString() + " host: " + getContainer() -> getString() );
}

String  PositionAdapter::getClassName() const
{
  return "PositionAdapter";
}

boolean   PositionAdapter::isValid () const
{
  preC_( getContainer() != nil );
  return getContainer() -> isValid( this );
}

Top *  PositionAdapter::getValue() const
{
  preC_( getContainer() != nil );
  return getContainer() -> getValue( this );
}

END_QR_NAMESPACE

#if defined(_INLINE)
#include "../src/Debug.ipp"
#endif


#if defined(_INLINE)
#include "../src/String.ipp"
#endif

/*
 * $Log: PositionAdapter.cpp,v $
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
 * Revision 1.2  1999/02/28 16:30:01  philogelos
 * LayeredContainer adde. Tuned for inlines.
 *
 * Revision 1.1.1.1  1998/11/25 20:11:02  philogelos
 * Quercus Robusta
 *
 * Revision 1.1  1998/07/09 09:30:41  philogelos
 * new files added to the repository
 * */
