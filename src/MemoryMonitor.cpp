//-*-C++-*-

/*  src/MemoryMonitor.cpp  */


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



/* $Id: MemoryMonitor.cpp,v 1.1.1.1 2000/07/19 16:41:07 philogelos Exp $ */
#if !defined(_INLINE)
static char cvsid[] = "@(#)$Id: MemoryMonitor.cpp,v 1.1.1.1 2000/07/19 16:41:07 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif


#include "MemoryMonitor.hpp"
#include "defines.h"

BEGIN_QR_NAMESPACE

Index         MemoryMonitor::allocated = 0;
char         *MemoryMonitor::memoryHog = ( char * ) NIL;
Index         MemoryMonitor::hogSize = 0; /* set in ::init() */
Index         MemoryMonitor::maxArea = 0;
Index         MemoryMonitor::statBufferSize = 0; /* set in ::init() */
StatRecord   *MemoryMonitor::statBuffer = ( StatRecord * ) NIL;
boolean       MemoryMonitor::wasInitialised = false;
int           MemoryMonitor::dummyBootstrapper = MemoryMonitor::init();

END_QR_NAMESPACE

#include "../src/MemoryMonitor.ipp"

/*
 * $Log: MemoryMonitor.cpp,v $
 * Revision 1.1.1.1  2000/07/19 16:41:07  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:39  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:28  god
 * Imported sources
 *
 * Revision 1.4  1999/05/22 13:00:29  philogelos
 * Merging sources back from SPARC
 *
 * Revision 1.3  1999/03/03 19:09:27  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.2  1999/02/28 15:49:55  philogelos
 * Tuned for inlines. Code moved out to .ipp
 *
 * Revision 1.1.1.1  1998/11/25 20:11:01  philogelos
 * Quercus Robusta
 *
 * Revision 1.1  1998/07/09 09:30:37  philogelos
 * new files added to the repository
 * */
