//-*-C++-*-

/*  src/exceptions/Exception.cpp  */


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



/* $Id: Exception.cpp,v 1.1.1.1 2000/07/19 16:49:01 philogelos Exp $ */
#if !defined(_INLINE)
static char cvsid[] = "@(#)$Id: Exception.cpp,v 1.1.1.1 2000/07/19 16:49:01 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif


#include "defines.h"
#include "Backtrace.hpp"
#include "exceptions/Exception.hpp"
#include "LinkManager.hpp"
/* #include "String.hpp" */
/* #include "Object.hpp" */

BEGIN_QR_NAMESPACE

/* Exception::Exception() : 
  message(),
  source( null )
  {}*/

Exception::Exception( String aMessage, const Top *const aSource ) : 
  message( aMessage ),
  source( aSource )
{
  if( source != nil )
	{
	  OREG( source );
	}
  FINIT( backtrace, new Backtrace() );
  backtrace -> fill();
}

Exception::~Exception()
{
  FDONE( backtrace );
}

String Exception::getMessage() const
{
  return message;
}

const Top *Exception::getSource() const
{
  return source;
}

String Exception::getDescription() const
{
  return String( "General Exception", false );
}

Backtrace *Exception::getBacktrace() const
{
  return backtrace;
}

String Exception::getFullDescription() const
{
  String fullDescription;

  fullDescription = String( "Exception of class: ", false ) + getDescription();
  if( getSource() != null )
	{
	  fullDescription = fullDescription + "thrown by : " + getSource()->toString();
	}
  fullDescription = fullDescription + ", message: " + getMessage();

  return fullDescription;
}

String  Exception::getString() const
{
  return Object::getString() + getFullDescription();
}

String  Exception::getClassName() const
{
  return String( "Exception", false );
}

END_QR_NAMESPACE

/*
 * $Log: Exception.cpp,v $
 * Revision 1.1.1.1  2000/07/19 16:49:01  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:42  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:33  god
 * Imported sources
 *
 * Revision 1.3  1999/03/03 19:09:42  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.2  1999/02/28 16:30:44  philogelos
 * Tuned for inlines.
 *
 * Revision 1.1.1.1  1998/11/25 20:11:03  philogelos
 * Quercus Robusta
 *
 * Revision 1.4  1998/07/09 09:04:47  philogelos
 * custom new/delete added
 *
 * Revision 1.3  1998/07/07 14:30:02  philogelos
 * Memory leak in SUNWspro dynamic_cast fixed.
 *
 * Revision 1.2  1998/06/22 18:13:02  philogelos
 * Enumerations and containers added
 *
 * Revision 1.1.1.1  1998/06/22 08:47:13  philogelos
 * First version under CVS
 *
 * Revision 1.1.1.1  1998/04/01 17:15:29  philogelos
 * first version under CVS
 * */
