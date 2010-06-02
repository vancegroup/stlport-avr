# Time-stamp: <10/06/02 15:17:35 ptr>
#
# Copyright (c) 2004-2009
# Petr Ovtchenkov
#
# This material is provided "as is", with absolutely no warranty expressed
# or implied. Any use is at your own risk.
#
# Permission to use or copy this software for any purpose is hereby granted
# without fee, provided the above notices are retained on all copies.
# Permission to modify the code and to distribute modified code is granted,
# provided the above notices are retained, and a notice that the code was
# modified is included with the above copyright notice.
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
