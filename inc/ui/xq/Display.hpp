// -*-C++-*- 

/*  inc/ui/xq/Display.hpp  */

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



#ifndef __DISPLAY_HPP__
#define __DISPLAY_HPP__

/* $Id: Display.hpp,v 1.1.1.1 2000/07/19 17:15:23 philogelos Exp $ */

#if defined( INSIDE_XQ_SCOPE )

/**

   @author Philogelos
   @created
*/
public: class Display : public Aq::EventSource
{
protected: Display( struct _XDisplay *aDisplay );
public: virtual ~Display();

public: void close();
public: int connectionNumber() const;
public: int screen() const;
public: Xq::Window *getRootWindow() const;
public: XID defaultColormap() const;
public: int blackPixel() const;
public: int whitePixel() const;
public: int defaultDepth() const;
public: Visual *defaultVisual( int aScreen ) const;

public: Coord getWidth() const;
public: Coord getHeight() const;

public: static Display *open();
public: static Display *open( const char *aName );

public: void setData( struct _XDisplay *aDisplay );
public: struct _XDisplay *getData() const;

public: virtual Aq::AqEvent *getNextTypedElement();

public: virtual String getClassName() const;

protected: struct _XDisplay *x11Data;
protected: Xq::Window *rootWindow;

#if defined( USE_THREADS ) && defined( XQ_USE_X11_MUTEX )
public: Mutex *getX11Serialiser() const;
protected: Mutex *x11Serializer;
#endif
};

#endif

/*
 * $Log: Display.hpp,v $
 * Revision 1.1.1.1  2000/07/19 17:15:23  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:37  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:42  god
 * Imported sources
*/

/* __DISPLAY_HPP__ */
#endif
