
/*  src/test.cpp  */


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

#if !defined(_INLINE)
static char cvsid[] = "@(#)$Id: test.cpp,v 1.5 2000/10/20 20:29:20 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif

#include "OGuard.hpp"
#include "Debug.hpp"
#include "String.hpp"
#include "Integer.hpp"
#include "StringEnumeration.hpp"
#include "iter/enumerations/Enumeration.hpp"
#include "iter/iterators/Iterator.hpp"
#include "iter/iterators/EnumerationIterator.hpp"
#include "iter/iterables/EchoIterable.hpp"
#include "iter/iterables/PrettyPrintIterable.hpp"
#include "containers/Queue.hpp"
#include "containers/Stack.hpp"
#include "containers/Pair.hpp"
#include "containers/Empty.hpp"
#include "containers/arrays/CArray.hpp"
#include "containers/Singleton.hpp"
#include "containers/MutablePositionEnumeration.hpp"
#include "containers/MutablePosition.hpp"
#include "containers/lists/List.hpp"
#include "containers/dicts/DumbDictionary.hpp"
#include "algorithms/enumerations/EnumerationAlgorithms.hpp"
#include "algorithms/parse/ParseStream.hpp"
#include "algorithms/parse/Lexer.hpp"
#include "algorithms/parse/GrammarNode.hpp"
#include "algorithms/parse/WordParser.hpp"
#include "observe/ObservableAdapter.hpp"
#include "platform/POSIXPlatform.hpp"
#include "platform/Platform.hpp"
#include "MemoryMonitor.hpp"
#include "MemoryAllocator.hpp"
#include "containers/Set.hpp"
#include "new-operator.hpp"

#include "Backtrace.hpp"

#include "algorithms/string/StringAlgorithms.hpp"
#include "algorithms/string/IdentityFilter.hpp"
#include "algorithms/string/OneOfFilter.hpp"

#include "containers/trees/DefTree.hpp"

#include "CRef.hpp"
#include "Proxy.hpp"
#include "ObjectFactory.hpp"

#include "platform/dl/SolarisDL.hpp"

#include "platform/threads/Thread.hpp"
#include "platform/threads/ThreadFactory.hpp"
#include "ui/xq/Xq.hpp"
#include "ui/wq/Wq.hpp"
#include "ui/cq/Cq.hpp"

#include "store/DefField.hpp"

#include <stdio.h>

BEGIN_QR_NAMESPACE

int QRMain( List * )
{
#if defined( USE_POSIX )
//	  TCAST( PLAF, POSIXPlatform ) -> 
//		startProfilingThread( "./tmp/profil-%li" );
#endif
  for( int i = 0 ; i < 1000 ; ++i )
	{
	  //          test_( false );

	  TCAST( THR_SYSTEM -> getSelf(), Object ) -> tester( 0 );
/* unused tests */
#if 0
	  {  
		GrammarNode::testerGrammarNode( 0 );
	  }
	  {
		BaseDefField< Top, Top >::testerBaseDefField( 0 );
	  }
	  {
		DefTree *quercus;

		quercus = new DefTree();
		OGuard _quercus( quercus, quercus );
		quercus -> tester( 0 );
	  }
	  {
		CRef< Proxy< Top > > proxy;

		proxy = new Proxy< Top >( new ObjectFactory( new Object() ) );
		proxy -> tester( 0 );
	  }
	  {  
		CRef< Lexer > parser;

		parser = new Lexer( new ParseStream( new StringEnumeration( "" ) ) );
		parser -> tester( 0 );
	  }
	  {  
		EALG -> tester( 0 );
	  }
	  {
		CRef< List > listy;

		listy = new List();
		DLOGOBJECT( "listy: %s", &listy );
		listy -> append( new String( "foo" ) );
		DLOGOBJECT( "listy+foo: %s", &listy );
	  }
	  {
		//		CRef< SolarisDL > test = new SolarisDL( "dummy" );
		//		test -> tester( 0 );
	  }
	  {
		Backtrace *trace;
			
		trace = new Backtrace();
		OGuard _trace( trace, trace );
			
		trace -> tester( 0 );
	  }
	  {
#if defined( USE_WQ )
		Wq::tester( 0 );
#endif
	  }
	  {
		String().tester( 20 );
	  }
	  {
		List *list;
		list = new List();
		OGuard _list( list, list );
		if( !list -> tester( 0 ) )
		  {
			Debug::getLogger() -> log( "no!" );
			break;
		  }
	  }
	  {
#if defined( USE_BOEHM_GC )
		new String( "bah!" );
		new String( "oooooooooooooooooooooooooooooooooooops!" );
#endif
		/* GC test */
	  }

	  {
		Queue *line;

		line = new Queue();
		OGuard _line( line, line );
		line -> tester( 0 );
	  }
	  {
		PrettyPrintIterable *ppi;

		ppi = new PrettyPrintIterable( "(", ", ", ")", " ... ", 0, &Top::getString );
		OGuard _ppi( ppi, ppi );
		if( !ppi -> tester( 0 ) )
		  {
			Debug::getLogger() -> log( "no!" );
			break;
		  }
	  }
	  SAlg::get() -> tester( 0 );
	  {
#if !defined( WIN32 )
		WordParser *parser;

		parser = new WordParser
		  ( new StringEnumeration( "Statly plump" ) );
		OGuard _parser( parser, parser );
		parser -> tester( 0 );
#endif
	  }
	  {
		OneOfFilter( new IdentityFilter( "blablablafoobarbaz" ), "abo" ).
		  tester( 0 );
	  }
	  {
		Stack *pdl;

		pdl = new Stack();
		OGuard _pdl( pdl, pdl );
		pdl -> tester( 0 );
	  }
	  {
		Object *obj;

		obj = new Object();
		OGuard _obj( obj, obj );
		obj -> tester( 0 );
	  }
	  {
		ObservableAdapter *publisher;
		publisher = new ObservableAdapter();
		OGuard _publisher( publisher, publisher );

		publisher -> tester( 0 );
	  }
	  {
		DumbDictionary *dummy;
		dummy = new DumbDictionary();
		OGuard _dummy( dummy, dummy );
		if( ! ( dummy -> tester( 0 ) ) )
		  {
			Debug::getLogger() -> log( "no!" );
			break;
		  }
	  }
	  {
		Integer *dummyInt;

		dummyInt = new Integer( 0 );
		OGuard _dummyInt( dummyInt, dummyInt );
		if( ! ( dummyInt -> tester( 0 ) ) )
		  {
			Debug::getLogger() -> log( "no!" );
			break;
		  }
	  }
	  {
		Set  *set;

		set = new Set();
		OGuard _set( set, set );
		if( !( set -> tester( 0 ) ) )
		  {
			Debug::getLogger() -> log( "no!" );
			break;
		  }
	  }
	  {
		Empty *em;

		em = new Empty();
		OGuard _em( em, em );
		if( !em -> tester( 0 ) )
		  {
			Debug::getLogger() -> log( "no!" );
			break;
		  }
	  }
	  {
		CArray *ar;

		ar = new CArray( 0, 1 );
		OGuard _ar( ar, ar );
		if( !ar -> tester( 0 ) )
		  {
			Debug::getLogger() -> log( "no!" );
			break;
		  }
	  }
	  {
#if 0 && defined( USE_XQ )
		Xq::tester( 0 );
#endif
	  }
	  {
#if defined( USE_CQ )
		Cq::tester( 0 );
#endif
	  }
#if defined( USE_POSIX )
	  {
		TCAST( PLAF, POSIXPlatform ) -> tester( 0 );
	  }
#endif
	  {
#if defined( USE_THREADS )
		TCAST( THR_SYSTEM -> getSelf(), Object ) -> tester( 0 );
#endif
	  }
/* end of tests */
#endif
	  DLOG( "------------------------------------" );
#if defined( PROFILE_MEM_ALLOC )
	  DLOG( "Allocated: %li", MemoryMonitor::amount() );
#endif
#if defined( MEMORY_LEAK_TEST )
	  // Top::dumpAllocated();
#endif
#if defined( TRACK_BACKPOINTERS )
	  // Top::dumpBackpointers();
#endif
#if defined( USE_ALLOC_CHAIN )
	  // dumpAllocatedByNew();
#endif
	  DLOG( "------------------------------------" );
	  DLOGOBJECT( Platform::getInstance() );
#if 0 && defined( PROFILE_MEM_ALLOC )
// 	  if( ( i % 10 ) == 0 )
// 		{
// 		  MemoryMonitor::dumpStatistics();
// 		  MemoryAllocator::dumpStatistics();
// 		}
#endif
	}
  return 0;
}

END_QR_NAMESPACE


#if defined(_INLINE)
#include "../src/Debug.ipp"
#endif


#if defined(_INLINE)
#include "../src/String.ipp"
#endif

