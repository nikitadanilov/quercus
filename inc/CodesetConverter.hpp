// -*-C++-*- 

/*  inc/CodesetConverter.hpp  */

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



#ifndef __CODESETCONVERTER_HPP__
#define __CODESETCONVERTER_HPP__

/* $Id: CodesetConverter.hpp,v 1.1.1.1 2000/07/19 16:55:12 philogelos Exp $ */

#include "Top.hpp"
#include "defines.h"

BEGIN_QR_NAMESPACE

class Char;
/**
   Interface for character encodings.

   @see Char
   @author Philogelos
   @created
*/
abstract class CodesetConverter : virtual public Top
{
  /**
	 Creates UCS2 representation from bit-pattern.
	 Should throw Runtime exception if format is invalid.

	 Puts number of bytes read into aBytesRead.

	 @see RuntimeError

	 @precond ( aBytesRead != NULL )
  */
 public:  virtual unichar fromBits( const char *const aSource, 
									Index *aBytesRead ) = 0;
  /**
	 Same as ::fromBits() with different calling interface.
	 
	 @see #fromBits()
	 @precond ( aBytesRead != NULL )
  */
 public:  virtual Char *charFromBits( const char *const aSource, 
									  Index *aBytesRead );

  /**
	 Returns bit-pattern of given UCS2 character in this encoding.
	 If anArena is not null, pattern is written there, otherwise
	 fresh array is allocated.
	 Puts length of bit-pattern into aBytesWritten.

	 @precond ( aBytesWritten != NULL )
  */
 public:  virtual char *toBits( const unichar aChar, 
								char * anArena,
								Index *aBytesWritten ) = 0;

  /**
	 Same as ::toBits() with different calling interface.
	 
	 @see #toBits()
  */
 public:  virtual char *charToBits( const Char *aChar, 
									char * anArena,
									Index *aBytesWritten );
};

END_QR_NAMESPACE

/*
 * $Log: CodesetConverter.hpp,v $
 * Revision 1.1.1.1  2000/07/19 16:55:12  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:16  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:37  god
 * Imported sources
 *
 * Revision 1.2  1999/03/03 19:09:01  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.1  1999/02/28 12:47:07  philogelos
 * *** empty log message ***
 * */

/* __CODESETCONVERTER_HPP__ */
#endif
