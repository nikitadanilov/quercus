// -*-C++-*- 

/*  src/algorithms/parse/WordParser.cpp  */

/*
 * Author: Philogelos A. <Philogelos@yahoo.com>
 * Maintainer: Philogelos A.
 * Keywords: C++, library, containers
 *
 * Copyright (C) 1998, 1999 Philogelos A.
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



/* $Id: WordParser.cpp,v 1.1.1.1 2000/07/19 16:44:13 philogelos Exp $ */
#if !defined(_INLINE)
static char cvsid[] = "@(#)$Id: WordParser.cpp,v 1.1.1.1 2000/07/19 16:44:13 philogelos Exp $";
static char debugFileId[] = __FILE__;
#endif


#include "algorithms/parse/TokenAdapter.hpp"
#include "algorithms/parse/WordParser.hpp"
#include "containers/lists/List.hpp"
#include "containers/Container.hpp"
#include "containers/Pair.hpp"
#include "StringBuffer.hpp"
#include "LinkManager.hpp"
#include "UCSChar.hpp"
#include "OGuard.hpp"
#include "PGuard.hpp"
#include "Debug.hpp"

#include "exceptions/NoEntity.hpp"

BEGIN_QR_NAMESPACE

CharEnumeration::CharEnumeration()
{
  FINIT( current, new UCSChar( ( unichar ) 0 ) );
}

CharEnumeration::~CharEnumeration()
{
  FCDONE( current );
}

Char *CharEnumeration::getNextTypedElement()
{
  return DCAST( getNextCharFast() -> clone(), Char );
}

WordParser::WordParser( CharEnumeration *aSource )
{
  preC_( aSource != ( CharEnumeration * ) NULL );

  LinkManager::reg( this, aSource );
  
  source = aSource;
  readChar = ( Char * ) NULL;

  alphabets = new List();
  LinkManager::reg( this, alphabets );
  prototypes = new List();
  LinkManager::reg( this, prototypes );
}

WordParser::~WordParser()
{
  LinkManager::free( this, source );
  LinkManager::free( this, alphabets );
  LinkManager::free( this, prototypes );
  if( defToken != ( Token * ) NULL )
	{
	  LinkManager::free( this, defToken );
	}
  if( readChar != ( Char * ) NULL )
	{
	  LinkManager::free( ( const Top * ) this, 
						 ( const Top * ) readChar );
	}
}

void WordParser::addSyntaxEntry( Container *anAlphabet, Token *aPrototype )
{
  preC_( anAlphabet != ( Container * ) NIL );
  preC_( aPrototype != ( Token * ) NIL );

  alphabets -> append( anAlphabet );
  prototypes -> append( aPrototype );
}

void WordParser::addDefaultEntry( Token *aPrototype )
{
  preC_( aPrototype != ( Token * ) NIL );

  LinkManager::move( this, defToken, aPrototype );
  defToken = aPrototype;
}

void WordParser::removeSyntaxEntry( Container *anAlphabet ) THROWS( NoEntity * )
{
  preC_( anAlphabet != ( Container * ) NIL );

  for( alphabets -> toFirst() ; !( alphabets -> atEnd() ) ; )
	{
	  Container *alphabet;
	  
	  alphabet = TCAST( alphabets -> getCurrentValue(), Container );
	  test_( alphabet != ( Container * ) NULL );
	  if( alphabet == anAlphabet )
		{
		  alphabets -> remove();
		  return;
		}
	}
  throw new NoEntity( "WordParser::removeSyntaxEntry(): no such alphabet", null );
}

Token *WordParser::getNextToken()
{
  preC_( hasMoreElements() );

  StringBuffer buffer( StringBuffer::defaultLength,
					   StringBuffer::defaultDelta );
  Token  *result;

  buffer.dontManage();
  if( readChar == ( Char * ) NULL )
	{
	  Char *newChar;

	  newChar = source -> getNextCharFast();
	  LinkManager::move( this, readChar, newChar );
	  readChar = newChar;
	}
  current = findIndex( readChar );
  if( current >=0 )
	{
	  result = TCAST( prototypes -> getAt( current ), Token ) -> cloneToken();
	}
  else
	{
	  test_( defToken != ( Token * ) NIL );
	  result = defToken -> cloneToken();
	}
  PGuard _result( result, this );

  do
	{
	  buffer.add( readChar );
	  if( source -> hasMoreElements() )
		{
		  Char *newChar;
		  
		  newChar = source -> getNextCharFast();
		  LinkManager::move( this, readChar, newChar );
		  readChar = newChar;
		}
	  else
		{
		  LinkManager::free( this, readChar );
		  readChar = ( Char * ) NULL;
		  break;
		}
	}
  while( current == findIndex( readChar ) );
  result -> setCore( buffer.asString().clone() );
  return result;
}

Token *WordParser::getNextTypedElement()
{
  return getNextToken();
}

boolean WordParser::hasMoreElements()
{
  return ( readChar != ( Char * ) NULL ) || 
	( source -> hasMoreElements() );
}

boolean WordParser::equals( const Top *anOther ) const
{
  WordParser *other;

  other = DCAST( anOther, WordParser );
  if( other == ( WordParser * ) NULL )
	{
	  return false;
	}
  else
	{
	  OGuard _other( other, this );
	  return( other -> source -> equals( source ) );
	}
}

Top *WordParser::clone() const
{
  WordParser *parser;

  parser = new WordParser( source );
  PGuard _parser( parser, this );
  for( Index i = 0 ; i < alphabets -> length() ; ++i )
	{
	  parser -> 
		addSyntaxEntry( TCAST( alphabets -> getAt( i ), Container ), 
						TCAST( prototypes -> getAt( i ), Token ) );
	}
  if( defToken != ( Token * ) NIL )
	{
	  parser -> addDefaultEntry( defToken );
	}
  return parser;
}

String  WordParser::getClassName() const
{
  return "WordParser";
}

Index WordParser::findIndex( Char *aLetter )
{
  preC_( aLetter != ( Char * ) NIL );
  Index newCurrent;

  newCurrent = 0;
  for( alphabets -> toFirst() ; 
	   !( alphabets -> atEnd() ) ;
	   alphabets -> next(), ++newCurrent )
	{
	  Container *alphabet;

	  alphabet = TCAST( alphabets -> getCurrentValue(), Container );
	  OGuard _alphabet( alphabet, this );

	  if( alphabet -> contains( readChar ) )
		{
		  return newCurrent;
		}
	}
  return -1;
}

#if defined( TESTING )

END_QR_NAMESPACE

#include "containers/lists/List.hpp"
#include "iter/iterables/PrettyPrintIterable.hpp"
#include "iter/iterables/EchoIterable.hpp"
#include "iter/iterables/NOPIterable.hpp"
#include "StringEnumeration.hpp"
#include "algorithms/parse/TokenAdapter.hpp"
#include "algorithms/enumerations/EnumerationAlgorithms.hpp"

BEGIN_QR_NAMESPACE

boolean WordParser::tester( int ) const
{
  TokenAdapter *space;
  TokenAdapter *word;
  TokenAdapter *punctuation;

  space = new TokenAdapter();
  OGuard _space( space, this );

  word  = new TokenAdapter();
  OGuard _word( word, this );

  punctuation = new TokenAdapter();
  OGuard _punctuation( punctuation, this );

  space -> setTag( new String( "space" ) );
  word -> setTag( new String( "word" ) );
  punctuation -> setTag( new String( "punctuation" ) );

  List *spaces;
  List *punctuations;
  WordParser *parser;

  Iterator *it;
  PrettyPrintIterable *runner;
  String result;

  spaces = new List();
  OGuard _spaces( spaces, this );
  spaces -> append( new UCSChar( ' ' ) );

  punctuations = new List();
  OGuard _punctuations( punctuations, this );
  punctuations -> append( new UCSChar( '.' ) );
  punctuations -> append( new UCSChar( ',' ) );
  punctuations -> append( new UCSChar( '?' ) );
  punctuations -> append( new UCSChar( ';' ) );
  punctuations -> append( new UCSChar( '(' ) );
  punctuations -> append( new UCSChar( ')' ) );

  parser = new WordParser
	  ( new StringEnumeration( "Who do you no tonigh, lazy and gentleman? The echo is where in the back of the wodes; callhim forth! (Shaun Mac Irewick, briefdragger, for the concern of Messrs Jhon Jhamieson and Song, rated one hundrick and thin per storehundred on this nightly quisquiquock of the twelve apostrophes, set by Jockit Mic Ereweak. He misunderstruck and aim for am ollo of number three of them and left his free natural ri postes to four of them in their own fine artful disorder.)  I. What secondtonone myther rector and maximost bridges maker was the first to rise taller through his beanstale than the bluegum buaboababbaun or the giganteous Wellingtonia Sequoia" ) );
  OGuard _parser( parser, parser );
  parser -> addSyntaxEntry( spaces, space );
  parser -> addSyntaxEntry( punctuations, punctuation );
  parser -> addDefaultEntry( word );

  it = parser -> getIterator();
  runner = new PrettyPrintIterable( "(", ", ", ")", " ... ", 0, &Top::getString );

  OGuard _runner( runner, this );
  OGuard _it( it, this );
  
  it -> iterate( runner );
  /* it -> iterate( new EchoIterable() ); */
  result = String( *( String * )( runner -> getResult() ) );
  
  DLOGSTRING( "Parsed: %s", result );
  
  DLOG( "totally %li tokens", EAlg::get() -> getCardinality( parser ) );
  return true;
}
#endif


END_QR_NAMESPACE

#if defined(_INLINE)
#include "../src/Debug.ipp"
#endif

/*
 * $Log: WordParser.cpp,v $
 * Revision 1.1.1.1  2000/07/19 16:44:13  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:40  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:30  god
 * Imported sources
 *
 * Revision 1.3  1999/05/22 13:00:33  philogelos
 * Merging sources back from SPARC
 *
 * Revision 1.2  1999/03/03 19:09:32  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.1  1999/02/28 16:29:18  philogelos
 * Parser added
 * */



