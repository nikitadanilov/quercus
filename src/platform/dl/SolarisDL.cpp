// -*-C++-*- 

/*  src/platform/dl/SolarisDL.cpp  */

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



/* $Id: SolarisDL.cpp,v 1.1.1.1 2000/07/19 16:51:34 philogelos Exp $ */
#if !defined( _INLINE )
static char cvsid[] = "@(#)$Id: SolarisDL.cpp,v 1.1.1.1 2000/07/19 16:51:34 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif

#if defined(__linux__)
/* for Dl_info and dladdr */
#define _GNU_SOURCE
#endif

#include "exceptions/Errno.hpp"
#include "exceptions/NoEntity.hpp"
#include "platform/dl/SolarisDL.hpp"
#include "platform/threads/MGuard.hpp"
#include "Debug.hpp"
#include "CRef.hpp"

#include <dlfcn.h>

BEGIN_QR_NAMESPACE

#if defined( USE_THREADS )
Mutex *SolarisDL::loadMutex = NULL;
#define LOCK_DL_MUTEX MGuard _( SolarisDL::loadMutex, this )
#else
#define LOCK_DL_MUTEX 
#endif

SolarisDL::SolarisDL( String aLibName ) :
  DynamicModule( aLibName )
{
  if( loadMutex == NULL )
	{
	  loadMutex = THR_SYSTEM -> mutex();
	  TCAST( loadMutex, Object ) -> dontManage();
	}
  handle = NULL;
  setPlatformName( convertPortableToPlatform( aLibName ) );
}

SolarisDL::~SolarisDL()
{}

void *SolarisDL::getSymbolAddress( String aSymbol ) THROWS( NoEntity * )
{
  preC_( isLoaded() );
  
  void *result;
  char *symbolName;

  LOCK_DL_MUTEX;

  symbolName = aSymbol.getChars();
  result = ::dlsym( handle, symbolName );
  delete []symbolName;
  if( result == NULL )
	{
	  char *error;

	  error = dlerror();
	  if( error == NULL )
		{
		  return NULL;
		}
	  else
		{
		  throw new NoEntity( String( "dlsym: " ) + String( error ),
							  aSymbol.clone() );
		}
	}
  else
	{
	  return result;
	}
}

String SolarisDL::convertPortableToPlatform( String aName ) const
{
  return String( "lib" ) + aName + String( ".so" );
}

void SolarisDL::platformLoad() THROWS( Errno * )
{
  char *libName;

  libName = getPlatformName().getChars();
  handle = dlopen( libName, RTLD_NOW | RTLD_GLOBAL );
  delete []libName;
  if( handle == NULL )
	{
	  char *error;

	  error = dlerror();
	  throw new Errno( String( "dlopen: " ) + 
					   String( ( error != NULL ) ? error :
							   "undefined dlerror()" ),
					   getPlatformName().clone() );
	}
  loaded = true;
}

void SolarisDL::platformUnload() THROWS( Errno * )
{
  if( dlclose( handle ) != 0 )
	{
	  char *error;

	  error = dlerror();
	  throw new Errno( String( "dlclose: " ) + 
					   String( ( error != NULL ) ? 
							   error : "undefined dlerror()" ),
					   getPlatformName().clone() );
	}
}

String  SolarisDL::getClassName() const
{
  return "SolarisDL";
}

#if defined( TESTING )
boolean SolarisDL::tester( int ) const
{
  CRef< SolarisDL > libc( new SolarisDL( "c" ) );

  libc -> load();
  DLOG( "fork address: 0x%p", libc -> getSymbolAddress( "fork" ) );
  return true;
}
#endif

END_QR_NAMESPACE

#if defined( _INLINE )
#include "../src/Debug.ipp"
#endif


/*
 * $Log: SolarisDL.cpp,v $
 * Revision 1.1.1.1  2000/07/19 16:51:34  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.3  2000/04/09 12:00:49  god
 * CVS Log keyword correction finished
 *
 * Revision 1.2  2000/04/09 11:29:43  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1  2000/04/07 18:02:55  god
 * Added
 *
 * Revision 1.1  2000/04/05 10:12:56  god
 * Initial revision
 * */
