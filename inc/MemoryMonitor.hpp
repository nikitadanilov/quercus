//-*-C++-*-

/*  inc/MemoryMonitor.hpp  */


/*
 * Author: Philogelos A. <Philogelos@yahoo.com>
 * Maintainer: Philogelos A.
 * Keywords: C++, library, containers
 *
 * Copyright (C) 1998 Philogelos A.
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


#ifndef __MEMORYMONITOR_HPP__
#define __MEMORYMONITOR_HPP__

/* $Id: MemoryMonitor.hpp,v 1.1.1.1 2000/07/19 16:56:54 philogelos Exp $ */

#include "defines.h"

BEGIN_QR_NAMESPACE

struct StatRecord
{
  Index total;
  Index actual;
  Index max;
  double average;
};
  

class MemoryMonitor
{
public:
  INLINE static int  init();
  INLINE static void release();

  INLINE static void inc( Index anAmount, void *anAddr );
  INLINE static void dec( Index anAmount, void *anAddr );
  INLINE static Index amount();

  INLINE static boolean checkDelete( const void *aPointer );

  INLINE static void dumpStatistics();

  static char         *memoryHog;
  static Index         hogSize;
  static Index         allocated;
  static Index         maxArea;
  static Index         statBufferSize;
  static StatRecord   *statBuffer;
  static boolean       wasOverflowed;
  static int           dummyBootstrapper;
  static boolean       wasInitialised;
};

END_QR_NAMESPACE

/* __MEMORYMONITOR_HPP__ */
#endif

