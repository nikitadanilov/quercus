// -*-C++-*- 

/*  inc/MethodMap.hpp  */


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


#ifndef __METHODMAP_HPP__
#define __METHODMAP_HPP__

/* $Id: MethodMap.hpp,v 1.1.1.1 2000/07/19 16:56:55 philogelos Exp $ */

#define USE_METHOD_MAP

#if defined( WANT_USE_METHOD_MAP )
#define USE_METHOD_MAP
#elif defined( UNWANT_USE_METHOD_MAP )
#if defined( USE_METHOD_MAP )
#undef USE_METHOD_MAP
#endif
#endif

#if defined( USE_METHOD_MAP )

#include "Object.hpp"
#include "Map.hpp"
#include "String.hpp"
#include "defines.h"

BEGIN_QR_NAMESPACE


/**
   Maps argument to result
   by given method.
   f : X -> Y

   @author Philogelos
   @created
*/
template< class X, class Y > class MethodMap : public Map, public Object
{

public: MethodMap< X, Y >( Y *( X::*aMethod )() );

public: MethodMap< X, Y >( Y *( X::*aMethod )( Top * ), 
				   Top *anAdditionalArgument );

  /* public: MethodMap< X, Y >( String ( Top::*aMethod )(), boolean isDepend ); */

public: virtual ~MethodMap();

public: virtual Top *apply( Top *anArgument );
public: virtual Y *typedApply( X *anArgument );

  /**
	*/
public:  virtual boolean equals( const Top *anOther ) const;

  /**
  */
public:  virtual Top *clone() const;

  /**
	*/
public:  virtual String  getString() const;

  /**
	*/
public:  virtual String  getClassName() const;

protected: enum MapType { direct, partial /*, string */};
protected: const MapType type;

  /* intent is to declare immutable method poinetrs,
	 but this is declaration of poinetrs to methods
	 with return value of type ``const Y *''.
	 
	 What is the right way? XXX
  */
protected: /* const */ Y *( X::*directMethod )();
protected: /* const */ Y *( X::*partialMethod )( Top * );
protected: Top *addArg;
  /* protected: const String ( Top::*stringMethod )(); */
};

END_QR_NAMESPACE

#if defined( INCLUDE_TEMPLATES )
#include "src/MethodMap.tpp"
#endif

/*
 * $Log: MethodMap.hpp,v $
 * Revision 1.1.1.1  2000/07/19 16:56:55  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:16  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:38  god
 * Imported sources
 *
 * Revision 1.3  1999/05/22 13:00:23  philogelos
 * Merging sources back from SPARC
 *
 * Revision 1.2  1999/03/03 19:09:03  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.1.1.1  1998/11/25 20:11:05  philogelos
 * Quercus Robusta
 *
 * Revision 1.1  1998/07/09 09:30:26  philogelos
 * new files added to the repository
 * */

/* USE_METHOD_MAP */
#endif

/* __METHODMAP_HPP__ */
#endif
