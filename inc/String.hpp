//-*-C++-*-

/*  inc/String.hpp  */


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


#ifndef __STRING_H__
#define __STRING_H__

/* $Id: String.hpp,v 1.1.1.1 2000/07/19 16:57:28 philogelos Exp $ */
#include "defines.h"
/* #include "StringImplementation.hpp" */
#include "Object.hpp"

#include <stdarg.h>

BEGIN_QR_NAMESPACE

class Char;
class StringImplementation;
class CodesetConverter;

/** Variable length string.
	Basic class representing fast mutable String.
	Such Strings can be passed by themselves rather than as pointers
	or references. String objects count references to them and share
	characters between instances.
	
	@author Philogelos
	@created «‚“ 18 ∏Ó› 1998 17:59:29
*/
class String : public Object
{
  /** Creates empty string.
	
  */
public:  String();

  /** Copy constructor.
	
  */
public:  String( const String &src );

  /** Creates string from given C-string.
	  s points to UTF8 encoded string.
  */
public:  String( const char *s );

  /** Creates string from given C-string.
	  s points to UTF8 encoded string.
  */
public:  String( const char *s, 
				 boolean shouldDelete );

  /** Creates string from given C-string.
	  Iff second parameter is true memory is allocated
	  and characters are copied in it.

	  s points to UCS2 encoded string.
  */
public:  String( const unichar *s, 
				 boolean shouldCopy = false, 
				 boolean shouldDelete = false );

  /** Creates string from given C-string.
	  Iff second parameter is true memory is allocated
	  and characters are copied in it.

	  s points to strig encoded according to 
	  aConverter conversion.
  */
public:  String( const char *s, CodesetConverter *aConverter,
				 boolean shouldDelete = false );

  /** Creates String containing decimal representaion
	  of given number.
	
  */
public:  String( const Index i );

  /** Creates String containing  representaion
	of given number in a given radix.
	
  */
public:  String( const Index i, const int base );

  /** Creates String containing only
	  given UNICODE character.
  */
public:  String( const Char *aChar );

public:  virtual ~String();

  /** Assignment operator.
	
  */
public:  String  operator =(String src);

  /** Concatenates strings. Returns new string iff
	  left operand is non empty.
	
  */
public:  String  operator +(const String src) const;

  /** Appends given string to this string.
	  Returns this string.

  */
public:  String  &operator +=(const String src);

  /** Appends given char to this string.
	  Returns this string.

  */
public:  String  &operator +=(const Char *src);

  /** Compares strings.
	
  */
public:  boolean operator ==(const String &rside) const;

  /** Compares strings.
	
  */
public:  virtual boolean equals( const Top *anOther ) const;

  /** Returns underlying C string in UTF8 encoding.

   */
public:  char *getChars() const;
  
  /** Casts String to char *.
	
  */
public:  operator char *() const;

  /** Returns underlying C string in UCS2 encoding.

   */
public:  unichar *getUNIChars() const;
  /** Returns internal string representation.	
  */
  //public:  operator StringImplementation *() const;

public:  virtual String getString() const;
public:  virtual String  getClassName() const;
public:  virtual Top *clone() const;

  /** Returns length of a String.
	
  */
public:  Index length() const;

  /** Searches for given character within String.
	
  */
public:  Index lindex( const unichar what) const;

  /** Searches for given sub-string within String.
	
  */
public:  Index lindex( const String what) const;

  /** Checks that this string contains given character.
	
  */
public:  boolean contains( const unichar aChar ) const;

  /** Returns sub-string of this string with given
	  lower and upper sub-scripts.
	
  */
public:  String clip( const Index aBegin, const Index anEnd ) const;

  /** Converts this string to number, if possible.
	
  */
public:  Index toNum( int aRadix = 0 ) const;

  /** Checks that this string consists exclusively of
	  characters from given string.
	
  */
public:  boolean consistsOf(const String aPattern = String( " \t\n" ) ) const;

  /** Checks that this string consists exclusively of
	  whitespaces.
	
  */
public:  boolean isBlank() const;

  /**
	 Simple analog of standard sprintf function.
	 Following formats are supported:
	 <pre>
	   %s, %c, %i, %li, %d, %ld, %o, %lo, %x, %lx, %% --- much like in sprintf
	   %lc --- interprets argument as UNICODE characted in UCS2 
	           (of type unichar)
	   %O  --- argument is instance of ObjectWrapper, to its value
	           toString() is applied.
	   %lO --- argument is instance of ObjectWrapper, to its value
	           getString() is applied.
	   %S  --- argument is String
	   %B  --- argument is boolean, "t" or "f" inserted
	   %lB --- argument is boolean, "true" or "false" inserted
	 </pre>
	 @see #vformat()
	 @see #sprintf()
	 @see Platform::sprintf()
	 @see unichar
	 @see Top::toString()
	 @see Top::getString()
	 @see ObjectWrapper
	 @see OW
  */
public:  virtual String format( int aDummy, ... );

  /**
	 Same as String::format() with different calling 
	 interface.

	 @see #format()
  */
public:  virtual String vformat( va_list args );

  /**
	 Wrapper around sprintf function.
	 First argument is ignored.

	 @see Platform::sprintf()
  */
public:  virtual String sprintf( int aDummy, ... );

  /**
	 Wrapper around vsprintf function.

	 @see Platform::vsprintf()
  */
public:  virtual String vsprintf( va_list args );
public:  virtual String strip( String aSpaces );
  
public:  static unichar *codeToUCS( const char *anUTF8Chars, 
									CodesetConverter *aConverter );
public:  static char *ucsToCode( const unichar *anUCSChars, 
								 CodesetConverter *aConverter );

public:  static unichar *utf8ToUCS( const char *anUTF8Chars );
public:  static char *ucsToUTF8( const unichar *anUCSChars );
  
public:  static Index getUCSLength( const char *anUTF8Chars, 
									CodesetConverter *aConv );
public:  static Index getLength( const unichar *anUCSChars, 
								 CodesetConverter *aConv );
  
  /** Enumeration of sprintf-like specs supported by ::format().

   */
protected: typedef enum { CharFormat, 
						  IntFormat, 
						  CStringFormat, 
						  StringFormat, 
						  ObjFormat, 
						  OtherFormat,
						  BooleanFormat } Format;

  /** Initialise internal representation
	  of string.
	
  */
protected:  void init( const unichar *s, boolean shouldCopy, 
					   boolean shouldDelete );

  /** Internal representation of string.
	
  */
protected:  StringImplementation *core;

  /** Buffer used internally to convert strings
	  to and fro numbers.
	
  */
  //protected:  static char numBuffer[];
protected: StringImplementation *getCore() const;

public: static String nullLiteral;
#if defined( TESTING )
public:  virtual boolean tester( int aParam ) const;
#endif
};

END_QR_NAMESPACE

/*
 * $Log: String.hpp,v $
 * Revision 1.1.1.1  2000/07/19 16:57:28  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:17  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:38  god
 * Imported sources
 *
 * Revision 1.4  1999/03/03 19:09:05  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.3  1999/02/28 12:39:49  philogelos
 * Create string from UNICODE char and += operator added
 *
 * Revision 1.2  1998/12/01 16:14:36  philogelos
 * conditionally introduce ::tester()
 *
 * Revision 1.1.1.1  1998/11/25 20:11:05  philogelos
 * Quercus Robusta
 *
 * Revision 1.4  1998/07/09 09:04:42  philogelos
 * custom new/delete added
 *
 * Revision 1.3  1998/07/07 14:29:49  philogelos
 * Memory leak in SUNWspro dynamic_cast fixed.
 *
 * Revision 1.2  1998/06/22 18:12:55  philogelos
 * Enumerations and containers added
 *
 * Revision 1.1.1.1  1998/06/22 08:47:11  philogelos
 * First version under CVS
 *
 * Revision 1.1.1.1  1998/04/01 17:15:30  philogelos
 * first version under CVS
 * */

/* __STRING_H__ */
#endif
