// -*-C++-*- 

/*  inc/platform/threads/CondVar.hpp  */

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



#ifndef __CONDVAR_HPP__
#define __CONDVAR_HPP__

/* $Id: CondVar.hpp,v 1.1.1.1 2000/07/19 17:13:53 philogelos Exp $ */

#include "Top.hpp"
#include "Mutex.hpp"
#include "defines.h"



BEGIN_QR_NAMESPACE

/**
   Conditional variables. Each conditional
   variable has associated mutex.

   To avoid races this mutex should be locked during
   wait(), signal() and broadcast().

   @see Mutex
   @author Philogelos
   @created
*/
interface CondVar : public virtual Top
{
  /**
	 Returns mutex associated with this conditional
	 variable.
  */
 public: virtual Mutex *getMutex() const = 0;

 /**
	Waits while this object signalled. This
	atomically unlocks associated mutex and puts
	calling thread to sleep until call to signal()
	or broadcast()
 */
 public: virtual void wait() = 0;

 /**
	Signals this object. One thread waiting
	on this object wakes up.
 */
 public: virtual void signal() = 0;

 /**
	Broadcasts this object. All threads waiting
	on this object wake up.
 */
 public: virtual void broadcast() = 0;
};

END_QR_NAMESPACE

/*
 * $Log: CondVar.hpp,v $
 * Revision 1.1.1.1  2000/07/19 17:13:53  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:36  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:48  god
 * Imported sources
*/

/* __CONDVAR_HPP__ */
#endif
