#
# Note : this makefile is for gcc-2.95 and later !
#

#
# compiler
#
CC = gcc
CXX = c++ -pthreads

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
DYN_LINK=c++ -pthreads -shared -o

OBJEXT=o
DYNEXT=so
STEXT=a
RM=rm -rf
PATH_SEP=/
MKDIR=mkdir -p
COMP=GCC-SUN
INSTALL_STEP = install_unix 

all: all_dynamic all_static

include common_macros.mak

WARNING_FLAGS= -Wall -W -Wno-sign-compare -Wno-unused -Wno-uninitialized

CXXFLAGS_COMMON =  -nostdinc++ -fexceptions -ftemplate-depth-32 -shared -I${STLPORT_DIR} ${WARNING_FLAGS}

CXXFLAGS_RELEASE_static = $(CXXFLAGS_COMMON) -O2 -fno-implement-inlines
CXXFLAGS_RELEASE_dynamic = $(CXXFLAGS_COMMON) -O2 -fPIC -fno-implement-inlines

CXXFLAGS_DEBUG_static = $(CXXFLAGS_COMMON) -gstabs
CXXFLAGS_DEBUG_dynamic = $(CXXFLAGS_COMMON) -gstabs -fPIC

CXXFLAGS_STLDEBUG_static = $(CXXFLAGS_DEBUG_static) -D__STL_DEBUG
CXXFLAGS_STLDEBUG_dynamic = $(CXXFLAGS_DEBUG_dynamic) -D__STL_DEBUG

include common_percent_rules.mak
include common_rules.mak

#%.s: %.cpp
#	$(CXX) $(CXXFLAGS) -O4 -S -pto $<  -o $@


