// -*-C++-*- 

/*  inc/Equivalence.hpp  */

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



#ifndef __EQUIVALENCE_HPP__
#define __EQUIVALENCE_HPP__

/* $Id: Equivalence.hpp,v 1.1 2001/04/13 19:32:35 philogelos Exp $ */

#include "Object.hpp"
#include "Top.hpp"
#include "defines.h"
#include "CRef.hpp"
#include "BinaryRelation.hpp"

BEGIN_QR_NAMESPACE

/**
   Interface for implementors of various equivalence relations.

   @author Philogelos
   @created Fri Apr 13 15:13:37 2001
*/
abstract class Equivalence : public virtual BinaryRelation
{
 public: virtual boolean areEqual( const Top *anObj1, 
								   const Top *anObj2 ) const = 0;
 public: virtual boolean in( const Top *anObj1, const Top *anObj2 ) const;
};

/** Minimal equivalence relation. Object is equivalent only to itself. */
class DeltaRelation : public virtual Equivalence,
					  public virtual Object
{
public: DeltaRelation();
public: virtual ~DeltaRelation();
public: static DeltaRelation *getDelta();
public: virtual boolean areEqual( const Top *anObj1, const Top *anObj2 ) const;

public: virtual String  getClassName() const;
protected: static CRef< DeltaRelation > instance;
};

/** Maximal equivalence relation. All object are equal, and nobody
	is more equal. */
class TotalRelation : public virtual Equivalence,
					  public virtual Object
{
public: TotalRelation();
public: virtual ~TotalRelation();
public: static TotalRelation *getTotal();
public: virtual boolean areEqual( const Top *anObj1, const Top *anObj2 ) const;

public: virtual String  getClassName() const;
protected: static CRef< TotalRelation > instance;
};

/** Equivalence relation based on Top::equals() method. */
class EqualsRelation : public virtual Equivalence,
					   public virtual Object
{
public: EqualsRelation();
public: virtual ~EqualsRelation();
public: static EqualsRelation *getEquals();
public: virtual boolean areEqual( const Top *anObj1, const Top *anObj2 ) const;

public: virtual String  getClassName() const;
protected: static CRef< EqualsRelation > instance;
};

END_QR_NAMESPACE

/*
 * $Log: Equivalence.hpp,v $
 * Revision 1.1  2001/04/13 19:32:35  philogelos
 * Classes for various equivalence relations (sameness, total relation, relation based on ::equals() method)
 *
 */

/* __EQUIVALENCE_HPP__ */
#endif
