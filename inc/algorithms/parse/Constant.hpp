// -*-C++-*- 

/*  inc/algorithms/parse/Constant.hpp  */

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



#ifndef __CONSTRANT_HPP__
#define __CONSTRANT_HPP__

/* $Id: Constant.hpp,v 1.3 2000/09/19 18:20:07 philogelos Exp $ */

#include "TokenFactory.hpp"
#include "Object.hpp"
#include "defines.h"
#include "String.hpp"
#include "CRef.hpp"

BEGIN_QR_NAMESPACE

/**

   @author Philogelos
   @created Sun Apr 30 14:17:29 2000
*/
class Constant : public virtual TokenFactory,
				 public virtual Object
{

  /**
   */
public: Constant( String aString, Top *aTokenCore );

  /**
   */
public: virtual ~Constant();

public: virtual Index accept( TokenCradle *aCradle ) const;
public: virtual Top *getTokenTag() const;

protected: virtual Token *getMatrix() const;

  /**
   */
public:  virtual String  getClassName() const;

protected: CRef< Top > core;
protected: String string;
};

END_QR_NAMESPACE

/*
 * $Log: Constant.hpp,v $
 * Revision 1.3  2000/09/19 18:20:07  philogelos
 * Lexer and parser redone.
 *
 * Revision 1.2  2000/08/26 13:26:57  philogelos
 * New simple parser framework done. Compiles and passes Parser::tester()
 *
 * Revision 1.1.1.1  2000/07/19 16:58:45  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.1  2000/07/19 08:48:03  god
 * new parse method: ask all factories and accept one with longest match
 *
 */

/* __CONSTRANT_HPP__ */
#endif
