// -*-C++-*- 

/*  src/PGuard.cpp  */


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


/* $Id: PGuard.cpp,v 1.1.1.1 2000/07/19 16:42:02 philogelos Exp $ */
#if !defined(_INLINE)
static char cvsid[] = "@(#)$Id: PGuard.cpp,v 1.1.1.1 2000/07/19 16:42:02 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif


#include "PGuard.hpp"
#include "Debug.hpp"
#include "String.hpp"

BEGIN_QR_NAMESPACE

PGuard::PGuard( const Top *aTarget, const Top *anOwner ) :
  target( aTarget ), owner( anOwner )
{
  //  preC_( aTarget != nil );
  preC_( anOwner != nil );

  if( target != null )
	{
	  target -> lock( anOwner );
	}
}

PGuard::~PGuard()
{
  if( target != null )
	{
	  target -> unlock( owner );
	}
}


String  PGuard::getClassName() const
{
  return "PGuard";
}

END_QR_NAMESPACE

#if defined(_INLINE)
#include "../src/Debug.ipp"
#endif


#if defined(_INLINE)
#include "../src/String.ipp"
#endif

/*
 * $Log: PGuard.cpp,v $
 * Revision 1.1.1.1  2000/07/19 16:42:02  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:39  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:28  god
 * Imported sources
 *
 * Revision 1.3  1999/03/03 19:09:29  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.2  1999/02/28 15:52:51  philogelos
 * Tuned for inlines. Copyright updated
 *
 * Revision 1.1.1.1  1998/11/25 20:11:01  philogelos
 * Quercus Robusta
 * */
