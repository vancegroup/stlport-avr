# -*- Makefile -*- Time-stamp: <08/06/29 19:26:11 ptr>

SRCROOT := ../../..

include Makefile.inc
include ${SRCROOT}/Makefiles/gmake/top.mak

STLPORT_DIR := ../../..


INCLUDES += -I../../include
DEFS += -D__FIT_EXAM

LIBEXAM_DIR = ../../exam
LIBMISC_DIR = ..

ifeq ($(OSNAME),linux)

release-shared:	LDFLAGS += -L${LIBEXAM_DIR}/${OUTPUT_DIR} -L${LIBMISC_DIR}/${OUTPUT_DIR} -L../../../src/${OUTPUT_DIR} -Wl,--rpath=${LIBEXAM_DIR}/${OUTPUT_DIR}:${LIBXMT_DIR}/${OUTPUT_DIR}:${LIBMISC_DIR}/${OUTPUT_DIR}:../../../src/${OUTPUT_DIR}

dbg-shared:	LDFLAGS += -L${LIBEXAM_DIR}/${OUTPUT_DIR_DBG} -L${LIBMISC_DIR}/${OUTPUT_DIR_DBG} -L../../../src/${OUTPUT_DIR_DBG} -Wl,--rpath=${LIBEXAM_DIR}/${OUTPUT_DIR_DBG}:${LIBMISC_DIR}/${OUTPUT_DIR_DBG}:../../../src/${OUTPUT_DIR_DBG}

ifndef WITHOUT_STLPORT
stldbg-shared:	LDFLAGS += -L${LIBEXAM_DIR}/${OUTPUT_DIR_STLDBG} -L${LIBMISC_DIR}/${OUTPUT_DIR_STLDBG} -L../../../src/${OUTPUT_DIR_STLDBG} -Wl,--rpath=${LIBEXAM_DIR}/${OUTPUT_DIR_STLDBG}:${LIBMISC_DIR}/${OUTPUT_DIR_STLDBG}:../../../src/${OUTPUT_DIR_STLDBG}
endif

endif

ifeq ($(OSNAME),openbsd)

ifndef WITHOUT_STLPORT
release-shared:	LDFLAGS += -Wl,-R:${STLPORT_LIB_DIR}
dbg-shared:	LDFLAGS += -Wl,-R:${STLPORT_LIB_DIR}
stldbg-shared:	LDFLAGS += -Wl,-R:${STLPORT_LIB_DIR}
endif

endif

release-shared : LDLIBS = -lexam -lopts
dbg-shared     : LDLIBS = -lexamg -loptsg
ifndef WITHOUT_STLPORT
stldbg-shared  : LDLIBS = -lexamstlg -loptsstlg
endif

ifeq ($(OSNAME),freebsd)
release-shared : LDLIBS += -lthr
dbg-shared     : LDLIBS += -lthr
ifndef WITHOUT_STLPORT
stldbg-shared  : LDLIBS += -lthr
endif
endif

ifeq ($(OSNAME),sunos)
release-shared : LDLIBS += -lrt
dbg-shared     : LDLIBS += -lrt
ifndef WITHOUT_STLPORT
stldbg-shared  : LDLIBS += -lrt
endif
endif


