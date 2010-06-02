# -*- makefile -*- Time-stamp: <07/05/31 00:12:45 ptr>
#
# Copyright (c) 1997-1999, 2002, 2003, 2005-2007
# Petr Ovtchenkov
#
# Copyright (c) 2006, 2007
# Francois Dumont
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

