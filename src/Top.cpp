// -*-C++-*-

/*  src/Top.cpp  */


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


/* $Id: Top.cpp,v 1.2 2000/10/20 20:29:20 philogelos Exp $ */
#if !defined(_INLINE)
static char cvsid[] = "@(#)$Id: Top.cpp,v 1.2 2000/10/20 20:29:20 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif

#include "platform/threads/ThreadFactory.hpp"
#include "platform/threads/Mutex.hpp"
#include "platform/threads/MGuard.hpp"
#include "Top.hpp"
#include "String.hpp"
#include "Debug.hpp"

BEGIN_QR_NAMESPACE

Top::~Top()
{
#if defined( MEMORY_LEAK_TEST )

  if( topLock != NULL )
	{
	  topLock -> enter( this );
	}

  if( nextInAllocatedChain != null )
	{
	  nextInAllocatedChain -> 
		prevInAllocatedChain = prevInAllocatedChain;
	}
  else
	{
	  lastInAllocatedChain = prevInAllocatedChain;
	}

  if( prevInAllocatedChain != null )
	{
	  prevInAllocatedChain -> 
		nextInAllocatedChain = nextInAllocatedChain;
	}
  else
	{
	  firstInAllocatedChain = nextInAllocatedChain;
	}
  if( topLock != NULL )
	{
	  topLock -> leave( this );
	}

/* MEMORY_LEAK_TEST */
#endif
}

#if defined( MEMORY_LEAK_TEST )
Top *Top::firstInAllocatedChain = nil;
Top *Top::lastInAllocatedChain = nil;
Mutex *Top::topLock = NULL;

#endif

#if defined( USE_TYPEID )
String  Top::getClassName() const
{
  return String( typeid( *this ).name() );
}

#endif

END_QR_NAMESPACE

#include "Top.ipp"


#if defined(_INLINE)
#include "../src/String.ipp"
#endif

/*
 * $Log: Top.cpp,v $
 * Revision 1.2  2000/10/20 20:29:20  philogelos
 * Simplifications through using of NopThreads
 *
 * Revision 1.1.1.1  2000/07/19 16:42:42  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:39  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:28  god
 * Imported sources
 *
 * Revision 1.3  1999/03/03 19:09:30  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.2  1999/02/28 15:58:42  philogelos
 * Tuned for inlines.
 *
 * Revision 1.1.1.1  1998/11/25 20:11:01  philogelos
 * Quercus Robusta
 *
 * Revision 1.4  1998/07/09 09:04:47  philogelos
 * custom new/delete added
 *
 * Revision 1.3  1998/07/07 14:30:01  philogelos
 * Memory leak in SUNWspro dynamic_cast fixed.
 *
 * Revision 1.2  1998/06/22 18:13:01  philogelos
 * Enumerations and containers added
 *
 * Revision 1.1.1.1  1998/06/22 08:47:12  philogelos
 * First version under CVS
 *
 * Revision 1.1.1.1  1998/04/01 17:15:29  philogelos
 * first version under CVS
 * */
