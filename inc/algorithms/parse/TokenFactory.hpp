// -*-C++-*- 

/*  inc/algorithms/parse/TokenFactory.hpp  */

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



#ifndef __TOKENFACTORY_HPP__
#define __TOKENFACTORY_HPP__

/* $Id: TokenFactory.hpp,v 1.3 2000/09/19 18:20:08 philogelos Exp $ */

#include "Top.hpp"
#include "defines.h"
#include "Recongnizer.hpp"

BEGIN_QR_NAMESPACE

class TokenCradle;
class Token;

/**

   @author Philogelos
   @created Sun Apr 30 01:41:09 2000
*/
interface TokenFactory : public virtual Recognizer
{
 public: virtual Index accept( TokenCradle *aCradle ) const = 0;
 public: virtual Token *graduate( TokenCradle *aCradle, Index aLength );

 public: virtual boolean accepts( const Top *const anObject ) const;

 protected: virtual Token *getMatrix() const;
 protected: virtual Top   *getTokenTag() const;
};

END_QR_NAMESPACE

/*
 * $Log: TokenFactory.hpp,v $
 * Revision 1.3  2000/09/19 18:20:08  philogelos
 * Lexer and parser redone.
 *
 * Revision 1.2  2000/08/26 13:26:57  philogelos
 * New simple parser framework done. Compiles and passes Parser::tester()
 *
 * Revision 1.1.1.1  2000/07/19 16:58:32  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/07/19 08:48:03  god
 * new parse method: ask all factories and accept one with longest match
 *
 * Revision 1.1  2000/05/06 08:36:26  god
 * committed
 *
 */

/* __TOKENFACTORY_HPP__ */
#endif
