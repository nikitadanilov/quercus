// -*-C++-*- 

/*  src/MethodMap.tpp  */


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


/* $Id: MethodMap.tpp,v 1.1.1.1 2000/07/19 16:41:43 philogelos Exp $ */

#include "MethodMap.hpp"

#if defined( USE_METHOD_MAP )

#include "Debug.hpp"
#include "LinkManager.hpp"

BEGIN_QR_NAMESPACE

template< class X, class Y > MethodMap< X, Y >::MethodMap( Y *( X::*aMethod )() ) :
  type( direct ),
  directMethod( aMethod )
{}

template< class X, class Y > MethodMap< X, Y >::MethodMap( Y *( X::*aMethod )( Top * ), 
														   Top *anAdditionalArgument ) :
  type( partial ),
  partialMethod( aMethod )
{
  addArg = anAdditionalArgument;
  if( addArg != nil )
	{
	  OREG( addArg );
	}
}

// MethodMap< X, Y >::MethodMap( String ( Top::*aMethod )() ) :
//   type( string ),
//   stringMethod( aMethod )
// {}

template< class X, class Y > MethodMap< X, Y >::~MethodMap()
{
  FCDONE( addArg );
}

template< class X, class Y > Y *MethodMap< X, Y >::typedApply( X *anArgument )
{
  switch( type )
	{
	case direct:
	  return ( anArgument ->* directMethod )();
	case partial:
	  return ( anArgument ->* partialMethod )( addArg );
	  // 	case string:
	  // 	  return ( anArgument ->* stringMethod )().clone();
	default:
	  impossible_;
	  return nil;
	}
  impossible_;
  return nil;
}

template< class X, class Y > Top *MethodMap< X, Y >::apply( Top *anArgument )
{
  Top *rawResult;

  preC( DCAST( anArgument, X ) != nil,
		"Agrument of invalid type" );

  rawResult = typedApply( DCAST( anArgument, X ) );

  postC( DCAST( rawResult, Y ) != nil,
		 "Result of invalid type" );

  return dynamic_cast< Y * >( rawResult );
}

template< class X, class Y > boolean MethodMap< X, Y >::equals( const Top *anOther ) const
{
  MethodMap< X, Y > *other;

  if( DCAST( anOther, MethodMap< X commaForCpp Y > ) == null )
	{
	  return false;
	}
  other = DCAST( anOther, MethodMap< X commaForCpp Y > );
  if( other -> type != type )
	{
	  return false;
	}
  switch( type )
	{
	case direct:
	  if( directMethod != other -> directMethod )
		{
		  return false;
		}
	  break;
	case partial:
	  if( partialMethod != other -> partialMethod )
		{
		  return false;
		}
	  else
		{
		  if( ! ( addArg -> equals( other -> addArg ) ) )
			{
			  return false;
			}
		}
	  break;
	  // 	case string:
	  // 	  if( stringMethod != other -> stringMethod )
	  // 		{
	  // 		  return false;
	  // 		}
	  // 	  break;
	default:
	  impossible_;
	  return false;
	}
  return true;
}

template< class X, class Y > Top *MethodMap< X, Y >::clone() const
{
  switch( type )
	{
	case direct:
#if defined(__GNUC__)
	  /* gcc fails with internal error otherwise */
	  Y *( X::*fakeDirect )();

	  fakeDirect = directMethod;
	  return new MethodMap( fakeDirect, 
							isCallerResponsibility(),
							isResultDependOnArg() );
#else
	  return new MethodMap( directMethod, 
							isCallerResponsibility(),
							isResultDependOnArg() );
#endif
	case partial:
#if defined(__GNUC__)
	  /* gcc fails with ``sorry, not implemented: `integer_cst' not 
		 supported by dump_type'' otherwise */
	  Y *( X::*fakePartial )( Top * );

	  fakePartial = partialMethod;
	  return new MethodMap( fakePartial, 
							addArg, false,
							isCallerResponsibility(),
							isResultDependOnArg() );
#else
	  return new MethodMap( ( Y *( X::* )( Top * ) ) partialMethod, 
							addArg, false,
							isCallerResponsibility(),
							isResultDependOnArg() );
#endif
	  // 	case string:
	  // 	  return new MethodMap( ( String ( Top::* )() ) stringMethod,
	  // 							isResultDependOnArg() );
	default:
	  impossible_;
	}
  impossible_;
  return nil;
}

template< class X, class Y > String  MethodMap< X, Y >::getString() const
{
  switch( type )
	{
	case direct:
	  return "direct method";
	case partial:
	  return String( "partially evealuated with arg: " ) + 
		( ( addArg != null ) ? addArg -> getString() : String( "null" ) );
	  // 	case string:
	  // 	  return "string method";
	default:
	  impossible_;
	}
  impossible_;
  return String();
}

template< class X, class Y > String  MethodMap< X, Y >::getClassName() const
{
  return "MethodMap";
}

END_QR_NAMESPACE

#if defined(_INLINE)
#include "../src/Debug.ipp"
#endif

/* USE_METHOD_MAP */
#endif


/*
 * $Log: MethodMap.tpp,v $
 * Revision 1.1.1.1  2000/07/19 16:41:43  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:39  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:28  god
 * Imported sources
 *
 * Revision 1.4  1999/05/22 13:00:30  philogelos
 * Merging sources back from SPARC
 *
 * Revision 1.3  1999/03/03 19:09:28  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.2  1999/02/28 15:50:58  philogelos
 * Tuned for inlines.
 *
 * Revision 1.1.1.1  1998/11/25 20:11:01  philogelos
 * Quercus Robusta
 *
 * Revision 1.1  1998/07/09 09:30:38  philogelos
 * new files added to the repository
 * */
