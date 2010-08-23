# -*- Makefile -*- Time-stamp: <09/10/06 17:26:48 ptr>

SRCROOT := ../..
COMPILER_NAME := gcc
#NOT_USE_NOSTDLIB := 1
#WITHOUT_STLPORT := 1
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

ifneq ($(OSNAME),windows)
ifneq ($(CXX_VERSION_MAJOR),2)
ifneq ($(CXX_VERSION_MAJOR),3)
# CXXFLAGS += -fvisibility=hidden
# CFLAGS += -fvisibility=hidden
endif
endif
endif

ifeq (${OSNAME},android)
# CXXFLAGS += -fexceptions -frtti
endif

dbg-shared:	DEFS += -D_STLP_DEBUG_UNINITIALIZED
ifndef WITHOUT_STLPORT
stldbg-shared:	DEFS += -D_STLP_DEBUG_UNINITIALIZED
endif

INCLUDES += -I../include

ifdef STLP_BUILD_BOOST_PATH
INCLUDES += -I${STLP_BUILD_BOOST_PATH}
endif

ifndef TARGET_OS
ifndef WITHOUT_STLPORT

ifeq ($(OSNAME), sunos)
release-shared: LDFLAGS += -L${STLPORT_DIR}/src/${OUTPUT_DIR} -Wl,-R${STLPORT_DIR}/src/${OUTPUT_DIR}
dbg-shared:     LDFLAGS += -L${STLPORT_DIR}/src/${OUTPUT_DIR_DBG} -Wl,-R${STLPORT_DIR}/src/${OUTPUT_DIR_DBG}
stldbg-shared:  LDFLAGS += -L${STLPORT_DIR}/src/${OUTPUT_DIR_STLDBG} -Wl,-R${STLPORT_DIR}/src/${OUTPUT_DIR_STLDBG}
endif

ifeq ($(OSNAME), freebsd)
release-shared: LDFLAGS += -L${STLPORT_DIR}/src/${OUTPUT_DIR} -Wl,-R${STLPORT_DIR}/src/${OUTPUT_DIR}
dbg-shared:     LDFLAGS += -L${STLPORT_DIR}/src/${OUTPUT_DIR_DBG} -Wl,-R${STLPORT_DIR}/src/${OUTPUT_DIR_DBG}
stldbg-shared:  LDFLAGS += -L${STLPORT_DIR}/src/${OUTPUT_DIR_STLDBG} -Wl,-R${STLPORT_DIR}/src/${OUTPUT_DIR_STLDBG}
endif

ifeq ($(OSNAME), openbsd)
release-shared: LDFLAGS += -L${STLPORT_DIR}/src/${OUTPUT_DIR} -Wl,-R${STLPORT_DIR}/src/${OUTPUT_DIR}
dbg-shared:     LDFLAGS += -L${STLPORT_DIR}/src/${OUTPUT_DIR_DBG} -Wl,-R${STLPORT_DIR}/src/${OUTPUT_DIR_DBG}
stldbg-shared:  LDFLAGS += -L${STLPORT_DIR}/src/${OUTPUT_DIR_STLDBG} -Wl,-R${STLPORT_DIR}/src/${OUTPUT_DIR_STLDBG}
endif

ifeq ($(OSNAME), linux)
release-shared:	LDFLAGS += -L${STLPORT_DIR}/src/${OUTPUT_DIR} \
  -L../misc/${OUTPUT_DIR} -L../exam/${OUTPUT_DIR} \
  -Wl,-rpath=${STLPORT_DIR}/src/${OUTPUT_DIR}:../misc/${OUTPUT_DIR}:../exam/${OUTPUT_DIR}
release-shared:	LDLIBS += -lopts -lexam
dbg-shared:	LDFLAGS += -L${STLPORT_DIR}/src/${OUTPUT_DIR_DBG} \
  -L../misc/${OUTPUT_DIR_DBG} -L../exam/${OUTPUT_DIR_DBG} \
  -Wl,-rpath=${STLPORT_DIR}/src/${OUTPUT_DIR_DBG}:../misc/${OUTPUT_DIR_DBG}:../exam/${OUTPUT_DIR_DBG}
dbg-shared:	LDLIBS += -loptsg -lexamg
stldbg-shared:	LDFLAGS += -L${STLPORT_DIR}/src/${OUTPUT_DIR_STLDBG} \
  -L../misc/${OUTPUT_DIR_STLDBG} -L../exam/${OUTPUT_DIR_STLDBG} \
  -Wl,-rpath=${STLPORT_DIR}/src/${OUTPUT_DIR_STLDBG}:../misc/${OUTPUT_DIR_STLDBG}:../exam/${OUTPUT_DIR_STLDBG}
stldbg-shared:	LDLIBS += -loptsstlg -lexamstlg
endif

ifeq ($(OSNAME), hp-ux)
release-shared: LDFLAGS += -L${STLPORT_DIR}/src/${OUTPUT_DIR} -Wl,+b${STLPORT_DIR}/src/${OUTPUT_DIR}
dbg-shared:	LDFLAGS += -L${STLPORT_DIR}/src/${OUTPUT_DIR_DBG} -Wl,+b${STLPORT_DIR}/src/${OUTPUT_DIR_DBG}
stldbg-shared:	LDFLAGS += -L${STLPORT_DIR}/src/${OUTPUT_DIR_STLDBG} -Wl,+b${STLPORT_DIR}/src/${OUTPUT_DIR_STLDBG}
endif

endif
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

PHONY += check check-release-shared check-dbg-shared check-stldbg-shared
