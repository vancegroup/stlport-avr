# Time-stamp: <10/06/02 15:17:35 ptr>
#
# Copyright (c) 1997-1999, 2002, 2003, 2005-2008
# Petr Ovtchenkov
#
# This material is provided "as is", with absolutely no warranty expressed
# or implied. Any use is at your own risk.
#
# Permission to use or copy this software for any purpose is hereby granted
# without fee, provided the above notices are retained on all copies.
# Permission to modify the code and to distribute modified code is granted,
# provided the above notices are retained, and a notice that the code was
# modified is included with the above copyright notice.
#

INCLUDES :=

ifndef _FORCE_CXX
CXX := CC
else
CXX := ${_FORCE_CXX}
endif

ifndef _FORCE_CC
CC := cc
else
CC := ${_FORCE_CC}
endif

CXX_VERSION := $(shell ${CXX} -V 2>&1 | grep ${CXX} | awk '{ print $$4; }')

CXX_VERSION_MAJOR := $(shell echo ${CXX_VERSION} | awk 'BEGIN { FS = "."; } { print $$1; }')
CXX_VERSION_MINOR := $(shell echo ${CXX_VERSION} | awk 'BEGIN { FS = "."; } { print $$2; }')
CXX_VERSION_PATCH := $(shell echo ${CXX_VERSION} | awk 'BEGIN { FS = "."; } { if (NF > 2) {print $$3;}else{print "0"} }')

DEFS ?=
OPT ?=

OUTPUT_OPTION = -o $@
LINK_OUTPUT_OPTION = ${OUTPUT_OPTION}
CPPFLAGS = $(DEFS) $(INCLUDES)

OPT += -mt +w2
CFLAGS = -errtags -xildoff $(OPT) $(EXTRA_CFLAGS)
# diffenumtype warnings seem bogus.
# inllargeuse is not important.
# reftotemp can issue warnings about code from the C++ standard.
CXXFLAGS = -errtags -erroff=doubunder,diffenumtype,inllargeuse,reftotemp,notemsource -qoption ccfe -expand=1000 -library=no%Cstd,no%iostream,no%rwtools7 -xildoff $(OPT) $(EXTRA_CXXFLAGS)
CDEPFLAGS = -xM
CCDEPFLAGS = -xM

# STLport DEBUG mode specific defines
stldbg-static :	    DEFS += -D_STLP_DEBUG
stldbg-shared :     DEFS += -D_STLP_DEBUG
stldbg-static-dep : DEFS += -D_STLP_DEBUG
stldbg-shared-dep : DEFS += -D_STLP_DEBUG

# optimization and debug compiler flags
release-static : OPT += -xO2
release-shared : OPT += -xO2

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


