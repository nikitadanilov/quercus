// -*-C++-*- 

/*  src/algorithms/string/FromToBy.cpp  */

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



/* $Id: FromToBy.cpp,v 1.1.1.1 2000/07/19 16:44:34 philogelos Exp $ */
#if !defined(_INLINE)
static char cvsid[] = "@(#)$Id: FromToBy.cpp,v 1.1.1.1 2000/07/19 16:44:34 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif

#include "algorithms/string/FromToBy.hpp"
#include "Debug.hpp"

BEGIN_QR_NAMESPACE

FromToBy::FromToBy( StringFilter *aBase, 
					Index aStart, Index anEnd, Index aStep ) :
  StringFilterAdapter( aBase )
{
  preC_( aStep > 0 );
    
  start = aStart;
  end = anEnd;
  step = aStep;
}

FromToBy::~FromToBy()
{}

unichar FromToBy::getNext()
{
  preC_( getBase() != NIL );
  
  unichar next;

  next = ( unichar ) 0;
  if( position < start )
	{
	  do
		{
		  next = getBase() -> getNext();
		  if( next == ( unichar ) 0 )
			{
			  return ( unichar ) 0;
			}
		  ++position;
		}
	  while( position < start );
	  return next;
	}
  if( position + step >= end )
	{
	  return ( unichar ) 0;
	}
  for( Index i = 0 ; i < step ; ++i )
	{
	  next = getBase() -> getNext();
	  if( next == ( unichar ) 0 )
		{
		  return ( unichar ) 0;
		}
	  ++position;
	}
  test_( ( position - start ) % step == 0 );
  return next;
}

String  FromToBy::getClassName() const
{
  return "FromToBy";
}

END_QR_NAMESPACE

#if defined(_INLINE)
#include "../src/Debug.ipp"
#endif


/*
 * $Log: FromToBy.cpp,v $
 * Revision 1.1.1.1  2000/07/19 16:44:34  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:40  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:30  god
 * Imported sources
*/
