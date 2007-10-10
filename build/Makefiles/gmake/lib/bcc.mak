# -*- makefile -*- Time-stamp: <07/05/31 01:29:22 ptr>
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

release-shared : OPT += -tWD
dbg-shared : OPT += -tWD
stldbg-shared : OPT += -tWD

release-shared : LDFLAGS += -Tpd -V4.00 -w -w-dup
dbg-shared : LDFLAGS += -Tpd -V4.00 -v -w -w-dup
stldbg-shared : LDFLAGS += -Tpd -V4.00 -v -w -w-dup

START_OBJ := c0d32.obj

install-dbg-shared: install-dbg-shared-tds 
install-stldbg-shared: install-stldbg-shared-tds

TDS_LIBNAME_DBG := $(LIB_PREFIX)${LIBNAME}${DBG_SUFFIX}${LIB_TYPE}${LIB_SUFFIX}.tds
TDS_LIBNAME_STLDBG := $(LIB_PREFIX)${LIBNAME}${STLDBG_SUFFIX}${LIB_TYPE}${LIB_SUFFIX}.tds

install-dbg-shared-tds:
	$(INSTALL_SO) $(subst /,\,$(OUTPUT_DIR_DBG)/${TDS_LIBNAME_DBG} $(INSTALL_BIN_DIR)/)

install-stldbg-shared-tds:
	$(INSTALL_SO) $(subst /,\,$(OUTPUT_DIR_STLDBG)/${TDS_LIBNAME_STLDBG} $(INSTALL_BIN_DIR)/)
