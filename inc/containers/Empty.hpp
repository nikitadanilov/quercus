// -*- C++ -*-

/*  inc/containers/Empty.hpp  */


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



#ifndef __EMPTY_HPP__
#define __EMPTY_HPP__

/* $Id: Empty.hpp,v 1.1.1.1 2000/07/19 16:59:21 philogelos Exp $ */

#include "Object.hpp"
#include "Container.hpp"
#include "EnumeratedValues.hpp"

BEGIN_QR_NAMESPACE



/**
   Container containing no elements.

   @author Philogelos
   @created ø›‘ 22 ∏Ó› 1998 21:44:59
*/
class Empty : public EnumeratedValues
{
public: Empty();

public:    virtual String getClassName() const;

#if defined( TESTING )
public:  virtual boolean tester( int aParam ) const;
#endif
};

END_QR_NAMESPACE

/*
 * $Log: Empty.hpp,v $
 * Revision 1.1.1.1  2000/07/19 16:59:21  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:33  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:44  god
 * Imported sources
 *
 * Revision 1.3  1999/03/03 19:09:08  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.2  1998/12/01 16:16:25  philogelos
 * conditionally compile ::tester()
 *
 * Revision 1.1.1.1  1998/11/25 20:11:05  philogelos
 * Quercus Robusta
 *
 * Revision 1.1  1998/07/09 09:30:27  philogelos
 * new files added to the repository
 * */

/* __EMPTY_HPP__ */
#endif
