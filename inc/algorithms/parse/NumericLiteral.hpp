// -*-C++-*- 

/*  inc/algorithms/parse/NumericLiteral.hpp  */

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



#ifndef __NUMERICLITERAL_HPP__
#define __NUMERICLITERAL_HPP__

/* $Id: NumericLiteral.hpp,v 1.2 2000/08/26 13:26:57 philogelos Exp $ */

#include "TokenFactory.hpp"
#include "Object.hpp"
#include "defines.h"

BEGIN_QR_NAMESPACE

/**

   @author Philogelos
   @created Sun Apr 30 18:54:38 2000
*/
class NumericLiteral : public virtual TokenFactory,
					   public virtual Object
{

  /**
   */
public: NumericLiteral();

  /**
   */
public: virtual ~NumericLiteral();

public: virtual Index accept( TokenCradle *aCradle ) const;

public: static boolean isDigitInBase( unichar aChar, Index aBase );
public: static Index getBase( unichar aChar );

/**
*/
public:  virtual String  getClassName() const;
};

END_QR_NAMESPACE

/*
 * $Log: NumericLiteral.hpp,v $
 * Revision 1.2  2000/08/26 13:26:57  philogelos
 * New simple parser framework done. Compiles and passes Parser::tester()
 *
 * Revision 1.1.1.1  2000/07/19 16:58:34  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.1  2000/07/19 08:48:03  god
 * new parse method: ask all factories and accept one with longest match
 *
 */

/* __NUMERICLITERAL_HPP__ */
#endif
