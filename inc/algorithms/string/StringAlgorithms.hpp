// -*-C++-*- 

/*  inc/algorithms/string/StringAlgorithms.hpp  */

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



#ifndef __STRINGALGORITHMS_HPP__
#define __STRINGALGORITHMS_HPP__

/* $Id: StringAlgorithms.hpp,v 1.1.1.1 2000/07/19 16:58:48 philogelos Exp $ */

#include "StringFilter.hpp"

#include "algorithms/AlgorithmPackage.hpp"
#include "Object.hpp"
#include "defines.h"



BEGIN_QR_NAMESPACE

/**
   Shortcut for getting singleton instance of
   class StringAlgorithms.

   @see StringAlgorithms
   @see EALG
*/
#define SALG SAlg::get()

/**
   Strings algorithms.

   @author Philogelos
   @created
*/
class StringAlgorithms : public virtual AlgorithmPackage,
						 public virtual Object
{
  /**
	 Converts occurences of the given filter in the given string
	 to the lower case.
  */
public: virtual void toLower( String aString, StringFilter *aFilter );

  /**
	 Converts occurences of the given filter in the given string
	 to the upper case.
  */
public: virtual void toUpper( String aString, StringFilter *aFilter );

  /**
	 Returns number of occurences of the given filter in the given string.
  */
public: virtual Index length( String aString, StringFilter *aFilter );

  /**
	 True iff there is at least one occurence of the given filter 
	 within the given string.
  */
public: virtual Index isEmpty( String aString, StringFilter *aFilter );

  /**
	 Replaces all occurences of the given filter 
	 within the given string to the given character.
  */
public: virtual void replace( String aString, StringFilter *aFilter, 
							  unichar aTo );
  
  
  /**
	 Returns singleton instance of this class.

	 @see #instance
  */
public: static StringAlgorithms *get();

  /**
	 Returns "StringAlgorithms".
   */
public:  virtual String  getClassName() const;

  /**
	 Nop.
   */
protected: StringAlgorithms();
protected: virtual ~StringAlgorithms();

  /**
	 Singleton instance.

	 @see #get()
  */
protected: static StringAlgorithms *instance;

#if defined( TESTING )
public:  virtual boolean tester( int aParam ) const;
#endif
};

/**
   Shortcut.
*/
typedef StringAlgorithms SAlg;


END_QR_NAMESPACE

/*
 * $Log: StringAlgorithms.hpp,v $
 * Revision 1.1.1.1  2000/07/19 16:58:48  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:17  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:43  god
 * Imported sources
*/

/* __STRINGALGORITHMS_HPP__ */
#endif
