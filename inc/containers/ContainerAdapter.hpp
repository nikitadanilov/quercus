// -*- C++ -*-

/*  inc/containers/ContainerAdapter.hpp  */


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



#ifndef __CONTAINERADAPTER_HPP__
#define __CONTAINERADAPTER_HPP__

/* $Id: ContainerAdapter.hpp,v 1.1.1.1 2000/07/19 16:59:21 philogelos Exp $ */

#include "Map.hpp"
#include "Object.hpp"
#include "Container.hpp"

BEGIN_QR_NAMESPACE

/**
   Default implementation for containers.
   Implements unmodifiable container.

   @author Philogelos
   @created ø›‘ 22 ∏Ó› 1998 17:55:04
*/
abstract class ContainerAdapter : public virtual Container,
								  virtual public Object
{
protected: ContainerAdapter();
public: ~ContainerAdapter();

public:  virtual boolean isEmpty() const;

public:  virtual PositionEnumeration *getEnumeration() const = 0;
public:  virtual Iterator            *getIterator() const;

public:  virtual Enumeration *getValueEnumeration() const;
public:  virtual Iterator    *getValueIterator() const;

public:  virtual Index        getCardinality() const;
public:  virtual boolean contains( const Top *anElement ) const;
public:  virtual Position *find( const Top *anObject ) const;

public:  virtual boolean   isValid ( const Position *aPosition ) const;

public:  virtual String  print( String ( Top::* aMethod )() const ) const;

public:  virtual String  getPrintHeader() const;
public:  virtual String  getPrintSeparator() const;
public:  virtual String  getPrintFooter() const;
public:  virtual String  getEllipsis() const;
public:  virtual Index   getMaxPrintCount() const;
  
public:  virtual boolean equals( const Top *anOther ) const;
public:  virtual String  toString() const;
public:  virtual String  getString() const;
public:  virtual String  getClassName() const;

public:  virtual Top   *getValue( const Position *aPosition );

public:    virtual Map *getAsMap() const;
protected: static Index maxPrintCount;
protected: class ContainerMap : public Map, virtual public Object
 {
   public: ContainerMap( Container *aHost );
   public: Top *apply( Top *anArg ) THROWS( InvalidArgument * );

   protected: Container *container;
};

};

END_QR_NAMESPACE

/*
 * $Log: ContainerAdapter.hpp,v $
 * Revision 1.1.1.1  2000/07/19 16:59:21  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:33  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:44  god
 * Imported sources
 *
 * Revision 1.3  1999/03/03 19:09:08  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.2  1999/02/28 12:52:42  philogelos
 * Sub-typed from Object (virtually)
 *
 * Revision 1.1.1.1  1998/11/25 20:11:05  philogelos
 * Quercus Robusta
 *
 * Revision 1.1  1998/07/09 09:30:27  philogelos
 * new files added to the repository
 *
 * Revision 1.1.1.1  1998/06/22 08:47:11  philogelos
 * First version under CVS
 *
 * Revision 1.1.1.1  1998/04/01 17:15:30  philogelos
 * first version under CVS
 * */

/* __CONTAINERADAPTER_HPP__ */
#endif
