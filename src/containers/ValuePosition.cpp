// -*-C++-*- 

/*  src/containers/ValuePosition.cpp  */

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



/* $Id: ValuePosition.cpp,v 1.1.1.1 2000/07/19 16:45:50 philogelos Exp $ */
#if !defined(_INLINE)
static char cvsid[] = "@(#)$Id: ValuePosition.cpp,v 1.1.1.1 2000/07/19 16:45:50 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif


#include "containers/ValuePosition.hpp"
#include "containers/Container.hpp"
#include "LinkManager.hpp"
#include "String.hpp"
#include "OGuard.hpp"
#include "Debug.hpp"

BEGIN_QR_NAMESPACE

ValuePosition::ValuePosition( Container *aHost, Top *aValue ) :
  PositionAdapter( aHost )
{
  FINIT( value, aValue );
}

ValuePosition::~ValuePosition()
{
  FCDONE( value );
}

boolean ValuePosition::isValid() const
{
  return( getContainer() -> contains( value ) );
}

Top *ValuePosition::getValue() const
{
  preC_( isValid() );
  return value;
}

Top *ValuePosition::clone() const
{
  return new ValuePosition( getContainer(), value );
}

String  ValuePosition::getString() const
{
  String result;
  
  result = PositionAdapter::getString();
  result += String( " value: " ) + 
	( ( value == null ) ? String::nullLiteral : value -> getString() );
  return result;
}

String  ValuePosition::getClassName() const
{
  return "ValuePosition";
}


END_QR_NAMESPACE

#if defined(_INLINE)
#include "../src/Debug.ipp"
#endif

/*
 * $Log: ValuePosition.cpp,v $
 * Revision 1.1.1.1  2000/07/19 16:45:50  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:41  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:32  god
 * Imported sources
 *
 * Revision 1.2  1999/03/03 19:09:39  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.1  1999/02/28 16:30:02  philogelos
 * LayeredContainer adde. Tuned for inlines.
 * */
