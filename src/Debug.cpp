//-*-C++-*-

/*  src/Debug.cpp  */


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



/* $Id: Debug.cpp,v 1.2 2000/08/30 12:20:35 philogelos Exp $ */
#if !defined(_INLINE)
static char cvsid[] = "@(#)$Id: Debug.cpp,v 1.2 2000/08/30 12:20:35 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif


#include "DebugDialogue.hpp"
#include "Debug.hpp"
#include "defines.h"
#include "String.hpp"
#include "exceptions/InternalError.hpp"

BEGIN_QR_NAMESPACE

Debug  *Debug::logger = ( Debug * ) 0L;
boolean Debug::shouldDropCore = DROP_CORE_ON_PANIC;
boolean Debug::assertionFailsAreFatal = ASSERTION_FAILS_ARE_FATAL;
boolean Debug::attachDebuggerOnError = ATTACH_DEBUGGER_ON_ERROR;

const char * const Debug::assertionFailedMessage = "Assertion failed";
const char * const Debug::impossibleMessage = "Impossible";
const char * const Debug::conditionFailedMessage = "Condition doesn't met";
const char * const Debug::preConditionFailedMessage = "Pre-condition doesn't hold";
const char * const Debug::postConditionFailedMessage = "Post-condition doesn't hold";
const char * const Debug::nilObjectLiteral = "<nil-object>";

Debug::~Debug()
{}

void Debug::monitor() const
{
  DebugDialogue dialog;

  dialog.run();
}

String  Debug::getString() const
{
  String result;

  result = Object::getString() + 
	String( " totally %li messages logged, core on panic: %lB, "
			"core on assertion: %lB, "
			"debugger on panic: %lB" ).
	format( 1, totalMessagesLogged, shouldDropCore, 
			assertionFailsAreFatal, attachDebuggerOnError );
  return result;
}

String  Debug::getClassName() const
{
  return "Debug";
}

#if defined( PURE_PANICS ) && defined( PURE_THROWS )
#error Only one of PURE_PANICS and PURE_THROWS may be defined.
#endif

extern "C"
{

#if defined( __GNUC__ )

  static const char *pureMethodMessage = "Pure virtual method called";
  void __pure_virtual()
  {
#if defined( PURE_PANICS )
	Debug::getLogger() -> panic( pureMethodMessage );
#elif defined( PURE_THROWS )
	throw new RuntimeError( pureMethodMessage, null );
#endif
  }

  /* GNUC */
#endif

  void terminateHandler()
  {
	Debug::getLogger() -> panic( "terminateHandler() called." );
  }

  void unexpectedHandler()
  {
	Debug::getLogger() -> panic( "unexpectedHandler() called." );
  }
}

END_QR_NAMESPACE

#include "../src/Debug.ipp"


#if defined(_INLINE)
#include "../src/String.ipp"
#endif

/*
 * $Log: Debug.cpp,v $
 * Revision 1.2  2000/08/30 12:20:35  philogelos
 * THROWS clauses updates to correspond to the real throws.
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
 * Revision 1.2  2000/04/05 17:19:40  god
 * Dynamic modules, askUser (+readline) dlsym/dladdr-based Backtrace
 *
 * Revision 1.1.1.1  2000/04/01 14:07:28  god
 * Imported sources
 *
 * Revision 1.3  1999/03/03 19:09:26  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.2  1999/02/28 15:46:02  philogelos
 * Tuned for inlines. ::toString() prettyfied
 *
 * Revision 1.1.1.1  1998/11/25 20:11:01  philogelos
 * Quercus Robusta
 *
 * Revision 1.5  1998/07/09 09:04:44  philogelos
 * custom new/delete added
 *
 * Revision 1.4  1998/07/07 14:29:58  philogelos
 * Memory leak in SUNWspro dynamic_cast fixed.
 *
 * Revision 1.3  1998/06/23 07:26:12  philogelos
 * ::logObject() methods added
 *
 * Revision 1.2  1998/06/22 18:12:59  philogelos
 * Enumerations and containers added
 *
 * Revision 1.1.1.1  1998/06/22 08:47:12  philogelos
 * First version under CVS
 *
 * Revision 1.1.1.1  1998/04/01 17:15:29  philogelos
 * first version under CVS
 * */
