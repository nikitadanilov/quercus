// -*- C++ -*-

/*  inc/iter/iterables/IterableAdapter.hpp  */


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



#ifndef __ITERABLEADAPTER_HPP__
#define __ITERABLEADAPTER_HPP__

/* $Id: IterableAdapter.hpp,v 1.1.1.1 2000/07/19 17:02:20 philogelos Exp $ */

#include "Iterable.hpp"

BEGIN_QR_NAMESPACE



/**
   Default implementation of Iterable interface.

   @see Iterable
   @author Philogelos
   @created ø‚› 19 ∏Ó› 1998 13:45:06
*/
abstract class IterableAdapter : public Iterable, virtual public Object
{
 public: virtual void initIterations();

 public: virtual void fireOn( Top *anElement );

 public: virtual boolean isMore();

 public: virtual void doneIterations();
};

END_QR_NAMESPACE

/*
 * $Log: IterableAdapter.hpp,v $
 * Revision 1.1.1.1  2000/07/19 17:02:20  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.3  2000/05/25 18:51:53  god
 * typo in comment corrected
 *
 * Revision 1.2  2000/04/09 11:29:35  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:40  god
 * Imported sources
 *
 * Revision 1.2  1999/03/03 19:09:21  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.1.1.1  1998/11/25 20:11:07  philogelos
 * Quercus Robusta
 *
 * Revision 1.2  1998/07/07 14:29:56  philogelos
 * Memory leak in SUNWspro dynamic_cast fixed.
 *
 * Revision 1.1.1.1  1998/06/22 08:47:12  philogelos
 * First version under CVS
 *
 * Revision 1.1.1.1  1998/04/01 17:15:30  philogelos
 * first version under CVS
 * */

/* __ITERABLEADAPTER_HPP__ */
#endif
