// -*-C++-*- 

/*  inc/ui/xq/Pixmap.hpp  */

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



#ifndef __PIXMAP_HPP__
#define __PIXMAP_HPP__

/* $Id: Pixmap.hpp,v 1.2 2000/08/30 12:20:35 philogelos Exp $ */

#if defined( INSIDE_XQ_SCOPE )

/**

   @author Philogelos
   @created
*/
public: class Pixmap : public virtual Drawable
{
public: Pixmap( Display *aDisplay, XID anId, 
				int aWidth, int aHeight, 
				int aXHot, int aYHot );
public: virtual ~Pixmap();

public: Xq::Coord getWidth() const;
public: Xq::Coord getHeight() const;
public: int getXHot() const;
public: int getYHot() const;

public: void writeToXBMFile( String aFileName );

public: static Pixmap *create( Xq::Drawable *aDrawable, 
							   int aWidth, 
							   int aHeight, 
							   int aDepth );
public: static Pixmap *create( Xq::Drawable *aDrawable, 
							   String aFileName );
#if defined( USE_XPM )
public: static Pixmap *createFromXPM( Xq::Drawable *aDrawable, 
									  String aFileName,
									  Xq::Pixmap **aMask );
public: void writeToXPMFile( String aFileName );
public: static void handleXPMError( int aCode, String aMessage ) 
  THROWS( XException * );
#endif

public: static Pixmap *create( Xq::Drawable *aDrawable, 
							   char *aData,
							   int aWidth, int aHeight );

protected: Xq::Coord width;
protected: Xq::Coord height;
protected: int xHot;
protected: int yHot;
};

#endif

/*
 * $Log: Pixmap.hpp,v $
 * Revision 1.2  2000/08/30 12:20:35  philogelos
 * THROWS clauses updates to correspond to the real throws.
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

/* __PIXMAP_HPP__ */
#endif
