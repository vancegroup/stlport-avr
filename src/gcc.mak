#
# Note : this makefile is for gcc-2.95 and later !
#

#
# compiler
#
CC = gcc 
CXX = g++ 

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
DYN_LINK=g++ -shared -o

OBJEXT=o
DYNEXT=so
STEXT=a
RM=rm -rf
PATH_SEP=/
MKDIR=mkdir -p
COMP=GCC$(ARCH)
INSTALL_STEP = install_unix 

all:  all_dynamic all_static symbolic_links 

include common_macros.mak

WARNING_FLAGS= -Wall -W -Wno-sign-compare -Wno-unused -Wno-uninitialized -ftemplate-depth-32

CXXFLAGS_COMMON = -pthread -fexceptions -I${STLPORT_DIR} ${WARNING_FLAGS}

ifdef STLP_BUILD_BOOST_PATH
CXXFLAGS_COMMON += -I$(STLP_BUILD_BOOST_PATH) -DBOOST_STDLIB_CONFIG="<boost/config/stdlib/stlport.hpp>"
endif

CXXFLAGS_RELEASE_static = $(CXXFLAGS_COMMON) -O4
CXXFLAGS_RELEASE_dynamic = $(CXXFLAGS_COMMON) -O4 -fPIC
#CXXFLAGS_RELEASE_static = $(CXXFLAGS_COMMON) -g -O3
#CXXFLAGS_RELEASE_dynamic = $(CXXFLAGS_COMMON) -g -O3 -fPIC

CXXFLAGS_DEBUG_static = $(CXXFLAGS_COMMON) -g
CXXFLAGS_DEBUG_dynamic = $(CXXFLAGS_COMMON) -g -fPIC

CXXFLAGS_STLDEBUG_static = $(CXXFLAGS_DEBUG_static) -D_STLP_DEBUG
CXXFLAGS_STLDEBUG_dynamic = $(CXXFLAGS_DEBUG_dynamic) -D_STLP_DEBUG

include common_percent_rules.mak
include common_rules.mak


