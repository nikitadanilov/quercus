// -*-C++-*- 

/*  inc/ui/xq/Applet.hpp  */

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



#ifndef __APPLET_HPP__
#define __APPLET_HPP__

/* $Id: Applet.hpp,v 1.1.1.1 2000/07/19 17:15:22 philogelos Exp $ */

#if defined( INSIDE_XQ_SCOPE )

/**

   @author Philogelos
   @created
*/
public: class Applet : public virtual XqObject,
  public virtual Aq::EventDispatcher,
  public virtual PassiveObserver
{
public: Applet( Xq::Drawable *aDrawable, 
				Xq::XqEventSource *aSource, Xq::GC *aGC  );
public: virtual ~Applet();

public: virtual void paint( Xq::Drawable *aDrawable, Xq::GC *aGraphics ) = 0;

public: virtual Xq::Drawable *getDrawable() const;

public: virtual void activate();
public: virtual void deactivate();

public: virtual void onWindowEvent( Aq::WindowEvent *anEvent );
public: virtual HandlerResult fire( Condition *aCondition, 
									ObservationContext *aContext );

protected: Xq::Drawable *drawable;
protected: Xq::GC *graphics;
};

#endif

/*
 * $Log: Applet.hpp,v $
 * Revision 1.1.1.1  2000/07/19 17:15:22  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:37  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:43  god
 * Imported sources
*/

/* __APPLET_HPP__ */
#endif
