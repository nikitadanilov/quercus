// -*-C++-*- 

/*  inc/containers/IndexPosition.hpp  */


/*
 * Author: Philogelos A. <Philogelos@yahoo.com>
 * Maintainer: Philogelos A.
 * Keywords: C++, library, containers
 *
 * Copyright (C) 1998 Philogelos A.
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


#ifndef __INDEXPOSITION_HPP__
#define __INDEXPOSITION_HPP__

/* $Id: IndexPosition.hpp,v 1.2 2001/06/23 12:26:33 philogelos Exp $ */

#include "MutablePositionAdapter.hpp"
#include "defines.h"

BEGIN_QR_NAMESPACE

interface IndexableContainer;

/**
   Position within IndexableContainer. This position addresses slot
   just by indicating its index within IndexableContainer.


   @see IndexableContainer

   @author Philogelos
   @created ¡‡‘ 24 ∏Ó› 1998 13:49:38
*/
class IndexPosition : public MutablePositionAdapter,
					  public virtual Object
{

/**
   Creates position pointing to slot
   with given index.

   @param anIndex index of slot addressed by this position.
   @param aHost container within which slot is located.
*/
public: IndexPosition( const Index anIndex, 
					   IndexableContainer *aHost );
public: virtual ~IndexPosition();

  /** 
	  Returns index of slot addressed by this position.
  */
public: virtual Index getIndex() const;

public: virtual boolean   isValid () const;
public: virtual Top *getValue() const;
public: virtual Top *setValue( Top *aNewValue );

/**
*/
public:  virtual boolean equals( const Top *anOther ) const;

/**
*/
public:  virtual Top *clone() const;

/**
*/
public:  virtual String  getString() const;

/**
*/
public:  virtual String  getClassName() const;

protected: Index index_;
};

END_QR_NAMESPACE

/*
 * $Log: IndexPosition.hpp,v $
 * Revision 1.2  2001/06/23 12:26:33  philogelos
 * class and methods commented
 *
 * Revision 1.1.1.1  2000/07/19 16:59:22  philogelos
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
 * Revision 1.2  1999/02/28 12:54:43  philogelos
 * Sub-typed from Object
 *
 * Revision 1.1.1.1  1998/11/25 20:11:05  philogelos
 * Quercus Robusta
 *
 * Revision 1.1  1998/07/09 09:30:29  philogelos
 * new files added to the repository
 * */

/* __INDEXPOSITION_HPP__ */
#endif
