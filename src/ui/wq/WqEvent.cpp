// -*-C++-*- 

/*  src/ui/wq/WqEvent.cpp  */

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



/* $Id: WqEvent.cpp,v 1.1.1.1 2000/07/19 16:53:55 philogelos Exp $ */
#if !defined(_INLINE)
static char cvsid[] = "@(#)$Id: WqEvent.cpp,v 1.1.1.1 2000/07/19 16:53:55 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif

#include "ui/wq/WqCommon.hpp"
#include "Debug.hpp"

#if defined( USE_WQ )

BEGIN_QR_NAMESPACE

Wq::WqEvent::WqEvent( MSG *anEvent )
{
  PLAF -> memcpy( &event, anEvent, sizeof event );
}

String Wq::WqEvent::toString() const
{
  String result;

  result = Object::toString() + " [" + getEventName( event.message ) + "]";
  result += String
	( " hwnd: 0x%x message: %li wParam: %li lParam: %li"
	  " time: %li x: %i y: %i" ).
	sprintf( 1, event.hwnd, ( long ) event.message,
			 ( long ) event.wParam, ( long ) event.lParam,
			 ( long ) event.time, event.pt.x, event.pt.y );
  return result;
}

Wq::WqEvent::MessageType *Wq::WqEvent::types = NULL;

void Wq::WqEvent::initTypes()
{
  if( types == NULL )
	{
	  types = new Wq::WqEvent::MessageType[ WM_PENWINLAST + 1 ];

#define F( MSG, NAME, TYPE ) types[ MSG ].type = TYPE ; types[ MSG ].name = NAME

	F( WM_VKEYTOITEM, "WM_VKEYTOITEM", Wq::WqEvent::key );
	F( WM_CHARTOITEM, "WM_CHARTOITEM", Wq::WqEvent::key );
	F( WM_KEYDOWN, "WM_KEYDOWN", Wq::WqEvent::key );
	F( WM_KEYUP, "WM_KEYUP", Wq::WqEvent::key );
	F( WM_CHAR, "WM_CHAR", Wq::WqEvent::key );
	F( WM_DEADCHAR, "WM_DEADCHAR", Wq::WqEvent::key );
	F( WM_SYSKEYDOWN, "WM_SYSKEYDOWN", Wq::WqEvent::key );
	F( WM_SYSKEYUP, "WM_SYSKEYUP", Wq::WqEvent::key );
	F( WM_SYSCHAR, "WM_SYSCHAR", Wq::WqEvent::key );
	F( WM_SYSDEADCHAR, "WM_SYSDEADCHAR", Wq::WqEvent::key );
	F( WM_KEYLAST, "WM_KEYLAST", Wq::WqEvent::key );
	F( WM_MENUCHAR, "WM_MENUCHAR", Wq::WqEvent::key );
	F( WM_HOTKEY, "WM_HOTKEY", Wq::WqEvent::key );
	F( WM_LBUTTONDOWN, "WM_LBUTTONDOWN", Wq::WqEvent::button );
	F( WM_LBUTTONUP, "WM_LBUTTONUP", Wq::WqEvent::button );
	F( WM_LBUTTONDBLCLK, "WM_LBUTTONDBLCLK", Wq::WqEvent::button );
	F( WM_RBUTTONDOWN, "WM_RBUTTONDOWN", Wq::WqEvent::button );
	F( WM_RBUTTONUP, "WM_RBUTTONUP", Wq::WqEvent::button );
	F( WM_RBUTTONDBLCLK, "WM_RBUTTONDBLCLK", Wq::WqEvent::button );
	F( WM_MBUTTONDOWN, "WM_MBUTTONDOWN", Wq::WqEvent::button );
	F( WM_MBUTTONUP, "WM_MBUTTONUP", Wq::WqEvent::button );
	F( WM_MBUTTONDBLCLK, "WM_MBUTTONDBLCLK", Wq::WqEvent::button );
	F( WM_SETCURSOR, "WM_SETCURSOR", Wq::WqEvent::mouse );
	F( WM_MOUSEACTIVATE, "WM_MOUSEACTIVATE", Wq::WqEvent::mouse );
	F( WM_MOUSEMOVE, "WM_MOUSEMOVE", Wq::WqEvent::mouse );
#if(_WIN32_WINNT >= 0x0400)
	F( WM_MOUSEWHEEL, "WM_MOUSEWHEEL", Wq::WqEvent::mouse );
	F( WM_MOUSEHOVER, "WM_MOUSEHOVER", Wq::WqEvent::mouse );
	F( WM_MOUSELEAVE, "WM_MOUSELEAVE", Wq::WqEvent::mouse );
#endif /* _WIN32_WINNT >= 0x0400 */
	F( WM_SETFOCUS, "WM_SETFOCUS", Wq::WqEvent::focus );
	F( WM_KILLFOCUS, "WM_KILLFOCUS", Wq::WqEvent::focus );
	F( WM_ENABLE, "WM_ENABLE", Wq::WqEvent::focus );
	F( WM_CREATE, "WM_CREATE", Wq::WqEvent::window );
	F( WM_MOVE, "WM_MOVE", Wq::WqEvent::window );
	F( WM_ACTIVATE, "WM_ACTIVATE", Wq::WqEvent::window );
	F( WM_SETTEXT, "WM_SETTEXT", Wq::WqEvent::window );
	F( WM_PAINT, "WM_PAINT", Wq::WqEvent::window );
	F( WM_QUERYOPEN, "WM_QUERYOPEN", Wq::WqEvent::window );
	F( WM_ERASEBKGND, "WM_ERASEBKGND", Wq::WqEvent::window );
	F( WM_SYSCOLORCHANGE, "WM_SYSCOLORCHANGE", Wq::WqEvent::window );
	F( WM_SHOWWINDOW, "WM_SHOWWINDOW", Wq::WqEvent::window );
	F( WM_PAINTICON, "WM_PAINTICON", Wq::WqEvent::window );
	F( WM_ICONERASEBKGND, "WM_ICONERASEBKGND", Wq::WqEvent::window );
	F( WM_DRAWITEM, "WM_DRAWITEM", Wq::WqEvent::window );
#if( WINVER >= 0x0400 )
	F( WM_MOVING, "WM_MOVING", Wq::WqEvent::window );
#endif /* WINVER >= 0x0400 */
	F( WM_DESTROY, "WM_DESTROY", Wq::WqEvent::destroy );
	F( WM_CLOSE, "WM_CLOSE", Wq::WqEvent::destroy );
	F( WM_QUERYENDSESSION, "WM_QUERYENDSESSION", Wq::WqEvent::destroy );
	F( WM_QUIT, "WM_QUIT", Wq::WqEvent::destroy );
	F( WM_ENDSESSION, "WM_ENDSESSION", Wq::WqEvent::destroy );
	F( WM_SIZE, "WM_SIZE", Wq::WqEvent::resize );
	F( WM_GETMINMAXINFO, "WM_GETMINMAXINFO", Wq::WqEvent::resize );
#if( WINVER >= 0x0400 )
	F( WM_SIZING, "WM_SIZING", Wq::WqEvent::resize );
#endif /* WINVER >= 0x0400 */
	F( WM_CUT, "WM_CUT", Wq::WqEvent::selection );
	F( WM_COPY, "WM_COPY", Wq::WqEvent::selection );
	F( WM_PASTE, "WM_PASTE", Wq::WqEvent::selection );
	F( WM_CLEAR, "WM_CLEAR", Wq::WqEvent::selection );
	F( WM_RENDERFORMAT, "WM_RENDERFORMAT", Wq::WqEvent::selection );
	F( WM_RENDERALLFORMATS, "WM_RENDERALLFORMATS", Wq::WqEvent::selection );
	F( WM_DESTROYCLIPBOARD, "WM_DESTROYCLIPBOARD", Wq::WqEvent::selection );
	F( WM_DRAWCLIPBOARD, "WM_DRAWCLIPBOARD", Wq::WqEvent::selection );
	F( WM_PAINTCLIPBOARD, "WM_PAINTCLIPBOARD", Wq::WqEvent::selection );
	F( WM_VSCROLLCLIPBOARD, "WM_VSCROLLCLIPBOARD", Wq::WqEvent::selection );
	F( WM_SIZECLIPBOARD, "WM_SIZECLIPBOARD", Wq::WqEvent::selection );
	F( WM_ASKCBFORMATNAME, "WM_ASKCBFORMATNAME", Wq::WqEvent::selection );
	F( WM_CHANGECBCHAIN, "WM_CHANGECBCHAIN", Wq::WqEvent::selection );
	F( WM_HSCROLLCLIPBOARD, "WM_HSCROLLCLIPBOARD", Wq::WqEvent::selection );
	F( WM_NULL, "WM_NULL", Wq::WqEvent::other );
	F( WM_SETREDRAW, "WM_SETREDRAW", Wq::WqEvent::other );
	F( WM_GETTEXT, "WM_GETTEXT", Wq::WqEvent::other );
	F( WM_GETTEXTLENGTH, "WM_GETTEXTLENGTH", Wq::WqEvent::other );
#if( WINVER >= 0x0400 )
	F( WM_SETTINGCHANGE, "WM_SETTINGCHANGE", Wq::WqEvent::other );
#else
	F( WM_WININICHANGE, "WM_WININICHANGE", Wq::WqEvent::other );
#endif /* WINVER >= 0x0400 */
	F( WM_DEVMODECHANGE, "WM_DEVMODECHANGE", Wq::WqEvent::other );
	F( WM_ACTIVATEAPP, "WM_ACTIVATEAPP", Wq::WqEvent::other );
	F( WM_FONTCHANGE, "WM_FONTCHANGE", Wq::WqEvent::other );
	F( WM_TIMECHANGE, "WM_TIMECHANGE", Wq::WqEvent::other );
	F( WM_CANCELMODE, "WM_CANCELMODE", Wq::WqEvent::other );
	F( WM_CHILDACTIVATE, "WM_CHILDACTIVATE", Wq::WqEvent::other );
	F( WM_QUEUESYNC, "WM_QUEUESYNC", Wq::WqEvent::other );
	F( WM_NEXTDLGCTL, "WM_NEXTDLGCTL", Wq::WqEvent::other );
	F( WM_SPOOLERSTATUS, "WM_SPOOLERSTATUS", Wq::WqEvent::other );
	F( WM_MEASUREITEM, "WM_MEASUREITEM", Wq::WqEvent::other );
	F( WM_DELETEITEM, "WM_DELETEITEM", Wq::WqEvent::other );
	F( WM_SETFONT, "WM_SETFONT", Wq::WqEvent::other );
	F( WM_GETFONT, "WM_GETFONT", Wq::WqEvent::other );
	F( WM_SETHOTKEY, "WM_SETHOTKEY", Wq::WqEvent::other );
	F( WM_GETHOTKEY, "WM_GETHOTKEY", Wq::WqEvent::other );
	F( WM_QUERYDRAGICON, "WM_QUERYDRAGICON", Wq::WqEvent::other );
	F( WM_COMPAREITEM, "WM_COMPAREITEM", Wq::WqEvent::other );
	F( WM_COMPACTING, "WM_COMPACTING", Wq::WqEvent::other );
	F( WM_COMMNOTIFY, "WM_COMMNOTIFY", Wq::WqEvent::other );
	F( WM_WINDOWPOSCHANGING, "WM_WINDOWPOSCHANGING", Wq::WqEvent::other );
	F( WM_WINDOWPOSCHANGED, "WM_WINDOWPOSCHANGED", Wq::WqEvent::other );
	F( WM_POWER, "WM_POWER", Wq::WqEvent::other );
	F( WM_COPYDATA, "WM_COPYDATA", Wq::WqEvent::other );
	F( WM_CANCELJOURNAL, "WM_CANCELJOURNAL", Wq::WqEvent::other );
	  
#if( WINVER >= 0x0400 )
	F( WM_NOTIFY, "WM_NOTIFY", Wq::WqEvent::other );
	F( WM_INPUTLANGCHANGEREQUEST, "WM_INPUTLANGCHANGEREQUEST", Wq::WqEvent::other );
	F( WM_INPUTLANGCHANGE, "WM_INPUTLANGCHANGE", Wq::WqEvent::other );
	F( WM_TCARD, "WM_TCARD", Wq::WqEvent::other );
	F( WM_HELP, "WM_HELP", Wq::WqEvent::other );
	F( WM_USERCHANGED, "WM_USERCHANGED", Wq::WqEvent::other );
	F( WM_NOTIFYFORMAT, "WM_NOTIFYFORMAT", Wq::WqEvent::other );
	F( WM_CONTEXTMENU, "WM_CONTEXTMENU", Wq::WqEvent::other );
	F( WM_STYLECHANGING, "WM_STYLECHANGING", Wq::WqEvent::other );
	F( WM_STYLECHANGED, "WM_STYLECHANGED", Wq::WqEvent::other );
	F( WM_DISPLAYCHANGE, "WM_DISPLAYCHANGE", Wq::WqEvent::other );
	F( WM_GETICON, "WM_GETICON", Wq::WqEvent::other );
	F( WM_SETICON, "WM_SETICON", Wq::WqEvent::other );
#endif /* WINVER >= 0x0400 */
	  
	F( WM_NCCREATE, "WM_NCCREATE", Wq::WqEvent::other );
	F( WM_NCDESTROY, "WM_NCDESTROY", Wq::WqEvent::other );
	F( WM_NCCALCSIZE, "WM_NCCALCSIZE", Wq::WqEvent::other );
	F( WM_NCHITTEST, "WM_NCHITTEST", Wq::WqEvent::other );
	F( WM_NCPAINT, "WM_NCPAINT", Wq::WqEvent::other );
	F( WM_NCACTIVATE, "WM_NCACTIVATE", Wq::WqEvent::other );
	F( WM_GETDLGCODE, "WM_GETDLGCODE", Wq::WqEvent::other );
	  
	F( WM_NCMOUSEMOVE, "WM_NCMOUSEMOVE", Wq::WqEvent::other );
	F( WM_NCLBUTTONDOWN, "WM_NCLBUTTONDOWN", Wq::WqEvent::other );
	F( WM_NCLBUTTONUP, "WM_NCLBUTTONUP", Wq::WqEvent::other );
	F( WM_NCLBUTTONDBLCLK, "WM_NCLBUTTONDBLCLK", Wq::WqEvent::other );
	F( WM_NCRBUTTONDOWN, "WM_NCRBUTTONDOWN", Wq::WqEvent::other );
	F( WM_NCRBUTTONUP, "WM_NCRBUTTONUP", Wq::WqEvent::other );
	F( WM_NCRBUTTONDBLCLK, "WM_NCRBUTTONDBLCLK", Wq::WqEvent::other );
	F( WM_NCMBUTTONDOWN, "WM_NCMBUTTONDOWN", Wq::WqEvent::other );
	F( WM_NCMBUTTONUP, "WM_NCMBUTTONUP", Wq::WqEvent::other );
	F( WM_NCMBUTTONDBLCLK, "WM_NCMBUTTONDBLCLK", Wq::WqEvent::other );
	  
	F( WM_INITDIALOG, "WM_INITDIALOG", Wq::WqEvent::other );
	F( WM_COMMAND, "WM_COMMAND", Wq::WqEvent::other );
	F( WM_SYSCOMMAND, "WM_SYSCOMMAND", Wq::WqEvent::other );
	F( WM_TIMER, "WM_TIMER", Wq::WqEvent::other );
	F( WM_HSCROLL, "WM_HSCROLL", Wq::WqEvent::other );
	F( WM_VSCROLL, "WM_VSCROLL", Wq::WqEvent::other );
	F( WM_INITMENU, "WM_INITMENU", Wq::WqEvent::other );
	F( WM_INITMENUPOPUP, "WM_INITMENUPOPUP", Wq::WqEvent::other );
	F( WM_MENUSELECT, "WM_MENUSELECT", Wq::WqEvent::other );
	F( WM_ENTERIDLE, "WM_ENTERIDLE", Wq::WqEvent::other );
	  
	F( WM_CTLCOLORMSGBOX, "WM_CTLCOLORMSGBOX", Wq::WqEvent::other );
	F( WM_CTLCOLOREDIT, "WM_CTLCOLOREDIT", Wq::WqEvent::other );
	F( WM_CTLCOLORLISTBOX, "WM_CTLCOLORLISTBOX", Wq::WqEvent::other );
	F( WM_CTLCOLORBTN, "WM_CTLCOLORBTN", Wq::WqEvent::other );
	F( WM_CTLCOLORDLG, "WM_CTLCOLORDLG", Wq::WqEvent::other );
	F( WM_CTLCOLORSCROLLBAR, "WM_CTLCOLORSCROLLBAR", Wq::WqEvent::other );
	F( WM_CTLCOLORSTATIC, "WM_CTLCOLORSTATIC", Wq::WqEvent::other );
	  
	F( WM_PARENTNOTIFY, "WM_PARENTNOTIFY", Wq::WqEvent::other );
	F( WM_ENTERMENULOOP, "WM_ENTERMENULOOP", Wq::WqEvent::other );
	F( WM_EXITMENULOOP, "WM_EXITMENULOOP", Wq::WqEvent::other );
	  
#if(WINVER >= 0x0400)
	F( WM_NEXTMENU, "WM_NEXTMENU", Wq::WqEvent::other );
	F( WM_CAPTURECHANGED, "WM_CAPTURECHANGED", Wq::WqEvent::other );
	F( WM_POWERBROADCAST, "WM_POWERBROADCAST", Wq::WqEvent::other );
	F( WM_DEVICECHANGE, "WM_DEVICECHANGE", Wq::WqEvent::other );
#endif /* WINVER >= 0x0400 */
	  
	F( WM_MDICREATE, "WM_MDICREATE", Wq::WqEvent::other );
	F( WM_MDIDESTROY, "WM_MDIDESTROY", Wq::WqEvent::other );
	F( WM_MDIACTIVATE, "WM_MDIACTIVATE", Wq::WqEvent::other );
	F( WM_MDIRESTORE, "WM_MDIRESTORE", Wq::WqEvent::other );
	F( WM_MDINEXT, "WM_MDINEXT", Wq::WqEvent::other );
	F( WM_MDIMAXIMIZE, "WM_MDIMAXIMIZE", Wq::WqEvent::other );
	F( WM_MDITILE, "WM_MDITILE", Wq::WqEvent::other );
	F( WM_MDICASCADE, "WM_MDICASCADE", Wq::WqEvent::other );
	F( WM_MDIICONARRANGE, "WM_MDIICONARRANGE", Wq::WqEvent::other );
	F( WM_MDIGETACTIVE, "WM_MDIGETACTIVE", Wq::WqEvent::other );
	  
	F( WM_MDISETMENU, "WM_MDISETMENU", Wq::WqEvent::other );
	F( WM_ENTERSIZEMOVE, "WM_ENTERSIZEMOVE", Wq::WqEvent::other );
	F( WM_EXITSIZEMOVE, "WM_EXITSIZEMOVE", Wq::WqEvent::other );
	F( WM_DROPFILES, "WM_DROPFILES", Wq::WqEvent::other );
	F( WM_MDIREFRESHMENU, "WM_MDIREFRESHMENU", Wq::WqEvent::other );
	  
	F( WM_UNDO, "WM_UNDO", Wq::WqEvent::other );
	F( WM_QUERYNEWPALETTE, "WM_QUERYNEWPALETTE", Wq::WqEvent::other );
	F( WM_PALETTEISCHANGING, "WM_PALETTEISCHANGING", Wq::WqEvent::other );
	F( WM_PALETTECHANGED, "WM_PALETTECHANGED", Wq::WqEvent::other );
#if(WINVER >= 0x0400)
	F( WM_PRINT, "WM_PRINT", Wq::WqEvent::other );
	F( WM_PRINTCLIENT, "WM_PRINTCLIENT", Wq::WqEvent::other );
	  
	F( WM_HANDHELDFIRST, "WM_HANDHELDFIRST", Wq::WqEvent::other );
	F( WM_HANDHELDLAST, "WM_HANDHELDLAST", Wq::WqEvent::other );
	  
	F( WM_AFXFIRST, "WM_AFXFIRST", Wq::WqEvent::other );
	F( WM_AFXLAST, "WM_AFXLAST", Wq::WqEvent::other );
#endif /* WINVER >= 0x0400 */
	F( WM_PENWINFIRST, "WM_PENWINFIRST", Wq::WqEvent::other );
	F( WM_PENWINLAST, "WM_PENWINLAST", Wq::WqEvent::other );

#undef F
	}
  test_( types != NULL );
}

String Wq::WqEvent::getEventName( unsigned anId )
{
  initTypes();
  test_( types != NULL );

  if( ( 0 <= anId ) && ( anId <= WM_PENWINLAST ) )
	{
	  return types[ anId ].name;
	}
  else
	{
	  return "";
	}
}

String Wq::WqEvent::getClassName() const
{
  return "WqEvent";
}

Wq::WqEvent *Wq::WqEvent::create( MSG *anEvent )
{
  preC_( anEvent != NULL );

  Wq::WqEvent *result;

  if( ( 0 <= anEvent -> message ) && ( anEvent -> message <= WM_PENWINLAST ) )
	{
	  switch( types[ anEvent -> message ].type )
		{
		case Wq::WqEvent::key:
		  result = new Wq::KeyEvent( anEvent );
		  break;
		case Wq::WqEvent::button:
		  result = new Wq::ButtonEvent( anEvent );
		  break;
		case Wq::WqEvent::mouse:
		  result = new Wq::MouseMotionEvent( anEvent );
		  break;
		case Wq::WqEvent::focus:
		  result = new Wq::FocusEvent( anEvent );
		  break;
		case Wq::WqEvent::window:
		  result = new Wq::WindowEvent( anEvent );
		  break;
		case Wq::WqEvent::destroy:
		  result = new Wq::DestroyEvent( anEvent );
		  break;
		case Wq::WqEvent::resize:
		  result = new Wq::ResizeEvent( anEvent );
		  break;
		case Wq::WqEvent::selection:
		  result = new Wq::SelectionEvent( anEvent );
		  break;
		case Wq::WqEvent::other:
		  result = new Wq::WqEvent( anEvent );
		  break;
		default:
		  test( false, "Unknown or impossible message type" );
		}
	}
  else
	{
	  result = new Wq::WqEvent( anEvent );
	}
  test_( result != NULL );
  return result;
}

Wq::KeyEvent::KeyEvent( MSG *anEvent ) :
  WqEvent( anEvent )
{}

String Wq::KeyEvent::getClassName() const
{
  return "KeyEvent";
}

Wq::ButtonEvent::ButtonEvent( MSG *anEvent ) :
  WqEvent( anEvent )
{}

String Wq::ButtonEvent::getClassName() const
{
  return "ButtonEvent";
}

Wq::MouseMotionEvent::MouseMotionEvent( MSG *anEvent ) :
  WqEvent( anEvent )
{}

String Wq::MouseMotionEvent::getClassName() const
{
  return "MouseMotionEvent";
}

Wq::FocusEvent::FocusEvent( MSG *anEvent ) :
  WqEvent( anEvent )
{}

String Wq::FocusEvent::getClassName() const
{
  return "FocusEvent";
}

Wq::WindowEvent::WindowEvent( MSG *anEvent ) :
  WqEvent( anEvent )
{}

String Wq::WindowEvent::getClassName() const
{
  return "WindowEvent";
}

Wq::DestroyEvent::DestroyEvent( MSG *anEvent ) :
  WqEvent( anEvent )
{}

String Wq::DestroyEvent::getClassName() const
{
  return "DestroyEvent";
}

Wq::ResizeEvent::ResizeEvent( MSG *anEvent ) :
  WqEvent( anEvent )
{}

String Wq::ResizeEvent::getClassName() const
{
  return "ResizeEvent";
}

Wq::SelectionEvent::SelectionEvent( MSG *anEvent ) :
  WqEvent( anEvent )
{}

String Wq::SelectionEvent::getClassName() const
{
  return "SelectionEvent";
}

END_QR_NAMESPACE

#if defined(_INLINE)
#include "../src/Debug.ipp"
#endif

/* USE_WQ */
#endif

/* $Log: WqEvent.cpp,v $
/* Revision 1.1.1.1  2000/07/19 16:53:55  philogelos
/* stored sources into sourceforge.net CVS
/*
/* Revision 1.1.1.1  2000/04/01 14:07:36  god
/* Imported sources
/* */
