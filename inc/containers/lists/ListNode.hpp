// -*-C++-*- 

/*  inc/containers/lists/ListNode.hpp  */


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


#ifndef __LISTNODE_HPP__
#define __LISTNODE_HPP__

/* $Id: ListNode.hpp,v 1.1.1.1 2000/07/19 17:00:34 philogelos Exp $ */

#include "Top.hpp"
#include "defines.h"



BEGIN_QR_NAMESPACE

/**
   Interface for List nodes. Lists are composed of nodes.
   Each node stores value and links to previous and next
   nodes in the list. Implementations of this interface
   can add additional state to provide for sorting and 
   sharing of nodes among lists.

   @see List

   @author Philogelos
   @created Птн 25 Сен 1998 18:12:09
*/
interface ListNode : public virtual Top
{
  /**
	 Returns value stored in this node.
  */
 public: virtual Top *getValue() const = 0;

 /**
	Stores value in this node.
 */
 public: virtual void setValue( Top *aValue ) = 0;

 /**
	Returns next node.
 */
 public: virtual ListNode *getNext() const = 0;

 /**
	Returns previous node.
 */
 public: virtual ListNode *getPrev() const = 0;

 /**
	Sets next node.
 */
 public: virtual void setNext( ListNode *aNode ) = 0;

 /**
	Sets previous node.
 */
 public: virtual void setPrev( ListNode *aNode ) = 0;
};

END_QR_NAMESPACE

/*
 * $Log: ListNode.hpp,v $
 * Revision 1.1.1.1  2000/07/19 17:00:34  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:34  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:45  god
 * Imported sources
 *
 * Revision 1.2  1999/03/03 19:09:15  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.1.1.1  1998/11/25 20:11:06  philogelos
 * Quercus Robusta
 * */

/* __LISTNODE_HPP__ */
#endif
