// -*-C++-*- 

/*  inc/Protector.hpp  */


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


#ifndef __PROTECTOR_HPP__
#define __PROTECTOR_HPP__

/* $Id: Protector.hpp,v 1.1.1.1 2000/07/19 16:57:18 philogelos Exp $ */

#include "Top.hpp"
#include "defines.h"

BEGIN_QR_NAMESPACE



/**
   Protectors are objects through which
   serialisation protocols are implemented.

   @author Philogelos
   @created Чтв 10 Сен 1998 20:27:16
*/
interface Protector : public virtual Top
{
 public: virtual void enter( const Top *aSubject = null ) = 0;
 public: virtual void leave( const Top *aSubject = null ) = 0;

 public: virtual void enterRead( const Top *aSubject = null );
 public: virtual void enterWrite( const Top *aSubject = null );
};

END_QR_NAMESPACE

/*
 * $Log: Protector.hpp,v $
 * Revision 1.1.1.1  2000/07/19 16:57:18  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.4  2000/04/29 14:57:20  god
 * signatures changed to avoid hiding of Protector member functions
 *
 * Revision 1.3  2000/04/29 14:15:15  god
 * enterRead/Write added
 *
 * Revision 1.2  2000/04/09 11:29:17  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:38  god
 * Imported sources
 *
 * Revision 1.2  1999/03/03 19:09:04  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.1.1.1  1998/11/25 20:11:05  philogelos
 * Quercus Robusta
 * */

/* __PROTECTOR_HPP__ */
#endif
