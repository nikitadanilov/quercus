// -*-C++-*- 

/*  src/platform/threads/MGuard.cpp  */

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



/* $Id: MGuard.cpp,v 1.2 2001/03/06 17:44:55 philogelos Exp $ */
#if !defined(_INLINE)
static char cvsid[] = "@(#)$Id: MGuard.cpp,v 1.2 2001/03/06 17:44:55 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif

#include "platform/threads/MGuard.hpp"
#include "platform/threads/Mutex.hpp"
#include "LinkManager.hpp"
#include "String.hpp"
#include "Debug.hpp"

BEGIN_QR_NAMESPACE

MGuard::MGuard( Mutex *aMutex, Top * )
{
  preC_( aMutex != NIL );

  mutex = aMutex;
  /* LinkManager::reg( mutex, mutex ); XXX */
  mutex -> enter();
}

MGuard::~MGuard()
{
  mutex -> leave();
  /* LinkManager::free( mutex, mutex ); */
}

String  MGuard::getClassName() const
{
  return "MGuard";
}

END_QR_NAMESPACE

#if defined(_INLINE)
#include "../src/Debug.ipp"
#endif


/*
 * $Log: MGuard.cpp,v $
 * Revision 1.2  2001/03/06 17:44:55  philogelos
 * _Don't_ lock mutex itself
 *
 * Revision 1.1.1.1  2000/07/19 16:51:35  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:44  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:35  god
 * Imported sources
*/
