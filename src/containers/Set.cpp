// -*-C++-*- 

/*  src/containers/Set.cpp  */


/*
 * Author: Philogelos A. <Philogelos@yahoo.com>
 * Maintainer: Philogelos A.
 * Keywords: C++, library, containers
 *
 * Copyright (C) 1998, 1999 Philogelos A.
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


/* $Id: Set.cpp,v 1.1.1.1 2000/07/19 16:45:42 philogelos Exp $ */
#if !defined(_INLINE)
static char cvsid[] = "@(#)$Id: Set.cpp,v 1.1.1.1 2000/07/19 16:45:42 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif


#include "iter/enumerations/MappedEnumeration.hpp"
#include "containers/EmptyContainer.hpp"
#include "containers/lists/List.hpp"
#include "containers/Set.hpp"
#include "Debug.hpp"
#include "LinkManager.hpp"
#include "OGuard.hpp"
#include "PGuard.hpp"

BEGIN_QR_NAMESPACE

Set::Set()
{
  FINIT( core, new List() );
}

Set::~Set()
{
  FDONE( core );
}

MutablePositionEnumeration *Set::getMutableEnumeration() const
{
  /* isn-t-it-lispish-p */
  return MutablePositionEnumeration::createMutableFrom
	( TypedEnumeration< MutablePosition >::upcast
	  ( new MappedEnumeration( core -> getEnumeration(), 
							   new SetPositionMap( ( Set * ) this ) ) ) );
  /* this is just plain wrong and will break class invariants 
	 return( getCore() -> getMutableEnumeration() );
  */
}

Top   *Set::setValue( MutablePosition *aPosition, Top *aNewValue )
{
  preC_( aPosition != ( MutablePosition * ) NIL );
  preC_( aPosition -> isValid() );

  return( aPosition -> setValue( aNewValue ) );
}

Top   *Set::getValue( const Position *aPosition )
{
  preC_( aPosition != ( MutablePosition * ) NIL );
  preC_( aPosition -> isValid() );

  return( aPosition -> getValue() );
}

PositionFactory *Set::getDefaultPositionFactory() const
{
  return new SetPositionFactory( ( Set * ) this );
}

TypedEnumeration< RemovablePosition > *Set::getRemovable() const
{
  return TypedEnumeration< RemovablePosition >::upcast( getEnumeration() );
}

void Set::add( const Top *anObject )
{
  OGuard _this( this, this );
  OGuard _core( getCore(), this );
  OGuard _obj( anObject, this );

  MutablePosition *pos;

  pos = getNew( anObject );
  OGuard _pos( pos, this );
  OGuard _oldValue( pos -> setValue( ( Top * ) anObject ), 
					this );
}

Top *Set::getAny() const THROWS( EmptyContainer * )
{
  OGuard _this( this, this );
  OGuard _core( getCore(), this );
  if( isEmpty() )
	{
	  throw new EmptyContainer( "Set::getAny()", null );
	}
  return( getCore() -> car() );
}

Top *Set::getAndRemove() const
{
  OGuard _this( this, this );
  OGuard _core( getCore(), this );

  Top *element;

  element = getAny();
  OGuard _element( element, this );
  getCore() -> behead();
  return element;
}

boolean Set::isEmpty() const
{
  return( getCore() -> isEmpty() );
}

Index   Set::getCardinality() const
{
  return( getCore() -> getCardinality() );
}

Set::Set( List *aCore )
{
  FNNINIT( core, aCore );
}

Position *Set::unify( const Top *anObject ) const
{
  OGuard _this( this, this );
  OGuard _core( getCore(), this );

  return( getCore() -> find( anObject ) );
}

MutablePosition *Set::getNew( const Top *anObject ) const
{
  OGuard _this( this, this );
  OGuard _core( getCore(), this );
  OGuard _obj( anObject, this );
  Position *pos;
  MutablePosition *mpos;

  pos = unify( anObject );
  if( pos == ( Position * ) NIL )
	{
	  PositionFactory *factory;

	  factory = getCore() -> getDefaultPositionFactory();
	  OGuard _factory( factory, this );
	  pos = factory -> createPosition();
	}
  mpos = DCAST( pos, MutablePosition );
  PGuard _mpos( mpos, this );
  postC_( mpos != ( MutablePosition * ) NIL );
  postC_( mpos -> isValid() );
  return mpos;
}

List *Set::getCore() const
{
  return core;
}

Top *Set::clone() const
{
  return new Set( new List( *getCore() ) );
}

String  Set::getClassName() const
{
  return "Set";
}




#if defined( TESTING )

boolean Set::tester( int ) const
{
  {
	DLOG( "Set Testing: constructor" );

	Set *target;
	target = new Set();
	OGuard _target( target, this );

	DLOGOBJECT( "Created fresh: %s", target );
	if( !( target -> isEmpty() ) )
	  {
		return false;
	  }
  }
  {
	DLOG( "Set Testing: add" );

	Set *target;
	target = new Set();
	OGuard _target( target, this );

	DLOGOBJECT( "Created fresh: %s", target );
	target -> add( new String( "element-the-only" ) );
	DLOGOBJECT( "Added: %s", target );
	if( ( target -> getCardinality() ) != 1 )
	  {
		return false;
	  }
  }
  {
	DLOG( "Set Testing: add different" );

	Set *target;
	target = new Set();
	OGuard _target( target, this );

	DLOGOBJECT( "Created fresh: %s", target );
	target -> add( new String( "element-1" ) );
	DLOGOBJECT( "Added: %s", target );
	target -> add( new String( "element-2" ) );
	DLOGOBJECT( "Added: %s", target );
	if( ( target -> getCardinality() ) != 2 )
	  {
		return false;
	  }
  }
  {
	DLOG( "Set Testing: add same" );

	Set *target;
	target = new Set();
	OGuard _target( target, this );

	DLOGOBJECT( "Created fresh: %s", target );
	target -> add( new String( "element-the-same" ) );
	DLOGOBJECT( "Added: %s", target );
	target -> add( new String( "element-the-same" ) );
	DLOGOBJECT( "Added: %s", target );
	if( ( target -> getCardinality() ) != 1 )
	  {
		return false;
	  }
  }
  {
	DLOG( "Set Testing: getAny" );

	Set *target;
	target = new Set();
	OGuard _target( target, this );

	DLOGOBJECT( "Created fresh: %s", target );
	target -> add( new String( "element-get-any" ) );
	DLOGOBJECT( "Added: %s", target );
	if( !( target -> getAny() -> equals( new String( "element-get-any" ) ) ) )
	  {
		return false;
	  }
  }
  {
	DLOG( "Set Testing: getAndRemove" );

	Set *target;
	target = new Set();
	OGuard _target( target, this );

	DLOGOBJECT( "Created fresh: %s", target );
	target -> add( new String( "element-get-and-remove" ) );
	DLOGOBJECT( "Added: %s", target );
	if( !( target -> getAny() -> equals( new String( "element-get-and-remove" ) ) ) )
	  {
		return false;
	  }
  }
  return true;
}

#endif



SetPositionFactory::SetPositionFactory( Set *aSet )
{
  FNNINIT( set, aSet );
}

SetPositionFactory::~SetPositionFactory()
{
  FDONE( set );
}

MutablePosition *SetPositionFactory::createPosition()
{
  return( set -> getNew( null ) );
}

SetPosition::SetPosition( Set *aContainer ) :
  PositionAdapter( aContainer )
{
  corePosition = ( MutablePosition * ) NIL;
}

SetPosition::~SetPosition()
{
  LinkManager::free( this, corePosition );
}

void SetPosition::setCore( MutablePosition *aCorePosition )
{
  preC_( aCorePosition != ( MutablePosition * ) NIL );
  LinkManager::move( this, corePosition, aCorePosition );
  corePosition = aCorePosition;
}

boolean   SetPosition::isValid () const
{
  preC_( corePosition != NIL );
  return( corePosition -> isValid() );
}

Top *SetPosition::setValue( Top *aNewValue )
{
  preC_( corePosition != NIL );
  Position *pos;
  MutablePosition *mpos;

  OGuard _host( getContainer(), this );

  pos = getSet() -> unify( aNewValue );
  if( pos == ( Position * ) NIL )
	/*
	  Changing to new value, not present in this set
	*/
	{
	  return( corePosition -> setValue( aNewValue ) );
	}
  else
	/*
	  Already has such element, move to it
	*/
	{
	  Top *oldValue;

	  mpos = DCAST( pos, MutablePosition );
	  PGuard _mpos( mpos, this );
	  postC_( mpos != NIL );
	  postC_( mpos -> isValid() );

	  oldValue = getValue();
	  PGuard _oldValue( oldValue, this );
	  
	  setCore( mpos );
	  return oldValue;
	}
}

Top *SetPosition::getValue() const
{
  preC_( corePosition != NIL );
  return( corePosition -> getValue() );
}

Set *SetPosition::getSet() const
{
  Container *hostSet;

  hostSet = getContainer();
  test_( hostSet != NIL );
  return DCAST( hostSet, Set );
}

void SetPosition::remove()
{
  preC_( isValid() );
  DCAST( corePosition, RemovablePosition ) -> remove();
  postC_( !isValid() );
}

String  SetPosition::getClassName() const
{
  return "SetPosition";
}




SetPositionMap::SetPositionMap( Set *aSet )
{
  FNNINIT( set, aSet );
}

SetPositionMap::~SetPositionMap()
{
  FDONE( set );
}

Top *SetPositionMap::apply( Top *anArg )
{
  preC_( set != ( Set * ) NIL );
  preC_( anArg != ( Top * ) nil );

  MutablePosition *position;
  SetPosition *wrapper;

  position = DCAST( anArg, MutablePosition );
  test_( position != null );
  OGuard _position( position, this );

  wrapper = new SetPosition( set );
  PGuard _wrapper( wrapper, this );

  wrapper -> setCore( position );
  return wrapper;
}

END_QR_NAMESPACE

#if defined(_INLINE)
#include "../src/Debug.ipp"
#endif

/*
 * $Log: Set.cpp,v $
 * Revision 1.1.1.1  2000/07/19 16:45:42  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:41  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:31  god
 * Imported sources
 *
 * Revision 1.4  1999/05/22 13:00:54  philogelos
 * Merging sources back from SPARC
 *
 * Revision 1.3  1999/03/03 19:09:38  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.2  1999/02/28 16:30:01  philogelos
 * LayeredContainer adde. Tuned for inlines.
 *
 * Revision 1.1.1.1  1998/11/25 20:11:03  philogelos
 * Quercus Robusta
 * */
