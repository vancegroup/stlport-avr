
CUR_DIR= ${PWD}/

STL_INCL= -I. -I${PWD}/../stlport

#
# guts for common stuff
#
#
LINK=$(CC) -xar -o
DYN_LINK=$(CC) -G -o

OBJEXT=o
DYNEXT=so
STEXT=a
RM=rm -rf
PATH_SEP=/
MKDIR=mkdir -p
INSTALL_STEP = install_unix 
PREPARE_STEP = prepare_sunpro

all: all_dynamic symbolic_links  all_static

include common_macros.mak

CXXFLAGS_COMMON = -mt +w2 -features=rtti -xildoff ${STL_INCL}

SHCXXFLAGS = -PIC

DEBUG_FLAGS = -g +w2 -D_STLP_DEBUG

#
# Try those flags to see if they help to get maximum efficiency :
# -Qoption iropt -R,-Ml30,-Ms30,-Mi1000000,-Mm1000000,-Mr1000000,-Ma1000000,-Mc1000000,-Mt1000000
RELEASE_FLAGS = -O2 +w2 -qoption ccfe -expand=1000


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

CXXFLAGS_STLDEBUG_static = $(CXXFLAGS_COMMON) -g ${STLDEBUG_static_rep} -D_STLP_DEBUG
CXXFLAGS_STLDEBUG_dynamic = $(CXXFLAGS_COMMON) -g $(SHCXXFLAGS) ${STLDEBUG_dynamic_rep} -D_STLP_DEBUG


LDFLAGS_RELEASE_static = ${CXXFLAGS_RELEASE_static} sparc_atomic.s
LDFLAGS_RELEASE_dynamic = ${CXXFLAGS_RELEASE_dynamic} -h${RELEASE_DYNLIB_SONAME} sparc_atomic.s

LDFLAGS_DEBUG_static = ${CXXFLAGS_DEBUG_static} sparc_atomic.s
LDFLAGS_DEBUG_dynamic = ${CXXFLAGS_DEBUG_dynamic} -h${DEBUG_DYNLIB_SONAME} sparc_atomic.s

LDFLAGS_STLDEBUG_static = ${CXXFLAGS_STLDEBUG_static} sparc_atomic.s
LDFLAGS_STLDEBUG_dynamic = ${CXXFLAGS_STLDEBUG_dynamic} -h${STLDEBUG_DYNLIB_SONAME} sparc_atomic.s

LDLIBS_RELEASE_dynamic =  -lposix4
LDLIBS_STLDEBUG_dynamic = -lposix4

include common_percent_rules.mak
include common_rules.mak
