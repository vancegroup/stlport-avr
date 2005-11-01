# -*- Makefile -*- Time-stamp: <04/03/30 14:53:15 ptr>
# $Id$

SRCROOT=../..
STLPORT_DIR=../../..

!include Makefile.inc

INCLUDES=$(INCLUDES) /I$(STLPORT_INCLUDE_DIR) /I$(STLPORT_DIR)/src /FI vc_warning_disable.h

!ifdef STLP_BUILD_BOOST_PATH
INCLUDES=$(INCLUDES) /I "$(STLP_BUILD_BOOST_PATH)"
!endif

LDSEARCH=$(LDSEARCH) /LIBPATH:$(STLPORT_LIB_DIR)

!include $(SRCROOT)/Makefiles/nmake/top.mak
