// -*- C++ -*-

/*  src/Char.cpp  */


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


/* $Id: Char.cpp,v 1.1.1.1 2000/07/19 16:40:28 philogelos Exp $ */
#if !defined(_INLINE)
static char cvsid[] = "@(#)$Id: Char.cpp,v 1.1.1.1 2000/07/19 16:40:28 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif


#include "Char.hpp"
#include "Debug.hpp"
#include "OGuard.hpp"

#include "exceptions/NotImplemented.hpp"
#include "UTF8Converter.hpp"

BEGIN_QR_NAMESPACE

String Char::asString() const
{
  return String( toCChar(), false );
}

unsigned char    Char::getPage() const
{
  return ( ( getUNICODE() >> 8 ) & 0xff );
}

unsigned char    Char::getOffset() const
{
  return ( getUNICODE() & 0xff );
}

boolean Char::equals( const Top *anOther ) const
{
  Char *other;
  
  other = DCAST( anOther, Char );
  OGuard _other( other, this );
  if( other == null )
	{
	  return false;
	}
  else
	{
	  return( getUNICODE() == other -> getUNICODE() );
	}
}

END_QR_NAMESPACE

#if defined(_INLINE)
#include "../src/Debug.ipp"
#endif


/*
 * $Log: Char.cpp,v $
 * Revision 1.1.1.1  2000/07/19 16:40:28  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:38  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:28  god
 * Imported sources
 *
 * Revision 1.3  1999/05/22 13:00:28  philogelos
 * Merging sources back from SPARC
 *
 * Revision 1.2  1999/03/03 19:09:25  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.1  1999/02/28 15:44:24  philogelos
 * UNICODE support added
 * */


