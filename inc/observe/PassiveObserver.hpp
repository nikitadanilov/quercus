// -*-C++-*- 

/*  inc/observe/PassiveObserver.hpp  */


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


#ifndef __PASSIVEOBSERVER_HPP__
#define __PASSIVEOBSERVER_HPP__

/* $Id: PassiveObserver.hpp,v 1.1.1.1 2000/07/19 17:12:37 philogelos Exp $ */

#include "ObservationContext.hpp"
#include "ObserverAdapter.hpp"
#include "defines.h"

BEGIN_QR_NAMESPACE

typedef Index HandlerResult;
class Condition;

/**
   Flavour of Observer passively
   listening for events.

   @author Philogelos
   @created ø‚› 10 ∏Ó€ 1998 14:07:24
*/
abstract class PassiveObserver : public ObserverAdapter
{
  /**
	 Subscribe this observer to given observable 
	 in passive mode.
  */
public: virtual void subscribeTo( Observable *aPublisher );

  /** 
	  Method called by Observables to 
	  announce Condition.
  */
public: virtual HandlerResult fire( Condition *aCondition, 
									ObservationContext *aContext ) = 0;

public: virtual HandlerResult firePost( Condition *aCondition, 
										ObservationContext *aContext );
};

END_QR_NAMESPACE

/*
 * $Log: PassiveObserver.hpp,v $
 * Revision 1.1.1.1  2000/07/19 17:12:37  philogelos
 * stored sources into sourceforge.net CVS
 *
 * Revision 1.2  2000/04/09 11:29:36  god
 * CVS Log keyword transferred to remove slash-star in comments
 *
 * Revision 1.1.1.1  2000/04/01 14:07:47  god
 * Imported sources
 *
 * Revision 1.3  1999/03/03 19:09:24  philogelos
 * Put sources under GNU Library License
 *
 * Revision 1.2  1999/02/28 15:39:07  philogelos
 * Publish/Subscribe re-worked
 *
 * Revision 1.1.1.1  1998/11/25 20:11:05  philogelos
 * Quercus Robusta
 *
 * Revision 1.1  1998/07/10 10:39:31  philogelos
 * Publish-subscribe sub-system initialised
 * */

/* __PASSIVEOBSERVER_HPP__ */
#endif
