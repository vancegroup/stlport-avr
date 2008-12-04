# -*- Makefile -*- Time-stamp: <08/06/12 16:25:17 ptr>

SRCROOT := ../..
COMPILER_NAME := CC
-include ${SRCROOT}/Makefiles/gmake/config.mak
ALL_TAGS = release-shared check-release-shared
CHECK_TAGS = check-release-shared
ifndef WITHOUT_STLPORT
ALL_TAGS += stldbg-shared check-stldbg-shared
CHECK_TAGS += check-stldbg-shared
endif
STLPORT_DIR ?= ../..

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

ifndef WITHOUT_STLPORT
release-shared: LDFLAGS += -L${STLPORT_DIR}/src/${OUTPUT_DIR} -Qoption ld -R${STLPORT_DIR}/src/${OUTPUT_DIR}
dbg-shared:	LDFLAGS += -L${STLPORT_DIR}/src/${OUTPUT_DIR_DBG} -Qoption ld -R${STLPORT_DIR}/src/${OUTPUT_DIR_DBG}
stldbg-shared:	LDFLAGS += -L${STLPORT_DIR}/src/${OUTPUT_DIR_STLDBG} -Qoption ld -R${STLPORT_DIR}/src/${OUTPUT_DIR_STLDBG}
endif

check-release-shared:	release-shared
	-${OUTPUT_DIR}/${PRGNAME}

ifndef WITHOUT_STLPORT
check-stldbg-shared:	stldbg-shared
	-${OUTPUT_DIR_STLDBG}/${PRGNAME}
endif

check:	${CHECK_TAGS}

