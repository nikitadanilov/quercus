// -*-C++-*- 

/*  inc/algorithms/string/StringFilterAdapter.hpp  */

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



#ifndef __STRINGFILTERADAPTER_HPP__
#define __STRINGFILTERADAPTER_HPP__

/* $Id: StringFilterAdapter.hpp,v 1.1.1.1 2000/07/19 16:58:53 philogelos Exp $ */

#include "StringFilter.hpp"
#include "defines.h"



BEGIN_QR_NAMESPACE

/**

   @author Philogelos
   @created
!*/
abstract class StringFilterAdapter : public virtual StringFilter
{

  /**
   */
public: StringFilterAdapter();
public: StringFilterAdapter( StringFilter *aBase );

  /**
   */
public: virtual ~StringFilterAdapter();

public: virtual void setBase( StringFilter *aBase );
public: virtual StringFilter *getBase();
public: virtual String asString();
public: virtual String restAsString();
public: virtual Index length();
public: virtual Index rest();
public: virtual unichar getNext() = 0;
public: virtual Index getPosition();
public: virtual void reset();

public: Index getCounter() const;
  
protected: StringFilter *base;
protected: Index counter;
protected: Index position;
};


END_QR_NAMESPACE

/*
 * $Log: StringFilterAdapter.hpp,v $
 * Revision 1.1.1.1  2000/07/19 16:58:53  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:17  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:43  god
 * Imported sources
*/

/* __STRINGFILTERADAPTER_HPP__ */
#endif
