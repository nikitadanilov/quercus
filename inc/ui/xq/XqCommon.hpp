// -*-C++-*- 

/*  inc/ui/xq/XqCommon.hpp  */

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



#ifndef __XQCOMMON_HPP__
#define __XQCOMMON_HPP__

/* $Id: XqCommon.hpp,v 1.2 2000/10/20 20:29:19 philogelos Exp $ */

#include "Xq.hpp"

#if defined( USE_XQ )

#include "exceptions/OSError.hpp"
#include "String.hpp"
#include "Debug.hpp"
#include "OGuard.hpp"
#include "LinkManager.hpp"

#include "platform/threads/ThreadsSystem.hpp"
#include "platform/threads/ThreadFactory.hpp"
#include "platform/threads/Mutex.hpp"
#include "platform/threads/RecMutex.hpp"
#include "platform/Platform.hpp"

#include "Backtrace.hpp"

#include <X11/Xproto.h>
#include <X11/cursorfont.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <sched.h>

#if defined( USE_XPM )
#include <X11/xpm.h>
#endif

#if !defined( __linux__ )
extern "C" void *memset( void *s, int c, size_t n );
#endif

#define __USE_BSD
#define __EXTENSIONS__

/* XXX why on the earth M_PI in protected by some conditionals in math.h? */
#if defined(__SUNPRO_CC) && (__SUNPRO_CC >= 0x510)
/* for some obscure reason default math.h
   defines struct exception that conflicts with std::exception
*/
#define	M_PI		3.14159265358979323846
extern "C" double sin( double );
extern "C" double cos( double );
#else
#include <math.h>
#endif

#include <sys/time.h>
#include <sys/types.h>

#if !defined( XQ_USE_X11_MUTEX ) && !defined( XQ_USE_XINITTHREADS )
#warning "One ought to define XQ_USE_X11_MUTEX or XQ_USE_XINITTHREADS"
#endif

#if defined( XQ_USE_X11_MUTEX )
#include "platform/threads/MGuard.hpp"
 
#define LOCK_X11_DISPLAY( display )  \
   MGuard _x11Serial( display -> getX11Serialiser(), \
      ( Xq::Display * ) display )

#define LOCK_X11 LOCK_X11_DISPLAY( getDisplay() ) 

#else

#define LOCK_X11 do {} while( false )
#define LOCK_X11_DISPLAY( display ) do {} while( false )

/* XQ_USE_X11_MUTEX */
#endif

/* USE_XQ */
#endif

/* __XQCOMMON_HPP__ */
#endif
