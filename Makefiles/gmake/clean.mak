# -*- Makefile -*- Time-stamp: <08/10/22 18:32:42 ptr>
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

PHONY += clean distclean mostlyclean maintainer-clean uninstall

define obj_clean
clean::
	@-rm -f $$($(1)_OBJ) $$($(1)_DEP)
	@-rm -f $$($(1)_OBJ_DBG) $$($(1)_DEP_DBG)
	@-rm -f $$($(1)_OBJ_STLDBG) $$($(1)_DEP_STLDBG)
endef

clean::	
	@-rm -f core core.*
ifdef PRGNAME
	@-rm -f $(OBJ) $(DEP)
	@-rm -f $(OBJ_DBG) $(DEP_DBG)
	@-rm -f $(OBJ_STLDBG) $(DEP_STLDBG)
endif
ifdef LIBNAME
	@-rm -f $(OBJ) $(DEP)
	@-rm -f $(OBJ_DBG) $(DEP_DBG)
	@-rm -f $(OBJ_STLDBG) $(DEP_STLDBG)
endif

$(foreach prg,$(PRGNAMES),$(eval $(call obj_clean,$(prg))))

$(foreach prg,$(LIBNAMES),$(eval $(call obj_clean,$(prg))))

distclean::	clean
# $(DEPENDS_COLLECTION) removed before directory,
# see app/clean.mak and lib/clean.mak

mostlyclean::	clean
	@-rm -f $(DEPENDS_COLLECTION)
	@-rm -f TAGS tags

maintainer-clean::	distclean
	@rm -f ${RULESBASE}/gmake/config.mak
	@-rm -f TAGS tags
