# -*- makefile -*- Time-stamp: <03/10/27 18:48:11 ptr>
# $Id$

# Static libraries tags

PHONY += release-static dbg-static stldbg-static

release-static: $(OUTPUT_DIR_A) ${A_NAME_OUT}

dbg-static:	$(OUTPUT_DIR_A_DBG) ${A_NAME_OUT_DBG}

stldbg-static:	$(OUTPUT_DIR_A_STLDBG) ${A_NAME_OUT_STLDBG}

${A_NAME_OUT}:	$(OBJ_A)
	$(AR) $(AR_INS_R) $(AR_OUT) $(OBJ_A)

${A_NAME_OUT_DBG}:	$(OBJ_A_DBG)
	$(AR) $(AR_INS_R) $(AR_OUT) $(OBJ_A_DBG)

${A_NAME_OUT_STLDBG}:	$(OBJ_A_STLDBG)
	$(AR) $(AR_INS_R) $(AR_OUT) $(OBJ_A_STLDBG)
