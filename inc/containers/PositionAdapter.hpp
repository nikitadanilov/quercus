// -*-C++-*- 

/*  inc/containers/PositionAdapter.hpp  */


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


#ifndef __POSITIONADAPTER_HPP__
#define __POSITIONADAPTER_HPP__

/* $Id: PositionAdapter.hpp,v 1.1.1.1 2000/07/19 16:59:43 philogelos Exp $ */

#include "containers/MutablePosition.hpp"
#include "defines.h"

BEGIN_QR_NAMESPACE

interface Container;

/**
   Default implementaion stub for
   position within the container.

   @author Philogelos
   @created ≤‚‡ 23 ∏Ó› 1998 17:52:30
*/
class PositionAdapter : public virtual Position,
						public virtual Object
{

  /**
	 Creates undefined position within given 
	 container.

	 @precond ( aHost != ( Container * ) null )
	 @postcond ( getContainer() == aHost )
  */
public: PositionAdapter( Container *aHost );

  /**
	 Destructor.
	 Deletes host container if needed.
  */
public: virtual ~PositionAdapter();

public:  virtual boolean isValid() const = 0;

  /**
	 Returns value located at this position in
	 the host container.
  */
public:  virtual Top *getValue() const;

  /**
	 Returns host container.
  */
public:  virtual Container *getContainer() const;

public:  virtual String  getString() const;
public:  virtual String  getClassName() const;

protected:  Container *host;
};

END_QR_NAMESPACE

/*
 * $Log: PositionAdapter.hpp,v $
 * Revision 1.1.1.1  2000/07/19 16:59:43  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:33  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:45  god
 * Imported sources
 *
 * Revision 1.3  1999/03/03 19:09:11  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.2  1999/02/28 12:59:48  philogelos
 * Sub-classed from Object
 *
 * Revision 1.1.1.1  1998/11/25 20:11:05  philogelos
 * Quercus Robusta
 *
 * Revision 1.1  1998/07/09 09:30:31  philogelos
 * new files added to the repository
 * */

/* __POSITIONADAPTER_HPP__ */
#endif
