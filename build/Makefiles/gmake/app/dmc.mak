# -*- Makefile -*- Time-stamp: <07/05/31 01:05:57 ptr>
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

CXXFLAGS += -w6 -w7 -w18

stldbg-shared : CXXFLAGS += -HP50
stldbg-static : CXXFLAGS += -HP50

OPT += -WA

release-shared: LDFLAGS += 
release-static: LDFLAGS += 
dbg-shared : LDFLAGS += /CODEVIEW/NOCVPACK
dbg-static : LDFLAGS += /CODEVIEW/NOCVPACK
stldbg-shared : LDFLAGS += /CODEVIEW/NOCVPACK
stldbg-static : LDFLAGS += /CODEVIEW/NOCVPACK

# workaround for stl/config/_auto_link.h
STL_LIBNAME = stlport
DBG_SUFFIX := g
STLDBG_SUFFIX := stlg

ifdef STLP_BUILD_LIB_MOTIF
LIB_SUFFIX := _$(STLP_BUILD_LIB_MOTIF).${LIBMAJOR}.${LIBMINOR}
else
LIB_SUFFIX := .${LIBMAJOR}.${LIBMINOR}
endif

# Shared libraries:
ifdef STLP_BUILD_FORCE_STATIC_RUNTIME
LIB_TYPE := _x
else
LIB_TYPE := 
endif

LIB_NAME := $(LIB_PREFIX)${STL_LIBNAME}${LIB_TYPE}${LIB_SUFFIX}.$(LIB)
LIB_NAME_DBG := $(LIB_PREFIX)${STL_LIBNAME}${DBG_SUFFIX}${LIB_TYPE}${LIB_SUFFIX}.$(LIB)
LIB_NAME_STLDBG := $(LIB_PREFIX)${STL_LIBNAME}${STLDBG_SUFFIX}${LIB_TYPE}${LIB_SUFFIX}.$(LIB)

# Static libraries:
ifdef STLP_BUILD_FORCE_DYNAMIC_RUNTIME
A_LIB_TYPE := _statix
else
A_LIB_TYPE := _static
endif

A_NAME := $(LIB_PREFIX)${STL_LIBNAME}${A_LIB_TYPE}${LIB_SUFFIX}.$(ARCH)
A_NAME_DBG := $(LIB_PREFIX)${STL_LIBNAME}${DBG_SUFFIX}${A_LIB_TYPE}${LIB_SUFFIX}.${ARCH}
A_NAME_STLDBG := ${LIB_PREFIX}${STL_LIBNAME}${STLDBG_SUFFIX}${A_LIB_TYPE}${LIB_SUFFIX}.${ARCH}

ifndef STLP_BUILD_FORCE_STATIC_RUNTIME
release-shared : LDLIBS += $(CURDIR)\..\..\..\lib\$(LIB_NAME)
dbg-shared : LDLIBS += $(CURDIR)\..\..\..\lib\$(LIB_NAME_DBG)
stldbg-shared : LDLIBS += $(CURDIR)\..\..\..\lib\$(LIB_NAME_STLDBG)
else
release-shared : LDLIBS += $(CURDIR)\..\..\..\lib\$(A_NAME)
dbg-shared : LDLIBS += $(CURDIR)\..\..\..\lib\$(A_NAME_DBG)
stldbg-shared : LDLIBS += $(CURDIR)\..\..\..\lib\$(A_NAME_STLDBG)
endif
ifndef STLP_BUILD_FORCE_DYNAMIC_RUNTIME
release-static : LDLIBS += $(CURDIR)\..\..\..\lib\$(A_NAME)
dbg-static : LDLIBS += $(CURDIR)\..\..\..\lib\$(A_NAME_DBG)
stldbg-static : LDLIBS += $(CURDIR)\..\..\..\lib\$(A_NAME_STLDBG)
else
release-static : LDLIBS += $(CURDIR)\..\..\..\lib\$(LIB_NAME)
dbg-static : LDLIBS += $(CURDIR)\..\..\..\lib\$(LIB_NAME_DBG)
stldbg-static : LDLIBS += $(CURDIR)\..\..\..\lib\$(LIB_NAME_STLDBG)
endif

