// -*-C++-*- 

/*  src/Backtrace.cpp  */

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



/* $Id: Backtrace.cpp,v 1.4 2001/03/06 17:40:59 philogelos Exp $ */
#if !defined(_INLINE)
static char cvsid[] = "@(#)$Id: Backtrace.cpp,v 1.4 2001/03/06 17:40:59 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif

#if defined(__linux__)
/* for Dl_info and dladdr */
#define _GNU_SOURCE
#endif

#include "Debug.hpp"
#include "OGuard.hpp"
#include "Backtrace.hpp"
#include "StringBuffer.hpp"
#include "LinkManager.hpp"
#include "DataWrapper.hpp"
#include "containers/Pair.hpp"
#include "platform/Platform.hpp"
#include "containers/lists/List.hpp"
#include "containers/dicts/DumbDictionary.hpp"
#include "platform/threads/ThreadsSystem.hpp"

#if defined( USE_DLADDR_DLSYM_FOR_BACKTRACE )
#define _GNU_SOURCE
#define __USE_GNU
#undef _DLFCN_H
#include <dlfcn.h>
#undef _GNU_SOURCE
#undef __USE_GNU
#endif

#include <stdlib.h> /* for qsort of sorts and free */

#if defined( HAS_BFD )

/* BFD uses boolean typedef (well, quercus too) */
#define boolean bfd_boolean_kludge
#define TRUE_FALSE_ALREADY_DEFINED
#include <bfd.h>
#undef boolean

#endif

#if defined( __SUNPRO_CC )
#include <demangle.h>
#elif defined( HAS_LIBERTY )
/* from libiberty cplus-dem.c */
extern "C" char *cplus_demangle( const char *mangled, int options );
#define DMGL_NO_OPTS	0		/* For readability... */
#define DMGL_PARAMS	(1 << 0)	/* Include function args */
#define DMGL_ANSI	(1 << 1)	/* Include const, volatile, etc */
#define DMGL_JAVA	(1 << 2)	/* Demangle as Java rather than C++. */

#define DMGL_AUTO	(1 << 8)
#define DMGL_GNU	(1 << 9)
#define DMGL_LUCID	(1 << 10)
#define DMGL_ARM	(1 << 11)

#endif


#include "defines.h"
#include "platform/threads/ThreadFactory.hpp"
#include "platform/threads/Mutex.hpp"
#include "platform/threads/MGuard.hpp"

#define LOCK_BACKTRACE( back ) MGuard _( getMutex(), back )

BEGIN_QR_NAMESPACE

Backtrace::Backtrace()
{
  LOCK_BACKTRACE( this );
  test_( !recursion );
  
  recursion = true;

  FINIT( frames, new List() );
  truncated = false;

  recursion = false;
}

Backtrace::~Backtrace()
{
  FDONE( frames );
}

void Backtrace::fill()
{
  void *fp;
  Index frame = 0;
    
  LOCK_BACKTRACE( this );
  test_( !recursion );
  
  recursion = true;
  do
	{
	  fp = getAddressAtFrame( frame );
	  if( fp == NULL )
		{
		  truncated = true;
		  recursion = false;
		  return;
		}
	  else
		{
		  frames -> append( new DataWrapper( fp ) );
		  ++frame;
		}
	}
  while( ! isInitialFrame( fp ) ); 
  /*!( ( ( ( void * ) mainStartsHere ) <= fp ) && 
	( fp <= ( ( void * ) mainEndsHere ) ) ) ); */
  recursion = false;
}

void *Backtrace::getFrame( Index aFrame ) const
{
  preC_( isValidFrame( aFrame ) );
  
  return TCAST( getFrames() -> getAt( aFrame ), DataWrapper ) -> getValue();
}

boolean Backtrace::isTruncated() const
{
  return truncated;
}

Index Backtrace::getDepth() const
{
  return getFrames() -> getCardinality();
}

void Backtrace::setAddress( Index aFrame, void *anAddress )
{
  preC_( isValidFrame( aFrame ) );
  
  TCAST( getFrames() -> getAt( aFrame ), DataWrapper ) -> setValue( anAddress );
}

boolean Backtrace::isValidFrame( Index aFrame ) const
{
  return getFrames() -> isValidIndex( aFrame );
}
  
List *Backtrace::getFrames() const
{
  return frames;
}

boolean Backtrace::isInitialFrame( void *anAddress )
{
  return !initialised || ( anAddress == crt0Address )
#if defined( USE_THREADS )
	  ||
	( ( threadStartAddress != NIL ) && 
	  ( threadStartAddress == anAddress ) )
#endif
	;
}

void Backtrace::initBacktrace()
{
  if( ! initialised )
	{
	  /* __builtin_return_address( 0 ) == &initBacktrace()
		 __builtin_return_address( 1 ) == &main()
		 __builtin_return_address( 2 ) == somewhere in crt0 or whatever... */
	  crt0Address = getAddressAtFrame( 2 );
	  initialised = true;
	}
}
  
#if defined( USE_THREADS )
void Backtrace::initThreadBacktrace()
{
  threadStartAddress = getAddressAtFrame( 2 );
}

void *Backtrace::threadStartAddress = NIL;
#endif

String  Backtrace::toString() const
{
#if defined( CAN_BACKTRACE )
  Index depth;
  StringBuffer result( StringBuffer::defaultLength,
					   StringBuffer::defaultDelta );
  
  depth = 0;
  for( getFrames() -> toFirst() ; 
	   ! getFrames() -> atEnd() ; getFrames() -> next() )
	{
	  DataWrapper *frame;
	  char *symName;
	  
	  frame = DCAST( getFrames() -> getCurrentValue(), DataWrapper );
	  OGuard _frame( frame, this );
	  
	  symName = getDescriptionFor( frame -> getValue() ).getChars();
	  result.add( String( "[ %li ]: 0x%x (%s)\n" ).
				  sprintf( 1, depth++, frame -> getValue(), symName ).
				  getUNIChars() );
	  delete []symName;
	}
  if( truncated )
	{
	  result.add( String( "and more frames follows ..." ).getUNIChars() );
	}
  return result.asString();
#else
  return "No support for backtrace";
#endif
}

String  Backtrace::getString() const
{
  return Object::getString() + 
	getFrames() -> getString();
}

String  Backtrace::getClassName() const
{
  return "Backtrace";
}

#define RA( i ) __builtin_return_address( i )

void *Backtrace::getAddressAtFrame( Index aFrame )
{
  preC_( aFrame >= 0 );

#if defined( __GNUC__ )
  switch( aFrame )
	{
	case 0: return RA( 0 );
	case 1: return RA( 1 );
	case 2: return RA( 2 );
	case 3: return RA( 3 );
	case 4: return RA( 4 );
	case 5: return RA( 5 );
	case 6: return RA( 6 );
	case 7: return RA( 7 );
	case 8: return RA( 8 );
	case 9: return RA( 9 );
	case 10: return RA( 10 );
	case 11: return RA( 11 );
	case 12: return RA( 12 );
	case 13: return RA( 13 );
	case 14: return RA( 14 );
	case 15: return RA( 15 );
	case 16: return RA( 16 );
	case 17: return RA( 17 );
	case 18: return RA( 18 );
	case 19: return RA( 19 );
	case 20: return RA( 20 );
	case 21: return RA( 21 );
	case 22: return RA( 22 );
	case 23: return RA( 23 );
	case 24: return RA( 24 );
	case 25: return RA( 25 );
	case 26: return RA( 26 );
	case 27: return RA( 27 );
	case 28: return RA( 28 );
	case 29: return RA( 29 );
	case 30: return RA( 30 );
	default: return ( void * ) NULL;
	}
#else
  /* XXX is there any (semi-)portable way to walk
	 through stack frames? */
  return ( void * ) NULL;
#endif
}

#undef RA

#if defined( HAS_BFD )
#if defined(__SUNPRO_CC) && (__SUNPRO_CC >= 0x510)
extern "C" int compare_by_address( const void *symb1, const void *symb2 );
#else
static 
#endif
int compare_by_address( const void *symb1, const void *symb2 )
{
  return( bfd_asymbol_value( *( asymbol ** ) symb1 ) - 
		  bfd_asymbol_value( *( asymbol ** ) symb2 ) );
}

boolean Backtrace::loadSymTableFor( const char *
#if defined( CAN_LOAD_SYM_TABLE )
									anImage 
#endif
									)
{
#if !defined( CAN_LOAD_SYM_TABLE )
  return false;
#else
#if !defined( HAS_BFD )
#error The only way supported of loading symbol table is through libbfd
#endif
  preC_( anImage != NULL );
  
  LOCK_BACKTRACE( nil );

  bfd *abfd;
  Index storage_needed = 0;
  asymbol **symbol_table = ( asymbol ** ) NULL;
  Index number_of_symbols;
  Index tableSize;
  Index i;
  Index j;
    
  test_( initialised );
  
  if( tableLoaded )
	{
	  return true;
	}
  if( wasBFDError )
	{
	  return false;
	}
    
  bfd_init();
  if( bfd_get_error() != bfd_error_no_error )
	{
	  bfd_perror( "bfd_init()" );
	  wasBFDError = true;
	  return false;
	}

  abfd = bfd_openr( anImage, "default" );
  if( bfd_get_error() != bfd_error_no_error )
	{
	  bfd_perror( "bfd_fdopenr()" );
	  wasBFDError = true;
	  return false;
	}
  if( ! bfd_check_format( abfd, bfd_object ) )
	{
	  bfd_perror( "bfd_check_format()" );
	  wasBFDError = true;
	  return false;
	}

  storage_needed = bfd_get_symtab_upper_bound( abfd );
     
  if( storage_needed < 0 )
	{
	  bfd_perror( "bfd_get_symtab_upper_bound(): storage_needed < 0" );
	  wasBFDError = true;
	  return false;
	}
  if( storage_needed == 0 ) 
	{
	  DLOG( "no symbols\n" );
	  wasBFDError = true;
	  return false;
	}
  symbol_table = new asymbol *[ storage_needed ];

  number_of_symbols = bfd_canonicalize_symtab( abfd, symbol_table );
  if( number_of_symbols < 0 )
	{
	  bfd_perror( "bfd_canonicalize_symtab()" );
	  delete []symbol_table;
	  wasBFDError = true;
	  return false;
	}
     
  qsort( symbol_table, number_of_symbols, sizeof symbol_table[ 0 ],
		 compare_by_address );

  tableSize = 0;
  for( i = 0 ; i < number_of_symbols ; ++i )
	{
	  /* to defeat strange entries on SPARC Solaris */
	  if( bfd_asymbol_bfd( symbol_table[ i ] ) == ( bfd * ) NIL )
		{
		  continue;
		}
	  /* unnamed sections and other garbage */
	  if( symbol_table[ i ] -> name[ 0 ] == ( char ) 0 )
		{
		  continue;
		}
	  ++tableSize;
	}
  
  addresses = new CArray( 0, tableSize );
  names = new CArray( 0, tableSize );

  j = 0;
  for( i = 0 ; i < number_of_symbols ; ++i )
	{
	  if( bfd_asymbol_bfd( symbol_table[ i ] ) == ( bfd * ) NIL )
		{
		  continue;
		}
	  if( symbol_table[ i ] -> name[ 0 ] == ( char ) 0 )
		{
		  continue;
		}
	  addresses -> setAt
		( j, new DataWrapper( ( void * ) bfd_asymbol_value
							  ( symbol_table[ i ] ) ) );
	  names -> setAt
		( j, new String( symbol_table[ i ] -> name ) );
	  ++j;
	}
  
  delete []symbol_table;
  if( ! bfd_close( abfd ) )
	{
	  bfd_perror( "bfd_close()" );
	  wasBFDError = true;
	  /* return true anyway */
	}
  
  tableLoaded = true;
  
  return true;
/* defined( CAN_LOAD_SYM_TABLE ) */
#endif
}

boolean Backtrace::wasBFDError = false;
boolean Backtrace::tableLoaded = false;
CArray *Backtrace::addresses = NULL;
CArray *Backtrace::names = NULL;

/* HAS_BFD */
#endif

String Backtrace::getDescriptionFor( void *anAddress )
{
  String result;
  boolean found;

  found = false;
#if defined( USE_DLADDR_DLSYM_FOR_BACKTRACE )
  Dl_info symbolInfo;

  if( dladdr( anAddress, &symbolInfo ) == 0 )
	{
	  result = "not mapped";
	}
  else 
	{
	  result = String( " in %s @ 0x%x" ).
		format( 1, symbolInfo.dli_fname, symbolInfo.dli_fbase );
	  if( symbolInfo.dli_sname != NULL )
		{
		  result = demangle( symbolInfo.dli_sname ) + " : 0x" +
			String( ( Index ) symbolInfo.dli_saddr, 16 ) + result;
		  found = true;
		}
	  else
		{
		  result = String( "no dlinfo" ) + result;
		}
	}
#endif
  if( !found )
	{
	  result = result + " " + demangle( getNameFor( anAddress ) );
	}
  return result;
}

String Backtrace::getNameFor( void *anAddress )
{
#if defined( HAS_BFD )
  Index tableSize;
  Index low;
  Index high;
          
  test_( initialised );
  
  if( !loadSymTableFor( PLAF -> getImageName() ) )
	{
	  return "no symbol table";
	}
  test_( addresses != NULL );
  test_( names != NULL );
  
  tableSize = addresses -> getCardinality();
  test_( names -> getCardinality() == tableSize );
  
  low = addresses -> getLowBound();
  high = addresses -> getHighBound() - 1;

  if( TCAST( addresses -> getAt( high ), DataWrapper ) -> 
	  getValue() <= anAddress )
	{
	  return "address is too big";
	}
  if( TCAST( addresses -> getAt( low ), DataWrapper ) -> 
	  getValue() > anAddress )
	{
	  return "address is too small";
	}
  
  /* binary serach */
  while( high - low > 1 )
	{
	  Index median;
	  
	  median = ( high + low ) / 2;
	  if( ( TCAST( addresses -> getAt( median ), DataWrapper ) -> 
			getValue() ) > anAddress )
		{
		  high = median;
		}
	  else
		{
		  low = median;
		}
	  test_( high > low );
 	}
  test_( ( high == low + 1 ) &&
		 ( TCAST( addresses -> getAt( low ), DataWrapper ) -> 
		   getValue() <= anAddress ) &&
		 ( anAddress < TCAST( addresses -> getAt( high ), DataWrapper ) -> 
		   getValue() ) );
  return *TCAST( names -> getAt( low ), String );

/* HAS_BFD */
#elif defined( USE_DLADDR_DLSYM_FOR_BACKTRACE )
  Dl_info symbolInfo;

  if( dladdr( anAddress, &symbolInfo ) == 0 )
	{
	  return "address is not mapped";
	}
  else if( symbolInfo.dli_sname != NULL )
	{
	  return symbolInfo.dli_sname;
	}
  else
	{
	  return "address not found";
	}
#else
  return "no support for run-time symbol resolution";
#endif
}

String Backtrace::demangle( String aMangled )
{
#if defined( CAN_DEMANGLE )
#if defined( __GNUC__ )
  char *mangledChars;
  char *demangled;
  
  LOCK_BACKTRACE( nil );

  mangledChars = aMangled.getChars();
  demangled = cplus_demangle( mangledChars, 
							  DMGL_ANSI | DMGL_PARAMS | DMGL_AUTO );
  delete []mangledChars;
  if( demangled == NULL )
	{
	  return aMangled;
	}
  else
	{
	  String result;
	  
	  result = String( demangled, false );
	  ::free( demangled ); 	  /* XXX heck! */
	  return result;
	}
#elif defined( __SUNPRO_CC )
  char *mangled;
  char *demangled;
  Index size;
  
  mangled = aMangled.getChars();
  demangled = NIL;
  size = aMangled.length();
  do
	{
	  if( demangled != NULL )
		{
		  delete []demangled;
		}
	  size *=2;
	  demangled = new char[ size + 1 ];
	}
  while( cplus_demangle( mangled, demangled, size ) == DEMANGLE_ESPACE );
  delete []mangled;
  return String( demangled, true );
#else
#error liberty or SUNWspro is required to demangle
#endif
  return aMangled;
#endif
  return String();
}

void  *Backtrace::getAddressFor( String aName )
{
#if defined( USE_DLADDR_DLSYM_FOR_BACKTRACE )
  char *symbol;
  void *result;

  symbol = aName.getChars();
  result = dlsym( RTLD_DEFAULT, symbol );
  delete []symbol;
  return result;
#else
  Index tableSize;
          
  test_( initialised );
  
  if( !loadSymTableFor( PLAF -> getImageName() ) )
	{
	  return ( void *) NULL;
	}
  test_( addresses != ( CArray * ) NULL );
  test_( names != ( CArray * ) NULL );
  
  tableSize = addresses -> getCardinality();
  test_( names -> getCardinality() == tableSize );
  
  for( Index i = 0 ; i < tableSize ; ++i )
	{
	  if( aName.equals( names -> getAt( i ) ) )
		{
		  return TCAST( addresses -> getAt( i ), DataWrapper ) -> getValue();
		}
	}
  return ( void *) NULL;
#endif
}

Mutex *Backtrace::getMutex()
{
  if( mutex == ( Mutex * ) NULL )
	{
	  mutex = THR_SYSTEM -> mutex();
	  TCAST( mutex, Object ) -> dontManage();
	}
  return mutex;
}

void *Backtrace::crt0Address = ( void * ) NULL;
boolean Backtrace::initialised = false;
boolean Backtrace::recursion = false;

Mutex  *Backtrace::mutex = ( Mutex * ) NULL;

#if defined( TESTING )
boolean Backtrace::tester( int ) const
{
  {
	Backtrace *trace;
	
	trace = new Backtrace();
	OGuard _trace( trace, this );
	
	trace -> fill();
	//	loadSymTableFor( PLAF -> getImageName() );
	DLOGOBJECT( "trace: %s", trace );
	if( trace -> getDepth() > 0 )
	  {
		trace -> setAddress( 0, ( void *) NULL );
		trace -> setAddress( 1, ( void * ) 0xffffffff );
		trace -> setAddress( 2, ( void * ) 0x0005eeee );
		DLOGOBJECT( "modified trace: %s", trace );
	  }
	DLOG( "main() address: 0x%p", getAddressFor( "main" ) );

  }
  {
	/* const char *argv[] = { "/bin/sh", "-i", NULL }; */

	/* reflection in C, isn't it funny? 
	if( ( ( int (*)() ) getAddressFor( "fork" ) )() == 0 )
	  {
		( ( int (*)( const char *, const char *, ... ) ) getAddressFor( "execlp" ) )
		  ( "/bin/sh", "/bin/sh", "-i", NULL );
	  }
	*/
  }
  return true;
}
#endif

END_QR_NAMESPACE

#if defined(_INLINE)
#include "../src/Debug.ipp"
#endif


/*
 * $Log: Backtrace.cpp,v $
 * Revision 1.4  2001/03/06 17:40:59  philogelos
 * __USE_GNU for <dlfcn.h>; support of both dladdr abd libbfd at the same time
 *
 * Revision 1.3  2000/10/20 20:29:20  philogelos
 * Simplifications through using of NopThreads
 *
 * Revision 1.2  2000/09/21 18:03:18  philogelos
 * dladdr() support improved
 *
 * Revision 1.1.1.1  2000/07/19 16:40:28  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.5  2000/04/09 12:00:48  god
 * CVS Log keyword correction finished
 *
 * Revision 1.4  2000/04/09 11:29:38  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.3  2000/04/09 11:09:23  god
 * call ::demangle() in ::getDescriptionFor()
 *
 * Revision 1.2  2000/04/05 17:19:37  god
 * Dynamic modules, askUser (+readline) dlsym/dladdr-based Backtrace
 *
 * Revision 1.1.1.1  2000/04/01 14:07:29  god
 * Imported sources
 * */
