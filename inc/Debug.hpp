//-*-C++-*-

/*  inc/Debug.hpp  */


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


#ifndef __DEBUG_HPP__
#define __DEBUG_HPP__

/* $Id: Debug.hpp,v 1.4 2001/06/23 12:15:32 philogelos Exp $ */

#include "defines.h"
#include "Object.hpp"
#include "platform/threads/Thread.hpp"
#include "platform/threads/RecMutex.hpp"

/* #include "exceptions/Exception.hpp" */

#include "debug-macros.hpp"

BEGIN_QR_NAMESPACE

class Mutex;
class String;
class Object;
class Exception;
interface Top;

#define GET_LOGGER_BODY							\
{												\
  if( logger == nil )							\
	{											\
	  logger = new Debug();						\
	  logger -> dontManage();					\
	}											\
  return logger;								\
}

/** 
	Debugging and logging facility.
	
	@author Philogelos
	@created «‚“ 18 ∏Ó› 1998 19:03:15
*/
class Debug : public Object
{
public: INLINE static Debug *getLogger
( const Top *const /* aClient */ = ( const Top * ) null, 
  const char *const /* aModule */ = NULL, 
  const char *const /* aMethod */ = NULL,
  const Index /* anOffset */ = 0 )
#if defined( INLINE_GETLOGGER )
  GET_LOGGER_BODY
#endif
 ;

  /** 
	  Formats arguments like sprintf and calls
	  Platform::rawErrorVPrintf() prepending
	  timestamp and thread id.

	  @see Platform::rawErrorVPrintf()
   */
public:  INLINE void log( const char *const, ... ) PRINTF_ALIKE( 2, 3 );

  /**
	 Calls given method on the given object and passes
	 result to ::log().
	 
	 @see #log()
  */
public:  INLINE void logObject( const Top *,
						 String ( Top::* )() const = &Top::toString );
  /**
	 Calls given method on the given object and passes
	 result to ::log().
	 
	 @see #log()
  */
public:  INLINE void logObject( const char *const, const Top *,
						 String ( Top::* )() const = &Top::toString ) 
  PRINTF_ALIKE( 2, 0 );

  /**
	 Converts string to the UTF8 and calls ::log().

	 @see #log()
   */
public:  INLINE void logString( const char *const, String aString );
  
  /** Call this as last resort.
	  Prints message on stderr and _exits.
  */
public:  INLINE void panic(const char *const );

  /** Silently drops core.
	*/
public:  INLINE static void dumpCore();

  /** 
	  If first argument is true does nothing else logs a message.
  */
public:  INLINE void assertion( boolean aCondition,
								const char *const aMessage,
								const char *const aConditionAsString = "",
								const char *const aFunction = "",
								const char *const aFileName = "",
								const Index   aLineNo = -1 );

  /** If condition doesn't hold, logs message and
	  throws InternalError. 
  */
public:  INLINE void testCondition( boolean aCondition,
									const char *const aMessage,
									const char *const aConditionAsString = "",
									const char *const aFunction = "",
									const char *const aFileName = "",
									const Index   aLineNo = -1 );
  
public:  INLINE void preCondition( boolean aCondition,
								   const char *const aMessage,
								   const char *const aConditionAsString = 
								   preConditionFailedMessage,
								   const char *const aFunction = "",
								   const char *const aFileName = "",
								   const Index   aLineNo = -1 );

public:  INLINE void postCondition( boolean aCondition,
									const char *const aMessage,
									const char *const aConditionAsString = 
									postConditionFailedMessage,
									const char *const aFunction = "",
									const char *const aFileName = "",
									const Index   aLineNo  = -1 );

  /** Describes exception using Exception::diagnoze().*/
public:  INLINE void exception( Exception *anEx );

  /** Prints stack backtrace to the debug log, if possible. */
public:  INLINE void printStackTrace();

  /** Enter some rudimentary interaction with user. */
public:  virtual void monitor() const;

public:  virtual String  getString() const;
public:  virtual String  getClassName() const;

public: static const char * const assertionFailedMessage;
public: static const char * const impossibleMessage;
public: static const char * const conditionFailedMessage;
public: static const char * const preConditionFailedMessage;
public: static const char * const postConditionFailedMessage;
public: static const char * const nilObjectLiteral;

  /**
	 Setup exception handling machinery:
	 install terminate and unexpected handlers
  */
protected:  INLINE Debug();
protected:  virtual ~Debug();

protected: Mutex *getMutex() const;
protected: mutable Mutex *mutex;

protected:  static Debug *logger;

protected:  static boolean shouldDropCore;
protected:  static boolean assertionFailsAreFatal;
protected:  static boolean attachDebuggerOnError;
protected:  Index  totalMessagesLogged;
};


END_QR_NAMESPACE

/*
 * $Log: Debug.hpp,v $
 * Revision 1.4  2001/06/23 12:15:32  philogelos
 * ::mutex member marked mutable
 *
 * Revision 1.3  2000/10/20 20:29:19  philogelos
 * Simplifications through using of NopThreads
 *
 * Revision 1.2  2000/08/26 13:48:57  philogelos
 * new parameters added to the ::getLogger(). Hopefully will evolve into
 * per-module controllable debug settings
 *
 * Revision 1.1.1.1  2000/07/19 16:55:41  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.4  2000/04/09 12:00:47  god
 * CVS Log keyword correction finished
 *
 * Revision 1.3  2000/04/09 11:29:16  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.2  2000/04/05 17:19:20  god
 * Dynamic modules, askUser (+readline) dlsym/dladdr-based Backtrace
 *
 * Revision 1.1.1.1  2000/04/01 14:07:39  god
 * Imported sources
 *
 * Revision 1.5  1999/05/22 13:00:22  philogelos
 * Merging sources back from SPARC
 *
 * Revision 1.4  1999/03/03 20:43:08  philogelos
 * Switch to vararg-style argument passing
 *
 * Revision 1.3  1999/03/03 19:09:02  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.2  1999/02/28 12:44:17  philogelos
 * checks for printf-alikes added (does not work for now)
 *
 * Revision 1.1.1.1  1998/11/25 20:11:05  philogelos
 * Quercus Robusta
 *
 * Revision 1.5  1998/07/09 09:04:42  philogelos
 * custom new/delete added
 *
 * Revision 1.4  1998/07/07 14:29:48  philogelos
 * Memory leak in SUNWspro dynamic_cast fixed.
 *
 * Revision 1.3  1998/06/23 07:26:06  philogelos
 * ::logObject() methods added
 *
 * Revision 1.2  1998/06/22 18:12:54  philogelos
 * Enumerations and containers added
 *
 * Revision 1.1.1.1  1998/06/22 08:47:11  philogelos
 * First version under CVS
 *
 * Revision 1.1.1.1  1998/04/01 17:15:30  philogelos
 * first version under CVS
 * */

/* __DEBUG_HPP__ */
#endif
