// -*-C++-*- 

/*  src/ui/xq/GC.cpp  */

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



/* $Id: GC.cpp,v 1.1.1.1 2000/07/19 16:54:28 philogelos Exp $ */
#if !defined(_INLINE)
static char cvsid[] = "@(#)$Id: GC.cpp,v 1.1.1.1 2000/07/19 16:54:28 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif

#include "ui/xq/XqCommon.hpp"
#include "Debug.hpp"

#if defined( USE_XQ )

BEGIN_QR_NAMESPACE

Xq::GC::GC( Xq::Display *aDisplay, struct _XGC *aGC ) :
  XqObject( aDisplay ),
  Aq::GraphicContext( X11WindowSystem::x11WindowSystem )
{
  x11Data = aGC;
}

Xq::GC::~GC()
{
  LOCK_X11;
  ::XFreeGC( getDisplay() -> getData(), x11Data );
}

struct _XGC *Xq::GC::getData() const
{
  return x11Data;
}

void Xq::GC::setData( struct _XGC *aGC )
{
  if( x11Data != ( struct _XGC * ) NULL )
	{
	  LOCK_X11;
	  ::XFreeGC( getDisplay() -> getData(), x11Data );
	}
  x11Data = aGC;
}

void Xq::GC::setBackground( Xq::Color *aColor )
{
  preC_( aColor != ( Xq::Color * ) NULL );
  OGuard _color( aColor, this );
  LOCK_X11;
  ::XSetBackground( getDisplay() -> getData(), 
					getData(), aColor -> getData() -> pixel );
}

void Xq::GC::setForeground( Xq::Color *aColor )
{
  preC_( aColor != ( Xq::Color * ) NULL );
  OGuard _color( aColor, this );
  LOCK_X11;
  ::XSetForeground( getDisplay() -> getData(), 
					getData(), aColor -> getData() -> pixel );
}

void Xq::GC::setFont( Xq::Font *aFont )
{
  preC_( aFont != ( Xq::Font * ) NULL );

  OGuard _font( aFont, this );
  LOCK_X11;
  ::XSetFont( getDisplay() -> getData(), getData(), 
			  aFont -> getData() -> fid );

}

void Xq::GC::setClipMask( Xq::Pixmap *aPixmap )
{
  preC_( aPixmap != NULL );

  OGuard _pixmap( aPixmap, this );

  LOCK_X11;
  ::XSetClipMask( getDisplay() -> getData(), 
				  getData(), aPixmap -> getId() );
}

Xq::Color *Xq::GC::getBackground() const
{
  XGCValues returnValues;

  LOCK_X11;
  ::XGetGCValues( getDisplay() -> getData(), 
				  getData(), GCBackground, &returnValues );
  return Xq::Color::create( getDisplay(), returnValues.background );
}

Xq::Color *Xq::GC::getForeground() const
{
  XGCValues returnValues;

  LOCK_X11;
  ::XGetGCValues( getDisplay() -> getData(), 
				  getData(), GCForeground, &returnValues );
  return Xq::Color::create( getDisplay(), returnValues.foreground );
}

void Xq::GC::copyTo( Xq::GC *aGC ) const
{
  preC_( aGC != NULL );

  LOCK_X11;
  ::XCopyGC( getDisplay() -> getData(), getData(),
			 GCFunction | GCPlaneMask |
			 GCForeground | GCBackground | GCLineWidth | GCLineStyle |
			 GCCapStyle | GCJoinStyle | GCFillStyle | GCFillRule | GCTile |
			 GCStipple | GCTileStipXOrigin | GCTileStipYOrigin | GCFont |
			 GCSubwindowMode | GCGraphicsExposures | GCClipXOrigin | 
			 GCClipYOrigin | GCDashOffset | GCArcMode,
			 aGC -> getData() );
}

void Xq::GC::setGraphicsExposures( boolean aFlag )
{
  LOCK_X11;
  ::XSetGraphicsExposures( getDisplay() -> getData(),
						   getData(), aFlag );
}

Xq::GC *Xq::GC::create( Xq::Display *aDisplay, Xq::Drawable *aDrawable )
{
  preC_( aDisplay != ( Xq::Display * ) NULL );
  preC_( aDrawable != ( Xq::Drawable * ) NULL );

  struct _XGC *data;

  unsigned int valueMask;
  XGCValues values;

  valueMask = GCPlaneMask;
  values.plane_mask = AllPlanes;

  LOCK_X11_DISPLAY( aDisplay );
  data = ::XCreateGC( aDisplay -> getData(), 
					  aDrawable -> getId(), valueMask, &values );
  //  DLOG( "XCreateGC: %p", data );
  return new Xq::GC( aDisplay, data );
}


END_QR_NAMESPACE

#if defined(_INLINE)
#include "../src/Debug.ipp"
#endif

/* USE_XQ */
#endif

/*
 * $Log: GC.cpp,v $
 * Revision 1.1.1.1  2000/07/19 16:54:28  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:44  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:35  god
 * Imported sources
*/

