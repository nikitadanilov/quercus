// -*-C++-*- 

/*  src/algorithms/string/OneOfFilter.cpp  */

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



/* $Id: OneOfFilter.cpp,v 1.1.1.1 2000/07/19 16:44:39 philogelos Exp $ */
#if !defined(_INLINE)
static char cvsid[] = "@(#)$Id: OneOfFilter.cpp,v 1.1.1.1 2000/07/19 16:44:39 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif

#include "algorithms/string/IdentityFilter.hpp"
#include "algorithms/string/OneOfFilter.hpp"
#include "platform/Platform.hpp"
#include "Debug.hpp"

BEGIN_QR_NAMESPACE

OneOfFilter::OneOfFilter( StringFilter *aBase, String anElements ) :
  StringFilterAdapter( aBase ),
  elements( anElements )
{}

OneOfFilter::~OneOfFilter()
{}

unichar OneOfFilter::getNext()
{
  preC_( getBase() != ( StringFilterAdapter * ) NIL );
  
  unichar next;
  
  while( ( next = getBase() -> getNext() ) != ( unichar ) 0 )
	{
	  ++position;
	  if( elements.contains( next ) )
		{
		  ++counter;
		  return next;
		}
	}
  return ( unichar ) 0;
}

String  OneOfFilter::getClassName() const
{
  return "OneOfFilter";
}

#if defined( TESTING )
boolean OneOfFilter::tester( int  ) const
{
  {
	OneOfFilter filter( new IdentityFilter( "blablablafoobarbaz" ), "abo" );
	DLOGSTRING( "filtered: %s", filter.asString() );
	return true;
  }
}
#endif

END_QR_NAMESPACE

#if defined(_INLINE)
#include "../src/Debug.ipp"
#endif


/*
 * $Log: OneOfFilter.cpp,v $
 * Revision 1.1.1.1  2000/07/19 16:44:39  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:40  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:30  god
 * Imported sources
*/
