// -*-C++-*- 

/*  inc/ui/wq/DC.hpp  */

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



#ifndef __DC_HPP__
#define __DC_HPP__

/* $Id: DC.hpp,v 1.1.1.1 2000/07/19 17:14:50 philogelos Exp $ */

#if defined( INSIDE_WQ_SCOPE )

/**

   @author Philogelos
   @created
*/
public: class DC : public Win32Object
		{
		public: DC( HANDLE aHandle );
		public: virtual ~DC();

		public: void drawString( Aq::CoordX aX, Aq::CoordY aY, String aString );
		public: void drawCString( Aq::CoordX aX, Aq::CoordY aY, char *aString );

		public: void fillRectangle( Aq::CoordX aX, Aq::CoordY aY, 
									Aq::Size aWidth, 
									Aq::Size aHeight, Brush *aBrush );

		public: void copyTo( Aq::CoordX aSourceX, Aq::CoordY aSourceY,
							 Aq::Size aWidth, Aq::Size aHeight,
							 DC *aDC, 
							 Aq::CoordX aDestX, Aq::CoordY aDestY,
							 DWORD anOp );

		public: void setFont( Font *aFont );
		public: void setBitmap( Bitmap *aBitmap );
		public: void setBrush( Brush *aBrush );
		public: void setPen( Pen *aPen );

		public: Font   *getFont() const;
		public: Bitmap *getBitmap() const;
		public: Brush  *getBrush() const;
		public: Pen    *getPen() const;

		public: void setTextForeground( COLORREF aColor );
		public: void setTextBackground( COLORREF aColor );

		public: COLORREF getTextForeground() const;
		public: COLORREF getTextBackground() const;

		public: void selectObject( Win32Object *anObject );
		public: HANDLE  getObject( UINT anObjType ) const;

		public: static DC *create( Window *aWindow );
		public: static DC *createInMemory( HANDLE aHandle );
		};

#endif

/*
 * $Log: DC.hpp,v $
 * Revision 1.1.1.1  2000/07/19 17:14:50  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:37  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:41  god
 * Imported sources
*/

/* __DC_HPP__ */
#endif
