// -*- C++ -*-

/*  src/Integer.cpp  */


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


/* $Id: Integer.cpp,v 1.1.1.1 2000/07/19 16:40:50 philogelos Exp $ */
#if !defined(_INLINE)
static char cvsid[] = "@(#)$Id: Integer.cpp,v 1.1.1.1 2000/07/19 16:40:50 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif


#include "Integer.hpp"
#include "Debug.hpp"
#include "OGuard.hpp"
#include "AeternalLifeController.hpp"

#include "exceptions/NotImplemented.hpp"
#include "exceptions/DivideByZero.hpp"

BEGIN_QR_NAMESPACE

Integer::Integer( Index anInt )
{
  setInt( anInt );
}

Integer::Integer( const Integer &anInteger ) : Object()
  /* Got strange gcc-2.95 warning here: base class `class Object' should be 
	 explicitly initialized in the copy constructor.
  */
{
  setInt( anInteger.getInt() );
}

Index Integer::getInt() const
{
  return core;
}

void  Integer::setInt( Index anInt )
{
  core = anInt;
}

const Integer *Integer::getZero()
{
  if( zero == ( const Integer * ) NIL )
	{
	  zero = new Integer( 0 );
	  zero -> dontManage();
	}
  return zero;
}

Integer *Integer::next() const
{
  return new Integer( getInt() + 1 );
}

void     Integer::inc()
{
  setInt( getInt() + 1 );
}

boolean  Integer::isZero() const
{
  return( equals( getZero() ) );
}

Integer *Integer::add( const Integer *aTerm ) const
{
  preC_( aTerm != ( const Integer * ) NIL );
  return new Integer( getInt() + ( aTerm -> getInt() ) );
}

Integer *Integer::sub( const Integer *aTerm ) const
{
  preC_( aTerm != ( const Integer * ) NIL );
  return new Integer( getInt() - ( aTerm -> getInt() ) );
}

Integer *Integer::mul( const Integer *aTerm ) const
{
  preC_( aTerm != ( const Integer * ) NIL );
  return new Integer( getInt() * ( aTerm -> getInt() ) );
}

Integer *Integer::div( const Integer *aTerm ) const THROWS( DivideByZero * )
{
  preC_( aTerm != ( const Integer * ) NIL );
  if( aTerm -> equals( getZero() ) )
	{
	  throw new DivideByZero( "Integer::div", null );
	  RET_THROW( NULL );
	}
  else
	{
	  return new Integer( getInt() / ( aTerm -> getInt() ) );
	}
}


boolean Integer::equals( const Top *anOther ) const
{
  Integer *other;

  other = DCAST( anOther, Integer );
  if( other == ( Integer * ) NIL )
	{
	  return false;
	}
  else
	{
	  return( getInt() == other -> getInt() );
	}
}

Top    *Integer::clone() const
{
  return new Integer( *this );
}

String  Integer::getString() const
{
  return String( getInt() );
}

String  Integer::getClassName() const
{
  return "Integer";
}

boolean Integer::invariant() const
{
  return( Object::invariant() &&
		  (true /* testing of Peano axioms should go there */ ) );
}

#if defined( TESTING )
boolean Integer::tester( int ) const
{
  {
	DLOG( "Integer testing: constructor" );
	Integer *target;

	target = new Integer( 0 );
	OGuard _target( target, this );
	DLOGOBJECT( "Fresh: %s", target );
	if( ! ( target -> invariant() ) )
	  {
		DLOG( "Invariant broken!" );
		return false;
	  }
  }
  {
	DLOG( "Integer testing: getZero" );
	Integer *target;

	target = new Integer( 0 );
	OGuard _target( target, this );
	DLOGOBJECT( "Fresh: %s", target );
	DLOGOBJECT( "getZero: %s", getZero() );
	if( ! ( target -> equals( getZero() ) ) )
	  {
		DLOG( "Wrong zero!" );
		return false;
	  }
  }
  return true;
}
#endif

const Integer *Integer::zero = ( const Integer * ) NIL;

END_QR_NAMESPACE

#if defined(_INLINE)
#include "../src/Debug.ipp"
#endif

/*
 * $Log: Integer.cpp,v $
 * Revision 1.1.1.1  2000/07/19 16:40:50  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:38  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:28  god
 * Imported sources
 *
 * Revision 1.3  1999/05/22 13:00:29  philogelos
 * Merging sources back from SPARC
 *
 * Revision 1.2  1999/03/03 19:09:26  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.1  1999/02/28 15:47:35  philogelos
 * Added
 * */
