// -*-C++-*- 

/*  inc/algorithms/parse/Identifier.hpp  */

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



#ifndef __IDENTIFIER_HPP__
#define __IDENTIFIER_HPP__

/* $Id: Identifier.hpp,v 1.1.1.1 2000/07/19 16:58:35 philogelos Exp $ */

#include "TokenFactory.hpp"
#include "Object.hpp"
#include "defines.h"

BEGIN_QR_NAMESPACE

/**

   @author Philogelos
   @created Sun Apr 30 04:04:40 2000
*/
class Identifier : public virtual TokenFactory,
				   public virtual Object
{

  /**
   */
public: Identifier();

/**
*/
public: virtual ~Identifier();

public: virtual boolean canStartHere( TokenCradle *aCradle ) const;
public: virtual void grow( TokenCradle *aCradle );
public: virtual Token *graduate( TokenCradle *aCradle );

public: static boolean canStartIdentifier( const unichar aChar );
public: static boolean canContinueIdentifier( const unichar aChar );
public: static boolean isLetter( const unichar aChar );
public: static boolean isDigit( const unichar aChar );

protected: Index doInternal( TokenCradle *aCradle ) const;

  /**
   */
public:  virtual String  getClassName() const;

protected: static String letters;
protected: static String digits;
};

END_QR_NAMESPACE

/*
 * $Log: Identifier.hpp,v $
 * Revision 1.1.1.1  2000/07/19 16:58:35  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.1  2000/07/19 08:48:03  god
 * new parse method: ask all factories and accept one with longest match
 *
 */

/* __IDENTIFIER_HPP__ */
#endif
