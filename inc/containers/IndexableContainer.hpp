// -*-C++-*- 

/*  inc/containers/IndexableContainer.hpp  */


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


#ifndef __INDEXABLECONTAINER_HPP__
#define __INDEXABLECONTAINER_HPP__

/* $Id: IndexableContainer.hpp,v 1.1.1.1 2000/07/19 16:59:23 philogelos Exp $ */

#include "MutableContainer.hpp"
#include "exceptions/InvalidArgument.hpp"
#include "defines.h"
#include "Map.hpp"

BEGIN_QR_NAMESPACE

interface IndexPosition;

/**
   Container with mapping from natural 
   numbers to positions.

   @author Philogelos
   @created ²âà 23 ¸îÝ 1998 19:37:13
*/
abstract class IndexableContainer : virtual public MutableContainer
{
public: virtual ~IndexableContainer();

  /**
	 Returns position at given index.

	 @precond ( isValidIndex( anIndex ) )
  */
public: virtual IndexPosition *getPosition( const Index anIndex );

 /**
	True iff index is within valid range.
 */
public: virtual boolean isValidIndex( const Index anIndex ) const = 0;

 /**
	@precond ( isValidIndex( anIndex ) )
	@invariant ergo( single thread, 
	  ( getAt( anIndex ) == getPosition( anIndex ) -> getValue() ) )
 */
public: virtual Top *getAt( const Index anIndex ) const = 0;
public: virtual Top *setAt( const Index anIndex, Top *aNewValue ) = 0;

public: virtual boolean   isValid ( const Position *aPosition ) const;

public: class InvalidIndex : public InvalidArgument
{
public:  InvalidIndex( String aMessage, const Top *const aSource );
public:  virtual String getDescription() const;
public:  virtual String  getClassName() const;
};

};

class PiMap : public Map,
			  public virtual Object
{
public: PiMap( const Index aProj );
public: virtual ~PiMap();
public: virtual void setProj( const Index aProj );

public: virtual Top *apply( Top *anArgument );

protected: Index projection;
};

END_QR_NAMESPACE

/*
 * $Log: IndexableContainer.hpp,v $
 * Revision 1.1.1.1  2000/07/19 16:59:23  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:33  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:44  god
 * Imported sources
 *
 * Revision 1.3  1999/03/03 19:09:09  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.2  1999/02/28 12:55:21  philogelos
 * class PiMap added
 *
 * Revision 1.1.1.1  1998/11/25 20:11:05  philogelos
 * Quercus Robusta
 *
 * Revision 1.1  1998/07/09 09:30:29  philogelos
 * new files added to the repository
 * */

/* __INDEXABLECONTAINER_HPP__ */
#endif
