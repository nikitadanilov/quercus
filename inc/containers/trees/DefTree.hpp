// -*-C++-*- 

/*  inc/containers/trees/DefTree.hpp  */

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



#ifndef __DEFTREE_HPP__
#define __DEFTREE_HPP__

/* $Id: DefTree.hpp,v 1.1.1.1 2000/07/19 17:00:40 philogelos Exp $ */

#include "containers/PositionFactory.hpp"
#include "Object.hpp"
#include "MutableTree.hpp"
#include "MutableTreeNode.hpp"
#include "defines.h"

class DefTreeNode;



BEGIN_QR_NAMESPACE

/**
   Default implementation of the Tree interface.

   @author Philogelos
   @created
*/
class DefTree : public virtual MutableTree,
				public virtual ModifiableContainer,
				public virtual MutableContainerAdapter,
				public virtual Object
{

  /**
   */
public: DefTree();
public: DefTree( MutableTreeNode *aRootNode );

  /**
   */
public: virtual ~DefTree();

public: virtual TypedEnumeration< Tree > *getSubtrees() const;
  
public: virtual MutableTreeNode *getMutableRoot() const THROWS( EmptyContainer * );
public: virtual MutablePositionEnumeration *getMutableEnumeration() const;

  /**
	 Returns sequence containing all removable slots.
	 Empty sequence.
  */
public: virtual TypedEnumeration< RemovablePosition > *getRemovable() const;

public: virtual MutablePositionEnumeration *getLeaves() const;
public: virtual MutablePositionEnumeration *getValuesFirst() const;
public: virtual MutablePositionEnumeration *getValuesLast() const;
  
public: virtual PositionFactory *getPositionFactoryAt( MutableTreeNode *aRoot, 
													   boolean goDepth ) const;

public: virtual PositionFactory *getDefaultPositionFactory() const;

  /**
   */
public:  virtual String  getClassName() const;

protected: MutableTreeNode *root;
  
#if defined( TESTING )
public: boolean tester( int ) const;
#endif
};

class MutableTreePath;

class TreePositionFactory : public virtual PositionFactory,
							public virtual Object
{
public: TreePositionFactory( MutableTreePath *aRoot, 
							 MutableTreeNodeFactory *aFactory, 
							 boolean goDepth );
public: virtual ~TreePositionFactory();

public: virtual MutablePosition *createPosition();

protected: MutableTreePath *root;
protected: MutableTreeNodeFactory *factory;
protected: boolean toDepth;
};

class ModifiableContainer;

class DefTreeNode : public virtual MutableTreeNode,
					public virtual Object
{
public: DefTreeNode();
public: DefTreeNode( ModifiableContainer *aStorage );
public: virtual ~DefTreeNode();
  
public: virtual Top *getValue() const;
public: virtual Top *setValue( Top *aValue );
public: virtual TypedEnumeration< MutableTreeNode > *getMutableChildren() const;
public: virtual ModifiableContainer *getMutableChildrenHome() const;
public: virtual boolean isLeaf();

public: virtual Top *clone() const;

protected: Top *value;
protected: ModifiableContainer *children;
};

class DefTreeNodeFactory : public virtual MutableTreeNodeFactory,
						   public virtual Object
{
public: DefTreeNodeFactory( MutableTreeNode *aNode );
public: virtual ~DefTreeNodeFactory();
  
public: virtual MutableTreeNode *createNode();

protected:  MutableTreeNode *node;
};


END_QR_NAMESPACE

/*
 * $Log: DefTree.hpp,v $
 * Revision 1.1.1.1  2000/07/19 17:00:40  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:34  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:46  god
 * Imported sources
*/

/* __DEFTREE_HPP__ */
#endif
