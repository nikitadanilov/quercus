// -*-C++-*- 

/*  inc/Relation.hpp  */

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



#ifndef __RELATION_HPP__
#define __RELATION_HPP__

/* $Id: Relation.hpp,v 1.2 2001/06/23 12:18:52 philogelos Exp $ */

#include "Object.hpp"
#include "Top.hpp"
#include "defines.h"

BEGIN_QR_NAMESPACE

interface Container;
interface Enumeration;

/**
   Interface for various relations.

   @author Philogelos
   @created Fri Apr 13 19:43:11 2001
*/
interface Relation : public virtual Top
{
  /** Returns true iff all elements of given container are 
	  in this relation (to each other). */
 public: virtual boolean areElementsIn( const Container *anObjects ) const;

  /** Returns true iff all elements of given enumeration are 
	  in this relation (to each other). */
 public: virtual boolean areIn( Enumeration *anElements ) const = 0;

 public: static Relation *getTruthValue( boolean aValue );
};

class TruthValueRel : public virtual Relation, public virtual Object
{
public: TruthValueRel( boolean aTruthValue );
public: virtual boolean areIn( Enumeration *anElements ) const;

protected: boolean truthValue;
};

END_QR_NAMESPACE

/*
 * $Log: Relation.hpp,v $
 * Revision 1.2  2001/06/23 12:18:52  philogelos
 * ::getTruthValue() and class TruthValueRel added
 *
 * Revision 1.1  2001/04/13 19:29:45  philogelos
 * Relations added
 *
 */

/* __RELATION_HPP__ */
#endif
