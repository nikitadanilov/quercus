// -*-C++-*- 

/*  inc/ui/wq/Window.hpp  */

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



#ifndef __WQ_WINDOW_HPP__
#define __WQ_WINDOW_HPP__

/* $Id: Window.hpp,v 1.1.1.1 2000/07/19 17:14:59 philogelos Exp $ */

#if defined( INSIDE_WQ_SCOPE )

/**

   @author Philogelos
   @created
*/
public: class Window : public virtual Win32Object,
		public Aq::Window,
		public Drawable
		{
			friend WindowEventSource;

		public: Window( HANDLE aHandle );
		public: virtual ~Window();

		public: void show() const;
		public: virtual Aq::EventSource *getEventSource() const;
		public: WindowEventSource *getWEventSource() const;

		public: void move( Aq::CoordX aX, Aq::CoordY aY );
		public: void setSize( Aq::Size aWidth, 
						Aq::Size aHeight );
		public: void setTitle( String aTitle );

		public: void makeForeground();

		public: void setCursor( Cursor *aCursor );
		public: void showCursor( boolean toShow );

		public: virtual DC *getDC() const;
		public: virtual void ungetDC( DC *aDC ) const;

		public: virtual boolean isCursorWithin() const;

		public: static String getDefaultClassName();
		public: static Window *create();
		public: static UINT  terminateMessage;
		public: static UINT  wakeUpMessage;

		protected: Thread *eventLoop;
		protected: WindowEventSource *events;
		protected: List *triggers;
		protected: Cursor *cursor;

		protected: static boolean defaultClassRegistered;
		protected: static LRESULT CALLBACK defWinProc
					   ( HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
		protected: static void *winLoop( void * );
		};

#endif

/*
 * $Log: Window.hpp,v $
 * Revision 1.1.1.1  2000/07/19 17:14:59  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:37  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:41  god
 * Imported sources
*/

/* __WQ_WINDOW_HPP__ */
#endif
