# -*- makefile -*- Time-stamp: <07/05/31 00:12:45 ptr>
#
# Copyright (c) 1997-1999, 2002, 2003, 2005-2007
# Petr Ovtchenkov
#
# Copyright (c) 2006, 2007
# Francois Dumont
#
# Portion Copyright (c) 1999-2001
# Parallel Graphics Ltd.
#
# Licensed under the Academic Free License version 3.0
#

INSTALL_TAGS ?= install-shared

PHONY += install $(INSTALL_TAGS)

install: $(INSTALL_TAGS)

install-release-shared:	release-shared $(INSTALL_BIN_DIR) $(INSTALL_LIB_DIR)
	$(INSTALL_SO) ${SO_NAME_OUT} $(INSTALL_BIN_DIR)/
	$(INSTALL_SO) ${LIB_NAME_OUT} $(INSTALL_LIB_DIR)/
#	$(INSTALL_SO) ${EXP_NAME_OUT} $(INSTALL_LIB_DIR)/

install-dbg-shared:	dbg-shared $(INSTALL_BIN_DIR) $(INSTALL_LIB_DIR_DBG)
	$(INSTALL_SO) ${SO_NAME_OUT_DBG} $(INSTALL_BIN_DIR)/
	$(INSTALL_SO) ${LIB_NAME_OUT_DBG} $(INSTALL_LIB_DIR_DBG)/
#	$(INSTALL_SO) ${EXP_NAME_OUT_DBG} $(INSTALL_LIB_DIR_DBG)/

install-stldbg-shared:	stldbg-shared $(INSTALL_BIN_DIR) $(INSTALL_LIB_DIR_DBG)
	$(INSTALL_SO) ${SO_NAME_OUT_STLDBG} $(INSTALL_BIN_DIR)/
	$(INSTALL_SO) ${LIB_NAME_OUT_STLDBG} $(INSTALL_LIB_DIR_STLDBG)/
#	$(INSTALL_SO) ${EXP_NAME_OUT_STLDBG} $(INSTALL_LIB_DIR_STLDBG)/

