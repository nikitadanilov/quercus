// -*-C++-*- 

/*  inc/ui/xq/Window.hpp  */

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



#ifndef __WINDOW_HPP__
#define __WINDOW_HPP__

/* $Id: Window.hpp,v 1.2 2000/10/12 21:29:41 philogelos Exp $ */

#if defined( INSIDE_XQ_SCOPE )

/**

   @author Philogelos
   @created
*/
public: class Window : public Drawable,
		public Aq::Window
		
{
public: Window( Display *aDisplay, XID anId );
public: virtual ~Window();

public: void map();
public: void unmap();
public: void clear();
public: void setCursor( Xq::Cursor *aCursor );
public: void unsetCursor();

public: void setSize( int aWidth, int aHeight );
public: void setSizeHints( int aMinWidth, int aMinHeight,
						   int aMaxWidth, int aMaxHeight,
						   int aBaseWidth, int aBaseHeight,
						   int aWidthInc, int aHeightInc );

public: void setName( String aName );
public: void setClass( String aName, String aClass );

public: void selectInput( long aMask );

public: Xq::WindowEventSource *getXEventSource( boolean allEvents = false ) const;
public: Aq::EventSource *getEventSource() const;

public: static Xq::Window *createSimple( Xq::Display *aDisplay,
										 Xq::Window *aParent,
										 int aX, int aY, 
										 int aWidth, int aHeight, 
										 int aBorderWidth,
										 int aForePixel, int aBackPixel );
public: virtual String getClassName() const;
};


#endif

/*
 * $Log: Window.hpp,v $
 * Revision 1.2  2000/10/12 21:29:41  philogelos
 * Option to get all events on display added to getXEventSource()
 *
 * Revision 1.1.1.1  2000/07/19 17:15:23  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:37  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:42  god
 * Imported sources
*/

/* __WINDOW_HPP__ */
#endif
