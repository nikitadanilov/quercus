// -*-C++-*- 

/*  inc/Recongnizer.hpp  */

/*
 * Author: Philogelos A. <Philogelos@yahoo.com>
 * Maintainer: Philogelos A.
 * Keywords: C++, library, containers
 *
 * Copyright (C) 1999, 2000 Philogelos A.
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



#ifndef __RECONGNIZER_HPP__
#define __RECONGNIZER_HPP__

/* $Id: Recognizer.hpp,v 1.1 2000/09/21 18:20:31 philogelos Exp $ */

#include "Top.hpp"
#include "defines.h"

BEGIN_QR_NAMESPACE

/**

   @author Philogelos
   @created Tue Sep 12 16:55:23 2000
*/
interface Recongnizer : public virtual Top
{
 public: virtual boolean accepts( const Top *const anObject ) const = 0;
};

END_QR_NAMESPACE

/*
 * $Log: Recognizer.hpp,v $
 * Revision 1.1  2000/09/21 18:20:31  philogelos
 * Interface used (currently only) by Lexer
 *
 */

/* __RECONGNIZER_HPP__ */
#endif
