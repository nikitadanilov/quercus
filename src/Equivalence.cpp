// -*-C++-*- 

/*  src/Equivalence.cpp  */

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



/* $Id: Equivalence.cpp,v 1.1 2001/04/13 19:32:35 philogelos Exp $ */
#if !defined( _INLINE )
static char cvsid[] = "@(#)$Id: Equivalence.cpp,v 1.1 2001/04/13 19:32:35 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif

#include "Equivalence.hpp"
#include "String.hpp"
#include "OGuard.hpp"
#include "Debug.hpp"

BEGIN_QR_NAMESPACE

boolean Equivalence::in( const Top *anObj1, const Top *anObj2 ) const
{
  OGuard _o1( anObj1, this );
  OGuard _o2( anObj2, this );

  return areEqual( anObj1, anObj2 );
}

DeltaRelation::DeltaRelation()
{}

DeltaRelation::~DeltaRelation()
{}

DeltaRelation *DeltaRelation::getDelta()
{
  if( *instance == NULL )
	{
	  instance = new DeltaRelation();
	}
  return *instance;
}

boolean DeltaRelation::areEqual( const Top *anObj1, const Top *anObj2 ) const
{
  OGuard _o1( anObj1, this );
  OGuard _o2( anObj2, this );

  return( anObj1 == anObj2 );
}

CRef< DeltaRelation > DeltaRelation::instance;

String  DeltaRelation::getClassName() const
{
  return "DeltaRelation";
}

TotalRelation::TotalRelation()
{}

TotalRelation::~TotalRelation()
{}

TotalRelation *TotalRelation::getTotal()
{
  if( *instance == NULL )
	{
	  instance = new TotalRelation();
	}
  return *instance;
}

boolean TotalRelation::areEqual( const Top *anObj1, const Top *anObj2 ) const
{
  OGuard _o1( anObj1, this );
  OGuard _o2( anObj2, this );

  return true;
}

CRef< TotalRelation > TotalRelation::instance;

String  TotalRelation::getClassName() const
{
  return "TotalRelation";
}

EqualsRelation::EqualsRelation()
{}

EqualsRelation::~EqualsRelation()
{}

EqualsRelation *EqualsRelation::getEquals()
{
  if( *instance == NULL )
	{
	  instance = new EqualsRelation();
	}
  return *instance;
}

boolean EqualsRelation::areEqual( const Top *anObj1, const Top *anObj2 ) const
{
  OGuard _o1( anObj1, this );
  OGuard _o2( anObj2, this );

  if( anObj1 != NULL )
	{
	  return anObj1 -> equals( anObj2 );
	}
  else
	{
	  /* NULL is equal to NULL and only to NULL by any other name. */
	  return( anObj2 == NULL );
	}
}

CRef< EqualsRelation > EqualsRelation::instance;

String  EqualsRelation::getClassName() const
{
  return "EqualsRelation";
}

END_QR_NAMESPACE

#if defined( _INLINE )
#include "../src/Debug.ipp"
#endif


/*
 * $Log: Equivalence.cpp,v $
 * Revision 1.1  2001/04/13 19:32:35  philogelos
 * Classes for various equivalence relations (sameness, total relation, relation based on ::equals() method)
 *
 */
