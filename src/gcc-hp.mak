#
# Note : this makefile is for gcc-2.95 and later (HP-UX)!
#

#
# compiler
#
CC = gcc
CXX = c++ -pthreads
# CXX = c++ -pthreads -nostdinc++ -fexceptions -frtti -fno-implement-inlines -Winline -Wextern-inline
# -fkeep-inline-functions
# -finline-functions
# -fno-default-inline

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
# DYN_LINK=c++ -pthreads -fPIC -shared -o
# DYN_LINK=c++ -pthreads -nostdinc++ -fexceptions -frtti -fPIC -O -fno-implement-inlines -Winline -Wextern-inline -shared -D__STL_DEBUG -o
# DYN_LINK=ld -shared -export-dynamic -Bdynamic -Bsymbolic -Ur -o
DYN_LINK=ld -z -b -o

OBJEXT=o
DYNEXT=sl
STEXT=a
RM=rm -rf
PATH_SEP=/
MKDIR=mkdir -p
COMP=GCC-HP
INSTALL_STEP = install_unix 

all: all_dynamic all_static

include common_macros.mak

WARNING_FLAGS= -Wall -W -Wno-sign-compare -Wno-unused -Wno-uninitialized -ftemplate-depth-32

CXXFLAGS_COMMON = -I${STLPORT_DIR} ${WARNING_FLAGS}

CXXFLAGS_RELEASE_static = $(CXXFLAGS_COMMON) -O
CXXFLAGS_RELEASE_dynamic = $(CXXFLAGS_COMMON) -O -fPIC

CXXFLAGS_DEBUG_static = $(CXXFLAGS_COMMON) -g
CXXFLAGS_DEBUG_dynamic = $(CXXFLAGS_COMMON) -g -fPIC

CXXFLAGS_STLDEBUG_static = $(CXXFLAGS_DEBUG_static) -D__STL_DEBUG
CXXFLAGS_STLDEBUG_dynamic = $(CXXFLAGS_DEBUG_dynamic) -D__STL_DEBUG

include common_percent_rules.mak
include common_rules.mak

#install: all
#	cp -p $(LIB_TARGET) ${D_LIB_TARGET} ../lib

#%.s: %.cpp
#	$(CXX) $(CXXFLAGS) -O4 -S -pto $<  -o $@
