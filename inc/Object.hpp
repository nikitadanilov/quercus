//-*-C++-*-

/*  inc/Object.hpp  */


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


#ifndef __OBJECT_HPP__

#define __OBJECT_HPP__
/* $Id: Object.hpp,v 1.2 2001/06/23 12:17:37 philogelos Exp $ */

#include "defines.h"
#include "Top.hpp"

#if defined( __BORLANDC__  )
#include <stddef.h>
#endif

/* #define GUARD_ADDREF */

#if defined( WANT_GUARD_ADDREF )
#define GUARD_ADDREF
#elif defined( UNWANT_GUARD_ADDREF )
#if defined( GUARD_ADDREF )
#undef GUARD_ADDREF
#endif
#endif

BEGIN_QR_NAMESPACE

class String;
class ShouldBeOverriden;
interface Protector;
interface LifeTimeController;

/** Terminal class in inheritance lattice.
	Every class in system inherits this class
	implementaion.

	Includes default implementation of Top
	interface.

	@see Top
	@author Philogelos
	@created ÇâÒ 18 ¸îÝ 1998 17:38:49
*/
class Object : virtual public Top
{

  /**
     Creates new object without external
     references, with life-time controller and
     protector set to nil.

     @postcond( !isRef() )
  */
public:  Object();

  /**
     Destroys object.
     If there is life-time controller for this 
     object it is notified of object destroying.
     After that controller and protecror are
     detached from this object.

     @precond( !isRef() )
  */
public:  virtual ~Object();

public:  virtual const Object *dontManage() const;

  /**
     Checks objects for sameness.
     As Object class defines no user-sensible structure
     of it's instances they are equal iff they are the
     same object.

     @precond( typeid( anOther ) == typeid( this ) )
  */
public:  virtual boolean equals( const Top *anOther ) const;

  /**
     Clones this instance.
     This method throws ShouldBeOverriden exception.

     @post false
     @see ShouldBeOverriden
   */
public:  virtual Top    *clone() const THROWS( ShouldBeOverriden * );

  /**
     General contract is that ::getString() returns
     string representation of object sensible in the
     application domain (``business data'') and
     ::toString() returns representation useful for
     debugging. Therefore reasonable implementation
     of ::toString() can call ::getString() and
     (pre-)|(ap-)pend some internal data (in this
     case, just instance address).

     @see #getString
   */
public:  virtual String  toString() const;

  /**
     Returns empty string due to lack of
     user-visible structure in this class.

     @see #toString
   */
public:  virtual String  getString() const;

  /**
     Returns ``Object''
  */
public:  virtual String  getClassName() const;

  /**
	 Returns 
	 ( ( this != null ) && ( getRefCount() >= 0 ) && equals( this ) )
  */
public:  virtual boolean invariant() const;


  /**
     Returns protector.

     @see #protector
  */
public:  virtual Protector *getProtector() const;

  /**
     Installs protector.
     XXX If we are changing protector and object was 
     under protection should we leave protection?

     @see protector
  */
public:  virtual void setProtector( Protector *aProtector ) const;


  /**
     Locks this object: enters protector protection (if any)
     and adds link from anOwner to this object
     (i.e., marks that this object is in use by anOwner).

     @see Protector
     @see Protector#enter
     @see LinkManager::reg
     @see #unlock
  */
public:  virtual void lock( const Top *anOwner ) const;

  /**
     Leaves protection of protector and marks that
     object is no longer in use by anOwner.

     @see Protector
     @see Protector#leave
     @see LinkManager::unreg
     @see #lock
     @see #lockRead
  */
public:  virtual void unlock( const Top *anOwner ) const;

  /**
     Locks this object to read: enters protector read protection
	 (if any) and adds link from anOwner to this object

     @see Protector
     @see Protector#enter
     @see LinkManager::reg
     @see #lock
  */
public:  virtual void lockRead( const Top *anOwner ) const;

  /**
     Installs life-time controller for this object.
     Controller will be notified about changes in
     number of registered links to this instance.

     @see LifeTimeController
     @see #addRef
     @see #delRef
     @see #getLifeTimeController
     @see #ltController
  */
public:  virtual void setLifeTimeController( LifeTimeController *aController ) const;
  /**
     Returns life-time controller for this object or nil if
     no controller were registered through 
     ::setLifeTimeController().

     @see LifeTimeController
     @see #setLifeTimeController
     @see #ltController
  */
public:  virtual LifeTimeController *getLifeTimeController() const;

  /**
     Increments number of references to this object
     and notifies object's life-time controller if any.

     @see #delRef
     @see #isRef
     @see #getRefCount
     @see #refCount
     @see #getLifeTimeController
  */
public:  virtual void addRef() const;

  /**
     Decrements number of references to this object
     and notifies object's life-time controller if any.

     @see #addRef
     @see #isRef
     @see #getRefCount
     @see #refCount
     @see #getLifeTimeController
  */
public:  virtual void delRef() const;

  /**
     Returns number of references to this object.

     @see #delRef
     @see #addRef
     @see #isRef
     @see #refCount
  */
public:  virtual Index getRefCount() const;

  /**
     Returns true iff there are references to this object.

     @see #delRef
     @see #addRef
     @see #getRefCount
     @see #refCount
  */
public:  virtual boolean isRef() const;


  /**
     True iff object is currently being deleted
     (that is it's destructor was called but
     didn't complete). This is useful
     to avoid infinite loops during reference-count
     based garbage collection in data structures with
     cyclic pointers.

     @see LinkManager
     @see #setBeingDeleted
     @see #beingDeleted
  */
public:  virtual boolean isBeingDeleted() const;

  /**
     Declares that object is being deleted.
     This flag is set by LinkManager just before it 
     about to call object's destructor.

     @see LinkManager
     @see #isBeingDeleted
     @see #beingDeleted
  */
public:  virtual void setBeingDeleted( boolean aFlag ) const;


#if defined( TESTING )
  /**
     Test method.
  */
public:  virtual boolean tester( int aParam ) const;
#endif

  /**
     Number of references to this object from other
     objects in the system.

     @see #addRef
     @see #delRef
     @see #isRef
     @see #getRefCount
  */
protected: mutable Index refCount;

  /**
     Protector which auspices this object enjoys.
     Presumably some kind of synchronization object
     (mutex, semaphore etc.).

     @see #getProtector
     @see #setProtector
     @see #lock
     @see #unlock
  */
protected: mutable Protector *protector;

  /**
     Object controlling this object life span.

     @see getLifeTimeController
     @see setLifeTimeController
  */
protected: mutable LifeTimeController *ltController;

  /**
     True iff object is currently being deleted.

     @see LinkManager
     @see #setBeingDeleted
     @see #isBeingDeleted
  */
protected: mutable boolean beingDeleted;

#if defined( USE_PER_CLASS_NEW )
public: void *operator new( size_t size );
#endif
};

END_QR_NAMESPACE

/*
 * $Log: Object.hpp,v $
 * Revision 1.2  2001/06/23 12:17:37  philogelos
 *  . ::setProtector(), ::setLifeTimeController() made const
 *  . ::protector, ::ltController made mutable
 *  . ::beingDeleted is no longer bit-field
 *
 * Revision 1.1.1.1  2000/07/19 16:57:02  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.3  2000/04/29 14:58:07  god
 * ::lockRead() added
 *
 * Revision 1.2  2000/04/09 11:29:16  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:38  god
 * Imported sources
 *
 * Revision 1.5  1999/05/22 13:00:23  philogelos
 * Merging sources back from SPARC
 *
 * Revision 1.4  1999/03/03 19:09:04  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.3  1999/02/28 12:39:00  philogelos
 * ::dontManage() added
 *
 * Revision 1.2  1998/12/01 16:14:14  philogelos
 * conditionally introduce ::tester()
 *
 * Revision 1.1.1.1  1998/11/25 20:11:04  philogelos
 * Quercus Robusta
 *
 * Revision 1.4  1998/07/07 14:29:48  philogelos
 * Memory leak in SUNWspro dynamic_cast fixed.
 *
 * Revision 1.3  1998/06/22 18:12:54  philogelos
 * Enumerations and containers added
 *
 * Revision 1.2  1998/06/22 13:34:22  philogelos
 * ::getString() added
 *
 * Revision 1.1.1.1  1998/06/22 08:47:11  philogelos
 * First version under CVS
 *
 * Revision 1.1.1.1  1998/04/01 17:15:29  philogelos
 * first version under CVS
 * */

/* __OBJECT_HPP__ */
#endif
