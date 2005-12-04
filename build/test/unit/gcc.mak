# -*- Makefile -*- Time-stamp: <05/09/04 22:01:11 ptr>

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

LDSEARCH = -L${STLPORT_LIB_DIR}

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

ifeq ($(OSNAME),cygming)
LIB_VERSION = ${LIBMAJOR}.${LIBMINOR}
release-shared : LDLIBS = -lstlport.${LIB_VERSION}
dbg-shared     : LDLIBS = -lstlportg.${LIB_VERSION}
stldbg-shared  : LDLIBS = -lstlportstlg.${LIB_VERSION}
release-static : LDLIBS = -lstlport.${LIB_VERSION}
dbg-static     : LDLIBS = -lstlportg.${LIB_VERSION}
stldbg-static  : LDLIBS = -lstlportstlg.${LIB_VERSION}
else
ifeq ($(OSNAME),windows)
LIB_VERSION = ${LIBMAJOR}.${LIBMINOR}
release-shared : LDLIBS = -lstlport.${LIB_VERSION}
dbg-shared     : LDLIBS = -lstlportg.${LIB_VERSION}
stldbg-shared  : LDLIBS = -lstlportstlg.${LIB_VERSION}
else
release-shared : LDLIBS = -lstlport
dbg-shared     : LDLIBS = -lstlportg
stldbg-shared  : LDLIBS = -lstlportstlg
endif
endif

ifeq ($(OSNAME),sunos)
release-shared : LDLIBS = -lstlport -lrt
stldbg-shared  : LDLIBS = -lstlportstlg -lrt
dbg-shared     : LDLIBS = -lstlportg -lrt
endif

