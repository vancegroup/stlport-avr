# -*- makefile -*- Time-stamp: <04/07/25 17:58:50 ptr>
# $Id$

install:	install-shared

# The program name to be installed will be the same as compiled name,
# but it will be a bit altered in case of installation debug and/or
# stlport-debug program in the same catalog as 'release' program.

INSTALL_PRGNAME := ${PRGNAME}${EXE}
INSTALL_PRGNAME_A := ${PRGNAME}_static${EXE}

ifeq (${INSTALL_BIN_DIR},${INSTALL_BIN_DIR_DBG})
INSTALL_PRGNAME_DBG := ${PRGNAME}g${EXE}
INSTALL_PRGNAME_A_DBG := ${PRGNAME}g_static${EXE}
else
INSTALL_PRGNAME_DBG := ${INSTALL_PRGNAME}
INSTALL_PRGNAME_A_DBG := ${INSTALL_PRGNAME_A}
endif

ifeq (${INSTALL_BIN_DIR},${INSTALL_BIN_DIR_STLDBG})
INSTALL_PRGNAME_STLDBG := ${PRGNAME}stlg${EXE}
INSTALL_PRGNAME_A_STLDBG := ${PRGNAME}stlg_static${EXE}
else
INSTALL_PRGNAME_STLDBG := ${INSTALL_PRGNAME}
INSTALL_PRGNAME_A_STLDBG := ${INSTALL_PRGNAME_A}
endif

ifeq (${INSTALL_BIN_DIR_DBG},${INSTALL_BIN_DIR_STLDBG})
INSTALL_PRGNAME_DBG := ${PRGNAME}g${EXE}
INSTALL_PRGNAME_STLDBG := ${PRGNAME}stlg${EXE}
INSTALL_PRGNAME_A_DBG := ${PRGNAME}g_static${EXE}
INSTALL_PRGNAME_A_STLDBG := ${PRGNAME}stlg_static${EXE}
endif

ifneq ($(OSNAME),windows)
install-release-shared: release-shared
	@if [ ! -d $(INSTALL_BIN_DIR) ] ; then \
	  mkdir -p $(INSTALL_BIN_DIR) ; \
	fi
	$(INSTALL_EXE) ${PRG} $(INSTALL_BIN_DIR)/${INSTALL_PRGNAME}

install-dbg-shared: dbg-shared
	@if [ ! -d $(INSTALL_BIN_DIR_DBG) ] ; then \
	  mkdir -p $(INSTALL_BIN_DIR_DBG) ; \
	fi
	$(INSTALL_EXE) ${PRG_DBG} $(INSTALL_BIN_DIR_DBG)/${INSTALL_PRGNAME_DBG}

install-stldbg-shared: stldbg-shared
	@if [ ! -d $(INSTALL_BIN_DIR_STLDBG) ] ; then \
	  mkdir -p $(INSTALL_BIN_DIR_STLDBG) ; \
	fi
	$(INSTALL_EXE) ${PRG_STLDBG} $(INSTALL_BIN_DIR_STLDBG)/${INSTALL_PRGNAME_STLDBG}

install-release-static: release-static
	@if [ ! -d $(INSTALL_BIN_DIR) ] ; then \
	  mkdir -p $(INSTALL_BIN_DIR) ; \
	fi
	$(INSTALL_EXE) ${PRG_A} $(INSTALL_BIN_DIR)/${INSTALL_PRGNAME_A}

install-dbg-static: dbg-static
	@if [ ! -d $(INSTALL_BIN_DIR_DBG) ] ; then \
	  mkdir -p $(INSTALL_BIN_DIR_DBG) ; \
	fi
	$(INSTALL_EXE) $(PRG_A_DBG) $(INSTALL_BIN_DIR_DBG)/$(INSTALL_PRGNAME_A_DBG)

install-stldbg-static: stldbg-static
	@if [ ! -d $(INSTALL_BIN_DIR_STLDBG) ] ; then \
	  mkdir -p $(INSTALL_BIN_DIR_STLDBG) ; \
	fi
	$(INSTALL_EXE) ${PRG_A_STLDBG} $(INSTALL_BIN_DIR_STLDBG)/${INSTALL_PRGNAME_A_STLDBG}
else
install-release-shared: release-shared
	$(INSTALL_EXE) $(subst /,\,$(PRG) $(INSTALL_BIN_DIR)/$(INSTALL_PRGNAME))

install-dbg-shared: dbg-shared
	$(INSTALL_EXE) $(subst /,\,$(PRG_DBG) $(INSTALL_BIN_DIR_DBG)/$(INSTALL_PRGNAME_DBG))

install-stldbg-shared: stldbg-shared
	$(INSTALL_EXE) $(subst /,\,$(PRG_STLDBG) $(INSTALL_BIN_DIR_STLDBG)/$(INSTALL_PRGNAME_STLDBG))

install-release-static: release-static
	$(INSTALL_EXE) $(subst /,\,$(PRG_A) $(INSTALL_BIN_DIR)/$(INSTALL_PRGNAME_A))

install-dbg-static: dbg-static
	$(INSTALL_EXE) $(subst /,\,$(PRG_A_DBG) $(INSTALL_BIN_DIR_DBG)/$(INSTALL_PRGNAME_A_DBG))

install-stldbg-static: stldbg-static
	$(INSTALL_EXE) $(subst /,\,$(PRG_A_STLDBG) $(INSTALL_BIN_DIR_STLDBG)/$(INSTALL_PRGNAME_A_STLDBG))
endif
