#
# Basename for libraries
#
LIB_BASENAME = libstlport_forte6

STL_INCL= -I. -I${PWD}/../stlport/SC5

CC = CC
CXX = CC

#
# guts for common stuff
#
#
LINK=$(CC) -mt -xar -o
DYN_LINK=$(CC) -mt -G -o

OBJEXT=o
DYNEXT=so
STEXT=a
RM=rm -rf
PATH_SEP=/
MKDIR=mkdir -p
COMP=forte
INSTALL_STEP = install_unix 

# LINK_OUT=-xar -o  
# DYNLINK_OUT=-o 

all: all_dynamic all_static

include common_macros.mak

CXXFLAGS_COMMON = -mt -pta +w2 -features=rtti -xildoff ${STL_INCL} -D__SGI_STL_OWN_IOSTREAMS

SHCXXFLAGS = -PIC

DEBUG_FLAGS = -g +w2 -D__STL_DEBUG

#
# Try those flags to see if they help to get maximum efficiency :
# -Qoption iropt -R,-Ml30,-Ms30,-Mi1000000,-Mm1000000,-Mr1000000,-Ma1000000,-Mc1000000,-Mt1000000
RELEASE_FLAGS = -O2 +w2 -Qoption iropt -R,-Ml30,-Ms30,-Mi1000000,-Mm1000000,-Mr1000000,-Ma1000000,-Mc1000000,-Mt1000000


# install: $(TARGETS)
#	cp -p $(TARGETS) ${INSTALLDIR}

RELEASE_static_rep = -ptr${RELEASE_OBJDIR_static}
RELEASE_dynamic_rep = -ptr${RELEASE_OBJDIR_dynamic}
DEBUG_static_rep = -ptr${DEBUG_OBJDIR_static}
DEBUG_dynamic_rep = -ptr${DEBUG_OBJDIR_dynamic}
STLDEBUG_static_rep = -ptr${STLDEBUG_OBJDIR_static}
STLDEBUG_dynamic_rep = -ptr${STLDEBUG_OBJDIR_dynamic}

CXXFLAGS_RELEASE_static = $(CXXFLAGS_COMMON) ${RELEASE_FLAGS} ${RELEASE_static_rep}
CXXFLAGS_RELEASE_dynamic = $(CXXFLAGS_COMMON) ${RELEASE_FLAGS} $(SHCXXFLAGS) ${RELEASE_dynamic_rep}

CXXFLAGS_DEBUG_static = $(CXXFLAGS_COMMON) -g ${DEBUG_static_rep}
CXXFLAGS_DEBUG_dynamic = $(CXXFLAGS_COMMON) -g $(SHCXXFLAGS) ${DEBUG_dynamic_rep}

CXXFLAGS_STLDEBUG_static = $(CXXFLAGS_COMMON) -g ${STLDEBUG_static_rep} -D__STL_DEBUG
CXXFLAGS_STLDEBUG_dynamic = $(CXXFLAGS_COMMON) -g $(SHCXXFLAGS) ${STLDEBUG_dynamic_rep} -D__STL_DEBUG

LDFLAGS_RELEASE_static = ${CXXFLAGS_RELEASE_static}
LDFLAGS_RELEASE_dynamic = ${CXXFLAGS_RELEASE_dynamic}

LDFLAGS_DEBUG_static = ${CXXFLAGS_DEBUG_static}
LDFLAGS_DEBUG_dynamic = ${CXXFLAGS_DEBUG_dynamic}

LDFLAGS_STLDEBUG_static = ${CXXFLAGS_STLDEBUG_static}
LDFLAGS_STLDEBUG_dynamic = ${CXXFLAGS_STLDEBUG_dynamic}

include common_percent_rules.mak
include common_rules.mak

