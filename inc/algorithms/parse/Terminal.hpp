// -*-C++-*- 

/*  inc/algorithms/parse/Terminal.hpp  */

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



#ifndef __TERMINAL_HPP__
#define __TERMINAL_HPP__

/* $Id: Terminal.hpp,v 1.1 2000/09/19 18:20:08 philogelos Exp $ */

#include "UnableToParse.hpp"
#include "GrammarNode.hpp"
#include "Object.hpp"
#include "defines.h"
#include "CRef.hpp"

BEGIN_QR_NAMESPACE

class TokenFactory;
class Recognizer;

/**

   @author Philogelos
   @created Sun Sep 10 19:12:54 2000
*/
class Terminal : public virtual GrammarNode
{

  /**
   */
public: Terminal( String aName, Recognizer *aToken );

  /**
   */
public: virtual ~Terminal();

public: virtual Recognizer *getRecognizer() const;

protected:  virtual void parse( LookAheadEnumeration *aStream ) 
  THROWS( ParseError * );

  /**
   */
public:  virtual String  getString() const;

  /**
   */
public:  virtual String  getClassName() const;

protected: const CRef< Recognizer > token;
};

class WrongToken : public virtual UnableToParse
{
public: WrongToken( String aMessage, const Top *const aSource );
public: virtual String getClassName() const;
public: virtual String getDescription() const;
};

class EOSDuringParse : public virtual UnableToParse
{
public: EOSDuringParse( String aMessage, const Top *const aSource );
public: virtual String getClassName() const;
public: virtual String getDescription() const;
};

END_QR_NAMESPACE

/*
 * $Log: Terminal.hpp,v $
 * Revision 1.1  2000/09/19 18:20:08  philogelos
 * Lexer and parser redone.
 *
 */

/* __TERMINAL_HPP__ */
#endif
