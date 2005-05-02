# Time-stamp:
# $Id: rules-install-so.mak

!message build\Makefiles\borland\lib\rules-install-so.mak

.AUTODEPEND

!ifndef INSTALL_TAGS
INSTALL_TAGS = install-release-shared install-dbg-shared install-stldbg-shared 
!endif

install-release-shared: release-shared
	$(INSTALL_SO) $(SO_NAME_OUT) $(INSTALL_DLL_DIR) > NUL
	$(INSTALL_SO) $(LIB_NAME_OUT) $(INSTALL_LIB_DIR) > NUL

install-dbg-shared: dbg-shared
	$(INSTALL_SO) $(SO_NAME_OUT_DBG) $(INSTALL_DLL_DIR) > NUL
	$(INSTALL_SO) $(LIB_NAME_OUT_DBG) $(INSTALL_LIB_DIR) > NUL

install-stldbg-shared: stldbg-shared
	$(INSTALL_SO) $(SO_NAME_OUT_STLDBG) $(INSTALL_DLL_DIR) > NUL
	$(INSTALL_SO) $(LIB_NAME_OUT_STLDBG) $(INSTALL_LIB_DIR) > NUL
