// -*-C++-*- 

/*  inc/platform/threads/RWLock.hpp  */

/*
 * Author: Philogelos A. <Philogelos@yahoo.com>
 * Maintainer: Philogelos A.
 * Keywords: C++, library, containers
 *
 * Copyright (C) 1999, 2000 Philogelos A.
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



#ifndef __RWLOCK_HPP__
#define __RWLOCK_HPP__

/* $Id: RWLock.hpp,v 1.1.1.1 2000/07/19 17:14:40 philogelos Exp $ */

#include "Protector.hpp"
#include "defines.h"

BEGIN_QR_NAMESPACE

/**
   Interface to the read/write locks.

   @author Philogelos
   @created Sat Apr 29 16:36:06 2000
*/
interface RWLock : public virtual Protector
{
 public: typedef enum { readLock, writeLock } LockType;
 public: virtual void enterRead( const Top * = null ) = 0;
 public: virtual void enterWrite( const Top * = null ) = 0;
 public: virtual void leave( const Top * = null ) = 0;
 public: virtual boolean tryEnterRead() = 0;
 public: virtual boolean tryEnterWrite() = 0;

 public: virtual void enter( const Top * = null );
 public: virtual void enterByType( LockType aType );
 public: virtual boolean tryEnter( LockType aType );
};

END_QR_NAMESPACE

/*
 * $Log: RWLock.hpp,v $
 * Revision 1.1.1.1  2000/07/19 17:14:40  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.3  2000/04/29 14:59:44  god
 * PRWLock and RWLock signatures changed to conform to Protector without hiding
 *
 * Revision 1.2  2000/04/29 14:20:59  god
 * inherited from Protector
 *
 * Revision 1.1  2000/04/29 12:46:23  god
 * Class definition created
 *
 */

/* __RWLOCK_HPP__ */
#endif
