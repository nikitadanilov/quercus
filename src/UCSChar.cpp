// -*- C++ -*-

/*  src/UCSChar.cpp  */


/*
 * Author: Philogelos A. <Philogelos@yahoo.com>
 * Maintainer: Philogelos A.
 * Keywords: C++, library, containers
 *
 * Copyright (C) 1998 Philogelos A.
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


/* $Id: UCSChar.cpp,v 1.1.1.1 2000/07/19 16:42:48 philogelos Exp $ */
#if !defined(_INLINE)
static char cvsid[] = "@(#)$Id: UCSChar.cpp,v 1.1.1.1 2000/07/19 16:42:48 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif


#include "UCSChar.hpp"
#include "Debug.hpp"

#include "exceptions/NotImplemented.hpp"
#include "UTF8Converter.hpp"
#include "platform/Platform.hpp"

BEGIN_QR_NAMESPACE

UCSChar::UCSChar( unichar aCode )
{
  code = aCode;
}

UCSChar::UCSChar( const Char &aChar )
{
  code = aChar.getUNICODE();
}

UCSChar::UCSChar( char anOffset, char aPage )
{
  setPage( aPage );
  setOffset( anOffset );
}

UCSChar::~UCSChar()
{}

unichar   UCSChar::getUNICODE() const
{
  return getCChar();
}

void    UCSChar::setUNICODE( unichar aCode )
{
  code = aCode;
}

char   *UCSChar::toCChar() const
{
  char *result;

  result = new char[ 3 ];
  result[ 0 ] = getPage();
  result[ 1 ] = getOffset();
  result[ 2 ] = ( char ) 0;
  return result;
}

char   *UCSChar::toUTF8() const
{
  Index dummy;

  return UTF8Converter::getDefaultUTF8Converter() -> 
	charToBits( this, NIL, &dummy );
}

void    UCSChar::setPage( unsigned char aPage )
{
  code &= 0x00ff;
  code += ( aPage << 8 );
}

void    UCSChar::setOffset( unsigned char anOffset )
{
  code &= 0xff00;
  code += anOffset;
}

int16   UCSChar::getCChar() const
{
  return code;
}

boolean UCSChar::equals( const Top *anOther ) const
{
  return Char::equals( anOther );
}

Top *UCSChar::clone() const
{
  return new UCSChar( ( const Char & ) *this );
}

String  UCSChar::getString() const
{
  char *result;

  result = new char[ 10 ];
  PLAF -> sprintf( result, "[ %2.2x, %c ]", getPage(), getOffset() );
  return String( result, true );
}

String  UCSChar::getClassName() const
{
  return "Char";
}

#if defined( TESTING )
boolean UCSChar::tester( int ) const
{
  return true;
}
#endif

char UCSChar::defaultUnicodePage = ( char )0;


END_QR_NAMESPACE

#if defined(_INLINE)
#include "../src/Debug.ipp"
#endif

/*
 * $Log: UCSChar.cpp,v $
 * Revision 1.1.1.1  2000/07/19 16:42:48  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:39  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:28  god
 * Imported sources
 *
 * Revision 1.3  1999/05/22 13:00:31  philogelos
 * Merging sources back from SPARC
 *
 * Revision 1.2  1999/03/03 19:09:31  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.1  1999/02/28 15:59:41  philogelos
 * Added
 * */


