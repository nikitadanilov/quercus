// -*-C++-*- 

/*  inc/containers/arrays/CArray.hpp  */


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


#ifndef __CARRAY_HPP__
#define __CARRAY_HPP__

/* $Id: CArray.hpp,v 1.1.1.1 2000/07/19 17:00:10 philogelos Exp $ */

#include "Array.hpp"
#include "containers/MutableContainerAdapter.hpp"
#include "defines.h"



BEGIN_QR_NAMESPACE

/**
   Default implementation of Array interface.
   C for C (the language).

   @author Philogelos
   @created ²âà 23 ¸îÝ 1998 20:01:52
*/
class CArray : public Array, public MutableContainerAdapter
{
  /**
	 @precond ( aLen >= 0 )
  */
public: CArray( Index aBase, Index aLength );

public: virtual ~CArray();

public: Index getBase() const;
public: Index getLength() const;

public: virtual Index getLowBound() const;
public: virtual Index getHighBound() const;

public: virtual String  getClassName() const;

public: virtual Top *getAt( const Index anIndex ) const;
public: virtual Top *setAt( const Index anIndex, Top *aNewValue );

public: virtual void clearAll();

  /*
	We need explicitly define following methods,
	otherwise C++ complains about ``has two overriders''
	(in base case, gcc message is incomprehensible),
	although in fact one of those overriders is always
	pure virtual.
   */
public: virtual MutablePositionEnumeration *getMutableEnumeration() const;
public: virtual PositionEnumeration *getEnumeration() const;
public: virtual Index        getCardinality() const;
public: virtual boolean      isValid( const Position *aPosition ) const;

#if defined( TESTING )
public:  virtual boolean tester( int aParam ) const;
#endif

protected: Top const **core;
protected: Index base;
protected: Index length;
};

END_QR_NAMESPACE

/*
 * $Log: CArray.hpp,v $
 * Revision 1.1.1.1  2000/07/19 17:00:10  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:34  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:45  god
 * Imported sources
 *
 * Revision 1.4  1999/03/03 19:09:14  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.3  1999/02/28 15:34:33  philogelos
 * Copyright updated
 *
 * Revision 1.2  1998/12/01 16:16:49  philogelos
 * conditionally compile ::tester()
 *
 * Revision 1.1.1.1  1998/11/25 20:11:06  philogelos
 * Quercus Robusta
 *
 * Revision 1.1  1998/07/09 09:30:32  philogelos
 * new files added to the repository
 * */

/* __CArray_HPP__ */
#endif
