// -*-C++-*- 

/*  src/ui/xq/XException.cpp  */

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



/* $Id: XException.cpp,v 1.1.1.1 2000/07/19 16:54:40 philogelos Exp $ */
#if !defined(_INLINE)
static char cvsid[] = "@(#)$Id: XException.cpp,v 1.1.1.1 2000/07/19 16:54:40 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif

#include "ui/xq/XqCommon.hpp"
#include "Debug.hpp"

#if defined( USE_XQ )

BEGIN_QR_NAMESPACE

Xq::XException::XException( struct _XDisplay *aDisplay, 
							XErrorEvent *anEvent ) :
  OSError( "Error in X protocol", null ),
  Exception( "Error in X protocol", null )
{
  preC_( anEvent != ( XErrorEvent * ) NULL );
  event.type = anEvent -> type;
  event.display = anEvent -> display;
  event.serial = anEvent -> serial;
  event.error_code = anEvent -> error_code;
  event.request_code = anEvent -> request_code;
  event.minor_code = anEvent -> minor_code;
  event.resourceid = anEvent -> resourceid;

  test_( event.display == aDisplay );
  fromEvent = true;
}

Xq::XException::XException( String aMessage ) :
  OSError( aMessage, null ),
  Exception( aMessage, null )
{
  fromEvent = false;
}

Xq::XException::~XException()
{}

String  Xq::XException::getClassName() const
{
  return "XException";
}

String  Xq::XException::getDescription() const
{
  if( fromEvent )
	{
	  String requestName;
	  char errorTextBuffer[ 1024 ]; /* XXX param */

	  requestName = "Unknown request";
	  for( int i = 0 ; requestNameMap[ i ].xRequestId != -1 ; ++i )
		{
		  if( requestNameMap[ i ].xRequestId == event.request_code )
			{
			  requestName = requestNameMap[ i ].xRequestName;
			  break;
			}
		}
	  requestName = String( "%s (%i)" ).sprintf
		( 1, requestName.getChars(), event.request_code );

	  /* XXX x11Serializer _must_ be recursive: 
		 this can be called from within Xlib! */
	  // LOCK_X11_DISPLAY();
	  ::XGetErrorText
		( event.display, 
		  event.error_code, errorTextBuffer, 
		  ( sizeof errorTextBuffer ) / ( sizeof errorTextBuffer[ 0 ] ) );
	  return OSError::getDescription() + 
		String( " :\n XError: serial: " ) + String( event.serial, 10 ) +
		String( " error code: " ) + String( event.error_code ) +
		String( " error text: " ) + String( errorTextBuffer ) +
		String( " request: " ) + requestName +
		String( " minor code: " ) + String( event.minor_code, 10 ) +
		String( " resource: " ) + String( event.resourceid, 0x10 );
	}
  else
	{
	  return OSError::getDescription() + 
		" :\nError in call to Xlib";
	}
}

Xq::XException::MapEntry Xq::XException::requestNameMap[] = 
{
  /* generated from X11/Xproto.h */
  { X_CreateWindow,			"X_CreateWindow" },
  { X_ChangeWindowAttributes,			"X_ChangeWindowAttributes" },
  { X_GetWindowAttributes,			"X_GetWindowAttributes" },
  { X_DestroyWindow,			"X_DestroyWindow" },
  { X_DestroySubwindows,			"X_DestroySubwindows" },
  { X_ChangeSaveSet,			"X_ChangeSaveSet" },
  { X_ReparentWindow,			"X_ReparentWindow" },
  { X_MapWindow,			"X_MapWindow" },
  { X_MapSubwindows,			"X_MapSubwindows" },
  { X_UnmapWindow,			"X_UnmapWindow" },
  { X_UnmapSubwindows,			"X_UnmapSubwindows" },
  { X_ConfigureWindow,			"X_ConfigureWindow" },
  { X_CirculateWindow,			"X_CirculateWindow" },
  { X_GetGeometry,			"X_GetGeometry" },
  { X_QueryTree,			"X_QueryTree" },
  { X_InternAtom,			"X_InternAtom" },
  { X_GetAtomName,			"X_GetAtomName" },
  { X_ChangeProperty,			"X_ChangeProperty" },
  { X_DeleteProperty,			"X_DeleteProperty" },
  { X_GetProperty,			"X_GetProperty" },
  { X_ListProperties,			"X_ListProperties" },
  { X_SetSelectionOwner,			"X_SetSelectionOwner" },
  { X_GetSelectionOwner,			"X_GetSelectionOwner" },
  { X_ConvertSelection,			"X_ConvertSelection" },
  { X_SendEvent,			"X_SendEvent" },
  { X_GrabPointer,			"X_GrabPointer" },
  { X_UngrabPointer,			"X_UngrabPointer" },
  { X_GrabButton,			"X_GrabButton" },
  { X_UngrabButton,			"X_UngrabButton" },
  { X_ChangeActivePointerGrab,			"X_ChangeActivePointerGrab" },
  { X_GrabKeyboard,			"X_GrabKeyboard" },
  { X_UngrabKeyboard,			"X_UngrabKeyboard" },
  { X_GrabKey,			"X_GrabKey" },
  { X_UngrabKey,			"X_UngrabKey" },
  { X_AllowEvents,			"X_AllowEvents" },
  { X_GrabServer,			"X_GrabServer" },
  { X_UngrabServer,			"X_UngrabServer" },
  { X_QueryPointer,			"X_QueryPointer" },
  { X_GetMotionEvents,			"X_GetMotionEvents" },
  { X_TranslateCoords,			"X_TranslateCoords" },
  { X_WarpPointer,			"X_WarpPointer" },
  { X_SetInputFocus,			"X_SetInputFocus" },
  { X_GetInputFocus,			"X_GetInputFocus" },
  { X_QueryKeymap,			"X_QueryKeymap" },
  { X_OpenFont,			"X_OpenFont" },
  { X_CloseFont,			"X_CloseFont" },
  { X_QueryFont,			"X_QueryFont" },
  { X_QueryTextExtents,			"X_QueryTextExtents" },
  { X_ListFonts,			"X_ListFonts" },
  { X_ListFontsWithInfo,			"X_ListFontsWithInfo" },
  { X_SetFontPath,			"X_SetFontPath" },
  { X_GetFontPath,			"X_GetFontPath" },
  { X_CreatePixmap,			"X_CreatePixmap" },
  { X_FreePixmap,			"X_FreePixmap" },
  { X_CreateGC,			"X_CreateGC" },
  { X_ChangeGC,			"X_ChangeGC" },
  { X_CopyGC,			"X_CopyGC" },
  { X_SetDashes,			"X_SetDashes" },
  { X_SetClipRectangles,			"X_SetClipRectangles" },
  { X_FreeGC,			"X_FreeGC" },
  { X_ClearArea,			"X_ClearArea" },
  { X_CopyArea,			"X_CopyArea" },
  { X_CopyPlane,			"X_CopyPlane" },
  { X_PolyPoint,			"X_PolyPoint" },
  { X_PolyLine,			"X_PolyLine" },
  { X_PolySegment,			"X_PolySegment" },
  { X_PolyRectangle,			"X_PolyRectangle" },
  { X_PolyArc,			"X_PolyArc" },
  { X_FillPoly,			"X_FillPoly" },
  { X_PolyFillRectangle,			"X_PolyFillRectangle" },
  { X_PolyFillArc,			"X_PolyFillArc" },
  { X_PutImage,			"X_PutImage" },
  { X_GetImage,			"X_GetImage" },
  { X_PolyText8,			"X_PolyText8" },
  { X_PolyText16,			"X_PolyText16" },
  { X_ImageText8,			"X_ImageText8" },
  { X_ImageText16,			"X_ImageText16" },
  { X_CreateColormap,			"X_CreateColormap" },
  { X_FreeColormap,			"X_FreeColormap" },
  { X_CopyColormapAndFree,			"X_CopyColormapAndFree" },
  { X_InstallColormap,			"X_InstallColormap" },
  { X_UninstallColormap,			"X_UninstallColormap" },
  { X_ListInstalledColormaps,			"X_ListInstalledColormaps" },
  { X_AllocColor,			"X_AllocColor" },
  { X_AllocNamedColor,			"X_AllocNamedColor" },
  { X_AllocColorCells,			"X_AllocColorCells" },
  { X_AllocColorPlanes,			"X_AllocColorPlanes" },
  { X_FreeColors,			"X_FreeColors" },
  { X_StoreColors,			"X_StoreColors" },
  { X_StoreNamedColor,			"X_StoreNamedColor" },
  { X_QueryColors,			"X_QueryColors" },
  { X_LookupColor,			"X_LookupColor" },
  { X_CreateCursor,			"X_CreateCursor" },
  { X_CreateGlyphCursor,			"X_CreateGlyphCursor" },
  { X_FreeCursor,			"X_FreeCursor" },
  { X_RecolorCursor,			"X_RecolorCursor" },
  { X_QueryBestSize,			"X_QueryBestSize" },
  { X_QueryExtension,			"X_QueryExtension" },
  { X_ListExtensions,			"X_ListExtensions" },
  { X_ChangeKeyboardMapping,			"X_ChangeKeyboardMapping" },
  { X_GetKeyboardMapping,			"X_GetKeyboardMapping" },
  { X_ChangeKeyboardControl,			"X_ChangeKeyboardControl" },
  { X_GetKeyboardControl,			"X_GetKeyboardControl" },
  { X_Bell,			"X_Bell" },
  { X_ChangePointerControl,			"X_ChangePointerControl" },
  { X_GetPointerControl,			"X_GetPointerControl" },
  { X_SetScreenSaver,			"X_SetScreenSaver" },
  { X_GetScreenSaver,			"X_GetScreenSaver" },
  { X_ChangeHosts,			"X_ChangeHosts" },
  { X_ListHosts,			"X_ListHosts" },
  { X_SetAccessControl,			"X_SetAccessControl" },
  { X_SetCloseDownMode,			"X_SetCloseDownMode" },
  { X_KillClient,			"X_KillClient" },
  { X_RotateProperties,			"X_RotateProperties" },
  { X_ForceScreenSaver,			"X_ForceScreenSaver" },
  { X_SetPointerMapping,			"X_SetPointerMapping" },
  { X_GetPointerMapping,			"X_GetPointerMapping" },
  { X_SetModifierMapping,			"X_SetModifierMapping" },
  { X_GetModifierMapping,			"X_GetModifierMapping" },
  { X_NoOperation,			"X_NoOperation" },
  { -1, "" }
};

END_QR_NAMESPACE

#if defined(_INLINE)
#include "../src/Debug.ipp"
#endif

/* USE_XQ */
#endif

/*
 * $Log: XException.cpp,v $
 * Revision 1.1.1.1  2000/07/19 16:54:40  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:45  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:36  god
 * Imported sources
*/
