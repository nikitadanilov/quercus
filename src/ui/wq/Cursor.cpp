// -*-C++-*- 

/*  src/ui/wq/Cursor.cpp  */

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



/* $Id: Cursor.cpp,v 1.1.1.1 2000/07/19 16:52:37 philogelos Exp $ */
#if !defined(_INLINE)
static char cvsid[] = "@(#)$Id: Cursor.cpp,v 1.1.1.1 2000/07/19 16:52:37 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif

#include "ui/wq/WqCommon.hpp"
#include "Debug.hpp"

#if defined( USE_WQ )

BEGIN_QR_NAMESPACE

Wq::Cursor::Cursor( HANDLE aHandle ) : Win32Object( aHandle )
{}

Wq::Cursor::~Cursor()
{
  DestroyCursor( getHandle() );
  handle = NULL;
}

Wq::Cursor *Wq::Cursor::load( char *aResource )
{
  return loadGlobal( GetModuleHandle( NULL ), aResource );
}

Wq::Cursor *Wq::Cursor::loadGlobal( HANDLE aModule, char *aResource )
{
  CREATE_OBJECT( Wq::Cursor, 
				 LoadCursor( aModule, aResource ), 
				 Wq::Cursor::load() );
}

Wq::Cursor *Wq::Cursor::create( Aq::Size aWidth, Aq::Size aHeight, 
								Aq::CoordX aHotSpotX, Aq::CoordY aHotSpotY, 
								void *anANDMask, void *aXORMask )
{
  CREATE_OBJECT( Wq::Cursor, 
				 CreateCursor( GetModuleHandle( NULL ), 
							   aHotSpotX, aHotSpotY, aWidth, aHeight, 
							   anANDMask, aXORMask ), 
				 Wq::Cursor::create() );
}

END_QR_NAMESPACE

#if defined(_INLINE)
#include "../src/Debug.ipp"
#endif

/* USE_WQ */
#endif

/* $Log: Cursor.cpp,v $
/* Revision 1.1.1.1  2000/07/19 16:52:37  philogelos
/* stored sources into sourceforge.net CVS
/*
/* Revision 1.1.1.1  2000/04/01 14:07:37  god
/* Imported sources
/* */
