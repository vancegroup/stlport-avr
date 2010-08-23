# -*- Makefile -*- Time-stamp: <08/10/26 20:04:35 ptr>

SRCROOT := ../..

ALL_TAGS := release-shared dbg-shared stldbg-shared

include Makefile.inc
include ${SRCROOT}/Makefiles/gmake/top.mak

STLPORT_DIR := ../..

ifeq (${OSNAME},android)
# CXXFLAGS += -fexceptions
endif

INCLUDES += -I../include

release-shared:	LDFLAGS += -L${SRCROOT}/src/${OUTPUT_DIR}

dbg-shared:	LDFLAGS += -L${SRCROOT}/src/${OUTPUT_DIR_DBG}

ifndef WITHOUT_STLPORT
stldbg-shared:	LDFLAGS += -L${SRCROOT}/src/${OUTPUT_DIR_STLDBG}
endif

#check:	all-shared
#	$(MAKE) -C ./ut
#	(cd ./ut; ${OUTPUT_DIR}/exam_self_test) || exit 1
#	(cd ./ut; ${OUTPUT_DIR_DBG}/exam_self_test) || exit 1
#ifndef WITHOUT_STLPORT
#	(cd ./ut; ${OUTPUT_DIR_STLDBG}/exam_self_test) || exit 1
#endif

#check-release-shared:	release-shared
#	$(MAKE) -C ./ut release-shared
#	(cd ./ut; ${OUTPUT_DIR}/exam_self_test) || exit 1

#check-dbg-shared:	dbg-shared
#	$(MAKE) -C ./ut dbg-shared
#	(cd ./ut; ${OUTPUT_DIR_DBG}/exam_self_test) || exit 1

#ifndef WITHOUT_STLPORT
#check-stldbg-shared:	stldbg-shared
#	$(MAKE) -C ./ut stldbg-shared
#	(cd ./ut; ${OUTPUT_DIR_STLDBG}/exam_self_test) || exit 1
#endif

depend clean distclean mostlyclean maintainer-clean::

#	${MAKE} -C ut $@
