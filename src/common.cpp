// -*-C++-*- 

/*  src/common.cpp  */

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

#if !defined(__COMMON_CPP__)
#define __COMMON_CPP__

/* $Id: common.cpp,v 1.1.1.1 2000/07/19 16:42:55 philogelos Exp $ */
#if !defined(_INLINE) && !defined(INCLUDE_TEMPLATES)
static char cvsid[] = "@(#)$Id: common.cpp,v 1.1.1.1 2000/07/19 16:42:55 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif

#include "defines.h"

#if defined(INCLUDE_TEMPLATES)

BEGIN_QR_NAMESPACE

class Debug;
class Top;

#else

#include "Debug.hpp"
#include "Top.hpp"

BEGIN_QR_NAMESPACE

#endif

#if (!defined(INCLUDE_TEMPLATES) && !defined(__COMMON_FROM_DEFINES__)) || (defined(INCLUDE_TEMPLATES) && defined(__COMMON_FROM_DEFINES__))

template< class X > X *brainDamagedDynamicCast( Top *aValue, X * )
{
  return dynamic_cast< X * >( aValue );
}

#include "debug-macros.hpp"

template< class X > X *castOrThrow( Top *aValue, X * )
{
  X *value;

  value = DCAST( aValue, X );
  testF( value != ( X * ) NIL, "cast failed" );
  return value;
}

#endif

END_QR_NAMESPACE

/*
 * $Log: common.cpp,v $
 * Revision 1.1.1.1  2000/07/19 16:42:55  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:40  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:29  god
 * Imported sources
*/

/* __COMMON_CPP__ */
#endif
