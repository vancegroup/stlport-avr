#
# Note : this makefile is for gcc-2.95 and later !
#

#
# compiler
#
CC = gcc
CXX = /lang/cygnus/99r1/bin/c++ -pthreads

#
# Basename for libraries
#
LIB_BASENAME = libstlport_gcc

#
# guts for common stuff
#
#
LINK=ar cr
# 2.95 flag
DYN_LINK=/lang/cygnus/99r1/bin/c++ -pthreads -shared -o

OBJEXT=o
DYNEXT=so
STEXT=a
RM=rm -rf
PATH_SEP=/
MKDIR=mkdir -p
COMP=GCC-SUN
INSTALL_STEP = install_unix 

all: symbolic_links all_dynamic all_static

include common_macros.mak

WARNING_FLAGS= -Wall -W -Wno-sign-compare -Wno-unused -Wno-uninitialized

CXXFLAGS_COMMON =  -nostdinc++ -fexceptions -ftemplate-depth-32 -shared -I${STLPORT_DIR} ${WARNING_FLAGS}

CXXFLAGS_RELEASE_static = $(CXXFLAGS_COMMON) -O2
CXXFLAGS_RELEASE_dynamic = $(CXXFLAGS_COMMON) -O2 -fPIC

CXXFLAGS_DEBUG_static = $(CXXFLAGS_COMMON) -gstabs
CXXFLAGS_DEBUG_dynamic = $(CXXFLAGS_COMMON) -gstabs -fPIC

CXXFLAGS_STLDEBUG_static = $(CXXFLAGS_DEBUG_static) -D_STLP_DEBUG
CXXFLAGS_STLDEBUG_dynamic = $(CXXFLAGS_DEBUG_dynamic) -D_STLP_DEBUG

LDFLAGS_RELEASE_dynamic = ${CXXFLAGS_RELEASE_dynamic} -Wl,-soname,${RELEASE_DYNLIB_SONAME}

LDFLAGS_DEBUG_dynamic = ${CXXFLAGS_DEBUG_dynamic} -Wl,-soname,${DEBUG_DYNLIB_SONAME}

LDFLAGS_STLDEBUG_dynamic = ${CXXFLAGS_STLDEBUG_dynamic} -Wl,-soname,${STLDEBUG_DYNLIB_SONAME}

include common_percent_rules.mak
include common_rules.mak

#%.s: %.cpp
#	$(CXX) $(CXXFLAGS) -O4 -S -pto $<  -o $@


