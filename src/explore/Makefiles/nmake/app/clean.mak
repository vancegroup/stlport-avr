# -*- makefile -*- Time-stamp: <03/10/26 16:17:03 ptr>
# $Id$

clobber:	clean
	@-del /F /Q $(PRG)
	@-del /F /Q $(PRG_DBG)
	@-del /F /Q $(PRG_STLDBG)

distclean:	clobber
	@-del /F /Q  $(INSTALL_BIN_DIR)/$(PRGNAME)
	@-del /F /Q  $(INSTALL_BIN_DIR_DBG)/$(PRGNAME)
	@-del /F /Q  $(INSTALL_BIN_DIR_STLDBG)/$(PRGNAME)
