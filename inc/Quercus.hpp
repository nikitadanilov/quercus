// -*-C++-*- 

/*  inc/Quercus.hpp  */

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



#ifndef __QUERCUS_HPP__
#define __QUERCUS_HPP__

/* $Id: Quercus.hpp,v 1.1.1.1 2000/07/19 16:57:18 philogelos Exp $ */

#include "Object.hpp"
#include "defines.h"
#include "String.hpp"

// #define SHOW_COPYRIGHT_ON_STARTUP

#if defined( WANT_SHOW_COPYRIGHT_ON_STARTUP )
#define SHOW_COPYRIGHT_ON_STARTUP
#elif defined( UNWANT_SHOW_COPYRIGHT_ON_STARTUP )
#if defined( SHOW_COPYRIGHT_ON_STARTUP )
#undef SHOW_COPYRIGHT_ON_STARTUP
#endif
#endif

BEGIN_QR_NAMESPACE

/**
   Class holding some global infos.

   @author Philogelos
   @created 2000-02-22
*/
class Quercus : public Object
{
public: static String  buildDate();
public: static String  buildHost();
public: static String  builder();
public: static Index   build();

public: static Index   majorVersion();
public: static Index   minorVersion();
public: static Index   microVersion();

public: static String  codename();

public: static String  versionInfo();
public: static String  copyrightInfo();
public: static String  configInfo();

public: static boolean isDebugOn();
public: static boolean isPurePanicOn();
public: static boolean isPureThrowsOn();
public: static boolean isDropCoreOnPanicOn();
public: static boolean isAsserionFailsAreFatalOn();
public: static boolean isAttachDebuggerOnErrorOn();
public: static boolean isEnterMonitorOnException();
public: static boolean isInlineGetLoggerOn();
public: static boolean isTestingOn();
public: static boolean isInlineOn();
public: static boolean isPerClassNewOn();
public: static boolean isProfileMemAllocOn();
public: static boolean isUseSTLOn();
public: static boolean isUseTypeidOn();
public: static boolean isUseThreadsOn();
public: static boolean isUseNamespaceOn();
public: static boolean isMemoryLeakTestOn();
public: static boolean isTrackBackpointersOn();
public: static boolean isGuardAddrefOn();
public: static boolean isUseBoehmGCOn();
public: static boolean isAskUserUseReadlineOn(); 
public: static boolean isUsePOSIXOn();
public: static boolean isUseGetTimeOfDayOn();
public: static boolean isUseClockGettimeOn();
public: static boolean isUseClockOn();
public: static boolean isShareSignalCounterOn();
public: static boolean isWrapMainOn();
public: static boolean isCheckDeletesOn();
public: static boolean isUseAllocChainOn();
public: static boolean isDecarateAllocationsOn();
public: static boolean isDebugThreadsOn();
public: static boolean isUseXqOn();
public: static boolean isXqUseX11MutexOn();
public: static boolean isXqUseXInitThreadsOn();
public: static boolean isXqXCheckEventHackOn();
public: static boolean isUseXPMOn();
public: static boolean isUseWqOn();
public: static boolean isSolarisMGuardBugOn();
public: static boolean isHasBFDOn();
public: static boolean isHasLibertyOn();
public: static boolean isUseDladdrDlsymForBacktraceOn();
public: static boolean isUseMethodMapOn();
public: static boolean isUsePThreadsOn();
public: static boolean isUseWin32On();
public: static boolean isUseWin32ThreadsOn();
public: static boolean isLightweightGuardOn();
public: static boolean isUseCqOn();
public: static boolean isShowCopyrightOnStartupOn();

public: static String  platform();

protected: static int initClass();
protected: static int initHook;
};

END_QR_NAMESPACE

/*
 * $Log: Quercus.hpp,v $
 * Revision 1.1.1.1  2000/07/19 16:57:18  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.7  2000/04/22 19:25:39  god
 * isUseGetTimeOfDayOn() added
 *
 * Revision 1.6  2000/04/09 12:00:47  god
 * CVS Log keyword correction finished
 *
 * Revision 1.5  2000/04/09 11:29:17  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.4  2000/04/05 18:11:22  god
 * ::isShareSignalCounterOn() added
 *
 * Revision 1.3  2000/04/05 16:49:29  god
 * ::platform() added
 *
 * Revision 1.2  2000/04/02 13:48:52  god
 * boolean isUseClock() added
 *
 * Revision 1.1.1.1  2000/04/01 14:07:39  god
 * Imported sources
 * */

/* __QUERCUS_HPP__ */
#endif
