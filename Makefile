# Time-stamp: <08/06/12 14:28:42 ptr>
#
# Copyright (c) 2004-2008
# Petr Ovtchenkov
#
# Licensed under the Academic Free License version 3.0
#

SRCROOT := .
SUBDIRS := src

include ${SRCROOT}/Makefiles/gmake/subdirs.mak

all install depend clean distclean mostlyclean maintainer-clean uninstall::
	+$(call doinsubdirs,${SUBDIRS})

distclean clean depend mostlyclean maintainer-clean::
	+$(call doinsubdirs,test/exam test/misc test/cmp_unit test/unit)

release-shared install-release-shared dbg-shared stldbg-shared:
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

install::	install-headers

install-headers:
	${MAKE} -C src install-headers

.PHONY: all install depend release-shared install-release-shared \
        clean distclean mostlyclean maintainer-clean uninstall \
        dbg-shared stldbg-shared \
        install-headers \
        check check-release-shared check-dbg-shared check-stldbg-shared
