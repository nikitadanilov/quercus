// -*-C++-*- 

/*  inc/observe/Observable.hpp  */


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


#ifndef __OBSERVABLE_HPP__
#define __OBSERVABLE_HPP__

/* $Id: Observable.hpp,v 1.1.1.1 2000/07/19 17:03:13 philogelos Exp $ */

#include "Top.hpp"
#include "defines.h"

BEGIN_QR_NAMESPACE

class List;
interface Observer;
interface PassiveObserver;
interface ActiveObserver;

/**
   Publisher part of 
   Publish-subscribe pattern.

   @author Philogelos
   @created ø‚› 10 ∏Ó€ 1998 13:58:26
*/
class Observable : virtual public Top
{
public: virtual void addPassive( PassiveObserver *anObserver ) = 0;
public: virtual void addActive( ActiveObserver *anObserver ) = 0;
public: virtual void removePassive( PassiveObserver *anObserver ) = 0;
public: virtual void removeActive( ActiveObserver *anObserver ) = 0;

public: virtual void addClassPassive( PassiveObserver *anObserver ) = 0;
public: virtual void addClassActive( ActiveObserver *anObserver ) = 0;
public: virtual void removeClassPassive( PassiveObserver *anObserver ) = 0;
public: virtual void removeClassActive( ActiveObserver *anObserver ) = 0;

protected: virtual List *getPassives() = 0;
protected: virtual List *getActives() = 0;

protected: virtual List *getClassPassives() = 0;
protected: virtual List *getClassActives() = 0;
};

END_QR_NAMESPACE

/*
 * $Log: Observable.hpp,v $
 * Revision 1.1.1.1  2000/07/19 17:03:13  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:36  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:47  god
 * Imported sources
 *
 * Revision 1.3  1999/03/03 19:09:23  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.2  1999/02/28 15:39:06  philogelos
 * Publish/Subscribe re-worked
 *
 * Revision 1.1.1.1  1998/11/25 20:11:05  philogelos
 * Quercus Robusta
 *
 * Revision 1.1  1998/07/10 10:39:30  philogelos
 * Publish-subscribe sub-system initialised
 * */

/* __OBSERVABLE_HPP__ */
#endif
