// -*-C++-*- 

/*  src/ui/wq/GC.cpp  */

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



/* $Id: GC.cpp,v 1.1.1.1 2000/07/19 16:52:58 philogelos Exp $ */
#if !defined(_INLINE)
static char cvsid[] = "@(#)$Id: GC.cpp,v 1.1.1.1 2000/07/19 16:52:58 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif

#include "ui/wq/WqCommon.hpp"
#include "Debug.hpp"

#if defined( USE_WQ )

BEGIN_QR_NAMESPACE

Wq::GC::GC( COLORREF aFore, COLORREF aBack, 
			Wq::Pen *aPen, Wq::Brush *aBrush, Wq::Font *aFont ) :
  GraphicContext( MSWindowSystem::msWindowSystem )
{
  preC_( aPen != NULL );
  preC_( aBrush != NULL );
  preC_( aFont != NULL );

  fg = aFore;
  bg = aBack;
  
  FNNINIT( pen, aPen );
  FNNINIT( brush, aBrush );
  FNNINIT( font, aFont );
  FINIT( cleanBrush, Wq::Brush::createSolid( aBack ) );
}

Wq::GC::~GC()
{
  FDONE( cleanBrush );
  FDONE( font );
  FDONE( brush );
  FDONE( pen );
}

void Wq::GC::flushTo( Wq::DC *aDC )
{
  preC_( aDC != NULL );

  aDC -> setPen( pen );
  aDC -> setBrush( brush );
  aDC -> setFont( font );
  aDC -> setTextForeground( fg );
  aDC -> setTextBackground( bg );
}

END_QR_NAMESPACE

#if defined(_INLINE)
#include "../src/Debug.ipp"
#endif

/* USE_WQ */
#endif

/* $Log: GC.cpp,v $
/* Revision 1.1.1.1  2000/07/19 16:52:58  philogelos
/* stored sources into sourceforge.net CVS
/*
/* Revision 1.1.1.1  2000/04/01 14:07:36  god
/* Imported sources
/* */
