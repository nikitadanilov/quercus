// -*-C++-*- 

/*  src/platform/threads/ThreadDeath.cpp  */

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



/* $Id: ThreadDeath.cpp,v 1.1.1.1 2000/07/19 16:52:02 philogelos Exp $ */
#if !defined(_INLINE)
static char cvsid[] = "@(#)$Id: ThreadDeath.cpp,v 1.1.1.1 2000/07/19 16:52:02 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif

#include "platform/threads/Thread.hpp"
#include "platform/threads/ThreadDeath.hpp"
#include "Debug.hpp"

BEGIN_QR_NAMESPACE

ThreadDeath::ThreadDeath( Thread *aThread, 
						  String aMessage, 
						  const Top *const aSource ) :
  RuntimeError( aMessage, aSource ),
  Exception( aMessage, aSource )
{
  preC_( aThread != ( Thread * ) NULL );
  thread = aThread;
}

ThreadDeath::~ThreadDeath()
{}

Thread *ThreadDeath::getThread() const
{
  return thread;
}

String  ThreadDeath::getDescription() const
{
  return RuntimeError::getDescription() + 
	" :\n thread cancelled";
}

String  ThreadDeath::getClassName() const
{
  return "ThreadDeath";
}

END_QR_NAMESPACE

#if defined(_INLINE)
#include "../src/Debug.ipp"
#endif


/*
 * $Log: ThreadDeath.cpp,v $
 * Revision 1.1.1.1  2000/07/19 16:52:02  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:44  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:35  god
 * Imported sources
*/
