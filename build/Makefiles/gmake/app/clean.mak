# -*- makefile -*- Time-stamp: <03/07/10 00:20:54 ptr>
# $Id$

clobber::
	@-rm -f ${PRG}
	@-rm -f ${PRG_DBG}
	@-rm -f ${PRG_STLDBG}

distclean::
	@-rm -f $(INSTALL_BIN_DIR)/$(PRG)
	@-rm -f $(INSTALL_BIN_DIR_DBG)/$(PRG_DBG)
	@-rm -f $(INSTALL_BIN_DIR_STLDBG)/$(PRG_STLDBG)
