# -*- Makefile -*- Time-stamp: <08/11/17 21:38:45 ptr>

SRCROOT := ../../..

# EXTRA_POST := checks
# EXTRA_POST_DBG := checks-dbg
# EXTRA_POST_STLDBG := checks-stldbg

SUBDIRS := one two three
DESTDIR := dest

include ${SRCROOT}/Makefiles/gmake/subdirs.mak

check0:
	$(call doinsubdirs,${SUBDIRS})

check:	check0
	$(call doinsubdirs,${SUBDIRS},DESTDIR=${DESTDIR})

.PHONY:	check0 check

