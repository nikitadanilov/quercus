// -*-C++-*- 

/*  src/containers/dict/DumbDictionary.cpp  */


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



/* $Id: DumbDictionary.cpp,v 1.3 2001/06/23 12:31:24 philogelos Exp $ */
#if !defined(_INLINE)
static char cvsid[] = "@(#)$Id: DumbDictionary.cpp,v 1.3 2001/06/23 12:31:24 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif


#include "containers/dicts/DumbDictionary.hpp"
#include "containers/dicts/DictKeyPosition.hpp"

#include "algorithms/enumerations/EnumerationAlgorithms.hpp"
#include "iter/enumerations/MappedEnumeration.hpp"
#include "iter/iterators/EnumerationIterator.hpp"
#include "containers/lists/List.hpp"
#include "containers/Pair.hpp"
#include "Debug.hpp"
#include "LinkManager.hpp"
#include "OGuard.hpp"
#include "PGuard.hpp"

BEGIN_QR_NAMESPACE

DumbDictionary::DumbDictionary()
{
  FINIT( conses, new List() );
}

DumbDictionary::~DumbDictionary()
{
  FDONE( conses );
}

Enumeration *DumbDictionary::getKeys() const
{
  return new MappedEnumeration( getConses() -> getValueEnumeration(),
								new PiMap( 1 ) );
}

Enumeration *DumbDictionary::getValues() const
{
  return new MappedEnumeration( getConses() -> getValueEnumeration(),
								new PiMap( 2 ) );
}

boolean DumbDictionary::isSuchKey( const DictKey *aKey ) const
{
  return( EAlg::get() -> contains( getKeys(), aKey ) != NULL );
}

Enumeration *DumbDictionary::getKeyEnumeration() const
{
  return getKeys();
}

Top *DumbDictionary::setValueAtKey( const DictKey *aKey, Top *aValue )
{
  OGuard _this( this, this );
  OGuard _key( aKey, this );
  OGuard _value( aValue, this );
  preC_( isSuchKey( aKey ) );

  return( getConsOf( aKey ) -> setAt( 2, aValue ) );
}

Top *DumbDictionary::getValueAtKey( const DictKey *aKey ) const
{
  OGuard _this( this, this );
  OGuard _key( aKey, this );
  preC_( isSuchKey( aKey ) );

  return( getConsOf( aKey ) -> getAt( 2 ) );
}

void DumbDictionary::addKey( const DictKey *aKey, Top *aValue )
{
  OGuard _this( this, this );
  OGuard _key( aKey, this );
  OGuard _value( aValue, this );
  preC_( !( isSuchKey( aKey ) ) );

  getConses() -> append( new Pair( ( Top * ) aKey, aValue ) );
}

Top *DumbDictionary::removeKey( const DictKey *aKey )
{
  OGuard _this( this, this );
  OGuard _key( aKey, this );
  preC_( isSuchKey( aKey ) );
  Index keyIndex;
  Top *oldValue;

  oldValue = getValueAtKey( aKey );
  PGuard _old( oldValue, this );
  keyIndex = getIndexOf( aKey );
  getConses() -> setCurrentAt( keyIndex );
  OGuard _del( getConses() -> remove(), this );
  return oldValue;
}

Top *DumbDictionary::getValue( const Position *aPosition )
{
  OGuard _position( aPosition, this );
  preC_( isValid( aPosition ) );
  return( aPosition -> getValue() );
}

Top   *DumbDictionary::setValue( MutablePosition *aPosition, Top *aNewValue )
{
  OGuard _position( aPosition, this );
  OGuard _value( aNewValue, this );
  preC_( isValid( aPosition ) );
  return( aPosition -> setValue( aNewValue ) );
}

Index DumbDictionary::getCardinality() const
{
  return( getConses() -> getCardinality() );
}

PositionFactory *DumbDictionary::getDefaultPositionFactory() const
{
  return new DictPositionFactory( ( Dictionary * ) this );
}

TypedEnumeration< RemovablePosition > *DumbDictionary::getRemovable() const
{
  return TypedEnumeration< RemovablePosition >::upcast( getEnumeration() );
}

PositionEnumeration *DumbDictionary::getEnumeration() const
{
  return ( getMutableEnumeration() );
}

Enumeration *DumbDictionary::getValueEnumeration() const
{
  return getValues();
}

Iterator    *DumbDictionary::getMutableIterator() const
{
  return new EnumerationIterator( getMutableEnumeration() );
}

MutablePositionEnumeration *DumbDictionary::getMutableEnumeration() const
{
  return MutablePositionEnumeration::createMutableFrom
	( TypedEnumeration< MutablePosition >::upcast
	  ( new MappedEnumeration
		( getKeys(), 
		  new DictPositionMap( ( Dictionary * ) this ) ) ) );
}

Top *DumbDictionary::clone() const
{
  OGuard _this( this, this );
  return new DumbDictionary( TCAST( getConses() -> clone(), List ) );
}

String  DumbDictionary::getClassName() const
{
  return "DumbDictionary";
}

Pair *DumbDictionary::getConsAt( const Index anIndex ) const
{
  OGuard _this( this, this );
  
  Top *cons;

  cons = getConses() -> getAt( anIndex );
  test_( DCAST( cons, Pair ) != NIL );
  return DCAST( cons, Pair );
}

DumbDictionary::DumbDictionary( List *aConses )
{
  FINIT( conses, aConses );
}

List *DumbDictionary::getConses() const
{
  return conses;
}

Index DumbDictionary::getIndexOf( const DictKey *aKey ) const
{
  OGuard _this( this, this );
  OGuard _key( aKey, this );
  preC_( isSuchKey( aKey ) );
  return( EAlg::get() ->
		  findIndex( getKeys(), aKey, getCardinality() ) );
}

Pair *DumbDictionary::getConsOf( const DictKey *aKey ) const
{
  OGuard _this( this, this );
  OGuard _key( aKey, this );
  preC_( isSuchKey( aKey ) );
  return( getConsAt( getIndexOf( aKey ) ) );
}

/* XXX this should be moved out there! */
DictPositionMap::DictPositionMap( Dictionary *aDict )
{
  FNNINIT( dict, aDict );
}

DictPositionMap::~DictPositionMap()
{
  FDONE( dict );
}

Top *DictPositionMap::apply( Top *anArg )
{
  preC_( dict != NIL );
  preC_( anArg != ( Top * ) nil );

  DictKeyPosition *wrapper;
  OGuard _arg( anArg, this );

  wrapper = new DictKeyPosition( dict );
  PGuard _wrapper( wrapper, this );

  wrapper -> setKey( anArg );
  return wrapper;
}

DictPositionFactory::DictPositionFactory( Dictionary *aDict )
{
  FNNINIT( dict, aDict );
  FINIT( count, new Integer( 0 ) );
}

DictPositionFactory::~DictPositionFactory()
{
  FDONE( dict );
  FDONE( count );
}

MutablePosition *DictPositionFactory::createPosition()
{
  OGuard _dict( dict, this );
  DictKeyPosition *result;

  while( dict -> isSuchKey( count ) )
	{
	  count -> inc();
	}
   result = new DictKeyPosition( dict );
   result -> setKey( count -> clone() );
   return result;
}

#if defined( TESTING )

boolean DumbDictionary::tester( int ) const
{
  {
	DLOG( "DumbDictionary Testing: constructor" );

	DumbDictionary *target;
	target = new DumbDictionary();
	OGuard _target( target, this );

	DLOGOBJECT( "Created fresh: %s", target );
	if( !( target -> isEmpty() ) )
	  {
		return false;
	  }
  }
  {
	DLOG( "DumbDictionary Testing: addKey" );

	DumbDictionary *target;
	target = new DumbDictionary();
	OGuard _target( target, this );

	DLOGOBJECT( "Created fresh: %s", target );
	if( !( target -> isEmpty() ) )
	  {
		return false;
	  }
	target -> addKey( new String( "key" ), new String( "value" ) );
	DLOGOBJECT( "Added: %s", target );
	if( target -> getCardinality() != 1 )
	  {
		DLOG( "Wrong addKey()" );
		return false;
	  }
  }
  {
	DLOG( "DumbDictionary Testing: isSuchKey" );

	DumbDictionary *target;
	target = new DumbDictionary();
	OGuard _target( target, this );

	DLOGOBJECT( "Created fresh: %s", target );
	if( !( target -> isEmpty() ) )
	  {
		return false;
	  }
	target -> addKey( new String( "key" ), new String( "value" ) );
	DLOGOBJECT( "Added: %s", target );
	if( target -> getCardinality() != 1 )
	  {
		return false;
	  }
	String *key = new String( "key" );
	String *value = new String( "value" );

	OGuard _key( key, this );
	OGuard _value( value, this );

	if( !( target -> isSuchKey( key ) ) )
	  {
		DLOG( "Wrong isSuchKey()" );
		return false;
	  }
	if( target -> isSuchKey( nil ) )
	  {
		DLOG( "Wrong isSuchKey()" );
		return false;
	  }
	if( target -> isSuchKey( value ) )
	  {
		DLOG( "Wrong isSuchKey()" );
		return false;
	  }
  }
  {
	DLOG( "DumbDictionary Testing: getValueAtKey" );

	DumbDictionary *target;
	target = new DumbDictionary();
	OGuard _target( target, this );

	String *key = new String( "key" );
	String *value = new String( "value" );

	OGuard _key( key, this );
	OGuard _value( value, this );

	DLOGOBJECT( "Created fresh: %s", target );
	if( !( target -> isEmpty() ) )
	  {
		return false;
	  }
	target -> addKey( key, value );
	DLOGOBJECT( "Added: %s", target );
	if( target -> getCardinality() != 1 )
	  {
		DLOG( "Wrong addKey()" );
		return false;
	  }
	DLOGOBJECT( "Value: %s", target -> getValueAtKey( key ) );
	if( !( target -> getValueAtKey( key ) -> 
		   equals( value ) ) )
	  {
		DLOG( "Wrong getValueAtKey()" );
		return false;
	  }
  }
  {
	DLOG( "DumbDictionary Testing: setValueAtKey" );

	DumbDictionary *target;
	target = new DumbDictionary();
	OGuard _target( target, this );

	String *key = new String( "key" );
	String *value = new String( "value" );
	String *newValue = new String( "new-value" );

	OGuard _key( key, this );
	OGuard _value( value, this );
	OGuard _newValue( newValue, this );

	DLOGOBJECT( "Created fresh: %s", target );
	if( !( target -> isEmpty() ) )
	  {
		return false;
	  }
	target -> addKey( key, value );
	DLOGOBJECT( "Added: %s", target );
	if( target -> getCardinality() != 1 )
	  {
		DLOG( "Wrong addKey()" );
		return false;
	  }
	target -> setValueAtKey( key, newValue ); 
	DLOGOBJECT( "Value: %s", target -> 
									 getValueAtKey( key ) );
	if( !( target -> getValueAtKey( key ) -> 
		   equals( newValue ) ) )
	  {
		DLOG( "Wrong setValueAtKey()" );
		return false;
	  }
  }
  return true;
}

#endif

END_QR_NAMESPACE

#if defined(_INLINE)
#include "../src/Debug.ipp"
#endif

/*
 * $Log: DumbDictionary.cpp,v $
 * Revision 1.3  2001/06/23 12:31:24  philogelos
 * updated to conform to changed return type of
 * EnumerationAlgorithms::contains()
 *
 * Revision 1.2  2001/04/16 10:40:41  philogelos
 * Memory leak on key/value removeal corrected
 *
 * Revision 1.1.1.1  2000/07/19 16:46:21  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:42  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:33  god
 * Imported sources
 *
 * Revision 1.3  1999/05/22 13:00:54  philogelos
 * Merging sources back from SPARC
 *
 * Revision 1.2  1999/03/03 19:09:40  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.1  1999/02/28 16:30:24  philogelos
 * Tuned for inlines.
 * */
