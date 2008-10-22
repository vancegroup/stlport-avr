# Time-stamp: <07/05/31 00:07:23 ptr>
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

CC ?= gcc
CXX ?= g++

# shared library:
SO  := dll
ifeq (gcc,$(COMPILER_NAME))
LIB := dll.a
else
LIB := lib
endif
EXP := exp

# executable:
EXE := .exe

# static library extention:
ifeq (dmc,$(COMPILER_NAME))
ARCH := lib
AR := dm_lib -n
AR_INS_R := -c
AR_EXTR := -x
AR_OUT = $(subst /,\,$@)
else
ifeq (bcc,$(COMPILER_NAME))
ARCH := lib
AR := tlib
AR_INS_R := +
AR_EXTR := *
AR_OUT = $(subst /,\,$@)
else
ARCH := a
AR := ar
AR_INS_R := -rs
AR_EXTR := -x
AR_OUT = $@
endif
endif
