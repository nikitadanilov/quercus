// -*-C++-*- 

/*  inc/iter/enumerations/TypedEnumeration.hpp  */


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


#ifndef __TYPEDENUMERATION_HPP__
#define __TYPEDENUMERATION_HPP__

/* $Id: TypedEnumeration.hpp,v 1.1.1.1 2000/07/19 17:02:16 philogelos Exp $ */

#include "Enumeration.hpp"
#include "defines.h"

BEGIN_QR_NAMESPACE

class InvalidArgument;
/**

   @author Philogelos
   @created Пнд 21 Сен 1998 14:22:42
*/
template< class X > abstract class TypedEnumeration : public virtual Enumeration
{
public: virtual X *getNextTypedElement() = 0;

public: virtual Top *getNextElement();

public: static TypedEnumeration< X > *upcast( Enumeration *aBase );
};

template< class X > class EnumerationUpcaster : public TypedEnumeration< X >, 
												virtual public Object
{
public: EnumerationUpcaster( Enumeration *aBase );
public: virtual ~EnumerationUpcaster();
public: virtual X *getNextTypedElement() THROWS( InvalidArgument * );
public: virtual boolean hasMoreElements();

public:  virtual String  getClassName() const;

protected: Enumeration *base;
};

END_QR_NAMESPACE

#if defined( INCLUDE_TEMPLATES )
#include "src/iter/enumerations/TypedEnumeration.tpp"
#endif

/*
 * $Log: TypedEnumeration.hpp,v $
 * Revision 1.1.1.1  2000/07/19 17:02:16  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:35  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:40  god
 * Imported sources
 *
 * Revision 1.2  1999/03/03 19:09:20  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.1.1.1  1998/11/25 20:11:07  philogelos
 * Quercus Robusta
 * */

/* __TYPEDENUMERATION_HPP__ */
#endif
