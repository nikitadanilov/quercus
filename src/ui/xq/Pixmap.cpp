// -*-C++-*- 

/*  src/ui/xq/Pixmap.cpp  */

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



/* $Id: Pixmap.cpp,v 1.1.1.1 2000/07/19 16:54:35 philogelos Exp $ */
#if !defined(_INLINE)
static char cvsid[] = "@(#)$Id: Pixmap.cpp,v 1.1.1.1 2000/07/19 16:54:35 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif

#include "ui/xq/XqCommon.hpp"
#include "Debug.hpp"

#if defined( USE_XQ )

BEGIN_QR_NAMESPACE

Xq::Pixmap::Pixmap( Display *aDisplay, XID anId, 
					int aWidth, int aHeight, 
					int aXHot, int aYHot ) :
  Xq::Drawable( aDisplay, anId ),
  Xq::XIDObject( aDisplay, anId ),
  Xq::XqObject( aDisplay )
{
  preC_( aWidth >= 0 );
  preC_( aHeight >= 0 );

  width = aWidth;
  height = aHeight;
  xHot = aXHot;
  yHot = aYHot;
}

Xq::Pixmap::~Pixmap()
{
  LOCK_X11;
  ::XFreePixmap( getDisplay() -> getData(), getId() );
}

Xq::Coord Xq::Pixmap::getWidth() const
{
  return width;
}

Xq::Coord Xq::Pixmap::getHeight() const
{
  return height;
}

int Xq::Pixmap::getXHot() const
{
  return xHot;
}

int Xq::Pixmap::getYHot() const
{
  return yHot;
}

Xq::Pixmap *Xq::Pixmap::create( Xq::Drawable *aDrawable, 
							int aWidth, 
							int aHeight, 
							int aDepth )
{
  preC_( aDrawable != ( Xq::Drawable * ) NULL );
  preC_( aWidth >= 0 );
  preC_( aHeight >= 0 );
  preC_( aDepth >= 0 );

  XID id_;

  LOCK_X11_DISPLAY( aDrawable -> getDisplay() );
  id_ = ::XCreatePixmap( aDrawable -> getDisplay() -> getData(), 
						 aDrawable -> getId(), 
						 ( unsigned ) aWidth, ( unsigned ) aHeight, aDepth );
  return new Xq::Pixmap( aDrawable -> getDisplay(), id_,
						 aWidth, aHeight, 0, 0 );
}

Xq::Pixmap *Xq::Pixmap::create( Xq::Drawable *aDrawable, 
								String aFileName )
{
  preC_( aDrawable != ( Xq::Drawable * ) NULL );

  XID id_;
  char *fileName;
  unsigned width_;
  unsigned height_;
  int xHot_;
  int yHot_;

  fileName = aFileName.getChars();
  LOCK_X11_DISPLAY( aDrawable -> getDisplay() );
  ::XReadBitmapFile( aDrawable -> getDisplay() -> getData(), 
					 aDrawable -> getId(), fileName,
					 &width_, &height_, &id_, &xHot_, &yHot_ );
  delete []fileName;
  return new Xq::Pixmap( aDrawable -> getDisplay(), id_,
						 width_, height_, xHot_, yHot_ );
}

#if defined( USE_XPM )
Xq::Pixmap *Xq::Pixmap::createFromXPM( Xq::Drawable *aDrawable, 
									   String aFileName,
									   Xq::Pixmap **aMask )
{
  preC_( aDrawable != NULL );

  XID id_;
  XID shapeId;
  XpmAttributes attrib;
  char *fileName;
  int returnCode;
		
  attrib.visual = aDrawable -> getDisplay() -> defaultVisual
	( aDrawable -> getDisplay() -> screen() );
  attrib.colormap = aDrawable -> getDisplay() -> defaultColormap();
  attrib.depth = aDrawable -> getDisplay() -> defaultDepth();
  //  attrib.closeness = 65000;
  //  attrib.exactColors = 0;

  attrib.valuemask = XpmVisual | XpmColormap | XpmDepth 
	/* | XpmCloseness | XpmExactColors */;
  fileName = aFileName.getChars();

  LOCK_X11_DISPLAY( aDrawable -> getDisplay() );

  returnCode = ::XpmReadFileToPixmap
	( aDrawable -> getDisplay() -> getData(),
	  aDrawable -> getId(),
	  fileName, &id_, &shapeId, &attrib );
  handleXPMError( returnCode, "Xq::Pixmap::createFromXPM()" );

  delete []fileName;
  test_( attrib.valuemask & XpmSize );
  if( aMask != NULL )
	{
	  if( shapeId != None )
		{
		  *aMask = new Xq::Pixmap( aDrawable -> getDisplay(), shapeId, 
								   attrib.width, attrib.height,
								   attrib.x_hotspot, attrib.y_hotspot );
		}
	  else
		{
		  *aMask = NULL;
		}
	}
  return new Xq::Pixmap( aDrawable -> getDisplay(), id_, 
						 attrib.width, attrib.height,
						 attrib.x_hotspot, attrib.y_hotspot );
}

void Xq::Pixmap::writeToXPMFile( String aFileName )
{
  char *fileName;

  fileName = aFileName.getChars();
  LOCK_X11;
  handleXPMError
	( ::XpmWriteFileFromPixmap( getDisplay() -> getData(),
								fileName,
								getId(),
								None,
								NULL ),
	  "Xq::Pixmap::writeToXPMFile()" );
  delete []fileName;
}

void Xq::Pixmap::handleXPMError( int aCode, String aMessage )
{
  if( aCode != XpmSuccess )
	{
	  const char *errorMsg;

	  switch( aCode )
		{
		case XpmColorError:
		  errorMsg = "XpmColorError";
		  break;
		case XpmOpenFailed:
		  errorMsg = "XpmOpenFailed";
		  break;
		case XpmFileInvalid:
		  errorMsg = "XpmFileInvalid";
		  break;
		case XpmNoMemory:
		  errorMsg = "XpmNoMemory";
		  break;
		case XpmColorFailed:
		  errorMsg = "XpmColorFailed";
		  break;
		default:
		  errorMsg = "Xpm Unknown error";
		  break;
		}
	  throw new XException( aMessage + errorMsg );
	}
}

#endif

Xq::Pixmap *Xq::Pixmap::create( Xq::Drawable *aDrawable, 
								char *aData,
								int aWidth, int aHeight )
{
  preC_( aDrawable != ( Xq::Drawable * ) NULL );
  preC_( aData != NULL );
  preC_( aWidth >= 0 );
  preC_( aHeight >= 0 );

  XID id_;

  LOCK_X11_DISPLAY( aDrawable -> getDisplay() );
  id_ = ::XCreateBitmapFromData
	( aDrawable -> getDisplay() -> getData(), aDrawable -> getId(),
 	  aData,
	  aWidth, aHeight );
  return new Xq::Pixmap( aDrawable -> getDisplay(), id_,
						 aWidth, aHeight, 0, 0 );
}

void Xq::Pixmap::writeToXBMFile( String aFileName )
{
  char *fileName;

  fileName = aFileName.getChars();
  LOCK_X11;
  ::XWriteBitmapFile( getDisplay() -> getData(),
					  fileName, getId(), getWidth(), getHeight(), 
					  getXHot(), getYHot() );
  delete []fileName;
}


END_QR_NAMESPACE

#if defined(_INLINE)
#include "../src/Debug.ipp"
#endif

/* USE_XQ */
#endif

/*
 * $Log: Pixmap.cpp,v $
 * Revision 1.1.1.1  2000/07/19 16:54:35  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:44  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:35  god
 * Imported sources
*/
