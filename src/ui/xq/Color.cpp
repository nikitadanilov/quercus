// -*-C++-*- 

/*  src/ui/xq/Color.cpp  */

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



/* $Id: Color.cpp,v 1.2 2000/08/30 12:33:23 philogelos Exp $ */
#if !defined(_INLINE)
static char cvsid[] = "@(#)$Id: Color.cpp,v 1.2 2000/08/30 12:33:23 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif

#include "ui/xq/XqCommon.hpp"
#include "Debug.hpp"

#if defined( USE_XQ )

BEGIN_QR_NAMESPACE

Xq::Color::Color( Display *aDisplay, XColor *aColor ) :
  Xq::XqObject( aDisplay )
{
  setData( aColor );
}

Xq::Color::~Color()
{}

XColor *Xq::Color::getData() const
{
  return ( XColor * ) &x11Data;
}

void Xq::Color::setData( XColor *aData )
{
  PLAF -> memcpy
	( &x11Data, aData, sizeof( XColor ) );
}

Xq::Color *Xq::Color::create( Display *aDisplay, String aName ) 
  THROWS( XException * )
{
  preC_( aDisplay != NULL );

  XColor data;
  char *name;
  XID defColormap;

  name = aName.getChars();
  
  defColormap = aDisplay -> defaultColormap();
  LOCK_X11_DISPLAY( aDisplay );
  if( ::XParseColor( aDisplay -> getData(), defColormap, name, &data ) == 0 )
	{
	  delete []name;
	  throw new XException( String( "Cannot XParseColor( " ) + aName + " )" );
	}
  delete []name;
  if( ::XAllocColor( aDisplay -> getData(), defColormap, &data ) == 0 )
	{
	  throw new XException( String( "Cannot XAllocColor( " ) + aName + " )" );
	}
  return new Xq::Color( aDisplay, &data );
}

Xq::Color *Xq::Color::create( Display *aDisplay, unsigned long aPixel )
  THROWS( XException * )
{
  XColor data;

  data.pixel = aPixel;
  return new Xq::Color( aDisplay, &data );
}


END_QR_NAMESPACE

#if defined(_INLINE)
#include "../src/Debug.ipp"
#endif

/* USE_XQ */
#endif

/*
 * $Log: Color.cpp,v $
 * Revision 1.2  2000/08/30 12:33:23  philogelos
 * update THROWS to correspond to the actual throws
 *
 * Revision 1.1.1.1  2000/07/19 16:54:11  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:44  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:35  god
 * Imported sources
*/
