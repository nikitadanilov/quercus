// -*-C++-*- 

/*  inc/Backtrace.hpp  */

/*
 * Author: Philogelos A. <Philogelos@yahoo.com>
 * Maintainer: Philogelos A.
 * Keywords: C++, library, containers
 *
 * Copyright (C) 1999 Philogelos A.
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



#ifndef __BACKTRACE_HPP__
#define __BACKTRACE_HPP__

/* $Id: Backtrace.hpp,v 1.1.1.1 2000/07/19 16:55:11 philogelos Exp $ */

#include "Object.hpp"
#include "defines.h"
#include "platform/threads/Thread.hpp"

BEGIN_QR_NAMESPACE

class List;
class DataWrapper;
class DumbDictionary;
class CArray;
class Mutex;

#define HAS_BFD
#define HAS_LIBERTY
// #define USE_DLADDR_DLSYM_FOR_BACKTRACE

#if defined( WANT_HAS_BFD )
#define HAS_BFD
#elif defined( UNWANT_HAS_BFD )
#if defined( HAS_BFD )
#undef HAS_BFD
#endif
#endif

#if defined( WANT_HAS_LIBERTY )
#define HAS_LIBERTY
#elif defined( UNWANT_HAS_LIBERTY )
#if defined( HAS_LIBERTY )
#undef HAS_LIBERTY
#endif
#endif

#if defined( WANT_USE_DLADDR_DLSYM_FOR_BACKTRACE )
#define USE_DLADDR_DLSYM_FOR_BACKTRACE
#elif defined( UNWANT_USE_DLADDR_DLSYM_FOR_BACKTRACE )
#if defined( USE_DLADDR_DLSYM_FOR_BACKTRACE )
#undef USE_DLADDR_DLSYM_FOR_BACKTRACE
#endif
#endif

#if defined( HAS_BFD )
#define CAN_LOAD_SYM_TABLE
#endif

#if defined( HAS_LIBERTY ) || defined( __SUNPRO_CC )
#define CAN_DEMANGLE
#endif

#if defined( __GNUC__ )
#define CAN_BACKTRACE
#endif

/**
   Implements some trivial run-time reflection.
   Instances of this class can be filled with stack backtrace,
   which can be printed or somehow examined later.

   Stack backtrace consists of frames. Each frame is just address.
   Also there are methods to resolve frame address to function name 
   and visa versa. This in effect allows you to call function 
   by it's name.

   Services provided depend upon specific features of GCC compiler
   (builtin_return_address) to obtain stack trace and GNU BFD library
   to resolve address to name. C++ demangling supported on GCC and 
   Solaris SUNWspro compiler.

   This class behavior will degrade gracefully if abovementioned 
   features not present, executable image is stripped of symbols info
   or was compiled with GCC option -fomit-frame-pointer.

   @author Philogelos
   @created
*/
class Backtrace : public virtual Object
{

  /**
	 Creates empty backtrace.
   */
public: Backtrace();

  /**
	 Destructor.
   */
public: virtual ~Backtrace();

  /**
	 Fills this object with current backtrace.
  */
public: virtual void fill();
  
  /**
	 Returns address of AFRAME frame in recorded stack.
  */
public: virtual void *getFrame( Index aFrame ) const;
  
  /**
	 True iff stack recording was truncated
	 (due to technical limitations).
  */
public: virtual boolean isTruncated() const;
  
  /**
	 Returns filled stack depth.
	 Frames [ 0 .. getDepth() ) are valid.

	 @see #isValid()
  */
public: virtual Index getDepth() const;
  
  /**
	 Sets address of given frame to given value.
	 This affects only backtrace object, not stack itself.

	 No checks on address is done. 
  */
public: virtual void setAddress( Index aFrame, void *anAddress );

  /**
	 True if given index is valid for this backtrace.

	 @see #getDepth()
  */
public: virtual boolean isValidFrame( Index aFrame ) const;
  
  /**
	 Returns list of stack frames, stored in backtrace
	 object by fill method. Each element of list is instance 
	 of DataWrapper with value set to frame address.

	 @see #fill()
	 @see DataWrapper
  */	 
public: virtual List *getFrames() const;
  
  /**
	 Returns given frame address within this backtrace.
   */
public: static void *getAddressAtFrame( Index aFrame );

  /**
	 This function (euristically tries to check whether
	 given address is the bottom of the stack.
  */
public: static boolean isInitialFrame( void *anAddress );

  /**
	 Resolves address to name of function it belongs to.
  */
public: static String getNameFor( void *anAddress );

  /**
	 Returns all information available about given address.
   */
public: static String getDescriptionFor( void *anAddress );

  /**
	 Demangles mangled C++ symbol name.
  */
public: static String demangle( String aMangled );

  /**
	 Returns initial address of symbol with given name.
  */
public: static void  *getAddressFor( String aName );

  /** 
	  This call initialises magic required by 
	  isInitialFrame() to work. Call this from main()!
	  Standard platform-dependent main provided when 
	  WRAP_MAIN is defined to call this.

	  @see #isInitialFrame()
	  @see WRAP_MAIN
   */
public: static void initBacktrace();
  
  /**
	 Returns backtrace representation with somehwat 
	 redundant info.
   */
public: virtual String  toString() const;

  /**
	 Returns backtrace representation suitable to print from 
	 exception handlers etc.
   */
public:  virtual String  getString() const;

  /**
	 Returns "Backtrace"
   */
public:  virtual String  getClassName() const;

protected: List *frames;
protected: boolean truncated;

#if defined( HAS_BFD )
protected: static boolean loadSymTableFor( const char *anImage );
  
protected: static boolean tableLoaded;
protected: static boolean wasBFDError;

protected: static CArray *addresses;
protected: static CArray *names;
#endif
      
protected: static void *crt0Address;

#if defined( USE_THREADS )
public: static void initThreadBacktrace();
protected: static void *threadStartAddress;
#endif

protected: static boolean initialised;
protected: static boolean recursion;

protected: static Mutex *getMutex();

protected: static Mutex *mutex;

  
#if defined( TESTING )
public: boolean tester( int aParam ) const;
#endif
};

END_QR_NAMESPACE


/*
 * $Log: Backtrace.hpp,v $
 * Revision 1.1.1.1  2000/07/19 16:55:11  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.4  2000/04/09 12:00:46  god
 * CVS Log keyword correction finished
 *
 * Revision 1.3  2000/04/09 11:29:16  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.2  2000/04/05 17:19:19  god
 * Dynamic modules, askUser (+readline) dlsym/dladdr-based Backtrace
 *
 * Revision 1.1.1.1  2000/04/01 14:07:39  god
 * Imported sources
 * */

/* __BACKTRACE_HPP__ */
#endif
