// -*-C++-*- 

/*  src/platform/Xq.cpp  */

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



/* $Id: Xq.cpp,v 1.1.1.1 2000/07/19 16:55:01 philogelos Exp $ */

#if !defined(_INLINE)
static char cvsid[] = "@(#)$Id: Xq.cpp,v 1.1.1.1 2000/07/19 16:55:01 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif

#include "ui/xq/XqCommon.hpp"

#if defined( USE_XQ )

#if defined( TESTING )

#include "observe/EchoCondition.hpp"
#include "observe/ObservationContext.hpp"
#include "observe/EchoObserver.hpp"

#include <unistd.h>
#include <string.h>

BEGIN_QR_NAMESPACE

class TestApplet : public Xq::Applet
{
public: TestApplet( Xq::Drawable *aDrawable, 
					Xq::XqEventSource *aSource,
					Xq::GC *aGC ) :
  Xq::XqObject( aDrawable -> getDisplay() ),
  Xq::Applet( aDrawable, aSource, aGC  )
	{
	  Xq::Color *red;
	  Xq::Color *black;
	  x = y = 10;

	  red = Xq::Color::create( getDisplay(), "red" );
	  OGuard _red( red, this );
	  graphics -> setForeground( red );

	  FINIT( clearGraphics, Xq::GC::create( getDisplay(), aDrawable ) );

	  black = Xq::Color::create( getDisplay(), "black" );
	  OGuard _black( black, this );

	  clearGraphics -> setForeground( black );
	  clearGraphics -> setBackground( black );
	};

public: virtual ~TestApplet()
	{
	  FDONE( clearGraphics );
	};

public: virtual void deactivate()
	{
	  LOCK_X11_DISPLAY( drawable -> getDisplay() );
	  ::XFillRectangle( drawable -> getDisplay() -> getData(), 
						drawable -> getId(), clearGraphics -> getData(),
						x, y, 6, 6 );
	};

public: virtual void paint( Xq::Drawable *aDrawable, Xq::GC *aGraphics )
	{
	  LOCK_X11_DISPLAY( aDrawable -> getDisplay() );
	  ::XDrawRectangle( aDrawable -> getDisplay() -> getData(),
						aDrawable -> getId(),
						aGraphics -> getData(), x, y, 5, 5 );
	  // DLOG( "TestApplet::paint()" );
	};

public: int x;
public: int y;

protected: Xq::GC *clearGraphics;
};

class TestAppletThread : public Xq::AppletThread
{
public: TestAppletThread( TestApplet *anApplet, int aDelay, int aDx, int aDy ) :
  Xq::AppletThread( anApplet, aDelay )
	{
	  this -> dx = aDx;
	  this -> dy = aDy;
	};

public: void step()
	{
	  TestApplet *app;

	  if( rand() % 20 == 0 )
		{
		  dx += ( rand() % 3 ) - 1;
		  dy += ( rand() % 3 ) - 1;
		}

	  app = TCAST( applet, TestApplet );
	  if( ( app -> x + dx > 200 ) ||
		  ( app -> x + dx < 0 ) )
		{
		  dx = -dx;
		}
	  if( ( app -> y + dy > 200 ) ||
		  ( app -> y + dy < 0 ) )
		{
		  dy = -dy;
		}
	  app -> x += dx;
	  app -> y += dy;
	};
protected: int dx;
protected: int dy;
};

class TestCursor : public Runnable,
				   public virtual Object
{
public: TestCursor( Xq::Window *aWindow )
	{
	  preC_( aWindow != NULL );
	  
	  FNNINIT( window, aWindow );

	  for( int r = 0 ; r < 32 ; ++r )
		{
		  Xq::Pixmap *pix;

		  pix = Xq::Pixmap::create
			( window, String( "tmp/cursor-%2.2i.xbm" ).sprintf( 1, r ) );
		  FINIT( cursor[ r ], Xq::Cursor::create
				 ( window -> getDisplay(),
				   pix, pix,
				   Xq::Color::create( window -> getDisplay(), "green" ), 
				   Xq::Color::create( window -> getDisplay(), "red" ), 
				   32, 32 ) );
		}
	};

public: virtual ~TestCursor()
	{
	  for( int r = 0 ; r < 32 ; ++r )
		{
		  FDONE( cursor[ r ] );
		}
	  FDONE( window );
	}

public: virtual void *run()
	{
	  for( int i = 0 ; ; ++i )
		{
		  int r;

		  if( ( i / 32 ) % 2 == 0 )
			{
			  r = i % 32;
			}
		  else
			{
			  r = ( 63 - ( i % 64 ) ) % 32;
			}
		  window -> setCursor( cursor[ r ] );
		  THR_SYSTEM -> sleep( 0, 100000000 );
		}
	  return NULL;
	}

protected: Xq::Window *window;
protected: Xq::Cursor *cursor[ 32 ];
};

class TestFrameFeeder : public Runnable,
					public virtual Object
{
public: TestFrameFeeder( Xq::Drawable *aSource,
					 Xq::Drawable *aTarget,
					 Xq::GC *aGC,
					 Index aDelay )
	{
	  preC_( aSource != NULL );
	  preC_( aTarget != NULL );
	  preC_( aGC != NULL );
	  preC_( aDelay > 0 );
	  
	  FNNINIT( source, aSource );
	  FNNINIT( target, aTarget );
	  FNNINIT( gc, aGC );

	  delay = aDelay;
	};

public: virtual ~TestFrameFeeder()
	{
	  FDONE( gc );
	  FDONE( target );
	  FDONE( source );
	}

public: virtual void *run()
	{
	  while( true )
		{
		  {
			OGuard _lock( source, this );
			source -> copyTo( target, gc, 0, 0, 200, 200, 0, 0 );
		  }
		  THR_SYSTEM -> sleep( 0, delay );
		}
	  return NULL;
	}

protected: Xq::Drawable *source;
protected: Xq::Drawable *target;
protected: Xq::GC *gc;
protected: Index delay;
};

boolean Xq::tester( int )
{
  Xq::Display *display;
  Xq::Window *win;
  EchoObserver *echo;
  Xq::XqEventSource *eventSource;
  Xq::Pixmap *pix;
  Xq::GC *gc;

#if defined( XQ_USE_XINITTHREADS )
  test_( ::XInitThreads() != 0 );
#endif

  display = Xq::Display::open();
  display -> dontManage();

  DLOG( "typeid: %s", typeid( *new Object() ).name() );
  win = Xq::Window::createSimple
	( display, display -> getRootWindow(),
	  0, 0,
	  200, 200, 
	  3,
	  display -> whitePixel(), display -> blackPixel() );
  OGuard _win( win, win );
  win -> map();
  win -> selectInput
	( ExposureMask | KeyPressMask | ButtonPressMask | StructureNotifyMask |
	  KeyReleaseMask | ButtonReleaseMask | EnterWindowMask | LeaveWindowMask |
	  PointerMotionMask | /* PointerMotionHintMask | */ Button1MotionMask |
	  Button2MotionMask |Button3MotionMask | Button4MotionMask | 
	  Button5MotionMask | ButtonMotionMask | KeymapStateMask | ExposureMask |
	  VisibilityChangeMask | ResizeRedirectMask | SubstructureNotifyMask |
	  SubstructureRedirectMask | FocusChangeMask | PropertyChangeMask |
	  ColormapChangeMask | OwnerGrabButtonMask );

  echo = new EchoObserver();
  OGuard _echo( echo, echo );

  eventSource = win -> getXEventSource();
  OGuard _eventSource( eventSource, eventSource );

  pix = Xq::Pixmap::create( win, 200, 200, display -> defaultDepth() );
  OGuard _pix( pix, pix );

  pix -> setProtector( THR_SYSTEM -> recMutex() );

  gc = Xq::GC::create( pix -> getDisplay(), pix );
  OGuard _gc( gc, gc );

  gc -> setBackground( Xq::Color::create( display, "black" ) );
  gc -> setForeground( Xq::Color::create( display, "black" ) );

  {
	LOCK_X11_DISPLAY( display );
	::XFillRectangle( display -> getData(), pix -> getId(), 
					  gc -> getData(), 
					  0, 0, 200, 200 );
  }

  char bitmapData[ 64 * 8 ];
  for( int r = 0 ; r < 32 ; ++r )
	{
	  PLAF -> memset( bitmapData, 0, sizeof bitmapData );
	  for( int a = 0 ; a < 100 ; ++a )
		{
		  double angle;
		  int x;
		  int y;

		  angle = 2 * M_PI / 100 * a;
		  x = 32 + ( int ) ( r * cos( angle ) );
		  y = 32 - ( int ) ( r * sin( angle ) );
		  bitmapData[ y * 8 + ( x / 8 ) ] |= ( 1 << ( x % 8 ) );
		  if( r > 2 )
			{
			  x = 32 + ( int ) ( ( r - 2 ) * cos( angle ) );
			  y = 32 - ( int ) ( ( r - 2 ) * sin( angle ) );
			  bitmapData[ y * 8 + ( x / 8 ) ] |= ( 1 << ( x % 8 ) );
			}

		  if( a < 96 )
			{
			  for( int petal = 0 ; petal < 4 ; ++petal )
				{
				  angle = 2 * M_PI / 100 * a + 2 * M_PI / 32 * r + 
					M_PI / 2 * petal;
				  x = 32 + ( int ) ( a / 3 * cos( angle ) );
				  y = 32 - ( int ) ( a / 3 * sin( angle ) );
				  bitmapData[ y * 8 + ( x / 8 ) ] |= ( 1 << ( x % 8 ) );
				}
			}
		}
	  {
		  Xq::Pixmap *cursor;

		  cursor = Xq::Pixmap::create( win, bitmapData, 64, 64 );
		  OGuard _cursor( cursor, cursor );
		  cursor -> writeToXBMFile( String( "tmp/cursor-%2.2i.xbm" ).
									sprintf( 1, r ) );
	  }
	}


  //  eventSource -> addPassive( echo );

  THR_FACTORY -> createFromRunner( eventSource );
  THR_FACTORY -> createFromRunner( new TestCursor( win ) );
  THR_FACTORY -> createFromRunner( new TestFrameFeeder( pix, win, gc, 100000000 ) );

  for( int i = 0 ; i < 6 ; ++i )
	{
	  TestApplet *applet;
	  TestAppletThread *thread;

	  applet = new TestApplet( pix, eventSource, gc );

	  OGuard _applet( applet, applet );

	  thread = new TestAppletThread
		( applet, 10000000 * ( rand() % 10 + 1 ), 
		  rand() % 10, rand() % 10 );
	  //	  OGuard _thread( thread, thread );
	  thread -> start();
	}

//   TestApplet *applet1;
//   applet1 = new TestApplet( win, eventSource );
//   OGuard _applet1( applet1, applet1 );

//   TestApplet *applet2;
//   applet2 = new TestApplet( win, eventSource );
//   OGuard _applet2( applet2, applet2 );

//   TestAppletThread *thread1;
//   thread1 = new TestAppletThread( applet1, 100000000, 1, 2 );
//   OGuard _thread1( thread1, thread1 );
//   thread1 -> start();

//   TestAppletThread *thread2;
//   thread2 = new TestAppletThread( applet2, 100000000, 3, 1 );
//   OGuard _thread2( thread2, thread2 );
//   thread2 -> start();

  for( ; ; )
	{
	  THR_SYSTEM -> sleep( 1, 0 );
#if defined( XQ_USE_X11_MUTEX )
	  //	  DLOGOBJECT
	  //		( "Display mutex: %s", display -> getX11Serialiser() );
#endif
	}
  return true;
}

END_QR_NAMESPACE

/* TESTING */
#endif

#if defined(_INLINE)
#include "../src/Debug.ipp"
#endif

/* USE_XQ */
#endif

/*
 * $Log: Xq.cpp,v $
 * Revision 1.1.1.1  2000/07/19 16:55:01  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.5  2000/04/09 12:00:49  god
 * CVS Log keyword correction finished
 *
 * Revision 1.4  2000/04/09 11:29:45  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.3  2000/04/07 17:17:35  god
 * missing namespace corrected
 *
 * Revision 1.2  2000/04/06 13:48:45  god
 * namespace closed properly
 *
 * Revision 1.1.1.1  2000/04/01 14:07:35  god
 * Imported sources
 * */
