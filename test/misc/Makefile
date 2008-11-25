# -*- Makefile -*- Time-stamp: <08/10/25 00:51:14 ptr>

SRCROOT := ../..

ALL_TAGS := release-shared dbg-shared stldbg-shared

include Makefile.inc
include ${SRCROOT}/Makefiles/gmake/top.mak

STLPORT_DIR := ../..

INCLUDES += -I../include
# DEFS += -D_STLP_DESIGNATED_DLL
# CXXFLAGS += -fvisibility=hidden

release-shared:	LDFLAGS += -L${SRCROOT}/src/${OUTPUT_DIR}

dbg-shared:	LDFLAGS += -L${SRCROOT}/src/${OUTPUT_DIR_DBG}

ifndef WITHOUT_STLPORT
stldbg-shared:	LDFLAGS += -L${SRCROOT}/src/${OUTPUT_DIR_STLDBG}
endif
