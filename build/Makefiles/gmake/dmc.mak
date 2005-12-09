# Time-stamp: <03/11/30 11:46:14 ptr>
# $Id$

#INCLUDES :=

CXX := dmc
# For the C compiler we force cpp build otherwise wchar_t is not
# supported
CC := dmc
RC := rcc

DEFS ?=
OPT ?=

CFLAGS = -Aa -Ab -Ae -Aw -w- -p
CXXFLAGS = -Aa -Ab -Ae -Aw -w- -p

release-shared : OPT += -WD
dbg-shared : OPT += -WD
stldbg-shared : OPT += -WD

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

OUTPUT_OPTION = -o$@
LINK_OUTPUT_OPTION = -o$(subst /,\,$@)
CPPFLAGS = $(DEFS) $(OPT) $(INCLUDES) 

CDEPFLAGS = -E -M
CCDEPFLAGS = -E -M
RCFLAGS = -32 -I${STLPORT_INCLUDE_DIR} -DCOMP=dmc

release-shared : RCFLAGS += -DBUILD=r -DBUILD_INFOS="-o"
dbg-shared : RCFLAGS += -DBUILD=g -DBUILD_INFOS="-g"
stldbg-shared : RCFLAGS += -DBUILD=stlg -DBUILD_INFOS="-g -D_STLP_DEBUG"
RC_OUTPUT_OPTION = $(OUTPUT_OPTION)

COMPILE.rc = ${RC} ${RCFLAGS}

# STLport DEBUG mode specific defines
stldbg-static :	    DEFS += -D_STLP_DEBUG
stldbg-shared :     DEFS += -D_STLP_DEBUG
stldbg-static-dep : DEFS += -D_STLP_DEBUG
stldbg-shared-dep : DEFS += -D_STLP_DEBUG

# optimization and debug compiler flags
release-static : OPT += -o
release-shared : OPT += -o

dbg-static : OPT += -g
dbg-shared : OPT += -g
stldbg-static : OPT += -g
stldbg-shared : OPT += -g

release-static : AR += -p256
dbg-static : AR += -p1024
stldbg-static : AR += -p2048

# dependency output parser (dependencies collector)

DP_OUTPUT_DIR = | sed 's|\($*\)\.o[ :]*|$(OUTPUT_DIR)/\1.o $@ : |g' > $@; \
                           [ -s $@ ] || rm -f $@

DP_OUTPUT_DIR_DBG = | sed 's|\($*\)\.o[ :]*|$(OUTPUT_DIR_DBG)/\1.o $@ : |g' > $@; \
                           [ -s $@ ] || rm -f $@

DP_OUTPUT_DIR_STLDBG = | sed 's|\($*\)\.o[ :]*|$(OUTPUT_DIR_STLDBG)/\1.o $@ : |g' > $@; \
                           [ -s $@ ] || rm -f $@

