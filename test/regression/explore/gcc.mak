# -*- Makefile -*- Time-stamp: <03/10/26 18:54:04 ptr>
# $Id$

SRCROOT := ../../../src/explore
COMPILER_NAME := gcc

# STLPORT_DIR := /export/home/ptr/STLport.lab/cvs.stlport.com/STLport-R451_dev
ALL_TAGS := release-shared stldbg-shared
STLPORT_DIR := ../../..
include Makefile.inc
include ${SRCROOT}/Makefiles/top.mak


INCLUDES += -I${STLPORT_INCLUDE_DIR}

ifdef STLP_BUILD_BOOST_PATH
INCLUDES += -I${STLP_BUILD_BOOST_PATH}
endif

release-shared:	LDSEARCH = -L${STLPORT_LIB_DIR} -Wl,-R${STLPORT_LIB_DIR}
stldbg-shared:	LDSEARCH = -L${STLPORT_LIB_DIR} -Wl,-R${STLPORT_LIB_DIR}
dbg-shared:	LDSEARCH = -L${STLPORT_LIB_DIR} -Wl,-R${STLPORT_LIB_DIR}

ifeq ($(OSNAME),sunos)
release-shared : LDLIBS = -lstlport_gcc -lrt
stldbg-shared  : LDLIBS = -lstlport_gcc_stldebug -lrt
dbg-shared     : LDLIBS = -lstlport_gcc_debug -lrt
else
release-shared : LDLIBS = -lstlport_gcc
stldbg-shared  : LDLIBS = -lstlport_gcc_stldebug
dbg-shared     : LDLIBS = -lstlport_gcc_debug
endif

