// -*-C++-*- 

/*  inc/algorithms/parse/Parser.hpp  */

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



#ifndef __PARSER_HPP__
#define __PARSER_HPP__

/* $Id: Parser.hpp,v 1.2 2000/08/30 12:20:35 philogelos Exp $ */

#include "Object.hpp"
#include "CRef.hpp"
#include "defines.h"
#include "Token.hpp"

BEGIN_QR_NAMESPACE

class List;
class ParseStream;
class TokenCradle;
class TokenFactory;
class Token;

class ParseError;

/**

   @author Philogelos
   @created Sun Apr 30 02:48:56 2000
*/
class Parser : public TokenEnumeration,
			   public virtual Object
{

  /**
   */
public: Parser( ParseStream *aStream );

  /**
   */
public: virtual ~Parser();

public: virtual void add( TokenFactory *aFactory );

public: virtual Token *getNextToken() THROWS( ParseError * );
public: virtual Token *getNextTypedElement();
public: virtual boolean hasMoreElements();

  /**
   */
public:  virtual String  getClassName() const;

protected: CRef< TokenCradle > cradle;
protected: CRef< List > factory;

#if defined( TESTING )
public:  virtual boolean tester( int aParam ) const;
#endif
};

END_QR_NAMESPACE

/*
 * $Log: Parser.hpp,v $
 * Revision 1.2  2000/08/30 12:20:35  philogelos
 * THROWS clauses updates to correspond to the real throws.
 *
 * Revision 1.1.1.1  2000/07/19 16:58:45  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.1  2000/07/19 08:48:03  god
 * new parse method: ask all factories and accept one with longest match
 *
 */

/* __PARSER_HPP__ */
#endif
