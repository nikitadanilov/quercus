//-*-C++-*-

/*  src/MemoryMonitor.ipp  */


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

/* $Id: MemoryMonitor.ipp,v 1.1.1.1 2000/07/19 16:41:07 philogelos Exp $ */

#if !defined(__MEMORYMONITOR_IPP__)
#define __MEMORYMONITOR_IPP__

#include "MemoryMonitor.hpp"
#include "defines.h"
#include "new-operator.hpp"
#include "Debug.hpp"

BEGIN_QR_NAMESPACE

INLINE int MemoryMonitor::init()
{
  if( !wasInitialised )
	{
	  statBufferSize = 8192;
	  hogSize = 8192;

	  if( hogSize != 0 )
		{
		  memoryHog = new char[ hogSize ];
		}
	  if( statBufferSize != 0 )
		{
		  statBuffer = new StatRecord[ statBufferSize + 1 ];
		}
	  wasInitialised = true;
	}
  return 0;
}

INLINE void MemoryMonitor::release()
{
  if( memoryHog != NIL )
	{
	  delete []memoryHog;
	  memoryHog = NIL;
	}
}

INLINE void MemoryMonitor::inc( Index anAmount, void * /* anAddress */ )
{ 
  allocated += anAmount;
  if( anAmount > maxArea )
	{
	  maxArea = anAmount;
	}
  if( wasInitialised && ( anAmount <= statBufferSize ) )
	{
	  Index totalTimes;

	  totalTimes = ++( statBuffer[ anAmount ].total );
	  ++( statBuffer[ anAmount ].actual );
	  statBuffer[ anAmount ].average = 
		( statBuffer[ anAmount ].average * ( totalTimes - 1 ) + statBuffer[ anAmount ].actual ) / totalTimes;
	  if( statBuffer[ anAmount ].actual > statBuffer[ anAmount ].max )
		{
		  statBuffer[ anAmount ].max = statBuffer[ anAmount ].actual;
		}
	}
}

INLINE void MemoryMonitor::dec( Index anAmount, void * /* anAddress */ )
{
  allocated -= anAmount;
  testF_( amount >= 0 );
  if( wasInitialised && ( anAmount <= statBufferSize ) )
	{
	  Index totalTimes;

	  totalTimes = ++( statBuffer[ anAmount ].total );
	  --( statBuffer[ anAmount ].actual );
	  statBuffer[ anAmount ].average = 
		( statBuffer[ anAmount ].average * ( totalTimes - 1 ) + 
		  statBuffer[ anAmount ].actual ) / totalTimes;
	}
}

INLINE Index MemoryMonitor::amount()
{
  return allocated;
}

INLINE boolean MemoryMonitor::checkDelete( const void *aPointer )
{
  return checkForDelete( aPointer );
}

INLINE void MemoryMonitor::dumpStatistics()
{
  DLOG( "Maximum area allocated: %li bytes", maxArea );
  if( wasInitialised )
	{
	  for( Index i = 0 ; i <= statBufferSize ; ++i )
		{
		  if( statBuffer[ i ].total != 0 )
			{
			  Debug::getLogger() -> 
				log( "%li: total: %li, actual: %li, average: %f, max: %li", 
					 i, 
					 statBuffer[ i ].total,
					 statBuffer[ i ].actual,
					 statBuffer[ i ].average,
					 statBuffer[ i ].max );
			}
		}
	}
}

END_QR_NAMESPACE

/* __MEMORYMONITOR_IPP__ */
#endif

/*
 * $Log: MemoryMonitor.ipp,v $
 * Revision 1.1.1.1  2000/07/19 16:41:07  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:39  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:28  god
 * Imported sources
 *
 * Revision 1.3  1999/05/22 13:00:30  philogelos
 * Merging sources back from SPARC
 *
 * Revision 1.2  1999/03/03 19:09:27  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.1  1999/02/28 15:50:19  philogelos
 * Code moved here from .cpp
 * */
