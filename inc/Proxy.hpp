// -*-C++-*- 

/*  inc/Proxy.hpp  */

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



#ifndef __PROXY_HPP__
#define __PROXY_HPP__

/* $Id: Proxy.hpp,v 1.2 2000/08/30 12:20:35 philogelos Exp $ */

#include "Top.hpp"
#include "CRef.hpp"
#include "defines.h"

BEGIN_QR_NAMESPACE

class AbstractFactory;

/**
   Proxy objects.

   @author Philogelos
   @created 2000-08-28
*/
template< class X > class Proxy : public virtual Object
{

  /**
   */
public: Proxy< X >( AbstractFactory *aFactory );

  /**
   */
public: virtual ~Proxy();

public: virtual X *getValue() const;
public: virtual X *operator -> () const;
public: virtual X *operator  = ( X *aTarget );
public: virtual X *operator  * () const;

  /**
   */
public:  virtual boolean equals( const Top *anOther) const;

  /**
   */
public:  virtual Top *clone() const;

  /**
   */
public:  virtual String  toString() const;

  /**
   */
public:  virtual String  getString() const;

  /**
   */
public:  virtual String  getClassName() const;

#if defined( TESTING )
public:  virtual boolean tester( int aParam ) const;
#endif

protected: CRef< X > core;
protected: CRef< AbstractFactory > factory;
};

END_QR_NAMESPACE

#if defined( INCLUDE_TEMPLATES )
#include "src/Proxy.tpp"
#endif

/*
 * $Log: Proxy.hpp,v $
 * Revision 1.2  2000/08/30 12:20:35  philogelos
 * THROWS clauses updates to correspond to the real throws.
 *
 * Revision 1.1  2000/08/29 17:48:07  philogelos
 * Proxy class for lazy object creation added.
 *
 */

/* __PROXY_HPP__ */
#endif
