// -*-C++-*- 

/*  src/ui/wq/Bitmap.cpp  */

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



/* $Id: Bitmap.cpp,v 1.1.1.1 2000/07/19 16:52:31 philogelos Exp $ */
#if !defined(_INLINE)
static char cvsid[] = "@(#)$Id: Bitmap.cpp,v 1.1.1.1 2000/07/19 16:52:31 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif

#include "ui/wq/WqCommon.hpp"
#include "Debug.hpp"

#if defined( USE_WQ )

BEGIN_QR_NAMESPACE

Wq::Bitmap::Bitmap( HANDLE aHandle ) : Win32Object( aHandle )
{
  dc = NULL;
}

Wq::Bitmap::~Bitmap()
{
  FCDONE( dc );
  DeleteObject( getHandle() );
  handle = NULL;
}

Aq::Size Wq::Bitmap::getWidth() const
{
  SIZE size;

  GUI_WRAP( GetBitmapDimensionEx( getHandle(), &size ), 0, 
			Wq::Bitmap::getWidth() );
  return size.cx;
}

void Wq::Bitmap::setSize( Aq::Size aWidth, Aq::Size aHeight )
{
  SIZE size;

  GUI_WRAP( SetBitmapDimensionEx( getHandle(), aWidth, aHeight, &size ), 0, 
			Wq::Bitmap::getWidth() );
}

Aq::Size Wq::Bitmap::getHeight() const
{
  SIZE size;

  GUI_WRAP( GetBitmapDimensionEx( getHandle(), &size ), 0, 
			Wq::Bitmap::getWidth() );
  return size.cy;
}

void Wq::Bitmap::setDC( DC *aDC )
{
  FCDONE( dc );
  if( aDC != NULL )
	{
	  OGuard _dc( aDC, this );

	  ( ( Wq::DC * ) dc ) = Wq::DC::createInMemory
		( aDC -> getHandle() );
	}
  else
	{
	  ( ( Wq::DC * ) dc ) = Wq::DC::createInMemory( NULL );
	}
  PGuard _self( this, this );

  OREG( dc );
  dc -> setBitmap( ( Wq::Bitmap * ) this );
}

Wq::DC *Wq::Bitmap::getDC() const
{
  if( dc == NULL )
	{
	  const_cast< Wq::Bitmap * >( this ) -> setDC( NULL );
	  test_( dc != NULL );
	}
  //  dc -> fillRectangle( 0, 0, 10, 10, 
  //	  Wq::Brush::createSolid( RGB( 0xff, 0, 0 ) ) );
  return dc;
}

void Wq::Bitmap::ungetDC( DC *aDC ) const
{}

Wq::Bitmap *Wq::Bitmap::create( DC *aDC, Aq::Size aWidth,
								Aq::Size aHeight )
{
  preC_( aDC != NULL );

  OGuard _dc( aDC, aDC );

  CREATE_OBJECT( Wq::Bitmap, 
				 CreateCompatibleBitmap( aDC -> getHandle(),
										 aWidth, aHeight ), 
				 Wq::Bitmap::create() );
}

Wq::Bitmap *Wq::Bitmap::load( int aResource )
{
  CREATE_OBJECT( Wq::Bitmap, 
				 LoadBitmap( GetModuleHandle( NULL ), 
							 MAKEINTRESOURCE( aResource ) ), 
				 Wq::Bitmap::load() );
}

END_QR_NAMESPACE

#if defined(_INLINE)
#include "../src/Debug.ipp"
#endif

/* USE_WQ */
#endif

/* $Log: Bitmap.cpp,v $
/* Revision 1.1.1.1  2000/07/19 16:52:31  philogelos
/* stored sources into sourceforge.net CVS
/*
/* Revision 1.1.1.1  2000/04/01 14:07:37  god
/* Imported sources
/* */
