//-*-C++-*-

/*  src/Debug.ipp  */


/*
 * Author: Philogelos A. <Philogelos@yahoo.com>
 * Maintainer: Philogelos A.
 * Keywords: C++, library, containers
 *
 * Copyright (C) 1998, 1999 Philogelos A.
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



#ifndef __DEBUG_IPP__
#define __DEBUG_IPP__

/* $Id: Debug.ipp,v 1.2 2000/08/26 13:48:57 philogelos Exp $ */

#include "Debug.hpp"
#include "String.hpp"
#include "Quercus.hpp"
#include "Backtrace.hpp"
#include "platform/Platform.hpp"
#include "exceptions/InternalError.hpp"

#if defined( USE_THREADS )
#include "platform/threads/ThreadsSystem.hpp"
#include "platform/threads/ThreadFactory.hpp"
#include "platform/threads/MGuard.hpp"
#define LOCK_INSTANCE NS_PREFIX MGuard _instanceLock( getMutex(), this )
#else
#define LOCK_INSTANCE
#endif

#if defined( __BORLANDC__ )
#include <except.h>
#endif

#if !defined(__SUNPRO_CC) || ( defined(__SUNPRO_CC) && (__SUNPRO_CC < 0x510) )
extern "C"
{
#endif
  /* defined in Debug.cpp */
  void ( *oldTerminateHandler )( void );
  void ( *oldUnexpectedHandler )( void );
  void terminateHandler( void );
  void unexpectedHandler( void );
#if !defined(__SUNPRO_CC) || ( defined(__SUNPRO_CC) && (__SUNPRO_CC < 0x510) )
}
#endif

BEGIN_QR_NAMESPACE

#if !defined( INLINE_GETLOGGER )
INLINE Debug *Debug::getLogger( const Top *const /* aClient */, 
								const char *const /* aModule */, 
								const char *const /* aMethod */,
								const Index /* anOffset */ )
GET_LOGGER_BODY
#endif

INLINE Debug::Debug()
{
  oldTerminateHandler = set_terminate( terminateHandler );
  oldUnexpectedHandler = set_unexpected( unexpectedHandler );
  totalMessagesLogged = 0;

}

INLINE void Debug::log( const char *const aMessage, ... )
{
  LOCK_INSTANCE;
  
  va_list args;

  va_start( args, aMessage );
  PLAF -> rawErrorPrintf
	( "%s[%s] ", PLAF -> getNL(), PLAF -> getTimeStampString() );
#if defined( USE_THREADS )
  Thread *thisThread;

  thisThread = THR_SYSTEM -> getSelf();
  if( thisThread != NULL )
	{
	  if( thisThread -> isSystemThread() )
		{
		  PLAF -> rawErrorPrintf( "(*) " );
		}
	  else
		{
		  PLAF -> rawErrorPrintf( "(%li) ", thisThread -> getId() );
		}
	}
  else
	{
	  PLAF -> rawErrorPrintf( "(?!) " );
	}
#endif
  PLAF -> rawErrorVPrintf( aMessage, args );
  va_end(args);
}


INLINE void Debug::logObject( const Top *anObject,
					   String ( Top::*aMethod )() const )
{
  logObject( "%s", anObject, aMethod );
}

INLINE void Debug::logObject( const char *const aMessage,
					   const Top *anObject,
					   String ( Top::*aMethod )() const )
{
  LOCK_INSTANCE;

  if( anObject != nil )
	{
	  char *formatted;
  
	  formatted = ( anObject ->* aMethod )().getChars();
	  test_( formatted != NULL );
  
	  log( aMessage, formatted );
	  delete []formatted;
	}
  else
	{
	  log( aMessage, nilObjectLiteral );
	}
}

INLINE void Debug::logString( const char *const aMessage, String aString )
{
  LOCK_INSTANCE;
  char *formatted;
  
  formatted = aString.getChars();
  test_( formatted != NULL );
  
  log( aMessage, formatted );
  delete []formatted;
}

INLINE void Debug::panic( const char *const aMessage )
{
  PLAF -> 
	rawErrorPrintf( "A serious error `%s' occurred. Choosing suicide...",
					aMessage );

  if( shouldDropCore )
	{
	  PLAF -> suicide();
	}
  else if( attachDebuggerOnError )
	{
	  PLAF -> attachDebugger();
	}
  else
	{
	  PLAF -> exitImmediate( -1 );
	}
}

INLINE void Debug::dumpCore()
{
  PLAF -> suicide();
}

INLINE void Debug::assertion( boolean aCondition,
							  const char *const aMessage,
							  const char *const aConditionAsString,
							  const char *const aFunction,
							  const char *const aFileName,
							  const Index   aLineNo )
{
  if( !aCondition )
    {
      log( "Assertion `%s' (%s) failed in %s (%s:%li)",
		   aMessage, aConditionAsString, aFunction, aFileName, aLineNo );
	  if( Quercus::isEnterMonitorOnException() )
		{
		  monitor();
		}
      if( assertionFailsAreFatal )
		{
		  panic( "Assertion failed" );
		}
	  else if( attachDebuggerOnError )
		{
		  printStackTrace();
		  PLAF -> attachDebugger();
		}
    }
}

INLINE void Debug::testCondition( boolean aCondition,
								  const char *const aMessage,
								  const char *const aConditionAsString,
								  const char *const aFunction,
								  const char *const aFileName,
								  const Index   aLineNo )
{
  if( !aCondition )
	{
      log( "Condition `%s' (%s) not met in %s (%s:%li)",
		   aMessage, aConditionAsString, aFunction, aFileName, aLineNo );

	  printStackTrace();

	  if( Quercus::isEnterMonitorOnException() )
		{
		  monitor();
		}

	  if( attachDebuggerOnError )
		{
		  PLAF -> attachDebugger();
		}
	  else
		{
		  throw ( new InternalError( aMessage, null ) );
		}
	}
}

INLINE void Debug::preCondition( boolean aCondition,
								 const char *const aMessage,
								 const char *const aConditionAsString,
								 const char *const aFunction,
								 const char *const aFileName,
								 const Index   aLineNo )
{
  testCondition( aCondition, aMessage, aConditionAsString, 
				 aFunction, aFileName, aLineNo );
}

INLINE void Debug::postCondition( boolean aCondition,
								  const char *const aMessage,
								  const char *const aConditionAsString,
								  const char *const aFunction,
								  const char *const aFileName,
								  const Index   aLineNo )
{
  testCondition( aCondition, aMessage, aConditionAsString, 
				 aFunction, aFileName, aLineNo );
}

INLINE void Debug::exception( Exception *anEx )
{
  preC_( anEx != NULL );
  
  logString( "Exception description: %s", anEx -> getFullDescription() );
  logObject( "Backtrace: %s", anEx -> getBacktrace() );
}

INLINE void Debug::printStackTrace()
{
  Backtrace trace;

  trace.fill();
  logObject( "Backtrace: %s", &trace );
}

END_QR_NAMESPACE

#if defined( USE_THREADS )
#include "LinkManager.hpp"

BEGIN_QR_NAMESPACE

Mutex *Debug::getMutex() const
{
  /* Use pthread_once! XXX */
  if( mutex == ( Mutex * ) NULL )
	{
	  MUTATE_MEMBER( mutex, Debug ) = THR_SYSTEM -> recMutex();
	  OREG( ( const Mutex * ) mutex );
	}
  return mutex;
}

END_QR_NAMESPACE

#endif

#if defined(_INLINE)
#include "../src/String.ipp"
#endif

/*
 * $Log: Debug.ipp,v $
 * Revision 1.2  2000/08/26 13:48:57  philogelos
 * new parameters added to the ::getLogger(). Hopefully will evolve into
 * per-module controllable debug settings
 *
 * Revision 1.1.1.1  2000/07/19 16:40:35  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.4  2000/04/09 12:00:48  god
 * CVS Log keyword correction finished
 *
 * Revision 1.3  2000/04/09 11:29:38  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.2  2000/04/05 17:19:41  god
 * Dynamic modules, askUser (+readline) dlsym/dladdr-based Backtrace
 *
 * Revision 1.1.1.1  2000/04/01 14:07:29  god
 * Imported sources
 *
 * Revision 1.5  1999/05/22 13:00:28  philogelos
 * Merging sources back from SPARC
 *
 * Revision 1.4  1999/03/03 20:43:27  philogelos
 * Switch to vararg-style argument passing
 *
 * Revision 1.3  1999/03/03 19:09:26  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.2  1999/02/28 15:46:48  philogelos
 * Tuned for inlines. Copyright updated.
 *
 * Revision 1.1.1.1  1998/11/25 20:11:01  philogelos
 * Quercus Robusta
 *
 * Revision 1.1  1998/07/09 09:30:36  philogelos
 * new files added to the repository
 * */

/* __DEBUG_IPP__ */
#endif
