// -*-C++-*- 

/*  src/algorithms/access/Comparator.cpp  */

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



/* $Id: Comparator.cpp,v 1.1 2001/04/16 10:18:20 philogelos Exp $ */
#if !defined( _INLINE )
static char cvsid[] = "@(#)$Id: Comparator.cpp,v 1.1 2001/04/16 10:18:20 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif

#include "algorithms/access/Comparator.hpp"
#include "Debug.hpp"

BEGIN_QR_NAMESPACE

BinaryRelation *Comparator::getAsRelation( ComparisonRelation aRelation ) const
{
  return new ComparatorAsRelation( this, aRelation );
}

Comparator::ComparatorAsRelation::ComparatorAsRelation( Comparator *aComparator, 
														ComparisonRelation aRelation )
{
  preC_( aComparator != NULL );

  comparator = aComparator;
  relation = aRelation;
}

boolean Comparator::ComparatorAsRelation::in( const Top *anObj1, 
											  const Top *anObj2 ) const;
{
  ComparisonResult cmp;
  boolean result;

  cmp = comparator -> compare( anObj1, anObj2 );
  result = false;

  switch( relation )
	{
	case lessOrEqual:
	  result = ( cmp == equalTo );
	  /* fall through */
	case less:
	  result = result || ( cmp == lessThan );
	  break;
	case equal:
	  result = ( cmp == equalTo );
	  break;
	case greaterOrEqual:
	  result = ( cmp == equalTo );
	  /* fall through */
	case greater:
	  result = result || ( cmp == greaterThan );
	  break;
	default:
	  impossible_;
	}
  return result;
}

END_QR_NAMESPACE

#if defined( _INLINE )
#include "../src/Debug.ipp"
#endif


/*
 * $Log: Comparator.cpp,v $
 * Revision 1.1  2001/04/16 10:18:20  philogelos
 * ::getAsRelation() method to represent Comparator as order relation.
 * Now Comparators can be used (for example) by Container::contains()
 * method.
 *
 */
