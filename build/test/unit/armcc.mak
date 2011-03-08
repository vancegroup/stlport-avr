# -*- Makefile -*- Time-stamp: <08/06/06 11:01:34 yeti>
AR := armar
ifndef _FORCE_CXX
CXX := armcc
else
CXX := ${_FORCE_CXX}
endif

ifndef _FORCE_CC
CC := armcc
else
CC := ${_FORCE_CC}
endif

LINK := armlink
CFLAGS = --exceptions --cpp --fpmode=ieee_full -D__USE_C99_MATH
CXXFLAGS = --exceptions --cpp --fpmode=ieee_full -D__USE_C99_MATH

SRCROOT := ../..
COMPILER_NAME := armcc
#NOT_USE_NOSTDLIB := 1
#WITHOUT_STLPORT := 1
include ${SRCROOT}/Makefiles/gmake/config.mak
ALL_TAGS = release-shared check-release
CHECK_TAGS = check-release
ifndef WITHOUT_STLPORT
ALL_TAGS += stldbg-shared check-stldbg
CHECK_TAGS += check-stldbg
endif
STLPORT_DIR ?= ../../..

include Makefile.inc
include ${SRCROOT}/Makefiles/gmake/top.mak

ifdef WITHOUT_STLPORT
DEFS += -DWITHOUT_STLPORT
endif

dbg-shared:	DEFS += -D_STLP_DEBUG_UNINITIALIZED
ifndef WITHOUT_STLPORT
stldbg-shared:	DEFS += -D_STLP_DEBUG_UNINITIALIZED
endif

ifdef STLP_BUILD_BOOST_PATH
INCLUDES += -I${STLP_BUILD_BOOST_PATH}
endif

ifndef TARGET_OS
ifndef WITHOUT_STLPORT

ifeq ($(OSNAME), linux)
release-shared: LDFLAGS += -L${STLPORT_DIR}/build/lib/${OUTPUT_DIR_STLDBG}/libstlportstlg.a
dbg-shared:	LDFLAGS += -L${STLPORT_DIR}/build/lib/${OUTPUT_DIR_STLDBG}/libstlportstlg.a
stldbg-shared:	LDFLAGS += -L${STLPORT_DIR}/build/lib/${OUTPUT_DIR_STLDBG}/libstlportstlg.a
endif
endif
endif

check-release:	release-shared
	${ARM_MODEL} ${OUTPUT_DIR}/${PRGNAME}

ifndef WITHOUT_STLPORT
check-stldbg:	stldbg-shared
	${ARM_MODEL} ${OUTPUT_DIR_STLDBG}/${PRGNAME}
endif

check:	${CHECK_TAGS}

