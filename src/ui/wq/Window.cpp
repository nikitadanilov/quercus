// -*-C++-*- 

/*  src/ui/wq/Window.cpp  */

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



/* $Id: Window.cpp,v 1.1.1.1 2000/07/19 16:53:25 philogelos Exp $ */
#if !defined(_INLINE)
static char cvsid[] = "@(#)$Id: Window.cpp,v 1.1.1.1 2000/07/19 16:53:25 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif

#include "ui/wq/WqCommon.hpp"
#include "Debug.hpp"

#if defined( USE_WQ )

BEGIN_QR_NAMESPACE

Wq::Window::Window( HANDLE aHandle ) : Win32Object( aHandle ),
  VIRTUAL_BASE( Aq, Window )( MSWindowSystem::msWindowSystem )
{
  test_( IsWindow( getHandle() ) );
  eventLoop = NULL;
  events = NULL;
  FINIT( triggers, new List() );
}

Wq::Window::~Window()
{
  test_( terminateMessage != 0 );
  PostMessage( getHandle(), terminateMessage, 0, 0 );
  FDONE( triggers );
  FCDONE( cursor );

  if( eventLoop != NULL )
	{
	  eventLoop -> join();
	  FDONE( eventLoop );
	}
  FCDONE( events );
  setHandle( NULL );
}

String Wq::Window::getDefaultClassName()
{
  static char *defClassName = "Wq::Window::defClassName";

  if( !defaultClassRegistered )
	{
	  WNDCLASS classInfo;

		
	  classInfo.style = CS_DBLCLKS | CS_GLOBALCLASS | CS_OWNDC; 
	  classInfo.lpfnWndProc = &Wq::Window::defWinProc; 
	  classInfo.cbClsExtra = 0;
	  classInfo.cbWndExtra = sizeof( void * );
	  classInfo.hInstance = GetModuleHandle( NULL ); 
	  classInfo.hIcon = NULL; 
	  classInfo.hCursor = NULL; 
	  classInfo.hbrBackground = ( void * ) COLOR_WINDOW; 
	  classInfo.lpszMenuName = NULL; 
	  classInfo.lpszClassName = defClassName; 

	  GUI_WRAP( RegisterClass( &classInfo ), 0, 
				Wq::Window::getDefaultClassName() );
	  defaultClassRegistered = true;
	}
  if( terminateMessage == 0 )
	{
	  GUI_WRAP( terminateMessage = RegisterWindowMessage
				( "Wq::terminateMessage" ), 0, 
				Wq::Window::getDefaultClassName() );
	}
  if( wakeUpMessage == 0 )
	{
	  GUI_WRAP( wakeUpMessage = RegisterWindowMessage
				( "Wq::wakeUpMessage" ), 0, 
				Wq::Window::getDefaultClassName() );
	}
  return defClassName;
}

void Wq::Window::show() const
{
  ShowWindow( getHandle(), SW_RESTORE );
  GUI_WRAP( UpdateWindow( getHandle() ), 0, Wq::Window::show() );
	GUI_WRAP( SetActiveWindow( getHandle() ), 0, Wq::Window::show() );
}

Wq::DC *Wq::Window::getDC() const
{
  CREATE_OBJECT( Wq::DC, GetDC( getHandle() ), Wq::Window::getDC() );
}

void Wq::Window::ungetDC( Wq::DC *aDC ) const
{
  preC_( aDC != NULL );

  OGuard _dc( aDC, this );
  ReleaseDC( getHandle(), aDC -> getHandle() );
}

void Wq::Window::setCursor( Wq::Cursor *aCursor )
{
  preC_( aCursor != NULL );

  OGuard _cursor( aCursor, this );
  OGuard _self( this, this );

  FMOVE( cursor, aCursor );
  PostMessage( getHandle(), wakeUpMessage, 0, ( LPARAM ) this );
}

void Wq::Window::showCursor( boolean toShow )
{
  ShowCursor( toShow );
}

Aq::EventSource *Wq::Window::getEventSource() const
{
  return getWEventSource();
}

Wq::WindowEventSource *Wq::Window::getWEventSource() const
{
  return events;
}

Mutex *winCreateLock = NULL;
Semaphore *winCreateSema = NULL;
Wq::Window *freshWindow = NULL;

void Wq::initClass()
{
  if( winCreateLock == NULL )
	{
	  winCreateLock = THR_SYSTEM -> mutex();
	  TCAST( winCreateLock, Object ) -> dontManage();
	}

  if( winCreateSema == NULL )
	{
	  winCreateSema = THR_SYSTEM -> semaphore( 0 );
	  TCAST( winCreateSema, Object ) -> dontManage();
	}
}

Wq::Window *Wq::Window::create()
{
  Wq::Window *result;

  initClass();
  MGuard _lock( winCreateLock, winCreateLock );

  test_( freshWindow == NULL );
  THR_FACTORY -> createFromFunc( &winLoop, NULL );
  winCreateSema -> dec();
  test_( freshWindow != NULL );
  result = freshWindow;
  freshWindow = NULL;
  return result;
}


LRESULT CALLBACK Wq::Window::defWinProc
( HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
  Wq::Window *win;

  SetLastError( 0 );
  GUI_WRAP( win = ( Wq::Window * ) GetWindowLong( hwnd, 0 ), 
			0, Wq::Window::defWinProc );

  if( uMsg == terminateMessage )
	{
	  throw new Wq::CloseWindowException();
	}
  if( uMsg == wakeUpMessage )
	{
	  test_( win != NULL );
	  test_( win == ( Wq::Window * ) lParam );
	  test_( wParam == NULL );
	  test_( win -> getHandle() == hwnd );
	  while( ! win -> triggers -> isEmpty() )
		{
		  Pair *trigger;

		  trigger = TCAST( win -> triggers -> behead(), Pair );
		  OGuard _trigger( trigger, win );
		  ( ( void ( * )( void * ) ) 
			( TCAST( trigger -> getAt( 1 ), DataWrapper ) 
			  -> getValue() ) )
			( TCAST( trigger -> getAt( 2 ), DataWrapper ) 
			  -> getValue() );
		}
	}
  if( win != NULL )
	{
	  if( win -> cursor != NULL )
		{
		  SetCursor( win -> cursor -> getHandle() );
		}
	}
  return DefWindowProc( hwnd, uMsg, wParam, lParam );
}

boolean Wq::Window::defaultClassRegistered = false;
UINT  Wq::Window::terminateMessage = 0;
UINT  Wq::Window::wakeUpMessage = 0;

void *Wq::Window::winLoop( void * )
{
  return( ( new Wq::WindowEventSource() ) -> run() );
}


boolean Wq::Window::isCursorWithin() const
{
  POINT cursorPosition;
  RECT winRect;

  GUI_WRAP( GetCursorPos( &cursorPosition ), 0, 
			Wq::Window::isCursorWithin() );
  GUI_WRAP( GetClientRect( getHandle(), &winRect ), 0,
			Wq::Window::isCursorWithin() );
  return( PtInRect( &winRect, cursorPosition ) );
}

void Wq::Window::move( Aq::CoordX aX, Aq::CoordY aY )
{
  GUI_WRAP( SetWindowPos( 
						 getHandle(), 
						 HWND_TOP , 
						 aX, aY,
						 0, 0,
						 SWP_NOSIZE | SWP_NOZORDER ), 0, Wq::Window::move() );
}

void Wq::Window::setSize( Aq::Size aWidth, 
						  Aq::Size aHeight )
{
	NONCLIENTMETRICS metrics;

	metrics.cbSize = sizeof metrics;
	GUI_WRAP( SystemParametersInfo( 
		SPI_GETNONCLIENTMETRICS, 
		sizeof metrics, &metrics, 0 ), 0, Wq::Window::setSize );

	test_( metrics.iBorderWidth >= 0 );
	test_( metrics.iCaptionWidth >= 0 );
	test_( metrics.iCaptionHeight >= 0 );

	GUI_WRAP( SetWindowPos( 
						 getHandle(), HWND_TOP, 
						 0, 0,
						 aWidth + 2 * metrics.iBorderWidth, 
						 aHeight + 
							2 * metrics.iBorderWidth +
							metrics.iCaptionHeight,
						 SWP_NOMOVE | SWP_NOZORDER ), 0, Wq::Window::move() );
}

void Wq::Window::setTitle( String aTitle )
{
  char *title;

  title = aTitle.getChars();
  if( !SetWindowText( getHandle(), title ) )
	{
	  delete []title;
	  throw new Errno( "SetWindowText() in Wq::Window::setTitle()", null,
					   GetLastError() );
	}
  delete []title;
}

void Wq::Window::makeForeground()
{
  GUI_WRAP( SetForegroundWindow( getHandle() ), 0, Wq::Window::makeForeground() );
}

END_QR_NAMESPACE

#if defined(_INLINE)
#include "../src/Debug.ipp"
#endif

/* USE_WQ */
#endif

/* $Log: Window.cpp,v $
/* Revision 1.1.1.1  2000/07/19 16:53:25  philogelos
/* stored sources into sourceforge.net CVS
/*
/* Revision 1.1.1.1  2000/04/01 14:07:36  god
/* Imported sources
/* */
