// -*-C++-*- 

/*  inc/containers/lists/ListNodeFactory.hpp  */


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


#ifndef __LISTNODEFACTORY_HPP__
#define __LISTNODEFACTORY_HPP__

/* $Id: ListNodeFactory.hpp,v 1.1.1.1 2000/07/19 17:00:36 philogelos Exp $ */

#include "AbstractFactory.hpp"
#include "ListNode.hpp"
#include "defines.h"



BEGIN_QR_NAMESPACE

/**
   Interface for factories of list nodes.
   Each list has an object implementing
   this interface. List calls createListNode()
   method whenever it needs to create new node.

   @see List
   @see #createListNode()

   @author Philogelos
   @created Птн 25 Сен 1998 19:24:58
*/
interface ListNodeFactory : public AbstractFactory
{
  /**
	 Implementations should provide
	 this method.
  */
public: virtual ListNode *createListNode() = 0;

/**
   Overriden to call createListNode()

   @see #createListNode()
*/
public: virtual Top *create();
};

END_QR_NAMESPACE

/*
 * $Log: ListNodeFactory.hpp,v $
 * Revision 1.1.1.1  2000/07/19 17:00:36  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:34  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:46  god
 * Imported sources
 *
 * Revision 1.2  1999/03/03 19:09:15  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.1.1.1  1998/11/25 20:11:06  philogelos
 * Quercus Robusta
 * */

/* __LISTNODEFACTORY_HPP__ */
#endif
