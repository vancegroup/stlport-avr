# -*- makefile -*- Time-stamp: <03/10/29 22:20:01 ptr>
# $Id$

clean:
	@-del /F /Q $(OUTPUT_DIR)\*.o $(OUTPUT_DIR)\*.obj
	@-del /F /Q $(OUTPUT_DIR_DBG)\*.o $(OUTPUT_DIR_DBG)\*.obj
	@-del /F /Q $(OUTPUT_DIR_STLDBG)\*.o $(OUTPUT_DIR_STLDBG)\*.obj
	@-del /F /Q $(OUTPUT_DIR_A)\*.o $(OUTPUT_DIR_A)\*.obj
	@-del /F /Q $(OUTPUT_DIR_A_DBG)\*.o $(OUTPUT_DIR_A_DBG)\*.obj
	@-del /F /Q $(OUTPUT_DIR_A_STLDBG)\*.o $(OUTPUT_DIR_A_STLDBG)\*.obj
