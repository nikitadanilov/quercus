// -*-C++-*- 

/*  src/exceptions/OSError.cpp  */


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


/* $Id: OSError.cpp,v 1.1.1.1 2000/07/19 16:49:15 philogelos Exp $ */
#if !defined(_INLINE)
static char cvsid[] = "@(#)$Id: OSError.cpp,v 1.1.1.1 2000/07/19 16:49:15 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif


#include "exceptions/OSError.hpp"
#include "Debug.hpp"

BEGIN_QR_NAMESPACE

OSError::OSError( String aMessage, const Top *const aSource ) :
  ExternalError( aMessage, aSource ),
  Exception( aMessage, aSource )
{}

String  OSError::getClassName() const
{
  return "OSError";
}

String OSError::getDescription() const
{
  return ExternalError::getDescription() + 
	" :\n error in interface to the underlying OS";
}

END_QR_NAMESPACE

#if defined(_INLINE)
#include "../src/Debug.ipp"
#endif

/*
 * $Log: OSError.cpp,v $
 * Revision 1.1.1.1  2000/07/19 16:49:15  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:42  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:33  god
 * Imported sources
 *
 * Revision 1.3  1999/03/03 19:09:43  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.2  1999/02/28 16:30:46  philogelos
 * Tuned for inlines.
 *
 * Revision 1.1.1.1  1998/11/25 20:11:03  philogelos
 * Quercus Robusta
 *
 * Revision 1.1  1998/07/09 09:30:44  philogelos
 * new files added to the repository
 * */
