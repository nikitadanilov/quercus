// -*-C++-*- 

/*  inc/algorithms/parse/ListOf.hpp  */

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



#ifndef __LISTOF_HPP__
#define __LISTOF_HPP__

/* $Id: ListOf.hpp,v 1.2 2001/06/09 14:50:28 philogelos Exp $ */

#include "Concatenation.hpp"
#include "GrammarNode.hpp"
#include "Object.hpp"
#include "defines.h"
#include "CRef.hpp"

BEGIN_QR_NAMESPACE

class List;

/**

   @author Philogelos
   @created Mon Sep 11 18:48:00 2000
*/
class ListOf : public GrammarNode
{

  /**
   */
public: ListOf( String aName, 
				boolean canBeEmpty,
				GrammarNode *aStart, 
				GrammarNode *aItem,
				GrammarNode *aDelimiter,
				GrammarNode *anEnd );

  /**
   */
public: virtual ~ListOf();

public:  virtual void parse( LookAheadEnumeration *aStream )
  THROWS( ParseError * );

protected: virtual boolean isHere( LookAheadEnumeration *aStream,
								   GrammarNode *aNode, List *aResults,
								   boolean aFatal );
  /**
   */
public:  virtual String  getClassName() const;

protected: CRef< GrammarNode > start;
protected: CRef< GrammarNode > item;
protected: CRef< GrammarNode > delimiter;
protected: CRef< GrammarNode > end;
protected: boolean emptyable;
};

END_QR_NAMESPACE

/*
 * $Log: ListOf.hpp,v $
 * Revision 1.2  2001/06/09 14:50:28  philogelos
 * ListOf made special GrammarNode like Alternative rather than
 * sub-class of Concatenation.
 *
 * Revision 1.1  2000/09/19 18:20:07  philogelos
 * Lexer and parser redone.
 *
 */

/* __LISTOF_HPP__ */
#endif
