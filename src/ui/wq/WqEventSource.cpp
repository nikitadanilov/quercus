// -*-C++-*- 

/*  src/ui/wq/WqEventSource.cpp  */

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



/* $Id: WqEventSource.cpp,v 1.1.1.1 2000/07/19 16:53:57 philogelos Exp $ */
#if !defined(_INLINE)
static char cvsid[] = "@(#)$Id: WqEventSource.cpp,v 1.1.1.1 2000/07/19 16:53:57 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif

#include "ui/wq/WqCommon.hpp"
#include "Debug.hpp"

#if defined( USE_WQ )

BEGIN_QR_NAMESPACE

Wq::WqEventSource::WqEventSource()
{
  doneWithEvents = false;
}

void  Wq::WqEventSource::processEvent( Aq::AqEvent *anEvent )
{
  preC_( anEvent != NULL );

  WqEvent *event;
  
  event = TCAST( anEvent, Wq::WqEvent );
  OGuard _event( event, this );

  TranslateMessage( &( event -> event ) ); 
  DispatchMessage( &( event -> event ) ); 
}

END_QR_NAMESPACE

#if defined(_INLINE)
#include "../src/Debug.ipp"
#endif

/* USE_WQ */
#endif

/* $Log: WqEventSource.cpp,v $
/* Revision 1.1.1.1  2000/07/19 16:53:57  philogelos
/* stored sources into sourceforge.net CVS
/*
/* Revision 1.1.1.1  2000/04/01 14:07:36  god
/* Imported sources
/* */
