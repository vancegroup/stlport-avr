# -*- Makefile -*- Time-stamp: <08/06/06 11:01:34 yeti>

SRCROOT := ../..
COMPILER_NAME := gcc
#NOT_USE_NOSTDLIB := 1
#WITHOUT_STLPORT := 1
-include ${SRCROOT}/Makefiles/gmake/config.mak
ALL_TAGS = release-shared check-release
CHECK_TAGS = check-release
ifndef WITHOUT_STLPORT
ALL_TAGS += stldbg-shared check-stldbg
CHECK_TAGS += check-stldbg
endif
STLPORT_DIR := ../../..

include Makefile.inc
include ${SRCROOT}/Makefiles/gmake/top.mak

release-shared: STLPORT_LIB_DIR = ${SRCROOT}/lib/${OUTPUT_DIR}
dbg-shared:     STLPORT_LIB_DIR = ${SRCROOT}/lib/${OUTPUT_DIR_DBG}
ifndef WITHOUT_STLPORT
stldbg-shared:  STLPORT_LIB_DIR = ${SRCROOT}/lib/${OUTPUT_DIR_STLDBG}
endif

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
ifeq ($(OSNAME), sunos)
LDFLAGS += -Wl,-R${STLPORT_LIB_DIR}
endif
ifeq ($(OSNAME), freebsd)
LDFLAGS += -Wl,-R${STLPORT_LIB_DIR}
endif
ifeq ($(OSNAME), openbsd)
LDFLAGS += -Wl,-R${STLPORT_LIB_DIR}
endif
ifeq ($(OSNAME), linux)
LDFLAGS += -Wl,-rpath=${STLPORT_LIB_DIR}
endif
ifeq ($(OSNAME), hp-ux)
LDFLAGS += -Wl,+b${STLPORT_LIB_DIR}
endif
endif
endif

check-release:	release-shared
	-${OUTPUT_DIR}/${PRGNAME}

ifndef WITHOUT_STLPORT
check-stldbg:	stldbg-shared
	-${OUTPUT_DIR_STLDBG}/${PRGNAME}
endif

check:	${CHECK_TAGS}

