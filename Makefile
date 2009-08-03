# Time-stamp: <08/12/12 06:44:27 ptr>
#
# Copyright (c) 2004-2009
# Petr Ovtchenkov
#
# Licensed under the Academic Free License version 3.0
#

SRCROOT := .
SUBDIRS := src

include ${SRCROOT}/Makefiles/gmake/top.mak
include ${SRCROOT}/Makefiles/gmake/subdirs.mak

all uninstall:
	+$(call doinsubdirs,${SUBDIRS})

depend clean distclean mostlyclean maintainer-clean::
	+$(call doinsubdirs,${SUBDIRS} test/exam test/misc test/cmp_unit test/unit)

release-shared install-release-shared dbg-shared install-dbg-shared stldbg-shared install-stldbg-shared:
	+$(call doinsubdirs,${SUBDIRS})

check:	release-shared dbg-shared stldbg-shared
	+$(call dotaginsubdirs,all,test/exam test/misc test/cmp_unit test/unit)

check-release-shared:	release-shared
	+$(call dotaginsubdirs,release-shared,test/exam test/misc test/cmp_unit test/unit)
	+$(call doinsubdirs,test/cmp_unit test/unit)

check-dbg-shared:	dbg-shared
	+$(call dotaginsubdirs,dbg-shared,test/exam test/misc test/cmp_unit test/unit)
	+$(call doinsubdirs,test/cmp_unit test/unit)

check-stldbg-shared:	stldbg-shared
	+$(call dotaginsubdirs,stldbg-shared,test/exam test/misc test/cmp_unit test/unit)
	+$(call doinsubdirs,test/cmp_unit test/unit)

install:	
	+$(call doinsubdirs,${SUBDIRS})

install-headers:
	${MAKE} -C src install-headers

PHONY += all install depend \
         install-release-shared install-dbg-shared install-stldbg-shared \
         clean distclean mostlyclean maintainer-clean uninstall \
         release-shared dbg-shared stldbg-shared \
         install-headers \
         check check-release-shared check-dbg-shared check-stldbg-shared
