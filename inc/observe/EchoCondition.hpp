// -*-C++-*- 

/*  inc/observe/EchoCondition.hpp  */

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



#ifndef __ECHOCONDITION_HPP__
#define __ECHOCONDITION_HPP__

/* $Id: EchoCondition.hpp,v 1.1.1.1 2000/07/19 17:03:13 philogelos Exp $ */

#include "Condition.hpp"
#include "Object.hpp"
#include "String.hpp"
#include "defines.h"

BEGIN_QR_NAMESPACE

class String;

/**
   Dummy condition for debugging purposes.

   @author Philogelos
   @created
*/
class EchoCondition : public Condition,
					  public virtual Object
{

  /**
	 Creates instance with given message.
   */
public: EchoCondition( String aMessage );

  /**
	 Prints message to the debug log.
  */
public: virtual void announce();

  /**
   */
public: virtual ~EchoCondition();


  /**
   */
public:  virtual Top *clone() const;

  /**
   */
public:  virtual String  toString() const;

  /**
   */
public:  virtual String  getClassName() const;

protected: const String message;
};


END_QR_NAMESPACE

/*
 * $Log: EchoCondition.hpp,v $
 * Revision 1.1.1.1  2000/07/19 17:03:13  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:36  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:47  god
 * Imported sources
*/

/* __ECHOCONDITION_HPP__ */
#endif
