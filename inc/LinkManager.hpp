// -*-C++-*- 

/*  inc/LinkManager.hpp  */


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


#ifndef __LINKMANAGER_HPP__
#define __LINKMANAGER_HPP__

/* $Id: LinkManager.hpp,v 1.1.1.1 2000/07/19 16:56:54 philogelos Exp $ */

#include "Object.hpp"
#include "defines.h"

#define OREG( object ) LinkManager::reg( this, object )
#define OFREE( object ) LinkManager::free( this, object )

#define FINIT( field, expression ) \
    field = expression ; OREG( field )

#define FCINIT( field, expression ) \
    field = expression ; if( field != NULL ) { OREG( field ) }

#define FNNINIT( field, expression ) \
    preC_( expression != NULL ); FINIT( field, expression )

#define FDONE( field ) OFREE( field )

#define FCDONE( field ) \
    if( field != NULL ) \
       { \
          OFREE( field ); \
       } \
    field = NULL

#define FMOVE( field, expression ) \
    { \
       Top *oldValue; \
       \
       oldValue = field; \
       field = expression; \
       LinkManager::move( this, oldValue, field ); \
    }

BEGIN_QR_NAMESPACE



/**
   Manager links (through pointers) between objects.

   @author Philogelos
   @created
*/
class LinkManager : public Object
{

  /**
	*/
public: LinkManager();

  /**
	*/
public: virtual ~LinkManager();


public: static LinkManager *getInstance();
public: static void initClass();

public: static void reg( const Top *aFrom, const Top *aTo );
public: static void unreg( const Top *aFrom, const Top *aTo );
public: static void free( const Top *aFrom, const Top *aTo );
public: static void move( const Top *anOwner, const Top *aFrom, const Top *aTo );
public: static void recycle( const Top *anObject );

public: virtual void regImpl( const Top *aFrom, const Top *aTo );
public: virtual void unregImpl( const Top *aFrom, const Top *aTo );
public: virtual void freeImpl( const Top *aFrom, const Top *aTo );
public: virtual void moveImpl( const Top *anOwner, const Top *aFrom, const Top *aTo );
public: virtual void recycleImpl( const Top *anObject );

  /**
	 
	*/
public:  virtual Top *clone() const;

  /**
	*/
public:  virtual String  getClassName() const;

protected: static LinkManager *instance;
};

END_QR_NAMESPACE

/*
 * $Log: LinkManager.hpp,v $
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

/* __LINKMANAGER_HPP__ */
#endif
