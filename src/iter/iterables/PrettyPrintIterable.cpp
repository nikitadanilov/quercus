// -*- C++ -*-

/*  src/iter/iterables/PrettyPrintIterable.cpp  */


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


/* $Id: PrettyPrintIterable.cpp,v 1.2 2001/04/16 13:37:13 philogelos Exp $ */
#if !defined(_INLINE)
static char cvsid[] = "@(#)$Id: PrettyPrintIterable.cpp,v 1.2 2001/04/16 13:37:13 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif


#include "iter/iterables/PrettyPrintIterable.hpp"
#include "iter/iterators/Iterator.hpp"
#include "Debug.hpp"
#include "OGuard.hpp"
#include "defines.h"

#include "String.hpp"
#include "StringEnumeration.hpp"

BEGIN_QR_NAMESPACE

PrettyPrintIterable::PrettyPrintIterable( String aHeader,
										  String aPadder,
										  String aFooter,
										  String anEllipsis,
										  Index aMaxCount,
										  String ( Top::*aMethod )() const ) :
  header( aHeader ), padder( aPadder ), footer( aFooter ),
  ellipsis( anEllipsis ),
  method( aMethod ),
  buffer( StringBuffer::defaultLength, StringBuffer::defaultDelta ),
  maxCount( aMaxCount )
{}

void PrettyPrintIterable::initIterations()
{
  buffer.add( header.getUNIChars() );
  firstShot = true;
  count = 0;
}

void PrettyPrintIterable::fireOn( Top *anElement ) 
{
  //  preC_( anElement != null );

  if( firstShot )
	{
	  firstShot = false;
	}
  else
	{
	  buffer.add( padder.getUNIChars() );
	}

  if( ( maxCount > 0 ) && ( count > maxCount ) )
	{
	  return;
	}
  else if( count == maxCount )
	{
	  buffer.add( ellipsis.getUNIChars() );
	}
  else if( anElement != null )
	{
	  OGuard _( anElement, this );
	  buffer.add( ( anElement ->* method )().getUNIChars() );
	  //	  IterableAdapter::fire( anElement );
	}
  else
	{
	  buffer.add( String::nullLiteral.getUNIChars() );
	  IterableAdapter::fireOn( anElement );
	}
  ++count;
}

boolean PrettyPrintIterable::isMore()
{
  return( ( maxCount <= 0 ) ||
		  ( count <= maxCount ) );
}


void PrettyPrintIterable::doneIterations()
{
  buffer.add( footer.getUNIChars() );
  result = buffer.asString();
}

String PrettyPrintIterable::getStringResult()
{
  return result;
}

Object *PrettyPrintIterable::getResult()
{
  return &result;
}

#if defined( TESTING )
boolean PrettyPrintIterable::tester( int ) const
{
  StringEnumeration *en = new StringEnumeration( "Vext cwm fly jabs zing kurd qoph." );
  OGuard _( en, this );
  
  Iterator *it = en -> getIterator();
  OGuard __( ( Top * ) it, ( Top * ) this );
  
  PrettyPrintIterable  *runner;
  
  runner = new PrettyPrintIterable( "(", ", ", ")", " ... ", 0, &Top::getString );
  OGuard ___( runner, this );
  
  it -> iterate( runner );
  DLOGOBJECT( runner -> getResult(), &Top::getString );
	  
  return true;
}
#endif

END_QR_NAMESPACE

#if defined(_INLINE)
#include "../src/Debug.ipp"
#endif


#if defined(_INLINE)
#include "../src/String.ipp"
#endif

/*
 * $Log: PrettyPrintIterable.cpp,v $
 * Revision 1.2  2001/04/16 13:37:13  philogelos
 * Added ::getStringResult() to PrettyPrintIterable.
 * Clients updated to take advantage of this method.
 *
 * Revision 1.1.1.1  2000/07/19 16:50:17  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:43  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:29  god
 * Imported sources
 *
 * Revision 1.4  1999/03/03 19:09:46  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.3  1999/02/28 16:30:49  philogelos
 * Tuned for inlines.
 *
 * Revision 1.2  1998/12/01 16:21:25  philogelos
 * conditionally compile ::tester()
 *
 * Revision 1.1.1.1  1998/11/25 20:11:04  philogelos
 * Quercus Robusta
 *
 * Revision 1.4  1998/07/09 09:04:51  philogelos
 * custom new/delete added
 *
 * Revision 1.3  1998/07/07 14:30:07  philogelos
 * Memory leak in SUNWspro dynamic_cast fixed.
 *
 * Revision 1.2  1998/06/22 13:33:40  philogelos
 * Method to call on each object added
 *
 * Revision 1.1.1.1  1998/06/22 08:47:13  philogelos
 * First version under CVS
 *
 * Revision 1.1.1.1  1998/04/01 17:15:29  philogelos
 * first version under CVS
 * */
