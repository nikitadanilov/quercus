// -*-C++-*- 

/*  src/algorithms/string/IdentityFilter.cpp  */

/*
 * Author: Philogelos A. <Philogelos@yahoo.com>
 * Maintainer: Philogelos A.
 * Keywords: C++, library, containers
 *
 * Copyright (C) 1999 Philogelos A.
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



/* $Id: IdentityFilter.cpp,v 1.1.1.1 2000/07/19 16:44:35 philogelos Exp $ */
#if !defined(_INLINE)
static char cvsid[] = "@(#)$Id: IdentityFilter.cpp,v 1.1.1.1 2000/07/19 16:44:35 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif

#include "algorithms/string/IdentityFilter.hpp"
#include "Debug.hpp"

BEGIN_QR_NAMESPACE

IdentityFilter::IdentityFilter( String aString ) :
  StringFilterAdapter( ( StringFilter * ) NIL ),
  support( aString )
{}

IdentityFilter::~IdentityFilter()
{}

String IdentityFilter::asString()
{
  return support;
}

String IdentityFilter::restAsString()
{
  return support.clip( position, support.length() );
}

Index IdentityFilter::length()
{
  return support.length();
}

Index IdentityFilter::rest()
{
  return length() - position;
}

unichar IdentityFilter::getNext()
{
  if( position < support.length() )
	{
	  return support.getUNIChars()[ ++position ];
	}
  else
	{
	  return ( unichar ) 0;
	}
}

String  IdentityFilter::getClassName() const
{
  return "IdentityFilter";
}

END_QR_NAMESPACE

#if defined(_INLINE)
#include "../src/Debug.ipp"
#endif


/*
 * $Log: IdentityFilter.cpp,v $
 * Revision 1.1.1.1  2000/07/19 16:44:35  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:40  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:30  god
 * Imported sources
*/
