#
# compiler
#
CC = KCC
CXX = $(CC)

#
# Basename for libraries
#
LIB_BASENAME = libstlport_kcc

#
# guts for common stuff
#
#

WARNING_FLAGS= --one_per --thread_safe +K0 --exceptions --abstract_pointer

CXXFLAGS_COMMON = -I${STLPORT_DIR} ${WARNING_FLAGS}

LINK=ar crv
DYN_LINK=KCC ${CXXFLAGS_COMMON} -o

OBJEXT=o
DYNEXT=so
STEXT=a
RM=rm -rf
PATH_SEP=/
MKDIR=mkdir -p
COMP=KAI${ARCH}
INSTALL_STEP = install_unix 

all: all_dynamic symbolic_links all_static

include common_macros.mak

CXXFLAGS_RELEASE_static = $(CXXFLAGS_COMMON) -O2
CXXFLAGS_RELEASE_dynamic = $(CXXFLAGS_COMMON) -O2  -KPIC

CXXFLAGS_DEBUG_static = $(CXXFLAGS_COMMON) -g
CXXFLAGS_DEBUG_dynamic = $(CXXFLAGS_COMMON) -g  -KPIC

CXXFLAGS_STLDEBUG_static = $(CXXFLAGS_DEBUG_static) -D_STLP_DEBUG
CXXFLAGS_STLDEBUG_dynamic = $(CXXFLAGS_DEBUG_dynamic) -D_STLP_DEBUG -fpic

include common_percent_rules.mak
include common_rules.mak


#install: all
#	cp -p $(LIB_TARGET) ${D_LIB_TARGET} ../lib

#%.s: %.cpp
#	$(CXX) $(CXXFLAGS) -O4 -S -pto $<  -o $@


