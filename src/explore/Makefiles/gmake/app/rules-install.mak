# -*- makefile -*- Time-stamp: <03/07/09 23:45:45 ptr>
# $Id$

install:	install-release install-dbg install-stldbg

install-release:	release-shared
	$(INSTALL_EXE) ${PRG} $(INSTALL_BIN_DIR)

install-dbg:	dbg-shared
	$(INSTALL_EXE) ${PRG_DBG} $(INSTALL_BIN_DIR_DBG)

install-stldbg:	stldbg-shared
	$(INSTALL_EXE) ${PRG_STLDBG} $(INSTALL_BIN_DIR_STLDBG)
