//-*-C++-*-

/*  inc/debug-macros.hpp  */


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


#ifndef __DEBUGMACROS_HPP__
#define __DEBUGMACROS_HPP__

/* $Id: debug-macros.hpp,v 1.1.1.1 2000/07/19 16:58:13 philogelos Exp $ */

/** Defined if compiling in debug mode 
	(with pre-post-condition checking etc. */
#define DEBUG

/** Define this if calling of pure virtual function
	should result in panic (and coredump).
*/
#define PURE_PANICS

/** Define this if calling of pure virtual function
	should result throwing of exception (RuntimeError).
*/
/* #define PURE_THROWS */

#define DROP_CORE_ON_PANIC false
#define ASSERTION_FAILS_ARE_FATAL false
#define ATTACH_DEBUGGER_ON_ERROR true

#define ENTER_MONITOR_ON_EXCEPTION

/* if this defined, Debug::getLogger() (by far the most 
   frequently called method) is inlined. */
#define INLINE_GETLOGGER



#if defined( WANT_DEBUG )
#define DEBUG
#elif defined( UNWANT_DEBUG )
#if defined( DEBUG )
#undef DEBUG
#endif
#endif


#if defined( WANT_PURE_PANICS )
#define PURE_PANICS
#elif defined( UNWANT_PURE_PANICS )
#if defined( PURE_PANICS )
#undef PURE_PANICS
#endif
#endif

#if defined( WANT_PURE_THROWS )
#define PURE_THROWS
#elif defined( UNWANT_PURE_THROWS )
#if defined( PURE_THROWS )
#undef PURE_THROWS
#endif
#endif

#if defined( WANT_DROP_CORE_ON_PANIC )
#define DROP_CORE_ON_PANIC true
#elif defined( UNWANT_DROP_CORE_ON_PANIC )
#define DROP_CORE_ON_PANIC false
#endif

#if defined( WANT_ASSERTION_FAILS_ARE_FATAL )
#define ASSERTION_FAILS_ARE_FATAL true
#elif defined( UNWANT_ASSERTION_FAILS_ARE_FATAL )
#define ASSERTION_FAILS_ARE_FATAL false
#endif

#if defined( WANT_ATTACH_DEBUGGER_ON_ERROR )
#define ATTACH_DEBUGGER_ON_ERROR true
#elif defined( UNWANT_ATTACH_DEBUGGER_ON_ERROR )
#define ATTACH_DEBUGGER_ON_ERROR false
#endif

#if defined( WANT_INLINE_GETLOGGER )
#define INLINE_GETLOGGER
#elif defined( UNWANT_INLINE_GETLOGGER )
#if defined( INLINE_GETLOGGER )
#undef INLINE_GETLOGGER
#endif
#endif

#if defined( WANT_ENTER_MONITOR_ON_EXCEPTION )
#define ENTER_MONITOR_ON_EXCEPTION
#elif defined( UNWANT_ENTER_MONITOR_ON_EXCEPTION )
#if defined( ENTER_MONITOR_ON_EXCEPTION )
#undef ENTER_MONITOR_ON_EXCEPTION
#endif
#endif

#if defined( DEBUG )

#if defined( __GNUC__ )
#define __functionName __PRETTY_FUNCTION__
#else
#define __functionName ""
#endif

#if defined( __STDC__ )

/** STDC Assertions.*/
#define	__CALL_IT( EX, MESSAGE, METHOD ) \
        Debug::getLogger() -> METHOD \
             ( ( EX ), MESSAGE, #EX, __functionName, debugFileId, __LINE__ )
#define	__CALL_IT_FILE( EX, MESSAGE, METHOD ) \
        Debug::getLogger() -> METHOD \
             ( ( EX ), MESSAGE, #EX, __functionName, __FILE__, __LINE__ )
#else

/** Non-STDC Assertions.*/
#define	__CALL_IT( EX, MESSAGE, METHOD ) \
        Debug::getLogger() -> METHOD \
             ( ( EX ), MESSAGE, "EX", __functionName, debugFileId, __LINE__ )
#define	__CALL_IT_FILE( EX, MESSAGE, METHOD ) \
        Debug::getLogger() -> METHOD \
             ( ( EX ), MESSAGE, "EX", __functionName, __FILE__, __LINE__ )
/* __STDC__ */
#endif

/* if !DEBUG */
#else
#define __CALL_IT( EX, MESSAGE, METHOD )
#define	__CALL_IT_FILE( EX, MESSAGE, METHOD )
#endif

/** Call this to check condition that have to true be under ALL circumstances. */
#define sure( EX, MESSAGE ) if( !( EX ) ) __CALL_IT( EX, MESSAGE, assertion )
#define sureF( EX, MESSAGE ) if( !( EX ) ) __CALL_IT_FILE( EX, MESSAGE, assertion )

/** Call this to check condition that have to true be under normal circumstances. */
#define test( EX, MESSAGE ) if( !( EX ) ) __CALL_IT( EX, MESSAGE, testCondition )
#define testF( EX, MESSAGE ) if( !( EX ) ) __CALL_IT_FILE( EX, MESSAGE, testCondition )

/** Call this to check function/method pre-conditions. */
#define preC( EX, MESSAGE ) if( !( EX ) ) __CALL_IT( EX, MESSAGE, preCondition )
#define preCF( EX, MESSAGE ) if( !( EX ) ) __CALL_IT_FILE( EX, MESSAGE, preCondition )

/** Call this to check function/method post-conditions. */
#define postC( EX, MESSAGE ) if( !( EX ) ) __CALL_IT( EX, MESSAGE, postCondition )
#define postCF( EX, MESSAGE ) if( !( EX ) ) __CALL_IT_FILE( EX, MESSAGE, postCondition )

/** Call this to mark impossible situation (dead code). */
#define impossible( MESSAGE ) sure( false, MESSAGE )
#define impossibleF( MESSAGE ) sureF( false, MESSAGE )

#define	sure_( EX ) sure( EX, Debug::assertionFailedMessage )
#define impossible_ impossible( Debug::impossibleMessage )
#define test_( EX ) test( EX, Debug::conditionFailedMessage )
#define preC_( EX ) preC( EX, Debug::preConditionFailedMessage )
#define postC_( EX ) postC( EX, Debug::postConditionFailedMessage )

#define	sureF_( EX ) sureF( EX, Debug::assertionFailedMessage )
#define impossibleF_ impossibleF( Debug::impossibleMessage )
#define testF_( EX ) testF( EX, Debug::conditionFailedMessage )
#define preCF_( EX ) preCF( EX, Debug::preConditionFailedMessage )
#define postCF_( EX ) postCF( EX, Debug::postConditionFailedMessage )

#define DLOG       Debug::getLogger() -> log
#define DLOGSTRING Debug::getLogger() -> logString
#define DLOGOBJECT Debug::getLogger() -> logObject

/* __DEBUGMACROS_HPP__ */
#endif
