// -*- C++ -*-

/*  inc/StringEnumeration.hpp  */


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



#ifndef __STRINGENUMERATION_HPP__
#define __STRINGENUMERATION_HPP__

/* $Id: StringEnumeration.hpp,v 1.1.1.1 2000/07/19 16:57:59 philogelos Exp $ */

#include "Char.hpp"
#include "Object.hpp"
#include "String.hpp"
#include "algorithms/parse/WordParser.hpp"
#include "iter/enumerations/TypedEnumeration.hpp"

BEGIN_QR_NAMESPACE

interface CodesetConverter;

/**
   String represented as sequence.

   @author Philogelos
   @created ø‚› 19 ∏Ó› 1998 16:21:20
*/
class StringEnumeration : public virtual CharEnumeration,
						  virtual public Object
{
  /**
	 @postcond ( getString().equals( aString ) )
  */
public: StringEnumeration( String aString );
public: virtual ~StringEnumeration();

public: virtual boolean hasMoreElements();
public: virtual Char *getNextCharFast();

public:  virtual String  getString() const;

public:  virtual String  toString() const;
public:  virtual String  getClassName() const;

protected: const String core;
protected: Index  position;
};

END_QR_NAMESPACE

/*
 * $Log: StringEnumeration.hpp,v $
 * Revision 1.1.1.1  2000/07/19 16:57:59  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:17  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:38  god
 * Imported sources
 *
 * Revision 1.3  1999/03/03 19:09:05  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.2  1999/02/28 12:41:18  philogelos
 * Enumeration made typed and using of Char interface
 *
 * Revision 1.1.1.1  1998/11/25 20:11:04  philogelos
 * Quercus Robusta
 *
 * Revision 1.3  1998/07/07 14:29:50  philogelos
 * Memory leak in SUNWspro dynamic_cast fixed.
 *
 * Revision 1.2  1998/06/22 18:12:56  philogelos
 * Enumerations and containers added
 *
 * Revision 1.1.1.1  1998/06/22 08:47:11  philogelos
 * First version under CVS
 *
 * Revision 1.1.1.1  1998/04/01 17:15:30  philogelos
 * first version under CVS
 * */

/* __STRINGENUMERATION_HPP__ */
#endif
