// -*-C++-*- 

/*  inc/platform/threads/RecMutex.hpp  */

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



#ifndef __RECMUTEX_HPP__
#define __RECMUTEX_HPP__

/* $Id: RecMutex.hpp,v 1.2 2001/03/06 17:38:34 philogelos Exp $ */

#include "CondVar.hpp"
#include "Object.hpp"
#include "Mutex.hpp"
#include "ThreadsSystem.hpp"
#include "ThreadFactory.hpp"
#include "defines.h"

#define SOLARIS_MGUARD_BUG


#if defined( WANT_SOLARIS_MGUARD_BUG )
#define SOLARIS_MGUARD_BUG
#elif defined( UNWANT_SOLARIS_MGUARD_BUG )
#if defined( SOLARIS_MGUARD_BUG )
#undef SOLARIS_MGUARD_BUG
#endif
#endif



BEGIN_QR_NAMESPACE

/**
   Default implementation of the recursive mutex.
   Each instance has internal mutex to serialise
   operations and conditional variable
   to signal waiting threads.

   @author Philogelos
   @created
*/
class RecMutex : public virtual Mutex,
				 public virtual Object
{

  /**
	 Creates instance using conditional variable
	 created by default thread system.

	 @see ThreadsSystem::condVar()
   */
public: RecMutex();

  /**
	 Creates instance using given conditional
	 variable.
  */
public: RecMutex( CondVar *aCondVar );

public: virtual ~RecMutex();

public: virtual void enter( const Top * = null );
public: virtual void leave( const Top * = null );
public: virtual boolean tryEnter( const Top * = null );

public:  virtual String  toString() const;
public:  virtual String  getClassName() const;

protected: void init( CondVar *aCondVar );

protected: CondVar *condVar;

protected: Index count;
protected: Thread *thread;
protected: Mutex *guardian;
#if defined( LOCKS_INFO )
 public: virtual const void *holds() const;
 public: virtual const void *trying() const;
#endif
};

END_QR_NAMESPACE

/*
 * $Log: RecMutex.hpp,v $
 * Revision 1.2  2001/03/06 17:38:34  philogelos
 * Support for LOCKS_INFO
 *
 * Revision 1.1.1.1  2000/07/19 17:14:06  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:36  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:48  god
 * Imported sources
*/

/* __RECMUTEX_HPP__ */
#endif
