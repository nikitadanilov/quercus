// -*- C++ -*-

/*  src/Object.cpp  */


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


/* $Id: Object.cpp,v 1.1.1.1 2000/07/19 16:41:43 philogelos Exp $ */
#if !defined(_INLINE)
static char cvsid[] = "@(#)$Id: Object.cpp,v 1.1.1.1 2000/07/19 16:41:43 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif


#include "Object.hpp"
#include "OGuard.hpp"
#include "String.hpp"
#include "Protector.hpp"
#include "Debug.hpp"
#include "MemoryMonitor.hpp"
#include "LinkManager.hpp"
#include "LifeTimeController.hpp"
#include "AeternalLifeController.hpp"

#include "exceptions/ShouldBeOverriden.hpp"

#if defined( GUARD_ADDREF )
#define PENTER   do \
   if( getProtector() != NULL ) \
	{ \
	  getProtector() -> enter( this ); \
	} \
   while( false )

#define PLEAVE  do \
   if( getProtector() != NULL ) \
	{ \
	  getProtector() -> leave( this ); \
	} \
   while( false )
#else

#define PENTER do {} while( false )
#define PLEAVE do {} while( false )

#endif

BEGIN_QR_NAMESPACE

Object::~Object()
{
  if( getLifeTimeController() == NIL )
	{
	  if( isRef() )
		{
		  DLOGOBJECT( "referenced: %s", this );
		}
	  preC( !isRef(), "Attempt to recycle referenced object" );
	}
  else
	{
	  getLifeTimeController() -> notifyOfDestroy( this );
	  setLifeTimeController( NIL ); 
	}

  setProtector( NIL );
}

const Object *Object::dontManage() const
{
  addRef();
  ( ( Object * ) this ) -> 
	setLifeTimeController( new AeternalLifeController() );
  return this;
}

boolean Object::equals( const Top *anOther ) const
{
  OGuard _other( anOther, this );
  return ( this == anOther );
}

Top *Object::clone() const THROWS( ShouldBeOverriden * )
{
  throw ( new ShouldBeOverriden( "Object::clone()", null ) );
  RET_THROW( NULL );
}

String  Object::toString() const
{
  return getClassName() + 
	String( " (@%lx:%li)" ).format( 1, ( Index ) this, getRefCount() ) + 
	": " + getString();
}

String  Object::getString() const
{
  return String();
}

String  Object::getClassName() const
{
#if defined( USE_TYPEID )
	return Top::getClassName(); /* XXX */
#else
  return "Object";
#endif
}

boolean Object::invariant() const
{
  return( ( this != null ) && ( getRefCount() >= 0 ) && equals( this ) );
}

LifeTimeController *Object::getLifeTimeController() const
{
  return ltController;
}

void Object::setLifeTimeController( LifeTimeController *aController )
{
  FMOVE( ltController, aController );
}

void Object::addRef() const
{
  preC_( getRefCount() >= 0 );
  if( getLifeTimeController() != NULL )
	{
	  getLifeTimeController() -> notifyOfAddRef( this );
	}
  PENTER;
  MUTATE_MEMBER( refCount, Object )++;
  PLEAVE;
}

void Object::delRef() const
{
  if( getLifeTimeController() != NULL )
	{
	  getLifeTimeController() -> notifyOfDelRef( this );
	}
  PENTER;
  --MUTATE_MEMBER( refCount, Object );
  PLEAVE;
  postC_( getRefCount() >= 0 );
}

Index Object::getRefCount() const
{
  return refCount;
}

boolean Object::isRef() const
{
  preC_( getRefCount() >= 0 );
  return ( getRefCount() > 0 );
}


Protector *Object::getProtector() const
{
  return protector;
}

void Object::setProtector( Protector *aProtector )
{
  FMOVE( protector, aProtector );
}

void Object::lock( const Top *anOwner ) const
{
  preC_( anOwner != nil );

  if( getProtector() != NIL )
 	{
 	  getProtector() -> enter( this );
 	}
  LinkManager::reg( anOwner, this );
}

void Object::unlock( const Top *anOwner ) const
{
  preC_( anOwner != nil );

  if( getProtector() != NIL )
 	{
 	  getProtector() -> leave( this );
 	}
  LinkManager::unreg( anOwner, this );
}

void Object::lockRead( const Top *anOwner ) const
{
  preC_( anOwner != nil );

  if( getProtector() != NIL )
 	{
 	  getProtector() -> enterRead( this );
 	}
  LinkManager::reg( anOwner, this );
}

boolean Object::isBeingDeleted() const
{
  return beingDeleted;
}

void Object::setBeingDeleted( boolean aFlag ) const
{
  MUTATE_MEMBER( beingDeleted, Object ) = aFlag;
}

#if defined( TESTING )
boolean Object::tester( int ) const
{
  Object *instance;

  instance = new Object();
  OGuard _instance( instance, this );
  return true;
}
#endif


#include "../src/Object.ipp"

END_QR_NAMESPACE

#if defined(_INLINE)
#include "../src/Debug.ipp"
#endif


#if defined(_INLINE)
#include "../src/String.ipp"
#endif

/*
 * $Log: Object.cpp,v $
 * Revision 1.1.1.1  2000/07/19 16:41:43  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.3  2000/04/29 14:56:40  god
 * readonly-locking added
 *
 * Revision 1.2  2000/04/09 11:29:39  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:29  god
 * Imported sources
 *
 * Revision 1.5  1999/05/22 13:00:30  philogelos
 * Merging sources back from SPARC
 *
 * Revision 1.4  1999/03/03 19:09:29  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.3  1999/02/28 15:52:03  philogelos
 * Tuned for inlines. ::dontManage() added, arguments guarded
 *
 * Revision 1.2  1998/12/01 16:18:38  philogelos
 * conditionally compile ::tester()
 *
 * Revision 1.1.1.1  1998/11/25 20:11:01  philogelos
 * Quercus Robusta
 *
 * Revision 1.4  1998/07/09 09:04:44  philogelos
 * custom new/delete added
 *
 * Revision 1.3  1998/07/07 14:29:58  philogelos
 * Memory leak in SUNWspro dynamic_cast fixed.
 *
 * Revision 1.2  1998/06/22 13:34:22  philogelos
 * ::getString() added
 *
 * Revision 1.1.1.1  1998/06/22 08:47:12  philogelos
 * First version under CVS
 *
 * Revision 1.1.1.1  1998/04/01 17:15:28  philogelos
 * first version under CVS
 * */
