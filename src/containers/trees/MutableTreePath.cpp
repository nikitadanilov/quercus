// -*-C++-*- 

/*  src/containers/trees/MutableTreePath.cpp  */

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



/* $Id: MutableTreePath.cpp,v 1.1.1.1 2000/07/19 16:48:51 philogelos Exp $ */
#if !defined(_INLINE)
static char cvsid[] = "@(#)$Id: MutableTreePath.cpp,v 1.1.1.1 2000/07/19 16:48:51 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif

#include "containers/trees/MutableTreePath.hpp"
#include "containers/lists/List.hpp"
#include "containers/EmptyContainer.hpp"
#include "PGuard.hpp"
#include "Debug.hpp"

BEGIN_QR_NAMESPACE

MutableTreePath::MutableTreePath( MutableTree *aTree, MutableTreeNode *aNode ) :
  TreePath( aTree, aNode ),
  MutablePositionAdapter( aTree ),
  PositionAdapter( aTree )
{}

MutableTreePath::~MutableTreePath()
{}

Top *MutableTreePath::setValue( Top *aNewValue )
{
  preC_( isValid() );
  
  return topMutable() -> setValue( aNewValue );
}

void MutableTreePath::pushMutable( MutableTreeNode *aNode )
{
  push( aNode );
}

MutableTreeNode *MutableTreePath::popMutable() THROWS( EmptyContainer * )
{
  return TCAST( pop(), MutableTreeNode );
}

MutableTreeNode *MutableTreePath::topMutable() const
{
  return TCAST( top(), MutableTreeNode );
}


Top *MutableTreePath::clone() const
{
  MutableTreePath *result;
  
  result = new MutableTreePath( TCAST( getContainer(), MutableTree ), TCAST( nodes -> car(), MutableTreeNode ) );
  PGuard _result( result, this );
  
  for( Index i = 1 ; i < nodes -> getCardinality() ; ++i )
	{
	  result -> push( TCAST( nodes -> getAt( i ), MutableTreeNode ) );
	}
  test_( ( result -> top() == top() ) && equals( result ) );
  return result;
}


String  MutableTreePath::getClassName() const
{
  return "MutableTreePath";
}

END_QR_NAMESPACE

#if defined(_INLINE)
#include "../src/Debug.ipp"
#endif


/*
 * $Log: MutableTreePath.cpp,v $
 * Revision 1.1.1.1  2000/07/19 16:48:51  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:42  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:32  god
 * Imported sources
*/
