// -*-C++-*- 

/*  src/DebugDialogue.cpp  */

/*
 * Author: Philogelos A. <Philogelos@yahoo.com>
 * Maintainer: Philogelos A.
 * Keywords: C++, library, containers
 *
 * Copyright (C) 1999, 2000 Philogelos A.
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



/* $Id: DebugDialogue.cpp,v 1.1.1.1 2000/07/19 16:40:41 philogelos Exp $ */
#if !defined( _INLINE )
static char cvsid[] = "@(#)$Id: DebugDialogue.cpp,v 1.1.1.1 2000/07/19 16:40:41 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif

#include "Quercus.hpp"
#include "platform/Platform.hpp"
#include "Backtrace.hpp"
#include "exceptions/InternalError.hpp"
#include "DebugDialogue.hpp"
#include "Debug.hpp"
#include "containers/lists/List.hpp"
#include "platform/POSIXPlatform.hpp"
#include "new-operator.hpp"
#include "Top.hpp"

BEGIN_QR_NAMESPACE

DebugDialogue::DebugDialogue()
{}

DebugDialogue::~DebugDialogue()
{}

void *DebugDialogue::run()
{
  while( true )
	{
	  switch( PLAF -> askUser( "MCR", "> ",
							   cont,    "CONT", "Continue execution",
							   exit,    "EXIT", "Exit process",
							   core,    "CORE", "Drop core",
							   toss,    "TOSS", "Throw InternalError",
#if defined( USE_THREADS )
							   threads, "THRL", "List threads",
#endif
#if defined( MEMORY_LEAK_TEST )
							   objects, "OBJL", "List allocated objects",
#endif
#if defined( USE_ALLOC_CHAIN )
							   chunks,  "CHKL", "List allocated memory chunks",
#endif
#if defined( TRACK_BACKPOINTERS )
							   back,    "BACK", "Print back poinetrs",
#endif
							   debug,   "DBGR", "Attach debugger",
							   modules, "MODL", "List loaded modules",
							   trace,   "TRCE", "Print stack trace",
							   config,  "CNFG", "Print configuration",
							   shell,   "SHLL", "Escape to OS shell",
							   cont,    NULL,   NULL ) )
		{
		case cont:
		  return NULL;
		case exit:
		  PLAF -> exitImmediate( 1 );
		  break;
		case core:
		  PLAF -> suicide();
		  break;
		case toss:
		  throw new InternalError( "User choice", null );
		case threads:
#if defined( USE_THREADS )
		  DLOGOBJECT( THR_FACTORY -> listThreads() );
#endif
		  break;
		case objects:
#if defined( MEMORY_LEAK_TEST )
		  Top::dumpAllocated();
#endif
		  break;
		case chunks:
#if defined( USE_ALLOC_CHAIN )
		  dumpAllocatedByNew();
#endif
		  break;
		case back:
#if defined( TRACK_BACKPOINTERS )
		  Top::dumpBackpointers();
#endif
		  break;
		case debug:
		  PLAF -> attachDebugger();
		  break;
		case modules:
		  DLOG( "Not implemented yet." );
		  break;
		case trace:
		  {
			Backtrace backtrace;

			backtrace.fill();
			DLOGOBJECT( &backtrace );
		  }
		  break;
		case config:
		  DLOG( Quercus::configInfo() );
		  break;
		case shell:
#if defined( USE_POSIX )
		  DLOG( "Our pid: %li", TCAST( PLAF, POSIXPlatform ) -> getPid() );
		  DLOG( "Exit shell to return\n" );
		  TCAST( PLAF, POSIXPlatform ) -> system( "sh -i" );
		  DLOG( "Welcome back" );
#else
		  DLOG( "No support of shell for this OS yet." );
#endif
		  break;
		default:
		  impossible_;
		}
	}
}

String  DebugDialogue::getClassName() const
{
  return "DebugDialogue";
}

END_QR_NAMESPACE

#if defined( _INLINE )
#include "../src/Debug.ipp"
#endif


/*
 * $Log: DebugDialogue.cpp,v $
 * Revision 1.1.1.1  2000/07/19 16:40:41  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.5  2000/04/09 12:00:48  god
 * CVS Log keyword correction finished
 *
 * Revision 1.4  2000/04/09 11:29:38  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.3  2000/04/07 17:11:38  god
 * Backpointers and more decoration to shell exit added
 *
 * Revision 1.2  2000/04/05 17:19:42  god
 * Dynamic modules, askUser (+readline) dlsym/dladdr-based Backtrace
 *
 * Revision 1.1  2000/04/05 14:07:32  god
 * Created
 * */
