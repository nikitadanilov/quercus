//-*-C++-*-

/*  src/exceptions/Throwable.cpp  */


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



/* $Id: Throwable.cpp,v 1.1.1.1 2000/07/19 16:49:15 philogelos Exp $ */
#if !defined(_INLINE)
static char cvsid[] = "@(#)$Id: Throwable.cpp,v 1.1.1.1 2000/07/19 16:49:15 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif


#include "Debug.hpp"
#include "String.hpp"
#include "defines.h"
#include "exceptions/Throwable.hpp"

BEGIN_QR_NAMESPACE

Throwable::Throwable()
{}

void Throwable::announce()
{
  DLOGSTRING
	( "Condition ``%s'' is loudly announced", getString() );
}

END_QR_NAMESPACE

#if defined(_INLINE)
#include "../src/Debug.ipp"
#endif


#if defined(_INLINE)
#include "../src/String.ipp"
#endif

/*
 * $Log: Throwable.cpp,v $
 * Revision 1.1.1.1  2000/07/19 16:49:15  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:42  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:33  god
 * Imported sources
 *
 * Revision 1.3  1999/03/03 19:09:43  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.2  1999/02/28 16:30:46  philogelos
 * Tuned for inlines.
 *
 * Revision 1.1.1.1  1998/11/25 20:11:03  philogelos
 * Quercus Robusta
 *
 * Revision 1.3  1998/07/09 09:04:49  philogelos
 * custom new/delete added
 *
 * Revision 1.2  1998/07/07 14:30:04  philogelos
 * Memory leak in SUNWspro dynamic_cast fixed.
 *
 * Revision 1.1.1.1  1998/06/22 08:47:13  philogelos
 * First version under CVS
 *
 * Revision 1.1.1.1  1998/04/01 17:15:29  philogelos
 * first version under CVS
 * */
