// -*-C++-*- 

/*  inc/algorithms/parse/Epsilon.hpp  */

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



#ifndef __EPSILON_HPP__
#define __EPSILON_HPP__

/* $Id: Epsilon.hpp,v 1.1 2000/09/19 18:20:07 philogelos Exp $ */

#include "GrammarNode.hpp"
#include "String.hpp"
#include "defines.h"
#include "CRef.hpp"

BEGIN_QR_NAMESPACE

/**

   @author Philogelos
   @created Sun Sep 10 20:51:44 2000
*/
class Epsilon : public GrammarNode
{

  /**
   */
public: Epsilon( String aName );

  /**
   */
public: virtual ~Epsilon();

protected:  virtual void parse( LookAheadEnumeration *aStream ) 
  THROWS( ParseError * );

public: static Epsilon *getEpsilon();

  /**
   */
public:  virtual String  getString() const;

  /**
   */
public:  virtual String  getClassName() const;

protected: static Epsilon *epsilon;
};

END_QR_NAMESPACE

/*
 * $Log: Epsilon.hpp,v $
 * Revision 1.1  2000/09/19 18:20:07  philogelos
 * Lexer and parser redone.
 *
 */

/* __EPSILON_HPP__ */
#endif
