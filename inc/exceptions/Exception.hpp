// -*-C++-*-

/*  inc/exceptions/Exception.hpp  */


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


#ifndef __EXCEPTION_HPP__
#define __EXCEPTION_HPP__

/* $Id: Exception.hpp,v 1.1.1.1 2000/07/19 17:01:31 philogelos Exp $ */

#include "Top.hpp"
#include "Object.hpp"
#include "String.hpp"
#include "Throwable.hpp"
#include "Condition.hpp"
#include "observe/ObservableAdapter.hpp"



BEGIN_QR_NAMESPACE

class Backtrace;

/** 
	This class is the root of `exceptional' hierarchy :). 
	Generally, every abnormal situation during execution of the programme
	leads to the throwing of the pointer to some subclass of Exception.
	Different subclasses represent different kinds and/or degrees of
	abnormality.
	There are although a few places where old-style return-code
	techniques are used.
	Each subclass of Exceptions redefines `description' which denotes
	class of situations this subclass designed react at. Also, every
	instance may be labeled with `message' denoting particular error 
	situation.

	@author Philogelos
	@created ÇâÒ 18 ¸îÝ 1998 20:12:27
*/
class Exception : public Throwable
#if defined( USE_STL )
                  ,virtual public std::exception
#endif
{
  /** Default constructor.*/
  /* public:  Exception(); */

  /** 
	  Creates Exception with given message and source i.e., preferrably
	  object whose method causes exception. 

	  WARNING: Be careful! Throwing of exception causes stack unwinding
	  and calling of destructors. Make yourself double sure that pointer you 
	  supply to this constructor still will be valid in catch clause.
  */
public:  Exception( String aMessage, const Top *const aSource );
public:  virtual ~Exception();

public:  virtual String getMessage() const;
public:  const   Top   *getSource() const;
public:  virtual String getDescription() const;
public:  String         getFullDescription() const;

public:  virtual String getString() const;
public:  virtual String getClassName() const;

public:  virtual Backtrace *getBacktrace() const;

  /** 
	  Pushes description of exceptional situation to given stream.
	  Uses ::getMessage() and ::getSource()->toString().
  */
  //  public:  virtual void diagnoze(Stream *) const;
  
protected:  const String message;
protected:  const Top   *source;
protected:  Backtrace *backtrace;
};

END_QR_NAMESPACE

/*
 * $Log: Exception.hpp,v $
 * Revision 1.1.1.1  2000/07/19 17:01:31  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:35  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:46  god
 * Imported sources
 *
 * Revision 1.2  1999/03/03 19:09:16  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.1.1.1  1998/11/25 20:11:06  philogelos
 * Quercus Robusta
 *
 * Revision 1.4  1998/07/10 09:15:46  philogelos
 * sub-classed from Condition
 *
 * Revision 1.3  1998/07/07 14:29:52  philogelos
 * Memory leak in SUNWspro dynamic_cast fixed.
 *
 * Revision 1.2  1998/06/22 18:12:58  philogelos
 * Enumerations and containers added
 *
 * Revision 1.1.1.1  1998/06/22 08:47:11  philogelos
 * First version under CVS
 *
 * Revision 1.1.1.1  1998/04/01 17:15:30  philogelos
 * first version under CVS
 * */

/* __EXCEPTION_HPP__ */
#endif
