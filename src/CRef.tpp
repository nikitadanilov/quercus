// -*-C++-*- 

/*  src/CRef.cpp  */

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



/* $Id: CRef.tpp,v 1.1.1.1 2000/07/19 16:40:28 philogelos Exp $ */

#include "CRef.hpp"
#include "Debug.hpp"
#include "LinkManager.hpp"

BEGIN_QR_NAMESPACE

template < class X > CRef< X >::CRef()
{
  canBeNull = true;
  lock = false;
  recycle = true;
  link = true;

  init( NULL );
}

template < class X > CRef< X >::CRef( X *aTarget, 
									  boolean isNullable,
									  boolean mustLock,
									  boolean mustRecycle,
									  boolean mustLink )
{
  canBeNull = isNullable;
  lock = mustLock;
  recycle = mustRecycle;
  link = mustLink;

  init( aTarget );
}

template < class X > CRef< X >::~CRef()
{
  done();
}

template < class X > void CRef < X >::setValue( X *aTarget )
{
  done();
  init( aTarget );
}

template < class X > X *CRef < X >::getValue() const
{
  return target;
}

template < class X > X *CRef < X >::operator -> () const
{
  return getValue();
}

template < class X > X *CRef < X >::operator  = ( X *aTarget )
{
  done();
  init( aTarget );
  return aTarget;
}

template < class X > X *CRef < X >::operator * () const
{
  return getValue();
}

template < class X > boolean CRef < X >::equals( const Top *anOther ) const
{
  return( ( DCAST( anOther, CRef < X > ) != NULL ) &&
		  ( DCAST( anOther, CRef < X > ) -> getValue() -> 
			equals( getValue() ) ) );
}

template < class X > Top *CRef< X >::clone() const
{
  return new CRef< X >( getValue(), true, lock, recycle, link );
}

template < class X > String  CRef< X >::toString() const
{
  return Object::toString() + 
	" ref. to: " + ( ( getValue() == NULL ) ? 
					 String::nullLiteral : 
					 getValue() -> toString() );
}

template < class X > String  CRef< X >::getString() const
{
  return getValue() -> getString();
}

template < class X > String  CRef< X >::getClassName() const
{
  return "CRef";
}

template < class X > void CRef< X >::done()
{
  if( target != NULL )
	{
	  if( lock )
 		{
		  target -> unlock( this );
		}
	  else if( link )
		{
		  if( recycle )
			{
			  OFREE( target );
			}
		  else
			{
			  LinkManager::unreg( this, target );
			}
		}
	}
}

template < class X > void CRef< X >::init( X *aTarget )
{
  preC_( ergo( !canBeNull, aTarget != NULL ) );
  preC_( ergo( recycle, link ) );

  target = aTarget;
  if( target != NULL )
	{
	  if( lock )
		{
		  target -> lock( this );
		}
	  else if( link )
		{
		  OREG( target );
		}
	}
}

END_QR_NAMESPACE

#if defined(_INLINE)
#include "../src/Debug.ipp"
#endif


/*
 * $Log: CRef.tpp,v $
 * Revision 1.1.1.1  2000/07/19 16:40:28  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.6  2000/04/09 12:00:48  god
 * CVS Log keyword correction finished
 *
 * Revision 1.5  2000/04/09 11:29:38  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.4  2000/04/07 17:10:35  god
 * Handling of nulls in ::toString()
 *
 * Revision 1.3  2000/04/06 11:53:33  god
 * default constructor and ::operator * added
 *
 * Revision 1.2  2000/04/05 17:19:40  god
 * Dynamic modules, askUser (+readline) dlsym/dladdr-based Backtrace
 *
 * Revision 1.1.1.1  2000/04/01 14:07:29  god
 * Imported sources
 * */
