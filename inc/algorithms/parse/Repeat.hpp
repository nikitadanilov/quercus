// -*-C++-*- 

/*  inc/algorithms/parse/Repeat.hpp  */

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



#ifndef __REPEAT_HPP__
#define __REPEAT_HPP__

/* $Id: Repeat.hpp,v 1.1 2000/09/19 18:20:08 philogelos Exp $ */

#include "GrammarNode.hpp"
#include "Object.hpp"
#include "defines.h"
#include "CRef.hpp"

BEGIN_QR_NAMESPACE

/**

   @author Philogelos
   @created Mon Sep 11 19:52:27 2000
*/
class Repeat : public GrammarNode
{

public: static const Index infinity;

  /**
   */
public: Repeat( String aName, 
				Index aMin, Index aMax, 
				GrammarNode *aBody );
  /**
   */
public: virtual ~Repeat();

public:  virtual void parse( LookAheadEnumeration *aStream ) 
  THROWS( ParseError * );

  /**
   */
public:  virtual String  getString() const;

  /**
   */
public:  virtual String  getClassName() const;

protected: CRef< GrammarNode > body;
protected: Index min;
protected: Index max;
};

END_QR_NAMESPACE

/*
 * $Log: Repeat.hpp,v $
 * Revision 1.1  2000/09/19 18:20:08  philogelos
 * Lexer and parser redone.
 *
 */

/* __REPEAT_HPP__ */
#endif
