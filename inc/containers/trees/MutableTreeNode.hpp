// -*-C++-*- 

/*  inc/containers/trees/MutableTreeNode.hpp  */

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



#ifndef __MUTABLETREENODE_HPP__
#define __MUTABLETREENODE_HPP__

/* $Id: MutableTreeNode.hpp,v 1.1.1.1 2000/07/19 17:00:49 philogelos Exp $ */

#include "TreeNode.hpp"
#include "defines.h"

BEGIN_QR_NAMESPACE

class ModifiableContainer;

/**

   @author Philogelos
   @created
*/
abstract class MutableTreeNode : public TreeNode
{
public: virtual ~MutableTreeNode() {};

public: virtual Top *getValue() const = 0;
public: virtual Top *setValue( Top *aValue ) = 0;
public: virtual TypedEnumeration< TreeNode > *getChildren() const;
public: virtual TypedEnumeration< MutableTreeNode > *getMutableChildren() const = 0;
public: virtual Container *getChildrenHome() const;
public: virtual ModifiableContainer *getMutableChildrenHome() const = 0;
public: virtual boolean isLeaf() = 0;
};

END_QR_NAMESPACE

/*
 * $Log: MutableTreeNode.hpp,v $
 * Revision 1.1.1.1  2000/07/19 17:00:49  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:34  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:46  god
 * Imported sources
*/

/* __MUTABLETREENODE_HPP__ */
#endif
