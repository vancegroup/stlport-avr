# Time-stamp: <03/10/17 19:29:26 ptr>
# $Id$

install-release-static: release-static
	$(INSTALL_A) $(A_NAME_OUT) $(INSTALL_STATIC_LIB_DIR)

install-dbg-static: dbg-static
	$(INSTALL_A) $(A_NAME_OUT_DBG) $(INSTALL_STATIC_LIB_DIR_DBG)

install-stldbg-static: stldbg-static
	$(INSTALL_A) $(A_NAME_OUT_STLDBG) $(INSTALL_STATIC_LIB_DIR_STLDBG)
