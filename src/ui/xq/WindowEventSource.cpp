// -*-C++-*- 

/*  src/ui/xq/WindowEventSource.cpp  */

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



/* $Id: WindowEventSource.cpp,v 1.2 2000/08/30 12:33:23 philogelos Exp $ */
#if !defined(_INLINE)
static char cvsid[] = "@(#)$Id: WindowEventSource.cpp,v 1.2 2000/08/30 12:33:23 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif

#include "ui/xq/XqCommon.hpp"
#include "Debug.hpp"

#if defined( USE_XQ )

BEGIN_QR_NAMESPACE

Xq::WindowEventSource::WindowEventSource( const Xq::Window *aWindow ) :
  window( aWindow )
{
  preC_( window != ( Xq::Window * ) NULL );
  OREG( window );
}

Xq::WindowEventSource::~WindowEventSource()
{
  FDONE( window );
}

Xq::Window *Xq::WindowEventSource::getWindow() const
{
  return ( Xq::Window * ) window;
}

Aq::AqEvent *Xq::WindowEventSource::getNextTypedElement() THROWS( Errno * )
{
  /* busy loop! (somewhat relieved by ::select() ) XXX */
  while( true )
	{
	  XEvent event;

#if defined( XQ_XCHECKEVENT_HACK )

	  fd_set checkXConnection;
	  fd_set writeXConnection;
	  fd_set errorXConnection;
	  int result;
	  	  
	  FD_ZERO( &checkXConnection );
	  FD_ZERO( &writeXConnection );
	  FD_ZERO( &errorXConnection );

	  FD_SET( getWindow() -> getDisplay() -> connectionNumber(), 
			  &checkXConnection );
	  FD_SET( getWindow() -> getDisplay() -> connectionNumber(), 
			  &writeXConnection );
	  FD_SET( getWindow() -> getDisplay() -> connectionNumber(), 
			  &errorXConnection );
	  
	  /* magic, more magic! */
	  result = ::select
		( getWindow() -> getDisplay() -> connectionNumber() + 1,
		  &checkXConnection, &writeXConnection, &errorXConnection, NULL );
	  //	  DLOG( "::select()" );
	  THR_SYSTEM -> sleep( 0, XQ_XCHECKEVENT_HACK_TIMEOUT );
	  if( result == -1 )
		{
		  throw new Errno
			( "Xq::WindowEventSource::getNextTypedElement(): select()", null );
		}
#endif	  
	  LOCK_X11_DISPLAY( getWindow() -> getDisplay() );
	  if( ::XCheckWindowEvent
		  ( getWindow() -> getDisplay() -> getData(), 
			getWindow() -> getId(),
			ExposureMask | KeyPressMask | ButtonPressMask | 
			StructureNotifyMask |
			KeyReleaseMask | ButtonReleaseMask | EnterWindowMask | 
			LeaveWindowMask |  PointerMotionMask | 
			/* PointerMotionHintMask | */ 
			Button1MotionMask | Button2MotionMask |Button3MotionMask | 
			Button4MotionMask | Button5MotionMask | ButtonMotionMask | 
			KeymapStateMask | ExposureMask |
			VisibilityChangeMask | ResizeRedirectMask | 
			SubstructureNotifyMask |
			SubstructureRedirectMask | FocusChangeMask | 
			PropertyChangeMask |
			ColormapChangeMask | OwnerGrabButtonMask, &event ) )
		{
#if defined( XQ_XCHECKEVENT_HACK )
		  sched_yield();
#endif	  
		  return XqEvent::create( getWindow() -> getDisplay(), &event,
								  getWindow() );
		}
#if defined( XQ_XCHECKEVENT_HACK )
	  sched_yield();
#endif	  
	}
}

String Xq::WindowEventSource::getClassName() const
{
  return "WindowEventSource";
}


END_QR_NAMESPACE

#if defined(_INLINE)
#include "../src/Debug.ipp"
#endif

/* USE_XQ */
#endif


/*
 * $Log: WindowEventSource.cpp,v $
 * Revision 1.2  2000/08/30 12:33:23  philogelos
 * update THROWS to correspond to the actual throws
 *
 * Revision 1.1.1.1  2000/07/19 16:54:37  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:44  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:35  god
 * Imported sources
*/
