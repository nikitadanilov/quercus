// -*-C++-*- 

/*  src/ui/wq/DC.cpp  */

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



/* $Id: DC.cpp,v 1.1.1.1 2000/07/19 16:52:38 philogelos Exp $ */
#if !defined(_INLINE)
static char cvsid[] = "@(#)$Id: DC.cpp,v 1.1.1.1 2000/07/19 16:52:38 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif

#include "ui/wq/WqCommon.hpp"
#include "Debug.hpp"

#if defined( USE_WQ )

BEGIN_QR_NAMESPACE

Wq::DC::DC( HANDLE aHandle ) : Win32Object( aHandle )
{}

Wq::DC::~DC()
{
  //	ReleaseDC( getHandle() );
  handle = NULL;
}

Wq::DC *Wq::DC::create( Window *aWindow )
{
  preC_( aWindow != NULL );

  OGuard _window( aWindow, aWindow );

  CREATE_OBJECT( Wq::DC, GetDC( aWindow -> getHandle() ), Wq::DC::create( Window *aWindow ) );
}

Wq::DC *Wq::DC::createInMemory( HANDLE aHandle )
{
  CREATE_OBJECT( Wq::DC, CreateCompatibleDC( aHandle ), 
				 Wq::DC::createInMemory() );
}

void Wq::DC::drawString( Aq::CoordX aX, Aq::CoordY aY, 
						 String aString )
{
  char *text;

  text = aString.getChars();
  drawCString( aX, aY, text );
  delete []text;
}

void Wq::DC::drawCString( Aq::CoordX aX, Aq::CoordY aY, 
						  char *aString )
{
  preC_( aString != NULL );

  GUI_WRAP( TextOut( getHandle(), aX, aY, aString, 
					 PLAF -> strlen( aString ) ), 0, Wq::DC::drawCString() );
}

void Wq::DC::fillRectangle( Aq::CoordX aX, Aq::CoordY aY, 
							Aq::Size aWidth, Aq::Size aHeight, Brush *aBrush )
{
  preC_( aBrush != NULL );

  OGuard _brush( aBrush, this );

  RECT rect;

  rect.left = aX;
  rect.top = aY;
  rect.right = aX + aWidth;
  rect.bottom = aY + aHeight;

  GUI_WRAP( FillRect( getHandle(), &rect, aBrush -> getHandle() ), 0, Wq::DC::fillRectangle() );
}

void Wq::DC::copyTo( Aq::CoordX aSourceX, Aq::CoordY aSourceY,
					 Aq::Size aWidth, Aq::Size aHeight,
					 DC *aDC, 
					 Aq::CoordX aDestX, Aq::CoordY aDestY,
					 DWORD anOp )
{
  preC_( aDC != NULL );

  OGuard _dc( aDC, this );

  GUI_WRAP( BitBlt( aDC -> getHandle(), aDestX, aDestY, aWidth, aHeight, 
					getHandle(), aSourceX, aSourceY, anOp ), NULL, Wq::DC::copyTo );
}

void Wq::DC::setFont( Font *aFont )
{
  selectObject( aFont );
}

void Wq::DC::setBitmap( Bitmap *aBitmap )
{
  selectObject( aBitmap );
}

void Wq::DC::setBrush( Brush *aBrush )
{
  selectObject( aBrush );
}

void Wq::DC::setPen( Pen *aPen )
{
  selectObject( aPen );
}

void Wq::DC::selectObject( Win32Object *anObject )
{
  preC_( anObject != NULL );

  OGuard _obj( anObject, this );

  GUI_WRAP( SelectObject( getHandle(), anObject -> getHandle() ), NULL, Wq::DC::selectObject() );
}

Wq::Font   *Wq::DC::getFont() const
{
  return new Wq::Font( getObject( OBJ_FONT ) );
}

Wq::Bitmap *Wq::DC::getBitmap() const
{
  return new Wq::Bitmap( getObject( OBJ_BITMAP ) );
}

Wq::Brush  *Wq::DC::getBrush() const
{
  return new Wq::Brush( getObject( OBJ_BRUSH ) );
}

Wq::Pen    *Wq::DC::getPen() const
{
  return new Wq::Pen( getObject( OBJ_PEN ) );
}

HANDLE  Wq::DC::getObject( UINT anObjType ) const
{
  HANDLE result;

  GUI_WRAP( result = GetCurrentObject( getHandle(), anObjType ), NULL, Wq::DC::getObject() );
  return result;
}

void Wq::DC::setTextForeground( COLORREF aColor )
{
  GUI_WRAP( SetTextColor( getHandle(), aColor ), CLR_INVALID, Wq::DC::setTextForeground() );
}

void Wq::DC::setTextBackground( COLORREF aColor )
{
  GUI_WRAP( SetBkColor( getHandle(), aColor ), CLR_INVALID, Wq::DC::setTextBackground() );
}

COLORREF Wq::DC::getTextForeground() const
{
  COLORREF result;

  GUI_WRAP( result = GetTextColor( getHandle() ), CLR_INVALID, Wq::DC::getTextForeground() );
  return result;
}

COLORREF Wq::DC::getTextBackground() const
{
  COLORREF result;

  GUI_WRAP( result = GetBkColor( getHandle() ), CLR_INVALID, 
			Wq::DC::getTextBackground() );
  return result;
}

END_QR_NAMESPACE

#if defined(_INLINE)
#include "../src/Debug.ipp"
#endif

/* USE_WQ */
#endif

/* $Log: DC.cpp,v $
/* Revision 1.1.1.1  2000/07/19 16:52:38  philogelos
/* stored sources into sourceforge.net CVS
/*
/* Revision 1.1.1.1  2000/04/01 14:07:36  god
/* Imported sources
/* */
