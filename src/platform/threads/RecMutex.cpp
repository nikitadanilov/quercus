// -*-C++-*- 

/*  src/platform/threads/RecMutex.cpp  */

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



/* $Id: RecMutex.cpp,v 1.2 2001/03/06 17:38:34 philogelos Exp $ */
#if !defined(_INLINE)
static char cvsid[] = "@(#)$Id: RecMutex.cpp,v 1.2 2001/03/06 17:38:34 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif

#include "platform/threads/RecMutex.hpp"
#include "platform/threads/MGuard.hpp"
#include "LinkManager.hpp"
#include "String.hpp"
#include "Debug.hpp"

BEGIN_QR_NAMESPACE

RecMutex::RecMutex()
{
  init( THR_SYSTEM -> condition() );
}

RecMutex::RecMutex( CondVar *aCondVar )
{
  init( aCondVar );
}

RecMutex::~RecMutex()
{
  test( ( count == 0 ) && ( thread == NULL ),
		"RecMutex::~RecMutex(): in use!" );
  FDONE( guardian );
  FDONE( condVar );
}


void RecMutex::enter( const Top * )
{
#if !defined( SOLARIS_MGUARD_BUG )
  MGuard _protect( guardian, this );
#else
  guardian -> enter();
  try
	{
#endif

	  Thread *thisThread;

	  thisThread = THR_SYSTEM -> getSelf();
	  
	  if( count == 0 )
		{
 		  test_( thread == NULL );
		  /* XXX cannot be called from the main thread!!! */
		}
	  else if( thread != thisThread )
		{
		  while( count != 0 )
			{
			  condVar -> wait();
			}
		}
	  thread = thisThread;
	  test_( thread != NULL );
	  ++count;
	  
#if defined( SOLARIS_MGUARD_BUG )
	}
  catch( ... )
	{
	  guardian -> leave();
	  throw;
	}
  guardian -> leave();
#endif
}

void RecMutex::leave( const Top * )
{
#if !defined( SOLARIS_MGUARD_BUG )
  MGuard _protect( guardian, this );
#else
  guardian -> enter();
  try
	{
#endif
	  test_( count > 0 );
	  test_( thread == THR_SYSTEM -> getSelf() );
	  --count;
	  if( count == 0 )
		{
		  thread = NULL;
		}
	  condVar -> signal();
#if defined( SOLARIS_MGUARD_BUG )
	}
  catch( ... )
	{
	  guardian -> leave();
	  throw;
	}
  guardian -> leave();
#endif
}

boolean RecMutex::tryEnter( const Top * )
{
  MGuard _protect( guardian, this );

  Thread *thisThread;

  thisThread = THR_SYSTEM -> getSelf();

  if( thread == thisThread )
	{
	  ++count;
	  return true;
	}
  else if( count == 0 )
	{
	  test_( thread == NULL );
	  ++count;
	  thread = thisThread; 
	  test_( thread != NULL );
	  return true;
	}
  else
	{
	  return false;
	}
}

#if defined( LOCKS_INFO )
/* XXX not done yet */
const void *RecMutex::holds() const
{
  return ( void * ) 1;
}

const void *RecMutex::trying() const
{
  return ( void * ) 2;
}
#endif

String  RecMutex::toString() const
{
  String result;

  result = Object::toString();
  result += String( " condVar: " ) + condVar -> toString();
  result += String( " count: " ) + String( count, 10 );
  result += String( " thread: " ) + ( ( thread == NULL ) ? 
									  String( "null" ) : thread -> toString() );
  return result;
}

String  RecMutex::getClassName() const
{
  return "RecMutex";
}

void RecMutex::init( CondVar *aCondVar )
{
  preC_( aCondVar != NULL );
  
  FNNINIT( condVar, aCondVar );

  count = 0;
  thread = NULL;

  FINIT( guardian, condVar -> getMutex() );
}

END_QR_NAMESPACE

#if defined(_INLINE)
#include "../src/Debug.ipp"
#endif


/*
 * $Log: RecMutex.cpp,v $
 * Revision 1.2  2001/03/06 17:38:34  philogelos
 * Support for LOCKS_INFO
 *
 * Revision 1.1.1.1  2000/07/19 16:52:02  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:44  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:35  god
 * Imported sources
*/
