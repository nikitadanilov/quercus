// -*-C++-*- 

/*  inc/algorithms/enumerations/EnumerationAlgorithms.hpp  */


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


#ifndef __ENUMERATIONALGORITHMS_HPP__
#define __ENUMERATIONALGORITHMS_HPP__

/* $Id: EnumerationAlgorithms.hpp,v 1.2 2000/08/30 12:20:35 philogelos Exp $ */

#include "Object.hpp"
#include "algorithms/AlgorithmPackage.hpp"
#include "containers/Container.hpp"
#include "iter/enumerations/ResettableEnumeration.hpp"
#include "iter/iterables/Iterable.hpp"
#include "platform/threads/Runnable.hpp"
#include "defines.h"
#include "CRef.hpp"

/**
   Shortcut for getting singleton instance of
   class EnumerationAlgorithms.

   @see EnumerationAlgorithms
   @see SALG
*/
#define EALG EAlg::get()

BEGIN_QR_NAMESPACE

interface Enumeration;
interface ResettableEnumeration;
interface ECursor;
interface Container;
interface ModifiableContainer;
interface PositionFactory;
interface Iterator;

class NoEntity;

/**
   Enumeration algorithms.

   @author Philogelos
   @created Чтв 01 Окт 1998 16:45:23
*/
class EnumerationAlgorithms : public virtual AlgorithmPackage,
							  public virtual Object
{

public: virtual Index findIndex( Enumeration *anEnum, 
								 const Top *anObject, 
								 const Index aMaxSearch ) const 
  THROWS( NoEntity * );
public: virtual  Index getCardinality( Enumeration *anEnum );

  /**
	 Returns first element of the given
	 enumeration.

	 @precond( aBase -> hasMoreElements() )
  */
  //public: virtual  Top *getCar( Enumeration *aBase );

  /**
	 Returns enumeration containing all but the 
	 first elements of the given
	 enumeration.

	 @precond( aBase -> hasMoreElements() )
  */
  //public: virtual  Enumeration *getCdr( Enumeration *aBase );
public: virtual  boolean contains( Enumeration *anEnum, 
								   const Top *anElement, 
								   const boolean same = false );
public: virtual  Container *getAsContainer( ResettableEnumeration *anEnum );
public: virtual  boolean add( ModifiableContainer *aContainer, Enumeration *anEnum );
public: virtual  boolean addAt( PositionFactory *aFactory, Enumeration *anEnum );
public: virtual  ResettableEnumeration *getFromContainer( Container *aContainer );

public: virtual  ResettableEnumeration *getSum( ResettableEnumeration *aFirst, 
												ResettableEnumeration *aSecond );
public: virtual  ResettableEnumeration *getUnion( ResettableEnumeration *aFirst, 
												  ResettableEnumeration *aSecond );
public: virtual  ResettableEnumeration *getIntersection( ResettableEnumeration *aFirst, 
														 ResettableEnumeration *aSecond );

public: virtual  ResettableEnumeration *getProd( ResettableEnumeration *aFirst, 
												 ResettableEnumeration *aSecond );

  /*
public: virtual  ResettableEnumeration *getBeta( ResettableEnumeration *anEnum );
public: virtual  ResettableEnumeration *getBetaOfN( ResettableEnumeration *anEnum, Index aCardinality );

public: virtual  ResettableEnumeration *getOrdBeta( ResettableEnumeration *anEnum );
public: virtual  ResettableEnumeration *getOrdBetaOfN( ResettableEnumeration *anEnum, Index aCardinality );
*/

public: virtual  ResettableEnumeration *getInterleaved( ResettableEnumeration *anEnum, 
														ResettableEnumeration *aSecond );

#if defined( USE_THREADS )
  /**
	 Converts given passive iterator to the active iterator.
	 Spawns dedicated thread to fetch elements from 
	 anIterator.

	 XXX this is unstable! It leaks memory.
   */
public: virtual Enumeration *convertIterator( Iterator *anIterator );
#endif

  /**
	*/
public: EnumerationAlgorithms();

  /**
	*/
public: virtual ~EnumerationAlgorithms();


public: static EnumerationAlgorithms *get();

  /**
	*/
public:  virtual Top *clone() const;

  /**
	*/
public:  virtual String  getClassName() const;

protected: static EnumerationAlgorithms *instance;


#if defined( TESTING )
public: virtual boolean tester( int ) const;
#endif
};


abstract class EnumUnaryOp : public ResettableEnumeration
{
public: EnumUnaryOp( ResettableEnumeration *aFirst );
public: virtual ~EnumUnaryOp();
public: virtual void reset();

protected: CRef< ResettableEnumeration > firstArg;
};

abstract class EnumBinaryOp : public EnumUnaryOp
{
public: EnumBinaryOp( ResettableEnumeration *aFirst, 
					  ResettableEnumeration *aSecond );
public: virtual ~EnumBinaryOp();
public: virtual void reset();

protected: CRef< ResettableEnumeration > secondArg;
};

class SumEnumeration : public EnumBinaryOp,
					   public virtual Object
{
public: SumEnumeration( ResettableEnumeration *aFirst, 
						ResettableEnumeration *aSecond );
public: virtual ~SumEnumeration();

public: virtual Top *getNextElement();
public: virtual boolean hasMoreElements();
public: virtual void reset();

public:  virtual Top *clone() const;

protected: boolean firstDone;
};

class UnionEnumeration : public EnumBinaryOp,
						 public virtual Object
{
public: UnionEnumeration( ResettableEnumeration *aFirst, 
						  ResettableEnumeration *aSecond );
public: virtual ~UnionEnumeration();

public: virtual Top *getNextElement();
public: virtual boolean hasMoreElements();
public: virtual void reset();

public:  virtual Top *clone() const;

protected: virtual boolean getNextElementInternal();

protected: Top *cachedObject;

protected: boolean firstDone;
protected: boolean cacheValid;
protected: boolean hasMore;

};

class IntersectionEnumeration : public EnumBinaryOp,
								public virtual Object
{
public: IntersectionEnumeration( ResettableEnumeration *aFirst, 
								 ResettableEnumeration *aSecond );
public: virtual ~IntersectionEnumeration();

public: virtual Top *getNextElement();
public: virtual boolean hasMoreElements();
public: virtual void reset();

public:  virtual Top *clone() const;

protected: virtual boolean getNextElementInternal();

protected: Top *cachedObject;

protected: boolean cacheValid;
protected: boolean hasMore;
};


class ContainerEnumeration : public ResettableEnumeration,
							 public virtual Object
{
public: ContainerEnumeration( Container *aContainer );
public: virtual ~ContainerEnumeration();

public: virtual Top *getNextElement();
public: virtual boolean hasMoreElements();
public: virtual void reset();

public:  virtual Top *clone() const;

protected: CRef< Container > container;
protected: CRef< Enumeration > en;
};

class ProdEnumeration : public EnumBinaryOp,
						public virtual Object
{
public: ProdEnumeration( ResettableEnumeration *aFirst, 
						 ResettableEnumeration *aSecond );
public: virtual ~ProdEnumeration();

public: virtual Top *getNextElement();
public: virtual boolean hasMoreElements();
public: virtual void reset();

public:  virtual Top *clone() const;

protected: const boolean isEmpty;
protected: Top *rowObject;
};

class InterleavedEnumeration : public EnumBinaryOp,
						public virtual Object
{
public: InterleavedEnumeration( ResettableEnumeration *aFirst, 
								ResettableEnumeration *aSecond );
public: virtual ~InterleavedEnumeration();

public: virtual Top *getNextElement();
public: virtual boolean hasMoreElements();
public: virtual void reset();

public:  virtual Top *clone() const;

protected: ResettableEnumeration *current;
};

#if defined( USE_THREADS )
class EnumerationOverIterator : public virtual Enumeration,
								public virtual Runnable,
								public virtual Object,
								public virtual Iterable
{
public: EnumerationOverIterator( Iterator *anIterator );
public: virtual boolean hasMoreElements();
public: virtual Top *getNextElement();

public: virtual void *run();

public: virtual void initIterations();
public: virtual void fireOn( Top *anElement );
public: virtual boolean isMore();
public: virtual void doneIterations();

protected: CRef< Iterator > iterator;
protected: CRef< Thread >  thread;
protected: CRef< CondVar > condition;
protected: Top *queue;
protected: boolean filled;

protected: boolean done;
};
#endif

typedef EnumerationAlgorithms EAlg;

END_QR_NAMESPACE

/*
 * $Log: EnumerationAlgorithms.hpp,v $
 * Revision 1.2  2000/08/30 12:20:35  philogelos
 * THROWS clauses updates to correspond to the real throws.
 *
 * Revision 1.1.1.1  2000/07/19 16:58:29  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.5  2000/04/09 12:00:47  god
 * CVS Log keyword correction finished
 *
 * Revision 1.4  2000/04/09 11:29:17  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.3  2000/04/07 17:06:27  god
 * Mode CRefs<> added
 *
 * Revision 1.2  2000/04/06 11:57:51  god
 * converted to CRefs<> tests added to ::tester()
 *
 * Revision 1.1.1.1  2000/04/01 14:07:43  god
 * Imported sources
 *
 * Revision 1.5  1999/05/22 13:00:24  philogelos
 * Merging sources back from SPARC
 *
 * Revision 1.4  1999/03/03 19:09:07  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.3  1999/02/28 12:49:50  philogelos
 * ::findIndex() added
 *
 * Revision 1.2  1998/12/01 16:15:30  philogelos
 * conditionally introduce ::tester()
 *
 * Revision 1.1.1.1  1998/11/25 20:11:08  philogelos
 * Quercus Robusta
 * */

/* __ENUMERATIONALGORITHMS_HPP__ */
#endif
