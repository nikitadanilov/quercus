// -*-C++-*- 

/*  inc/ui/xq/XqEvent.hpp  */

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



#ifndef __XQEVENT_HPP__
#define __XQEVENT_HPP__

/* $Id: XqEvent.hpp,v 1.1.1.1 2000/07/19 17:16:13 philogelos Exp $ */

#if defined( INSIDE_XQ_SCOPE )


/**

   @author Philogelos
   @created
*/
public: class XqEvent : public virtual Aq::AqEvent,
		public virtual XqObject
{
public: XqEvent( Xq::Display *aDisplay, XEvent *aData );
public: virtual ~XqEvent();

public: XEvent *getData() const;

public: static XqEvent *create( Xq::Display *aDisplay, 
								XEvent *aData,
								Xq::Window *aWindow = ( Xq::Window * ) NULL );

public: Xq::Window *getWindow() const;
public: void setWindow( Xq::Window *aWindow );

public: virtual String toString() const;
public: virtual String getClassName() const;

protected: XEvent event;
protected: Xq::Window *window;
};

public: class KeyEvent : public virtual Xq::XqEvent,
		public virtual Aq::KeyEvent
{
public: KeyEvent( Xq::Display *aDisplay, XEvent *aData );
public: ~KeyEvent();

public: unsigned int getKeycode() const;
public: ::KeySym getKeySym() const;

public: static ::KeySym keycodeToKeysym( Xq::Display *aDisplay,
										 unsigned int aKeycode );
public: static String keysymToString( Xq::Display *aDisplay,
									  ::KeySym aKeySym );

public: virtual String getClassName() const;
};

public: class ButtonEvent : public virtual Xq::XqEvent,
		public virtual Aq::KeyEvent

{
public: ButtonEvent( Xq::Display *aDisplay, XEvent *aData );
public: ~ButtonEvent();

public: virtual String getClassName() const;
};

public: class MouseMotionEvent : public virtual Xq::XqEvent,
		public virtual Aq::KeyEvent

{
public: MouseMotionEvent( Xq::Display *aDisplay, XEvent *aData );
public: ~MouseMotionEvent();

public: virtual String getClassName() const;
};

public: class FocusEvent : public virtual Xq::XqEvent,
		public virtual Aq::KeyEvent

{
public: FocusEvent( Xq::Display *aDisplay, XEvent *aData );
public: ~FocusEvent();

public: virtual String getClassName() const;
};

public: class WindowEvent : public virtual Xq::XqEvent,
		public virtual Aq::KeyEvent

{
public: WindowEvent( Xq::Display *aDisplay, XEvent *aData );
public: ~WindowEvent();

public: virtual String getClassName() const;
};

public: class DestroyEvent : public virtual Xq::XqEvent,
		public virtual Aq::KeyEvent

{
public: DestroyEvent( Xq::Display *aDisplay, XEvent *aData );
public: ~DestroyEvent();

public: virtual String getClassName() const;
};

public: class ResizeEvent : public virtual Xq::XqEvent,
		public virtual Aq::KeyEvent

{
public: ResizeEvent( Xq::Display *aDisplay, XEvent *aData );
public: ~ResizeEvent();

public: virtual String getClassName() const;
};

public: class SelectionEvent : public virtual Xq::XqEvent,
		public virtual Aq::KeyEvent

{
public: SelectionEvent( Xq::Display *aDisplay, XEvent *aData );
public: ~SelectionEvent();

public: virtual String getClassName() const;
};

#endif

/*
 * $Log: XqEvent.hpp,v $
 * Revision 1.1.1.1  2000/07/19 17:16:13  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:38  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:42  god
 * Imported sources
*/

/* __XQEVENT_HPP__ */
#endif
