// -*-C++-*- 

/*  inc/containers/TextContainer.hpp  */

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



#ifndef __TEXTCONTAINER_HPP__
#define __TEXTCONTAINER_HPP__

/* $Id: TextContainer.hpp,v 1.1.1.1 2000/07/19 17:12:41 philogelos Exp $ */

#include "String.hpp"
#include "Container.hpp"
#include "MutableContainerAdapter.hpp"
#include "MutableContainer.hpp"
#include "ModifiableContainer.hpp"
#include "RangedContainer.hpp"
#include "PuncturedContainer.hpp"
#include "IndexPosition.hpp"
#include "VersionedObject.hpp"
#include "defines.h"

typedef Index Point;
abstract class TextCommand;

class List;

class PointPosition;
class CaretPosition;

/**
   OBSOLETE.

   @author Philogelos
   @created
*/
class TextContainer : public RangedContainer,
					  public ModifiableContainer,
					  public PuncturedContainer,
					  public VersionedObject,
					  public virtual MutableContainerAdapter
{
public: TextContainer( String aSource );
public: TextContainer();

public: virtual ~TextContainer();

public: virtual String getContent() const;
public: virtual Point  getCaret() const;

public: virtual Index getX() const;
public: virtual Index getY() const;

public: virtual Index getXOf( Point aPoint ) const;
public: virtual Index getYOf( Point aPoint ) const;

public: virtual void  apply( TextCommand *aCommand );

public: virtual Point translate( Point aSource, Version aVersion );

public: virtual PointPosition *getCaretPosition();
public: virtual CaretPosition *getAlwaysCaretPosition() const;

public: virtual Index getLowBound() const;
public: virtual Index getHighBound() const;

public: virtual Top *getAt( const Index anIndex );
public: virtual Top *setAt( const Index anIndex, Top *aNewValue );

public: virtual PositionFactory *getDefaultPositionFactory() const;
public: virtual boolean canRemoveSlot( Position *aPosition ) const;
public: virtual void removeSlot( Position *aPosition );

public: virtual Position *getPunct() const;

public: virtual IndexPosition *getPosition( const Index anIndex );

public: virtual MutablePositionEnumeration *getMutableEnumeration() const;
public: virtual PositionEnumeration *getEnumeration() const;
public: virtual Index getCardinality() const;
public: virtual boolean isValid( const Position *aPosition ) const;

public:  virtual Top *clone() const;
public:  virtual String  getString() const;
public:  virtual String  getClassName() const;

protected: void init( String aSource );
protected: boolean isChar( const Top *anObject ) const;

protected: Point caret;
protected: String content;

protected: List *history;
};

abstract class TextCommand : public virtual Top
{
public: virtual void  apply( TextContainer *aTarget ) = 0;
  /* public: virtual void  undo( TextContainer *aTarget ) = 0; */
public: virtual Point translate( Point aSource ) = 0;
public: virtual Point undoTranslate( Point aSource ) = 0;
};

class PointPosition : public IndexPosition
{
public: PointPosition( TextContainer *aContainer, Point aPoint );

public: virtual void update();
public: TextContainer *getTextContainer() const;

public: virtual boolean isValid() const;
public: virtual Top *getValue() const;
public: virtual Top *setValue( Top *aNewValue );

protected: Version version;
};

class CaretPosition : public PointPosition
{
public: CaretPosition( TextContainer *aContainer );

public: virtual boolean isValid() const;
public: virtual Top *getValue() const;
public: virtual Top *setValue( Top *aNewValue );
};

/* $Log: TextContainer.hpp,v $
/* Revision 1.1.1.1  2000/07/19 17:12:41  philogelos
/* stored sources into sourceforge.net CVS
/*
/* Revision 1.1.1.1  2000/04/01 14:07:48  god
/* Imported sources
/*
 * Revision 1.2  1999/03/03 19:09:13  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.1  1999/02/28 13:04:33  philogelos
 * Added Files:
 * 	EmptyContainer.hpp EmptyStack.hpp LayeredContainer.hpp
 * 	MutableLayeredContainer.hpp PuncturedContainer.hpp Stack.hpp
 * 	TextContainer.hpp ValuePosition.hpp
 * Removed Files:
 * 	Modifier.hpp
 * */

/* __TEXTCONTAINER_HPP__ */
#endif
