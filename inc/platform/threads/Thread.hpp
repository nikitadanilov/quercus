// -*-C++-*- 

/*  inc/platform/threads/Thread.hpp  */

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



#ifndef __THREAD_HPP__
#define __THREAD_HPP__

/* $Id: Thread.hpp,v 1.1.1.1 2000/07/19 17:14:10 philogelos Exp $ */

#include "Top.hpp"
#include "defines.h"

/* #define DEBUG_THREADS */

#if defined( WANT_DEBUG_THREADS )
#define DEBUG_THREADS
#elif defined( UNWANT_DEBUG_THREADS )
#if defined( DEBUG_THREADS )
#undef DEBUG_THREADS
#endif
#endif


BEGIN_QR_NAMESPACE

/**
   Interface to thread system.
   Mimicing POSIX threads.

   @author Philogelos
   @created
*/
interface Thread : public virtual Top
{
  /**
	 Returns some system-dependent thread identifier.
  */
 public: virtual Index getId() const = 0;

 /**
	True if this thread wasn't created by ThreadFactory.
	E.g., if it is main thread of the process.
 */
 public: virtual boolean isSystemThread() const = 0;

 /**
	Wait until this thread finishes execution.
 */
 public: virtual void join() = 0;

 /**
	Sets thread name.
 */
 public: virtual void setName( String aName ) = 0;

 /**
	Returns thread name.
 */
 public: virtual String getName() const = 0;
};

END_QR_NAMESPACE

/*
 * $Log: Thread.hpp,v $
 * Revision 1.1.1.1  2000/07/19 17:14:10  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:36  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:48  god
 * Imported sources
*/

/* __THREAD_HPP__ */
#endif
