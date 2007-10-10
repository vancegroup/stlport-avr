# Time-stamp: <07/07/12 11:00:18 ptr>
#
# Copyright (c) 1997-1999, 2002, 2003, 2005, 2006
# Petr Ovtchenkov
#
# Portion Copyright (c) 1999-2001
# Parallel Graphics Ltd.
#
# Licensed under the Academic Free License version 3.0
#

ifndef _FORCE_CXX
CXX := c++
else
CXX := $_FORCE_CXX
endif

ifndef _FORCE_CC
CC := gcc
else
CC := $_FORCE_CC
endif

ifeq ($(OSNAME), cygming)
RC := windres
endif

ifdef TARGET_OS
CXX := ${TARGET_OS}-${CXX}
CC := ${TARGET_OS}-${CC}
AS := ${TARGET_OS}-${AS}
endif

ifeq ($(OSNAME), darwin)
CXX_VERSION := $(shell ${CXX} -dumpversion)
# TODO: ensure PANTHER's gcc compatibility...
CXX_VERSION_MAJOR := $(shell ${CXX} -dumpversion | awk 'BEGIN { FS = "."; } { print $1; }')
CXX_VERSION_MINOR := $(shell ${CXX} -dumpversion | awk 'BEGIN { FS = "."; } { print $2; }')
CXX_VERSION_PATCH := $(shell ${CXX} -dumpversion | awk 'BEGIN { FS = "."; } { print $3; }')
# This is to differentiate Apple-builded compiler from original
# compiler (it's has different behaviour)
ifneq ("$(shell ${CXX} -v 2>&1 | grep Apple)", "")
GCC_APPLE_CC := 1
endif
else
CXX_VERSION := $(shell ${CXX} --version | grep GCC | awk '{ print $$3; }')

ifeq ($(CXX_VERSION),)
# 2.95 report only version
CXX_VERSION := $(shell ${CXX} --version)
endif

CXX_VERSION_MAJOR := $(shell echo ${CXX_VERSION} | awk 'BEGIN { FS = "."; } { print $$1; }')
CXX_VERSION_MINOR := $(shell echo ${CXX_VERSION} | awk 'BEGIN { FS = "."; } { print $$2; }')
CXX_VERSION_PATCH := $(shell echo ${CXX_VERSION} | awk 'BEGIN { FS = "."; } { print $$3; }')
endif

DEFS ?=
OPT ?=

ifdef WITHOUT_STLPORT
INCLUDES =
else
INCLUDES = -I${STLPORT_INCLUDE_DIR}
endif

ifdef BOOST_INCLUDE_DIR
INCLUDES += -I${BOOST_INCLUDE_DIR}
endif

OUTPUT_OPTION = -o $@
LINK_OUTPUT_OPTION = ${OUTPUT_OPTION}
CPPFLAGS = $(DEFS) $(INCLUDES)

ifeq ($(OSNAME), cygming)
RCFLAGS = --include-dir=${STLPORT_INCLUDE_DIR} --output-format coff -DCOMP=gcc
release-shared : RCFLAGS += -DBUILD_INFOS=-O2
dbg-shared : RCFLAGS += -DBUILD=g -DBUILD_INFOS=-g
stldbg-shared : RCFLAGS += -DBUILD=stlg -DBUILD_INFOS="-g -D_STLP_DEBUG"
RC_OUTPUT_OPTION = -o $@
CXXFLAGS = -Wall -Wsign-promo -Wcast-qual -fexceptions -fident
ifndef STLP_BUILD_NO_THREAD
ifeq ($(OSREALNAME), mingw)
CCFLAGS += -mthreads
CFLAGS += -mthreads
CXXFLAGS += -mthreads
else
DEFS += -D_REENTRANT
endif
endif
CCFLAGS += $(OPT)
CFLAGS += $(OPT)
CXXFLAGS += $(OPT)
COMPILE.rc = $(RC) $(RCFLAGS)
release-static : DEFS += -D_STLP_USE_STATIC_LIB
dbg-static : DEFS += -D_STLP_USE_STATIC_LIB
stldbg-static : DEFS += -D_STLP_USE_STATIC_LIB
ifeq ($(OSREALNAME), mingw)
dbg-shared : DEFS += -D_DEBUG
stldbg-shared : DEFS += -D_DEBUG
dbg-static : DEFS += -D_DEBUG
stldbg-static : DEFS += -D_DEBUG
endif
endif

ifeq ($(OSNAME),sunos)
CCFLAGS = -pthreads $(OPT)
CFLAGS = -pthreads $(OPT)
# CXXFLAGS = -pthreads -nostdinc++ -fexceptions -fident $(OPT)
CXXFLAGS = -pthreads  -fexceptions -fident $(OPT)
endif

ifeq ($(OSNAME),linux)
CCFLAGS = -pthread $(OPT)
CFLAGS = -pthread $(OPT)
# CXXFLAGS = -pthread -nostdinc++ -fexceptions -fident $(OPT)
CXXFLAGS = -pthread -fexceptions -fident $(OPT)
endif

ifeq ($(OSNAME),openbsd)
CCFLAGS = -pthread $(OPT)
CFLAGS = -pthread $(OPT)
# CXXFLAGS = -pthread -nostdinc++ -fexceptions -fident $(OPT)
CXXFLAGS = -pthread -fexceptions -fident $(OPT)
endif

ifeq ($(OSNAME),freebsd)
CCFLAGS = -pthread $(OPT)
CFLAGS = -pthread $(OPT)
DEFS += -D_REENTRANT
# CXXFLAGS = -pthread -nostdinc++ -fexceptions -fident $(OPT)
CXXFLAGS = -pthread -fexceptions -fident $(OPT)
endif

ifeq ($(OSNAME),darwin)
CCFLAGS = $(OPT)
CFLAGS = $(OPT)
DEFS += -D_REENTRANT
CXXFLAGS = -fexceptions $(OPT)
release-shared : CXXFLAGS += -dynamic
dbg-shared : CXXFLAGS += -dynamic
stldbg-shared : CXXFLAGS += -dynamic
endif

ifeq ($(OSNAME),hp-ux)
CCFLAGS = -pthread $(OPT)
CFLAGS = -pthread $(OPT)
# CXXFLAGS = -pthread -nostdinc++ -fexceptions -fident $(OPT)
CXXFLAGS = -pthread -fexceptions -fident $(OPT)
endif

ifeq ($(CXX_VERSION_MAJOR),2)
CXXFLAGS += -ftemplate-depth-32
endif

# Required for correct order of static objects dtors calls:
ifeq ("$(findstring $(OSNAME),darwin cygming)","")
ifneq ($(CXX_VERSION_MAJOR),2)
CXXFLAGS += -fuse-cxa-atexit
endif
endif

# Code should be ready for this option
ifneq ($(OSNAME),cygming)
ifneq ($(CXX_VERSION_MAJOR),2)
ifneq ($(CXX_VERSION_MAJOR),3)
CXXFLAGS += -fvisibility=hidden
CFLAGS += -fvisibility=hidden
endif
endif
endif

ifdef EXTRA_CXXFLAGS
CXXFLAGS += ${EXTRA_CXXFLAGS}
endif

CDEPFLAGS = -E -M
CCDEPFLAGS = -E -M

# STLport DEBUG mode specific defines
stldbg-static :	    DEFS += -D_STLP_DEBUG
stldbg-shared :     DEFS += -D_STLP_DEBUG
stldbg-static-dep : DEFS += -D_STLP_DEBUG
stldbg-shared-dep : DEFS += -D_STLP_DEBUG

# optimization and debug compiler flags
release-static : OPT += -O2
release-shared : OPT += -O2

dbg-static : OPT += -g
dbg-shared : OPT += -g
#dbg-static-dep : OPT += -g
#dbg-shared-dep : OPT += -g

stldbg-static : OPT += -g
stldbg-shared : OPT += -g
#stldbg-static-dep : OPT += -g
#stldbg-shared-dep : OPT += -g

# dependency output parser (dependencies collector)

DP_OUTPUT_DIR = | sed 's|\($*\)\.o[ :]*|$(OUTPUT_DIR)/\1.o $@ : |g' > $@; \
                           [ -s $@ ] || rm -f $@

DP_OUTPUT_DIR_DBG = | sed 's|\($*\)\.o[ :]*|$(OUTPUT_DIR_DBG)/\1.o $@ : |g' > $@; \
                           [ -s $@ ] || rm -f $@

DP_OUTPUT_DIR_STLDBG = | sed 's|\($*\)\.o[ :]*|$(OUTPUT_DIR_STLDBG)/\1.o $@ : |g' > $@; \
                           [ -s $@ ] || rm -f $@

