# -*- makefile -*- Time-stamp: <03/10/26 16:17:03 ptr>
# $Id$

clobber:	clean
	@-del /F /Q $(PRG)
	@-del /F /Q $(PRG_DBG)
	@-del /F /Q $(PRG_STLDBG)
	@-del /F /Q $(PRG_A)
	@-del /F /Q $(PRG_A_DBG)
	@-del /F /Q $(PRG_A_STLDBG)
	@-del /F /Q $(PDB_NAME_OUT)
	@-del /F /Q $(PDB_NAME_OUT_DBG)
	@-del /F /Q $(PDB_NAME_OUT_STLDBG)
	@-del /F /Q $(A_PDB_NAME_OUT)
	@-del /F /Q $(A_PDB_NAME_OUT_DBG)
	@-del /F /Q $(A_PDB_NAME_OUT_STLDBG)
	@-rd $(OUTPUT_DIR)
	@-rd $(OUTPUT_DIR_DBG)
	@-rd $(OUTPUT_DIR_STLDBG)
	@-rd $(OUTPUT_DIR_A)
	@-rd $(OUTPUT_DIR_A_DBG)
	@-rd $(OUTPUT_DIR_A_STLDBG)

distclean:	clobber
	@-del /F /Q  $(INSTALL_BIN_DIR)\$(PRG_NAME_BASE)$(EXE)
	@-del /F /Q  $(INSTALL_BIN_DIR_DBG)\$(PRG_NAME_DBG_BASE)$(EXE)
	@-del /F /Q  $(INSTALL_BIN_DIR_STLDBG)\$(PRG_NAME_STLDBG_BASE)$(EXE)
	@-del /F /Q  $(INSTALL_STATIC_BIN_DIR)\$(PRG_NAME_A_BASE)$(EXE)
	@-del /F /Q  $(INSTALL_STATIC_BIN_DIR_DBG)\$(PRG_NAME_A_DBG_BASE)$(EXE)
	@-del /F /Q  $(INSTALL_STATIC_BIN_DIR_STLDBG)\$(PRG_NAME_A_STLDBG_BASE)$(EXE)
	@-del /F /Q  $(INSTALL_BIN_DIR)\$(PRG_NAME_BASE).pdb
	@-del /F /Q  $(INSTALL_BIN_DIR_DBG)\$(PRG_NAME_DBG_BASE).pdb
	@-del /F /Q  $(INSTALL_BIN_DIR_STLDBG)\$(PRG_NAME_STLDBG_BASE).pdb
	@-del /F /Q  $(INSTALL_STATIC_BIN_DIR)\$(PRG_NAME_A_BASE).pdb
	@-del /F /Q  $(INSTALL_STATIC_BIN_DIR_DBG)\$(PRG_NAME_A_DBG_BASE).pdb
	@-del /F /Q  $(INSTALL_STATIC_BIN_DIR_STLDBG)\$(PRG_NAME_A_STLDBG_BASE).pdb
