// -*-C++-*- 

/*  src/algorithms/parse/Comment.cpp  */

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



/* $Id: Comment.cpp,v 1.2 2000/10/11 19:51:11 philogelos Exp $ */
#if !defined( _INLINE )
static char cvsid[] = "@(#)$Id: Comment.cpp,v 1.2 2000/10/11 19:51:11 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif

#include "algorithms/parse/Comment.hpp"
#include "algorithms/parse/TokenAdapter.hpp"
#include "algorithms/parse/ParseStream.hpp"
#include "algorithms/parse/TokenCradle.hpp"
#include "StringBuffer.hpp"
#include "Debug.hpp"
#include "Char.hpp"

BEGIN_QR_NAMESPACE

Comment::Comment( String aStart, String anEnd, boolean canNest )
{
  setStart( aStart );
  setEnd( anEnd );
  setNest( canNest );
}

Comment::~Comment()
{}

Index Comment::accept( TokenCradle *aCradle ) const
{
  preC_( aCradle != NULL );

  if( startsHere( aCradle, 0 ) )
	{
	  Index depth;
	  Index i;

	  depth = 1;
	  for( i = getStart().length() ; depth > 0 ; )
		{
		  if( !aCradle -> hasAt( i ) )
			{
			  return -1;
			}
		  if( getNest() && startsHere( aCradle, i ) )
			{
			  ++depth;
			  i += getStart().length();
			  continue;
			}
		  if( endsHere( aCradle, i ) )
			{
			  --depth;
			  i += getEnd().length();
			  continue;
			}
		  ++i;
		}
	  // DLOG( "Comment::accept: %li", i );
	  return i;
	}
  else
	{
	  return -1;
	}
}

void Comment::setStart( String aStart )
{
  start = aStart;
}

void Comment::setEnd( String anEnd )
{
  end = anEnd;
}

void Comment::setNest( boolean canNest )
{
  nest = canNest;
}

String  Comment::getStart() const
{
  return start;
}

String  Comment::getEnd() const
{
  return end;
}

boolean Comment::getNest() const
{
  return nest;
}

boolean Comment::startsHere( TokenCradle *aCradle, Index aPos ) const
{
  preC_( aCradle != NULL );
  preC_( aPos >= 0 );

  return startsWith( aCradle, aPos, getStart() );
}

boolean Comment::endsHere( TokenCradle *aCradle, Index aPos ) const
{
  preC_( aCradle != NULL );
  preC_( aPos >= 0 );

  return startsWith( aCradle, aPos, getEnd() );
}

boolean Comment::startsWith( TokenCradle *aCradle, 
							 Index aPos, String aString ) const
{
  preC_( aCradle != NULL );
  preC_( aPos >= 0 );

  for( Index i = 0 ; i < aString.length() ; ++i )
	{
	  if( ! aCradle -> hasAt( aPos + i ) ||
		  ( aCradle -> getAt( aPos + i ) != aString.getUNIChars()[ i ] ) )
		{
		  return false;
		}
	}
  return true;
}


String  Comment::getClassName() const
{
  return "Comment";
}

END_QR_NAMESPACE

#if defined( _INLINE )
#include "../src/Debug.ipp"
#endif


/*
 * $Log: Comment.cpp,v $
 * Revision 1.2  2000/10/11 19:51:11  philogelos
 * set/get methods added
 *
 * Revision 1.1  2000/09/21 18:34:02  philogelos
 * minor changes.
 *
 */
