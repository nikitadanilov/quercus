// -*-C++-*- 

/*  src/ui/wq/WindowEventSource.cpp  */

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



/* $Id: WindowEventSource.cpp,v 1.1.1.1 2000/07/19 16:53:25 philogelos Exp $ */
#if !defined(_INLINE)
static char cvsid[] = "@(#)$Id: WindowEventSource.cpp,v 1.1.1.1 2000/07/19 16:53:25 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif

#include "ui/wq/WqCommon.hpp"
#include "Debug.hpp"

#if defined( USE_WQ )

BEGIN_QR_NAMESPACE

Wq::WindowEventSource::WindowEventSource()
{
  selectMouseMotion( true );
}

void Wq::WindowEventSource::selectMouseMotion( boolean isSelected )
{
  generateMouseMotionEvents = isSelected;
}

boolean Wq::WindowEventSource::init()
{
  char *className;
  HANDLE handle;

  className = Wq::Window::getDefaultClassName().getChars();
  handle = CreateWindow(
						className,
						"",
						WS_OVERLAPPEDWINDOW | WS_VISIBLE,
						CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, 
						NULL, NULL, GetModuleHandle( NULL ), NULL );
  delete []className;

  if( handle == NULL )
	{
	  throw new Errno( "CreateWindow() in Wq::Window::winLoop()", null,
					   GetLastError() );
	}

  hostWindow = new Wq::Window( handle );

  SetLastError( 0 );
  GUI_WRAP( SetWindowLong( handle, 0, ( long ) ( void * ) hostWindow ), 
			0, Wq::WindowEventSource::init() );
  hostWindow -> eventLoop = THR_SYSTEM -> getSelf();
  LinkManager::reg( hostWindow, hostWindow -> eventLoop );
	
  hostWindow -> events = this;
  LinkManager::reg( hostWindow, hostWindow -> events );

  freshWindow = hostWindow;
  winCreateSema -> inc();

  return true;
}

void Wq::WindowEventSource::done()
{
  GUI_WRAP( DestroyWindow( hostWindow -> getHandle() ), 0, 
			Wq::WindowEventSource::done() );
}

boolean Wq::WindowEventSource::ignorableEvent( MSG *aMsg ) const
{
  preC_( aMsg != NULL );

  Wq::WqEvent::initTypes();
  test_( Wq::WqEvent::types != NULL );

  return( ( 0 <= aMsg -> message ) && ( aMsg -> message <= WM_PENWINLAST ) &&
		  ( !generateMouseMotionEvents ) && 
		  ( Wq::WqEvent::types[ aMsg -> message ].type == 
			Wq::WqEvent::mouse ) );
}

Aq::AqEvent *Wq::WindowEventSource::getNextTypedElement()
{
  int retCode;
  MSG msg;

  try
	{
	  do
		{
		  retCode = 
			GetMessage( &msg, ( HWND ) hostWindow -> getHandle(), 0, 0 );
		  if( ( retCode == -1 ) || ( retCode == 0 ) || 
			  ( msg.message == WM_DESTROY ) || ( msg.message == WM_QUIT ) ||
			  ( msg.message == Wq::Window::terminateMessage ) )
			{
			  doneWithEvents = true;
			  return NULL;
			}
		}
	  while( ignorableEvent( &msg ) );
	  return Wq::WqEvent::create( &msg );
	}
  catch( Wq::CloseWindowException *aMessenger )
	{
	  OGuard _page( aMessenger, this );
	  doneWithEvents = true;
	  return NULL;
	}
}

END_QR_NAMESPACE

#if defined(_INLINE)
#include "../src/Debug.ipp"
#endif

/* USE_WQ */
#endif

/* $Log: WindowEventSource.cpp,v $
/* Revision 1.1.1.1  2000/07/19 16:53:25  philogelos
/* stored sources into sourceforge.net CVS
/*
/* Revision 1.1.1.1  2000/04/01 14:07:36  god
/* Imported sources
/* */
