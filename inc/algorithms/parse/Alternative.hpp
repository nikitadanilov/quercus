// -*-C++-*- 

/*  inc/algorithms/parse/Alternative.hpp  */

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



#ifndef __ALTERNATIVE_HPP__
#define __ALTERNATIVE_HPP__

/* $Id: Alternative.hpp,v 1.2 2001/06/09 15:02:18 philogelos Exp $ */

#include "containers/Container.hpp"
#include "UnableToParse.hpp"
#include "GrammarNode.hpp"
#include "Object.hpp"
#include "defines.h"
#include "CRef.hpp"

BEGIN_QR_NAMESPACE

/**

   @author Philogelos
   @created Sun Sep 10 18:37:18 2000
*/
class Alternative : public GrammarNode
{

  /**
   */
public: Alternative( String aName, Container *aBranch );

  /**
   */
public: virtual ~Alternative();

public:  virtual void parse( LookAheadEnumeration *aStream ) 
  THROWS( ParseError * );

public: virtual GrammarNode *getSelected() const;

  /**
   */
public:  virtual String  getString() const;

  /**
   */
public:  virtual String  getClassName() const;

protected: CRef< Container > branches;
protected: CRef< GrammarNode > selected;
};

class AlternativesExhausted : public virtual UnableToParse
{
public:  AlternativesExhausted( String aMessage, const Top *const aSource );
public:  virtual String getClassName() const;
public:  virtual String getDescription() const;
};

END_QR_NAMESPACE

/*
 * $Log: Alternative.hpp,v $
 * Revision 1.2  2001/06/09 15:02:18  philogelos
 * GrammarNode::getResult() and ::[gs]etTransformer() added to the
 * interface and implemented in all nodes.
 *
 * Revision 1.1  2000/09/19 18:20:07  philogelos
 * Lexer and parser redone.
 *
 */

/* __ALTERNATIVE_HPP__ */
#endif
