// -*-C++-*- 

/*  inc/StringBuffer.hpp  */

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



#ifndef __STRINGBUFFER_HPP__
#define __STRINGBUFFER_HPP__

/* $Id: StringBuffer.hpp,v 1.2 2000/09/21 18:00:44 philogelos Exp $ */

#include "Object.hpp"
#include "defines.h"

BEGIN_QR_NAMESPACE

class String;
class Char;
/**

   @author Philogelos
   @created
*/
class StringBuffer : virtual public Object
{

  /**
   */
public: StringBuffer( Index aLength = defaultLength, 
					  Index aDelta = defaultDelta );

public: virtual ~StringBuffer();

public: virtual void add( unichar aChar );
public: virtual void add( Char *aChar );
public: virtual void add( unichar *aChar );
public: virtual void add( String aString );

public: virtual String asString() const;

public: virtual Index getLength() const;
public: virtual unichar getAt( Index anIndex ) const;
  
public: static Index defaultLength;
public: static Index defaultDelta;
  
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
public:  virtual String  getClassName() const;

protected: void init( Index aLength, Index aDelta );
  
protected: unichar *buffer;
protected: Index length;
protected: Index used;
protected: Index delta;
};

END_QR_NAMESPACE

/*
 * $Log: StringBuffer.hpp,v $
 * Revision 1.2  2000/09/21 18:00:44  philogelos
 * default constructor
 *
 * Revision 1.1.1.1  2000/07/19 16:57:28  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.3  2000/04/29 23:48:33  god
 * getLength() and getAt() added
 *
 * Revision 1.2  2000/04/09 11:29:17  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:39  god
 * Imported sources
*/

/* __STRINGBUFFER_HPP__ */
#endif
