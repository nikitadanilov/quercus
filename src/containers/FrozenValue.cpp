// -*-C++-*- 

/*  src/containers/FrozenValue.cpp  */


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


/* $Id: FrozenValue.cpp,v 1.1.1.1 2000/07/19 16:45:01 philogelos Exp $ */
#if !defined(_INLINE)
static char cvsid[] = "@(#)$Id: FrozenValue.cpp,v 1.1.1.1 2000/07/19 16:45:01 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif


#include "containers/Container.hpp"
#include "containers/FrozenValue.hpp"
#include "LinkManager.hpp"
#include "String.hpp"
#include "Debug.hpp"
#include "Map.hpp"

BEGIN_QR_NAMESPACE

FrozenValue::FrozenValue( Container *aHost, Top *aValue ) :
  value( aValue ),
  container( aHost )
{
  if( getValue() != nil )
	{
	  OREG( getValue() );
	}
  if( getContainer() != NIL )
	{
	  OREG( ( Top * ) getContainer() );
	}
}

FrozenValue::~FrozenValue()
{
  FCDONE( container );
  FCDONE( value );
}

Top *FrozenValue::getValue() const
{
  return ( Top * ) value;
}

boolean   FrozenValue::isValid() const
{
  return true;
}

Container *FrozenValue::getContainer() const
{
  return ( Container * ) container;
}

Top *FrozenValue::clone() const
{
  return new FrozenValue( ( Container * ) getContainer(), ( Top * ) value );
}

String  FrozenValue::getString() const
{
  //   return String( "Container: ``" ) + ( getContainer() -> getString() ) +
  // 	"'' with value: " + value -> getString();
  return String( " with value: " ) + ( ( getValue() != null ) ? value -> getString() : String::nullLiteral );
}

String  FrozenValue::getClassName() const
{
  return "FrozenValue";
}

END_QR_NAMESPACE

#if defined(_INLINE)
#include "../src/Debug.ipp"
#endif


#if defined(_INLINE)
#include "../src/String.ipp"
#endif

/*
 * $Log: FrozenValue.cpp,v $
 * Revision 1.1.1.1  2000/07/19 16:45:01  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.4  2000/04/09 12:00:49  god
 * CVS Log keyword correction finished
 *
 * Revision 1.3  2000/04/09 11:29:40  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.2  2000/04/07 17:14:46  god
 * Handling of nulls in ::getString() corrected
 *
 * Revision 1.1.1.1  2000/04/01 14:07:31  god
 * Imported sources
 *
 * Revision 1.3  1999/03/03 19:09:36  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.2  1999/02/28 16:29:59  philogelos
 * LayeredContainer adde. Tuned for inlines.
 *
 * Revision 1.1.1.1  1998/11/25 20:11:02  philogelos
 * Quercus Robusta
 *
 * Revision 1.1  1998/07/09 09:30:40  philogelos
 * new files added to the repository
 * */
