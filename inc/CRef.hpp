// -*-C++-*- 

/*  inc/CRef.hpp  */

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



#ifndef __CREF_HPP__
#define __CREF_HPP__

/* $Id: CRef.hpp,v 1.1.1.1 2000/07/19 16:55:11 philogelos Exp $ */

#include "Object.hpp"
#include "defines.h"

BEGIN_QR_NAMESPACE

/**
   Like STD auto_ptr.

   @author Philogelos
   @created
*/
template < class X > class CRef : public Object
{

public: CRef< X >();
  /**
   */
public: CRef< X >( X *aTarget, 
				   boolean isNullable = false,
				   boolean mustLock = false,
				   boolean mustRecycle = true,
				   boolean mustLink = true );

  /**
   */
public: virtual ~CRef();


public: virtual void setValue( X *aTarget );
public: virtual X *getValue() const;
public: virtual X *operator -> () const;
public: virtual X *operator  = ( X *aTarget );
public: virtual X *operator  * () const;

  /**
   */
public:  virtual boolean equals( const Top *anOther ) const;

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

protected: void done();
protected: void init( X *aTarget );

protected: X *target;
protected: boolean canBeNull :1;
protected: boolean lock :1;  
protected: boolean link :1;  
protected: boolean recycle :1;  
};

END_QR_NAMESPACE


#if defined( INCLUDE_TEMPLATES )
#include "src/CRef.tpp"
#endif

/*
 * $Log: CRef.hpp,v $
 * Revision 1.1.1.1  2000/07/19 16:55:11  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.5  2000/04/09 12:00:46  god
 * CVS Log keyword correction finished
 *
 * Revision 1.4  2000/04/09 11:29:16  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.3  2000/04/06 11:53:40  god
 * default constructor and ::operator * added
 *
 * Revision 1.2  2000/04/05 17:19:20  god
 * Dynamic modules, askUser (+readline) dlsym/dladdr-based Backtrace
 *
 * Revision 1.1.1.1  2000/04/01 14:07:39  god
 * Imported sources
 * */

/* __CREF_HPP__ */
#endif
