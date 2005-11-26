# -*- makefile -*- Time-stamp: <03/10/27 18:15:05 ptr>
# $Id$

# Shared libraries tags

PHONY += release-shared dbg-shared stldbg-shared

release-shared:	$(OUTPUT_DIR) ${SO_NAME_OUT}

dbg-shared:	$(OUTPUT_DIR_DBG) ${SO_NAME_OUT_DBG}

stldbg-shared:	$(OUTPUT_DIR_STLDBG) ${SO_NAME_OUT_STLDBG}

${SO_NAME_OUT}:	$(OBJ) $(RES) $(LIBSDEP)
ifneq (dmc, $(COMPILER_NAME))
	$(LINK.cc) $(LINK_OUTPUT_OPTION) $(OBJ) $(RES) $(LDLIBS)
else
	$(LINK.cc) $(LINK_OUTPUT_OPTION) $(subst /,\,$(OBJ) $(RES) $(LDLIBS))
endif

ifneq (bcc, $(COMPILER_NAME))
${SO_NAME_OUT_DBG}:	$(OBJ_DBG) $(RES_DBG) $(LIBSDEP)
ifneq (dmc, $(COMPILER_NAME))
	$(LINK.cc) $(LINK_OUTPUT_OPTION) $(OBJ_DBG) $(RES_DBG) $(LDLIBS)
else
	$(LINK.cc) $(LINK_OUTPUT_OPTION) $(subst /,\,$(OBJ_DBG) $(RES_DBG) $(LDLIBS))
endif
else
${SO_NAME_OUT_DBG}:	$(OBJ_DBG) $(RES_DBG) $(LIBSDEP)
	$(LINK.cc) $(subst /,\,$(OBJ_DBG),$(LINK_OUTPUT_OPTION),,$(LDLIBS),,$(RES_DBG))
endif

${SO_NAME_OUT_STLDBG}:	$(OBJ_STLDBG) $(RES_STLDBG) $(LIBSDEP)
ifneq (dmc, $(COMPILER_NAME))
	$(LINK.cc) $(LINK_OUTPUT_OPTION) $(OBJ_STLDBG) $(RES_STLDBG) $(LDLIBS)
else
	$(LINK.cc) $(LINK_OUTPUT_OPTION) $(subst /,\,$(OBJ_STLDBG) $(RES_STLDBG) $(LDLIBS))
endif

