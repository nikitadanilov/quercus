// -*-C++-*- 

/*  inc/platform/Wq.hpp  */

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



#ifndef __WQ_HPP__
#define __WQ_HPP__

/* $Id: Wq.hpp,v 1.1.1.1 2000/07/19 17:15:04 philogelos Exp $ */

/* #define USE_WQ */

#if defined( WANT_USE_WQ )
#define USE_WQ
#elif defined( UNWANT_USE_WQ )
#if defined( USE_WQ )
#undef USE_WQ
#endif
#endif

#if defined( USE_WQ )

#include "Top.hpp"
#include "defines.h"

#include "platform/Win32Platform.hpp"
#if !defined( USE_WIN32 )
#error "USE_WQ implies USE_WIN32"
#endif

#include "platform/threads/Win32Thread.hpp"
#if !defined( USE_WIN32THREADS )
#error "USE_WQ implies USE_WIN32THREADS"
#endif

#include "String.hpp"
#include "platform/threads/Runnable.hpp"
#include "observe/ObservableAdapter.hpp"
#include "Condition.hpp"
#include "iter/enumerations/TypedEnumeration.hpp"
#include "iter/iterators/Iterator.hpp"
#include "ui/aq/Aq.hpp"
#include "Guard.hpp"



BEGIN_QR_NAMESPACE

/**
   MSWindows UI. Implementation of Aq interface over
   calls to Win32 API.

   @author Philogelos
   @created
*/
class Wq : public virtual Top
{

#define INSIDE_WQ_SCOPE

public: class Window;
public: class WqEvent;
public: class WqEventSource;
public: class WindowEventSource;
public: class Drawable;
public: class GC;
public: class DC;
public: class WPainter;

public: class Bitmap;
public: class Brush;
public: class Pen;
public: class Font;
public: class Cursor;

public: class KeyEvent;
public: class ButtonEvent;
public: class MouseMotionEvent;
public: class FocusEvent;
public: class WindowEvent;
public: class DestroyEvent;
public: class ResizeEvent;
public: class SelectionEvent;

#include "WqEventSource.hpp"
#include "Drawable.hpp"
#include "MSWindowSystem.hpp"
#include "Window.hpp"
#include "WindowEventSource.hpp"
#include "CloseWindowException.hpp"
#include "GC.hpp"
#include "Wpainter.hpp"
#include "WqEvent.hpp"
#include "DC.hpp"
#include "Bitmap.hpp"
#include "Brush.hpp"
#include "FontIterator.hpp"
#include "Font.hpp"
#include "Cursor.hpp"
#include "Pen.hpp"

public: static void initClass();

#if defined( TESTING )
public: static boolean tester( int );
#endif

#undef INSIDE_WQ_SCOPE

};

END_QR_NAMESPACE

/* USE_WQ */
#endif

/*
 * $Log: Wq.hpp,v $
 * Revision 1.1.1.1  2000/07/19 17:15:04  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:37  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:41  god
 * Imported sources
*/

/* __WQ_HPP__ */
#endif
