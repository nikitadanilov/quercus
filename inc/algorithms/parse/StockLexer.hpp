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

/* $Id: StockLexer.hpp,v 1.2 2000/10/12 21:28:17 philogelos Exp $ */

#include "Lexer.hpp"
#include "defines.h"
#include "CRef.hpp"

BEGIN_QR_NAMESPACE

class Terminal;
class NumericalLiteral;
class Identifier;
class Comment;

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

public: virtual Terminal *getComment() const;
public: virtual Comment  *getCommentToken() const;

  /**
   */
public: virtual ~StockLexer();

  /**
   */
public:  virtual String  getClassName() const;

protected: CRef< Terminal > comma;
protected: CRef< Terminal > dot;
protected: CRef< Terminal > colon;
protected: CRef< Terminal > semicolon;
protected: CRef< Terminal > lparen;
protected: CRef< Terminal > rparen;
protected: CRef< Terminal > lbrace;
protected: CRef< Terminal > rbrace;
protected: CRef< Terminal > lbracket;
protected: CRef< Terminal > rbracket;
protected: CRef< Terminal > id;
protected: CRef< Terminal > number;
protected: CRef< Terminal > comment;
protected: CRef< Comment >  commentToken;
};

END_QR_NAMESPACE

/*
 * $Log: StockLexer.hpp,v $
 * Revision 1.2  2000/10/12 21:28:17  philogelos
 * Comment token added
 *
 * Revision 1.1  2000/09/19 18:20:08  philogelos
 * Lexer and parser redone.
 *
 */

/* __STOCKLEXER_HPP__ */
#endif
