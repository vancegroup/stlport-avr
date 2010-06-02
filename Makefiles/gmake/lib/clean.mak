# -*- makefile -*- Time-stamp: <07/05/30 23:55:47 ptr>
#
# Copyright (c) 1997-1999, 2002, 2003, 2005-2007
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

define lib_clean
clean::
	@-rm -f $${$(1)_SO_NAME_OUT}
	@-rm -f $${$(1)_SO_NAME_OUTx}
	@-rm -f $${$(1)_SO_NAME_OUTxx}
	@-rm -f $${$(1)_SO_NAME_OUTxxx}
	@-rm -f $${$(1)_SO_NAME_OUT_DBG}
	@-rm -f $${$(1)_SO_NAME_OUT_DBGx}
	@-rm -f $${$(1)_SO_NAME_OUT_DBGxx}
	@-rm -f $${$(1)_SO_NAME_OUT_DBGxxx}
	@-rm -f $${$(1)_SO_NAME_OUT_STLDBG}
	@-rm -f $${$(1)_SO_NAME_OUT_STLDBGx}
	@-rm -f $${$(1)_SO_NAME_OUT_STLDBGxx}
	@-rm -f $${$(1)_SO_NAME_OUT_STLDBGxxx}
	@-rm -f $${$(1)_A_NAME_OUT}
	@-rm -f $${$(1)_A_NAME_OUT_DBG}
	@-rm -f $${$(1)_A_NAME_OUT_STLDBG}
ifeq ($(OSNAME), windows)
	@-rm -f $${$(1)_LIB_NAME_OUT}
	@-rm -f $${$(1)_LIB_NAME_OUT_DBG}
	@-rm -f $${$(1)_LIB_NAME_OUT_STLDBG}
	@-rm -f $${$(1)_RES}
	@-rm -f $${$(1)_RES_DBG}
	@-rm -f $${$(1)_RES_STLDBG}
endif

uninstall::
	@-rm -f $$(INSTALL_LIB_DIR)/$$($(1)_SO_NAME)
	@-rm -f $$(INSTALL_LIB_DIR)/$$($(1)_SO_NAMEx)
	@-rm -f $$(INSTALL_LIB_DIR)/$$($(1)_SO_NAMExx)
	@-rm -f $$(INSTALL_LIB_DIR)/$$($(1)_SO_NAMExxx)
	@-rm -f $$(INSTALL_LIB_DIR_DBG)/$$($(1)_SO_NAME_DBG)
	@-rm -f $$(INSTALL_LIB_DIR_DBG)/$$($(1)_SO_NAME_DBGx)
	@-rm -f $$(INSTALL_LIB_DIR_DBG)/$$($(1)_SO_NAME_DBGxx)
	@-rm -f $$(INSTALL_LIB_DIR_DBG)/$$($(1)_SO_NAME_DBGxxx)
	@-rm -f $$(INSTALL_LIB_DIR_STLDBG)/$$($(1)_SO_NAME_STLDBG)
	@-rm -f $$(INSTALL_LIB_DIR_STLDBG)/$$($(1)_SO_NAME_STLDBGx)
	@-rm -f $$(INSTALL_LIB_DIR_STLDBG)/$$($(1)_SO_NAME_STLDBGxx)
	@-rm -f $$(INSTALL_LIB_DIR_STLDBG)/$$($(1)_SO_NAME_STLDBGxxx)
	@-rm -f $$(INSTALL_LIB_DIR)/$${$(1)_A_NAME_OUT}
	@-rm -f $$(INSTALL_LIB_DIR_DBG)/$${$(1)_A_NAME_OUT_DBG}
	@-rm -f $$(INSTALL_LIB_DIR_STLDBG)/$${$(1)_A_NAME_OUT_STLDBG}
	@-rmdir -p $$(INSTALL_LIB_DIR) $$(INSTALL_LIB_DIR_DBG) $$(INSTALL_LIB_DIR_STLDBG) 2>/dev/null
endef

$(foreach nm,$(LIBNAMES),$(eval $(call lib_clean,$(nm))))

clean::
ifdef LIBNAME
	@-rm -f ${SO_NAME_OUT}
	@-rm -f ${SO_NAME_OUTx}
	@-rm -f ${SO_NAME_OUTxx}
	@-rm -f ${SO_NAME_OUTxxx}
	@-rm -f ${SO_NAME_OUT_DBG}
	@-rm -f ${SO_NAME_OUT_DBGx}
	@-rm -f ${SO_NAME_OUT_DBGxx}
	@-rm -f ${SO_NAME_OUT_DBGxxx}
	@-rm -f ${SO_NAME_OUT_STLDBG}
	@-rm -f ${SO_NAME_OUT_STLDBGx}
	@-rm -f ${SO_NAME_OUT_STLDBGxx}
	@-rm -f ${SO_NAME_OUT_STLDBGxxx}
	@-rm -f ${A_NAME_OUT}
	@-rm -f ${A_NAME_OUT_DBG}
	@-rm -f ${A_NAME_OUT_STLDBG}
ifeq ($(OSNAME), windows)
	@-rm -f ${LIB_NAME_OUT}
	@-rm -f ${LIB_NAME_OUT_DBG}
	@-rm -f ${LIB_NAME_OUT_STLDBG}
	@-rm -f ${RES}
	@-rm -f ${RES_DBG}
	@-rm -f ${RES_STLDBG}
endif
endif

distclean::
	@-rm -f $(DEPENDS_COLLECTION)
	@-rmdir -p $(AUX_DIR) ${OUTPUT_DIR} ${OUTPUT_DIR_DBG} ${OUTPUT_DIR_STLDBG} 2>/dev/null

uninstall::
ifdef LIBNAME
	@-rm -f $(INSTALL_LIB_DIR)/$(SO_NAME)
	@-rm -f $(INSTALL_LIB_DIR)/$(SO_NAMEx)
	@-rm -f $(INSTALL_LIB_DIR)/$(SO_NAMExx)
	@-rm -f $(INSTALL_LIB_DIR)/$(SO_NAMExxx)
	@-rm -f $(INSTALL_LIB_DIR_DBG)/$(SO_NAME_DBG)
	@-rm -f $(INSTALL_LIB_DIR_DBG)/$(SO_NAME_DBGx)
	@-rm -f $(INSTALL_LIB_DIR_DBG)/$(SO_NAME_DBGxx)
	@-rm -f $(INSTALL_LIB_DIR_DBG)/$(SO_NAME_DBGxxx)
	@-rm -f $(INSTALL_LIB_DIR_STLDBG)/$(SO_NAME_STLDBG)
	@-rm -f $(INSTALL_LIB_DIR_STLDBG)/$(SO_NAME_STLDBGx)
	@-rm -f $(INSTALL_LIB_DIR_STLDBG)/$(SO_NAME_STLDBGxx)
	@-rm -f $(INSTALL_LIB_DIR_STLDBG)/$(SO_NAME_STLDBGxxx)
	@-rm -f $(INSTALL_LIB_DIR)/${A_NAME_OUT}
	@-rm -f $(INSTALL_LIB_DIR_DBG)/${A_NAME_OUT_DBG}
	@-rm -f $(INSTALL_LIB_DIR_STLDBG)/${A_NAME_OUT_STLDBG}
endif
	@-rmdir -p $(INSTALL_LIB_DIR) $(INSTALL_LIB_DIR_DBG) $(INSTALL_LIB_DIR_STLDBG) 2>/dev/null

