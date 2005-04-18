# -*- Makefile -*- Time-stamp: <04/03/14 18:55:49 ptr>
# $Id$

SRCROOT := ../..
COMPILER_NAME := icc

ALL_TAGS := release-shared stldbg-shared
STLPORT_DIR := ../../..
include Makefile.inc
include ${SRCROOT}/Makefiles/top.mak


INCLUDES += -I${STLPORT_INCLUDE_DIR}
DEFS += -DCPPUNIT_MINI=1

ifdef STLP_BUILD_BOOST_PATH
INCLUDES += -I${STLP_BUILD_BOOST_PATH}
endif

release-shared:	LDSEARCH = -L${STLPORT_LIB_DIR} -Wl,-R${STLPORT_LIB_DIR}
stldbg-shared:	LDSEARCH = -L${STLPORT_LIB_DIR} -Wl,-R${STLPORT_LIB_DIR}
dbg-shared:	LDSEARCH = -L${STLPORT_LIB_DIR} -Wl,-R${STLPORT_LIB_DIR}

ifeq ($(OSNAME),linux)
release-shared : LDLIBS = -lpthread -lstlport_icc
stldbg-shared  : LDLIBS = -lpthread -lstlport_icc_stldebug
dbg-shared     : LDLIBS = -lpthread -lstlport_icc_debug
endif

