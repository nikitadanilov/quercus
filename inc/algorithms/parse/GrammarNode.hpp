// -*-C++-*- 

/*  inc/algorithms/parse/GrammarNode.hpp  */

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



#ifndef __GRAMMARNODE_HPP__
#define __GRAMMARNODE_HPP__

/* $Id: GrammarNode.hpp,v 1.2 2001/06/09 15:02:18 philogelos Exp $ */

#include "CRef.hpp"
#include "String.hpp"
#include "Object.hpp"
#include "defines.h"
#include "Map.hpp"

BEGIN_QR_NAMESPACE

class LookAheadEnumeration;
class Map;

class ParseError;

/**

   @author Philogelos
   @created Sun Sep 10 17:40:23 2000
*/
abstract class GrammarNode : public virtual Object
{

public:  GrammarNode( String aName, Map *aTransformer = NULL );

public:  virtual void parse( LookAheadEnumeration *aStream ) 
  THROWS( ParseError * ) = 0;

public: virtual Top *getResult() const;
public:  virtual String getName() const;

public: virtual Map *getTransformer() const;
public: virtual void setTransformer( Map *aMap );

public: virtual String toString() const;
public: virtual String getString() const;

protected: const String name;
protected: CRef< Top > parseResult;
protected: CRef< Map > transformer;

#if defined( TESTING )
public:  static boolean testerGrammarNode( int aParam );
#endif
};

END_QR_NAMESPACE

/*
 * $Log: GrammarNode.hpp,v $
 * Revision 1.2  2001/06/09 15:02:18  philogelos
 * GrammarNode::getResult() and ::[gs]etTransformer() added to the
 * interface and implemented in all nodes.
 *
 * Revision 1.1  2000/09/19 18:20:07  philogelos
 * Lexer and parser redone.
 *
 */

/* __GRAMMARNODE_HPP__ */
#endif
