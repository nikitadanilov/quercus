// -*-C++-*- 

/*  inc/platform/Win32Platform.hpp  */

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



#ifndef __WIN32PLATFORM_HPP__
#define __WIN32PLATFORM_HPP__

/* $Id: Win32Platform.hpp,v 1.1.1.1 2000/07/19 17:13:53 philogelos Exp $ */

/* #define USE_WIN32 */


#if defined( WANT_USE_WIN32 )
#define USE_WIN32
#elif defined( UNWANT_USE_WIN32 )
#if defined( USE_WIN32 )
#undef USE_WIN32
#endif
#endif


#if defined( USE_WIN32 )

/* nonstandard extension used : nameless struct/union */
#pragma warning( disable : 4201 )
#include <windows.h>
#pragma warning( default: 4201 )

#undef interface
/** Marks interface (ie, type). */
#define interface    class

#include "ANSICPlatform.hpp"
#include "Object.hpp"
#include "defines.h"

/**
   Maximum possible module name length under WIN32.
*/
#define MODULE_NAME_LENGTH   255

/**
   Maximum possible length of the error message text under WIN32.
*/
#define ERROR_MESSAGE_LENGTH 1024

/**
   Maximum possible length or the command used to launch and attach debugger.
*/
#define SYSTEM_CMD_LENGTH    1024

/**
   Preferrable width of debugging console in characters.
*/
#define CONSOLE_WIDTH	     80

/**
   Preferrable height of debugging console in characters.
*/
#define CONSOLE_HEIGHT       900

#if defined( DEBUGGER_COMMAND )
#undef DEBUGGER_COMMAND
#endif

/**
   Debugger of choice under WIN32.
*/
#define DEBUGGER_COMMAND "MSDEV -p "


#if defined( WANT_MODULE_NAME_LENGTH )
#define MODULE_NAME_LENGTH WANT_MODULE_NAME_LENGTH
#endif

#if defined( WANT_ERROR_MESSAGE_LENGTH )
#define ERROR_MESSAGE_LENGTH WANT_ERROR_MESSAGE_LENGTH
#endif

#if defined( WANT_SYSTEM_CMD_LENGTH )
#define SYSTEM_CMD_LENGTH WANT_SYSTEM_CMD_LENGTH
#endif

#if defined( WANT_DEBUGGER_COMMAND )
#define DEBUGGER_COMMAND WANT_DEBUGGER_COMMAND
#endif

#if defined( WANT_LOG_BUFFER_SIZE )
#define LOG_BUFFER_SIZE WANT_LOG_BUFFER_SIZE
#endif

#if defined( WANT_CONSOLE_WIDTH )
#define CONSOLE_WIDTH WANT_CONSOLE_WIDTH
#endif

#if defined( WANT_CONSOLE_HEIGHT )
#define CONSOLE_HEIGHT WANT_CONSOLE_HEIGHT
#endif

class Mutex;
class Thread;



BEGIN_QR_NAMESPACE

/**
   Win32 object with handle. Helper base-class
   for objects used by Win32 API.

   @author Philogelos
   @created
*/
class Win32Object : public virtual Object
{

  /**
	 Creates object associated with given handle.
  */
public: Win32Object( HANDLE handle );

  /**
	 If handle is not null call CloseHandle() on it.
  */
public: virtual ~Win32Object();


  /**
	 Returns handle associated with this object.
  */
public: HANDLE getHandle() const;

  /**
	 Sets handle to be associated with this object.
  */
public: void setHandle( HANDLE aHandle );
		
protected: HANDLE handle;
};

/**
   Interface to WIN32 API.
*/
class Win32Platform : public ANSICPlatform,
					  public virtual Object
{

  /**
	 Opens debugging console.
   */
public: Win32Platform();

  /**
   */
public: virtual ~Win32Platform();

  /**
	 Printfs result to the debugging console. 
	 Uses _cputs.
  */
public: virtual void rawErrorVPrintf( const char * format, va_list raw );

  /**
	 Printfs result to the debugging console. 
	 Uses _cputs.
  */
public: virtual char *getErrorDescription( int errCode );

  /**
	 Calls _exit().
  */
public: virtual void exitImmediate( long status );
  
public: static void *allocateMemoryBootstrapWin32( Index aSize );
public: static void  deallocateMemoryBootstrapWin32( void *aPointer );

  /**
	 Calls abort().
  */
public: virtual void suicide() NORETURN;

  /**
	 Spawns DEBUGGER_COMMAND with the result of the call to
	 _getpid() as the only argument. Uses system to execute
	 command.
	 
	 @see DEBUGGER_COMMAND
  */
public: virtual void attachDebugger();

public: virtual void setImageName( const char *aName );
public: virtual const char *getImageName() const;

public: virtual char *getTimeStampString();

  /**
	 Returns "\r\n"
  */
public: virtual char *getNL() const;

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

protected: const char *imageName;
};

END_QR_NAMESPACE

/* USE_WIN32 */
#endif


/*
 * $Log: Win32Platform.hpp,v $
 * Revision 1.1.1.1  2000/07/19 17:13:53  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:36  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:48  god
 * Imported sources
*/

/* __WIN32PLATFORM_HPP__ */
#endif
