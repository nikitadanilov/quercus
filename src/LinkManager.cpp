// -*-C++-*- 

/*  src/LinkManager.cpp  */


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


/* $Id: LinkManager.cpp,v 1.2 2001/03/06 17:41:53 philogelos Exp $ */
#if !defined(_INLINE)
static char cvsid[] = "@(#)$Id: LinkManager.cpp,v 1.2 2001/03/06 17:41:53 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif


#include "LinkManager.hpp"
#include "MemoryMonitor.hpp"
#include "Debug.hpp"
#include "String.hpp"

BEGIN_QR_NAMESPACE

LinkManager::LinkManager()
{}

LinkManager::~LinkManager()
{}

LinkManager *LinkManager::getInstance()
{
  if( instance == ( LinkManager * ) NIL )
	{
	  initClass();
	}
  test_( instance != ( LinkManager * ) NIL );
  return instance;
}

void LinkManager::initClass()
{
  instance = new LinkManager();
}

void LinkManager::reg( const Top *aFrom, const Top *aTo )
{
  getInstance() -> regImpl( aFrom, aTo );
}

void LinkManager::unreg( const Top *aFrom, const Top *aTo )
{
  getInstance() -> unregImpl( aFrom, aTo );
}

void LinkManager::free( const Top *aFrom, const Top *aTo )
{
  getInstance() -> freeImpl( aFrom, aTo );
}

void LinkManager::move( const Top *anOwner, const Top *aFrom, const Top *aTo )
{
  getInstance() -> moveImpl( anOwner, aFrom, aTo );
}

void LinkManager::recycle( const Top *anObject )
{
  getInstance() -> recycleImpl( anObject );
}

void LinkManager::regImpl( const Top *aFrom, const Top *aTo )
{
  preC_( aFrom != nil );
  preC_( aTo != nil );

#if defined( TRACK_BACKPOINTERS )
  for( Index i = 0 ; i < BACKPOINTERS_LIST_LEN ; ++i )
	{
	  if( aTo -> backpointers[ i ] == nil )
		{
		  ( ( Top * ) aTo ) -> backpointers[ i ] = ( Top * ) aFrom;
		  break;
		}
	}
#endif
  aTo -> addRef();
}

void LinkManager::unregImpl( const Top *aFrom, const Top *aTo )
{
  preC_( aFrom != nil );
  preC_( aTo != nil );

#if defined( TRACK_BACKPOINTERS )
  for( Index i = 0 ; i < BACKPOINTERS_LIST_LEN ; ++i )
	{
	  if( aTo -> backpointers[ i ] == aFrom )
		{
		  ( ( Top * ) aTo ) -> backpointers[ i ] = nil;
		  break;
		}
	}
#endif
  aTo -> delRef();
}

void LinkManager::freeImpl( const Top *aFrom, const Top *aTo )
{
  preC_( aFrom != nil );
  preC_( aTo != nil );

  unreg( aFrom, aTo );
  recycle( aTo );
}

void LinkManager::moveImpl( const Top *anOwner, const Top *aFrom, const Top *aTo )
{
  if( aTo != null )
	{
	  reg( anOwner, aTo );
	}
  if( aFrom != null )
	{
	  free( anOwner, aFrom );
	}
}

void LinkManager::recycleImpl( const Top *anObject )
{
  preC_( anObject != nil );

  if( !( anObject -> isRef() ) )
	{
	  if( ! ( anObject -> isBeingDeleted() ) )
		{
		  anObject -> setBeingDeleted( true );
		  delete ( Top * ) anObject;
		}
	}
}

Top *LinkManager::clone() const
{
  return new LinkManager();
}

String  LinkManager::getClassName() const
{
  return "LinkManager";
}

LinkManager *LinkManager::instance = NIL;

END_QR_NAMESPACE

#if defined(_INLINE)
#include "../src/Debug.ipp"
#endif


#if defined(_INLINE)
#include "../src/String.ipp"
#endif

/*
 * $Log: LinkManager.cpp,v $
 * Revision 1.2  2001/03/06 17:41:53  philogelos
 * casts before NULL removed
 *
 * Revision 1.1.1.1  2000/07/19 16:41:06  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:39  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:28  god
 * Imported sources
 *
 * Revision 1.3  1999/03/03 19:09:27  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.2  1999/02/28 15:48:37  philogelos
 * Tuned for inlines.
 *
 * Revision 1.1.1.1  1998/11/25 20:11:01  philogelos
 * Quercus Robusta
 * */
