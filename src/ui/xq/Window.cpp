// -*-C++-*- 

/*  src/ui/xq/Window.cpp  */

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



/* $Id: Window.cpp,v 1.1.1.1 2000/07/19 16:54:35 philogelos Exp $ */
#if !defined(_INLINE)
static char cvsid[] = "@(#)$Id: Window.cpp,v 1.1.1.1 2000/07/19 16:54:35 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif

#include "ui/xq/XqCommon.hpp"
#include "Debug.hpp"

#if defined( USE_XQ )

BEGIN_QR_NAMESPACE

Xq::Window::Window( Display *aDisplay, XID anId ) :
  Xq::Drawable( aDisplay, anId ),
  Xq::XIDObject( aDisplay, anId ),
  Xq::XqObject( aDisplay ),
  Aq::Window( X11WindowSystem::x11WindowSystem )
{}

Xq::Window::~Window()
{
  LOCK_X11;
  ::XDestroyWindow( getDisplay() -> getData(), getId() );
}

void Xq::Window::map()
{
  LOCK_X11;
  ::XMapWindow( getDisplay() -> getData(), getId() );
}

void Xq::Window::unmap()
{
  LOCK_X11;
  ::XUnmapWindow( getDisplay() -> getData(), getId() );
}

void Xq::Window::clear()
{
  LOCK_X11;
  ::XClearWindow( getDisplay() -> getData(), getId() );
}

void Xq::Window::selectInput( long aMask )
{
  LOCK_X11;
  ::XSelectInput( getDisplay() -> getData(), getId(), aMask );
}

void Xq::Window::setSize( int aWidth, int aHeight )
{
  preC_( aWidth > 0 );
  preC_( aHeight > 0 );

  LOCK_X11;
  ::XResizeWindow( getDisplay() -> getData(), getId(), aWidth, aHeight );
}

void Xq::Window::setSizeHints( int aMinWidth, int aMinHeight,
							   int aMaxWidth, int aMaxHeight,
							   int aBaseWidth, int aBaseHeight,
							   int aWidthInc, int aHeightInc )
{
  XSizeHints hints;

  if( aMinWidth > 0 )
	{
	  test_( aMinHeight > 0 );

	  hints.min_width = aMinWidth;
	  hints.min_height = aMinHeight;
	  hints.flags |= PMinSize;
	}
  if( aMaxWidth > 0 )
	{
	  test_( aMaxHeight > 0 );

	  hints.max_width = aMaxWidth;
	  hints.max_height = aMaxHeight;
	  hints.flags |= PMaxSize;
	}
  if( aBaseWidth > 0 )
	{
	  test_( aBaseHeight > 0 );

	  hints.base_width = aBaseWidth;
	  hints.base_height = aBaseHeight;
	  hints.flags |= PBaseSize;
	}
  if( aWidthInc > 0 )
	{
	  test_( aHeightInc > 0 );

	  hints.width_inc = aWidthInc;
	  hints.height_inc = aHeightInc;
	  hints.flags |= PResizeInc;
	}
  ::XSetWMNormalHints( getDisplay() -> getData(), 
					   getId(), &hints );
}

void Xq::Window::setName( String aName )
{
  char *name;

  name = aName.getChars();
  LOCK_X11;
  ::XStoreName( getDisplay() -> getData(), 
				getId(), name );
  delete []name;
}

void Xq::Window::setClass( String aName, String aClass )
{
  char *appName;
  char *appClass;
  XClassHint hints;

  appName = aName.getChars();
  appClass = aClass.getChars();

  hints.res_name = appName;
  hints.res_class = appClass;
  LOCK_X11;
  XSetClassHint( getDisplay() -> getData(),
				 getId(), &hints );
  delete []appName;
  delete []appClass;
}

Aq::EventSource *Xq::Window::getEventSource() const
{
  return getXEventSource();
}

Xq::WindowEventSource *Xq::Window::getXEventSource() const
{
  return new Xq::WindowEventSource( this );
}

Xq::Window *Xq::Window::createSimple( Xq::Display *aDisplay,
									  Xq::Window *aParent,
									  int aX, int aY, 
									  int aWidth, int aHeight, 
									  int aBorderWidth,
									  int aForePixel, int aBackPixel )
{
  preC_( aDisplay != ( Xq::Display * ) NULL );
  preC_( aParent != ( Xq::Window * ) NULL );

  LOCK_X11_DISPLAY( aDisplay );
  return new Xq::Window
	( aDisplay, 
	  ::XCreateSimpleWindow( aDisplay -> getData(), aParent -> getId(),
							 aX, aY, aWidth, aHeight, aBorderWidth,
							 aForePixel, aBackPixel ) );
}

void Xq::Window::setCursor( Xq::Cursor *aCursor )
{
  preC_( aCursor != NULL );
  
  OGuard _cursor( aCursor, this );
  LOCK_X11;
  ::XDefineCursor( getDisplay() -> getData(), getId(), aCursor -> getId() );
}

void Xq::Window::unsetCursor()
{
  LOCK_X11;
  ::XUndefineCursor( getDisplay() -> getData(), getId() );
}

String Xq::Window::getClassName() const
{
  return "Window";
}

END_QR_NAMESPACE

#if defined(_INLINE)
#include "../src/Debug.ipp"
#endif

/* USE_XQ */
#endif

/*
 * $Log: Window.cpp,v $
 * Revision 1.1.1.1  2000/07/19 16:54:35  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:44  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:35  god
 * Imported sources
*/

