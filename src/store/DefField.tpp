// -*-C++-*- 

/*  src/store/DefField.cpp  */

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



/* $Id: DefField.tpp,v 1.1 2000/09/21 16:46:04 philogelos Exp $ */

#include "store/DefField.hpp"
#include "Debug.hpp"

BEGIN_QR_NAMESPACE

template< class S, class V > 
BaseDefField< S, V >::BaseDefField( String aName, const S *aBase )
{
  preC_( aBase != NULL );

  base = ( S * ) aBase;
  name = aName;
}

template< class S, class V > BaseDefField< S, V >::~BaseDefField()
{}

// template< class S, class V >
// BaseDefField< S, V > *BaseDefField< S, V >::setField( V S::*aField )
// {
//   field = aField;
//   return this;
// }

template< class S, class V > V BaseDefField< S, V >::getValue() const
{
  return getBase() ->* field;
}

template< class S, class V > void BaseDefField< S, V >::setValue( V aValue )
{
  getBase() ->* field = aValue;
}

template< class S, class V > S *BaseDefField< S, V >::getBase() const
{
  return *base;
}

template< class S, class V > String BaseDefField< S, V >::getName() const
{
  return name;
}

template< class S, class V > String  BaseDefField< S, V >::toString() const
{
  return Object::toString() + 
	" base: " + getBase() -> toString();
}

template< class S, class V > String  BaseDefField< S, V >::getClassName() const
{
  return "DefField";
}

/* subobject */

template< class S >
DefField< S, Storable * >::DefField( String aName, const S *aBase, 
									 Storable *S::*aField ) :
  BaseDefField< S, Storable * >( aName, aBase )
{
  field = aField;
}

template< class S > 
void DefField< S, Storable * >::store( StoreSession *aSession, 
									   FieldWriter *aWriter )
{
  preC_( aWriter != NULL );
  preC_( aSession != NULL );
  
  aWriter -> storeSubobject( aSession, getName(), getValue() );
}

template< class S > 
void DefField< S, Storable * >::retrieve( StoreSession *aSession, 
										  FieldReader *aReader )
{
  preC_( aReader != NULL );
  preC_( aSession != NULL );

  //  setValue( aReader -> retrieveSubObject( aSession, getName() ) );
}

/* string */

template< class S >
DefField< S, String >::DefField( String aName, const S *aBase, 
								 String S::*aField ) :
  BaseDefField< S, String >( aName, aBase )
{
  field = aField;
}

template< class S > 
void DefField< S, String >::store( StoreSession *aSession, 
								   FieldWriter *aWriter )
{
  preC_( aWriter != NULL );
  preC_( aSession != NULL );
  
  aWriter -> storeString( aSession, getName(), getValue() );
}

template< class S > 
void DefField< S, String >::retrieve( StoreSession *aSession, 
									  FieldReader *aReader )
{
  preC_( aReader != NULL );
  preC_( aSession != NULL );

  //  setValue( aReader -> retrieveString( aSession, getName() ) );
}

/* index */

template< class S >
DefField< S, Index >::DefField( String aName, const S *aBase, 
								Index S::*aField ) :
  BaseDefField< S, Index >( aName, aBase )
{
  field = aField;
}

template< class S > 
void DefField< S, Index >::store( StoreSession *aSession, 
								  FieldWriter *aWriter )
{
  preC_( aWriter != NULL );
  preC_( aSession != NULL );
  
  aWriter -> storeIndex( aSession, getName(), getValue() );
}

template< class S > 
void DefField< S, Index >::retrieve( StoreSession *aSession, 
									 FieldReader *aReader )
{
  preC_( aReader != NULL );
  preC_( aSession != NULL );

  //  setValue( aReader -> retrieveIndex( aSession, getName() ) );
}

/* boolean */

template< class S >
DefField< S, boolean >::DefField( String aName, const S *aBase, 
								  boolean S::*aField ) :
  BaseDefField< S, boolean >( aName, aBase )
{
  field = aField;
}

template< class S > 
void DefField< S, boolean >::store( StoreSession *aSession, 
										FieldWriter *aWriter )
{
  preC_( aWriter != NULL );
  preC_( aSession != NULL );
  
  aWriter -> storeBoolean( aSession, getName(), getValue() );
}

template< class S > 
void DefField< S, boolean >::retrieve( StoreSession *aSession, 
									   FieldReader *aReader )
{
  preC_( aReader != NULL );
  preC_( aSession != NULL );

  //  setValue( aReader -> retrieveBoolean( aSession, getName() ) );
}

/* cref */

template< class S >
DefField< S, CRef< Storable > >::DefField( String aName, const S *aBase, 
										   CRef< Storable > S::*aField ) :
  BaseDefField< S, CRef< Storable > >( aName, aBase )
{
  field = aField;
}

template< class S > 
void DefField< S, CRef< Storable > >::store( StoreSession *aSession, 
											 FieldWriter *aWriter )
{
  preC_( aWriter != NULL );
  preC_( aSession != NULL );
  
  aWriter -> storeSubobject( aSession, getName(), *getValue() );
}

template< class S > 
void DefField< S, CRef< Storable > >::retrieve( StoreSession *aSession, 
												FieldReader *aReader )
{
  preC_( aReader != NULL );
  preC_( aSession != NULL );

  //  setValue( aReader -> retrieveSubObject( aSession, getName() ) );
}


#if defined( TESTING )

END_QR_NAMESPACE
#include "store/DefField.hpp"
#include "store/Storable.hpp"
#include "store/StoreDescAdapter.hpp"
#include "platform/store/POSIXStore.hpp"
#include "ObjectWrapper.hpp"
#include "containers/lists/List.hpp"
BEGIN_QR_NAMESPACE

class SObject : public virtual Object,
				public virtual Storable
{
public: SObject() { foo = this; bar = NULL; };
public: virtual StorableDesc *getStorableDesc() const
  {
	return new StoreDescAdapter
	  ( "v0.0.1", 
		new List( 1, 
				  SSUBOBJ( SObject, foo ), 
				  SSUBOBJ( SObject, bar ),
				  RSUBOBJ( SObject, baz ),
				  SFIELD( SObject, String, str ), 
				  SFIELD( SObject, Index, ind ),
				  SFIELD( SObject, boolean, morgan ), NULL ) );
  }
public: Storable *foo;
public: Storable *bar;
public: String    str;
public: Index     ind;
public: boolean   morgan;
public: CRef< Storable > baz;
};

template< class S, class V > 
boolean BaseDefField< S, V >::testerBaseDefField( int )
{
  {
	DLOG( "DefField testing" );

	CRef< StoreSession > session;
	CRef< SObject > root;
	CRef< SObject > baz;

	root = new SObject();
	baz = new SObject();
	baz -> bar = *root;
	root -> baz = *baz;
	root -> str = "root.str";
	root -> ind = ( Index ) *root;
	root -> morgan = true;
	baz -> str = "baz.str";
	baz -> ind = ( Index ) *baz;
	baz -> morgan = false;
	session = new StoreSession( "root", *root, new POSIXStore( "store" ) );
	session -> store();
  }
  return true;
}

/* TESTING */
#endif

END_QR_NAMESPACE

#if defined( _INLINE )
#include "../src/Debug.ipp"
#endif

/*
 * $Log: DefField.tpp,v $
 * Revision 1.1  2000/09/21 16:46:04  philogelos
 * Persistency sub-system (first draft). Store only.
 *
 */
