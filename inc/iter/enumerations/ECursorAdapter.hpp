// -*-C++-*- 

/*  inc/iter/enumerations/ECursorAdapter.hpp  */


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


#ifndef __ECURSORADAPTER_HPP__
#define __ECURSORADAPTER_HPP__

/* $Id: ECursorAdapter.hpp,v 1.1.1.1 2000/07/19 17:02:15 philogelos Exp $ */

#include "ECursor.hpp"
#include "defines.h"

BEGIN_QR_NAMESPACE



/**
   Default implementation of the ECursor interface.
   Implements ::reset() and ::ff() methods in terms of
   isAtBeginning(), getPrevElement(), hasMoreElements()
   and getNextElement().

   @see Enumeration::getNextElement()
   @see Enumeration::hasMoreElements()
   @see ECursor::getPrevElement()
   @see ECursor::isAtBeginning()

   @author Philogelos
   @created Срд 30 Сен 1998 13:21:54
*/
abstract class ECursorAdapter : public ECursor
{
  /**
	 Calls getPrevElement() until isAtBeginning()
	 effectively scrolling this enumeration to the beginning.

	 @see ECursor::getPrevElement()
	 @see ECursor::isAtBeginning()
  */
public: virtual void reset();

  /**
	 Calls getNextElement() while hasMoreElements()
	 effectively scrolling this enumeration to the end.

	 @see Enumeration::getNextElement()
	 @see Enumeration::hasMoreElements()
  */
public: virtual void ff();
};

END_QR_NAMESPACE

/*
 * $Log: ECursorAdapter.hpp,v $
 * Revision 1.1.1.1  2000/07/19 17:02:15  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:35  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:40  god
 * Imported sources
 *
 * Revision 1.2  1999/03/03 19:09:19  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.1.1.1  1998/11/25 20:11:07  philogelos
 * Quercus Robusta
 * */

/* __ECURSORADAPTER_HPP__ */
#endif
