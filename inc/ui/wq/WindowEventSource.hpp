// -*-C++-*- 

/*  inc/ui/wq/WindowEventSource.hpp  */

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



#ifndef __WQ_WINDOWEVENTSOURCE_HPP__
#define __WQ_WINDOWEVENTSOURCE_HPP__

/* $Id: WindowEventSource.hpp,v 1.1.1.1 2000/07/19 17:14:59 philogelos Exp $ */

#if defined( INSIDE_WQ_SCOPE )

/**

   @author Philogelos
   @created
*/
public: class WindowEventSource : public WqEventSource
		{
		public: WindowEventSource();
		public: virtual boolean init();
		public: virtual void done();
		public: virtual Aq::AqEvent *getNextTypedElement();
		public: void selectMouseMotion( boolean isSelected );
		public: virtual boolean ignorableEvent( MSG *aMsg ) const;

		protected: Window *hostWindow;
		protected: boolean generateMouseMotionEvents;
		};

#endif

/* $Log: WindowEventSource.hpp,v $
/* Revision 1.1.1.1  2000/07/19 17:14:59  philogelos
/* stored sources into sourceforge.net CVS
/*
/* Revision 1.1.1.1  2000/04/01 14:07:41  god
/* Imported sources
/* */

/* __WQ_WINDOWEVENTSOURCE_HPP__ */
#endif
