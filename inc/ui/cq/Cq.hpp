// -*-C++-*- 

/*  inc/platform/Cq.hpp  */

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



#ifndef __CQ_HPP__
#define __CQ_HPP__

/* $Id: Cq.hpp,v 1.1.1.1 2000/07/19 17:14:40 philogelos Exp $ */

#include "defines.h"

//#define USE_CQ

#if defined( WANT_USE_CQ )
#define USE_CQ
#elif defined( UNWANT_USE_CQ )
#if defined( USE_CQ )
#undef USE_CQ
#endif
#endif

#if defined( USE_CQ )

#include "ui/aq/Aq.hpp"
#include "String.hpp"

#include <curses.h>
#if defined( move )
#undef move /* XXX conflicts with LinkManager::move */
#endif
#if defined( clear )
#undef clear /* XXX conflict */
#endif
#if defined( reg )
#undef reg
/* #define	reg	register !!! */
#endif



BEGIN_QR_NAMESPACE

/**
   (N)Curses-based UI. Implementation of Aq interface
   over curses library.

   @author Philogelos
   @created
*/
class Cq : public virtual Top
{
public: class CursesUI;
public: class Window;
public: class KeyEvent;
public: class EventSource;
public: class Painter;
public: class GC;

public: class CursesUI : public Aq::GUISystem,
		public virtual Object
{
public: CursesUI();
public: virtual ~CursesUI();

public: virtual Aq::Painter *createPainter( Aq::GraphicContext *aContext, 
											Aq::Drawable *aDrawable ) const;
public: static int getScreenWidth();
public: static int getScreenHeight();
public: static boolean hasColors();

public: static CursesUI *cursesUI;
};

public: class Window : public Aq::Window,
  public virtual Object
{
public: Window( WINDOW *aWin );
public: ~Window();

public: WINDOW *getCWin() const;

public: void update() const;
public: static Window *getRootWindow();

public: virtual Aq::EventSource *getEventSource() const;

public: static Window *create( Aq::CoordX aX, Aq::CoordY aY,
							   Aq::Size aWidth, Aq::Size aHeight );
protected: WINDOW *win;
protected: static Window *rootWindow;
};

public: class GC : public Aq::GraphicContext,
  public virtual Object
{
public: GC( int anAttr );

public: int getAttr() const;

protected: int attr;
};


public: class Painter : public Aq::Painter, public virtual Object
{
public: Painter( GC *aContext, Window *aDrawable );
public: virtual ~Painter();

public: virtual void init();
public: virtual void done();

public: virtual GC *getCContext() const;
public: virtual Window *getCWin() const;

public: virtual void drawChar( Aq::CoordX aStartX, Aq::CoordY aStartY, 
							   chtype aChar ) const;

public: virtual void drawLine( Aq::CoordX aStartX, Aq::CoordY aStartY, 
							   Aq::CoordX anEndX, Aq::CoordY anEndY ) const;
public: virtual void drawPoint( Aq::CoordX aX, Aq::CoordY aY ) const;
public: virtual void drawCString( Aq::CoordX aX, Aq::CoordY aY, 
								  char *aString ) const;
public: virtual void fillRectangle( Aq::CoordX aX, Aq::CoordY aY,
									Aq::Size aWidth, Aq::Size aHeight ) const;
public: virtual void clearRectangle( Aq::CoordX aX, Aq::CoordY aY,
									 Aq::Size aWidth, Aq::Size aHeight ) const;
public: virtual void copyFrom( Aq::CoordX aSourceX, Aq::CoordY aSourceY, 
							   Aq::Size aWidth, Aq::Size aHeight,
							   Aq::Drawable *aDrawable,
							   Aq::CoordX aDestX, Aq::CoordY aDestY ) const;
};

public: class KeyEvent : public Aq::KeyEvent,
		public virtual Object
{
public: KeyEvent( int aKey );

public: int getKey() const;

public: String getClassName() const;

protected: int key;
};

public: class EventSource : public Aq::EventSource
{
public: EventSource( const Window *aWindow );
public: virtual ~EventSource();

public: virtual Aq::AqEvent *getNextTypedElement();

protected: const Window *window;
};

public: static void initClass();
public: static void restore();

#if defined( USE_THREADS )
public: static Mutex *cursesLock;
#endif

public: String getClassName() const;

#if defined( TESTING )
public: static boolean tester( int );
#endif
};

END_QR_NAMESPACE

/*
 * $Log: Cq.hpp,v $
 * Revision 1.1.1.1  2000/07/19 17:14:40  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:37  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:42  god
 * Imported sources
*/

/* USE_CQ */
#endif

/* __CQ_HPP__ */
#endif
