// -*-C++-*- 

/*  inc/algorithms/parse/TokenAdapter.hpp  */

/*
 * Author: Philogelos A. <Philogelos@yahoo.com>
 * Maintainer: Philogelos A.
 * Keywords: C++, library, containers
 *
 * Copyright (C) 1998, 1999 Philogelos A.
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



#ifndef __TOKENADAPTER_HPP__
#define __TOKENADAPTER_HPP__

/* $Id: TokenAdapter.hpp,v 1.1.1.1 2000/07/19 16:58:31 philogelos Exp $ */

#include "Token.hpp"
#include "containers/Pair.hpp"
#include "defines.h"
#include "CRef.hpp"


BEGIN_QR_NAMESPACE

/**

   @author Philogelos
   @created
*/
class TokenAdapter : public Token,
					 virtual public Pair
{

  /**
   */
public: TokenAdapter();

  /**
   */
public: virtual ~TokenAdapter();

public: virtual void setCore( Top *aValue );
public: virtual Top *getCore() const;

public: virtual void setTag( ParseTag *aTag );
public: virtual ParseTag *getTag() const;

  /**
   */
public:  virtual boolean equals( const Top *anOther ) const;

public: virtual Token *cloneToken() const;

  /**
   */
public:  virtual Top *clone() const;

  /**
   */
public:  virtual String  getString() const;

  /**
   */
public:  virtual String  getClassName() const;
};

END_QR_NAMESPACE

/*
 * $Log: TokenAdapter.hpp,v $
 * Revision 1.1.1.1  2000/07/19 16:58:31  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.3  2000/05/06 08:36:26  god
 * committed
 *
 * Revision 1.2  2000/04/09 11:29:17  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:43  god
 * Imported sources
 *
 * Revision 1.2  1999/03/03 19:09:07  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.1  1999/02/28 12:50:47  philogelos
 * Parser classes added
 * */

/* __TOKENADAPTER_HPP__ */
#endif
