// -*-C++-*- 

/*  src/platform/Platform.cpp  */

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



/* $Id: Platform.cpp,v 1.1.1.1 2000/07/19 16:51:30 philogelos Exp $ */
#if !defined(_INLINE)
static char cvsid[] = "@(#)$Id: Platform.cpp,v 1.1.1.1 2000/07/19 16:51:30 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif

#include "platform/Platform.hpp"
#include "platform/ANSICPlatform.hpp"
#include "platform/POSIXPlatform.hpp"
#include "platform/Win32Platform.hpp"
#include "platform/MinimalPlatform.hpp"
#include "Debug.hpp"

BEGIN_QR_NAMESPACE

Platform *Platform::getInstance()
{
  if( instance == ( Platform * ) NIL )
	{
	  instance = new PLATFORM();
	  TCAST( instance, Object ) -> dontManage();
	}
  return instance;
}

Platform *Platform::getInstanceNow()
{
  return instance;
}

void *Platform::allocateMemoryBootstrap( Index aSize )
{
  return ANSICPlatform::allocateMemoryBootstrapANSI( aSize );
}

void  Platform::deallocateMemoryBootstrap( void *aPointer )
{
  ANSICPlatform::deallocateMemoryBootstrapANSI( aPointer );
}
 
Platform *Platform::instance = ( Platform * ) NIL;

END_QR_NAMESPACE

#if defined(_INLINE)
#include "../src/Debug.ipp"
#endif


/*
 * $Log: Platform.cpp,v $
 * Revision 1.1.1.1  2000/07/19 16:51:30  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:43  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:34  god
 * Imported sources
*/
