# -*- makefile -*- Time-stamp: <03/07/15 17:57:15 ptr>
# $Id$

dbg-shared:	$(OUTPUT_DIR_DBG) ${PRG_DBG}

stldbg-shared:	$(OUTPUT_DIR_STLDBG) ${PRG_STLDBG}

release-shared:	$(OUTPUT_DIR) ${PRG}

${PRG}:	$(OBJ) $(LIBSDEP)
	$(LINK.cc) $(LINK_OUTPUT_OPTION) $(OBJ) $(LDLIBS)

${PRG_DBG}:	$(OBJ_DBG) $(LIBSDEP)
	$(LINK.cc) $(LINK_OUTPUT_OPTION) $(OBJ_DBG) $(LDLIBS)

${PRG_STLDBG}:	$(OBJ_STLDBG) $(LIBSDEP)
	$(LINK.cc) $(LINK_OUTPUT_OPTION) $(OBJ_STLDBG) $(LDLIBS)

