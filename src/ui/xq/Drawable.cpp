// -*-C++-*- 

/*  src/ui/xq/Drawable.cpp  */

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



/* $Id: Drawable.cpp,v 1.1.1.1 2000/07/19 16:54:15 philogelos Exp $ */
#if !defined(_INLINE)
static char cvsid[] = "@(#)$Id: Drawable.cpp,v 1.1.1.1 2000/07/19 16:54:15 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif

#include "ui/xq/XqCommon.hpp"
#include "Debug.hpp"

#if defined( USE_XQ )

BEGIN_QR_NAMESPACE

Xq::Drawable::Drawable( Display *aDisplay, XID anId ) :
  Xq::XIDObject( aDisplay, anId ),
  Xq::XqObject( aDisplay ),
  Aq::Drawable( X11WindowSystem::x11WindowSystem )
{}

void Xq::Drawable::copyTo( Xq::Drawable *aDest, Xq::GC *aGC, 
						   Xq::Coord aSrcX, Xq::Coord aSrcY, 
						   int aWidth, int aHeight,
						   Xq::Coord aDstX, Xq::Coord aDstY )
{
  preC_( aDest != NULL );
  preC_( aGC != NULL );
  preC_( aSrcX >= 0 );
  preC_( aSrcY >= 0 );
  preC_( aDstX >= 0 );
  preC_( aDstY >= 0 );
  preC_( aWidth >= 0 );
  preC_( aHeight >= 0 );
  
  LOCK_X11;
  ::XCopyArea( getDisplay() -> getData(),
			   getId(), aDest -> getId(), aGC -> getData(), 
			   aSrcX, aSrcY, aWidth, aHeight, aDstX, aDstY );
}

void Xq::Drawable::drawPoint( Xq::GC *aGC, Xq::Coord aX, Xq::Coord aY )
{
  preC_( aGC != NULL );

  LOCK_X11;
  ::XDrawPoint( getDisplay() -> getData(),
				getId(), aGC -> getData(), aX, aY );
}

void Xq::Drawable::drawLine( Xq::GC *aGC, 
					   Xq::Coord aStartX, Xq::Coord aStartY,
					   Xq::Coord anEndX, Xq::Coord anEndY )
{
  preC_( aGC != NULL );

  LOCK_X11;
  ::XDrawLine( getDisplay() -> getData(),
			   getId(), aGC -> getData(), aStartX, aStartY, anEndX, anEndY );
}

void Xq::Drawable::fillRectangle( Xq::GC *aGC, Xq::Coord aX, Xq::Coord aY, 
								  int aWidth, int aHeight )
{
  preC_( aGC != NULL );

  LOCK_X11;
  ::XFillRectangle( getDisplay() -> getData(),
					getId(), aGC -> getData(),
					aX, aY, aWidth, aHeight );
}

void Xq::Drawable::drawString( Xq::GC *aGC, Xq::Coord aX, Xq::Coord aY, 
							   String aString )
{
  char *string;

  string = aString.getChars();
  drawCString( aGC, aX, aY, string );
  delete []string;
}

void Xq::Drawable::drawCString( Xq::GC *aGC, Xq::Coord aX, Xq::Coord aY, 
								char *aString )
{
  preC_( aGC != NULL );

  LOCK_X11;
  ::XDrawString( getDisplay() -> getData(), getId(), aGC -> getData(),
				 aX, aY, aString, PLAF -> strlen( aString ) );
}



END_QR_NAMESPACE

#if defined(_INLINE)
#include "../src/Debug.ipp"
#endif

/* USE_XQ */
#endif

/*
 * $Log: Drawable.cpp,v $
 * Revision 1.1.1.1  2000/07/19 16:54:15  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:44  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:36  god
 * Imported sources
*/
