//-*-C++-*-

/*  inc/Integer.hpp  */


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


#ifndef __INTEGER_HPP__

#define __INTEGER_HPP__

/* $Id: Integer.hpp,v 1.1.1.1 2000/07/19 16:55:57 philogelos Exp $ */

#include "defines.h"
#include "Object.hpp"

BEGIN_QR_NAMESPACE

class DivideByZero;
/** Wrapper around native (long) integer
	type (for now).

	Plans are to make this interface with 
	LISP-type integers behind.

	@author Philogelos
	@created
*/
class Integer : public Object
{
  /**
	 Creates instance from native integer.

	 @postcond ( getInt() == anInt )
  */
public:  Integer( Index anInt );

  /**
	 Copy constructor.

	 @postcond ( getInt() == anInteger.getInt() )
  */
public:  Integer( const Integer &anInteger );

  /**
	 Returns native integer corresponding to this
	 instance. Should throw RuntimeError is
	 instance cannot be represented in native format.
	 
	 @see RuntimeError
  */
public:  virtual Index getInt() const;

  /**
	 Modifies this object to correspond to the given native integer.

	 @postcond ( getInt() == anInt )
  */
public:  virtual void  setInt( Index anInt );

  /**
	 Returns object representing zero.

	 @postcond ( Result.getInt() == 0 );
  */
public:  static  const Integer *getZero();

  /**
	 Returns newly allocated next integer.

	 @postcond ( Result.getInt() == getInt() + 1 )
  */
public:  virtual Integer *next() const;

  /**
	 Increments this object.
  */
public:  virtual void     inc();

  /**
	 Returns true only if this object represents integer 0.
  */
public:  virtual boolean  isZero() const;

  /*
	As a general side note: operators considered harmful.
  */

public:  virtual Integer *add( const Integer *aTerm ) const;
public:  virtual Integer *sub( const Integer *aTerm ) const;
public:  virtual Integer *mul( const Integer *aTerm ) const;
public:  virtual Integer *div( const Integer *aTerm ) const THROWS( DivideByZero * );

public:  virtual boolean equals( const Top *anOther ) const;

public:  virtual Top    *clone() const;

public:  virtual String  getString() const;

public:  virtual String  getClassName() const;

public:  virtual boolean invariant() const;

#if defined( TESTING )
public:  virtual boolean tester( int aParam ) const;
#endif

protected: Index core;

static const Integer *zero;
};

END_QR_NAMESPACE

/*
 * $Log: Integer.hpp,v $
 * Revision 1.1.1.1  2000/07/19 16:55:57  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.3  2000/05/06 08:36:26  god
 * committed
 *
 * Revision 1.2  2000/04/09 11:29:16  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:38  god
 * Imported sources
 *
 * Revision 1.2  1999/03/03 19:09:02  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.1  1999/02/28 12:47:07  philogelos
 * *** empty log message ***
 * */

/* __INTEGER_HPP__ */
#endif

