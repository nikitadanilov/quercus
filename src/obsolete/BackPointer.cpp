// -*-C++-*- 

/*  src/structures/BackPointer.cpp  */


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


/* $Id: BackPointer.cpp,v 1.1.1.1 2000/07/19 16:50:38 philogelos Exp $ */
static char cvsid[] = "@(#)$Id: BackPointer.cpp,v 1.1.1.1 2000/07/19 16:50:38 philogelos Exp $";

#include "structures/BackPointer.hpp"
#include "String.hpp"
#include "Debug.hpp"

BackPointer::BackPointer( Index aPointersNumber ) :
  pointersNumber( aPointersNumber )
{
  state = init;
}

BackPointer::~BackPointer()
{
  state = beingDestroyed;
  addRef();
}

void BackPointer::pointerSetUp( boolean aFlag )
{
  if( aFlag )
	{
	  state = setUp;
	}
  else
	{
	  state = init;
	}
}

boolean BackPointer::isRef() const
{
  switch( state )
	{
	case init:
	  return ( Cyclic::isRef() );
	case setUp:
	  return ( Cyclic::getRefCount() > pointersNumber );
	case beingDestroyed:
	  if( Cyclic::getRefCount() <= 1 )
		{
		  MUTATE_MEMBER( state, BackPointer ) = done;
		  delRef();
		}
	  return ( Cyclic::getRefCount() );
	case done:
	  return ( 0 );
	default:
	  impossible( "Impossible BackPointer::state" );
	}
  return true;
}

String  BackPointer::getClassName() const
{
  return "BackPointer";
}

#if defined(_INLINE)
#include "../src/Debug.ipp"
#endif


#if defined(_INLINE)
#include "../src/String.ipp"
#endif


/* $Log: BackPointer.cpp,v $
/* Revision 1.1.1.1  2000/07/19 16:50:38  philogelos
/* stored sources into sourceforge.net CVS
/*
/* Revision 1.1.1.1  2000/04/01 14:07:29  god
/* Imported sources
/*
 * Revision 1.3  1999/03/03 19:09:47  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.2  1999/02/28 16:30:51  philogelos
 * Tuned for inlines.
 *
 * Revision 1.1.1.1  1998/11/25 20:11:04  philogelos
 * Quercus Robusta
 * */
