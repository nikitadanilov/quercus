// -*-C++-*- 

/*  src/platform/Aq.cpp  */

/*
 * Author: Philogelos A. <Philogelos@yahoo.com>
 * Maintainer: Philogelos A.
 * Keywords: C++, library, containers
 *
 * Copyright (C) 1999 Philogelos A.
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



/* $Id: Aq.cpp,v 1.1.1.1 2000/07/19 16:52:31 philogelos Exp $ */
#if !defined(_INLINE)
static char cvsid[] = "@(#)$Id: Aq.cpp,v 1.1.1.1 2000/07/19 16:52:31 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif

#include "ui/aq/Aq.hpp"
#include "Debug.hpp"

#if defined(__SUNPRO_CC) && (__SUNPRO_CC >= 0x510)
extern "C" double sqrt( double );
#else
#include <math.h>
#endif

BEGIN_QR_NAMESPACE

boolean Aq::GUISystem::isCompatible( const Aq::GUISystem *anOther ) const
{
  return( this == anOther );
}

Aq::AqObject::AqObject( const GUISystem *aSystem ) : system( aSystem )
{
  preC_( aSystem != NULL );

  OREG( system );
}

Aq::AqObject::~AqObject()
{
  FCDONE( system );
}

const Aq::GUISystem *Aq::AqObject::getGUISystem() const
{
  return system;
}

boolean Aq::AqObject::isCompatible( const GUISystem *aSystem ) const
{
  return 
	( getGUISystem() == NULL ) || 
	( getGUISystem() -> isCompatible( aSystem ) );
}

boolean Aq::AqObject::isCompatible( const AqObject *anObject ) const
{
  preC_( anObject != NULL );

  return isCompatible( anObject -> getGUISystem() );
}

void Aq::AqEvent::announce()
{}
  
void Aq::AqEvent::dispatch( Aq::EventDispatcher *aDispatcher )
{
  preC_( aDispatcher != NULL );

  aDispatcher -> onOtherEvent( this );
  aDispatcher -> onAnyEvent( this );
}

String Aq::AqEvent::getClassName() const
{
  return "AqEvent";
}

Aq::Window::Window( GUISystem *aSystem ) :
  Drawable( aSystem )
{}

void Aq::EventDispatcher::onKeyEvent( KeyEvent * )
{}

void Aq::EventDispatcher::onButtonEvent( ButtonEvent * )
{}

void Aq::EventDispatcher::onMouseMotionEvent( MouseMotionEvent * )
{}

void Aq::EventDispatcher::onFocusEvent( FocusEvent * )
{}

void Aq::EventDispatcher::onWindowEvent( WindowEvent * )
{}

void Aq::EventDispatcher::onDestroyEvent( DestroyEvent * )
{}

void Aq::EventDispatcher::onResizeEvent( ResizeEvent * )
{}

void Aq::EventDispatcher::onSelectionEvent( SelectionEvent * )
{}
  
void Aq::EventDispatcher::onOtherEvent( AqEvent * )
{}
  
void Aq::EventDispatcher::onAnyEvent( AqEvent * )
{}

boolean  Aq::EventSource::init()
{
  doneWithEvents = false;
  return true;
}

void  Aq::EventSource::done()
{}

void  Aq::EventSource::processEvent( AqEvent * )
{}

void *Aq::EventSource::run()
{
  if( init() )
	{
	  while( hasMoreElements() )
		{
		  AqEvent *event;

		  event = getNextTypedElement();
		  
		  if( event != NULL )
			{
			  OGuard _ev( event, this );

			  processEvent( event );
			  fire( event, new ObservationContext() );
			}
		}
	}
  done();
  return NULL;
}

boolean Aq::EventSource::hasMoreElements()
{
  return !isDoneWithEvents();
}

boolean Aq::EventSource::isDoneWithEvents() const
{
  return doneWithEvents;
}


void Aq::EventSource::initIterations()
{
  init();
}

void Aq::EventSource::fireOn( Top *anElement )
{
  processEvent( TCAST( anElement, Aq::AqEvent ) );
}

boolean Aq::EventSource::isMore()
{
  return hasMoreElements();
}

void Aq::EventSource::doneIterations()
{
  done();
}


void Aq::KeyEvent::dispatch( Aq::EventDispatcher *aDispatcher )
{
  preC_( aDispatcher != NULL );

  aDispatcher -> onKeyEvent( this );
  aDispatcher -> onAnyEvent( this );
}

String Aq::KeyEvent::getClassName() const
{
  return "KeyEvent";
}

void Aq::ButtonEvent::dispatch( Aq::EventDispatcher *aDispatcher )
{
  preC_( aDispatcher != NULL );

  aDispatcher -> onButtonEvent( this );
  aDispatcher -> onAnyEvent( this );
}

String Aq::ButtonEvent::getClassName() const
{
  return "ButtonEvent";
}

void Aq::MouseMotionEvent::dispatch( Aq::EventDispatcher *aDispatcher )
{
  preC_( aDispatcher != NULL );

  aDispatcher -> onMouseMotionEvent( this );
  aDispatcher -> onAnyEvent( this );
}

String Aq::MouseMotionEvent::getClassName() const
{
  return "MouseMotionEvent";
}

void Aq::FocusEvent::dispatch( Aq::EventDispatcher *aDispatcher )
{
  preC_( aDispatcher != NULL );

  aDispatcher -> onFocusEvent( this );
  aDispatcher -> onAnyEvent( this );
}

String Aq::FocusEvent::getClassName() const
{
  return "FocusEvent";
}

void Aq::WindowEvent::dispatch( Aq::EventDispatcher *aDispatcher )
{
  preC_( aDispatcher != NULL );

  aDispatcher -> onWindowEvent( this );
  aDispatcher -> onAnyEvent( this );
}

String Aq::WindowEvent::getClassName() const
{
  return "WindowEvent";
}

void Aq::DestroyEvent::dispatch( Aq::EventDispatcher *aDispatcher )
{
  preC_( aDispatcher != NULL );

  aDispatcher -> onDestroyEvent( this );
  aDispatcher -> onAnyEvent( this );
}

String Aq::DestroyEvent::getClassName() const
{
  return "DestroyEvent";
}

void Aq::ResizeEvent::dispatch( Aq::EventDispatcher *aDispatcher )
{
  preC_( aDispatcher != NULL );

  aDispatcher -> onResizeEvent( this );
  aDispatcher -> onAnyEvent( this );
}

String Aq::ResizeEvent::getClassName() const
{
  return "ResizeEvent";
}

void Aq::SelectionEvent::dispatch( Aq::EventDispatcher *aDispatcher )
{
  preC_( aDispatcher != NULL );

  aDispatcher -> onSelectionEvent( this );
  aDispatcher -> onAnyEvent( this );
}

String Aq::SelectionEvent::getClassName() const
{
  return "SelectionEvent";
}



Aq::Point::Point( CoordX aX, CoordY aY )
{
  init( aX, aY );
}

Aq::Point::Point( Coord *aCoord )
{
  preC_( aCoord != NULL );

  init( aCoord[ Aq::X ], aCoord[ Aq::Y ] );
}

Aq::Point::Point( const Point &aPoint )
{
  init( aPoint.getX(), aPoint.getY() );
}

Aq::Point::~Point()
{}

Aq::CoordX Aq::Point::getX() const
{
  return get( Aq::X );
}

Aq::CoordY Aq::Point::getY() const
{
  return get( Aq::Y );
}

Aq::Coord Aq::Point::get( Dimension aDim ) const
{
  preC_( ( aDim == Aq::X ) || ( aDim == Aq::Y ) );

  return coord[ aDim ];
}

void Aq::Point::setX( CoordX aX )
{
  set( Aq::X, aX );
}

void Aq::Point::setY( CoordY aY )
{
  set( Aq::Y, aY );
}

void Aq::Point::set( Dimension aDim, Coord aCoord )
{
  preC_( ( aDim == Aq::X ) || ( aDim == Aq::Y ) );

  coord[ aDim ] = aCoord;
}

void Aq::Point::init( CoordX aX, CoordY aY )
{
  setX( aX );
  setY( aY );
}

Aq::Rect::Rect( CoordX aX, CoordY aY, Size aWidth, Size aHeight )
{
  init( aX, aY, aX + aWidth, aY + aHeight );
}

Aq::Rect::Rect( CoordX aLUX, CoordY aLUY, CoordX aRDX, CoordY aRDY )
{
  init( aLUX, aLUY, aRDX, aRDY );
}

Aq::Rect::Rect( Point aLU, Size aWidth, Size aHeight )
{
  init( aLU.getX(), aLU.getY(), aLU.getX() + aWidth, aLU.getY() + aHeight );
}

Aq::Rect::Rect( Point aLU, Point aRD )
{
  init( aLU.getX(), aLU.getY(), aRD.getX(), aRD.getY() );
}

Aq::Rect::~Rect()
{
  FCDONE( lu );
  FCDONE( rd );
}

double Aq::Rect::getDiagonal() const
{
  return sqrt( getWidth() * getWidth() + getHeight() * getHeight() );
}

Index Aq::Rect::getArea() const
{
  return getWidth() * getHeight();
}

Aq::Point *Aq::Rect::getLU() const
{
  return lu;
}

Aq::Point *Aq::Rect::getRD() const
{
  return rd;
}

Aq::Size Aq::Rect::getWidth() const
{
  return getRD() -> getX() - getLU() -> getX();
}

Aq::Size Aq::Rect::getHeight() const
{
  return getRD() -> getY() - getLU() -> getY();
}

void Aq::Rect::init( CoordX aLUX, CoordY aLUY, CoordX aRDX, CoordY aRDY )
{
  FINIT( lu, new Aq::Point( aLUX, aLUY ) );
  FINIT( rd, new Aq::Point( aRDX, aRDY ) );
}

Aq::GraphicContext::GraphicContext( GUISystem *aSystem ) :
  AqObject( aSystem )
{}

Aq::Drawable::Drawable( GUISystem *aSystem ) :
  AqObject( aSystem )
{}

Aq::Painter::Painter( GraphicContext *aContext, Drawable *aDrawable ) :
  AqObject( aContext -> getGUISystem() )
{
  preC_( aContext != NULL );
  preC_( aDrawable != NULL );
  preC_( aContext -> isCompatible( aDrawable ) );

  FNNINIT( context, aContext );
  FNNINIT( drawable, aDrawable );
}

Aq::Painter::~Painter()
{
  FDONE( drawable );
  FDONE( context );
}

Aq::GraphicContext *Aq::Painter::getContext() const
{
  return context;
}

Aq::Drawable *Aq::Painter::getDrawable() const
{
  return drawable;
}

void Aq::Painter::setContext( GraphicContext *aContext )
{
  preC_( aContext != NULL );
  preC_( aContext -> isCompatible( drawable ) );

  FMOVE( context, aContext );
}

void Aq::Painter::setDrawable( Drawable *aDrawable )
{
  preC_( aDrawable != NULL );
  preC_( aDrawable -> isCompatible( context ) );

  FMOVE( drawable, aDrawable );
}

void Aq::Painter::drawPLine( Point *aStart, Point *anEnd ) const
{
  preC_( aStart != NULL );
  preC_( anEnd != NULL );

  drawLine( aStart -> getX(), aStart -> getY(),
			anEnd -> getX(), anEnd -> getY() );
}

void Aq::Painter::drawPPoint( Point *aPoint ) const
{
  preC_( aPoint != NULL );

  drawPoint( aPoint -> getX(), aPoint -> getY() );
}

void Aq::Painter::drawString( CoordX aX, CoordY aY, String aString ) const
{
  char *text;

  text = aString.getChars();
  drawCString( aX, aY, text );
  delete []text;
}

void Aq::Painter::fillPRectangle( Rect *aRect ) const
{
  preC_( aRect != NULL );

  fillRectangle( aRect -> getLU() -> getX(),
				 aRect -> getLU() -> getY(),
				 aRect -> getWidth(), aRect -> getHeight() );
}

void Aq::Painter::clearPRectangle( Rect *aRect ) const
{
  preC_( aRect != NULL );

  clearRectangle( aRect -> getLU() -> getX(),
				  aRect -> getLU() -> getY(),
				  aRect -> getWidth(), aRect -> getHeight() );
}

void Aq::Painter::copyRPFrom( Rect *aSource, Drawable *aDrawable,
							  Point *aPoint ) const
{
  preC_( aSource != NULL );
  preC_( aPoint != NULL );

  copyFrom( aSource -> getLU() -> getX(), aSource -> getLU() -> getY(), 
			aSource -> getWidth(), aSource -> getHeight(),
			aDrawable,
			aPoint -> getX(), aPoint -> getY() );
}

Aq::PainterGuard::PainterGuard( const Painter *aPainter, const Top *anOwner ) :
  OGuard( aPainter, anOwner )
{
  getPainter() -> init();
}

Aq::PainterGuard::~PainterGuard()
{
  getPainter() -> done();
}

Aq::Painter *Aq::PainterGuard::getPainter() const
{
  return TCAST( target, Aq::Painter );
}

END_QR_NAMESPACE

#if defined(_INLINE)
#include "../src/Debug.ipp"
#endif


/*
 * $Log: Aq.cpp,v $
 * Revision 1.1.1.1  2000/07/19 16:52:31  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:44  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:37  god
 * Imported sources
*/
