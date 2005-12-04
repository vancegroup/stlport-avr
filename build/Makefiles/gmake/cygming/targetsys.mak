# Time-stamp: <05/09/09 21:03:45 ptr>
# $Id$

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
AR := lib
else
ifeq (bcc,$(COMPILER_NAME))
ARCH := lib
AR := tlib
else
ARCH := a
AR := ar
AR_INS_R := -rs
AR_EXTR := -x
AR_OUT = $@
endif
endif
