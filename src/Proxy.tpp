// -*-C++-*- 

/*  src/Proxy.tpp  */

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



/* $Id: Proxy.tpp,v 1.3 2001/07/03 12:48:08 philogelos Exp $ */

#include "Proxy.hpp"
#include "Debug.hpp"
#include "AbstractFactory.hpp"

#include "defines.h"

BEGIN_QR_NAMESPACE

template< class X > Proxy< X >::Proxy( AbstractFactory *aFactory )
{
  preC_( aFactory != NULL );
  
  factory = aFactory;
  core = NULL;
}

template< class X > Proxy< X >::~Proxy()
{}

template< class X > X *Proxy< X >::getValue() const
{
  if( *core == NULL )
	{
	  *const_cast< CRef< X > * >( &core ) = TCAST( factory -> create(), X );
	}
  return *core;
}

template< class X > X *Proxy< X >::operator -> () const
{
  return getValue();
}

template< class X > X *Proxy< X >::operator  = ( X *aTarget )
{
  return( core = aTarget );
}

template< class X > X *Proxy< X >::operator  * () const
{
  return getValue();
}

template< class X > boolean Proxy< X >::equals( const Top *anOther) const
{
  if( DCAST( anOther, Proxy< X > ) != NULL )
	{
	  return( getValue() -> equals
			  ( TCAST( anOther, Proxy< X > ) -> getValue() ) );
	}
  return false;
}

template< class X > Top *Proxy< X >::clone() const
{
  return new Proxy< X >( *factory );
}

template< class X > String  Proxy< X >::toString() const
{
  return Object::toString();
}

template< class X > String  Proxy< X >::getString() const
{
  return( ( *core == NULL ) ? String( "<lazy>" ) : getValue() -> toString() );
}

template< class X > String  Proxy< X >::getClassName() const
{
  return "Proxy";
}

#if defined( TESTING )

END_QR_NAMESPACE
#include "Integer.hpp"
#include "ObjectFactory.hpp"
#include "containers/Queue.hpp"
#include "containers/lists/List.hpp"
BEGIN_QR_NAMESPACE

template< class X > boolean Proxy< X >::tester( int ) const
{
  TRACE( "start" );
  {
	TRACE( "create" );

	CRef< Proxy< List > > lazy;
	CRef< List > matrix;

	matrix = new List;
	matrix -> append( new Object() );
	matrix -> append( new String( "foo" ) );
	matrix -> append( new Queue() );

	lazy = new Proxy< List >( new ObjectFactory( *matrix ) );
	DLOGOBJECT( "created: %s", *lazy );
	( *( *lazy ) ) -> prepend( new Integer( 42 ) );
	DLOGOBJECT( "accessed: %s", *lazy );
  }
  return true;
}
#endif

END_QR_NAMESPACE

#if defined( _INLINE )
#include "../src/Debug.ipp"
#endif


/* 
 * $Log: Proxy.tpp,v $
 * Revision 1.3  2001/07/03 12:48:08  philogelos
 * add #include "containers/lists/List.hpp"
 *
 * Revision 1.2  2000/08/30 12:20:35  philogelos
 * THROWS clauses updates to correspond to the real throws.
 *
 * Revision 1.1  2000/08/29 17:48:08  philogelos
 * Proxy class for lazy object creation added.
 * 
 */
