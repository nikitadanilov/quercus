// -*-C++-*- 

/*  inc/platform/threads/Semaphore.hpp  */

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



#ifndef __SEMAPHORE_HPP__
#define __SEMAPHORE_HPP__

/* $Id: Semaphore.hpp,v 1.1.1.1 2000/07/19 17:14:10 philogelos Exp $ */

#include "Top.hpp"
#include "defines.h"



BEGIN_QR_NAMESPACE

/**
   Dijkstra semaphores. Semaphore is unowned (unlike mutex)
   counter that can be atomically incremented and 
   decremented. If it is decremented to be negative,
   calling thread is suspended until count became positive 
   again (through incrementing by other threads).

   @author Philogelos
   @created
*/

interface Semaphore : public virtual Top
{
 public: virtual void inc() = 0;
 public: virtual void dec() = 0;
 public: virtual boolean tryDec() = 0;
};


END_QR_NAMESPACE

/*
 * $Log: Semaphore.hpp,v $
 * Revision 1.1.1.1  2000/07/19 17:14:10  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:36  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:48  god
 * Imported sources
*/

/* __SEMAPHORE_HPP__ */
#endif
