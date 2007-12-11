# -*- Makefile -*- Time-stamp: <07/12/12 01:21:41 ptr>

SRCROOT := ..
COMPILER_NAME := gcc
STLP_BUILD := 1

STLPORT_INCLUDE_DIR = ../../stlport
HEADERS_BASE = ${STLPORT_INCLUDE_DIR}

include Makefile.inc
include ${SRCROOT}/Makefiles/gmake/top.mak

ifeq ($(OSNAME),linux)
DEFS += -D_STLP_REAL_LOCALE_IMPLEMENTED -D_GNU_SOURCE
endif

# options for build with boost support
ifdef STLP_BUILD_BOOST_PATH
INCLUDES += -I$(STLP_BUILD_BOOST_PATH)
endif
