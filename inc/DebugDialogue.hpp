// -*-C++-*- 

/*  inc/DebugDialogue.hpp  */

/*
 * Author: Philogelos A. <Philogelos@yahoo.com>
 * Maintainer: Philogelos A.
 * Keywords: C++, library, containers
 *
 * Copyright (C) 1999, 2000 Philogelos A.
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



#ifndef __DEBUGDIALOGUE_HPP__
#define __DEBUGDIALOGUE_HPP__

/* $Id: DebugDialogue.hpp,v 1.1.1.1 2000/07/19 16:55:41 philogelos Exp $ */

#include "Object.hpp"
#include "defines.h"
#include "platform/threads/Runnable.hpp"

BEGIN_QR_NAMESPACE

/**
   Handler of dialogue with user during abnormal conditions.

   @author Philogelos
   @created 2000-04-05
*/
class DebugDialogue : public Object,
  public Runnable
{

public: typedef enum { 
  cont = 1, exit, core, toss, threads, objects, chunks, back, debug, 
  trace, config, modules, shell } Action;
  /**
   */
public: DebugDialogue();

  /**
   */
public: virtual ~DebugDialogue();

public: virtual void *run();

public: virtual String getClassName() const;
};

END_QR_NAMESPACE

/*
 * $Log: DebugDialogue.hpp,v $
 * Revision 1.1.1.1  2000/07/19 16:55:41  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.4  2000/04/09 12:00:47  god
 * CVS Log keyword correction finished
 *
 * Revision 1.3  2000/04/09 11:29:16  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.2  2000/04/07 17:05:40  god
 * Backpointers added
 *
 * Revision 1.1  2000/04/05 17:19:21  god
 * Dynamic modules, askUser (+readline) dlsym/dladdr-based Backtrace
 * */

/* __DEBUGDIALOGUE_HPP__ */
#endif
