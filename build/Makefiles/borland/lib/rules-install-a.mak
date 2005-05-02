# Time-stamp: 
# $Id: rules-install-a.mak

!message build\Makefiles\borland\lib\rules-install-a.mak

.AUTODEPEND

!ifndef INSTALL_TAGS
INSTALL_TAGS = install-release-static install-dbg-static install-stldbg-static
!endif

install-release-static: release-static
	$(INSTALL_A) $(A_NAME_OUT) $(INSTALL_LIB_DIR) > NUL

install-dbg-static: dbg-static
	$(INSTALL_A) $(A_NAME_OUT_DBG) $(INSTALL_LIB_DIR) > NUL

install-stldbg-static: stldbg-static
	$(INSTALL_A) $(A_NAME_OUT_STLDBG) $(INSTALL_LIB_DIR) > NUL
