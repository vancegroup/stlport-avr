# Time-stamp: <08/06/06 10:38:18 yeti>
#
# Copyright (c) 2004-2008
# Petr Ovtchenkov
#
# Licensed under the Academic Free License version 3.0
#

SRCROOT := build
SUBDIRS := build/lib

include ${SRCROOT}/Makefiles/gmake/subdirs.mak

all install depend clean clobber distclean check:
	+$(call doinsubdirs,${SUBDIRS})

release-shared install-release-shared:
	+$(call doinsubdirs,${SUBDIRS})


.PHONY: all install depend clean clobber distclean check release-shared install-release-shared
