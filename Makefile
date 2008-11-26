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

all install depend clean distclean check mostlyclean maintainer-clean::
	+$(call doinsubdirs,${SUBDIRS})

distclean clean depend mostlyclean maintainer-clean::
	+$(call doinsubdirs,test/exam test/misc test/unit)

release-shared install-release-shared:
	+$(call doinsubdirs,${SUBDIRS})

install::
	${MAKE} -C src install-headers

.PHONY: all install depend check release-shared install-release-shared \
        clean distclean mostlyclean maintainer-clean
