// -*-C++-*- 

/*  src/BinaryRelation.cpp  */

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



/* $Id: BinaryRelation.cpp,v 1.1 2001/04/13 19:29:45 philogelos Exp $ */
#if !defined( _INLINE )
static char cvsid[] = "@(#)$Id: BinaryRelation.cpp,v 1.1 2001/04/13 19:29:45 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif

#include "BinaryRelation.hpp"
#include "iter/enumerations/Enumeration.hpp"
#include "OGuard.hpp"
#include "String.hpp"
#include "CRef.hpp"
#include "Debug.hpp"

BEGIN_QR_NAMESPACE

boolean BinaryRelation::areIn( Enumeration *anElements ) const
{
  preC_( anElements != NULL );
  preC_( anElements -> hasMoreElements() );
  OGuard _lmns( anElements, this );

  CRef< Top > o1;
  CRef< Top > o2;

  o1 = anElements -> getNextElement();
  test_( anElements -> hasMoreElements() );
  o2 = anElements -> getNextElement();
  test_( !anElements -> hasMoreElements() );
  return in( *o1, *o2 );
}

END_QR_NAMESPACE

#if defined( _INLINE )
#include "../src/Debug.ipp"
#endif


/*
 * $Log: BinaryRelation.cpp,v $
 * Revision 1.1  2001/04/13 19:29:45  philogelos
 * Relations added
 *
 */
