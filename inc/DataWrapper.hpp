// -*-C++-*- 

/*  inc/DataWrapper.hpp  */

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



#ifndef __DATAWRAPPER_HPP__
#define __DATAWRAPPER_HPP__

/* $Id: DataWrapper.hpp,v 1.1.1.1 2000/07/19 16:55:41 philogelos Exp $ */

#include "Object.hpp"
#include "defines.h"

BEGIN_QR_NAMESPACE



/**
   Instances of this class store single pointer to raw
   data (void *) uninterpreted by library.

   Useful when interfacing external data.

   @author Philogelos
   @created
*/
class DataWrapper : public virtual Object
{
public: DataWrapper( void *aValue );
  
public: void *getValue() const;
public: void setValue( void *aValue );
  
public: virtual String  toString() const;
public: virtual String  getString() const;
public: virtual String  getClassName() const;

protected: void *value;
};

END_QR_NAMESPACE

/*
 * $Log: DataWrapper.hpp,v $
 * Revision 1.1.1.1  2000/07/19 16:55:41  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:16  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:39  god
 * Imported sources
*/

/* __DATAWRAPPER_HPP__ */
#endif
