// -*-C++-*- 

/*  src/platform/Win32Platform.cpp  */

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


/* $Id: Win32Platform.cpp,v 1.3 2000/10/20 20:29:20 philogelos Exp $ */

#include "platform/Win32Platform.hpp"

#if defined( USE_WIN32 )

#if !defined(_INLINE)
static char cvsid[] = "@(#)$Id: Win32Platform.cpp,v 1.3 2000/10/20 20:29:20 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif

#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include <process.h>
#include <conio.h>

#include "String.hpp"
#include "Debug.hpp"
#include "platform/threads/Thread.hpp"
#include "platform/threads/ThreadFactory.hpp"
#include "platform/threads/ThreadsSystem.hpp"
#include "platform/threads/MGuard.hpp"
#include "platform/threads/Semaphore.hpp"
#include "exceptions/Errno.hpp"

BEGIN_QR_NAMESPACE

static Mutex     *logMutex = NULL;

Win32Platform::Win32Platform()
{
  static char moduleName[ MODULE_NAME_LENGTH ];
  COORD size;


  ::GetModuleFileName( NULL, moduleName, MODULE_NAME_LENGTH );
  setImageName( moduleName );

  logMutex = THR_SYSTEM -> mutex();
  TCAST( logMutex, Object ) -> dontManage();

  size.X = CONSOLE_WIDTH;
  size.Y = CONSOLE_HEIGHT;

  AllocConsole();
  if( !SetConsoleScreenBufferSize( 
								  GetStdHandle( STD_OUTPUT_HANDLE ), size ) )
	{
	  DLOG
  		( "Cannot SetConsoleScreenBufferSize(): %s", 
  		  PLAF -> getErrorDescription( GetLastError() ) );
	}
}

Win32Platform::~Win32Platform()
{}

void Win32Platform::rawErrorVPrintf( const char * format, va_list raw ) 
{
  preC_( format != NULL );

  char *buffer;
  DWORD length;

  length = PLAF -> vprintfLength( format, raw );
  buffer = new char[ length + 1 ];
  PLAF -> vsprintf( buffer, format, raw );

  MGuard _lock( logMutex, this );

#if defined( __BORLANDC__ )
  DWORD dummy;
  
  WriteConsole( GetStdHandle( STD_ERROR_HANDLE ),
				buffer, PLAF -> strlen( buffer ),
				&dummy,
				NULL );
#else
  _cputs( buffer );
#endif
  delete []buffer;
}


char *Win32Platform::getErrorDescription( int errCode )
{
  LPVOID lpMsgBuf;
  static char errorMessage[ ERROR_MESSAGE_LENGTH + 1 ];
  Index retCode;

  ++callsNum;

  retCode = FormatMessage
	( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
	  NULL, errCode, MAKELANGID( LANG_NEUTRAL, SUBLANG_DEFAULT ),
	  ( LPTSTR ) &lpMsgBuf, 0, NULL );
  if( retCode > 0 )
	{
	  if( retCode > ERROR_MESSAGE_LENGTH )
		{
		  retCode = ERROR_MESSAGE_LENGTH;
		}
	  PLAF -> memcpy( errorMessage, ( char * ) lpMsgBuf, retCode );
	}
  else
	{
	  char *fallBack;

	  fallBack = "Error when formatting error message";
	  test_( PLAF -> strlen( fallBack ) < ERROR_MESSAGE_LENGTH );
	  PLAF -> strcpy( errorMessage, fallBack );
	  ::LocalFree( lpMsgBuf );
	}
  return errorMessage;
}

void Win32Platform::exitImmediate( long status )
{
  ++callsNum;
  _exit( ( UINT ) status );
}
  
void Win32Platform::suicide()
{
  ++callsNum;
  abort();
}

void Win32Platform::attachDebugger()
{
  static char systemCmd[ SYSTEM_CMD_LENGTH + 1 ];
  boolean MelTheProgrammer;

  ++callsNum;
  this -> sprintf( systemCmd, "%s %li", DEBUGGER_COMMAND,
#if defined( __BORLANDC__ )
				   getpid()
#else
				   _getpid()
#endif
				   );
  if( system( systemCmd ) == -1 )
	{
	  rawErrorPrintf( "Error when attaching debugger" );
	  suicide();
	}
  MelTheProgrammer = true;
  while( MelTheProgrammer )
	{}
}

void Win32Platform::setImageName( const char *aName )
{
  preC_( aName != NULL );
  
  imageName = aName;
}

const char *Win32Platform::getImageName() const
{
  return imageName;
}

char *Win32Platform::getTimeStampString()
{
  static char buffer[ 40 ];
  SYSTEMTIME instant;

  GetLocalTime( &instant );

  sprintf( buffer, "%4.4i/%2.2i/%2.2i %2.2i:%2.2i:%2.2i.%3.3i",
		   instant.wYear, instant.wMonth, instant.wDay,
		   instant.wHour, instant.wMinute, instant.wSecond,
		   instant.wMilliseconds );
  return buffer;
}

char *Win32Platform::getNL() const
{
  return "\r\n";
}

void *Win32Platform::allocateMemoryBootstrapWin32( Index aSize )
{
  return allocateMemoryBootstrapANSI( aSize );
}

void  Win32Platform::deallocateMemoryBootstrapWin32( void *aPointer )
{
  deallocateMemoryBootstrapANSI( aPointer );
}

boolean Win32Platform::equals( const Top *anOther ) const
{
  return( DCAST( anOther, Win32Platform ) == this );
}

Top *Win32Platform::clone() const
{
  return ( Top * ) this;
}

String  Win32Platform::toString() const
{
  return Object::toString() + " calls: " + String( callsNum );
}

String  Win32Platform::getClassName() const
{
  return "Win32Platform";
}

Win32Object::Win32Object( HANDLE handle )
{
  setHandle( handle );
}

Win32Object::~Win32Object() THROWS( Errno * )
{
  if( getHandle() != NULL )
	{
	  if( !CloseHandle( getHandle() )
#if !defined( __BORLANDC__ )
		  && !std::uncaught_exception()
#endif
		  )
		{
		  throw new Errno
			( String( "CloseHandle() in Win32Object::~Win32Object() " ) +
			  getClassName(), 
			  null, 
			  GetLastError() );
		}
	}
}

HANDLE Win32Object::getHandle() const
{
  return handle;
}

void Win32Object::setHandle( HANDLE aHandle )
{
  handle = aHandle;
}
		

#if defined( WRAP_MAIN )

END_QR_NAMESPACE

#include "exceptions/Exception.hpp"
#include "containers/lists/List.hpp"
#include "Backtrace.hpp"
#include "new-operator.hpp"
#include "LinkManager.hpp"
#include "OGuard.hpp"

int WINAPI ::WinMain( HINSTANCE /* hInstance */, 
				    HINSTANCE /* hPrevInstance */, 
					LPSTR /* lpCmdLine */, 
					int /* nCmdShow */ )
{
  NS_PREFIX List *args;

  try
	{
	  int retCode;

#if !defined( __BORLANDC__ )
	  NS_PREFIX Platform::getInstance() -> setImageName( __argv[ 0 ] );
#endif
	  NS_PREFIX Backtrace::initBacktrace();

	  NS_PREFIX Top::initThreads();
	  NS_PREFIX operatorNewInitThreads();

	  args = new NS_PREFIX List();
	  NS_PREFIX LinkManager::reg( args, args );

#if !defined( __BORLANDC__ )
	  for( int i = 0 ; i < __argc ; ++i )
		{
		  // test_( __argv[ i ] != NULL );
		  args -> append( new NS_PREFIX String( __argv[ i ] ) );
		}
	  // test_( __argv[ __argc ] == NULL );
#endif

	  retCode = NS_PREFIX QRMain( args );

	  NS_PREFIX LinkManager::free( args, args );
	  return retCode;
	}
  catch( NS_PREFIX Exception *anEx )
	{
	  NS_PREFIX OGuard _ex( anEx, anEx );
	  NS_PREFIX Debug::getLogger() -> exception( anEx );
	}
  catch( NS_PREFIX Throwable *thrown )
	{
	  NS_PREFIX DLOG( "Throwable catched" );
	}
  catch( ... )
	{
	  NS_PREFIX DLOG( "Unidentified exception catched" );
	}
  return 0;
}

BEGIN_QR_NAMESPACE
 
#endif

END_QR_NAMESPACE

#if defined(_INLINE)
#include "../src/Debug.ipp"
#include "../src/String.ipp"
#endif

/* USE_WIN32 */
#endif

/*
 * $Log: Win32Platform.cpp,v $
 * Revision 1.3  2000/10/20 20:29:20  philogelos
 * Simplifications through using of NopThreads
 *
 * Revision 1.2  2000/08/30 12:33:23  philogelos
 * update THROWS to correspond to the actual throws
 *
 * Revision 1.1.1.1  2000/07/19 16:51:33  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:43  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:34  god
 * Imported sources
*/
