// -*-C++-*- 

/*  inc/LifeTimeControllerAdapter.hpp  */


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


#ifndef __LIFETIMECONTROLLERADAPTER_HPP__
#define __LIFETIMECONTROLLERADAPTER_HPP__

/* $Id: LifeTimeControllerAdapter.hpp,v 1.1.1.1 2000/07/19 16:56:54 philogelos Exp $ */

#include "LifeTimeController.hpp"
#include "Object.hpp"
#include "defines.h"

BEGIN_QR_NAMESPACE



/**

   @author Philogelos
   @created Срд 23 Сен 1998 16:45:00
*/
class LifeTimeControllerAdapter : public LifeTimeController, public virtual Object
{

  /**
	*/
public: LifeTimeControllerAdapter();
  
  /**
	*/
public: virtual ~LifeTimeControllerAdapter();

public: virtual void notifyOfCreate( const Top *aControlled );
public: virtual void notifyOfDestroy( const Top *aControlled );
public: virtual void notifyOfAddRef( const Top *aControlled );
public: virtual void notifyOfDelRef( const Top *aControlled );

  /**
	*/
public:  virtual String  getClassName() const;
};

END_QR_NAMESPACE

/*
 * $Log: LifeTimeControllerAdapter.hpp,v $
 * Revision 1.1.1.1  2000/07/19 16:56:54  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:16  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:38  god
 * Imported sources
 *
 * Revision 1.2  1999/03/03 19:09:03  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.1.1.1  1998/11/25 20:11:05  philogelos
 * Quercus Robusta
 * */

/* __LIFETIMECONTROLLERADAPTER_HPP__ */
#endif
