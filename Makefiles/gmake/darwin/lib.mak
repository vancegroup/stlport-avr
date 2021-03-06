# -*- makefile -*- Time-stamp: <06/11/02 10:37:02 ptr>
#
# Copyright (c) 1997-1999, 2002, 2003, 2005, 2006
# Petr Ovtchenkov
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

DBG_SUFFIX ?= g
STLDBG_SUFFIX ?= stl${DBG_SUFFIX}

# Shared libraries:

SO_NAME        := lib${LIBNAME}.$(SO)
SO_NAMEx       := lib${LIBNAME}.${MAJOR}.$(SO)
SO_NAMExx      := lib${LIBNAME}.${MAJOR}.${MINOR}.$(SO)
SO_NAMExxx     := lib${LIBNAME}.${MAJOR}.${MINOR}.${PATCH}.$(SO)

SO_NAME_OUT    := $(OUTPUT_DIR)/${SO_NAME}
SO_NAME_OUTx   := $(OUTPUT_DIR)/${SO_NAMEx}
SO_NAME_OUTxx  := $(OUTPUT_DIR)/${SO_NAMExx}
SO_NAME_OUTxxx := $(OUTPUT_DIR)/${SO_NAMExxx}

SO_NAME_DBG    := lib${LIBNAME}${DBG_SUFFIX}.$(SO)
SO_NAME_DBGx   := lib${LIBNAME}${DBG_SUFFIX}.${MAJOR}.$(SO)
SO_NAME_DBGxx  := lib${LIBNAME}${DBG_SUFFIX}.${MAJOR}.${MINOR}.$(SO)
SO_NAME_DBGxxx := lib${LIBNAME}${DBG_SUFFIX}.${MAJOR}.${MINOR}.${PATCH}.$(SO)

SO_NAME_OUT_DBG    := $(OUTPUT_DIR_DBG)/${SO_NAME_DBG}
SO_NAME_OUT_DBGx   := $(OUTPUT_DIR_DBG)/${SO_NAME_DBGx}
SO_NAME_OUT_DBGxx  := $(OUTPUT_DIR_DBG)/${SO_NAME_DBGxx}
SO_NAME_OUT_DBGxxx := $(OUTPUT_DIR_DBG)/${SO_NAME_DBGxxx}

ifndef WITHOUT_STLPORT
SO_NAME_STLDBG    := lib${LIBNAME}${STLDBG_SUFFIX}.$(SO)
SO_NAME_STLDBGx   := lib${LIBNAME}${STLDBG_SUFFIX}.${MAJOR}.$(SO)
SO_NAME_STLDBGxx  := lib${LIBNAME}${STLDBG_SUFFIX}.${MAJOR}.${MINOR}.$(SO)
SO_NAME_STLDBGxxx := lib${LIBNAME}${STLDBG_SUFFIX}.${MAJOR}.${MINOR}.${PATCH}.$(SO)

SO_NAME_OUT_STLDBG    := $(OUTPUT_DIR_STLDBG)/${SO_NAME_STLDBG}
SO_NAME_OUT_STLDBGx   := $(OUTPUT_DIR_STLDBG)/${SO_NAME_STLDBGx}
SO_NAME_OUT_STLDBGxx  := $(OUTPUT_DIR_STLDBG)/${SO_NAME_STLDBGxx}
SO_NAME_OUT_STLDBGxxx := $(OUTPUT_DIR_STLDBG)/${SO_NAME_STLDBGxxx}
# WITHOUT_STLPORT
endif

# Static libraries:

A_NAME := lib${LIBNAME}.$(ARCH)
A_NAME_OUT := $(OUTPUT_DIR_A)/$(A_NAME)

A_NAME_DBG := lib${LIBNAME}${DBG_SUFFIX}.$(ARCH)
A_NAME_OUT_DBG := $(OUTPUT_DIR_A_DBG)/$(A_NAME_DBG)

ifndef WITHOUT_STLPORT
A_NAME_STLDBG := lib${LIBNAME}${STLDBG_SUFFIX}.$(ARCH)
A_NAME_OUT_STLDBG := $(OUTPUT_DIR_A_STLDBG)/$(A_NAME_STLDBG)
endif
