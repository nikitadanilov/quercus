// -*-C++-*- 

/*  src/ui/wq/Font.cpp  */

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



/* $Id: Font.cpp,v 1.1.1.1 2000/07/19 16:52:58 philogelos Exp $ */
#if !defined(_INLINE)
static char cvsid[] = "@(#)$Id: Font.cpp,v 1.1.1.1 2000/07/19 16:52:58 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif

#include "ui/wq/WqCommon.hpp"
#include "Debug.hpp"

#if defined( USE_WQ )

BEGIN_QR_NAMESPACE

Wq::Font::Font( HANDLE handle ) : Win32Object( handle )
{}

Wq::Font::~Font()
{
  DeleteObject( getHandle() );
  handle = NULL;
}

Wq::Font *Wq::Font::create( 
						   int aHeight, 
						   int aWidth, 
						   int anEscapement, 
						   int anOrientation, 
						   int aWeight, 
						   DWORD anItalic, 
						   DWORD anUnderline, 
						   DWORD aStrikeOut, 
						   DWORD aCharSet, 
						   DWORD anOutputPrecision, 
						   DWORD anwClipPrecision, 
						   DWORD aQuality, 
						   DWORD aPitchAndFamily, 
						   LPCTSTR aFace )
{
  CREATE_OBJECT( Wq::Font, 
				 CreateFont(
							aHeight, 
							aWidth, 
							anEscapement, 
							anOrientation, 
							aWeight, 
							anItalic, 
							anUnderline, 
							aStrikeOut, 
							aCharSet, 
							anOutputPrecision, 
							anwClipPrecision, 
							aQuality, 
							aPitchAndFamily, 
							aFace ), 
				 Wq::Font::create() );
}
 
Wq::Font *Wq::Font::createDefault()
{
  return create( 0, 0, 0, 0, FW_DONTCARE, false, false, false, 
				 DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
				 DEFAULT_QUALITY, FIXED_PITCH | FF_DONTCARE, NULL );
}

END_QR_NAMESPACE

#if defined(_INLINE)
#include "../src/Debug.ipp"
#endif

/* USE_WQ */
#endif

/* $Log: Font.cpp,v $
/* Revision 1.1.1.1  2000/07/19 16:52:58  philogelos
/* stored sources into sourceforge.net CVS
/*
/* Revision 1.1.1.1  2000/04/01 14:07:37  god
/* Imported sources
/* */
