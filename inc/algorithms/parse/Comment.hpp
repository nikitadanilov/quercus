// -*-C++-*- 

/*  inc/algorithms/parse/Comment.hpp  */

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



#ifndef __COMMENT_HPP__
#define __COMMENT_HPP__

/* $Id: Comment.hpp,v 1.2 2000/10/11 19:51:11 philogelos Exp $ */

#include "TokenFactory.hpp"
#include "String.hpp"
#include "Object.hpp"
#include "defines.h"

BEGIN_QR_NAMESPACE

/**

   @author Philogelos
   @created Thu Sep 21 21:22:00 2000
*/
class Comment : public virtual TokenFactory,
				public virtual Object
{
public: Comment( String aStart, String anEnd, boolean canNest );
public: virtual ~Comment();

public: virtual Index accept( TokenCradle *aCradle ) const;
public: virtual String  getClassName() const;

public: virtual void setStart( String aStart );
public: virtual void setEnd( String anEnd );
public: virtual void setNest( boolean canNest );

public: virtual String  getStart() const;
public: virtual String  getEnd() const;
public: virtual boolean getNest() const;
 
protected: virtual boolean startsHere( TokenCradle *aCradle, Index aPos ) const;
protected: virtual boolean endsHere( TokenCradle *aCradle, Index aPos ) const;
protected: virtual boolean startsWith( TokenCradle *aCradle, 
									   Index aPos, String aString ) const;

protected: String  start;
protected: String  end;
protected: boolean nest;
};

END_QR_NAMESPACE

/*
 * $Log: Comment.hpp,v $
 * Revision 1.2  2000/10/11 19:51:11  philogelos
 * set/get methods added
 *
 * Revision 1.1  2000/09/21 18:34:02  philogelos
 * minor changes.
 *
 */

/* __COMMENT_HPP__ */
#endif
