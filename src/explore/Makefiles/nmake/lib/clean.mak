# -*- makefile -*- Time-stamp: <03/10/26 16:17:03 ptr>
# $Id$

clobber:	clean
	@-del /F /Q $(SO_NAME_OUT)
	@-del /F /Q  $(LIB_NAME_OUT)
	@-del /F /Q  $(EXP_NAME_OUT)
	@-del /F /Q  $(A_NAME_OUT)
	@-del /F /Q  $(SO_NAME_OUT_DBG)
	@-del /F /Q  $(LIB_NAME_OUT_DBG)
	@-del /F /Q  $(EXP_NAME_OUT_DBG)
	@-del /F /Q  $(A_NAME_OUT_DBG)
	@-del /F /Q  $(SO_NAME_OUT_STLDBG)
	@-del /F /Q  $(LIB_NAME_OUT_STLDBG)
	@-del /F /Q  $(EXP_NAME_OUT_STLDBG)
	@-del /F /Q  $(A_NAME_OUT_STLDBG)

distclean:	clobber
	@-del /F /Q  $(INSTALL_LIB_DIR)/$(SO_NAME)
	@-del /F /Q  $(INSTALL_LIB_DIR)/$(LIB_NAME)
	@-del /F /Q  $(INSTALL_LIB_DIR)/$(EXP_NAME)
	@-del /F /Q  $(INSTALL_LIB_DIR)/$(A_NAME)
	@-del /F /Q  $(INSTALL_LIB_DIR_DBG)/$(SO_NAME_DBG)
	@-del /F /Q  $(INSTALL_LIB_DIR_DBG)/$(LIB_NAME_DBG)
	@-del /F /Q  $(INSTALL_LIB_DIR_DBG)/$(EXP_NAME_DBG)
	@-del /F /Q  $(INSTALL_LIB_DIR_DBG)/$(A_NAME_DBG)
	@-del /F /Q  $(INSTALL_LIB_DIR_STLDBG)/$(SO_NAME_STLDBG)
	@-del /F /Q  $(INSTALL_LIB_DIR_STLDBG)/$(LIB_NAME_STLDBG)
	@-del /F /Q  $(INSTALL_LIB_DIR_STLDBG)/$(EXP_NAME_STLDBG)
	@-del /F /Q  $(INSTALL_LIB_DIR_STLDBG)/$(A_NAME_STLDBG)
