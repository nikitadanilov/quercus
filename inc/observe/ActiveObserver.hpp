// -*-C++-*- 

/*  inc/observe/ActiveObserver.hpp  */


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


#ifndef __ACTIVEOBSERVER_HPP__
#define __ACTIVEOBSERVER_HPP__

/* $Id: ActiveObserver.hpp,v 1.1.1.1 2000/07/19 17:02:48 philogelos Exp $ */

#include "ObserverAdapter.hpp"
#include "defines.h"



BEGIN_QR_NAMESPACE

/**
   Flavor of Observer actively
   choosing when to wait for events.

   @author Philogelos
   @created ø‚› 10 ∏Ó€ 1998 14:32:35
*/
abstract class ActiveObserver : public ObserverAdapter
{
  /**
	 Subscribe this observer to given observable 
	 in active mode.
  */
public: virtual void subscribeTo( Observable *aPublisher );
};

END_QR_NAMESPACE

/*
 * $Log: ActiveObserver.hpp,v $
 * Revision 1.1.1.1  2000/07/19 17:02:48  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:36  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:47  god
 * Imported sources
 *
 * Revision 1.3  1999/03/03 19:09:22  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.2  1999/02/28 15:39:06  philogelos
 * Publish/Subscribe re-worked
 *
 * Revision 1.1.1.1  1998/11/25 20:11:05  philogelos
 * Quercus Robusta
 * */

/* __ACTIVEOBSERVER_HPP__ */
#endif
