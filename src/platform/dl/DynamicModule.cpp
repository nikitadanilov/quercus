// -*-C++-*- 

/*  src/platform/dl/DynamicModule.cpp  */

/*
 * Author: Philogelos A. <Philogelos@yahoo.com>
 * Maintainer: Philogelos A.
 * Keywords: C++, library, containers
 *
 * Copyright (C) 1999, 2000 Philogelos A.
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



/* $Id: DynamicModule.cpp,v 1.1.1.1 2000/07/19 16:51:33 philogelos Exp $ */
#if !defined( _INLINE )
static char cvsid[] = "@(#)$Id: DynamicModule.cpp,v 1.1.1.1 2000/07/19 16:51:33 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif

#include "exceptions/Errno.hpp"
#include "platform/dl/DynamicModule.hpp"
#include "Debug.hpp"
#include "containers/lists/List.hpp"

BEGIN_QR_NAMESPACE

DynamicModule::DynamicModule( String aPortableName )
{
  portableName = aPortableName;
  platformName = aPortableName;
  moduleRefCount = 0;
  loaded = false;
  if( loadedModules == NULL )
	{
	  loadedModules = new List();
	  loadedModules -> dontManage();
	}
}

DynamicModule::~DynamicModule()
{}

void DynamicModule::load() THROWS( Errno * )
{
  preC_( moduleRefCount >= 0 );
  if( moduleRefCount == 0 )
	{
	  platformLoad();
	}
  if( loaded )
	{
	  ++moduleRefCount;
	}
  test_( loadedModules != NULL );
  loadedModules -> append( this );
}

void DynamicModule::unload() THROWS( Errno * )
{
  preC_( moduleRefCount > 0 );
  if( loaded )
	{
	  --moduleRefCount;
	}
  if( moduleRefCount == 0 )
	{
	  platformUnload();
	}
  /* XXX Need code in Algorithms to remove given object from given container. */
}

boolean DynamicModule::isLoaded() const
{
  return loaded;
}

void DynamicModule::setPortableName( String aName )
{
  portableName = aName;
}

void DynamicModule::setPlatformName( String aName )
{
  platformName = aName;
}

String DynamicModule::getPortableName() const
{
  return portableName;
}

String DynamicModule::getPlatformName() const
{
  return platformName;
}

List *DynamicModule::loadedModules = NULL;

END_QR_NAMESPACE

#if defined( _INLINE )
#include "../src/Debug.ipp"
#endif


/*
 * $Log: DynamicModule.cpp,v $
 * Revision 1.1.1.1  2000/07/19 16:51:33  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.3  2000/04/09 12:00:49  god
 * CVS Log keyword correction finished
 *
 * Revision 1.2  2000/04/09 11:29:43  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1  2000/04/07 18:02:55  god
 * Added
 *
 * Revision 1.1  2000/04/04 13:10:40  god
 * Initial revision
 * */
