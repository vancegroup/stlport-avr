# -*- Makefile -*- Time-stamp: <04/03/31 08:14:15 ptr>
# $Id$

SRCROOT=../../src/explore
COMPILER_NAME=evc3
CEVERSION=300
STLPORT_DIR=../..

!include Makefile.inc

INCLUDES=$(INCLUDES) /I "$(STLPORT_INCLUDE_DIR)" /I "cppunit" /I "$(STLPORT_DIR)/src/" /FI "vc_warning_disable.h"
DEFS = /DCPPUNIT_MINI=1
DEFS_DBG = /D_STLP_USE_DEBUG_LIB

LDSEARCH=$(LDSEARCH) /LIBPATH:$(STLPORT_LIB_DIR)

LDLIBS_REL=
LDLIBS_DBG=
LDLIBS_STLDBG=

!include $(SRCROOT)/Makefiles/nmake/top.mak
