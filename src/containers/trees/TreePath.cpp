// -*-C++-*- 

/*  src/containers/trees/TreePath.cpp  */

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



/* $Id: TreePath.cpp,v 1.2 2001/04/16 10:45:39 philogelos Exp $ */
#if !defined(_INLINE)
static char cvsid[] = "@(#)$Id: TreePath.cpp,v 1.2 2001/04/16 10:45:39 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif

#include "algorithms/enumerations/EnumerationAlgorithms.hpp"
#include "containers/EmptyContainer.hpp"
#include "containers/lists/List.hpp"
#include "containers/trees/TreePath.hpp"
#include "Equivalence.hpp"
#include "PGuard.hpp"
#include "Debug.hpp"

BEGIN_QR_NAMESPACE

TreePath::TreePath( Tree *aTree, TreeNode *aNode ) :
  PositionAdapter( aTree )
{
  preC_( aNode != NIL );

  FINIT( nodes, new List() );
  nodes -> append( aNode );
}

TreePath::~TreePath()
{
  FDONE( nodes );
}

void TreePath::push( TreeNode *aNode )
{
  preC_( aNode != ( TreeNode * ) NIL );
  
  if( ! EAlg::get() -> 
	  contains( top() -> getChildren(), aNode, DeltaRelation::getDelta() ) )
	{
	  throw new InternalError( "TreePath::push(): cannot append to path", null );
	}
  nodes -> append( aNode );
  postC_( isValid() );
}

TreeNode *TreePath::pop() THROWS( EmptyContainer * )
{
  if( nodes -> getCardinality() <= 1 )
	{
	  throw new EmptyContainer( "Cannot remove last item from path", null );
	}
  
  return TCAST( nodes -> betail(), TreeNode );
}

TreeNode *TreePath::top() const
{
  nodes -> toLast();
  return TCAST( nodes -> getCurrentValue(), TreeNode );
}

void TreePath::prepend( TreeNode *aNode )
{
  preC_( aNode != ( TreeNode * ) NIL );
  
  if( ! EAlg::get() -> 
	  contains( aNode -> getChildren(), top(), DeltaRelation::getDelta() ) )
	{
	  throw new InternalError( "TreePath::prepend(): cannot prepend to path", null );
	}
  nodes -> prepend( aNode );
  postC_( isValid() );
}


boolean TreePath::isValid() const
{
  TreeNode *scan;
  
  nodes -> toFirst();
  scan = TCAST( nodes -> getCurrentValue(), TreeNode );
  for( nodes -> next() ; ! nodes -> atEnd() ; nodes -> next() )
	{
	  TreeNode *nextNode;

	  nextNode = TCAST( nodes -> getCurrentValue(), TreeNode );
	  if( ! EAlg::get() -> contains( scan -> getChildren(), nextNode, 
									 DeltaRelation::getDelta() ) )
		{
		  return false;
		}
	  scan = nextNode;
	}
  return true;
}

Top *TreePath::getValue() const
{
  preC_( isValid() );
  
  return top() -> getValue();
}

boolean TreePath::equals( const Top *anOther ) const
{
  return ( DCAST( anOther, TreePath ) != ( TreePath * ) NIL ) && 
	( nodes ->equals( DCAST( anOther, TreePath ) -> nodes ) );
}

Top *TreePath::clone() const
{
  TreePath *result;
  
  result = new TreePath( TCAST( getContainer(), Tree ), TCAST( nodes -> car(), TreeNode ) );
  PGuard _result( result, this );
  
  for( Index i = 1 ; i < nodes -> getCardinality() ; ++i )
	{
	  result -> push( TCAST( nodes -> getAt( i ), TreeNode ) );
	}
  test_( ( result -> top() == top() ) && equals( result ) );
  return result;
}

String TreePath::getString() const
{
  return PositionAdapter::getString() + " nodes: " + nodes -> getString();
}

String  TreePath::getClassName() const
{
  return "TreePath";
}

END_QR_NAMESPACE

#if defined(_INLINE)
#include "../src/Debug.ipp"
#endif


/*
 * $Log: TreePath.cpp,v $
 * Revision 1.2  2001/04/16 10:45:39  philogelos
 * adapted to new interface of EnumerationAlgorithms::contains()
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
