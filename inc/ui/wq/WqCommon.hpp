// -*-C++-*- 

/*  inc/ui/wq/WqCommon.hpp  */

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



#ifndef __WQCOMMON_HPP__
#define __WQCOMMON_HPP__

/* $Id: WqCommon.hpp,v 1.1.1.1 2000/07/19 17:15:04 philogelos Exp $ */

#include "Wq.hpp"

#if defined( USE_WQ )

#include "Debug.hpp"
#include "exceptions/Errno.hpp"
#include "PGuard.hpp"
#include "OGuard.hpp"
#include "platform/threads/MGuard.hpp"
#include "containers/lists/List.hpp"
#include "containers/Pair.hpp"
#include "DataWrapper.hpp"

#if defined( __BORLANDC__ )
#define THROW_IN_PROGRESS   ( false )
#define VIRTUAL_BASE( PARENT_CLASS, BASE_CLASS )  PARENT_CLASS :: BASE_CLASS
#else
#define THROW_IN_PROGRESS   ( std::uncaught_exception() )
#define VIRTUAL_BASE( PARENT_CLASS, BASE_CLASS )  BASE_CLASS
#endif

#define GUI_WRAP( call, testValue, methodName ) do \
	if( ( ( call ) == testValue ) && \
		( GetLastError() != ERROR_SUCCESS ) && \
		!THROW_IN_PROGRESS ) \
	{ \
		throw new Errno( #call " failed in " #methodName " (" __FILE__ ")", null, GetLastError() ); \
	} while( false )

#define CREATE_OBJECT( className, call, methodName ) \
	HANDLE handle; \
	GUI_WRAP( ( handle = ( call ) ), NULL, methodName ); \
	return new className( handle );


BEGIN_QR_NAMESPACE

extern Mutex *winCreateLock;
extern Semaphore *winCreateSema;
extern Wq::Window *freshWindow;

END_QR_NAMESPACE

/* USE_WQ */
#endif

/*
 * $Log: WqCommon.hpp,v $
 * Revision 1.1.1.1  2000/07/19 17:15:04  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:37  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:41  god
 * Imported sources
*/

/* __WQCOMMON_HPP__ */
#endif
