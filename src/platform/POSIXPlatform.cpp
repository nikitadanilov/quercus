// -*-C++-*- 

/*  src/platform/POSIXPlatform.cpp  */

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



/* $Id: POSIXPlatform.cpp,v 1.6 2002/03/09 15:26:08 philogelos Exp $ */
#if !defined(_INLINE)
static char cvsid[] = "@(#)$Id: POSIXPlatform.cpp,v 1.6 2002/03/09 15:26:08 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif

#include "platform/POSIXPlatform.hpp"

#if defined( USE_POSIX )

#include <sys/signal.h>

#include <sys/types.h>
#include <sys/time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include <sys/mman.h>

#include "exceptions/Errno.hpp"
#include "String.hpp"
#include "Debug.hpp"
#include "OGuard.hpp"

#if defined( USE_THREADS )
#include "platform/threads/PThread.hpp"
#endif

#if defined( USE_GETITIMER ) && defined( USE_CLOCK_GETTIME )
#error "Use either USE_GETITIMER or USE_CLOCK_GETTIME"
#endif

#if defined( USE_GETITIMER ) && defined( USE_CLOCK )
#error "Use either USE_GETITIMER or USE_CLOCK"
#endif

#if defined( USE_CLOCK ) && defined( USE_CLOCK_GETTIME )
#error "Use either USE_CLOCK or USE_CLOCK_GETTIME"
#endif

BEGIN_QR_NAMESPACE

extern "C" int kill( pid_t pid, int sig );
#if defined( USE_CLOCK_GETTIME )
extern "C" int clock_gettime( clockid_t clock_id, struct timespec *tp );
#endif

#if defined( USE_GETITIMER )
static long resetTimer()
{
  struct itimerval newCharge;
  struct itimerval value;

  test_( getitimer( ITIMER_REAL, &value ) == 0 );
  if( value.it_value.tv_sec < 1000000 )
	{
	  newCharge.it_interval.tv_sec = 100000000;
	  newCharge.it_interval.tv_usec = 0;
	  newCharge.it_value.tv_sec = 100000000;
	  newCharge.it_value.tv_usec = 0;
	  
	  test_( setitimer( ITIMER_REAL, &newCharge, NULL ) == 0 );
	  if( value.it_value.tv_sec != 0 )
		{
		  DLOG( "Microsecond timer was adjusted!" );
		}
	}
  return 1000000 - value.it_value.tv_usec - 1;
}
#endif

#if defined( USE_THREADS )
PSemaphore *POSIXPlatform::signalCatched = NULL;
Thread     *POSIXPlatform::signalWaiter = NULL;

void *POSIXPlatform::signalWaiterLoop( void * )
{
  DLOG( "Signal waiter started." );
  while( true )
	{
	  test_( signalCatched != NULL );
	  signalCatched -> dec(); /* wait for signal */
	  signalCatched -> inc();
	  DLOG( "Signal catched by waiter thread." );
	  Debug::getLogger() -> monitor();
	}
}
/* USE_THREADS */
#endif

#if defined(__SUNPRO_CC) && (__SUNPRO_CC >= 0x510)
extern "C" void panicHandler( int aSigNum );
#else
static
#endif

void panicHandler( int aSigNum )
{
#if defined( USE_THREADS )
  if( POSIXPlatform::signalCatched != NULL )
	{
	  POSIXPlatform::signalCatched -> inc();
	}
#endif
  DLOG( "Catched unexpected signal %i (pid: %li)", 
		aSigNum, ( long ) getpid() );
  while( true )
	{}
}

static void setSignalHandlerToPanic( int aSigNum )
{
  test_( signal( aSigNum, panicHandler ) != SIG_ERR );
}

POSIXPlatform::POSIXPlatform()
{
  setImageName( IMAGE_NAME );
  setSignalHandlerToPanic( SIGSEGV );
  setSignalHandlerToPanic( SIGBUS );
#if defined( USE_GETITIMER )
  resetTimer();
#endif
}

#if defined( USE_THREADS )
void POSIXPlatform::startSignalWaiterThread()
{
  if( signalCatched == NULL )
	{
	  signalCatched = new PSemaphore::PSemaphore( SHARE_SIGNAL_COUNTER, 0 );
	  signalCatched -> dontManage();
	}
  if( signalWaiter == NULL )
	{
	  signalWaiter = THR_SYSTEM -> getSelf(); /* to avoid infinite recursion */
	  signalWaiter = THR_FACTORY -> createFromFunc( &signalWaiterLoop, NULL );
	  TCAST( signalWaiter, Object ) -> dontManage();
	}
}
#endif

POSIXPlatform::~POSIXPlatform()
{}

int POSIXPlatform::fork() THROWS( Errno * )
{
  int result;

  ++callsNum;
  result = ::fork();
  if( result == -1 )
	{
	  throw new Errno( "fork()", null );
	}
  else
	{
	  return result;
	}
}

void POSIXPlatform::execl( const char *path, ... ) THROWS( Errno * )
{
  preC_( path != NULL );

  void **args;
  Index length;

  nullTerminatedVaListToArray( path, length, args );
  this -> execv( path, ( char ** ) args );
}

void POSIXPlatform::vexecl( const char *path, 
							va_list nullTerminatedArgvs, Index aLength ) 
  THROWS( Errno * )
{
  preC_( path != NULL );
  preC_( aLength > 0 );

  char **argv;

  argv = ( char ** ) stdargToArrayLength( nullTerminatedArgvs, aLength );
  test_( argv[ aLength - 1 ] == NULL );
  this -> execv( path, argv );
}

void POSIXPlatform::execv( const char *path, char *const argv[] ) THROWS( Errno * )
{
  preC_( path != NULL );

  ++callsNum;
  if( ::execv( path, argv ) == -1 )
	{
	  throw new Errno( "execv", null );
	}
}

void POSIXPlatform::execle( const char *path, ... ) THROWS( Errno * )
{
  preC_( path != NULL );

  va_list argvs;
  Index length;

  va_start( argvs, path );
  length = stdargLengthFence( argvs, NULL );
  va_end( argvs );

  va_start( argvs, path );
  this -> vexecle( path, argvs, length );
  va_end( argvs );
}

void POSIXPlatform::vexecle( const char *path, 
							 va_list nullTerminatedArgvsAndEnvp,
							 Index aLength ) THROWS( Errno * )
{
  preC_( path != NULL );
  preC_( aLength > 0 );

  char **argv;
  char **envp;

  argv = new char *[ aLength ];
  for( Index i = 0 ; i < aLength ; ++i )
	{
	  argv[ i ] = va_arg( nullTerminatedArgvsAndEnvp, char * );
	}
  test_( argv[ aLength - 1 ] == NULL );
  envp = va_arg( nullTerminatedArgvsAndEnvp, char ** );
  test_( envp != NULL );
  this -> execve( path, argv, envp );
}

void POSIXPlatform::execve( const char *path, 
							char *const argv[], 
							char *const envp[] ) THROWS( Errno * )
{
  preC_( path != NULL );

  ++callsNum;
  if( ::execve( path, argv, envp ) == -1 )
	{
	  throw new Errno( "execve", null );
	}
}

void POSIXPlatform::execlp( const char *file, ... ) THROWS( Errno * )
{
  preC_( file != NULL );

  void **args;
  Index length;

  nullTerminatedVaListToArray( file, length, args );
  this -> execvp( file, ( char ** ) args );
}

void POSIXPlatform::vexeclp( const char *file, 
							 va_list nullTerminatedArgvs, Index aLength )
  THROWS( Errno * )
{
  preC_( file != NULL );
  preC_( aLength > 0 );

  char **argv;

  argv = ( char ** ) stdargToArrayLength( nullTerminatedArgvs, aLength );
  test_( argv[ aLength - 1 ] == NULL );
  this -> execvp( file, argv );
}

void POSIXPlatform::execvp( const char *file, char *const argv[] ) 
  THROWS( Errno * )
{
  preC_( file != NULL );

  ++callsNum;
  if( ::execvp( file, argv ) == -1 )
	{
	  throw new Errno( "execvp", null );
	}
}

void POSIXPlatform::system( const char *aCmd ) THROWS( Errno * )
{
  preC_( aCmd != NULL );
  if( ::system( aCmd ) != 0 )
	{
	  throw new Errno( "system", null );
	}
}

pid_t POSIXPlatform::getPid() THROWS( Errno * )
{
  pid_t result;

  ++callsNum;
  result = ::getpid();
  if( result == -1 )
	{
	  throw new Errno( "getpid", null );
	}
  else
	{
	  return result;
	}
}

void POSIXPlatform::kill( pid_t aPid, int aSig ) THROWS( Errno * )
{
  ++callsNum;
  if( ::kill( aPid, aSig ) == -1 )
	{
	  throw new Errno( "kill", null );
	}
}

#if defined( __linux__ )
#define MMAP_ADDRESS_TYPE void *
#else
#define MMAP_ADDRESS_TYPE caddr_t
#endif

void *POSIXPlatform::mmap( void *anAddr, size_t aLen, 
						   int aProt, int aFlags,
						   int aFildes, off_t anOff ) THROWS( Errno * )
{
  void *result;

  result = ::mmap( ( MMAP_ADDRESS_TYPE ) anAddr, aLen, 
				   aProt, aFlags, aFildes, anOff );
  ++callsNum;
  if( result == MAP_FAILED )
	{
	  throw new Errno( "mmap", null );
	}
  else
	{
	  return result;
	}
}

void POSIXPlatform::munmap( void *addr, size_t len ) THROWS( Errno * )
{
  ++callsNum;
  if( ::munmap( ( MMAP_ADDRESS_TYPE ) addr, len ) == -1 )
	{
	  throw new Errno( "munmap", null );
	}
}

String POSIXPlatform::getCWD() THROWS( Errno * )
{
  char *buffer;
  Index length;

  ++callsNum;
  for( buffer = NULL, length = 60 ; ; length *= 2 )
	{
	  if( buffer != NULL )
		{
		  delete []buffer;
		}
	  buffer = new char[ length ];
	  if( getcwd( buffer, length ) == NULL )
		{
		  if( errno == ERANGE )
			{
			  continue;
			}
		  else
			{
			  throw new Errno( "getcwd", null );
			}
		}
	  else
		{
		  return buffer;
		}
	}
}

#if defined( USE_THREADS )

END_QR_NAMESPACE

extern unsigned short *_etext;
// extern "C" void profil( unsigned short *buff, unsigned int bufsiz,
//					    unsigned int offset, unsigned int scale );

BEGIN_QR_NAMESPACE

typedef struct
{
  String outFileTemplate;
  Index  secDelay;
  Index  nanDelay;
} ProfileTask;

extern int profil( unsigned short int *, size_t, size_t, unsigned int );

static void *profileThread( void *aTask )
{
  preC_( aTask != NULL );

  unsigned short *startAddress;
  unsigned short *endAddress;
  unsigned int    scale;
  unsigned int    bufSize;
  double          ratio;
  ProfileTask    *task;

  startAddress = 0;
  endAddress = _etext;

  scale = 0x1000;
  ratio = ( ( double ) scale ) / 0200000L;
  bufSize = ( unsigned ) ( ( endAddress - startAddress ) * ratio );
  task = ( ProfileTask * ) aTask;

  DLOG( "Starting profiling: [ %p .. %p ) to buffer: %i at ratio: %f",
		startAddress, endAddress, bufSize, ratio );

  for( Index tick = 0 ; ; ++tick )
	{
	  unsigned short *buffer;
	  char *fileName = NULL;
	  int fd;
  
	  buffer = new unsigned short[ bufSize + 1 ];
	  profil( buffer, bufSize, startAddress - ( unsigned short * ) NULL, scale );
	  THR_SYSTEM -> sleep( task -> secDelay, task -> nanDelay );
	  profil( buffer, 0, startAddress - ( unsigned short * ) NULL, 0 );
	  
	  fileName = task -> outFileTemplate.format( 1, tick ).getChars();
	  DLOG( "Profiling: writing tick %li to `%s'", tick, fileName );
	  fd = open( fileName, O_WRONLY | O_CREAT, 0700 );
	  if( fd == -1 )
		{
		  throw new Errno( String( "open: " ) + fileName, null );
		}
	  else
		{
		  ::write( fd, buffer, bufSize );
		  ::close( fd );
		  delete []buffer;
		}
	  delete []fileName;
	}
  delete []task;
  return NULL;
}

void POSIXPlatform::startProfilingThread( String anOutFilesTemplate )
{
  ProfileTask *task;

  task = new ProfileTask();
  task -> outFileTemplate = anOutFilesTemplate;
  task -> secDelay = 10;
  task -> nanDelay = 0;

  THR_FACTORY -> createFromFunc( profileThread, task );
}

/* USE_THREADS */
#endif

char *POSIXPlatform::getErrorDescription( int errCode )
{
  ++callsNum;
  return strerror( errCode );
}

void POSIXPlatform::exitImmediate( long status )
{
  ++callsNum;
  _exit( status );
}
  
void POSIXPlatform::suicide()
{
  ++callsNum;
  kill( getpid(), SIGABRT );
  while( true )
	{}
}

void POSIXPlatform::attachDebugger()
{
  int result;
  const char *errorMessage;
  boolean MelTheProgrammer;

  ++callsNum;
  errorMessage = "Fork failed in attempt to attach debugger";
  result = fork();
  if( result == 0 )
	{
	  char *pidBuffer;

	  pidBuffer = new char[ ( 3 * sizeof( pid_t ) ) + 1 ];
	  this -> sprintf( pidBuffer, "%li", ( long ) getppid() );
	  /* XXX how to get to the argv[0]? */
	  result = ::execlp
		( DEBUGGER_COMMAND, DEBUGGER_COMMAND, 
		  getImageName(), pidBuffer, NULL );
	  delete []pidBuffer;
	  errorMessage = "Exec failed in attempt to attach debugger";
	}
  if( result < 0 )
	{
	  rawErrorPrintf( errorMessage );
	  suicide();
	}
  /* you can set this from debugger to break out of loop */
  MelTheProgrammer = true;
  while( MelTheProgrammer )
	{}
}

void POSIXPlatform::setImageName( const char *aName )
{
  preC_( aName != NULL );
  
  imageName = aName;
}

const char *POSIXPlatform::getImageName() const
{
  return imageName;
}

char *POSIXPlatform::getTimeStampString()
{
#if defined( USE_GETTIMEOFDAY )
  struct timeval timeValue;
#else
  time_t instant;
#endif

#if defined( USE_CLOCK_GETTIME )
  struct timespec nanos;
#elif defined( USE_CLOCK )
  /* `calibrate' clock() */
  static clock_t startUpTime = 0;
  static boolean firstTime = true;
  if( firstTime )
	{
	  time( &instant );
	  do
		{}
	  while( time( NULL ) == instant );
	  startUpTime = clock();
	  firstTime = false;
	}
#endif
  static char buffer[ 40 ];

#if defined( USE_GETTIMEOFDAY )
  if( gettimeofday( &timeValue, NULL ) == -1 )
#else
  if( ( time( &instant ) == -1 )
#if defined( USE_CLOCK_GETTIME )
	  || ( clock_gettime( CLOCK_REALTIME, &nanos ) == -1 )
#endif
	  )
/* USE_GETTIMEOFDAY */
#endif
	{
	  strcpy( buffer, "UNKNOWN TIME" );
	}
  else
	{
	  struct tm *t = NULL;
	  /* XXX _r version  localtime_r( &instant, &t ); */
#if defined( USE_CLOCK_GETTIME )
	  t = localtime( &nanos.tv_sec );
#elif defined( USE_GETTIMEOFDAY )
	  /* time normalization code from One True Editor.
		 xemacs-20.4/src/systime.h:  #define EMACS_NORMALIZE_TIME(time)
	  */
	  while( timeValue.tv_usec >= 1000000 )
		{
		  timeValue.tv_usec -= 1000000;
		  timeValue.tv_sec++;
		}
	  while( timeValue.tv_usec < 0 )
		{
		  timeValue.tv_usec += 1000000;
		  timeValue.tv_sec--;
		}
	  t = localtime( &timeValue.tv_sec );
#else
	  t = localtime( &instant );
#endif
	  sprintf( buffer, "%4.4i/%2.2i/%2.2i %2.2i:%2.2i:%2.2i"
#if defined( USE_CLOCK_GETTIME )
			   ".%9.9li"
#elif defined( USE_GETITIMER )
			   ".%6.6li"
#elif defined( USE_CLOCK )
			   ".%6.6li"
#elif defined( USE_GETTIMEOFDAY )
			   ".%6.6li"
#endif
			   ,
			   t -> tm_year + 1900, t -> tm_mon + 1, 
			   t -> tm_mday, t -> tm_hour, t -> tm_min, 
			   t -> tm_sec,
#if defined( USE_CLOCK_GETTIME )
			   nanos.tv_nsec
#elif defined( USE_GETITIMER )
			   resetTimer()
#elif defined( USE_CLOCK )
			   ( clock() - startUpTime ) % CLOCKS_PER_SEC
#elif defined( USE_GETTIMEOFDAY )
			   timeValue.tv_usec
#else
			   0
#endif
			   );
	}
  return buffer;
}

char *POSIXPlatform::getNL() const
{
  return ( char * ) "\n";
}

void *POSIXPlatform::allocateMemoryBootstrapPOSIX( Index aSize )
{
  return allocateMemoryBootstrapANSI( aSize );
}

void  POSIXPlatform::deallocateMemoryBootstrapPOSIX( void *aPointer )
{
  deallocateMemoryBootstrapANSI( aPointer );
}

boolean POSIXPlatform::equals( const Top *anOther ) const
{
  return( DCAST( anOther, POSIXPlatform ) == this );
}

Top *POSIXPlatform::clone() const
{
  return ( Top * ) this;
}

String  POSIXPlatform::toString() const
{
  return Object::toString() + " calls: " + String( callsNum );
}

String  POSIXPlatform::getClassName() const
{
  return "POSIXPlatform";
}

#if defined( WRAP_MAIN )

END_QR_NAMESPACE

#include "exceptions/Exception.hpp"
#include "containers/lists/List.hpp"
#include "Backtrace.hpp"
#include "new-operator.hpp"
#include "LinkManager.hpp"
#include "OGuard.hpp"

#if defined( USE_NAMESPACE )
using QR::Top;
#endif

int main( int argc, char *argv[], char *[] )
{
  NS_PREFIX List *args;

  try
	{
	  int retCode;

	  NS_PREFIX Platform::getInstance() -> setImageName( argv[ 0 ] );
	  NS_PREFIX Backtrace::initBacktrace();

	  NS_PREFIX Top::initThreads();
	  NS_PREFIX operatorNewInitThreads();
#if defined( USE_THREADS )
	  TCAST( NS_PREFIX Platform::getInstance(), NS_PREFIX POSIXPlatform ) 
		-> startSignalWaiterThread();
#endif

	  args = new NS_PREFIX List();
	  NS_PREFIX LinkManager::reg( args, args );

	  for( int i = 0 ; i < argc ; ++i )
		{
		  // test_( argv[ i ] != NULL );
		  args -> append( new NS_PREFIX String( argv[ i ] ) );
		}
	  // test_( argv[ argc ] == NULL );

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

#if defined( TESTING )

boolean POSIXPlatform::tester( int ) const
{
  if( TCAST( PLAF, POSIXPlatform ) -> fork() == 0 )
	{
	  DLOG( "In child" );
	  TCAST( PLAF, POSIXPlatform ) -> 
		execl( "/bin/sh", "/bin/sh", "-i", NULL );
	}
  else
	{
	  DLOG( "In parent" );
	  THR_SYSTEM -> sleep( 10, 0 );
	}
  int dummy;
  TCAST( PLAF, POSIXPlatform ) -> munmap( &dummy, 0xffff );
  return true;
}

#endif

END_QR_NAMESPACE

#if defined(_INLINE)
#include "../src/Debug.ipp"
#include "../src/String.ipp"
#endif

/* USE_POSIX */
#endif

/*
 * $Log: POSIXPlatform.cpp,v $
 * Revision 1.6  2002/03/09 15:26:08  philogelos
 * fight bit rot
 *
 * Revision 1.5  2001/03/06 17:44:14  philogelos
 * correct namespace handling for main()
 *
 * Revision 1.4  2000/10/20 20:29:20  philogelos
 * Simplifications through using of NopThreads
 *
 * Revision 1.3  2000/09/21 18:01:28  philogelos
 * getCWD() added
 *
 * Revision 1.2  2000/08/30 12:33:22  philogelos
 * update THROWS to correspond to the actual throws
 *
 * Revision 1.1.1.1  2000/07/19 16:51:29  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.15  2000/04/29 15:02:38  god
 * _XOPEN_SOURCE explicit definition is now in platform-specific.h
 *
 * Revision 1.14  2000/04/22 19:47:34  god
 * credit to EMACS_NORMALIZE_TIME(time) given
 *
 * Revision 1.13  2000/04/22 19:26:30  god
 * USE_GETTIMEOFDAY added. fileName deleted in profile thread.
 *
 * Revision 1.12  2000/04/09 15:19:31  god
 * signal-waiter thread implemented (but doesn't work)
 *
 * Revision 1.11  2000/04/09 14:31:07  god
 * typo in CVS log corrected
 *
 * Revision 1.10  2000/04/09 12:44:07  god
 * _POSIX_SOURCE defined for kill in <signal.h>
 *
 * Revision 1.9  2000/04/09 12:00:49  god
 * CVS Log keyword correction finished
 *
 * Revision 1.8  2000/04/09 11:29:43  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.7  2000/04/07 17:16:54  god
 * increment semaphore in signal handler. Preliminary version of profil-based monitoring (it is ugly right now)
 *
 * Revision 1.6  2000/04/05 18:01:03  god
 * added semaphore to count catched signals (incremented in signal handler).
 *
 * Revision 1.5  2000/04/05 17:19:44  god
 * Dynamic modules, askUser (+readline) dlsym/dladdr-based Backtrace
 *
 * Revision 1.4  2000/04/05 15:01:19  god
 * ::system() added
 *
 * Revision 1.3  2000/04/05 12:58:57  god
 * print pid on signal
 *
 * Revision 1.2  2000/04/03 10:52:37  god
 * fork and exec?? family of functions added.
 *
 * Revision 1.1.1.1  2000/04/01 14:07:34  god
 * Imported sources
 * */
