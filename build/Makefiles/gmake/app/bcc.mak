# -*- Makefile -*- Time-stamp: <05/12/07 00:56:53 ptr>

OPT += -tWC -w-par

LDFLAGS += -ap -Tpe -w -w-dup

START_OBJ = c0x32.obj

install-dbg-shared: install-dbg-shared-tds 
install-stldbg-shared: install-stldbg-shared-tds

install-dbg-static: install-dbg-static-tds 
install-stldbg-static: install-stldbg-static-tds

install-dbg-shared-tds:
	$(INSTALL_EXE) $(subst /,\,$(OUTPUT_DIR_DBG)/${PRGNAME}.tds $(INSTALL_BIN_DIR_DBG)/)

install-stldbg-shared-tds:
	$(INSTALL_EXE) $(subst /,\,$(OUTPUT_DIR_STLDBG)/${PRGNAME}.tds $(INSTALL_BIN_DIR_STLDBG)/)

install-dbg-static-tds:
	$(INSTALL_EXE) $(subst /,\,$(OUTPUT_DIR_DBG)/${PRGNAME}.tds $(INSTALL_BIN_DIR_DBG)/)

install-stldbg-static-tds:
	$(INSTALL_EXE) $(subst /,\,$(OUTPUT_DIR_STLDBG)/${PRGNAME}.tds $(INSTALL_BIN_DIR_STLDBG)/)

