# -*- Makefile -*- Time-stamp: <08/06/12 16:25:17 ptr>

SRCROOT := ../..
COMPILER_NAME := CC
-include ${SRCROOT}/Makefiles/gmake/config.mak
ALL_TAGS = release-shared check-release-shared dbg-shared check-dbg-shared
CHECK_TAGS = check-release-shared check-dbg-shared
ifndef WITHOUT_STLPORT
ALL_TAGS += stldbg-shared check-stldbg-shared
CHECK_TAGS += check-stldbg-shared
endif
STLPORT_DIR ?= ../..

STLPORT_INCLUDE_DIR = $(STLPORT_DIR)/stlport
STLPORT_ABS_INCLUDE_DIR := $(shell cd $(STLPORT_DIR) && pwd)/stlport
include Makefile.inc
include ${SRCROOT}/Makefiles/gmake/top.mak

ifdef WITHOUT_STLPORT
DEFS += -DWITHOUT_STLPORT
endif

dbg-shared:	DEFS += -D_STLP_DEBUG_UNINITIALIZED
ifndef WITHOUT_STLPORT
stldbg-shared:	DEFS += -D_STLP_DEBUG_UNINITIALIZED
endif

INCLUDES += -I$(STLPORT_ABS_INCLUDE_DIR)

ifdef STLP_BUILD_BOOST_PATH
INCLUDES += -I${STLP_BUILD_BOOST_PATH}
endif

ifndef WITHOUT_STLPORT
release-shared: STLPORT_LIB_DIR = ${STLPORT_DIR}/src/${OUTPUT_DIR}
dbg-shared:     STLPORT_LIB_DIR = ${STLPORT_DIR}/src/${OUTPUT_DIR_DBG}
stldbg-shared:  STLPORT_LIB_DIR = ${STLPORT_DIR}/src/${OUTPUT_DIR_STLDBG}
endif

check-release-shared:	release-shared
	-${OUTPUT_DIR}/${PRGNAME}

check-dbg-shared:	dbg-shared
	-${OUTPUT_DIR_DBG}/${PRGNAME}

ifndef WITHOUT_STLPORT
check-stldbg-shared:	stldbg-shared
	-${OUTPUT_DIR_STLDBG}/${PRGNAME}
endif

check:	${CHECK_TAGS}

