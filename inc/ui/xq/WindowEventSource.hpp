// -*-C++-*- 

/*  inc/ui/xq/WindowEventSource.hpp  */

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



#ifndef __XQ_WINDOWEVENTSOURCE_HPP__
#define __XQ_WINDOWEVENTSOURCE_HPP__

/* $Id: WindowEventSource.hpp,v 1.3 2000/10/12 21:30:46 philogelos Exp $ */

#if defined( INSIDE_XQ_SCOPE )

/**

   @author Philogelos
   @created
*/
public: class WindowEventSource : public XqEventSource
{
public: WindowEventSource( const Xq::Window *aWindow, boolean allEvents);
public: virtual ~WindowEventSource();

public: Xq::Window *getWindow() const;

public: virtual Aq::AqEvent *getNextTypedElement() THROWS( Errno * );

public: virtual String getClassName() const;

protected: const Xq::Window *window;
protected: boolean all;
};

/*
 * $Log: WindowEventSource.hpp,v $
 * Revision 1.3  2000/10/12 21:30:46  philogelos
 * Support of new parameter in Xq::Window::getXEventSource()
 *
 * Revision 1.2  2000/08/30 12:20:35  philogelos
 * THROWS clauses updates to correspond to the real throws.
 *
 * Revision 1.1.1.1  2000/07/19 17:15:23  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:38  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:42  god
 * Imported sources
*/

#endif

/* __XQ_WINDOWEVENTSOURCE_HPP__ */
#endif
