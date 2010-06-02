# Time-stamp: <10/06/02 13:14:13 ptr>
#
# Copyright (c) 2004-2008
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


SRCROOT := build
SUBDIRS := build/lib

include ${SRCROOT}/Makefiles/gmake/subdirs.mak

all install depend clean clobber distclean check::
	+$(call doinsubdirs,${SUBDIRS})

distclean clean depend clobber::
	+$(call doinsubdirs,build/test/unit)

release-shared install-release-shared:
	+$(call doinsubdirs,${SUBDIRS})

install::
	${MAKE} -C build/lib install-headers

.PHONY: all install depend clean clobber distclean check release-shared install-release-shared
