# -*- makefile -*- Time-stamp: <03/07/10 13:21:45 ptr>
# $Id$

PHONY += install-release-static install-dbg-static install-stldbg-static

install-release-static:	release-static
	$(INSTALL_A) ${A_NAME_OUT} $(INSTALL_LIB_DIR)

install-dbg-static:	dbg-static
	$(INSTALL_A) ${A_NAME_OUT_DBG} $(INSTALL_LIB_DIR_DBG)

install-stldbg-static:	stldbg-static
	$(INSTALL_A) ${A_NAME_OUT_STLDBG} $(INSTALL_LIB_DIR_STLDBG)
