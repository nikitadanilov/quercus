// -*-C++-*- 

/*  src/ui/xq/Display.cpp  */

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



/* $Id: Display.cpp,v 1.1.1.1 2000/07/19 16:54:13 philogelos Exp $ */
#if !defined(_INLINE)
static char cvsid[] = "@(#)$Id: Display.cpp,v 1.1.1.1 2000/07/19 16:54:13 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif

#include "ui/xq/XqCommon.hpp"
#include "Debug.hpp"

#if defined( USE_XQ )

BEGIN_QR_NAMESPACE

static int ( *oldXIOErrorHandler )( struct _XDisplay *aDisplay ) = NULL;
static int ( *oldXErrorHandler )( struct _XDisplay *aDisplay, 
								  XErrorEvent *anEvent ) = NULL;
static int XqXIOErrorHandler( struct _XDisplay *aDisplay );
static int XqXErrorHandler( struct _XDisplay *aDisplay, 
							XErrorEvent *anEvent );


Xq::Display::Display( struct _XDisplay *aDisplay )
{
#if defined( USE_THREADS ) && defined( XQ_USE_X11_MUTEX )
  FINIT( x11Serializer, THR_SYSTEM -> recMutex() );
  setProtector( x11Serializer );
#endif

  LOCK_X11_DISPLAY( this );

  x11Data = aDisplay;
  FINIT( rootWindow, 
		 new Xq::Window( this, RootWindow( getData(), screen() ) ) );

  oldXErrorHandler = ::XSetErrorHandler( XqXErrorHandler );
  oldXIOErrorHandler = ::XSetIOErrorHandler( XqXIOErrorHandler );

  doneWithEvents = false;
}

Xq::Display::~Display()
{
#if defined( USE_THREADS ) && defined( XQ_USE_X11_MUTEX )
  FDONE( x11Serializer );
#endif
  FDONE( rootWindow );
  close();
}

void Xq::Display::close()
{
  LOCK_X11_DISPLAY( this );
  ::XCloseDisplay( getData() );
  doneWithEvents = true;
}

int Xq::Display::connectionNumber() const
{
  return ConnectionNumber( getData() );
}

int Xq::Display::screen() const
{
  return DefaultScreen( getData() );
}

Xq::Window *Xq::Display::getRootWindow() const
{
  return rootWindow;
}

Xq::Coord Xq::Display::getWidth() const
{
  LOCK_X11_DISPLAY( this );
  return DisplayWidth( getData(), screen() );
}

Xq::Coord Xq::Display::getHeight() const
{
  LOCK_X11_DISPLAY( this );
  return DisplayHeight( getData(), screen() );
}

XID Xq::Display::defaultColormap() const
{
  LOCK_X11_DISPLAY( this );
  return DefaultColormap( getData(), screen() );
}

int Xq::Display::blackPixel() const
{
  LOCK_X11_DISPLAY( this );
  return BlackPixel( getData(), screen() );
}

int Xq::Display::whitePixel() const
{
  LOCK_X11_DISPLAY( this );
  return WhitePixel( getData(), screen() );
}

int Xq::Display::defaultDepth() const
{
  LOCK_X11_DISPLAY( this );
  return DefaultDepth( getData(), screen() );
}

Visual *Xq::Display::defaultVisual( int aScreen ) const
{
  LOCK_X11_DISPLAY( this );
  return DefaultVisual( getData(), aScreen );
}

Xq::Display *Xq::Display::open()
{
  return open( NULL );
}

Xq::Display *Xq::Display::open( const char *aName )
{
  struct _XDisplay *data;

  data = ::XOpenDisplay( aName );
  if( data == ( struct _XDisplay * ) NULL )
	{
	  DLOG
		( "Cannot XOpenDisplay( \"%s\" )\n",
		  XDisplayName( aName ) );
	  throw new XException( "Cannot XOpenDisplay()" );
	}
  return new Xq::Display( data );
}

void Xq::Display::setData( struct _XDisplay *aDisplay )
{
  x11Data = aDisplay;
}

struct _XDisplay *Xq::Display::getData() const
{
  return x11Data;
}

#if defined( USE_THREADS ) && defined( XQ_USE_X11_MUTEX )
Mutex *Xq::Display::getX11Serialiser() const
{
  return x11Serializer;
}
#endif

Aq::AqEvent *Xq::Display::getNextTypedElement()
{
  XEvent event;

  LOCK_X11_DISPLAY( this );
  ::XNextEvent( getData(), &event );
  return XqEvent::create( this, &event );
}

String Xq::Display::getClassName() const
{
  return "Display";
}


static int XqXIOErrorHandler( struct _XDisplay *aDisplay )
{
  Backtrace trace;
  static const char *fatalXError = "Fatal X protocol error";

  trace.fill();
  DLOG( fatalXError );
  DLOGOBJECT( "Backtrace %s", &trace );

  if( oldXIOErrorHandler != NULL )
	{
	  oldXIOErrorHandler( aDisplay );
	}
  Debug::getLogger() -> exception( new Xq::XFatalException( aDisplay ) );
  Debug::getLogger() -> panic( fatalXError );
  return 0;
}

static int XqXErrorHandler( struct _XDisplay *aDisplay, 
							XErrorEvent *anEvent )
{
  Backtrace trace;
  static const char *xErrorMsg = "X protocol error";

  trace.fill();
  DLOG( xErrorMsg );
  DLOGOBJECT( "Backtrace %s", &trace );

  if( oldXErrorHandler != NULL )
	{
	  oldXErrorHandler( aDisplay, anEvent );
	}

  Debug::getLogger() -> exception( new Xq::XException( aDisplay, anEvent ) );
  Debug::getLogger() -> panic( xErrorMsg );
  return 0;
}

END_QR_NAMESPACE

#if defined(_INLINE)
#include "../src/Debug.ipp"
#endif

/* USE_XQ */
#endif

/*
 * $Log: Display.cpp,v $
 * Revision 1.1.1.1  2000/07/19 16:54:13  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:44  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:35  god
 * Imported sources
*/
