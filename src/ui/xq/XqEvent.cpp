// -*-C++-*- 

/*  src/ui/xq/XqEvent.cpp  */

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



/* $Id: XqEvent.cpp,v 1.1.1.1 2000/07/19 16:55:01 philogelos Exp $ */
#if !defined(_INLINE)
static char cvsid[] = "@(#)$Id: XqEvent.cpp,v 1.1.1.1 2000/07/19 16:55:01 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif

#include "ui/xq/XqCommon.hpp"
#include "Debug.hpp"

#if defined( USE_XQ )

BEGIN_QR_NAMESPACE

Xq::XqEvent::XqEvent( Xq::Display *aDisplay, 
					  XEvent *aData ) :
  Xq::XqObject( aDisplay )
{
  PLAF -> memcpy
	( &event, aData, sizeof( XEvent ) );
}

Xq::XqEvent::~XqEvent()
{
  FCDONE( window );
}

XEvent *Xq::XqEvent::getData() const
{
  return ( XEvent * ) &event;
}

Xq::Window *Xq::XqEvent::getWindow() const
{
  return window;
}

void Xq::XqEvent::setWindow( Xq::Window *aWindow )
{
  FMOVE( window, aWindow );
}

Xq::XqEvent *Xq::XqEvent::create( Xq::Display *aDisplay, 
							  XEvent *aData,
							  Xq::Window *aWindow )
{
  preC_( aData != ( XEvent * ) NULL );

  Xq::XqEvent *result;

  result = NULL;
  switch( aData -> type )
	{
	case KeyPress:
	case KeyRelease:
	  result = new Xq::KeyEvent( aDisplay, aData );
	  break;
	case ButtonPress:
	case ButtonRelease:
	  result = new Xq::ButtonEvent( aDisplay, aData );
	  break;
	case MotionNotify:
	case EnterNotify:
	case LeaveNotify:
	  result = new Xq::MouseMotionEvent( aDisplay, aData );
	  break;
	case FocusIn:
	case FocusOut:
	  result = new Xq::FocusEvent( aDisplay, aData );
	  break;
	case Expose:
	case GraphicsExpose:
	case NoExpose:
	case VisibilityNotify:
	case MappingNotify:
	case CreateNotify:
	case UnmapNotify:
	case MapNotify:
	case CirculateNotify:
	  result = new Xq::WindowEvent( aDisplay, aData );
	  break;
	case DestroyNotify:
	  result = new Xq::DestroyEvent( aDisplay, aData );
	  break;
	case ConfigureNotify:
	case ResizeRequest:
	  result = new Xq::ResizeEvent( aDisplay, aData );
	  break;
	case SelectionClear:
	case SelectionRequest:
	case SelectionNotify:
	  result = new Xq::SelectionEvent( aDisplay, aData );
	  break;
	case ColormapNotify:
	case ClientMessage:

	case CirculateRequest:
	case PropertyNotify:
	case ConfigureRequest:
	case GravityNotify:
	case MapRequest:
	case ReparentNotify:
	case KeymapNotify:
	  result = new Xq::XqEvent( aDisplay, aData );
	  break;
	case LASTEvent:
	  test( false, "XEvent.type == LASTEvent ?!" );
	default:
	  test( false, "Unknown XEvent.type" );
	}
  result -> setWindow( aWindow );
  return result;
}

String Xq::XqEvent::toString() const
{
  return Xq::XqObject::toString() +
	String( " of type: %i serial: %lu SendEvent?: %s window: " ).
	sprintf( 1, event.type, event.xany.serial, 
			 ( event.xany.send_event ) ? "yes" : "no" ) +
	( ( window != ( Xq::Window * ) NULL ) ? window -> toString() : 
	  String( "unknown" ) );
}

String Xq::XqEvent::getClassName() const
{
  return "XqEvent";
}

Xq::KeyEvent::KeyEvent( Xq::Display *aDisplay, XEvent *aData ) :
  Xq::XqObject( aDisplay ),
  Xq::XqEvent( aDisplay, aData )
{
  preC_( aData != ( XEvent * ) NULL );
}

Xq::KeyEvent::~KeyEvent()
{}

unsigned int Xq::KeyEvent::getKeycode() const
{
  return event.xkey.keycode;
}

KeySym Xq::KeyEvent::getKeySym() const
{
  return keycodeToKeysym( getDisplay(), getKeycode() );
}

KeySym Xq::KeyEvent::keycodeToKeysym( Xq::Display *aDisplay,
									  unsigned int aKeycode )
{
  preC_( aDisplay != NULL );

  LOCK_X11_DISPLAY( aDisplay );
  return ::XKeycodeToKeysym( aDisplay -> getData(),
							 aKeycode, 0 );
}

String Xq::KeyEvent::keysymToString( Xq::Display *aDisplay,
									 ::KeySym aKeySym )
{
  preC_( aDisplay != NULL );

  LOCK_X11_DISPLAY( aDisplay );
  return ::XKeysymToString( aKeySym );
}

String Xq::KeyEvent::getClassName() const
{
  return "KeyEvent";
}

Xq::ButtonEvent::ButtonEvent( Xq::Display *aDisplay, XEvent *aData ) :
  Xq::XqObject( aDisplay ),
  Xq::XqEvent( aDisplay, aData )
{
  preC_( aData != ( XEvent * ) NULL );
}

Xq::ButtonEvent::~ButtonEvent()
{}

String Xq::ButtonEvent::getClassName() const
{
  return "ButtonEvent";
}

Xq::MouseMotionEvent::MouseMotionEvent( Xq::Display *aDisplay, XEvent *aData ) :
  Xq::XqObject( aDisplay ),
  Xq::XqEvent( aDisplay, aData )
{
  preC_( aData != ( XEvent * ) NULL );
}

Xq::MouseMotionEvent::~MouseMotionEvent()
{}

String Xq::MouseMotionEvent::getClassName() const
{
  return "MouseMotionEvent";
}

Xq::FocusEvent::FocusEvent( Xq::Display *aDisplay, XEvent *aData ) :
  Xq::XqObject( aDisplay ),
  Xq::XqEvent( aDisplay, aData )
{
  preC_( aData != ( XEvent * ) NULL );
}

Xq::FocusEvent::~FocusEvent()
{}

String Xq::FocusEvent::getClassName() const
{
  return "FocusEvent";
}

Xq::WindowEvent::WindowEvent( Xq::Display *aDisplay, XEvent *aData ) :
  Xq::XqObject( aDisplay ),
  Xq::XqEvent( aDisplay, aData )
{
  preC_( aData != ( XEvent * ) NULL );
}

Xq::WindowEvent::~WindowEvent()
{}

String Xq::WindowEvent::getClassName() const
{
  return "WindowEvent";
}

Xq::DestroyEvent::DestroyEvent( Xq::Display *aDisplay, XEvent *aData ) :
  Xq::XqObject( aDisplay ),
  Xq::XqEvent( aDisplay, aData )
{
  preC_( aData != ( XEvent * ) NULL );
}

Xq::DestroyEvent::~DestroyEvent()
{}

String Xq::DestroyEvent::getClassName() const
{
  return "DestroyEvent";
}

Xq::ResizeEvent::ResizeEvent( Xq::Display *aDisplay, XEvent *aData ) :
  Xq::XqObject( aDisplay ),
  Xq::XqEvent( aDisplay, aData )
{
  preC_( aData != ( XEvent * ) NULL );
}

Xq::ResizeEvent::~ResizeEvent()
{}

String Xq::ResizeEvent::getClassName() const
{
  return "ResizeEvent";
}

Xq::SelectionEvent::SelectionEvent( Xq::Display *aDisplay, XEvent *aData ) :
  Xq::XqObject( aDisplay ),
  Xq::XqEvent( aDisplay, aData )
{
  preC_( aData != ( XEvent * ) NULL );
}

Xq::SelectionEvent::~SelectionEvent()
{}

String Xq::SelectionEvent::getClassName() const
{
  return "SelectionEvent";
}

END_QR_NAMESPACE

#if defined(_INLINE)
#include "../src/Debug.ipp"
#endif

/* USE_XQ */
#endif

/*
 * $Log: XqEvent.cpp,v $
 * Revision 1.1.1.1  2000/07/19 16:55:01  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:45  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:36  god
 * Imported sources
*/
