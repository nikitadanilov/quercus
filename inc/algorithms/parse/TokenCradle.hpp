// -*-C++-*- 

/*  inc/algorithms/parse/TokenCradle.hpp  */

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



#ifndef __TOKENCRADLE_HPP__
#define __TOKENCRADLE_HPP__

/* $Id: TokenCradle.hpp,v 1.2 2000/08/26 13:26:57 philogelos Exp $ */

#include "Object.hpp"
#include "defines.h"
#include "CRef.hpp"

BEGIN_QR_NAMESPACE

class ParseStream;
class StringBuffer;
class Position;
class Dictionary;

/**

   @author Philogelos
   @created Sun Apr 30 01:56:41 2000
*/
class TokenCradle : public virtual Object
{

  /**
   */
public: TokenCradle( ParseStream *aStream );

  /**
   */
public: virtual ~TokenCradle();

public: virtual unichar getAt( Index anIndex );
public: virtual boolean hasAt( Index anIndex );

public: virtual ParseStream *getStream() const;
public: virtual StringBuffer *getBuffer() const;

public: virtual void markStart();
public: virtual void markEnd();

public: virtual String pop( Index aLength );

public: virtual Dictionary *getAttributes() const;
  /**
   */
public:  virtual Top *clone() const;

  /**
   */
public:  virtual String  toString() const;

  /**
   */
public:  virtual String  getClassName() const;

protected: CRef< ParseStream > stream;
protected: CRef< StringBuffer > buffer;
protected: CRef< Position > start;
protected: CRef< Position > end;
protected: CRef< Dictionary > attributes;

protected: Index accepted;
};

END_QR_NAMESPACE

/*
 * $Log: TokenCradle.hpp,v $
 * Revision 1.2  2000/08/26 13:26:57  philogelos
 * New simple parser framework done. Compiles and passes Parser::tester()
 *
 * Revision 1.1.1.1  2000/07/19 16:58:35  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.1  2000/05/06 08:36:26  god
 * committed
 *
 */

/* __TOKENCRADLE_HPP__ */
#endif
