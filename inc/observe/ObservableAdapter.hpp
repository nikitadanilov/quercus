// -*-C++-*- 

/*  inc/observe/ObservableAdapter.hpp  */

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



#ifndef __OBSERVABLEADAPTER_HPP__
#define __OBSERVABLEADAPTER_HPP__

/* $Id: ObservableAdapter.hpp,v 1.1.1.1 2000/07/19 17:03:13 philogelos Exp $ */

#include "ObservationContext.hpp"
#include "Observable.hpp"
#include "Object.hpp"
#include "defines.h"

BEGIN_QR_NAMESPACE

class List;
interface Condition;

/**

   @author Philogelos
   @created
*/
class ObservableAdapter : public virtual Observable,
						  public virtual Object
{

  /**
   */
public: ObservableAdapter();

  /**
   */
public: virtual ~ObservableAdapter();

public: virtual void addPassive( PassiveObserver *anObserver );
public: virtual void addActive( ActiveObserver *anObserver );
public: virtual void removePassive( PassiveObserver *anObserver );
public: virtual void removeActive( ActiveObserver *anObserver );

public: virtual void addClassPassive( PassiveObserver *anObserver );
public: virtual void addClassActive( ActiveObserver *anObserver );
public: virtual void removeClassPassive( PassiveObserver *anObserver );
public: virtual void removeClassActive( ActiveObserver *anObserver );

public: virtual boolean fire( Condition *aCondition,
							  ObservationContext *aContext );

  /** Should be in List? */
protected: Index strip( List *aList, Top *anObject );

  /**
   */
public: virtual boolean equals( const Top *anOther ) const;

  /**
   */
public: virtual Top *clone() const;

  /**
   */
public: virtual String  toString() const;

  /**
   */
public: virtual String  getString() const;

  /**
   */
public: virtual String  getClassName() const;

#if defined( TESTING )
boolean tester( int aParam ) const NOTHROWS;
#endif

protected: virtual List *getPassives();
protected: virtual List *getActives();

protected: virtual List *getClassPassives();
protected: virtual List *getClassActives();

protected: virtual boolean fireOnList( List *aList, 
									   Condition *aCondition,
									   ObservationContext *aContext,
									   boolean aPost = false );

protected: List *passiveObservers;
protected: List *activeObservers;

protected: static List *classPassiveObservers;
protected: static List *classActiveObservers;

#if defined( USE_PER_CLASS_NEW )
public: void *operator new( size_t size );
#endif
};

END_QR_NAMESPACE

/*
 * $Log: ObservableAdapter.hpp,v $
 * Revision 1.1.1.1  2000/07/19 17:03:13  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:36  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:47  god
 * Imported sources
 *
 * Revision 1.3  1999/05/22 13:00:26  philogelos
 * Merging sources back from SPARC
 *
 * Revision 1.2  1999/03/03 19:09:23  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.1  1999/02/28 15:39:06  philogelos
 * Publish/Subscribe re-worked
 * */

/* __OBSERVABLEADAPTER_HPP__ */
#endif
