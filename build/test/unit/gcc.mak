# -*- Makefile -*- Time-stamp: <07/10/11 00:47:54 ptr>

SRCROOT := ../..
COMPILER_NAME := gcc
#NOT_USE_NOSTDLIB := 1
#WITHOUT_STLPORT := 1
ALL_TAGS := release-shared stldbg-shared
STLPORT_DIR := ../../..
release-shared:	STLPORT_LIB_DIR = ${PWD}/../../lib/${OUTPUT_DIR}
dbg-shared:	STLPORT_LIB_DIR = ${PWD}/../../lib/${OUTPUT_DIR_DBG}
stldbg-shared:	STLPORT_LIB_DIR = ${PWD}/../../lib/${OUTPUT_DIR_STLDBG}

include Makefile.inc
include ${SRCROOT}/Makefiles/gmake/top.mak

dbg-shared:	DEFS += -D_STLP_DEBUG_UNINITIALIZED 
stldbg-shared:	DEFS += -D_STLP_DEBUG_UNINITIALIZED 

ifdef STLP_BUILD_BOOST_PATH
INCLUDES += -I${STLP_BUILD_BOOST_PATH}
endif

ifndef TARGET_OS
ifeq ($(OSNAME), sunos)
LDFLAGS += -Wl,-R${STLPORT_LIB_DIR}
endif
ifeq ($(OSNAME), freebsd)
LDFLAGS += -Wl,-R${STLPORT_LIB_DIR}
endif
ifeq ($(OSNAME), openbsd)
LDFLAGS += -Wl,-R${STLPORT_LIB_DIR}
endif
ifeq ($(OSNAME), linux)
LDFLAGS += -Wl,-rpath=${STLPORT_LIB_DIR}
endif
endif
