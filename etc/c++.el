;; -*- lisp -*-
;;
;; $Id: c++.el,v 1.2 2001/07/03 12:47:02 philogelos Exp $
;; $Author: philogelos $
;;
(defvar base-dir "~/projects/quercus-0.0.4/")
(defvar hpp-file-template "inc/%p/%n.hpp")
(defvar cpp-file-template "src/%p/%n.cpp")
(defvar ipp-file-template "src/%p/%n.ipp")

(defvar license-info
  (concat
   "\n/*"
   "\n * Author: Philogelos A. <Philogelos@yahoo.com>"
   "\n * Maintainer: Philogelos A."
   "\n * Keywords: C++, library, containers"
   "\n *"
   "\n * Copyright (C) 1999, 2000 Philogelos A."
   "\n *"
   "\n * This file is part of Quercus Robusta."
   "\n *"
   "\n * Quercus Robusta is free software; you can redistribute it and/or modify"
   "\n * it under the terms of the GNU Library General Public License as published by"
   "\n * the Free Software Foundation; either version 2, or (at your option)"
   "\n * any later version."
   "\n *"
   "\n * This software is distributed in the hope that it will be useful,"
   "\n * but WITHOUT ANY WARRANTY; without even the implied warranty of"
   "\n * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the"
   "\n * GNU Library General Public License for more details."
   "\n *"
   "\n * You should have received a copy of the GNU Library General Public License"
   "\n * along with this software; see the file COPYING.LIB.  If not, write to the"
   "\n * Free Software Foundation, Inc., 59 Temple Place - Suite 330,"
   "\n * Boston, MA 02111-1307, USA."
   "\n *"
   "\n */"))

(defun c++-replace-in-string ( string regexp newtext no-use)
  (let ((result "") (start 0) mb me)
    (while (string-match regexp string start)
      (setq mb (match-beginning 0)
	    me (match-end 0)
	    result (concat result (substring string start mb) newtext)
	    start me))
    (concat result (substring string start))))


(defvar hpp-template
  (concat
	"// -*-C++-*- "
	"\n"
	"\n/*  inc/%p/%n.hpp  */"
	"\n"
	"%l"
	"\n"
	"\n"
	"\n"
	"\n#ifndef __%m_HPP__"
	"\n#define __%m_HPP__"
	"\n"
	"\n/* $""Id""$ */" ;; ugly way to prevent CVS from expanding keywords
	"\n"
	"\n#include \".hpp\""
	"\n#include \"defines.h\""
	"\n"
	"\nBEGIN_QR_NAMESPACE"
	"\n"
	"\n/**"
	"\n"
	"\n@author Philogelos"
	"\n@created %t"
	"\n*/"
	"\nclass %n : public "
	"\n{"
	"\n"
	"\n/**"
	"\n*/"
	"\npublic: %n();"
	"\n"
	"\n/**"
	"\n*/"
	"\npublic: virtual ~%n();"
	"\n"
	"\n"
	"\n/**"
	"\n*/"
	"\npublic:  virtual boolean equals( const Top *anOther) const;"
	"\n"
	"\n/**"
	"\n*/"
	"\npublic:  virtual Top *clone() const;"
	"\n"
	"\n/**"
	"\n*/"
	"\npublic:  virtual String  toString() const;"
	"\n"
	"\n/**"
	"\n*/"
	"\npublic:  virtual String  getString() const;"
	"\n"
	"\n/**"
	"\n*/"
	"\npublic:  virtual String  getClassName() const;"
	"\n};"
	"\n"
	"\nEND_QR_NAMESPACE"
	"\n"
	"\n/*"
	"\n * $""Log""$" ;; ugly way to prevent CVS from expanding keywords
	"\n */" 
	"\n"
	"\n/* __%m_HPP__ */"
	"\n#endif"))


(defvar cpp-template
  (concat
    "// -*-C++-*- "
	"\n"
	"\n/*  src/%p/%n.cpp  */"
	"\n"
	"%l"
	"\n"
	"\n"
	"\n"
	"\n/* $""Id""$ */"  ;; ugly way to prevent CVS from expanding keywords
	"\n#if !defined( _INLINE )"
	"\nstatic char cvsid[] = \"@(#)$""Id""$\";"
	"\nstatic char debugFileId[] = __FILE__;"
	"\n#endif"
	"\n"
	"\n#include \"%p/%n.hpp\""
	"\n#include \"Debug.hpp\""
	"\n"
	"\nBEGIN_QR_NAMESPACE"
	"\n"
	"\n%n::%n()"
	"\n{}"
	"\n"
	"\n%n::~%n()"
	"\n{}"
	"\n"
	"\nboolean %n::equals( const Top *anOther) const"
	"\n{}"
	"\n"
	"\nTop *%n::clone() const"
	"\n{}"
	"\n"
	"\nString  %n::toString() const"
	"\n{}"
	"\n"
	"\nString  %n::getString() const"
	"\n{}"
	"\n"
	"\nString  %n::getClassName() const"
	"\n{"
	"\nreturn \"%n\";"
	"\n}"
	"\n"
	"\nEND_QR_NAMESPACE"
	"\n"
	"\n#if defined( _INLINE )"
	"\n#include \"../src/Debug.ipp\""
	"\n#endif"
	"\n"
	"\n"
	"\n/*"
	"\n * $""Log""$"
	"\n */"))

(defun replace-format (aString aName aPackage)
  ""
  (setq case-replace nil)
  (c++-replace-in-string
	(c++-replace-in-string
	  (c++-replace-in-string 
		(c++-replace-in-string 
		  (c++-replace-in-string 
			(c++-replace-in-string aString "%t" (current-time-string) t) 
			"%m" (upcase aName) t)
		  "%l" license-info t)
		"%n" aName t)
	  "%p" aPackage t)
	"%s" (upcase aPackage) t))


(defun c++-template (aName aPackage)
  ""
  (interactive "sClass Name: \nsPackage Name: ")
  (find-file (replace-format (concat base-dir hpp-file-template) aName aPackage))
  (insert (replace-format hpp-template aName aPackage))
  (find-file (replace-format (concat base-dir cpp-file-template) aName aPackage))
  (insert (replace-format cpp-template aName aPackage)))

(global-set-key [ (meta z) ] 'c++-template)

;;
;; $Log: c++.el,v $
;; Revision 1.2  2001/07/03 12:47:02  philogelos
;; update version
;;
;; Revision 1.1.1.1  2000/07/19 17:34:47  philogelos
;; stored sources into sourceforge.net CVS
;;
;; Revision 1.3  2000/04/22 20:35:45  god
;; more portable (but ugly) time-stamping
;;
;; Revision 1.2  2000/04/09 13:13:54  god
;; CVS keywords escaped from expansion
;;
;;

