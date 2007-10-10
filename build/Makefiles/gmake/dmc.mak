# Time-stamp: <07/05/31 01:03:50 ptr>
#
# Copyright (c) 1997-1999, 2002, 2003, 2005-2007
# Petr Ovtchenkov
#
# Copyright (c) 2006, 2007
# Francois Dumont
#
# Portion Copyright (c) 1999-2001
# Parallel Graphics Ltd.
#
# Licensed under the Academic Free License version 3.0
#

ALL_TAGS = all-static all-shared
ifdef LIBNAME
INSTALL_TAGS = install-static install-shared
endif

CXX := dmc
CC := dmc

DEFS ?=
OPT ?=

CFLAGS = -Ae -C -p -3 -w6 -w12
CXXFLAGS = -Ae -C -p -3 -w12

DEFS += -DSTRICT

ifdef STLP_BUILD_FORCE_DYNAMIC_RUNTIME
release-static : OPT += -ND
dbg-static : OPT += -ND
stldbg-static : OPT += -ND
endif

ifndef STLP_BUILD_FORCE_STATIC_RUNTIME
release-shared : OPT += -ND
dbg-shared : OPT += -ND
stldbg-shared : OPT += -ND
endif

ifndef STLP_BUILD_NO_RTTI
OPT += -Ar
endif

#Add Windows target.
ifndef STLP_BUILD_WINDOWS_95
WINVER=0x0410
else
WINVER=0x0400
endif
release-shared: DEFS += -DWINVER=$(WINVER)
dbg-shared: DEFS += -DWINVER=$(WINVER)
stldbg-shared: DEFS += -DWINVER=$(WINVER)
release-static: DEFS += -DWINVER=$(WINVER)
dbg-static: DEFS += -DWINVER=$(WINVER)
stldbg-static: DEFS += -DWINVER=$(WINVER)

OUTPUT_OPTION = -o$@
LINK_OUTPUT_OPTION = $(subst /,\,$@)
CPPFLAGS = $(DEFS) $(OPT) $(INCLUDES) 

CDEPFLAGS = -E -M
CCDEPFLAGS = -E -M
RCFLAGS = --include-dir=${STLPORT_INCLUDE_DIR} -DCOMP=dmc

release-shared : RCFLAGS += -DBUILD=r -DBUILD_INFOS="-o"
dbg-shared : RCFLAGS += -DBUILD=g -DBUILD_INFOS="-gl -D_DEBUG"
stldbg-shared : RCFLAGS += -DBUILD=stlg -DBUILD_INFOS="-gl -D_STLP_DEBUG"
RC_OUTPUT_OPTION = $(OUTPUT_OPTION)

COMPILE.rc = ${RC} ${RCFLAGS}
LINK.cc = dm_link $(LDFLAGS)

LDLIBS += user32.lib kernel32.lib

# STLport DEBUG mode specific defines
dbg-static : DEFS += -D_DEBUG
dbg-shared : DEFS += -D_DEBUG
stldbg-static : DEFS += -D_DEBUG
stldbg-shared : DEFS += -D_DEBUG
dbg-static-dep : DEFS += -D_DEBUG
dbg-shared-dep : DEFS +=  -D_DEBUG
stldbg-static :	    DEFS += -D_STLP_DEBUG
stldbg-shared :     DEFS += -D_STLP_DEBUG
stldbg-static-dep : DEFS += -D_STLP_DEBUG
stldbg-shared-dep : DEFS += -D_STLP_DEBUG

# optimization and debug compiler flags
release-static : OPT += -o
release-shared : OPT += -o
dbg-static : OPT += -gl
dbg-shared : OPT += -gl
stldbg-static : OPT += -gl
stldbg-shared : OPT += -gl

release-static : OPT += -D_MT
dbg-static : OPT += -D_MT
stldbg-static : OPT += -D_MT

release-static : AR += -p128
dbg-static : AR += -p512
stldbg-static : AR += -p512

ifndef LIBNAME
ifdef STLP_BUILD_FORCE_DYNAMIC_RUNTIME
release-static: DEFS += -D_STLP_USE_STATIC_LIB
dbg-static:  DEFS += -D_STLP_USE_STATIC_LIB
stldbg-static:  DEFS += -D_STLP_USE_STATIC_LIB
endif
ifdef STLP_BUILD_FORCE_STATIC_RUNTIME
release-shared: DEFS += -D_STLP_USE_DYNAMIC_LIB
dbg-shared:  DEFS += -D_STLP_USE_DYNAMIC_LIB
stldbg-shared:  DEFS += -D_STLP_USE_DYNAMIC_LIB
endif
endif

# map output option (move map files to output dir)

ifdef LIBNAME
release-shared: MAP_OUTPUT_OPTION = $(subst /,\,$(OUTPUT_DIR))\$(SO_NAME_BASE).map
dbg-shared: MAP_OUTPUT_OPTION = $(subst /,\,$(OUTPUT_DIR_DBG))\$(SO_NAME_DBG_BASE).map
stldbg-shared: MAP_OUTPUT_OPTION = $(subst /,\,$(OUTPUT_DIR_STLDBG))\$(SO_NAME_STLDBG_BASE).map
else
release-shared: MAP_OUTPUT_OPTION = $(subst /,\,$(OUTPUT_DIR))\$(PRGNAME).map
release-static: MAP_OUTPUT_OPTION = $(subst /,\,$(OUTPUT_DIR))\$(PRGNAME).map
dbg-shared: MAP_OUTPUT_OPTION = $(subst /,\,$(OUTPUT_DIR_DBG))\$(PRGNAME).map
dbg-static: MAP_OUTPUT_OPTION = $(subst /,\,$(OUTPUT_DIR_DBG))\$(PRGNAME).map
stldbg-shared: MAP_OUTPUT_OPTION = $(subst /,\,$(OUTPUT_DIR_STLDBG))\$(PRGNAME).map
stldbg-static: MAP_OUTPUT_OPTION = $(subst /,\,$(OUTPUT_DIR_STLDBG))\$(PRGNAME).map
endif

# dependency output parser (dependencies collector)

DP_OUTPUT_DIR = | sed 's|\($*\)\.o[ :]*|$(OUTPUT_DIR)/\1.o $@ : |g' > $@; \
                           [ -s $@ ] || rm -f $@

DP_OUTPUT_DIR_DBG = | sed 's|\($*\)\.o[ :]*|$(OUTPUT_DIR_DBG)/\1.o $@ : |g' > $@; \
                           [ -s $@ ] || rm -f $@

DP_OUTPUT_DIR_STLDBG = | sed 's|\($*\)\.o[ :]*|$(OUTPUT_DIR_STLDBG)/\1.o $@ : |g' > $@; \
                           [ -s $@ ] || rm -f $@

