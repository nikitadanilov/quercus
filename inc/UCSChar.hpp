//-*-C++-*-

/*  inc/UCSChar.hpp  */


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


#ifndef __UCSCHAR_HPP__

#define __UCSCHAR_HPP__
/* $Id: UCSChar.hpp,v 1.1.1.1 2000/07/19 16:58:07 philogelos Exp $ */

#include "Char.hpp"
#include "defines.h"
#include "Object.hpp"
#include "String.hpp"

BEGIN_QR_NAMESPACE



/** UNICODE character.
	Internally represented in UCS2.

	@author Philogelos
	@created
*/
class UCSChar : public Char,
				virtual public Object
{
public:  UCSChar( unichar aCode );
public:  UCSChar( const Char &aChar );
public:  UCSChar( char anOffset, char aPage = defaultUnicodePage );
public:  virtual ~UCSChar();

public:  virtual char   *toCChar() const;
public:  virtual char   *toUTF8() const;
public:  virtual unichar getUNICODE() const;
public:  virtual void    setUNICODE( unichar aCode );

public:  virtual void    setPage( unsigned char aPage );
public:  virtual void    setOffset( unsigned char anOffset );

public:  virtual unichar getCChar() const;

public:  virtual boolean equals( const Top *anOther ) const;

public:  virtual Top    *clone() const;

public:  virtual String  getString() const;

public:  virtual String  getClassName() const;

#if defined( TESTING )
public:  virtual boolean tester( int aParam ) const;
#endif

public:  static  char    defaultUnicodePage;
protected: unichar code;
};

END_QR_NAMESPACE

/*
 * $Log: UCSChar.hpp,v $
 * Revision 1.1.1.1  2000/07/19 16:58:07  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:17  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:38  god
 * Imported sources
 *
 * Revision 1.2  1999/03/03 19:09:05  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.1  1999/02/28 12:47:08  philogelos
 * *** empty log message ***
 * */

/* __UCSCHAR_HPP__ */
#endif

