# Time-stamp: <05/03/21 10:42:37 ptr>
# $Id$


#INCLUDES = -I$(SRCROOT)/include
INCLUDES :=

CXX := c++
CC := gcc -ansi

ifdef TARGET_OS
CXX := ${TARGET_OS}-${CXX}
CC := ${TARGET_OS}-${CC}
endif

ifeq ($(OSNAME), darwin)
CXX_VERSION := $(shell ${CXX} -dumpversion)
# TODO: ensure PANTHER's gcc compatibility...
CXX_VERSION_MAJOR := $(shell ${CXX} -dumpversion | awk 'BEGIN { FS = "."; } { print $1; }')
CXX_VERSION_MINOR := $(shell ${CXX} -dumpversion | awk 'BEGIN { FS = "."; } { print $2; }')
CXX_VERSION_PATCH := $(shell ${CXX} -dumpversion | awk 'BEGIN { FS = "."; } { print $3; }')
else
ifneq ($(OSNAME), windows)
CXX_VERSION := $(shell ${CXX} --version | grep GCC | awk '{ print $$3; }')

ifeq ($(CXX_VERSION),)
# 2.95 report only version
CXX_VERSION := $(shell ${CXX} --version)
endif

CXX_VERSION_MAJOR := $(shell echo ${CXX_VERSION} | awk 'BEGIN { FS = "."; } { print $$1; }')
CXX_VERSION_MINOR := $(shell echo ${CXX_VERSION} | awk 'BEGIN { FS = "."; } { print $$2; }')
CXX_VERSION_PATCH := $(shell echo ${CXX_VERSION} | awk 'BEGIN { FS = "."; } { print $$3; }')
endif
endif

DEFS ?=
OPT ?=

OUTPUT_OPTION = -o $@
LINK_OUTPUT_OPTION = ${OUTPUT_OPTION}
CPPFLAGS = $(DEFS) $(INCLUDES)

ifeq ($(OSNAME), cygming)
RCFLAGS = --include-dir=${STLPORT_INCLUDE_DIR} --output-format coff -DCOMP=gcc
release-shared : RCFLAGS += -DBUILD=r -DBUILD_INFOS="-O2"
dbg-shared : RCFLAGS += -DBUILD=g -DBUILD_INFOS="-g"
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
endif

ifeq ($(OSNAME), windows)
RCFLAGS = --include-dir=${STLPORT_INCLUDE_DIR} --output-format coff -DCOMP=gcc
release-shared : RCFLAGS += -DBUILD=r -DBUILD_INFOS="-O2"
dbg-shared : RCFLAGS += -DBUILD=g -DBUILD_INFOS="-g"
stldbg-shared : RCFLAGS += -DBUILD=stlg -DBUILD_INFOS="-g -D_STLP_DEBUG"
RC_OUTPUT_OPTION = -o $@
CXXFLAGS = -Wall -Wsign-promo -Wcast-qual -fexceptions -fident
ifndef STLP_BUILD_NO_THREAD
CCFLAGS += -mthreads
CFLAGS += -mthreads
CXXFLAGS += -mthreads
endif
CCFLAGS += $(OPT)
CFLAGS += $(OPT)
CXXFLAGS += $(OPT)
COMPILE.rc = $(RC) $(RCFLAGS)
endif

ifndef STLP_BUILD_NO_THREAD
PTHREAD = -pthread
else
PTHREAD =
endif

ifeq ($(OSNAME),sunos)
CCFLAGS = $(PTHREAD) $(OPT)
CFLAGS = $(PTHREAD) $(OPT)
# CXXFLAGS = $(PTHREAD) -nostdinc++ -fexceptions -fident $(OPT)
CXXFLAGS = $(PTHREAD) -fexceptions -fident $(OPT)
endif

ifeq ($(OSNAME),linux)
CCFLAGS = $(PTHREAD) $(OPT)
CFLAGS = $(PTHREAD) $(OPT)
# CXXFLAGS = $(PTHREAD) -nostdinc++ -fexceptions -fident $(OPT)
CXXFLAGS = $(PTHREAD) -fexceptions -fident $(OPT)
endif

ifeq ($(OSNAME),openbsd)
CCFLAGS = $(PTHREAD) $(OPT)
CFLAGS = $(PTHREAD) $(OPT)
# CXXFLAGS = $(PTHREAD) -nostdinc++ -fexceptions -fident $(OPT)
CXXFLAGS = $(PTHREAD) -fexceptions -fident $(OPT)
endif

ifeq ($(OSNAME),freebsd)
CCFLAGS = $(PTHREAD) $(OPT)
CFLAGS = $(PTHREAD) $(OPT)
ifndef STLP_BUILD_NO_THREAD
DEFS += -D_REENTRANT
endif
# CXXFLAGS = $(PTHREAD) -nostdinc++ -fexceptions -fident $(OPT)
CXXFLAGS = $(PTHREAD) -fexceptions -fident $(OPT)
endif

ifeq ($(OSNAME),darwin)
CCFLAGS = $(OPT)
CFLAGS = $(OPT)
ifndef STLP_BUILD_NO_THREAD
DEFS += -D_REENTRANT
endif
CXXFLAGS = -fexceptions $(OPT)
release-shared : CXXFLAGS += -dynamic
dbg-shared : CXXFLAGS += -dynamic
stldbg-shared : CXXFLAGS += -dynamic
endif

ifeq ($(OSNAME),hp-ux)
CCFLAGS = $(PTHREAD) $(OPT)
CFLAGS = $(PTHREAD) $(OPT)
# CXXFLAGS = $(PTHREAD) -nostdinc++ -fexceptions -fident $(OPT)
CXXFLAGS = $(PTHREAD) -fexceptions -fident $(OPT)
endif

#ifeq ($(CXX_VERSION_MAJOR),3)
#ifeq ($(CXX_VERSION_MINOR),2)
#CXXFLAGS += -ftemplate-depth-32
#endif
#ifeq ($(CXX_VERSION_MINOR),1)
#CXXFLAGS += -ftemplate-depth-32
#endif
#ifeq ($(CXX_VERSION_MINOR),0)
#CXXFLAGS += -ftemplate-depth-32
#endif
#endif
ifeq ($(CXX_VERSION_MAJOR),2)
CXXFLAGS += -ftemplate-depth-32
endif

# Required for correct order of static objects dtors calls:
ifneq ($(OSNAME),cygming)
ifneq ($(OSNAME),windows)
ifneq ($(CXX_VERSION_MAJOR),2)
CXXFLAGS += -fuse-cxa-atexit
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
