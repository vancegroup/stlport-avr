# -*- makefile -*- Time-stamp: <06/11/02 10:34:43 ptr>
#
# Copyright (c) 1997-1999, 2002, 2003, 2005, 2006
# Petr Ovtchenkov
#
# This material is provided "as is", with absolutely no warranty expressed
# or implied. Any use is at your own risk.
#
# Permission to use or copy this software for any purpose is hereby granted
# without fee, provided the above notices are retained on all copies.
# Permission to modify the code and to distribute modified code is granted,
# provided the above notices are retained, and a notice that the code was
# modified is included with the above copyright notice.
#

PHONY += install-release-static install-dbg-static install-stldbg-static

install-release-static:	release-static
	@if [ ! -d $(INSTALL_LIB_DIR) ] ; then \
	  mkdir -p $(INSTALL_LIB_DIR) ; \
	fi
	$(INSTALL_A) ${A_NAME_OUT} $(INSTALL_LIB_DIR)

install-dbg-static:	dbg-static
	@if [ ! -d $(INSTALL_LIB_DIR_DBG) ] ; then \
	  mkdir -p $(INSTALL_LIB_DIR_DBG) ; \
	fi
	$(INSTALL_A) ${A_NAME_OUT_DBG} $(INSTALL_LIB_DIR_DBG)

ifndef WITHOUT_STLPORT

install-stldbg-static:	stldbg-static
	@if [ ! -d $(INSTALL_LIB_DIR_STLDBG) ] ; then \
	  mkdir -p $(INSTALL_LIB_DIR_STLDBG) ; \
	fi
	$(INSTALL_A) ${A_NAME_OUT_STLDBG} $(INSTALL_LIB_DIR_STLDBG)

endif
