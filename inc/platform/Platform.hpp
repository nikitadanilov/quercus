// -*-C++-*- 

/*  inc/platform/Platform.hpp  */

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



#ifndef __PLATFORM_HPP__
#define __PLATFORM_HPP__

/* $Id: Platform.hpp,v 1.1.1.1 2000/07/19 17:13:53 philogelos Exp $ */

#include "Top.hpp"
#include "defines.h"

#include <stdarg.h>

#define PLAF Platform::getInstance()

/**
   Class name of default Platofrm used by application.
   This class must be not abstract.

   Can be one of: POSIXPlatform, MinimalPlatform or Win32Platform.
*/
#define PLATFORM POSIXPlatform /* */
/* #define PLATFORM MinimalPlatform */
/* #define PLATFORM Win32Platform */

/**
   If this defined, library provides default implementation
   of system-dependent application entry-point (main, WinMain etc).
   This entry point does some initialisation and calls user-provided
   QRMain.

   @see QRMain
*/
#define WRAP_MAIN

#if defined( WANT_PLATFORM )
#if defined( PLATFORM )
#undef PLATFORM
#endif
#define PLATFORM WANT_PLATFORM
#endif

#if defined( WANT_WRAP_MAIN )
#define WRAP_MAIN
#elif defined( UNWANT_WRAP_MAIN )
#if defined( WRAP_MAIN )
#undef WRAP_MAIN
#endif
#endif


BEGIN_QR_NAMESPACE

/**
   Interface to platform-dependent functions.

   @author Philogelos
   @created
*/
interface Platform : public virtual Top
{
  /**
	 Sub-classes should override this with method
	 implementing ANSIC sprintf() functionality.
  */
 public: virtual void sprintf( char *s, const char * format, /* args */ ... ) 
		   PRINTF_ALIKE( 3, 4 ) = 0;

  /**
	 Sub-classes should override this with method
	 implementing ANSIC vsprintf() functionality.
  */
 public: virtual void vsprintf( char *s, const char *format, va_list raw ) = 0;

  /**
	 Sub-classes should override this with method
	 returning the number of characters that would be output
	 by the call to printf( format, args... ).
  */
 public: virtual Index printfLength( const char * format, /* args */ ... ) 
		   PRINTF_ALIKE( 2, 3 ) = 0;

  /**
	 Sub-classes should override this with method
	 returning the number of characters that would be output
	 by the call to vprintf( format, raw ).
  */
 public: virtual Index vprintfLength( const char * format, va_list raw ) = 0;
 
  /**
	 Sub-classes should override this with method
	 formatting arguments like printf and making result
	 visible to user.

	 Possible implementation are: writing results to the file
	 with some predefined name, to the stderr, to the 
	 console (in Win32 sense) or all of the above.

	@see #rawErrorVPrintf
  */
 public: virtual void rawErrorPrintf( const char * format, /* args */ ... ) 
		   PRINTF_ALIKE( 2, 3 ) = 0;

 /**
	Same functionality as rawErrorPrintf, different interface.

	@see #rawErrorPrintf
 */
 public: virtual void rawErrorVPrintf( const char * format, va_list raw ) = 0;


 /**
	Rudimentary interactive facility.
 */
 public: virtual Index askUser( const char *caption,
							   const char *prompt, ... ) = 0;
 /**
	Returns static string describing platform-dependent
	error code.
 */
 public: virtual char *getErrorDescription( int errCode ) = 0;


 /**
	Exits the process. No cores, debuggers etc.
 */
 public: virtual void exitImmediate( long status ) = 0;

 /**
	Finish this process abnormally. Make some kind of information
	for post-mortem analysis available. E.g., drop core.
 */
 public: virtual void suicide() NORETURN = 0;

 /**
	Attach the debugger of choice to the calling process.
 */
 public: virtual void attachDebugger() = 0;

 public: virtual void setImageName( const char *aName ) = 0;
 public: virtual const char *getImageName() const = 0;
 
 /**
	Returns static string that should delimit lines of output
	on this platform. On UNIX it is "\n" on DOS "\r\n"
 */
 public: virtual char *getNL() const = 0;

 /**
	Returns string identifying current instant in time. 
	Should not be freed.
 */
 public: virtual char *getTimeStampString() = 0;


  /**
	 Sub-classes should override this with method
	 implementing ANSIC strcpy() functionality.
  */
 public: virtual char  *strcpy( char *dst, const char *src ) = 0;

  /**
	 Sub-classes should override this with method
	 implementing ANSIC strcmp() functionality.
  */
 public: virtual int    strcmp( const char *s1, const char *s2 ) = 0;

  /**
	 Sub-classes should override this with method
	 implementing ANSIC strlen() functionality.
  */
 public: virtual Index  strlen( const char *s ) = 0;

  /**
	 Sub-classes should override this with method
	 implementing ANSIC strcat() functionality.
  */
 public: virtual char  *strcat( char *dst, const char *src ) = 0;

  /**
	 Sub-classes should override this with method
	 implementing ANSIC strchr() functionality.
  */
 public: virtual char  *strchr( const char *s, int c ) = 0;

 /**
	Interface to strtol(3C). Throws InvalidArgument
	if value is too big (ERANGE), conversion failed (EINVAL) or
	endptr is not NULL and there are non-numeric characters 
	in the string.
 */
 public: virtual long   strtol( const char *str, char **endptr, int base ) = 0;



  /**
	 Sub-classes should override this with method
	 implementing ANSIC memcmp() functionality.
  */
 public: virtual int   memcmp( void *s1, const void *s2, Index n ) = 0;

  /**
	 Sub-classes should override this with method
	 implementing ANSIC memchr() functionality.
  */
 public: virtual void *memchr( const void *s, int c, Index n ) = 0;

  /**
	 Sub-classes should override this with method
	 implementing ANSIC memcpy() functionality.
  */
 public: virtual void *memcpy( void *s1, const void *s2, Index n ) = 0;

  /**
	 Sub-classes should override this with method
	 implementing ANSIC memset() functionality.
  */
 public: virtual void *memset( void *s, int c, Index n ) = 0;

 /**
	Allocates memory in fashion appropriate for this
	platform.

	@see #deallocateMemory
 */
 public: virtual void *allocateMemory( Index aSize ) = 0;

 /**
	Frees memory previously allocated with allocateMemory.

	@see #allocateMemory
 */
 public: virtual void  deallocateMemory( void *aPointer ) = 0;



 /**
	Allocate memory at bootstrap.
 */
 public: static void *allocateMemoryBootstrap( Index aSize );

 /**
	Deallocate memory at bootstrap.
 */
 public: static void  deallocateMemoryBootstrap( void *aPointer );


 public: static Platform *getInstance();
 public: static Platform *getInstanceNow();
 
 protected: static Platform *instance;
};

#if defined( WRAP_MAIN )
class List;

/**
   If WRAP_MAIN is defined this should be provided
   by user. This function will be called from
   library defined startup routine (main, WinMain etc.)
   with list of command line arguments.
*/
extern int QRMain( List *anArgs );
#endif

END_QR_NAMESPACE

/*
 * $Log: Platform.hpp,v $
 * Revision 1.1.1.1  2000/07/19 17:13:53  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.4  2000/04/09 12:00:47  god
 * CVS Log keyword correction finished
 *
 * Revision 1.3  2000/04/09 11:29:36  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.2  2000/04/05 17:19:33  god
 * Dynamic modules, askUser (+readline) dlsym/dladdr-based Backtrace
 *
 * Revision 1.1.1.1  2000/04/01 14:07:47  god
 * Imported sources
 * */

/* __PLATFORM_HPP__ */
#endif
