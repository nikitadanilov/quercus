// -*-C++-*- 

/*  src/containers/trees/DefTree.cpp  */

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



/* $Id: DefTree.cpp,v 1.2 2000/08/30 12:20:36 philogelos Exp $ */
#if !defined(_INLINE)
static char cvsid[] = "@(#)$Id: DefTree.cpp,v 1.2 2000/08/30 12:20:36 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif

#include "algorithms/enumerations/EnumerationAlgorithms.hpp"
#include "iter/enumerations/EmptyEnumeration.hpp"
#include "iter/enumerations/TypedEnumeration.hpp"
#include "containers/lists/List.hpp"
#include "containers/EmptyContainer.hpp"
#include "containers/trees/MutableTree.hpp"
#include "containers/trees/DefTree.hpp"
#include "containers/trees/TreeEnumeration.hpp"
#include "containers/trees/MutableTreePath.hpp"
#include "LinkManager.hpp"
#include "OGuard.hpp"
#include "PGuard.hpp"
#include "Debug.hpp"

BEGIN_QR_NAMESPACE

DefTree::DefTree()
{
  root = new DefTreeNode();
}

DefTree::DefTree( MutableTreeNode *aRootNode )
{
  root = aRootNode;
}

DefTree::~DefTree()
{}

MutableTreeNode *DefTree::getMutableRoot() const THROWS( EmptyContainer * )
{
  return *root;
}

MutablePositionEnumeration *DefTree::getMutableEnumeration() const
{
  return getValuesLast();
}

MutablePositionEnumeration *DefTree::getLeaves() const
{
  return new TreeEnumeration
	( ( MutableTree * ) this, getMutableRoot(), 
	  TreeEnumeration::leavesOnly );
}

MutablePositionEnumeration *DefTree::getValuesFirst() const
{
  return new TreeEnumeration
	( ( MutableTree * ) this, getMutableRoot(), 
	  TreeEnumeration::valueFirst );
}

MutablePositionEnumeration *DefTree::getValuesLast() const
{
  return new TreeEnumeration
	( ( MutableTree * ) this, getMutableRoot(), 
	  TreeEnumeration::valueLast );
}

TypedEnumeration< Tree > *DefTree::getSubtrees() const
{
  CRef< List > subtrees;
  CRef< TypedEnumeration< MutableTreeNode > > children;
  
  subtrees = new List();
  
  children = getMutableRoot() -> getMutableChildren();
  while( children -> hasMoreElements() )
	{
	  CRef< MutableTreeNode > child;
	  
	  child = children -> getNextTypedElement();

	  subtrees -> append( new DefTree( ( MutableTreeNode * ) *child ) );
	}
  return TypedEnumeration< Tree >::upcast( subtrees -> getValueEnumeration() );
}

TypedEnumeration< RemovablePosition > *DefTree::getRemovable() const
{
  return TypedEnumeration< RemovablePosition >::upcast
	( new EmptyEnumeration() );
}

String  DefTree::getClassName() const
{
  return "DefTree";
}

PositionFactory *DefTree::getDefaultPositionFactory() const
{
  return getPositionFactoryAt( getMutableRoot(), false );
}

PositionFactory *DefTree::getPositionFactoryAt( MutableTreeNode *aRoot, 
												boolean goDepth ) const
{
  preC_( aRoot != NIL );
  
  return new TreePositionFactory
	( new MutableTreePath( ( DefTree * ) this, aRoot ), 
	  new DefTreeNodeFactory( new DefTreeNode() ), goDepth );
}






TreePositionFactory::TreePositionFactory( MutableTreePath *aRoot, 
										  MutableTreeNodeFactory *aFactory,
										  boolean goDepth )
{
  root = aRoot;
  factory = aFactory;
  toDepth = goDepth;
}

TreePositionFactory::~TreePositionFactory()
{}

MutablePosition *TreePositionFactory::createPosition()
{
  CRef< MutableTreeNode > freshNode;
  CRef< MutableTreePath > result( NULL, true, false, false );
    
  freshNode = factory -> createNode();
  
  root -> topMutable() -> getMutableChildrenHome() -> defAdd( *freshNode );

  if( toDepth )
	{
	  root -> pushMutable( *freshNode );
	  result = TCAST( root -> clone(), MutableTreePath );
	}
  else
	{
	  result = TCAST( root -> clone(), MutableTreePath );
	  result -> pushMutable( *freshNode );
	}
  return *result;
}






DefTreeNode::DefTreeNode()
{
  setValue( nil );
  children = new List();
}

DefTreeNode::DefTreeNode( ModifiableContainer *aStorage )
{
  setValue( nil );
  children = aStorage;
}


DefTreeNode::~DefTreeNode()
{}

Top *DefTreeNode::getValue() const
{
  return *value;
}

Top *DefTreeNode::setValue( Top *aValue )
{
  Top *prevValue;
  
  prevValue = *value;
  value = aValue;
  return prevValue;
}

TypedEnumeration< MutableTreeNode > *DefTreeNode::getMutableChildren() const
{
  return TypedEnumeration< MutableTreeNode >::upcast
	( getMutableChildrenHome() -> getValueEnumeration() );
}

ModifiableContainer *DefTreeNode::getMutableChildrenHome() const
{
  return *children;
}

boolean DefTreeNode::isLeaf()
{
  return getMutableChildrenHome() -> isEmpty();
}

Top *DefTreeNode::clone() const
{
  CRef< DefTreeNode > result( NULL, true, false, false );
  
  result = new DefTreeNode
	( TCAST( getMutableChildrenHome() -> clone(), 
			 ModifiableContainer ) );
  result -> setValue( getValue() );
  return *result;
}



DefTreeNodeFactory::DefTreeNodeFactory( MutableTreeNode *aNode )
{
  node = aNode;
}

DefTreeNodeFactory::~DefTreeNodeFactory()
{}
  
MutableTreeNode *DefTreeNodeFactory::createNode()
{
  return TCAST( ( *node ) -> clone(), MutableTreeNode );
}

#if defined( TESTING )

#include "OGuard.hpp"

boolean DefTree::tester( int ) const
{
  {
	DefTree *target;
	
	target = new DefTree();
	OGuard _target( target, this );
	DLOGOBJECT( "fresh tree: %s", target );
  }
  {
	DefTree *target;
	DefTreeNode *node;
		
	target = new DefTree();
	OGuard _target( target, this );

	node = new DefTreeNode();
	OGuard _node( node, this );
	
	DLOGOBJECT( "fresh tree: %s", target );
	target -> getMutableRoot() -> setValue( new String( "foo" ) );
	DLOGOBJECT( "root value set: %s", target );
	target -> getMutableRoot() -> getMutableChildrenHome() -> defAdd( node );
	node -> setValue( new String( "bar!" ) );
	DLOGOBJECT( "child added: %s", target );
  }
  {
	DefTree *target;

	target = new DefTree();
	OGuard _target( target, this );

	target -> getMutableRoot() -> setValue( new String( "foo" ) );
	
	for( Index i = 0 ; i < 20 ; ++i )
	  {
		DefTreeNode *node;
				
		node = new DefTreeNode();
		OGuard _node( node, this );
	
		target -> getMutableRoot() -> getMutableChildrenHome() -> defAdd( node );
		node -> setValue( String( "bar #%li" ).sprintf( 1, i ).clone() );
		for( Index j = 0 ; j < i + 2 ; ++j )
		  {
			DefTreeNode *inode;
				
			inode = new DefTreeNode();
			OGuard _inode( inode, this );
			node -> getMutableChildrenHome() -> defAdd( inode );
			inode -> setValue( String( "baz #%li:%li" ).sprintf( 1, i, j ).clone() );
		  }
	  }
	DLOGOBJECT( "happy family: %s", target, &Top::getString );

	TypedEnumeration< Tree > *subfamilies;
	
	subfamilies = target -> getSubtrees();
	OGuard _sub( subfamilies, this );
	while( subfamilies -> hasMoreElements() )
	  {
		DLOGOBJECT( "family: %s", subfamilies -> getNextTypedElement(), 
										 &Top::getString );
	  }
	
  }
  {
	DefTree *target;
	List *term;
			
	target = new DefTree();
	OGuard _target( target, this );

	term = new List();
	OGuard _term( term, this );

	for( Index i = 0 ; i < 10 ; ++i )
	  {
		term -> append( new String( i, 10 ) );
	  }
	DLOG( "Modifiable tree" );
	target -> getMutableRoot() -> setValue( new String( "foo" ) );
	DLOGOBJECT( "source tree: %s", target );
	EAlg::get() -> add( target, term -> getValueEnumeration() );
	DLOGOBJECT( "result tree: %s", target );
	EAlg::get() -> addAt( target -> getPositionFactoryAt
						  ( target -> getMutableRoot(), true ), 
						  term -> getValueEnumeration() );
	DLOGOBJECT( "another result tree: %s", target );
	EAlg::get() -> addAt( target -> getPositionFactoryAt
						  ( target -> getMutableRoot(), true ), 
						  term -> getEnumeration() );
	DLOGOBJECT( "yet another result tree: %s", target );
  }
  return true;
}

#endif

END_QR_NAMESPACE

#if defined(_INLINE)
#include "../src/Debug.ipp"
#endif


/*
 * $Log: DefTree.cpp,v $
 * Revision 1.2  2000/08/30 12:20:36  philogelos
 * THROWS clauses updates to correspond to the real throws.
 *
 * Revision 1.1.1.1  2000/07/19 16:48:51  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:42  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:32  god
 * Imported sources
*/
