// -*-C++-*- 

/*  inc/ui/xq/Drawable.hpp  */

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



#ifndef __DRAWABLE_HPP__
#define __DRAWABLE_HPP__

/* $Id: Drawable.hpp,v 1.1.1.1 2000/07/19 17:15:23 philogelos Exp $ */

#if defined( INSIDE_XQ_SCOPE )

/**

   @author Philogelos
   @created
*/
public: class Drawable : public virtual XIDObject,
		public Aq::Drawable
{
public: Drawable( Display *aDisplay, XID anId );
public: void copyTo( Xq::Drawable *aDest, Xq::GC *aGC, 
					 Xq::Coord aSrcX, Xq::Coord aSrcY, 
					 int aWidth, int aHeight,
					 Xq::Coord aDstX, Xq::Coord aDstY );
public: void drawPoint( Xq::GC *aGC, Xq::Coord aX, Xq::Coord aY );
public: void drawLine( Xq::GC *aGC, 
					   Xq::Coord aStartX, Xq::Coord aStartY,
					   Xq::Coord anEndX, Xq::Coord anEndY );

public: void fillRectangle( Xq::GC *aGC, Xq::Coord aX, Xq::Coord aY, 
							int aWidth, int aHeight );
public: void drawString( Xq::GC *aGC, Xq::Coord aX, Xq::Coord aY, 
						 String aString );
public: void drawCString( Xq::GC *aGC, Xq::Coord aX, Xq::Coord aY, 
						  char *aString );
};

#endif

/*
 * $Log: Drawable.hpp,v $
 * Revision 1.1.1.1  2000/07/19 17:15:23  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:37  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:42  god
 * Imported sources
*/

/* __DRAWABLE_HPP__ */
#endif
