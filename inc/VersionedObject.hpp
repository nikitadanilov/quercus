// -*-C++-*- 

/*  inc/VersionedObject.hpp  */


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


#ifndef __VERSIONEDOBJECT_HPP__
#define __VERSIONEDOBJECT_HPP__

/* $Id: VersionedObject.hpp,v 1.1.1.1 2000/07/19 16:58:07 philogelos Exp $ */

#include "Object.hpp"
#include "defines.h"

BEGIN_QR_NAMESPACE

typedef Index Version;

/**

   @author Philogelos
   @created
*/
class VersionedObject : public virtual Object
{
public: static Version FirstVersion;

  /**
	*/
public: VersionedObject();

  /**
	*/
public: virtual ~VersionedObject();


public: Version getVersion() const;
public: void    setVesrion( const Version aVersion );
public: boolean isOlderOrEqual( const VersionedObject *anObject );
public: void    upgrade();

  /**
	*/
public:  virtual String  getClassName() const;

protected: Version version;

};

END_QR_NAMESPACE

/*
 * $Log: VersionedObject.hpp,v $
 * Revision 1.1.1.1  2000/07/19 16:58:07  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:17  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:39  god
 * Imported sources
 *
 * Revision 1.3  1999/03/03 19:09:06  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.2  1999/02/28 12:45:50  philogelos
 * Copyright updated
 *
 * Revision 1.1.1.1  1998/11/25 20:11:05  philogelos
 * Quercus Robusta
 * */

/* __VERSIONEDOBJECT_HPP__ */
#endif
