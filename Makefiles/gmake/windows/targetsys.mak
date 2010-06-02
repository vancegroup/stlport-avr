# Time-stamp: <10/06/02 15:17:35 ptr>
#
# Copyright (c) 1997-1999, 2002, 2003, 2005-2007
# Petr Ovtchenkov
#
# Copyright (c) 2006, 2007
# Francois Dumont
#
# This material is provided "as is", with absolutely no warranty expressed
# or implied. Any use is at your own risk.
#
# Permission to use or copy this software for any purpose is hereby granted
# without fee, provided the above notices are retained on all copies.
# Permission to modify the code and to distribute modified code is granted,
# provided the above notices are retained, and a notice that the code was
# modified is included with the above copyright notice.
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
