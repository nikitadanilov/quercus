// -*-C++-*- 

/*  inc/algorithms/parse/StockLexer.hpp  */

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



#ifndef __STOCKLEXER_HPP__
#define __STOCKLEXER_HPP__

/* $Id: StockLexer.hpp,v 1.1 2000/09/19 18:20:08 philogelos Exp $ */

#include "Lexer.hpp"
#include "defines.h"

BEGIN_QR_NAMESPACE

class Terminal;
class NumericalLiteral;
class Identifier;

/**

   @author Philogelos
   @created Mon Sep 11 23:13:20 2000
*/
class StockLexer : public Lexer
{
public: typedef enum { head, tail } Place;
  /**
   */
public: StockLexer( ParseStream *aStream );

public: virtual void addAt( TokenFactory *aFactory, Place aPlace );
public: virtual Terminal *addTerminal( String aName, String aValue, 
									   Place aPlace );
public: virtual Terminal *getTerminal( String aName, String aValue );
public: virtual Terminal *getComma() const;      /* , */
public: virtual Terminal *getDot() const;        /* . */
public: virtual Terminal *getColon() const;      /* : */
public: virtual Terminal *getSemicolon() const;  /* ; */
public: virtual Terminal *getLParen() const;     /* ( */
public: virtual Terminal *getRParen() const;     /* ) */
public: virtual Terminal *getLBrace() const;     /* { */
public: virtual Terminal *getRBrace() const;     /* } */
public: virtual Terminal *getLBracket() const;   /* [ */
public: virtual Terminal *getRBracket() const;   /* ] */

public: virtual Terminal *getId() const;
public: virtual Terminal *getNumber() const;

  /**
   */
public: virtual ~StockLexer();

  /**
   */
public:  virtual String  getClassName() const;

protected: static boolean   init;
protected: static Terminal *comma;
protected: static Terminal *dot;
protected: static Terminal *colon;
protected: static Terminal *semicolon;
protected: static Terminal *lparen;
protected: static Terminal *rparen;
protected: static Terminal *lbrace;
protected: static Terminal *rbrace;
protected: static Terminal *lbracket;
protected: static Terminal *rbracket;
protected: static Terminal *id;
protected: static Terminal *number;
};

END_QR_NAMESPACE

/*
 * $Log: StockLexer.hpp,v $
 * Revision 1.1  2000/09/19 18:20:08  philogelos
 * Lexer and parser redone.
 *
 */

/* __STOCKLEXER_HPP__ */
#endif
