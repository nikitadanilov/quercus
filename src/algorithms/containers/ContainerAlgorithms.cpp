// -*-C++-*- 

/*  src/algorithms/containers/ContainerAlgorithms.cpp  */

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



/* $Id: ContainerAlgorithms.cpp,v 1.1 2001/06/09 15:35:10 philogelos Exp $ */
#if !defined( _INLINE )
static char cvsid[] = "@(#)$Id: ContainerAlgorithms.cpp,v 1.1 2001/06/09 15:35:10 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif

#include "algorithms/containers/ContainerAlgorithms.hpp"
#include "containers/Container.hpp"
#include "containers/PositionFactory.hpp"
#include "containers/MutablePosition.hpp"
#include "OGuard.hpp"
#include "String.hpp"
#include "Debug.hpp"

BEGIN_QR_NAMESPACE

ContainerAlgorithms::ContainerAlgorithms()
{}

ContainerAlgorithms::~ContainerAlgorithms()
{}

void ContainerAlgorithms::flatten( Top *aStructure, PositionFactory *aFactory )
{
  preC_( aStructure != NULL );
  preC_( aFactory != NULL );

  OGuard _container( aStructure, this );
  OGuard _factory( aFactory, this );

  /*
  ;; from flame.el by Unknown
  (defun flatten (list)
   (cond ((atom list)
	 (list list))
	(t (apply 'append (mapcar 'flatten list)))))
  */

  if( DCAST( aStructure, Container ) != NULL )
	{
	  CRef< Enumeration > elements;

	  elements = DCAST( aStructure, Container ) -> getValueEnumeration();
	  while( elements -> hasMoreElements() )
		{
		  flatten( elements -> getNextElement(), aFactory );
		}
	}
  else
	{
	  CRef< MutablePosition > slot;
	  
	  slot = aFactory -> createPosition();
	  slot -> setValue( aStructure );
	}
  /* so, do you still think LISP is too verbose because of its
	 parens? */
}

ContainerAlgorithms *ContainerAlgorithms::get()
{
  return *instance;
}

String  ContainerAlgorithms::getClassName() const
{
  return "ContainerAlgorithms";
}

CRef< ContainerAlgorithms > ContainerAlgorithms::instance( new ContainerAlgorithms() );

#if defined( TESTING )

END_QR_NAMESPACE
#include "containers/lists/List.hpp"
#include "containers/Singleton.hpp"
#include "containers/Stack.hpp"
#include "containers/Pair.hpp"
#include "KOI8RConverter.hpp"
#include "ObjectWrapper.hpp"
#include "Integer.hpp"
BEGIN_QR_NAMESPACE

boolean ContainerAlgorithms::tester( int ) const
{
  {
	DLOG( "testing: flatten" );

	CRef< List > list;
	CRef< List > target;

	list = new List( 0, 
					 OW( new String( "foo" ) ),
					 OW( new Stack() ),
					 OW( new List( 0,
								   OW( new String( "bar" ) ),
								   OW( new Integer( 0xfacaded ) ),
								   NULL ) ),
					 OW( new Singleton( new Pair( new String( "1" ),
												  new String( "2" ) ) ) ),
					 OW( new Pair( new String( "раз", new KOI8RConverter() ), 
								   new String( "два", new KOI8RConverter() ) ) ),
					 NULL );
	DLOGOBJECT( "original: %s", *list, &Top::getString );
	target = new List();
	CALG -> flatten( *list, target -> getDefaultPositionFactory() );
	DLOGOBJECT( "flattened: %s", *target, &Top::getString );
  }
  return true;
}
#endif

END_QR_NAMESPACE

#if defined( _INLINE )
#include "../src/Debug.ipp"
#endif


/*
 * $Log: ContainerAlgorithms.cpp,v $
 * Revision 1.1  2001/06/09 15:35:10  philogelos
 * ContainerAlgorithms added (only ::flatten() is implemented as of now)
 *
 */
