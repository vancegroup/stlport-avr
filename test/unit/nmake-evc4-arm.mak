# -*- Makefile -*- Time-stamp: <04/03/31 08:14:15 ptr>
# $Id$

SRCROOT=../../src/explore
COMPILER_NAME=evc4-arm
CEVERSION=420
STLPORT_DIR=../..

!include Makefile.inc

INCLUDES=$(INCLUDES) /I "$(STLPORT_INCLUDE_DIR)" /I "cppunit"
DEFS = /DCPPUNIT_MINI=1

LDSEARCH=$(LDSEARCH) /LIBPATH:$(STLPORT_LIB_DIR)

LDLIBS_REL=
LDLIBS_DBG=
LDLIBS_STLDBG=

!include $(SRCROOT)/Makefiles/nmake/top.mak
