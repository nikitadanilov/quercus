// -*-C++-*- 

/*  src/OGuard.cpp  */


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


/* $Id: OGuard.cpp,v 1.1.1.1 2000/07/19 16:41:43 philogelos Exp $ */
#if !defined(_INLINE)
static char cvsid[] = "@(#)$Id: OGuard.cpp,v 1.1.1.1 2000/07/19 16:41:43 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif


#include "OGuard.hpp"
#include "String.hpp"
#include "Debug.hpp"
#include "LinkManager.hpp"

BEGIN_QR_NAMESPACE

OGuard::OGuard( const Top *aTarget, const Top *anOwner, boolean aReadOnly ) :
  target( aTarget ), owner( anOwner )
{
  //  preC_( aTarget != nil );
  preC_( anOwner != nil );

  if( target != null )
	{
	  if( aReadOnly )
		{
		  target -> lockRead( anOwner );
		}
	  else
		{
		  target -> lock( anOwner );
		}
	}
  postC_( target == aTarget );
}

OGuard::~OGuard()
{
  if( target != null )
	{
	  target -> unlock( owner );
	  LinkManager::recycle( target );
	}
}

#if !defined( LIGHTWEIGHT_GUARD )
Top *OGuard::clone() const
{
  return new OGuard( target, owner );
}

String  OGuard::toString() const
{
  return Guard::toString() + Guards + ( target -> toString() ) +
	OnBehalfOf + ( owner -> toString() );
}

String  OGuard::getString() const
{
  return Guard::getString() + Guards + ( target -> getString() ) +
	OnBehalfOf + ( owner -> getString() );
}

String  OGuard::getClassName() const
{
  return "OGuard";
}
#endif

String OGuard::Guards( " guards: " );
String OGuard::OnBehalfOf( " on behalf of: " );

END_QR_NAMESPACE

#if defined(_INLINE)
#include "../src/Debug.ipp"
#endif


#if defined(_INLINE)
#include "../src/String.ipp"
#endif

/*
 * $Log: OGuard.cpp,v $
 * Revision 1.1.1.1  2000/07/19 16:41:43  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.4  2000/05/06 08:36:27  god
 * committed
 *
 * Revision 1.3  2000/04/29 15:00:24  god
 * readonly locking implemented
 *
 * Revision 1.2  2000/04/09 11:29:39  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:28  god
 * Imported sources
 *
 * Revision 1.3  1999/03/03 19:09:28  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.2  1999/02/28 15:51:16  philogelos
 * Tuned for inlines.
 *
 * Revision 1.1.1.1  1998/11/25 20:11:01  philogelos
 * Quercus Robusta
 * */
