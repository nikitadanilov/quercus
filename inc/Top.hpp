//-*-C++-*-

/*  inc/Top.hpp  */


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


#ifndef __TOP_HPP__

#define __TOP_HPP__

/* $Id: Top.hpp,v 1.1.1.1 2000/07/19 16:58:00 philogelos Exp $ */

#include "defines.h"

#define MEMORY_LEAK_TEST
#define TRACK_BACKPOINTERS
#define BACKPOINTERS_LIST_LEN  10
#define USE_TYPEID

#if defined( WANT_MEMORY_LEAK_TEST )
#define MEMORY_LEAK_TEST
#elif defined( UNWANT_MEMORY_LEAK_TEST )
#if defined( MEMORY_LEAK_TEST )
#undef MEMORY_LEAK_TEST
#endif
#endif

#if defined( WANT_TRACK_BACKPOINTERS )
#define TRACK_BACKPOINTERS
#elif defined( UNWANT_TRACK_BACKPOINTERS )
#if defined( TRACK_BACKPOINTERS )
#undef TRACK_BACKPOINTERS
#endif
#endif

#if defined( WANT_BACKPOINTERS_LIST_LEN )
#define BACKPOINTERS_LIST_LEN WANT_BACKPOINTERS_LIST_LEN
#endif

#if defined( WANT_USE_TYPEID )
#define USE_TYPEID
#elif defined( UNWANT_USE_TYPEID )
#if defined( USE_TYPEID )
#undef USE_TYPEID
#endif
#endif


BEGIN_QR_NAMESPACE

#if defined( USE_THREADS )
class Mutex;
#endif

class String;
class Object;
interface Protector;
interface LifeTimeController;

/** Terminal interface in sub-typing lattice.
	Every class in system implements this interface.
	Default implementation proveded by Object.

	@see Object
	@author Philogelos
	@created «‚“ 18 ∏Ó› 1998 17:38:49
*/
interface Top
{
 protected: Top();
 public: virtual ~Top();

 public:  virtual boolean equals( const Top *Top ) const = 0;
 public:  virtual Top    *clone() const = 0;
 public:  virtual String  toString() const = 0;
 public:  virtual String  getString() const = 0;
 public:  virtual String  getClassName() const
#if !defined( USE_TYPEID )
			= 0
#endif
			;

 public:  virtual boolean invariant() const = 0;

 public:  virtual Protector *getProtector() const = 0;
 public:  virtual void setProtector( Protector *aProtector ) = 0;

 public:  virtual void lock( const Top *anOwner ) const = 0;
 public:  virtual void unlock( const Top *anOwner ) const = 0;
 public:  virtual void lockRead( const Top *anOwner ) const = 0;

 public:  virtual void setLifeTimeController( LifeTimeController *aController ) = 0;
 public:  virtual LifeTimeController *getLifeTimeController() const = 0;

 public:  virtual void addRef() const = 0;
 public:  virtual void delRef() const = 0;
 public:  virtual Index getRefCount() const = 0;
 public:  virtual boolean isRef() const = 0;

 public:  virtual boolean isBeingDeleted() const = 0;
 public:  virtual void setBeingDeleted( boolean aFlag ) const = 0;
#if defined( MEMORY_LEAK_TEST )
 public:  Top *nextInAllocatedChain;
 public:  Top *prevInAllocatedChain;
 public:  static Top *firstInAllocatedChain;
 public:  static Top *lastInAllocatedChain;

 public:  static void dumpAllocated();

#if defined( USE_THREADS )
 public: static Mutex *topLock;
#endif

/* MEMORY_LEAK_TEST */
#endif

#if defined( TRACK_BACKPOINTERS ) 
 public:  mutable Top *backpointers[ BACKPOINTERS_LIST_LEN ];
#if defined( MEMORY_LEAK_TEST )
 public:  static void dumpBackpointers();
#endif
#endif

#if defined( USE_THREADS )
 public: static void initThreads();
#endif
};

END_QR_NAMESPACE

/*
 * $Log: Top.hpp,v $
 * Revision 1.1.1.1  2000/07/19 16:58:00  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.3  2000/04/29 14:38:09  god
 * ::lockRead() added
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
 * Revision 1.2  1999/02/28 12:41:43  philogelos
 * *** empty log message ***
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
 * Revision 1.1.1.1  1998/04/01 17:15:29  philogelos
 * first version under CVS
 * */

/* __TOP_HPP__ */
#endif

