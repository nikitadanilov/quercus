// -*-C++-*- 

/*  inc/platform/dl/SolarisDL.hpp  */

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



#ifndef __SOLARISDL_HPP__
#define __SOLARISDL_HPP__

/* $Id: SolarisDL.hpp,v 1.2 2000/10/20 20:29:19 philogelos Exp $ */

#include "DynamicModule.hpp"
#include "defines.h"

BEGIN_QR_NAMESPACE

/**
   Implementation of DynamicModule over Solaris dlopen and
   friends.

   @author Philogelos
   @created 2000-04-04
*/
class SolarisDL : public virtual DynamicModule,
  public virtual Object
{

  /**
   */
public: SolarisDL( String aLibName );

  /**
   */
public: virtual ~SolarisDL();

public: virtual void *getSymbolAddress( String aSymbol ) THROWS( NoEntity * );
public: virtual String convertPortableToPlatform( String aName ) const;
public: virtual void platformLoad() THROWS( Errno * );
public: virtual void platformUnload() THROWS( Errno * );

  /**
   */
public:  virtual String  getClassName() const;

protected: void *handle;

protected: static Mutex *loadMutex;

#if defined( TESTING )
public: boolean tester( int aParam ) const;
#endif

};

END_QR_NAMESPACE

/*
 * $Log: SolarisDL.hpp,v $
 * Revision 1.2  2000/10/20 20:29:19  philogelos
 * Simplifications through using of NopThreads
 *
 * Revision 1.1.1.1  2000/07/19 17:13:53  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.3  2000/04/09 12:00:47  god
 * CVS Log keyword correction finished
 *
 * Revision 1.2  2000/04/09 11:29:36  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1  2000/04/07 18:03:14  god
 * Added
 *
 * Revision 1.1  2000/04/05 10:13:04  god
 * Initial revision
 * */

/* __SOLARISDL_HPP__ */
#endif
