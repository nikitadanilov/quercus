// -*-C++-*- 

/*  inc/Guard.hpp  */


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


#ifndef __GUARD_HPP__
#define __GUARD_HPP__

/* $Id: Guard.hpp,v 1.1.1.1 2000/07/19 16:55:41 philogelos Exp $ */

#include "Object.hpp"
#include "defines.h"

/**
   Iff this is defined Guard will not inherit from Object.
   This is big performance boost as instances of sub-classes of Guard,
   such as OGuard and MGuard are created very frequently and
   execution of Object and Top constructors can take considerable amout of 
   time, especially if MEMORY_LEAK_TEST and TRACK_BACKPOINTERS are defined
   (and even more in multi-threaded setting where Top::Top have to lock 
   global mutex!). This has disadvantage that guards cannot used as the rest
   of library objects, but it is not really needed anyway.

   @see MEMORY_LEAK_TEST
   @see TRACK_BACKPOINTERS
   @see Top::Top()
 */
#define LIGHTWEIGHT_GUARD

#if defined( WANT_LIGHTWEIGHT_GUARD )
#define LIGHTWEIGHT_GUARD
#elif defined( UNWANT_LIGHTWEIGHT_GUARD )
#if defined( LIGHTWEIGHT_GUARD )
#undef LIGHTWEIGHT_GUARD
#endif
#endif


#if defined( LIGHTWEIGHT_GUARD )
#define GUARD_INHERITANCE_CLAUSE
#else
#define GUARD_INHERITANCE_CLAUSE : virtual public Object
#endif

BEGIN_QR_NAMESPACE

/**
   Marker interface for objects whose sole purpose is to produce
   some side effects in constructor and destructor.
   Examples: lock mutex in constructor and unlock it in destructor,
   create some dependant object in constructor and delete it in destructor etc.
   See also auto_ptr in libstdc++.

   @author Philogelos
   @created Чтв 10 Сен 1998 20:41:15
*/
interface Guard GUARD_INHERITANCE_CLAUSE
{
};

END_QR_NAMESPACE

/*
 * $Log: Guard.hpp,v $
 * Revision 1.1.1.1  2000/07/19 16:55:41  philogelos
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
 * Revision 1.1.1.1  1998/11/25 20:11:05  philogelos
 * Quercus Robusta
 * */

/* __GUARD_HPP__ */
#endif
