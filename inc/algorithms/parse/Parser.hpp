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

/* $Id: Parser.hpp,v 1.4 2000/09/21 18:21:59 philogelos Exp $ */

#include "Object.hpp"
#include "defines.h"
#include "CRef.hpp"

BEGIN_QR_NAMESPACE

class GrammarNode;
class Lexer;

/**
   Recursive-descent parser.

   @author Philogelos
   @created Mon Sep 11 22:53:05 2000
*/
class Parser : public Object
{

  /**
   */
public: Parser( GrammarNode *aRoot, Lexer *aLexer );

  /**
   */
public: virtual ~Parser();

public: virtual void parse();

public: virtual void setRoot( GrammarNode *aRoot );
public: virtual GrammarNode *getRoot() const;

public: virtual void setLexer( Lexer *aLexer );
public: virtual Lexer *getLexer() const;

public: virtual Top    *clone() const;
public: virtual String  toString() const;
public: virtual String  getString() const;
public: virtual String  getClassName() const;

protected: CRef< GrammarNode > root;
protected: CRef< Lexer > lexer;
};

END_QR_NAMESPACE

/*
 * $Log: Parser.hpp,v $
 * Revision 1.4  2000/09/21 18:21:59  philogelos
 * wrapper around parsing classes
 *
 */

/* __PARSER_HPP__ */
#endif
