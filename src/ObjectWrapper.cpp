// -*-C++-*- 

/*  src/ObjectWrapper.cpp  */

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



/* $Id: ObjectWrapper.cpp,v 1.1.1.1 2000/07/19 16:41:57 philogelos Exp $ */
#if !defined(_INLINE)
static char cvsid[] = "@(#)$Id: ObjectWrapper.cpp,v 1.1.1.1 2000/07/19 16:41:57 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif

#include "ObjectWrapper.hpp"
#include "LinkManager.hpp"
#include "String.hpp"
#include "Debug.hpp"

BEGIN_QR_NAMESPACE

ObjectWrapper::ObjectWrapper( Top *aValue )
{
  setValue( aValue );
}

ObjectWrapper::~ObjectWrapper()
{
  FCDONE( value );
}

Top *ObjectWrapper::getValue() const
{
  return value;
}

void ObjectWrapper::setValue( Top *aValue )
{
  FMOVE( value, aValue );
}

boolean ObjectWrapper::equals( const Top *anOther ) const
{
  return 
	( TCAST( anOther, ObjectWrapper ) != NULL ) &&
	( TCAST( anOther, ObjectWrapper ) -> getValue() -> equals( getValue() ) );
}

Top *ObjectWrapper::clone() const
{
  return new ObjectWrapper( getValue() );
}

String  ObjectWrapper::toString() const
{
  return Object::toString() + " value: " + value -> toString();
}

String  ObjectWrapper::getString() const
{
  return value -> getString();
}

String  ObjectWrapper::getClassName() const
{
  return "ObjectWrapper";
}

END_QR_NAMESPACE

#if defined(_INLINE)
#include "../src/Debug.ipp"
#endif


/*
 * $Log: ObjectWrapper.cpp,v $
 * Revision 1.1.1.1  2000/07/19 16:41:57  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:39  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:29  god
 * Imported sources
*/
