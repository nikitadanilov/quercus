// -*-C++-*- 

/*  src/ui/xq/XPainter.cpp  */

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



/* $Id: XPainter.cpp,v 1.1.1.1 2000/07/19 16:54:43 philogelos Exp $ */
#if !defined(_INLINE)
static char cvsid[] = "@(#)$Id: XPainter.cpp,v 1.1.1.1 2000/07/19 16:54:43 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif

#include "ui/xq/XqCommon.hpp"
#include "Debug.hpp"

#if defined( USE_XQ )

BEGIN_QR_NAMESPACE

Xq::XPainter::XPainter( Xq::GC *aGC, Xq::Drawable *aDrawable ) :
  Aq::Painter( aGC, aDrawable )
{
  FINIT( clearGC, Xq::GC::create( aDrawable -> getDisplay(), aDrawable ) );
  
  aGC -> copyTo( clearGC );
  clearGC -> setForeground( aGC -> getBackground() );

  arena = aDrawable;
}

Xq::XPainter::~XPainter()
{
  FDONE( clearGC );
}

void Xq::XPainter::setDrawable( Aq::Drawable *aDrawable )
{
  arena = TCAST( aDrawable, Xq::Drawable );
}

void Xq::XPainter::init()
{
//   getDrawable() -> lock( this );
//   getContext() -> lock( this );
}

void Xq::XPainter::done()
{
//   getContext() -> unlock( this );
//   getDrawable() -> unlock( this );
}

void Xq::XPainter::drawLine( Aq::CoordX aStartX, Aq::CoordY aStartY, 
							 Aq::CoordX anEndX, Aq::CoordY anEndY ) const
{
  getXDrawable() -> drawLine( getGC(), aStartX, aStartY, anEndX, anEndY );
}

void Xq::XPainter::drawPoint( Aq::CoordX aX, Aq::CoordY aY ) const
{
  getXDrawable() -> drawPoint( getGC(), aX, aY );
}

void Xq::XPainter::drawCString( Aq::CoordX aX, Aq::CoordY aY, 
									char *aString ) const
{
  preC_( aString != NULL );

  getXDrawable() -> drawCString( getGC(), aX, aY, aString );
}

void Xq::XPainter::fillRectangle( Aq::CoordX aX, Aq::CoordY aY,
								  Aq::Size aWidth, Aq::Size aHeight ) const
{
  getXDrawable() -> fillRectangle( getGC(), aX, aY, aWidth, aHeight );
}

void Xq::XPainter::clearRectangle( Aq::CoordX aX, Aq::CoordY aY,
								   Aq::Size aWidth, Aq::Size aHeight ) const
{
  getXDrawable() -> fillRectangle( getClearGC(), aX, aY, aWidth, aHeight );
}

void Xq::XPainter::copyFrom( Aq::CoordX aSourceX, Aq::CoordY aSourceY, 
							 Aq::Size aWidth, Aq::Size aHeight,
							 Aq::Drawable *aDrawable,
							 Aq::CoordX aDestX, Aq::CoordY aDestY ) const
{
  preC_( aDrawable != NULL );
  preC_( getDrawable() -> isCompatible( aDrawable ) );

  Xq::Drawable *destination;

  destination = TCAST( aDrawable, Xq::Drawable );
  OGuard _destination( destination, this );

  destination -> copyTo
	( getXDrawable(), getGC(), aSourceX, aSourceY, aWidth, aHeight, 
	  aDestX, aDestY );
}


Xq::Drawable *Xq::XPainter::getXDrawable() const
{
  return arena;
}

Xq::GC *Xq::XPainter::getGC() const
{
  return TCAST( getContext(), Xq::GC );
}

Xq::GC *Xq::XPainter::getClearGC() const
{
  return clearGC;
}

Xq::XPainter *Xq::XPainter::create( GC *aGC, Drawable *aDrawable, 
									Xq::Color *aFore )
{
  preC_( aDrawable != NULL );
  preC_( aGC != NULL );
  preC_( aFore != NULL );

  OGuard _port( aDrawable, aDrawable );
  OGuard _gc( aGC, aGC );
  OGuard _fore( aFore, aFore );

  Xq::GC *newGC;
  
  newGC = Xq::GC::create( aDrawable -> getDisplay(), aDrawable );
  OGuard _newGC( newGC, newGC );

  aGC -> copyTo( newGC );
  newGC -> setForeground( aFore );
  return new Xq::XPainter( newGC, aDrawable );
}


END_QR_NAMESPACE

#if defined(_INLINE)
#include "../src/Debug.ipp"
#endif

/* USE_XQ */
#endif

/*
 * $Log: XPainter.cpp,v $
 * Revision 1.1.1.1  2000/07/19 16:54:43  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:45  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:36  god
 * Imported sources
*/
