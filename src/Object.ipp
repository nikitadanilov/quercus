//-*-C++-*-

/*  src/Object.ipp  */


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


/* $Id: Object.ipp,v 1.1.1.1 2000/07/19 16:41:57 philogelos Exp $ */

#include "Object.hpp"
#include "Protector.hpp"

BEGIN_QR_NAMESPACE

INLINE Object::Object()
{
  refCount = 0;
  protector = ( Protector * ) NIL;
  ltController = ( LifeTimeController * ) NIL;
  setBeingDeleted( false );
}

#if defined( USE_PER_CLASS_NEW )
INLINE void *Object::operator new( size_t size )
{
  return ::operator new( size );
}
#endif

END_QR_NAMESPACE

/*
 * $Log: Object.ipp,v $
 * Revision 1.1.1.1  2000/07/19 16:41:57  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.4  2000/04/09 12:00:48  god
 * CVS Log keyword correction finished
 *
 * Revision 1.3  2000/04/09 11:29:39  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.2  2000/04/07 12:30:51  god
 * namespace corrected
 *
 * Revision 1.1.1.1  2000/04/01 14:07:28  god
 * Imported sources
 *
 * Revision 1.3  1999/05/22 13:00:30  philogelos
 * Merging sources back from SPARC
 *
 * Revision 1.2  1999/03/03 19:09:29  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.1.1.1  1998/11/25 20:11:01  philogelos
 * Quercus Robusta
 *
 * Revision 1.1.1.1  1998/06/22 08:47:12  philogelos
 * First version under CVS
 *
 * Revision 1.1.1.1  1998/04/01 17:15:28  philogelos
 * first version under CVS
 * */
