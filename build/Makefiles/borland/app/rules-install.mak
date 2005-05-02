# Time-stamp: 
# $Id: rules-install.mak

!message build\Makefiles\borland\app\rules-install.mak

.AUTODEPEND

!ifndef INSTALL_TAGS
INSTALL_TAGS = install-release-shared install-dbg-shared install-stldbg-shared install-release-static install-dbg-static install-stldbg-static
!endif

install-release-shared: release-shared
	$(INSTALL_EXE) $(PRG) $(INSTALL_BIN_DIR) > NUL

install-dbg-shared: dbg-shared
	$(INSTALL_EXE) $(PRG_DBG) $(INSTALL_BIN_DIR) > NUL

install-stldbg-shared: stldbg-shared
	$(INSTALL_EXE) $(PRG_STLDBG) $(INSTALL_BIN_DIR) > NUL

install-release-static: release-static
	$(INSTALL_EXE) $(PRG_A) $(INSTALL_BIN_DIR) > NUL

install-dbg-static: dbg-static
	$(INSTALL_EXE) $(PRG_A_DBG) $(INSTALL_BIN_DIR) > NUL

install-stldbg-static: stldbg-static
	$(INSTALL_EXE) $(PRG_A_STLDBG) $(INSTALL_BIN_DIR) > NUL
