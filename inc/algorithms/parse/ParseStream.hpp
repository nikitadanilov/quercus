// -*-C++-*- 

/*  inc/algorithms/parse/ParseStream.hpp  */

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



#ifndef __PARSESTREAM_HPP__
#define __PARSESTREAM_HPP__

/* $Id: ParseStream.hpp,v 1.2 2000/09/19 18:20:07 philogelos Exp $ */

#include "WordParser.hpp"
#include "Object.hpp"
#include "defines.h"
#include "CRef.hpp"

BEGIN_QR_NAMESPACE

class CharEnumeration;
class Stack;
class Char;
class Position;

/**

   @author Philogelos
   @created Sun Apr 30 01:44:49 2000
*/
class ParseStream : public virtual CharEnumeration,
					public virtual Object
{

  /**
   */
public: ParseStream( CharEnumeration *aChars );

  /**
   */
public: virtual ~ParseStream();

public: virtual Char *getCharFast();
public: virtual Char *getChar();
public: virtual Char *getTop();
public: virtual void  ungetChar( Char *aChar );

public: virtual boolean startWithChar( Char *aChar );
public: virtual boolean startWithString( String aString );
public: virtual boolean isEOF() const;

  /* Returns trivial position indication: offset from the 
	 beginning of the stream. Override in sub-classes. */
public: virtual Position *getCurrentMark() const;
public: virtual CharEnumeration *getChars() const;

public: virtual Char *getNextCharFast();
public: virtual boolean hasMoreElements();

  /**
   */
public:  virtual String  getClassName() const;

protected: CRef< CharEnumeration > chars;
protected: CRef< Stack > pushBack;

protected: Index mark;
};

END_QR_NAMESPACE

/*
 * $Log: ParseStream.hpp,v $
 * Revision 1.2  2000/09/19 18:20:07  philogelos
 * Lexer and parser redone.
 *
 * Revision 1.1.1.1  2000/07/19 16:58:34  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.1  2000/05/06 08:36:26  god
 * committed
 *
 */

/* __PARSESTREAM_HPP__ */
#endif
