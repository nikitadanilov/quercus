// -*-C++-*- 

/*  src/containers/trees/TreeEnumeration.cpp  */

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



/* $Id: TreeEnumeration.cpp,v 1.1.1.1 2000/07/19 16:48:51 philogelos Exp $ */
#if !defined(_INLINE)
static char cvsid[] = "@(#)$Id: TreeEnumeration.cpp,v 1.1.1.1 2000/07/19 16:48:51 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif

#include "containers/Stack.hpp"
#include "containers/trees/MutableTreeNode.hpp"
#include "containers/trees/MutableTreePath.hpp"
#include "containers/trees/MutableTree.hpp"
#include "containers/trees/TreeEnumeration.hpp"
#include "LinkManager.hpp"
#include "Debug.hpp"

BEGIN_QR_NAMESPACE

TreeEnumeration::TreeEnumeration( MutableTree *aTree, MutableTreeNode *aRoot, 
								  TraversalKind anApproach )
{
  approach = anApproach;
  FNNINIT( root, aRoot );
  FNNINIT( tree, aTree );
  FINIT( children, root -> getMutableChildren() );
  valueFired = false;
  current = NIL;
}

TreeEnumeration::~TreeEnumeration()
{
  FCDONE( current );
  FDONE( children );
  FDONE( tree );
  FDONE( root );
}

MutablePosition *TreeEnumeration::getNextMutablePosition()
{
  preC_( hasMoreElements() );

  MutablePosition *result;
  
  result = getNextInternal();
  test_( result != NIL );
  cache = NIL;
  return result;
}


MutablePosition *TreeEnumeration::getNextInternal()
{
  if( cache != NIL )
	{
	  return cache;
	}
  
  if( ( approach == valueFirst ) || 
	  ( ( approach == leavesOnly ) && root -> isLeaf() ) )
	{
	  if( ! valueFired )
		{
		  valueFired = true;
		  return new MutableTreePath( tree, root );
		}
	}
  if( current == NIL )
	{
	  MutableTreeNode *child;
	    
	  if( children -> hasMoreElements() )
		{
		  child = children -> getNextTypedElement();
		  FINIT( current, new TreeEnumeration( tree, child, approach ) );
		}
	}
  if( current != NIL )
	{
	  while( !( current -> hasMoreElements() ) && 
			 ( children -> hasMoreElements() ) )
		{
		  MutableTreeNode *child;
		  
		  child = children -> getNextTypedElement();
		  FMOVE( current, new TreeEnumeration( tree, child, approach ) );
		}
	  if( current -> hasMoreElements() )
		{
		  return current -> getNextMutablePosition();
		}
	}
  if( approach == valueLast )
	{
	  if( valueFired )
		{
		  return NIL;
		}
	  test_( ! children -> hasMoreElements() );
	  valueFired = true;
	  return new MutableTreePath( tree, root );
	}
  return NIL;
}

boolean TreeEnumeration::hasMoreElements()
{
  cache = getNextInternal();
  return( cache != NIL );
}


String  TreeEnumeration::getClassName() const
{
  return "TreeEnumeration";
}

END_QR_NAMESPACE

#if defined(_INLINE)
#include "../src/Debug.ipp"
#endif


/*
 * $Log: TreeEnumeration.cpp,v $
 * Revision 1.1.1.1  2000/07/19 16:48:51  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:42  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:32  god
 * Imported sources
*/
