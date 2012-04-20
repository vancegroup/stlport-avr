# -*- Makefile -*- Time-stamp: <2012-04-20 19:59:39 ptr>

SRCROOT := ../..
COMPILER_NAME := clang

include Makefile.inc
include ${SRCROOT}/Makefiles/top.mak

INCLUDES += -I$(STLPORT_INCLUDE_DIR)

ifeq ($(OSNAME),linux)
DEFS += -D_GNU_SOURCE
endif
