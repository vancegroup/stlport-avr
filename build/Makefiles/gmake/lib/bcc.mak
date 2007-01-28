# -*- makefile -*- Time-stamp: <03/11/30 11:41:22 ptr>
# $Id$


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
