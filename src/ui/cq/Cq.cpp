// -*-C++-*- 

/*  src/platform/Cq.cpp  */

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



/* $Id: Cq.cpp,v 1.2 2000/10/20 20:29:20 philogelos Exp $ */
#if !defined(_INLINE)
static char cvsid[] = "@(#)$Id: Cq.cpp,v 1.2 2000/10/20 20:29:20 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif

#include "ui/cq/Cq.hpp"

#if defined( USE_CQ )

#include "Debug.hpp"
#include "LinkManager.hpp"
#include "platform/threads/ThreadFactory.hpp"
#include "platform/threads/MGuard.hpp"
#include "exceptions/Errno.hpp"

#define C_LOCK MGuard _lockCurses( Cq::cursesLock, Cq::cursesLock )

#if defined( __GNUC__ )
#define __functionName __PRETTY_FUNCTION__
#else
#define __functionName ""
#endif

#if defined( USE_STL )
#define CHECK_UNCAUGHT ( std::uncaught_exception() )
#else
#define CHECK_UNCAUGHT ( false )
#endif

#define ICCALL( CALL ) ACCALL( CALL, __functionName, ERR )
#define PCCALL( CALL ) ACCALL( CALL, __functionName, NULL )

#define ACCALL( CALL, SITE, WRONG_VALUE ) \
   { \
     C_LOCK; \
     if( ( ( CALL ) == WRONG_VALUE ) && !CHECK_UNCAUGHT )\
       { \
         Cq::restore(); \
		 DLOGSTRING \
            ( "Curses error: %s", \
              String( #CALL " failed in " #SITE " (" __FILE__ ":" ) + \
              String( ( Index ) __LINE__, 10 ) + ")" ); \
	   } \
   } 
// 		 throw new Errno
//             ( String( #CALL " failed in " #SITE " (" __FILE__ ":" ) +
//               String( ( Index ) __LINE__, 10 ) + ")", null );

BEGIN_QR_NAMESPACE

Cq::CursesUI::CursesUI()
{}

Cq::CursesUI::~CursesUI()
{}

int Cq::CursesUI::getScreenWidth()
{
  return COLS;
}

int Cq::CursesUI::getScreenHeight()
{
  return LINES;
}

boolean Cq::CursesUI::hasColors()
{
  return has_colors();
}

Aq::Painter *Cq::CursesUI::createPainter( Aq::GraphicContext *aContext, 
										  Aq::Drawable *aDrawable ) const
{
  preC_( aContext != NULL );
  preC_( aDrawable != NULL );

  preC_( aContext -> isCompatible( Cq::CursesUI::cursesUI ) );
  preC_( aDrawable -> isCompatible( Cq::CursesUI::cursesUI ) );

  return new Cq::Painter( TCAST( aContext, Cq::GC ),
						  TCAST( aDrawable, Cq::Window ) );
}

Cq::CursesUI *Cq::CursesUI::cursesUI = 
   TCAST( ( new Cq::CursesUI() ) -> dontManage(), Cq::CursesUI );

Cq::Window::Window( WINDOW *aWin ) : Aq::Window( Cq::CursesUI::cursesUI )
{
  preC_( aWin != NULL );
  win = aWin;
  ICCALL( scrollok( getCWin(), false ) );
}

Cq::Window::~Window()
{
  ICCALL( delwin( getCWin() ) );
}

WINDOW *Cq::Window::getCWin() const
{
  return win;
}

Aq::EventSource *Cq::Window::getEventSource() const
{
  return new Cq::EventSource( this );
}

Cq::Window *Cq::Window::create( Aq::CoordX aX, Aq::CoordY aY,
								Aq::Size aWidth, Aq::Size aHeight )
{
  WINDOW *cwin;

  PCCALL( cwin = newwin( aHeight, aWidth, aY, aX ) );
  test_( cwin != NULL );
  return new Cq::Window( cwin );
}

void Cq::Window::update() const
{
  ICCALL( wrefresh( getCWin() ) );
}

Cq::Window *Cq::Window::getRootWindow()
{
  if( rootWindow == NULL )
	{
	  Cq::initClass();
	  rootWindow = new Cq::Window( stdscr );
	  rootWindow -> dontManage();
	}
  return rootWindow;
}

Cq::Window *Cq::Window::rootWindow = NULL;

void Cq::initClass()
{
  if( cursesLock == NULL )
	{
	  cursesLock = THR_SYSTEM -> recMutex();
	  TCAST( cursesLock, Object ) -> dontManage();
	}
  /* init sequence as per ncurses(3X) man page */
  PCCALL( initscr() ); 
  ICCALL( cbreak() ); 
  ICCALL( noecho() );
  ICCALL( nonl() );
  ICCALL( intrflush( stdscr, false ) );
  //  ICCALL( keypad( stdscr, true ) );
  if( Cq::CursesUI::hasColors() )
	{
	  ICCALL( start_color() );
	}
  else
	{
	  DLOG( "Curses: terminal without colour support." );
	}
}

void Cq::restore()
{
  ICCALL( endwin() );
}

Cq::GC::GC( int anAttr ) : Aq::GraphicContext( Cq::CursesUI::cursesUI )
{
  attr = anAttr;
}

int Cq::GC::getAttr() const
{
  return attr;
}

Cq::Painter::Painter( GC *aContext, Window *aDrawable ) : 
  Aq::Painter( aContext, aDrawable )
{}

Cq::Painter::~Painter()
{}

void Cq::Painter::init()
{
  ICCALL( ( int ) wattrset( getCWin() -> getCWin(), getCContext() -> getAttr() ) );
}

void Cq::Painter::done()
{
  ICCALL( ( int ) wattrset( getCWin() -> getCWin(), A_NORMAL ) );
  getCWin() -> update();
}

Cq::GC *Cq::Painter::getCContext() const
{
  return TCAST( getContext(), Cq::GC );
}

Cq::Window *Cq::Painter::getCWin() const
{
  return TCAST( getDrawable(), Cq::Window );
}

void Cq::Painter::drawChar( Aq::CoordX aStartX, Aq::CoordY aStartY, 
							chtype aChar ) const
{
  mvwaddch( getCWin() -> getCWin(), aStartY, aStartX, aChar ) ;
}

void Cq::Painter::drawLine( Aq::CoordX , Aq::CoordY , 
							Aq::CoordX , Aq::CoordY  ) const
{
}

void Cq::Painter::drawPoint( Aq::CoordX , Aq::CoordY  ) const
{
}

void Cq::Painter::drawCString( Aq::CoordX aX, Aq::CoordY aY, 
							   char *aString ) const
{
  mvwaddstr( getCWin() -> getCWin(), aY, aX, aString );
}

void Cq::Painter::fillRectangle( Aq::CoordX , Aq::CoordY ,
								 Aq::Size , Aq::Size  ) const
{
}

void Cq::Painter::clearRectangle( Aq::CoordX aX, Aq::CoordY aY,
								  Aq::Size aWidth, Aq::Size aHeight ) const
{
  for( Aq::Size x = 0 ; x < aWidth ; ++x )
	{
	  for( Aq::Size y = 0 ; y < aHeight ; ++y )
		{
		  drawChar( aX + x, aY + y, ' ' );
		}
	}
}

void Cq::Painter::copyFrom( Aq::CoordX aSourceX, Aq::CoordY aSourceY, 
							   Aq::Size aWidth, Aq::Size aHeight,
							   Aq::Drawable *aDrawable,
							   Aq::CoordX aDestX, Aq::CoordY aDestY ) const
{
  preC_( aDrawable != NULL );
  preC_( aDrawable -> isCompatible( this ) );

  ICCALL( copywin( TCAST( aDrawable, Cq::Window ) -> getCWin(), 
				   getCWin() -> getCWin(), 
				   aSourceY, aSourceX,
				   aDestY, aDestX, aDestY + aHeight, aDestX + aWidth, false ) );
}

Cq::KeyEvent::KeyEvent( int aKey )
{
  key = aKey;
}

int Cq::KeyEvent::getKey() const
{
  return key;
}

String Cq::KeyEvent::getClassName() const
{
  return "Cq::KeyEvent";
}

Cq::EventSource::EventSource( const Cq::Window *aWindow ) :
  window( aWindow )
{
  preC_( aWindow != NULL );
  OREG( window );
}

Cq::EventSource::~EventSource()
{
  FDONE( window );
}

Aq::AqEvent *Cq::EventSource::getNextTypedElement()
{
  int keyCode;

  keyCode = wgetch( window -> getCWin() );
  ICCALL( keyCode );
  return new Cq::KeyEvent( keyCode );
}

String  Cq::getClassName() const
{
  return "Cq";
}

Mutex *Cq::cursesLock = NULL;


#if defined( TESTING )

END_QR_NAMESPACE
#include "observe/EchoObserver.hpp"
BEGIN_QR_NAMESPACE

boolean Cq::tester( int )
{
  Cq::Window *win;
  Cq::Painter *kandinsky;
  Aq::EventSource *sink;

  Cq::initClass();

  win = Cq::Window::create( 3, 3, 50, 15 );
  OGuard _win( win, win );

  kandinsky = new Cq::Painter( new Cq::GC( 0 ), win );
  OGuard _kandinsky( kandinsky, kandinsky );
  {
	Aq::PainterGuard molbert( kandinsky, kandinsky );

	kandinsky -> drawString( 3, 3, "Hello, world!" );
  }
  sink = win -> getEventSource();
  OGuard _sink( sink, sink );
  THR_FACTORY -> createFromRunner( sink );
  sink -> addPassive( new EchoObserver() );
  while( true )
	{
	  THR_SYSTEM -> sleep( 1, 0 );
	}
  return true;
}
#endif

END_QR_NAMESPACE

#if defined(_INLINE)
#include "../src/Debug.ipp"
#endif

/* USE_CQ */
#endif

/*
 * $Log: Cq.cpp,v $
 * Revision 1.2  2000/10/20 20:29:20  philogelos
 * Simplifications through using of NopThreads
 *
 * Revision 1.1.1.1  2000/07/19 16:52:31  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:44  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:37  god
 * Imported sources
*/
