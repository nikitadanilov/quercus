// -*- C++ -*-

/*  inc/iter/iterables/PrettyPrintIterable.hpp  */


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



#ifndef __PRETTYPRINTITERABLE_HPP__
#define __PRETTYPRINTITERABLE_HPP__

/* $Id: PrettyPrintIterable.hpp,v 1.1.1.1 2000/07/19 17:02:32 philogelos Exp $ */

#include "iter/iterables/IterativeBuilder.hpp"
#include "StringBuffer.hpp"
#include "String.hpp"

BEGIN_QR_NAMESPACE



/**
   Prints objects according to simple
   formatting rules.

   @see Iterable
   @author Philogelos
   @created ø‚› 19 ∏Ó› 1998 20:21:17
*/
class PrettyPrintIterable : public IterativeBuilder
{
public: PrettyPrintIterable( String aHeader,
							 String aPadder,
							 String aFooter,
#if defined( WIN32 )
							 String anEllipsis,
							 Index aMaxCount,
							 String (Top::*aMethod)()const );
#else
							 String anEllipsis = " ... ",
							 Index aMaxCount = -1,
							 String ( Top::*aMethod )() const = 
							 &Top::getString );
#endif

public: virtual void initIterations();

public: virtual void fireOn( Top *anElement );
public: virtual boolean isMore();
public: virtual void doneIterations();

public: Object *getResult();

#if defined( TESTING )
public:  virtual boolean tester( int aParam ) const;
#endif

protected: const String header;
protected: const String padder;
protected: const String footer;
protected: const String ellipsis;
protected: String ( Top::*method )() const;

protected: String result;
protected: boolean firstShot;
protected: StringBuffer buffer;
protected: Index count;
protected: Index maxCount;
};

END_QR_NAMESPACE

/*
 * $Log: PrettyPrintIterable.hpp,v $
 * Revision 1.1.1.1  2000/07/19 17:02:32  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:36  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:40  god
 * Imported sources
 *
 * Revision 1.3  1999/03/03 19:09:21  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.2  1998/12/01 16:18:08  philogelos
 * conditionally compile ::tester()
 *
 * Revision 1.1.1.1  1998/11/25 20:11:07  philogelos
 * Quercus Robusta
 *
 * Revision 1.3  1998/07/07 14:29:56  philogelos
 * Memory leak in SUNWspro dynamic_cast fixed.
 *
 * Revision 1.2  1998/06/22 13:33:40  philogelos
 * Method to call on each object added
 *
 * Revision 1.1.1.1  1998/06/22 08:47:12  philogelos
 * First version under CVS
 *
 * Revision 1.1.1.1  1998/04/01 17:15:30  philogelos
 * first version under CVS
 * */

/* __PRETTYPRINTITERABLE_HPP__ */
#endif
