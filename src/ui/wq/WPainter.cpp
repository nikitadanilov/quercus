// -*-C++-*- 

/*  src/ui/wq/WPainter.cpp  */

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



/* $Id: WPainter.cpp,v 1.1.1.1 2000/07/19 16:53:11 philogelos Exp $ */
#if !defined(_INLINE)
static char cvsid[] = "@(#)$Id: WPainter.cpp,v 1.1.1.1 2000/07/19 16:53:11 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif

#include "ui/wq/WqCommon.hpp"
#include "Debug.hpp"

#if defined( USE_WQ )

BEGIN_QR_NAMESPACE

Wq::WPainter::WPainter( Wq::GC *aGC, Wq::Drawable *aWindow ) :
  Painter( aGC, aWindow )
{
  dc = NULL;
  FNNINIT( arena, aWindow );
}

Wq::WPainter::~WPainter()
{
  FDONE( arena );
  test_( dc == NULL );
}

void Wq::WPainter::init()
{
  OGuard _self( this, this );

  test_( dc == NULL );
  FINIT( dc, getWDrawable() -> getDC() );
  getGC() -> flushTo( dc );
}

void Wq::WPainter::done()
{
  OGuard _self( this, this );

  test_( dc != NULL );
  getWDrawable() -> ungetDC( dc );
  FDONE( dc );
  dc = NULL;
}

void Wq::WPainter::drawLine( Aq::CoordX aStartX, 
							 Aq::CoordY aStartY, 
							 Aq::CoordX anEndX, 
							 Aq::CoordY anEndY ) const
{
  OGuard _self( this, this );

  test_( dc != NULL );
  //  dc -> drawLine( aStartX, aStartY, anEndX, anEndY );
}

void Wq::WPainter::drawPoint( Aq::CoordX aX, Aq::CoordY aY ) const
{
  OGuard _self( this, this );

  test_( dc != NULL );
  //  dc -> drawPoint( aX, aY );
}

void Wq::WPainter::drawCString( Aq::CoordX aX, Aq::CoordY aY, 
								char *aString ) const
{
  OGuard _self( this, this );

  test_( dc != NULL );
  dc -> drawCString( aX, aY, aString );
}

void Wq::WPainter::fillRectangle( Aq::CoordX aX, 
								  Aq::CoordY aY,
								  Aq::Size aWidth, 
								  Aq::Size aHeight ) const
{
  OGuard _self( this, this );

  test_( dc != NULL );
  dc -> fillRectangle( aX, aY, aWidth, aHeight, getGC() -> brush );
}

void Wq::WPainter::clearRectangle( Aq::CoordX aX, 
								   Aq::CoordY aY,
								   Aq::Size aWidth, 
								   Aq::Size aHeight ) const
{
  OGuard _self( this, this );

  test_( dc != NULL );
  dc -> fillRectangle( aX, aY, aWidth, aHeight, getGC() -> cleanBrush );
}

void Wq::WPainter::copyFrom( Aq::CoordX aSourceX, 
							 Aq::CoordY aSourceY, 
							 Aq::Size aWidth, Aq::Size aHeight,
							 Aq::Drawable *aDrawable,
							 Aq::CoordX aDestX, 
							 Aq::CoordY aDestY ) const
{
  OGuard _self( this, this );

  test_( dc != NULL );
  test_( aDrawable -> isCompatible( this ) );

  TCAST( aDrawable, Wq::Drawable ) -> getDC() -> copyTo
    ( aSourceX, aSourceY, aWidth, aHeight, dc, aDestX, aDestY, 
	  SRCCOPY );
}

void Wq::WPainter::setDrawable( Aq::Drawable *aDrawable )
{
  //  Aq::Painter::setDrawable( aDrawable );
  arena = TCAST( aDrawable, Wq::Drawable );
}

void Wq::WPainter::setWDrawable( Wq::Drawable *aDrawable )
{
  preC_( arena != NULL );

  FMOVE( arena, aDrawable );
}

Wq::Drawable *Wq::WPainter::getWDrawable() const
{
  return arena;
}

Wq::GC *Wq::WPainter::getGC() const
{
  return TCAST( getContext(), Wq::GC );
}

END_QR_NAMESPACE

#if defined(_INLINE)
#include "../src/Debug.ipp"
#endif

/* USE_WQ */
#endif

/* $Log: WPainter.cpp,v $
/* Revision 1.1.1.1  2000/07/19 16:53:11  philogelos
/* stored sources into sourceforge.net CVS
/*
/* Revision 1.1.1.1  2000/04/01 14:07:36  god
/* Imported sources
/* */
