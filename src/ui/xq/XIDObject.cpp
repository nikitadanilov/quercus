// -*-C++-*- 

/*  src/ui/xq/XIDObject.cpp  */

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



/* $Id: XIDObject.cpp,v 1.1.1.1 2000/07/19 16:54:41 philogelos Exp $ */
#if !defined(_INLINE)
static char cvsid[] = "@(#)$Id: XIDObject.cpp,v 1.1.1.1 2000/07/19 16:54:41 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif

#include "ui/xq/XqCommon.hpp"
#include "Debug.hpp"

#if defined( USE_XQ )

BEGIN_QR_NAMESPACE

Xq::XIDObject::XIDObject( Display *aDisplay, XID anId ) :
  Xq::XqObject( aDisplay )
{
  id = anId;
}

Xq::XIDObject::~XIDObject()
{}

void Xq::XIDObject::setId( XID anId )
{
  id = anId;
}

XID Xq::XIDObject::getId() const
{
  return id;
}

String Xq::XIDObject::toString() const
{
  return XqObject::toString() +
	String( " id: " ) + String( getId(), 16 );
}

String Xq::XIDObject::getClassName() const
{
  return "XIDObject";
}

END_QR_NAMESPACE

#if defined(_INLINE)
#include "../src/Debug.ipp"
#endif

/* USE_XQ */
#endif

/*
 * $Log: XIDObject.cpp,v $
 * Revision 1.1.1.1  2000/07/19 16:54:41  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:45  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:35  god
 * Imported sources
*/
