// -*-C++-*- 

/*  src/Quercus.cpp  */

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



/* $Id: Quercus.cpp,v 1.1.1.1 2000/07/19 16:42:05 philogelos Exp $ */
#if !defined( _INLINE )
static char cvsid[] = "@(#)$Id: Quercus.cpp,v 1.1.1.1 2000/07/19 16:42:05 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif

#include "Quercus.hpp"
#include "Debug.hpp"

#include "ObjectWrapper.hpp"

#include "debug-macros.hpp"
#include "defines.h"
#include "Top.hpp"
#include "Object.hpp"
#include "platform/ANSICPlatform.hpp"
#include "platform/POSIXPlatform.hpp"
#include "platform/Platform.hpp"
#include "new-operator.hpp"
#include "platform/threads/Thread.hpp"
#include "ui/xq/Xq.hpp"
#include "ui/wq/Wq.hpp"
#include "platform/threads/RecMutex.hpp"
#include "Backtrace.hpp"
#include "MethodMap.hpp"
#include "platform/threads/PThread.hpp"
#include "platform/threads/ThreadFactory.hpp"
#include "platform/Win32Platform.hpp"
#include "platform/threads/Win32Thread.hpp"
#include "Guard.hpp"
#include "ui/cq/Cq.hpp"
#include "Quercus.hpp"

BEGIN_QR_NAMESPACE

String  Quercus::buildDate()
{
  return BUILD_DATE;
}

String  Quercus::buildHost()
{
  return BUILD_HOST;
}

String  Quercus::builder()
{
  return BUILDER;
}

Index   Quercus::build()
{
  return BUILD;
}


Index   Quercus::majorVersion()
{
  return MAJOR_VERSION;
}

Index   Quercus::minorVersion()
{
  return MINOR_VERSION;
}

Index   Quercus::microVersion()
{
  return MICRO_VERSION;
}


String  Quercus::codename()
{
  return QR_CODENAME;
}


String  Quercus::versionInfo()
{
  return String( "Quercus Robusta %li.%li.%li" ).
	format( 1, majorVersion(), minorVersion(), microVersion() ) +
	" [" + codename() + "] " + builder() + "@" + buildHost() + 
	" " + buildDate();
}

String  Quercus::copyrightInfo()
{
  return 
	"\nCopyright (C) 1998, 2000 Philogelos A. <Philogelos@yahoo.com>\n"
	"\n"
	"\nThis file is part of Quercus Robusta."
	"\nQuercus Robusta is free software; you can redistribute it and/or modify"
	"\nit under the terms of the GNU Library General Public License as published by"
	"\nthe Free Software Foundation; either version 2, or (at your option)"
	"\nany later version."
	"\n"
	"\nThis software is distributed in the hope that it will be useful,"
	"\nbut WITHOUT ANY WARRANTY; without even the implied warranty of"
	"\nMERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the"
	"\nGNU Library General Public License for more details."
	"\n"
	"\nYou should have received a copy of the GNU Library General Public License"
	"\nalong with this software; see the file COPYING.LIB.  If not, write to the"
	"\nFree Software Foundation, Inc., 59 Temple Place - Suite 330,"
	"\nBoston, MA 02111-1307, USA.\n";
}

String  Quercus::configInfo()
{
  return versionInfo() + 
	String( "\n"
			"DEBUG: %B\n"
			"PURE_PANICS: %B\n"
			"PURE_THROWS: %B\n"
			"DROP_CORE_ON_PANIC: %B\n"
			"ASSERTION_FAILS_ARE_FATAL: %B\n"
			"ATTACH_DEBUGGER_ON_ERROR: %B\n"
			"ENTER_MONITOR_ON_EXCEPTION: %B\n"
			"INLINE_GETLOGGER: %B\n"

			"TESTING: %B\n"
			"_INLINE: %B\n"
			"USE_PER_CLASS_NEW: %B\n"
			"PROFILE_MEM_ALLOC: %B\n"
			"USE_STL: %B\n"
			"USE_TYPEID: %B\n"
			"USE_THREADS: %B\n"
			"USE_NAMESPACE: %B\n"

			"MEMORY_LEAK_TEST: %B\n"
			"TRACK_BACKPOINTERS: %B\n"

			"GUARD_ADDREF: %B\n"

			"USE_BOEHM_GC: %B\n"
			"ASK_USER_MAX_CHOICES: %li\n"
			"ASK_USER_USE_READLINE: %B\n"

			"USE_POSIX: %B\n"
			"USE_GETTIMEOFDAY: %B\n"
			"USE_CLOCK_GETTIME: %B\n"
			"USE_CLOCK: %B\n"
			"SHARE_SIGNAL_COUNTER: %B\n"

			"WRAP_MAIN: %B\n"

			"CHECK_DELETES: %B\n"
			"USE_ALLOC_CHAIN: %B\n"
			"DECORATE_ALLOCATIONS: %B\n"

			"DEBUG_THREADS: %B\n"

			"USE_XQ: %B\n"
			"XQ_USE_X11_MUTEX: %B\n"
			"XQ_USE_XINITTHREADS: %B\n"
			"XQ_XCHECKEVENT_HACK: %B\n"
			"USE_XPM: %B\n"
				 
			"USE_WQ: %B\n"

			"SOLARIS_MGUARD_BUG: %B\n"

			"HAS_BFD: %B\n"
			"HAS_LIBERTY: %B\n"
			"USE_DLADDR_DLSYM_FOR_BACKTRACE: %B\n"

			"USE_METHOD_MAP: %B\n"
				 
			"USE_PTHREADS: %B\n"

			"USE_WIN32: %B\n"

			"USE_WIN32THREADS: %B\n"

			"LIGHTWEIGHT_GUARD: %B\n"

			"USE_CQ: %B\n"

			"SHOW_COPYRIGHT_ON_STARTUP: %B\n"
			"PLATFORM: %O\n" ).
	format( 1,
			isDebugOn(),
			isPurePanicOn(),
			isPureThrowsOn(),
			isDropCoreOnPanicOn(),
			isAsserionFailsAreFatalOn(),
			isAttachDebuggerOnErrorOn(),
			isEnterMonitorOnException(),
			isInlineGetLoggerOn(),

			isTestingOn(),
			isInlineOn(),
			isPerClassNewOn(),
			isProfileMemAllocOn(),
			isUseSTLOn(),
			isUseTypeidOn(),
			isUseThreadsOn(),
			isUseNamespaceOn(),

			isMemoryLeakTestOn(),
			isTrackBackpointersOn(),

			isGuardAddrefOn(),

			isUseBoehmGCOn(),
			( Index ) ASK_USER_MAX_CHOICES,
			isAskUserUseReadlineOn(),

			isUsePOSIXOn(),
			isUseGetTimeOfDayOn(),
			isUseClockGettimeOn(),
			isUseClockOn(),
			isShareSignalCounterOn(),

			isWrapMainOn(),

			isCheckDeletesOn(),
			isUseAllocChainOn(),
			isDecarateAllocationsOn(),

			isDebugThreadsOn(),

			isUseXqOn(),
			isXqUseX11MutexOn(),
			isXqUseXInitThreadsOn(),
			isXqXCheckEventHackOn(),
			isUseXPMOn(),

			isUseWqOn(),

			isSolarisMGuardBugOn(),

			isHasBFDOn(),
			isHasLibertyOn(),
			isUseDladdrDlsymForBacktraceOn(),

			isUseMethodMapOn(),

			isUsePThreadsOn(),

			isUseWin32On(),

			isUseWin32ThreadsOn(),

			isLightweightGuardOn(),

			isUseCqOn(),

			isShowCopyrightOnStartupOn(),
			OW( platform().clone() ) );
}


boolean Quercus::isDebugOn()
{
#if defined( DEBUG )
  return true;
#else
  return false;
#endif
}

boolean Quercus::isPurePanicOn()
{
#if defined( PURE_PANICS )
  return true;
#else
  return false;
#endif
}

boolean Quercus::isPureThrowsOn()
{
#if defined( PURE_THROWS )
  return true;
#else
  return false;
#endif
}

boolean Quercus::isDropCoreOnPanicOn()
{
  return DROP_CORE_ON_PANIC;
}

boolean Quercus::isAsserionFailsAreFatalOn()
{
  return ASSERTION_FAILS_ARE_FATAL;
}

boolean Quercus::isAttachDebuggerOnErrorOn()
{
  return ATTACH_DEBUGGER_ON_ERROR;
}

boolean Quercus::isEnterMonitorOnException()
{
#if defined( ENTER_MONITOR_ON_EXCEPTION )
  return true;
#else
  return false;
#endif
}

boolean Quercus::isInlineGetLoggerOn()
{
#if defined( INLINE_GETLOGGER )
  return true;
#else
  return false;
#endif
}

boolean Quercus::isTestingOn()
{
#if defined( TESTING )
  return true;
#else
  return false;
#endif
}

boolean Quercus::isInlineOn()
{
#if defined( _INLINE )
  return true;
#else
  return false;
#endif
}

boolean Quercus::isPerClassNewOn()
{
#if defined( USE_PER_CLASS_NEW )
  return true;
#else
  return false;
#endif
}

boolean Quercus::isProfileMemAllocOn()
{
#if defined( PROFILE_MEM_ALLOC )
  return true;
#else
  return false;
#endif
}

boolean Quercus::isUseSTLOn()
{
#if defined( USE_STL )
  return true;
#else
  return false;
#endif
}

boolean Quercus::isUseTypeidOn()
{
#if defined( USE_TYPEID )
  return true;
#else
  return false;
#endif
}

boolean Quercus::isUseThreadsOn()
{
#if defined( USE_THREADS )
  return true;
#else
  return false;
#endif
}

boolean Quercus::isUseNamespaceOn()
{
#if defined( USE_NAMESPACE )
  return true;
#else
  return false;
#endif
}

boolean Quercus::isMemoryLeakTestOn()
{
#if defined( MEMORY_LEAK_TEST )
  return true;
#else
  return false;
#endif
}

boolean Quercus::isTrackBackpointersOn()
{
#if defined( TRACK_BACKPOINTERS )
  return true;
#else
  return false;
#endif
}

boolean Quercus::isGuardAddrefOn()
{
#if defined( GUARD_ADDREF )
  return true;
#else
  return false;
#endif
}

boolean Quercus::isUseBoehmGCOn()
{
#if defined( USE_BOEHM_GC )
  return true;
#else
  return false;
#endif
}

boolean Quercus::isAskUserUseReadlineOn()
{
#if defined( ASK_USER_USE_READLINE )
  return true;
#else
  return false;
#endif
}

boolean Quercus::isUsePOSIXOn()
{
#if defined( USE_POSIX )
  return true;
#else
  return false;
#endif
}

boolean Quercus::isUseGetTimeOfDayOn()
{
#if defined( USE_GETTIMEOFDAY )
  return true;
#else
  return false;
#endif
}

boolean Quercus::isUseClockGettimeOn()
{
#if defined( USE_CLOCK_GETTIME )
  return true;
#else
  return false;
#endif
}

boolean Quercus::isUseClockOn()
{
#if defined( USE_CLOCK )
  return true;
#else
  return false;
#endif
}

boolean Quercus::isShareSignalCounterOn()
{
  return SHARE_SIGNAL_COUNTER;
}

boolean Quercus::isWrapMainOn()
{
#if defined( WRAP_MAIN )
  return true;
#else
  return false;
#endif
}

boolean Quercus::isCheckDeletesOn()
{
#if defined( CHECK_DELETES )
  return true;
#else
  return false;
#endif
}

boolean Quercus::isUseAllocChainOn()
{
#if defined( USE_ALLOC_CHAIN )
  return true;
#else
  return false;
#endif
}

boolean Quercus::isDecarateAllocationsOn()
{
#if defined( DECORATE_ALLOCATIONS )
  return true;
#else
  return false;
#endif
}

boolean Quercus::isDebugThreadsOn()
{
#if defined( DEBUG_THREADS )
  return true;
#else
  return false;
#endif
}

boolean Quercus::isUseXqOn()
{
#if defined( USE_XQ )
  return true;
#else
  return false;
#endif
}

boolean Quercus::isXqUseX11MutexOn()
{
#if defined( XQ_USE_X11_MUTEX )
  return true;
#else
  return false;
#endif
}

boolean Quercus::isXqUseXInitThreadsOn()
{
#if defined( XQ_USE_XINITTHREADS )
  return true;
#else
  return false;
#endif
}

boolean Quercus::isXqXCheckEventHackOn()
{
#if defined( XQ_XCHECKEVENT_HACK )
  return true;
#else
  return false;
#endif
}

boolean Quercus::isUseXPMOn()
{
#if defined( USE_XPM )
  return true;
#else
  return false;
#endif
}

boolean Quercus::isUseWqOn()
{
#if defined( USE_WQ )
  return true;
#else
  return false;
#endif
}

boolean Quercus::isSolarisMGuardBugOn()
{
#if defined( SOLARIS_MGUARD_BUG )
  return true;
#else
  return false;
#endif
}

boolean Quercus::isHasBFDOn()
{
#if defined( HAS_BFD )
  return true;
#else
  return false;
#endif
}

boolean Quercus::isHasLibertyOn()
{
#if defined( HAS_LIBERTY )
  return true;
#else
  return false;
#endif
}

boolean Quercus::isUseDladdrDlsymForBacktraceOn()
{
#if defined( USE_DLADDR_DLSYM_FOR_BACKTRACE )
  return true;
#else
  return false;
#endif
}

boolean Quercus::isUseMethodMapOn()
{
#if defined( USE_METHOD_MAP )
  return true;
#else
  return false;
#endif
}

boolean Quercus::isUsePThreadsOn()
{
#if defined( USE_PTHREADS )
  return true;
#else
  return false;
#endif
}

boolean Quercus::isUseWin32On()
{
#if defined( USE_WIN32 )
  return true;
#else
  return false;
#endif
}

boolean Quercus::isUseWin32ThreadsOn()
{
#if defined( USE_WIN32THREADS )
  return true;
#else
  return false;
#endif
}

boolean Quercus::isLightweightGuardOn()
{
#if defined( LIGHTWEIGHT_GUARD )
  return true;
#else
  return false;
#endif
}

boolean Quercus::isUseCqOn()
{
#if defined( USE_CQ )
  return true;
#else
  return false;
#endif
}

boolean Quercus::isShowCopyrightOnStartupOn()
{
#if defined( SHOW_COPYRIGHT_ON_STARTUP )
  return true;
#else
  return false;
#endif
}

String  Quercus::platform()
{
  return PLAF -> getClassName();
}

int Quercus::initClass()
{
  if( isShowCopyrightOnStartupOn() )
	{
	  DLOGSTRING( "%s", copyrightInfo() );
	}
  return 1;
}

int Quercus::initHook = Quercus::initClass();

END_QR_NAMESPACE

#if defined( _INLINE )
#include "../src/Debug.ipp"
#endif

/*
 * $Log: Quercus.cpp,v $
 * Revision 1.1.1.1  2000/07/19 16:42:05  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.7  2000/04/22 19:25:33  god
 * isUseGetTimeOfDayOn() added
 *
 * Revision 1.6  2000/04/09 12:00:48  god
 * CVS Log keyword correction finished
 *
 * Revision 1.5  2000/04/09 11:29:39  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.4  2000/04/05 18:11:12  god
 * ::isShareSignalCounterOn() added
 *
 * Revision 1.3  2000/04/05 16:49:15  god
 * ::platform() added
 *
 * Revision 1.2  2000/04/02 13:49:10  god
 * boolean isUseClock() added
 *
 * Revision 1.1.1.1  2000/04/01 14:07:29  god
 * Imported sources
 * */
