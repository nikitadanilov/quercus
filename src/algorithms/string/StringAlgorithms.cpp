// -*-C++-*- 

/*  src/algorithms/string/StringAlgorithms.cpp  */

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



/* $Id: StringAlgorithms.cpp,v 1.1.1.1 2000/07/19 16:44:43 philogelos Exp $ */
#if !defined(_INLINE)
static char cvsid[] = "@(#)$Id: StringAlgorithms.cpp,v 1.1.1.1 2000/07/19 16:44:43 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif

#include "algorithms/string/IdentityFilter.hpp"
#include "algorithms/string/StringAlgorithms.hpp"
#include "OGuard.hpp"
#include "Debug.hpp"

BEGIN_QR_NAMESPACE

void StringAlgorithms::toLower( String, StringFilter *aFilter )
{
  OGuard _filter( aFilter, this );
}

void StringAlgorithms::toUpper( String, StringFilter *aFilter )
{
  OGuard _filter( aFilter, this );
}

Index StringAlgorithms::length( String aString, StringFilter *aFilter )
{
  OGuard _filter( aFilter, this );

  StringFilter *string;
  
  string = new IdentityFilter( aString );
  OGuard _string( string, this );
  aFilter -> setBase( string );
  return aFilter -> length();
}

Index StringAlgorithms::isEmpty( String aString, StringFilter *aFilter )
{
  OGuard _filter( aFilter, this );

  return( length( aString, aFilter ) == 0 );
}

void StringAlgorithms::replace( String aString, 
								StringFilter *aFilter, unichar aTo )
{
  OGuard _filter( aFilter, this );

  StringFilter *string;
  
  string = new IdentityFilter( aString );
  OGuard _string( string, this );
  aFilter -> setBase( string );
  while( aFilter -> getNext() != ( unichar ) 0 )
	{
	  aString.getUNIChars()[ aFilter -> getPosition() ] = aTo;
	}
}
  
StringAlgorithms *StringAlgorithms::get()
{
  if( instance == ( StringAlgorithms * ) NIL )
	{
	  instance = new StringAlgorithms();
	}
  return instance;
}

StringAlgorithms::StringAlgorithms()
{}

StringAlgorithms::~StringAlgorithms()
{}

String  StringAlgorithms::getClassName() const
{
  return "StringAlgorithms";
}

StringAlgorithms *StringAlgorithms::instance = ( StringAlgorithms * ) NIL;

#if defined( TESTING )

END_QR_NAMESPACE

#include "algorithms/string/FromToBy.hpp"
#include "algorithms/string/OneOfFilter.hpp"
#include "algorithms/string/InOrderFilter.hpp"

BEGIN_QR_NAMESPACE

static void victimize( String aString, StringFilter *aFilter )
{
  OGuard _filter( aFilter, aFilter );

  DLOG( "length: %li", SALG -> length( aString, aFilter ) );
  aFilter -> reset();
  SALG -> replace( aString, aFilter, ( unichar ) '*' );
  DLOGSTRING( "victimized: %s", aString );
}

boolean StringAlgorithms::tester( int ) const
{
  {
	String victim( "victim" );
	
	DLOGSTRING( "victim of OneOf: %s", victim );
	victimize( victim, new OneOfFilter( ( StringFilter * ) NULL, "i" ) );
  }
  {
	String victim( "victim" );
	
	DLOGSTRING( "victim of Identity: %s", victim );
	victimize( victim, new IdentityFilter( victim ) );
  }
  {
	String victim( "long-long victim" );
	
	DLOGSTRING( "victim of FromToBy: %s", victim );
	victimize( victim, new FromToBy( ( StringFilter * ) NULL, 10, 
								 victim.length(), 1 ) );
  }
  {
	String victim( "section.subsection: value" );
	
	DLOGSTRING( "victim of InOrder: %s", victim );
	victimize( victim, new InOrderFilter( ( StringFilter * ) NULL, ".:" ) );
  }
  return true;
}

#endif

END_QR_NAMESPACE

#if defined(_INLINE)
#include "../src/Debug.ipp"
#endif


/*
 * $Log: StringAlgorithms.cpp,v $
 * Revision 1.1.1.1  2000/07/19 16:44:43  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:40  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:30  god
 * Imported sources
*/
