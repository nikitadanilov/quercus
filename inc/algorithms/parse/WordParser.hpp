// -*-C++-*- 

/*  inc/algorithms/parse/WordParser.hpp  */

/*
 * Author: Philogelos A. <Philogelos@yahoo.com>
 * Maintainer: Philogelos A.
 * Keywords: C++, library, containers
 *
 * Copyright (C) 1998, 1999 Philogelos A.
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



#ifndef __WORDPARSER_HPP__
#define __WORDPARSER_HPP__

/* $Id: WordParser.hpp,v 1.1.1.1 2000/07/19 16:58:32 philogelos Exp $ */

#include "UCSChar.hpp"
#include "Token.hpp"
#include "defines.h"
#include "iter/enumerations/TypedEnumeration.hpp"

BEGIN_QR_NAMESPACE

abstract class CharEnumeration : public virtual TypedEnumeration< Char >
{
public: CharEnumeration();
public: virtual ~CharEnumeration();
  
public: virtual Char *getNextTypedElement();
public: virtual Char *getNextCharFast() = 0;
 
protected: UCSChar *current;
};

interface Container;
interface Position;
interface Token;
interface Char;
class List;

class NoEntity;


/**

   @author Philogelos
   @created
*/
class WordParser : public TokenEnumeration,
				   virtual public Object
{

  /**
   */
public: WordParser( CharEnumeration *aSource );

public: void addSyntaxEntry( Container *anAlphabet, Token *aPrototype );
public: void addDefaultEntry( Token *aPrototype );

public: void removeSyntaxEntry( Container *anAlphabet ) THROWS( NoEntity * );

  /**
   */
public: virtual ~WordParser();

public: virtual Token *getNextToken();
public: virtual Token *getNextTypedElement();

public: virtual boolean hasMoreElements();

  /**
   */
public:  virtual boolean equals( const Top *anOther ) const;

  /**
   */
public:  virtual Top *clone() const;

  /**
   */
public:  virtual String  getClassName() const;

protected: Index findIndex( Char *aLetter );

#if defined( TESTING )
public: virtual boolean tester( int aParam ) const;
#endif

protected: List *prototypes;
protected: List *alphabets;

protected: Token *defToken;

protected: CharEnumeration *source;
protected: Char      *readChar;
  /* -1 means default */
protected: Index current;
};

END_QR_NAMESPACE

/*
 * $Log: WordParser.hpp,v $
 * Revision 1.1.1.1  2000/07/19 16:58:32  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:17  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:43  god
 * Imported sources
 *
 * Revision 1.2  1999/03/03 19:09:08  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.1  1999/02/28 12:50:48  philogelos
 * Parser classes added
 * */

/* __WORDPARSER_HPP__ */
#endif

