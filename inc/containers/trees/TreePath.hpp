// -*-C++-*- 

/*  inc/containers/trees/TreePath.hpp  */

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



#ifndef __TREEPATH_HPP__
#define __TREEPATH_HPP__

/* $Id: TreePath.hpp,v 1.1.1.1 2000/07/19 17:01:31 philogelos Exp $ */

#include "containers/PositionAdapter.hpp"
#include "TreeNode.hpp"
#include "Tree.hpp"
#include "defines.h"

BEGIN_QR_NAMESPACE

class List;

/**

   @author Philogelos
   @created
*/
class TreePath : public virtual PositionAdapter
{
public: TreePath( Tree *aTree, TreeNode *aNode );

  /**
   */
public: virtual ~TreePath();

public: virtual void push( TreeNode *aNode );
public: virtual TreeNode *pop() THROWS( EmptyContainer * );
public: virtual TreeNode *top() const;
public: virtual void prepend( TreeNode *aNode );
  
public:  virtual boolean isValid() const;
public:  virtual Top *getValue() const;

  /**
   */
public:  virtual boolean equals( const Top *anOther ) const;

  /**
   */
public:  virtual Top *clone() const;

public:  virtual String getString() const;
    /**
   */
public:  virtual String  getClassName() const;

protected: List *nodes;
};

END_QR_NAMESPACE

/*
 * $Log: TreePath.hpp,v $
 * Revision 1.1.1.1  2000/07/19 17:01:31  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:34  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:46  god
 * Imported sources
*/

/* __TREEPATH_HPP__ */
#endif
