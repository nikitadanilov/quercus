//-*-C++-*-

/*  inc/StringImplementation.hpp  */


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


#ifndef __STRING_IMPLEMENTATION_H__
#define __STRING_IMPLEMENTATION_H__

/* $Id: StringImplementation.hpp,v 1.1.1.1 2000/07/19 16:57:59 philogelos Exp $ */

#include "RefCounted.hpp"
#include "MemoryAllocator.hpp"

BEGIN_QR_NAMESPACE



/** 
	This class used by class String to store characters.
	Main idea is that StringImplementation counts links
	to itself and deletes itself when no more links exist providing
	therefore rudimentary form of garbage collection.
*/
class StringImplementation : public RefCounted
{
  friend class String;

public:  StringImplementation( unichar *s, 
							   boolean shouldCopy = true, 
							   boolean shouldDelete = true );

public:  virtual ~StringImplementation();
public:  operator unichar *( void ) const;
public:  unichar &operator []( const Index i ) const;
public:  const Index length( void ) const;

public:  virtual String  toString() const;
public:  virtual String  getString() const;
public:  virtual String  getClassName() const;

public:  static StringImplementation *createNil( void );
public:  static StringImplementation *getNil( void );

protected:  unichar *core;
protected:  Index len;
protected:  boolean haveToCopy :1;
protected:  boolean haveToDelete :1;
protected:  static StringImplementation *nilStringImplementation;

#if defined( USE_PER_CLASS_NEW )
public: void *operator new( size_t size );
public: void  operator delete( void *anAddress );
protected: static MemoryAllocator *getAllocator();
protected: static MemoryAllocator *allocator;
#endif
};

END_QR_NAMESPACE

/*
 * $Log: StringImplementation.hpp,v $
 * Revision 1.1.1.1  2000/07/19 16:57:59  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:17  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:38  god
 * Imported sources
 *
 * Revision 1.4  1999/05/22 13:00:23  philogelos
 * Merging sources back from SPARC
 *
 * Revision 1.3  1999/03/03 19:09:05  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.2  1999/02/28 12:40:06  philogelos
 * *** empty log message ***
 *
 * Revision 1.1.1.1  1998/11/25 20:11:04  philogelos
 * Quercus Robusta
 *
 * Revision 1.4  1998/07/09 09:04:42  philogelos
 * custom new/delete added
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

/* __STRING_IMPLEMENTATION_H__ */
#endif
