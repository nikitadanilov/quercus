// -*-C++-*- 

/*  inc/platform/POSIXPlatform.hpp  */

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



#ifndef __POSIXPLATFORM_HPP__
#define __POSIXPLATFORM_HPP__

/* $Id: POSIXPlatform.hpp,v 1.1.1.1 2000/07/19 17:13:53 philogelos Exp $ */

#define USE_POSIX

#if defined( WANT_USE_POSIX )
#define USE_POSIX
#elif defined( UNWANT_USE_POSIX )
#if defined( USE_POSIX )
#undef USE_POSIX
#endif
#endif

#if defined( USE_POSIX )

#include "ANSICPlatform.hpp"
#include "Object.hpp"
#include "defines.h"
#include "platform/threads/Thread.hpp"

#if defined( __GNUC__ )

/** 
	Debugger of choice. E.g., gdb, dbx, adb, sdb etc.
*/
#define DEBUGGER_COMMAND "gdb"
#elif defined( __SUNPRO_CC )
#define DEBUGGER_COMMAND "dbx"
#else
#define DEBUGGER_COMMAND "adb"
#endif

/**
   Default image name. This image name will
   be reported by the POSIXPlatform::getImageName()
   until first call to the POSIXPlatform::setImageName().

   @see POSIXPlatform::getImageName()
   @see POSIXPlatform::setImageName()
*/
#define IMAGE_NAME "test"

#define USE_GETTIMEOFDAY
#if !defined( __linux__ )
#define USE_CLOCK_GETTIME
#endif

// #define USE_GETITIMER
// #define USE_CLOCK /* generally broken */
#define SHARE_SIGNAL_COUNTER false

#if defined( WANT_DEBUGGER_COMMAND )
#define DEBUGGER_COMMAND WANT_DEBUGGER_COMMAND
#endif

#if defined( WANT_IMAGE_NAME )
#define IMAGE_NAME WANT_IMAGE_NAME
#endif

#if defined( WANT_USE_GETTIMEOFDAY )
#define USE_GETTIMEOFDAY
#elif defined( UNWANT_USE_GETTIMEOFDAY )
#if defined( USE_GETTIMEOFDAY )
#undef USE_GETTIMEOFDAY
#endif
#endif

#if defined( WANT_USE_CLOCK_GETTIME )
#define USE_CLOCK_GETTIME
#elif defined( UNWANT_USE_CLOCK_GETTIME )
#if defined( USE_CLOCK_GETTIME )
#undef USE_CLOCK_GETTIME
#endif
#endif

#if defined( WANT_USE_CLOCK )
#define USE_CLOCK
#elif defined( UNWANT_USE_CLOCK )
#if defined( USE_CLOCK )
#undef USE_CLOCK
#endif
#endif

#if defined( WANT_SHARE_SIGNAL_COUNTER )
#if defined( SHARE_SIGNAL_COUNTER )
#undef SHARE_SIGNAL_COUNTER
#endif
#define SHARE_SIGNAL_COUNTER WANT_SHARE_SIGNAL_COUNTER
#endif


BEGIN_QR_NAMESPACE

#if defined( USE_THREADS )
class PSemaphore;
#endif
/**
   POSIX platform. Implements methods of Platform
   interface as wrappers around libc calls.

   @author Philogelos
   @created
*/
class POSIXPlatform : public ANSICPlatform,
					  public virtual Object
{

  /**
	 Sets panic handler on SIGSEGV and SIGBUS.
   */
public: POSIXPlatform();

  /**
	 Nop.
   */
public: virtual ~POSIXPlatform();


  /**
	 Fork. See man fork.
  */
public: virtual int fork();

  /**
	 Exec. Family of exec() functions.
  */
public: virtual void execl( const char *path, ... );
public: virtual void vexecl( const char *path, 
							 va_list nullTerminatedArgvs,
							 Index aLength );
public: virtual void execv( const char *path, char *const argv[] );
public: virtual void execle( const char *path, ... );
public: virtual void vexecle( const char *path, 
							  va_list nullTerminatedArgvsAndEnvp,
							  Index aLength );
public: virtual void execve( const char *path, 
							char *const argv[], 
							char *const envp[] );
public: virtual void execlp( const char *file, ... );
public: virtual void vexeclp( const char *path, va_list nullTerminatedArgvs,
							  Index aLength );
public: virtual void execvp( const char *file, char *const argv[] );

public: virtual void system( const char *aCmd );

  /**
	 Returns the pid of the caller process.
  */
public: virtual pid_t getPid();

  /**
	 Sends given signal to the process with given pid.
	 See kill(2) for details.
  */
public: virtual void kill( pid_t aPid, int aSig );


  /**
	 Maps memory object to the calling process virtual address space.
	 See mmap(2) for details.
  */
public: virtual void *mmap( void *addr, size_t len, 
							int prot, int flags,
							int fildes, off_t off );

  /**
	 Unmaps memory pages. See unmap(2) for details.
  */
public: virtual void munmap( void *addr, size_t len );

#if defined( USE_THREADS )
public: virtual void startProfilingThread( String anOutFilesTemplate );
#endif

  /**
	 Calls strerror().
  */
public: virtual char *getErrorDescription( int errCode );

  /**
	 Calls _exit().
  */
public: virtual void exitImmediate( long status );
  
public: static void *allocateMemoryBootstrapPOSIX( Index aSize );
public: static void  deallocateMemoryBootstrapPOSIX( void *aPointer );


  /**
	 Drops core.
  */
public: virtual void suicide() NORETURN;

  /**
	 Attaches debugger. Forks and execlps DEBUGGER_COMMAND
	 giving it two arguments (not counting argv[0]):
	 result of getImageName() and pid.

	 @see DEBUGGER_COMMAND
	 @see getImageName()
  */
public: virtual void attachDebugger();

  /**
	 Sets image name.
  */
public: virtual void setImageName( const char *aName );

  /**
	 Returns image name.
	 Default image name IMAGE_NAME can be overriden by call
	 to setImageName().

	 @see #setImageName()
	 @see IMAGE_NAME
  */
public: virtual const char *getImageName() const;

public: virtual char *getTimeStampString();

  /**
	 Returns "\n"
  */
public: virtual char *getNL() const;

#if defined( USE_THREADS )
public: void   startSignalWaiterThread();
public: static PSemaphore *signalCatched;
public: static Thread     *signalWaiter;
protected: static void *signalWaiterLoop( void * );
#endif

  /**
   */
public:  virtual boolean equals( const Top *anOther ) const;

  /**
   */
public:  virtual Top *clone() const;

public:  virtual String  toString() const;

  /**
   */
public:  virtual String  getClassName() const;

#if defined( TESTING )

  /**
     Test method.
  */
public:  virtual boolean tester( int aParam ) const;
#endif

protected: const char *imageName;
};

END_QR_NAMESPACE

/* USE_POSIX */
#endif


/*
 * $Log: POSIXPlatform.hpp,v $
 * Revision 1.1.1.1  2000/07/19 17:13:53  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.9  2000/04/22 19:25:58  god
 * USE_GETTIMEOFDAY added
 *
 * Revision 1.8  2000/04/09 12:00:47  god
 * CVS Log keyword correction finished
 *
 * Revision 1.7  2000/04/09 11:29:36  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.6  2000/04/07 17:08:59  god
 * SHARE_SIGNAL_COUNTER made true/false switch and initial version of ::startProfilingThread() added.
 *
 * Revision 1.5  2000/04/05 18:01:25  god
 * added semaphore to count catched signals (incremented in signal handler).
 *
 * Revision 1.4  2000/04/05 17:19:31  god
 * Dynamic modules, askUser (+readline) dlsym/dladdr-based Backtrace
 *
 * Revision 1.3  2000/04/05 15:01:06  god
 * ::system() added
 *
 * Revision 1.2  2000/04/03 10:52:47  god
 * fork and exec?? family of functions added.
 *
 * Revision 1.1.1.1  2000/04/01 14:07:47  god
 * Imported sources
 * */

/* __POSIXPLATFORM_HPP__ */
#endif
