// -*-C++-*- 

/*  inc/KOI8RConverter.hpp  */

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



#ifndef __KOI8RCONVERTER_HPP__
#define __KOI8RCONVERTER_HPP__

/* $Id: KOI8RConverter.hpp,v 1.1.1.1 2000/07/19 16:55:57 philogelos Exp $ */

#include "CodesetConverter.hpp"
#include "Object.hpp"
#include "defines.h"

BEGIN_QR_NAMESPACE



/**

   @author Philogelos
   @created
*/
class KOI8RConverter : virtual public CodesetConverter,
					   virtual public Object
{

  /**
   */
public: KOI8RConverter();

  /**
   */
public: virtual ~KOI8RConverter();


public:  virtual unichar fromBits( const char *const aSource, Index *aBytesRead );
public:  virtual char *toBits( const unichar aChar, 
							   char * anArena,
							   Index *aBytesWritten );

  /**
   */
public:  virtual boolean equals( const Top *anOther ) const;

  /**
   */
public:  virtual Top *clone() const;

  /**
   */
public:  virtual String  getClassName() const;

public:  static KOI8RConverter *getDefaultKOI8RConverter();

protected: static KOI8RConverter *instance;
};

typedef struct { 
  unsigned char offset;
  unsigned char page;
} UnicodeData;

#define UNULL ( ( unsigned char * ) NULL )
END_QR_NAMESPACE

/*
 * $Log: KOI8RConverter.hpp,v $
 * Revision 1.1.1.1  2000/07/19 16:55:57  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:16  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:38  god
 * Imported sources
 *
 * Revision 1.2  1999/03/03 19:09:02  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.1  1999/02/28 12:47:08  philogelos
 * *** empty log message ***
 * */

/* __KOI8RCONVERTER_HPP__ */
#endif
