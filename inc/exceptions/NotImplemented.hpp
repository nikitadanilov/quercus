// -*-C++-*-

/*  inc/exceptions/NotImplemented.hpp  */


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


#ifndef __NOTIMPLEMENTED_HPP__
#define __NOTIMPLEMENTED_HPP__

/* $Id: NotImplemented.hpp,v 1.1.1.1 2000/07/19 17:01:32 philogelos Exp $ */

#include "String.hpp"
#include "InternalError.hpp"

BEGIN_QR_NAMESPACE



/** 
	Signaling about unimplemented features.

	@author Philogelos
	@created «‚“ 18 ∏Ó› 1998 21:23:16
*/
class NotImplemented : public InternalError
{
public:  NotImplemented(String aMessage, const Top *const aSource );
public:  virtual String getDescription() const;
};

END_QR_NAMESPACE

/*
 * $Log: NotImplemented.hpp,v $
 * Revision 1.1.1.1  2000/07/19 17:01:32  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:35  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:46  god
 * Imported sources
 *
 * Revision 1.3  1999/05/22 13:00:26  philogelos
 * Merging sources back from SPARC
 *
 * Revision 1.2  1999/03/03 19:09:17  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.1.1.1  1998/11/25 20:11:06  philogelos
 * Quercus Robusta
 *
 * Revision 1.2  1998/07/07 14:29:54  philogelos
 * Memory leak in SUNWspro dynamic_cast fixed.
 *
 * Revision 1.1.1.1  1998/06/22 08:47:11  philogelos
 * First version under CVS
 *
 * Revision 1.1.1.1  1998/04/01 17:15:30  philogelos
 * first version under CVS
 * */

/* __NOTIMPLEMENTED_HPP__ */
#endif
