# -*- Makefile -*- Time-stamp: <04/03/31 08:17:03 ptr>
# $Id$

SRCROOT=../../src/explore
COMPILER_NAME=evc4-x86
CEVERSION=420
STLPORT_DIR=../..
MAKEFLAGS=/N

!include Makefile.inc

INCLUDES=$(INCLUDES) /I "$(STLPORT_INCLUDE_DIR)" /I "cppunit" /I "../../src/" /FI "vc_warning_disable.h"
DEFS = /DCPPUNIT_MINI=1
DEFS_DBG = /D_STLP_USE_DEBUG_LIB

LDSEARCH=$(LDSEARCH) /LIBPATH:$(STLPORT_LIB_DIR)

LDLIBS_REL=
LDLIBS_DBG=
LDLIBS_STLDBG=

!include $(SRCROOT)/Makefiles/nmake/top.mak
