# Time-stamp: <10/06/02 15:17:35 ptr>
#
# Copyright (c) 1997-1999, 2002, 2003, 2005, 2006, 2008
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

PHONY += release-static-dep release-shared-dep dbg-static-dep dbg-shared-dep \
         depend

ifndef WITHOUT_STLPORT
PHONY += stldbg-static-dep stldbg-shared-dep
endif

release-static-dep release-shared-dep:	$(DEP)

dbg-static-dep dbg-shared-dep:	$(DEP_DBG)

ifndef WITHOUT_STLPORT
stldbg-static-dep stldbg-shared-dep:	$(DEP_STLDBG)

_ALL_DEP := $(DEP) $(DEP_DBG) $(DEP_STLDBG)
_DASH_DEP := release-shared-dep dbg-shared-dep stldbg-shared-dep
else
_ALL_DEP := $(DEP) $(DEP_DBG)
_DASH_DEP := release-shared-dep dbg-shared-dep
endif


depend::	$(OUTPUT_DIRS) ${_DASH_DEP}
	@cat -s $(_ALL_DEP) /dev/null > $(DEPENDS_COLLECTION)

ifneq ($(OSNAME),windows)
TAGS:	$(OUTPUT_DIRS) ${_DASH_DEP}
	@cat -s $(_ALL_DEP) /dev/null | sed -e 's/^.*://;s/^ *//;s/\\$$//;s/ $$//;s/ /\n/g' | sort | uniq | xargs etags -I --declarations

tags:	$(OUTPUT_DIRS) ${_DASH_DEP}
	@cat -s $(_ALL_DEP) /dev/null | sed -e 's/^.*://;s/^ *//;s/\\$$//;s/ $$//;s/ /\n/g' | sort | uniq | xargs ctags -d --globals --declarations -t -T 
endif

-include $(DEPENDS_COLLECTION)
