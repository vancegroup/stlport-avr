# -*- Makefile -*- Time-stamp: <05/12/08 01:42:34 ptr>

SRCROOT := ../..
COMPILER_NAME := gcc

ALL_TAGS := release-shared stldbg-shared
STLPORT_DIR := ../../..
include Makefile.inc
include ${SRCROOT}/Makefiles/top.mak

INCLUDES += -I${STLPORT_INCLUDE_DIR}

dbg-shared:	DEFS += -D_STLP_DEBUG_UNINITIALIZED 
stldbg-shared:	DEFS += -D_STLP_DEBUG_UNINITIALIZED 

ifeq ($(OSNAME), cygming)
release-static:	DEFS += -D_STLP_USE_STATIC_LIB
dbg-static:	DEFS += -D_STLP_USE_STATIC_LIB
stldbg-static:	DEFS += -D_STLP_USE_STATIC_LIB
endif

ifeq ($(OSNAME), windows)
release-static:	DEFS += -D_STLP_USE_STATIC_LIB
dbg-static:	DEFS += -D_STLP_USE_STATIC_LIB
stldbg-static:	DEFS += -D_STLP_USE_STATIC_LIB
endif

ifdef STLP_BUILD_BOOST_PATH
INCLUDES += -I${STLP_BUILD_BOOST_PATH}
endif

ifndef TARGET_OS
ifeq ($(OSNAME), sunos)
release-shared:	LDFLAGS += -Wl,-R${STLPORT_LIB_DIR}
dbg-shared:	LDFLAGS += -Wl,-R${STLPORT_LIB_DIR}
stldbg-shared:	LDFLAGS += -Wl,-R${STLPORT_LIB_DIR}
endif
ifeq ($(OSNAME), freebsd)
release-shared:	LDFLAGS += -Wl,-R${STLPORT_LIB_DIR}
dbg-shared:	LDFLAGS += -Wl,-R${STLPORT_LIB_DIR}
stldbg-shared:	LDFLAGS += -Wl,-R${STLPORT_LIB_DIR}
endif
ifeq ($(OSNAME), openbsd)
release-shared:	LDFLAGS += -Wl,-R${STLPORT_LIB_DIR}
dbg-shared:	LDFLAGS += -Wl,-R${STLPORT_LIB_DIR}
stldbg-shared:	LDFLAGS += -Wl,-R${STLPORT_LIB_DIR}
endif
ifeq ($(OSNAME), linux)
release-shared:	LDFLAGS += -Wl,-rpath=${STLPORT_LIB_DIR}
dbg-shared:	LDFLAGS += -Wl,-rpath=${STLPORT_LIB_DIR}
stldbg-shared:	LDFLAGS += -Wl,-rpath=${STLPORT_LIB_DIR}
endif
ifeq ($(OSNAME),darwin)
release-shared:	LDFLAGS += -Wl,-L${STLPORT_LIB_DIR}
dbg-shared:	LDFLAGS += -Wl,-L${STLPORT_LIB_DIR}
stldbg-shared:	LDFLAGS += -Wl,-L${STLPORT_LIB_DIR}
endif
endif



