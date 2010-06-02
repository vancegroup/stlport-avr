# -*- makefile -*- Time-stamp: <07/05/31 22:11:48 ptr>
#
# Copyright (c) 1997-1999, 2002, 2003, 2005-2007
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

# Static libraries tags

PHONY += release-static dbg-static stldbg-static

release-static: $(OUTPUT_DIR_A) ${A_NAME_OUT}

dbg-static:	$(OUTPUT_DIR_A_DBG) ${A_NAME_OUT_DBG}

stldbg-static:	$(OUTPUT_DIR_A_STLDBG) ${A_NAME_OUT_STLDBG}

${A_NAME_OUT}:	$(OBJ_A) $(_LSUPCPP_AUX_TSMP)
	rm -f $@
	$(AR) $(AR_INS_R) $(AR_OUT) $(OBJ_A) $(_LSUPCPP_AUX_OBJ)

${A_NAME_OUT_DBG}:	$(OBJ_A_DBG) $(_LSUPCPP_AUX_TSMP)
	rm -f $@
	$(AR) $(AR_INS_R) $(AR_OUT) $(OBJ_A_DBG) $(_LSUPCPP_AUX_OBJ)

${A_NAME_OUT_STLDBG}:	$(OBJ_A_STLDBG) $(_LSUPCPP_AUX_TSMP)
	rm -f $@
	$(AR) $(AR_INS_R) $(AR_OUT) $(OBJ_A_STLDBG) $(_LSUPCPP_AUX_OBJ)
