// -*-C++-*- 

/*  src/observe/EchoCondition.cpp  */

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



/* $Id: EchoCondition.cpp,v 1.1.1.1 2000/07/19 16:50:22 philogelos Exp $ */
#if !defined(_INLINE)
static char cvsid[] = "@(#)$Id: EchoCondition.cpp,v 1.1.1.1 2000/07/19 16:50:22 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif

#include "observe/EchoCondition.hpp"
#include "String.hpp"
#include "Debug.hpp"

BEGIN_QR_NAMESPACE

EchoCondition::EchoCondition( String aMessage ) :
  message( aMessage )
{}

void EchoCondition::announce()
{
  DLOGSTRING
	( "EchoCondition announcing: %s", message );
}

EchoCondition::~EchoCondition()
{}

Top *EchoCondition::clone() const
{
  return new EchoCondition( message );
}

String  EchoCondition::toString() const
{
  return Object::toString() + " with message: " + message;
}

String  EchoCondition::getClassName() const
{
  return "EchoCondition";
}

END_QR_NAMESPACE

#if defined(_INLINE)
#include "../src/Debug.ipp"
#endif


/*
 * $Log: EchoCondition.cpp,v $
 * Revision 1.1.1.1  2000/07/19 16:50:22  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:43  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:34  god
 * Imported sources
*/
