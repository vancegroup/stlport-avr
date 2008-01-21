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

release-shared : LDFLAGS += -Tpd -V4.00 -w -w-dup -Gi
dbg-shared : LDFLAGS += -Tpd -V4.00 -v -w -w-dup -Gi
stldbg-shared : LDFLAGS += -Tpd -V4.00 -v -w -w-dup -Gi

START_OBJ := c0d32.obj

install-shared: install-release-shared install-dbg-shared install-stldbg-shared
install: install-shared

install-dbg-shared: install-dbg-shared-tds 
install-stldbg-shared: install-stldbg-shared-tds

BASE_LIBNAME := $(LIB_PREFIX)${LIBNAME}${LIB_TYPE}${LIB_SUFFIX}
BASE_LIBNAME_DBG := $(LIB_PREFIX)${LIBNAME}${DBG_SUFFIX}${LIB_TYPE}${LIB_SUFFIX}
BASE_LIBNAME_STLDBG := $(LIB_PREFIX)${LIBNAME}${STLDBG_SUFFIX}${LIB_TYPE}${LIB_SUFFIX}
BASE_LIBNAMES = ${BASE_LIBNAME} ${BASE_LIBNAME_DBG} ${BASE_LIBNAME_STLDBG}
BASE_LIB_EXTS = lib dll tds map
LIB_FILES := $(foreach n,$(BASE_LIBNAMES),$(foreach e,$(BASE_LIB_EXTS),$(n).$(e)))

install-dbg-shared-tds:
	$(INSTALL_SO) $(OUTPUT_DIR_DBG)/${BASE_LIBNAME_DBG}.tds $(INSTALL_BIN_DIR)/${BASE_LIBNAME_DBG}.tds

install-stldbg-shared-tds:
	$(INSTALL_SO) $(OUTPUT_DIR_STLDBG)/${BASE_LIBNAME_STLDBG}.tds $(INSTALL_BIN_DIR)/${BASE_LIBNAME_STLDBG}.tds

clean::
	$(foreach d,$(OUTPUT_DIRS),$(foreach f,$(LIB_FILES),@rm -f $(d)/$(f)))
 
uninstall::
	$(foreach d,$(INSTALL_DIRS),$(foreach f,$(LIB_FILES),@rm -f $(d)/$(f)))
	$(foreach d,$(INSTALL_DIRS),@rmdir -p $(d) 2>/dev/null)
