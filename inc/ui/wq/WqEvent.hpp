// -*-C++-*- 

/*  inc/ui/wq/WqEvent.hpp  */

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



#ifndef __WQEVENT_HPP__
#define __WQEVENT_HPP__

/* $Id: WqEvent.hpp,v 1.1.1.1 2000/07/19 17:15:22 philogelos Exp $ */

#if defined( INSIDE_WQ_SCOPE )

/**

   @author Philogelos
   @created
*/
public: class WqEvent : public Aq::AqEvent,
		  public virtual Object
		{
		public: WqEvent( MSG *anEvent );

		public: static WqEvent *create( MSG *anEvent );
		public: static String getEventName( unsigned anId );

		public: virtual String toString() const;
		public: virtual String getClassName() const;

		public: MSG event;

		public: typedef enum 
		{ 
		  key = ( 1<< 0 ), 
		  button = ( 1<< 1 ), 
		  mouse = ( 1<< 2 ), 
		  focus = ( 1<< 3 ), 
		  window = ( 1<< 4 ), 
		  destroy = ( 1<< 5 ), 
		  resize = ( 1<< 6 ),
		  selection = ( 1<< 7 ), 
		  other = ( 1<< 8 ) 
		} EventType;

		public: typedef struct
		{
		  Index type;
		  char *name;
		} MessageType;

		public: static void initTypes();
		public: static MessageType *types;
		};


public: class KeyEvent : public virtual WqEvent,
		public virtual Aq::KeyEvent
{
public: KeyEvent( MSG *anEvent );
public: virtual String getClassName() const;
};

public: class ButtonEvent : public virtual WqEvent,
		public virtual Aq::KeyEvent

{
public: ButtonEvent( MSG *anEvent );
public: virtual String getClassName() const;
};

public: class MouseMotionEvent : public virtual WqEvent,
		public virtual Aq::KeyEvent

{
public: MouseMotionEvent( MSG *anEvent );
public: virtual String getClassName() const;
};

public: class FocusEvent : public virtual WqEvent,
		public virtual Aq::KeyEvent

{
public: FocusEvent( MSG *anEvent );
public: virtual String getClassName() const;
};

public: class WindowEvent : public virtual WqEvent,
		public virtual Aq::KeyEvent

{
public: WindowEvent( MSG *anEvent );
public: virtual String getClassName() const;
};

public: class DestroyEvent : public virtual WqEvent,
		public virtual Aq::KeyEvent

{
public: DestroyEvent( MSG *anEvent );
public: virtual String getClassName() const;
};

public: class ResizeEvent : public virtual WqEvent,
		public virtual Aq::KeyEvent

{
public: ResizeEvent( MSG *anEvent );
public: virtual String getClassName() const;
};

public: class SelectionEvent : public virtual WqEvent,
		public virtual Aq::KeyEvent

{
public: SelectionEvent( MSG *anEvent );
public: virtual String getClassName() const;
};


#endif

/*
 * $Log: WqEvent.hpp,v $
 * Revision 1.1.1.1  2000/07/19 17:15:22  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:37  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:41  god
 * Imported sources
*/

/* __WQEVENT_HPP__ */
#endif
