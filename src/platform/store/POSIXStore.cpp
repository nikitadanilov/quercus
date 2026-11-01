// -*-C++-*- 

/*  src/platform/store/POSIXStore.cpp  */

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



/* $Id: POSIXStore.cpp,v 1.1 2000/09/21 16:46:04 philogelos Exp $ */
#if !defined( _INLINE )
static char cvsid[] = "@(#)$Id: POSIXStore.cpp,v 1.1 2000/09/21 16:46:04 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif

#include "platform/store/POSIXStore.hpp"
#include "platform/POSIXPlatform.hpp"
#include "store/StoreError.hpp"
#include "store/Storable.hpp"
#include "Debug.hpp"

#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>

BEGIN_QR_NAMESPACE

POSIXStore::POSIXStore( String aStartPath )
{
  if( aStartPath.getUNIChars()[ 0 ] != ( unichar ) '/' )
	{
	  startPath = TCAST( PLAF, POSIXPlatform ) -> getCWD() +
		"/" + aStartPath;
	}
  else
	{
	  startPath = aStartPath;
	}
  writer = new POSIXFieldWriter( this );
  //  reader = new POSIXFieldReader( this );
}

POSIXStore::~POSIXStore()
{}

StoringState *POSIXStore::init( StoreSession *aSession ) THROWS( StoreError * )
{
  preC_( aSession != NULL );

  String rootPath;

  rootPath = getStartPath();
  mkdir( rootPath );
  mkdir( rootPath + "/" + getRefTag() );
  write( open( rootPath + "/" + getVerTag() ), "???" );
  return rootPath.clone();
}

FieldWriter  *POSIXStore::getWriter( StoreSession *aSession )
{
  preC_( aSession != NULL );

  return *writer;
}

StoringState *POSIXStore::getState( String aName, 
									StoreSession *aSession,
									Storable *anObject ) THROWS( StoreError * )
{
  preC_( aSession != NULL );
  String subDir;

  subDir = getFullPath( aSession, aName );
  mkdir( subDir );
  write( open( subDir + "/" + getTypeTag() ), 
		 ( anObject != NULL ) ? 
		 anObject -> getClassName() : String::nullLiteral );
  return subDir.clone();
}

void POSIXStore::storeRef( StoreSession *aSession,
						   RefId anId, StoringState *aState, 
						   Storable *, String aName ) 
  THROWS( StoreError * )
{
  preC_( aSession != NULL );
  preC_( aState != NULL );

  String source;
  String target;

  source = getStartPath() + "/" + getRefTag() + "/" + String( anId );
  target = *TCAST( aState, String ) + "/" + getSubobjPrefix() + aName;
  if( symlink( target.getChars(), source.getChars() ) == -1 )
	{
	  throw new POSIXStoreError
		( String( "symlink failed: " ) + source + " -> " + target, NULL );
	}
}

String POSIXStore::getStartPath() const
{
  return startPath;
}

String  POSIXStore::getClassName() const
{
  return "POSIXStore";
}

int POSIXStore::open( String aName ) THROWS( StoreError * )
{
  int fd;

  fd = ::open( aName.getChars(), O_CREAT | O_EXCL | O_RDWR, 0700 );
  if( fd == -1 )
	{
	  throw new POSIXStoreError
		( aName + ": open failed", NULL );
	}
  return fd;
}

int POSIXStore::write( int fd, String aValue ) THROWS( StoreError * )
{
  preC_( fd >= 0 );

  for( Index todo = aValue.length() ; todo > 0 ; )
	{
	  int callResult;

	  callResult = ::write( fd, aValue.getChars() + aValue.length() - todo, 
							todo );
	  if( callResult == -1 )
		{
		  throw new POSIXStoreError
			( String( fd ) + ": write failed", NULL );
		}
	  else
		{
		  todo -= callResult;
		}
	}
}

void POSIXStore::mkdir( String aPath ) THROWS( StoreError * )
{
  if( ::mkdir( aPath.getChars(), 0700 ) == -1 )
	{
	  throw new POSIXStoreError( aPath + ": mkdir fails", NULL );
	}
}


String POSIXStore::getTypeTag() const
{
  return ".type";
}

String POSIXStore::getRefTag() const
{
  return ".refs";
}

String POSIXStore::getVerTag() const
{
  return ".ver";
}

String POSIXStore::getSubobjPrefix() const
{
  return "";
}

String POSIXStore::getStringPrefix() const
{
  return "\"";
}

String POSIXStore::getIndexPrefix() const
{
  return "=";
}

String POSIXStore::getBooleanPrefix() const
{
  return "?";
}

String POSIXStore::getRefPrefix() const
{
  return "@";
}

String POSIXStore::getPath( StoreSession *aSession )
{
  preC_( aSession != NULL );

  return *TCAST( aSession -> getCurrentState(), String );
}

String POSIXStore::getFullPath( StoreSession *aSession, String aName )
{
  preC_( aSession != NULL );

  return getPath( aSession ) + "/" + getSubobjPrefix() + aName;
}

POSIXFieldWriter::POSIXFieldWriter( POSIXStore *aStore )
{
  store = aStore;
}

void POSIXFieldWriter::storeString( StoreSession *aSession, 
									String aName, 
									String aValue ) THROWS( StoreError * )
{
  preC_( aSession != NULL );

  store -> write( store -> open( store -> getFullPath
								 ( aSession, 
								   store -> getStringPrefix() + aName ) ),
				  aValue );
}

void POSIXFieldWriter::storeIndex( StoreSession *aSession, 
								   String aName, 
								   Index aValue ) THROWS( StoreError * )
{
  preC_( aSession != NULL );

  store -> write( store -> open( store -> getFullPath
								 ( aSession, 
								   store -> getIndexPrefix() + aName ) ),
				  String( aValue ) );
}

void POSIXFieldWriter::storeBoolean( StoreSession *aSession, 
									 String aName, 
									 boolean aValue ) THROWS( StoreError * )
{
  preC_( aSession != NULL );

  store -> write( store -> open( store -> getFullPath
								 ( aSession, 
								   store -> getBooleanPrefix() + aName ) ),
				  String( aValue ? "t" : "f" ) );
}

void POSIXFieldWriter::storeRef( StoreSession *aSession, 
								 String aName, 
								 RefId anId ) THROWS( StoreError * )
{
  preC_( aSession != NULL );

  String source;
  String target;

  source = store -> getFullPath( aSession, aName );
  target = store -> getStartPath() + "/" + 
	store -> getRefTag() + "/" + String( anId );
  if( symlink( target.getChars(), source.getChars() ) == -1 )
	{
	  throw new POSIXStoreError
		( String( "symlink failed: " ) + source + " -> " + target, NULL );
	}
}

POSIXStoreError::POSIXStoreError( String aMessage, const Top *const aSource ) :
  StoreError( aMessage, aSource ),
  ExternalError( aMessage, aSource ),
  Exception( aMessage, aSource ),
  Errno( aMessage, aSource )
{}

String POSIXStoreError::getClassName() const
{
  return "POSIXStoreError";
}

String POSIXStoreError::getDescription() const
{
  return Errno::getDescription() + 
	": error during storing object into POSIX file-system";
}

END_QR_NAMESPACE

#if defined( _INLINE )
#include "../src/Debug.ipp"
#endif


/*
 * $Log: POSIXStore.cpp,v $
 * Revision 1.1  2000/09/21 16:46:04  philogelos
 * Persistency sub-system (first draft). Store only.
 *
 */
