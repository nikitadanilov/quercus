// -*-C++-*- 

/*  inc/ui/wq/Bitmap.hpp  */

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



#ifndef __BITMAP_HPP__
#define __BITMAP_HPP__

/* $Id: Bitmap.hpp,v 1.1.1.1 2000/07/19 17:14:40 philogelos Exp $ */

#if defined( INSIDE_WQ_SCOPE )

/**

   @author Philogelos
   @created
*/
public: class Bitmap : public Win32Object,
		public Drawable
		{
		public: Bitmap( HANDLE aHandle );
		public: virtual ~Bitmap();

		public: Aq::Size getWidth() const;
		public: Aq::Size getHeight() const;

		public: void setSize( Aq::Size aWidth, Aq::Size aHeight );

		public: virtual void setDC( DC *aDC );
		public: virtual DC *getDC() const;
		public: virtual void ungetDC( DC *aDC ) const;

		public: static Bitmap *create( DC *aDC, Aq::Size aWidth,
									   Aq::Size aHeight );
		public: static Bitmap *load( int aResource );

		protected: DC *dc;
		};

#endif

/*
 * $Log: Bitmap.hpp,v $
 * Revision 1.1.1.1  2000/07/19 17:14:40  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:37  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:41  god
 * Imported sources
*/

/* __BITMAP_HPP__ */
#endif
