// -*-C++-*- 

/*  inc/ui/xq/XPainter.hpp  */

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



#ifndef __XPAINTER_HPP__
#define __XPAINTER_HPP__

/* $Id: XPainter.hpp,v 1.1.1.1 2000/07/19 17:16:06 philogelos Exp $ */

#if defined( INSIDE_XQ_SCOPE )

/**

   @author Philogelos
   @created
*/
public: class XPainter : public Aq::Painter,
  public virtual Object
{
public: XPainter( GC *aGC, Drawable *aDrawable );
public: virtual ~XPainter();

public: virtual void init();
public: virtual void done();

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

public: virtual void setDrawable( Aq::Drawable *aDrawable );
public: Drawable *getXDrawable() const;
public: GC *getGC() const;
public: GC *getClearGC() const;

public: static XPainter *create( GC *aGC, Drawable *aDrawable, 
								 Xq::Color *aFore );

protected: GC *clearGC;
protected: Drawable *arena;
};

#endif

/*
 * $Log: XPainter.hpp,v $
 * Revision 1.1.1.1  2000/07/19 17:16:06  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:38  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:42  god
 * Imported sources
*/

/* __XPAINTER_HPP__ */
#endif
