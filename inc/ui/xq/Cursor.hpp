// -*-C++-*- 

/*  inc/ui/xq/Cursor.hpp  */

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


#ifndef __XQ_CURSOR_HPP__
#define __XQ_CURSOR_HPP__

/* $Id: Cursor.hpp,v 1.1.1.1 2000/07/19 17:15:23 philogelos Exp $ */

#if defined( INSIDE_XQ_SCOPE )

/**

   @author Philogelos
   @created
*/
public: class Cursor : public virtual XIDObject
{
public: Cursor( Display *aDisplay, XID anId );
public: virtual ~Cursor();

public: void recolor( Xq::Color *fg, Xq::Color *bg );

public: static Xq::Cursor *createStd( Xq::Display *aDisplay,
									  int shape );
public: static Xq::Cursor *create( Xq::Display *aDisplay,
								   Xq::Pixmap *source, Xq::Pixmap *mask,
								   Xq::Color *foreground, 
								   Xq::Color *background,
								   Xq::Coord xHot, Xq::Coord yHot );
};

#endif

/*
 * $Log: Cursor.hpp,v $
 * Revision 1.1.1.1  2000/07/19 17:15:23  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:37  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:42  god
 * Imported sources
*/

/* __XQ_CURSOR_HPP__ */
#endif
