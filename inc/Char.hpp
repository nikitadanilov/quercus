//-*-C++-*-

/*  inc/Char.hpp  */


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


#ifndef __CHAR_HPP__

#define __CHAR_HPP__
/* $Id: Char.hpp,v 1.1.1.1 2000/07/19 16:55:12 philogelos Exp $ */

#include "defines.h"
#include "Object.hpp"
#include "String.hpp"

BEGIN_QR_NAMESPACE

/** 
	Character. Interface for objects representing
	characters. Sub-classes probably will correspond
	to different coding schemas.

	@author Philogelos
	@created
*/
abstract class Char : virtual public Top
{
  /**
	 Returns fresh-allocated char array with
	 the bit pattern of this character.
  */
public:  virtual char   *toCChar() const = 0;

  /**
	 Returns string initialised with the bit-pattern of this
	 character.

	 @see #toCChar()
  */
public:  virtual String  asString() const;

  /**
	 Returns UTF8 representation of this character.
  */
public:  virtual char   *toUTF8() const = 0;

  /**
	 Returns UCS2 representation of this character.

	 @see unichar
  */
public:  virtual unichar          getUNICODE() const = 0;

  /**
	 Returns high byte of the UCS2 representation.
  */
public:  virtual unsigned char    getPage() const;

  /**
	 Returns low byte of the UCS2 representation.
  */
public:  virtual unsigned char    getOffset() const;

  /**
	 Checks that two characters are the same.
  */
public:  virtual boolean equals( const Top *anOther ) const;
};

END_QR_NAMESPACE


/*
 * $Log: Char.hpp,v $
 * Revision 1.1.1.1  2000/07/19 16:55:12  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.4  2000/04/09 12:00:47  god
 * CVS Log keyword correction finished
 *
 * Revision 1.3  2000/04/09 11:29:16  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.2  2000/04/01 14:22:46  god
 * Comments corrected (testing CVS setup actually).
 *
 * Revision 1.1.1.1  2000/04/01 14:07:37  god
 * Imported sources
 *
 * Revision 1.2  1999/03/03 19:09:01  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.1  1999/02/28 12:47:07  philogelos
 * *** empty log message ***
 * */

/* __CHAR_HPP__ */
#endif

