// -*-C++-*- 

/*  inc/platform/MinimalPlatform.hpp  */

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
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 */



#ifndef __MINIMALPLATFORM_HPP__
#define __MINIMALPLATFORM_HPP__

/* $Id: MinimalPlatform.hpp,v 1.1.1.1 2000/07/19 17:12:57 philogelos Exp $ */

#include "Platform.hpp"
#include "Object.hpp"
#include "defines.h"



BEGIN_QR_NAMESPACE

/**

   @author Philogelos
   @created
*/
class MinimalPlatform : public Platform,
						virtual public Object
{

/**
*/
public: MinimalPlatform();

/**
*/
public: virtual ~MinimalPlatform();

public: virtual void sprintf( char *s, const char * format, /* args */ ...) 
  PRINTF_ALIKE( 3, 4 );
public: virtual void vsprintf( char *s, const char *format, va_list raw );

public: virtual Index printfLength( const char * format, /* args */ ...) 
  PRINTF_ALIKE( 2, 3 ) = 0;
public: virtual Index vprintfLength( const char * format, va_list raw ) = 0;

public: virtual void rawErrorPrintf( const char * format, /* args */ ... ) 
  PRINTF_ALIKE( 2, 3 );
public: virtual void rawErrorVPrintf( const char * format, va_list raw );

public: virtual char *getErrorDescription( int errCode );

public: virtual void exitImmediate( long status );
public: virtual void suicide() NORETURN;
public: virtual void attachDebugger();

public: virtual void setImageName( const char *aName );
public: virtual const char *getImageName() const;

public: virtual char *getTimeStampString();

public: virtual void *allocateMemory( Index aSize );
public: virtual void  deallocateMemory( void *aPointer );

public: virtual char  *strcpy( char *dst, const char *src );
public: virtual int    strcmp( const char *s1, const char *s2 );
public: virtual Index  strlen( const char *s );
public: virtual char  *strcat( char *dst, const char *src );
public: virtual char  *strchr( const char *s, int c );
public: virtual long   strtol( const char *str, char **endptr, int base );

public: virtual int memcmp( void *s1, const void *s2, Index n );
public: virtual void *memchr( const void *s, int c, Index n );
public: virtual void *memcpy( void *s1, const void *s2, Index n );
public: virtual void *memset( void *s, int c, Index n );

  /**
	*/
public:  virtual boolean equals( const Top *anOther ) const;

  /**
	*/
public:  virtual Top *clone() const;

public:  virtual String  getClassName() const;

protected: const char *imageName;
};


END_QR_NAMESPACE

/*
 * $Log: MinimalPlatform.hpp,v $
 * Revision 1.1.1.1  2000/07/19 17:12:57  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:36  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:47  god
 * Imported sources
*/

/* __MINIMALPLATFORM_HPP__ */
#endif
