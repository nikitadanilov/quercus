// -*-C++-*- 

/*  src/ui/xq/Cursor.cpp  */

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



/* $Id: Cursor.cpp,v 1.1.1.1 2000/07/19 16:54:11 philogelos Exp $ */
#if !defined(_INLINE)
static char cvsid[] = "@(#)$Id: Cursor.cpp,v 1.1.1.1 2000/07/19 16:54:11 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif

#include "ui/xq/XqCommon.hpp"
#include "Debug.hpp"

#if defined( USE_XQ )

BEGIN_QR_NAMESPACE

Xq::Cursor::Cursor( Display *aDisplay, XID anId ) :
  Xq::XIDObject( aDisplay, anId ),
  Xq::XqObject( aDisplay )
{
}

Xq::Cursor::~Cursor()
{
  LOCK_X11;
  ::XFreeCursor( getDisplay() -> getData(), getId() );
}

void Xq::Cursor::recolor( Xq::Color *fg, Xq::Color *bg )
{
  preC_( bg != NULL );
  preC_( fg != NULL );

  LOCK_X11;
  ::XRecolorCursor( getDisplay() -> getData(),
					getId(), fg -> getData(), bg -> getData() );
  
}

Xq::Cursor *Xq::Cursor::createStd( Xq::Display *aDisplay,
								   int shape )
{
  preC_( aDisplay != NULL );

  LOCK_X11_DISPLAY( aDisplay );
  return new Xq::Cursor( aDisplay,
						 ::XCreateFontCursor( aDisplay -> getData(),
											  shape ) );
}

Xq::Cursor *Xq::Cursor::create( Xq::Display *aDisplay,
								   Xq::Pixmap *aSource, Xq::Pixmap *aMask,
								   Xq::Color *foreground, 
								   Xq::Color *background,
								   Xq::Coord xHot, Xq::Coord yHot )
{
  preC_( aDisplay != NULL );
  preC_( aSource != NULL );
  preC_( aMask != NULL );
  preC_( foreground != NULL );
  preC_( background != NULL );

  OGuard _source( aSource, aSource );
  OGuard _mask( aMask, aMask );
  OGuard _fore( foreground, foreground );
  OGuard _back( background, background );

  LOCK_X11_DISPLAY( aDisplay );
  return new Xq::Cursor
	( aDisplay,
	  ::XCreatePixmapCursor( aDisplay -> getData(), 
							 aSource -> getId(), aMask -> getId(),
							 foreground -> getData(), background -> getData(), 
							 xHot, yHot ) );
}


END_QR_NAMESPACE

#if defined(_INLINE)
#include "../src/Debug.ipp"
#endif

/* USE_XQ */
#endif

/*
 * $Log: Cursor.cpp,v $
 * Revision 1.1.1.1  2000/07/19 16:54:11  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:44  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:35  god
 * Imported sources
*/
