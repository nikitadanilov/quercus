// -*-C++-*- 

/*  inc/platform/dl/DynamicModule.hpp  */

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



#ifndef __DYNAMICMODULE_HPP__
#define __DYNAMICMODULE_HPP__

/* $Id: DynamicModule.hpp,v 1.2 2001/06/23 19:02:50 philogelos Exp $ */

#include "String.hpp"
#include "Top.hpp"
#include "defines.h"

BEGIN_QR_NAMESPACE

class List;
class NoEntity;
class Errno;
/**
   Interface to dynamically loadable modules
   (shared objects in unices or dlls in MSWindows).

   @author Philogelos
   @created 2000-04-04
*/
abstract class DynamicModule : public virtual Top
{

public: DynamicModule( String aPortableName );

  /**
   */
public: virtual ~DynamicModule();

public: void load() THROWS( Errno * );
public: void unload() THROWS( Errno * );

public: boolean isLoaded() const;

public: virtual void *getSymbolAddress( String aSymbol ) 
  THROWS( NoEntity * ) = 0;

public: void setPortableName( String aName );
public: void setPlatformName( String aName );

public: String getPortableName() const;
public: String getPlatformName() const;

public: virtual String convertPortableToPlatform( String aName ) const = 0;
public: virtual void platformLoad() THROWS( Errno * ) = 0;
public: virtual void platformUnload() THROWS( Errno * ) = 0;

public:  virtual String  getString() const;

protected: boolean loaded;
protected: Index   moduleRefCount;
protected: String  portableName;
protected: String  platformName;

protected: static List *loadedModules;
};

END_QR_NAMESPACE

/*
 * $Log: DynamicModule.hpp,v $
 * Revision 1.2  2001/06/23 19:02:50  philogelos
 * ::getString() added for DynamicModule and SolarisDL
 *
 * Revision 1.1.1.1  2000/07/19 17:13:53  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.3  2000/04/09 12:00:47  god
 * CVS Log keyword correction finished
 *
 * Revision 1.2  2000/04/09 11:29:36  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1  2000/04/07 18:03:14  god
 * Added
 *
 * Revision 1.1  2000/04/04 13:10:29  god
 * Initial revision
 * */

/* __DYNAMICMODULE_HPP__ */
#endif
