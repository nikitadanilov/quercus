// -*-C++-*- 

/*  src/UTF8Converter.cpp  */

/*
 * Author: Philogelos A. <Philogelos@yahoo.com>
 * Maintainer: Philogelos A.
 * Keywords: C++, library, containers
 *
 * Copyright (C) 1998, 1999 Philogelos A.
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



/* $Id: UTF8Converter.cpp,v 1.1.1.1 2000/07/19 16:42:51 philogelos Exp $ */
#if !defined(_INLINE)
static char cvsid[] = "@(#)$Id: UTF8Converter.cpp,v 1.1.1.1 2000/07/19 16:42:51 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif


#include "UTF8Converter.hpp"
#include "OGuard.hpp"
#include "Debug.hpp"
#include "UCSChar.hpp"

BEGIN_QR_NAMESPACE

UTF8Converter::UTF8Converter()
{}

UTF8Converter::~UTF8Converter()
{}

unichar UTF8Converter::fromBits( const char *const aSource, Index *aBytesRead )
{
  preC_( aSource != NIL );
  preC_( aBytesRead != ( Index * ) NIL );

  char firstByte;
  firstByte = aSource[ 0 ];
  if( ( firstByte & 0x80 ) == 0 )
	{
	  /* first byte high bit 0 */
	  *aBytesRead = 1;
	  /* return new UCSChar( ( firstByte & 0x7f ), 0 ); */
	  return firstByte & 0x7f;
	}
  else
	{
	  /* first byte high bit 1 */
	  test( ( firstByte & 0x40 ) != 0, 
			"UTF-8: reading from the middle of the multi-byte." );
	  char secondByte;
	  
	  secondByte = aSource[ 1 ];
	  test_( ( secondByte & 0x80 ) != 0 );
	  test_( ( secondByte & 0x40 ) == 0 );

	  if( ( firstByte & 0x20 ) == 0 )
		{
		  /* 2-byte sequence */
		  *aBytesRead = 2;
		  /* return new UCSChar( ( int16 )( ( ( firstByte & 0x1f ) << 6 ) + 
			 ( secondByte & 0x3f ) ) ); */
		  return ( ( ( firstByte & 0x1f ) << 6 ) + ( secondByte & 0x3f ) );
		}
	  else
		{
		  /* 3-byte sequence */
		  char thirdByte;
		  test( ( firstByte & 0x10 ) == 0,
				"Wrong UTF-8 or 32-bit Unicode." );

		  thirdByte = aSource[ 2 ];
		  test_( ( thirdByte & 0x80 ) != 0 );
		  test_( ( thirdByte & 0x40 ) == 0 );

		  *aBytesRead = 3;
		  /* return new UCSChar( ( int16 )( ( ( firstByte & 0xf ) << 12 ) + 
			 ( ( secondByte & 0x3f ) << 6 ) +
			 ( ( thirdByte & 0x3f ) ) ) ); */
		  return ( ( ( firstByte & 0xf ) << 12 ) + 
				   ( ( secondByte & 0x3f ) << 6 ) +
				   ( ( thirdByte & 0x3f ) ) );
		}
	}
  impossible_;
}

char *UTF8Converter::toBits( const unichar aChar, 
							 char * anArena, 
							 Index *aBytesWritten )

{
  preC_( aBytesWritten != ( Index * ) NIL );

  unsigned char page;
  unsigned char offset;
  char *arena;

  page = ( aChar >> 8 ) & 0xff;
  offset = aChar & 0xff;

  if( ( page == 0 ) && ( offset < 0x80 ) )
	{
	  *aBytesWritten = 1;
	}
  else
	{
	  if( page <= 7 )
		{
		  *aBytesWritten = 2;
		}
	  else
		{
		  *aBytesWritten = 3;
		}
	}

  if( anArena == NIL )
	{
	  arena = new char[ *aBytesWritten + 1 ];
	}
  else
	{
	  arena = anArena;
	}

  switch( *aBytesWritten )
	{
	case 1:
	  arena[ 0 ] = offset;
	  break;
	case 2:
	  arena[ 0 ] = 0xc0 + ( page << 2 ) + ( offset >> 6 );
	  arena[ 1 ] = 0x80 + ( offset & 0x3f );
	  break;
	case 3:
	  arena[ 0 ] = 0xe0 + ( page >> 4 );
	  arena[ 1 ] = 0x80 + ( ( page & 0x0f ) << 2 ) + ( offset >> 6 );
	  arena[ 2 ] = 0x80 + ( offset & 0x3f );
	  break;
	default:
	  impossible_;
	}
  return arena;
}

boolean UTF8Converter::equals( const Top *anOther ) const
{
  return( DCAST( anOther, UTF8Converter ) != ( UTF8Converter * ) NIL );
}

Top *UTF8Converter::clone() const
{
  return new UTF8Converter();
}

String  UTF8Converter::getClassName() const
{
  return "UTF8Converter";
}

UTF8Converter *UTF8Converter::getDefaultUTF8Converter()
{
  if( instance == ( UTF8Converter * ) NIL )
	{
	  instance = new UTF8Converter();
	  instance -> dontManage();
	}
  return instance;
}

UTF8Converter *UTF8Converter::instance = ( UTF8Converter * ) NIL;


END_QR_NAMESPACE

#if defined(_INLINE)
#include "../src/Debug.ipp"
#endif

/*
 * $Log: UTF8Converter.cpp,v $
 * Revision 1.1.1.1  2000/07/19 16:42:51  philogelos
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
 * Revision 1.1  1999/02/28 15:59:57  philogelos
 * Added
 * */
