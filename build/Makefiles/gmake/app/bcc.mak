# -*- Makefile -*- Time-stamp: <07/05/31 01:05:40 ptr>
#
# Copyright (c) 1997-1999, 2002, 2003, 2005-2007
# Petr Ovtchenkov
#
# Copyright (c) 2006, 2007
# Francois Dumont
#
# Portion Copyright (c) 1999-2001
# Parallel Graphics Ltd.
#
# Licensed under the Academic Free License version 3.0
#

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

