// -*-C++-*- 

/*  src/ui/xq/Font.cpp  */

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



/* $Id: Font.cpp,v 1.3 2000/09/21 18:07:24 philogelos Exp $ */
#if !defined(_INLINE)
static char cvsid[] = "@(#)$Id: Font.cpp,v 1.3 2000/09/21 18:07:24 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif

#include "ui/xq/XqCommon.hpp"
#include "Debug.hpp"

#if defined( USE_XQ )

BEGIN_QR_NAMESPACE

Xq::Font::Font( Display *aDisplay, XFontStruct *aData ) :
  Xq::XqObject( aDisplay )
{
  x11Data = aData;
}

Xq::Font::~Font()
{
  LOCK_X11;
  XFreeFont( getDisplay() -> getData(), getData() );
}

XFontStruct *Xq::Font::getData() const
{
  return x11Data;
}

void Xq::Font::setData( XFontStruct *aData )
{
  if( x11Data != ( XFontStruct * ) NULL )
	{
	  LOCK_X11;
	  XFreeFont( getDisplay() -> getData(), x11Data );
	}
  x11Data = aData;
}  

Aq::Size Xq::Font::getWidth() const
{
  return getData() -> max_bounds.width;
}

Aq::Size Xq::Font::getHeight() const
{
  return getData() -> max_bounds.ascent + getData() -> max_bounds.descent;
}

Aq::Size Xq::Font::getAscent() const
{
  return getData() -> max_bounds.ascent;
}

Xq::Font *Xq::Font::createFixed( Display *aDisplay ) THROWS( XException * )
{
  return create( aDisplay, "fixed" );
}

Xq::Font *Xq::Font::create( Display *aDisplay, String aName ) 
  THROWS( XException * )
{
  preC_( aDisplay != ( Xq::Display * ) NULL );

  XFontStruct *data;
  char *name;

  name = aName.getChars();
  LOCK_X11_DISPLAY( aDisplay );
  data = XLoadQueryFont( aDisplay -> getData(), name );
  delete []name;
  if( data == ( XFontStruct * ) NULL )
	{
	  throw new XException( "Cannot XLoadQueryFont()" );
	}
  return new Xq::Font( aDisplay, data );
}

END_QR_NAMESPACE

#if defined(_INLINE)
#include "../src/Debug.ipp"
#endif

/* USE_XQ */
#endif

/*
 * $Log: Font.cpp,v $
 * Revision 1.3  2000/09/21 18:07:24  philogelos
 * updated throws clauses
 *
 * Revision 1.2  2000/08/30 12:33:23  philogelos
 * update THROWS to correspond to the actual throws
 *
 * Revision 1.1.1.1  2000/07/19 16:54:26  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:44  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:35  god
 * Imported sources
*/
