// -*- C++ -*-

/*  src/iter/enumerations/SingletonEnumeration.cpp  */


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


/* $Id: SingletonEnumeration.cpp,v 1.1.1.1 2000/07/19 16:50:11 philogelos Exp $ */
#if !defined(_INLINE)
static char cvsid[] = "@(#)$Id: SingletonEnumeration.cpp,v 1.1.1.1 2000/07/19 16:50:11 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif


#include "iter/enumerations/SingletonEnumeration.hpp"
#include "Debug.hpp"
#include "LinkManager.hpp"

BEGIN_QR_NAMESPACE

SingletonEnumeration::SingletonEnumeration( Top *aContent ) :
  content( aContent )
{
  if( content != nil )
	{
	  OREG( content );
	}
  wasFired = false;
}

SingletonEnumeration::~SingletonEnumeration()
{
  FCDONE( content );
}

boolean SingletonEnumeration::hasMoreElements()
{
  return ( ! wasFired );
}

Top *SingletonEnumeration::getNextElement()
{
  preC_( hasMoreElements() );
  wasFired = true;
  return content;
}

void SingletonEnumeration::reset()
{
  wasFired = false;
}

Top *SingletonEnumeration::clone() const
{
  return new SingletonEnumeration( content );
}

END_QR_NAMESPACE

#if defined(_INLINE)
#include "../src/Debug.ipp"
#endif

/*
 * $Log: SingletonEnumeration.cpp,v $
 * Revision 1.1.1.1  2000/07/19 16:50:11  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:43  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:29  god
 * Imported sources
 *
 * Revision 1.3  1999/03/03 19:09:45  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.2  1999/02/28 16:30:48  philogelos
 * Tuned for inlines.
 *
 * Revision 1.1.1.1  1998/11/25 20:11:03  philogelos
 * Quercus Robusta
 *
 * Revision 1.1  1998/07/09 09:30:46  philogelos
 * new files added to the repository
 * */
