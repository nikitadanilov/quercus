// -*-C++-*- 

/*  src/algorithms/parse/SimpleWordParser.cpp  */

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



/* $Id: SimpleWordParser.cpp,v 1.1.1.1 2000/07/19 16:44:06 philogelos Exp $ */
#if !defined(_INLINE)
static char cvsid[] = "@(#)$Id: SimpleWordParser.cpp,v 1.1.1.1 2000/07/19 16:44:06 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif

#include "containers/lists/List.hpp"
#include "algorithms/parse/TokenAdapter.hpp"
#include "algorithms/enumerations/EnumerationAlgorithms.hpp"

#include "algorithms/parse/SimpleWordParser.hpp"
#include "UCSChar.hpp"
#include "OGuard.hpp"
#include "Debug.hpp"

BEGIN_QR_NAMESPACE

SimpleWordParser::SimpleWordParser( CharEnumeration *aSource, String aDelimiters ) :
  WordParser( aSource ),
  delimiters( aDelimiters )
{
  TokenAdapter *space;
  TokenAdapter *word;

  List *spaces;

  space = new TokenAdapter();
  OGuard _space( space, this );

  word  = new TokenAdapter();
  OGuard _word( word, this );

  space -> setTag( new String( " " ) );
  word -> setTag( new String( "w" ) );

  spaces = new List();
  OGuard _spaces( spaces, this );

  for( int i = 0 ; i < delimiters.length() ; ++i )
	{
	  spaces -> append( new UCSChar( delimiters.getUNIChars()[ i ] ) );
	}
  addSyntaxEntry( spaces, space );
  addDefaultEntry( word );
}

String  SimpleWordParser::getClassName() const
{
  return "SimpleWordParser";
}

END_QR_NAMESPACE

#if defined(_INLINE)
#include "../src/Debug.ipp"
#endif


/*
 * $Log: SimpleWordParser.cpp,v $
 * Revision 1.1.1.1  2000/07/19 16:44:06  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:40  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:30  god
 * Imported sources
*/
