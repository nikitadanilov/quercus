// -*-C++-*- 

/*  src/containers/LayeredPosition.cpp  */

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



/* $Id: LayeredPosition.cpp,v 1.1.1.1 2000/07/19 16:45:10 philogelos Exp $ */
#if !defined(_INLINE)
static char cvsid[] = "@(#)$Id: LayeredPosition.cpp,v 1.1.1.1 2000/07/19 16:45:10 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif

#include "containers/Container.hpp"
#include "containers/LayeredPosition.hpp"
#include "LinkManager.hpp"
#include "String.hpp"
#include "OGuard.hpp"
#include "Debug.hpp"

BEGIN_QR_NAMESPACE

LayeredPosition::LayeredPosition( Container *aHost, Position *aBasePosition ) :
  PositionAdapter( aHost )
{
  preC_( aHost != NULL );
  FNNINIT( position, aBasePosition );
}

LayeredPosition::~LayeredPosition()
{
  FDONE( position );
}

boolean LayeredPosition::isValid() const
{
  return( position -> isValid() );
}

Top *LayeredPosition::getValue() const
{
  return( position -> getValue() );
}

boolean LayeredPosition::equals( const Top *anOther ) const
{
  if( DCAST( anOther, LayeredPosition ) == ( LayeredPosition * ) NULL )
	{
	  return false;
	}
  else
	{
	  LayeredPosition *other;

	  other = DCAST( anOther, LayeredPosition );
	  return( other -> position -> equals( position ) &&
			  other -> getContainer() -> equals( getContainer() ) );
	}
}

Top *LayeredPosition::clone() const
{
  return new LayeredPosition( getContainer(), position );
}

String  LayeredPosition::toString() const
{
  return PositionAdapter::toString() + 
	" container: " + getContainer() -> toString() +
	" position: " + position -> toString();
}

String  LayeredPosition::getClassName() const
{
  return "LayeredPosition";
}

END_QR_NAMESPACE

#if defined(_INLINE)
#include "../src/Debug.ipp"
#endif


/*
 * $Log: LayeredPosition.cpp,v $
 * Revision 1.1.1.1  2000/07/19 16:45:10  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:41  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:30  god
 * Imported sources
*/
