// -*-C++-*- 

/*  inc/platform/Xq.hpp  */

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



#ifndef __XQ_HPP__
#define __XQ_HPP__

/* $Id: Xq.hpp,v 1.1.1.1 2000/07/19 17:16:06 philogelos Exp $ */

#define USE_XQ

#if defined( WANT_USE_XQ )
#define USE_XQ
#elif defined( UNWANT_USE_XQ )
#if defined( USE_XQ )
#undef USE_XQ
#endif
#endif

#if defined( USE_XQ )

#include "String.hpp"
#include "Object.hpp"
#include "Top.hpp"
#include "defines.h"
#include "platform/threads/Runnable.hpp"
#include "platform/threads/Thread.hpp"
#include "exceptions/Errno.hpp"
#include "iter/enumerations/TypedEnumeration.hpp"
#include "observe/ObservableAdapter.hpp"
#include "observe/PassiveObserver.hpp"
#include "Condition.hpp"
#include "ui/aq/Aq.hpp"

#include <X11/X.h>
#include <X11/Xlib.h>

#define XQ_USE_X11_MUTEX
/* #define XQ_USE_XINITTHREADS */

#define XQ_XCHECKEVENT_HACK
#define XQ_XCHECKEVENT_HACK_TIMEOUT 10000000

#define USE_XPM

#if defined( WANT_XQ_USE_X11_MUTEX )
#define XQ_USE_X11_MUTEX
#elif defined( UNWANT_XQ_USE_X11_MUTEX )
#if defined( XQ_USE_X11_MUTEX )
#undef XQ_USE_X11_MUTEX
#endif
#endif

#if defined( WANT_XQ_USE_XINITTHREADS )
#define XQ_USE_XINITTHREADS
#elif defined( UNWANT_XQ_USE_XINITTHREADS )
#if defined( XQ_USE_XINITTHREADS )
#undef XQ_USE_XINITTHREADS
#endif
#endif

#if defined( WANT_XQ_XCHECKEVENT_HACK )
#define XQ_XCHECKEVENT_HACK
#elif defined( UNWANT_XQ_XCHECKEVENT_HACK )
#if defined( XQ_XCHECKEVENT_HACK )
#undef XQ_XCHECKEVENT_HACK
#endif
#endif

#if defined( WANT_XQ_XCHECKEVENT_HACK_TIMEOUT )
#define XQ_XCHECKEVENT_HACK_TIMEOUT
#elif defined( UNWANT_XQ_XCHECKEVENT_HACK_TIMEOUT )
#if defined( XQ_XCHECKEVENT_HACK_TIMEOUT )
#undef XQ_XCHECKEVENT_HACK_TIMEOUT
#endif
#endif

#if defined( WANT_XQ_XCHECKEVENT_HACK_TIMEOUT )
#define XQ_XCHECKEVENT_HACK_TIMEOUT WANT_XQ_XCHECKEVENT_HACK_TIMEOUT
#endif

#if defined( WANT_USE_XPM )
#define USE_XPM
#elif defined( UNWANT_USE_XPM )
#if defined( USE_XPM )
#undef USE_XPM
#endif
#endif

class Mutex;



BEGIN_QR_NAMESPACE

/**
   X Window System UI. Implementation of Aq interface over 
   Xlib.

   @author Philogelos
   @created
*/
class Xq : public virtual Top
{

#define INSIDE_XQ_SCOPE

public:
  class XqObject;

  class XIDObject;
  class Display;
  class Window;
  class GC;
  class Font;
  class Pixmap;
  class Bitmap;
  class Color;
  class Point;
  class Rectangle;
  class Geometry;
  class Bitmask;
  class Drawable;
  class Cursor;
  class KeySym;
  class XException;
 
  class XqEvent;
  class XqEventSource;
  class WindowEventSource;
  class XqEventDispatcher;

  class KeyEvent;
  class ButtonEvent;
  class MouseMotionEvent;
  class FocusEvent;
  class WindowEvent;
  class DestroyEvent;
  class ResizeEvent;
  class SelectionEvent;

  class Applet;
  class AppletThread;

  typedef int Coord;

#include "XqObject.hpp"
#include "XIDObject.hpp"
#include "Drawable.hpp"
#include "XqEventSource.hpp"
#include "Display.hpp"
#include "Window.hpp"
#include "WindowEventSource.hpp"
#include "GC.hpp"
#include "Font.hpp"
#include "Pixmap.hpp"
#include "Color.hpp"
#include "Cursor.hpp"
#include "XException.hpp"
#include "XFatalException.hpp"
#include "XqEvent.hpp"
#include "Applet.hpp"
#include "AppletThread.hpp"
#include "X11WindowSystem.hpp"
#include "XPainter.hpp"

#if defined( TESTING )
public: static boolean tester( int );
#endif

#undef INSIDE_XQ_SCOPE

/* 
public: class Bitmap : public virtual Pixmap
{
};
*/

/*
public: class Point : public virtual XqObject
{
};

public: class Rectangle : public virtual XqObject
{
};

public: class Geometry : public virtual XqObject
{
};

public: class Bitmask : public virtual XqObject
{
};

public: class KeySym : public virtual XqObject
{
};
*/


};


END_QR_NAMESPACE

/* USE_XQ */
#endif

/*
 * $Log: Xq.hpp,v $
 * Revision 1.1.1.1  2000/07/19 17:16:06  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:38  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:42  god
 * Imported sources
*/

/* __XQ_HPP__ */
#endif

