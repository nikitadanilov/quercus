// -*-C++-*- 

/*  inc/platform/threads/ThreadDeath.hpp  */

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



#ifndef __THREADDEATH_HPP__
#define __THREADDEATH_HPP__

/* $Id: ThreadDeath.hpp,v 1.1.1.1 2000/07/19 17:14:10 philogelos Exp $ */

#include "exceptions/Exception.hpp"
#include "exceptions/RuntimeError.hpp"
#include "defines.h"

class Thread;



BEGIN_QR_NAMESPACE

/**
   Objects of this class are thrown when
   thread is cancelled.

   @see ThreadsSystem::cancel()

   @author Philogelos
   @created
*/
class ThreadDeath : public RuntimeError
{
public: ThreadDeath( Thread *aThread, 
					 String aMessage, 
					 const Top *const aSource );
public: virtual ~ThreadDeath();

public:  virtual String  getClassName() const;
public:  virtual String  getDescription() const;

public: Thread *getThread() const;

protected: Thread *thread;
};


END_QR_NAMESPACE

/*
 * $Log: ThreadDeath.hpp,v $
 * Revision 1.1.1.1  2000/07/19 17:14:10  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:36  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:48  god
 * Imported sources
*/

/* __THREADDEATH_HPP__ */
#endif
