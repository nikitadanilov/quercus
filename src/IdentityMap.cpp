// -*-C++-*- 

/*  src/IdentityMap.cpp  */


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


/* $Id: IdentityMap.cpp,v 1.1.1.1 2000/07/19 16:40:46 philogelos Exp $ */
#if !defined(_INLINE)
static char cvsid[] = "@(#)$Id: IdentityMap.cpp,v 1.1.1.1 2000/07/19 16:40:46 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif


#include "IdentityMap.hpp"
#include "Debug.hpp"

BEGIN_QR_NAMESPACE

Top *IdentityMap::apply( Top *anArgument )
{
  return( anArgument );
}

END_QR_NAMESPACE

#if defined(_INLINE)
#include "../src/Debug.ipp"
#endif


/*
 * $Log: IdentityMap.cpp,v $
 * Revision 1.1.1.1  2000/07/19 16:40:46  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:38  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:28  god
 * Imported sources
 *
 * Revision 1.3  1999/03/03 19:09:26  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.2  1999/02/28 15:47:16  philogelos
 * Tuned for inlines.
 *
 * Revision 1.1  1998/12/01 16:30:05  philogelos
 * created
 * */
