# -*- makefile -*- Time-stamp: <03/07/10 00:01:14 ptr>
# $Id$

clobber::
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

distclean::
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
