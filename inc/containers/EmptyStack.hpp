// -*-C++-*- 

/*  inc/containers/EmptyStack.hpp  */

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



#ifndef __EMPTYSTACK_HPP__
#define __EMPTYSTACK_HPP__

/* $Id: EmptyStack.hpp,v 1.1.1.1 2000/07/19 16:59:21 philogelos Exp $ */

#include "EmptyContainer.hpp"
#include "defines.h"



BEGIN_QR_NAMESPACE

/**
   Raised when operation (pop)
   applied to empty stack.

   @author Philogelos
   @created
*/
class EmptyStack : public EmptyContainer
{

/**
*/
public: EmptyStack( String aMessage, const Top *const aSource );

public:  virtual String getDescription() const;

/**
*/
public:  virtual String  getClassName() const;
};

END_QR_NAMESPACE

/*
 * $Log: EmptyStack.hpp,v $
 * Revision 1.1.1.1  2000/07/19 16:59:21  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:33  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:44  god
 * Imported sources
 *
 * Revision 1.2  1999/03/03 19:09:09  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.1  1999/02/28 13:04:32  philogelos
 * Added Files:
 * 	EmptyContainer.hpp EmptyStack.hpp LayeredContainer.hpp
 * 	MutableLayeredContainer.hpp PuncturedContainer.hpp Stack.hpp
 * 	TextContainer.hpp ValuePosition.hpp
 * Removed Files:
 * 	Modifier.hpp
 * */

/* __EMPTYSTACK_HPP__ */
#endif
