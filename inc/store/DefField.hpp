// -*-C++-*- 

/*  inc/store/DefField.hpp  */

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



#ifndef __DEFFIELD_HPP__
#define __DEFFIELD_HPP__

/* $Id: DefField.hpp,v 1.1 2000/09/21 16:46:01 philogelos Exp $ */

#include "Field.hpp"
#include "Object.hpp"
#include "defines.h"
#include "CRef.hpp"

#define STORE_FIELD( cl, type, name ) \
                     new DefField< cl, type >( #name, this, &cl::name )

#define SFIELD( cl, type, name ) \
                     OW( STORE_FIELD( cl, type, name ) )

#define SSUBOBJ( cl, name ) SFIELD( cl, Storable *, name )
#define RSUBOBJ( cl, name ) SFIELD( cl, CRef< Storable >, name )

BEGIN_QR_NAMESPACE

class Storable;

/**

   @author Philogelos
   @created Thu Sep 14 20:39:22 2000
*/
template< class S, class V > 
abstract class BaseDefField : public virtual Object,
							  public virtual Field
{

  /**
   */
public: BaseDefField< S, V >( String aName, const S *aBase );

  /**
   */
public: virtual ~BaseDefField();


  // public: virtual BaseDefField< S, V > *setField( V S::*aField );
public: virtual V getValue() const;
public: virtual void setValue( V aValue );
public: virtual S *getBase() const;

public: virtual String getName() const;
  /**
   */
public: virtual String  toString() const;

  /**
   */
public: virtual String  getClassName() const;

protected: CRef< S > base;
  /* XXX to work around gcc bug: template function definition with
	 member pointer to one of template arguments fails with 
	 `common_type called with uncommon member types (compiler error)'
  */
public: V S::*field;
protected: String name;

#if defined( TESTING )
public: static boolean testerBaseDefField( int aParam );
#endif
};

template< class S, class V > abstract class DefField
{
};

/* partial template specialization */
template< class S > abstract class DefField< S, Storable * > :
  public virtual BaseDefField< S, Storable * >
{
public: DefField< S, Storable * >( String aName, const S *aBase, 
								   Storable *S::*aField );
public: void store( StoreSession *aSession, FieldWriter *aWriter );
public: void retrieve( StoreSession *aSession, FieldReader *aReader );
};

template< class S > abstract class DefField< S, String > :
  public virtual BaseDefField< S, String >
{
public: DefField< S, String >( String aName, const S *aBase, 
							   String S::*aField );
public: void store( StoreSession *aSession, FieldWriter *aWriter );
public: void retrieve( StoreSession *aSession, FieldReader *aReader );
};

template< class S > abstract class DefField< S, Index > :
  public virtual BaseDefField< S, Index >
{
public: DefField< S, Index >( String aName, const S *aBase, 
							  Index S::*aField );
public: void store( StoreSession *aSession, FieldWriter *aWriter );
public: void retrieve( StoreSession *aSession, FieldReader *aReader );
};

template< class S > abstract class DefField< S, boolean > :
  public virtual BaseDefField< S, boolean >
{
public: DefField< S, boolean >( String aName, const S *aBase, 
								boolean S::*aField );
public: void store( StoreSession *aSession, FieldWriter *aWriter );
public: void retrieve( StoreSession *aSession, FieldReader *aReader );
};

template< class S > abstract class DefField< S, CRef< Storable > > :
  public virtual BaseDefField< S, CRef< Storable > >
{
public: DefField< S, CRef< Storable > >( String aName, const S *aBase, 
										 CRef< Storable > S::*aField );
public: void store( StoreSession *aSession, FieldWriter *aWriter );
public: void retrieve( StoreSession *aSession, FieldReader *aReader );
};


END_QR_NAMESPACE

#if defined( INCLUDE_TEMPLATES )
#include "src/store/DefField.tpp"
#endif

/*
 * $Log: DefField.hpp,v $
 * Revision 1.1  2000/09/21 16:46:01  philogelos
 * Persistency sub-system (first draft). Store only.
 *
 */

/* __DEFFIELD_HPP__ */
#endif
