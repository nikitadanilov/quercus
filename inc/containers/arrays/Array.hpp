// -*-C++-*- 

/*  inc/containers/arrays/Array.hpp  */


/*
 * Author: Philogelos A. <Philogelos@yahoo.com>
 * Maintainer: Philogelos A.
 * Keywords: C++, library, containers
 *
 * Copyright (C) 1998, 1999 Philogelos A.
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


#ifndef __ARRAY_HPP__
#define __ARRAY_HPP__

/* $Id: Array.hpp,v 1.1.1.1 2000/07/19 17:00:10 philogelos Exp $ */

#include "containers/RangedContainer.hpp"
#include "defines.h"

BEGIN_QR_NAMESPACE

/**
   Array: data structure with constant access time.
   
   @author Philogelos
   @created ≤‚‡ 23 ∏Ó› 1998 19:44:52
*/
class Array : public RangedContainer
{
protected: Array();
};

END_QR_NAMESPACE

/*
 * $Log: Array.hpp,v $
 * Revision 1.1.1.1  2000/07/19 17:00:10  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:34  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:45  god
 * Imported sources
 *
 * Revision 1.3  1999/03/03 19:09:14  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.2  1999/02/28 15:34:32  philogelos
 * Copyright updated
 *
 * Revision 1.1.1.1  1998/11/25 20:11:06  philogelos
 * Quercus Robusta
 *
 * Revision 1.1  1998/07/09 09:30:32  philogelos
 * new files added to the repository
 * */

/* __ARRAY_HPP__ */
#endif
