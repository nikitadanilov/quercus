// -*-C++-*- 

/*  src/exceptions/Errno.cpp  */


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


/* $Id: Errno.cpp,v 1.1.1.1 2000/07/19 16:48:55 philogelos Exp $ */
#if !defined(_INLINE)
static char cvsid[] = "@(#)$Id: Errno.cpp,v 1.1.1.1 2000/07/19 16:48:55 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif

#include <errno.h>
// int errno;

#include "platform/Platform.hpp"
#include "exceptions/Errno.hpp"
#include "Debug.hpp"

BEGIN_QR_NAMESPACE

Errno::Errno( String aMessage, const Top *const aSource, int aErrno ) : 
  OSError( aMessage, aSource ),
  Exception( aMessage, aSource )
{
  errNo = aErrno;
}

String  Errno::getClassName() const
{
  return "Errno";
}

String  Errno::getDescription() const
{
  return OSError::getDescription() + " :\n system call failed: errno = " + 
	String( errNo, 10 ) + " ( " + 
	PLAF -> getErrorDescription( errNo ) + " ) ";
}

END_QR_NAMESPACE

#if defined(_INLINE)
#include "../src/Debug.ipp"
#endif

/*
 * $Log: Errno.cpp,v $
 * Revision 1.1.1.1  2000/07/19 16:48:55  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.4  2000/04/09 12:00:49  god
 * CVS Log keyword correction finished
 *
 * Revision 1.3  2000/04/09 11:29:42  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.2  2000/04/07 16:52:35  god
 * explicit declaration of errno commented out
 *
 * Revision 1.4  1999/05/22 13:00:55  philogelos
 * Merging sources back from SPARC
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
 * Revision 1.1  1998/07/09 09:30:43  philogelos
 * new files added to the repository
 * */
