// -*-C++-*- 

/*  src/containers/TextContainer.cpp  */

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



/* $Id: TextContainer.cpp,v 1.1.1.1 2000/07/19 16:50:39 philogelos Exp $ */
static char cvsid[] = "@(#)$Id: TextContainer.cpp,v 1.1.1.1 2000/07/19 16:50:39 philogelos Exp $";

#include "containers/TextContainer.hpp"
#include "containers/lists/List.hpp"
#include "Char.hpp"
#include "Debug.hpp"

TextContainer::TextContainer( String aSource )
{
  init( aSource );
}

TextContainer::TextContainer()
{
  init( String() );
}

TextContainer::~TextContainer()
{
  if( history != ( List * ) nil )
	{
	  LinkManager::free( this, history );
	}
}

String TextContainer::getContent() const
{
  return content;
}

Point  TextContainer::getCaret() const
{
  return caret;
}

Index TextContainer::getX() const
{
  return getXOf( getCaret() );
}

Index TextContainer::getY() const
{
  return getYOf( getCaret() );
}

Index TextContainer::getXOf( Point aPoint ) const
{
  return 0;
}

Index TextContainer::getYOf( Point aPoint ) const
{
  return 0;
}

void  TextContainer::apply( TextCommand *aCommand )
{
  preC_( aCommand != ( TextCommand * ) null );
  preC_( history != ( List * ) null );

  history -> prepend( aCommand );
  aCommand -> apply( this );
}

Point TextContainer::translate( Point aSource, Version aVersion )
{
  preC_( history != ( List * ) null );

  OGuard _this( this, this );

  test_( aVersion <= getVersion() );
  if( aVersion == getVersion() )
	{
	  return aSource;
	}
  history -> setCurrentAt( getVersion() - aVersion - 1 );
  while( true )
	{
	  Top *item;
	  TextCommand *cmd;

	  item = history -> getCurrentValue();
	  cmd = dynamic_cast< TextCommand * >( item );
	  test_( cmd != ( TextCommand * ) null );

	  aSource = cmd -> translate( aSource );
	  if( history -> isFirst() )
		{
		  break;
		}
	  else
		{
		  history -> prev();
		}
	}

  return aSource;
}

PointPosition *TextContainer::getCaretPosition()
{
  return new PointPosition( this, getCaret() );
}

CaretPosition *TextContainer::getAlwaysCaretPosition() const
{
  return new CaretPosition( ( TextContainer * ) this );
}

Index TextContainer::getLowBound() const
{
  return 0;
}

Index TextContainer::getHighBound() const
{
  return( getContent().length() );
}

Top *TextContainer::getAt( const Index anIndex )
{
  preC_( isValidIndex( anIndex ) );
  //  return( getContent().getCharAt( anIndex ) );
  return nil;
}

Top *TextContainer::setAt( const Index anIndex, Top *aNewValue )
{
  preC_( isValidIndex( anIndex ) );
  preC_( isChar( aNewValue ) );
  //  return( getContent().setCharAt( anIndex, aNewValue ) );
  return nil;
}

PositionFactory *TextContainer::getDefaultPositionFactory() const
{
  return ( PositionFactory * ) nil;
}

boolean TextContainer::canRemoveSlot( Position *aPosition ) const
{
  return false;
}

void TextContainer::removeSlot( Position *aPosition )
{
  preC_( aPosition != ( Position * ) nil );
  preC_( canRemoveSlot( aPosition ) );
}

Position *TextContainer::getPunct() const
{
  return getAlwaysCaretPosition();
}

IndexPosition *TextContainer::getPosition( const Index anIndex )
{
  return new PointPosition( this, anIndex );
}

MutablePositionEnumeration *TextContainer::getMutableEnumeration() const
{
  return RangedContainer::getMutableEnumeration();
}

PositionEnumeration *TextContainer::getEnumeration() const
{
  return getMutableEnumeration();
}

Index TextContainer::getCardinality() const
{
  return RangedContainer::getCardinality();
}

boolean TextContainer::isValid( const Position *aPosition ) const
{
  preC_( aPosition != ( Position * ) nil );
  return( aPosition -> isValid() );
}

Top *TextContainer::clone() const
{
  return new TextContainer( getContent() );
}

String  TextContainer::getString() const
{
  return String( "Content: " ) + getContent() +
	"caret at: " + String( getCaret() ) +
	"history: " + ( history -> getString() );
}

String  TextContainer::getClassName() const
{
  return "TextContainer";
}


void TextContainer::init( String aSource )
{
  content = aSource;
  history = new List();
  LinkManager::reg( this, history );
}

boolean TextContainer::isChar( const Top *anObject ) const
{
  return( dynamic_cast< Char * >( ( Top * ) anObject ) != null );
}

PointPosition::PointPosition( TextContainer *aContainer, Point aPoint ) :
  IndexPosition( aPoint, aContainer )
{
  version = aContainer -> getVersion();
}

TextContainer *PointPosition::getTextContainer() const
{
  Container *placeholder;
  TextContainer *container;

  placeholder = getContainer();
  container = dynamic_cast< TextContainer * >( placeholder );

  postC_( container != ( TextContainer * ) nil );
  return container;
}

void PointPosition::update()
{
  index_ = getTextContainer() -> translate( index_, version );
}

boolean PointPosition::isValid() const
{
  ( ( PointPosition * ) this ) -> update();
  return( getContainer() -> isValid( this ) );
}

Top *PointPosition::getValue() const
{
  ( ( PointPosition * ) this ) -> update();
  test_( isValid() );
  return( getTextContainer() -> getAt( getIndex() ) );
}

Top *PointPosition::setValue( Top *aNewValue )
{
  update();
  test_( isValid() );
  return( getTextContainer() -> setAt( getIndex(), aNewValue ) );
}

CaretPosition::CaretPosition( TextContainer *aContainer ) :
  PointPosition( aContainer, aContainer -> getCaret() )
{
}

boolean CaretPosition::isValid() const
{
  return( ! ( getTextContainer() -> isEmpty() ) );
}

Top *CaretPosition::getValue() const
{
  return( getTextContainer() -> getAt
		  ( getTextContainer() -> getCaret() ) );
}

Top *CaretPosition::setValue( Top *aNewValue )
{
  return( getTextContainer() -> setAt
		  ( getTextContainer() -> getCaret(), aNewValue ) );
}


#if defined(_INLINE)
#include "../src/Debug.ipp"
#endif

/* $Log: TextContainer.cpp,v $
/* Revision 1.1.1.1  2000/07/19 16:50:39  philogelos
/* stored sources into sourceforge.net CVS
/*
/* Revision 1.1.1.1  2000/04/01 14:07:29  god
/* Imported sources
/*
 * Revision 1.2  1999/03/03 19:09:39  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.1  1999/02/28 16:30:02  philogelos
 * LayeredContainer adde. Tuned for inlines.
 * */

