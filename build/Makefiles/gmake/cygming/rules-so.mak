# -*- makefile -*- Time-stamp: <03/10/27 18:15:05 ptr>
# $Id$

# Shared libraries tags

PHONY += release-shared dbg-shared stldbg-shared

release-shared:	$(OUTPUT_DIR) ${SO_NAME_OUT}

dbg-shared:	$(OUTPUT_DIR_DBG) ${SO_NAME_OUT_DBG}

stldbg-shared:	$(OUTPUT_DIR_STLDBG) ${SO_NAME_OUT_STLDBG}

ifeq (bcc, $(COMPILER_NAME))
# Borland linker
${SO_NAME_OUT}:	$(OBJ) $(RES) $(LIBSDEP)
	$(LINK.cc) $(subst /,\,$(START_OBJ) $(OBJ) $(END_OBJ), $(LINK_OUTPUT_OPTION), , $(LDLIBS), , $(RES))
${SO_NAME_OUT_DBG}:	$(OBJ_DBG) $(RES_DBG) $(LIBSDEP)
	$(LINK.cc) $(subst /,\,$(START_OBJ) $(OBJ_DBG) $(END_OBJ), $(LINK_OUTPUT_OPTION), , $(LDLIBS), , $(RES_DBG))
${SO_NAME_OUT_STLDBG}:	$(OBJ_STLDBG) $(RES_STLDBG) $(LIBSDEP)
	$(LINK.cc) $(subst /,\,$(START_OBJ) $(OBJ_STLDBG) $(END_OBJ), $(LINK_OUTPUT_OPTION), , $(LDLIBS), , $(RES_STLDBG))
else
ifeq (dmc, $(COMPILER_NAME))
# Digital Mars linker
${SO_NAME_OUT}:	$(OBJ) $(RES) $(LIBSDEP)
	$(LINK.cc) $(subst /,\,$(OBJ), $(LINK_OUTPUT_OPTION),, $(LDLIBS),,$(RES))
${SO_NAME_OUT_DBG}: $(OBJ_DBG) $(RES_DBG) $(LIBSDEP)
	$(LINK.cc) $(subst /,\,$(OBJ_DBG), $(LINK_OUTPUT_OPTION),, $(LDLIBS),,$(RES_DBG))
${SO_NAME_OUT_STLDBG}:	$(OBJ_STLDBG) $(RES_STLDBG) $(LIBSDEP)
	$(LINK.cc) $(subst /,\,$(OBJ_STLDBG), $(LINK_OUTPUT_OPTION),, $(LDLIBS),,$(RES_STLDBG))
else
# GNU linker
${SO_NAME_OUT}:	$(OBJ) $(RES) $(LIBSDEP)
	$(LINK.cc) $(LINK_OUTPUT_OPTION) $(OBJ) $(RES) $(LDLIBS)
${SO_NAME_OUT_DBG}:	$(OBJ_DBG) $(RES_DBG) $(LIBSDEP)
	$(LINK.cc) $(LINK_OUTPUT_OPTION) $(OBJ_DBG) $(RES_DBG) $(LDLIBS)
${SO_NAME_OUT_STLDBG}:	$(OBJ_STLDBG) $(RES_STLDBG) $(LIBSDEP)
	$(LINK.cc) $(LINK_OUTPUT_OPTION) $(OBJ_STLDBG) $(RES_STLDBG) $(LDLIBS)
endif
endif
