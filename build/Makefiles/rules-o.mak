# -*- Makefile -*- Time-stamp: <03/10/27 17:19:13 ptr>
# $Id$

# Rules for release output:

$(OUTPUT_DIR)/%.o:	$(WORD1)%.cpp
	$(COMPILE.cc) $(OUTPUT_OPTION) $<

$(OUTPUT_DIR)/%.o:	$(WORD1)%.cc
	$(COMPILE.cc) $(OUTPUT_OPTION) $<

$(OUTPUT_DIR)/%.o:	$(WORD1)%.c
	$(COMPILE.c) $(OUTPUT_OPTION) $<

ifneq ($(OUTPUT_DIR),$(OUTPUT_DIR_A))

$(OUTPUT_DIR_A)/%.o:	$(WORD1)%.cpp
	$(COMPILE.cc) $(OUTPUT_OPTION) $<

$(OUTPUT_DIR_A)/%.o:	$(WORD1)%.cc
	$(COMPILE.cc) $(OUTPUT_OPTION) $<

$(OUTPUT_DIR_A)/%.o:	$(WORD1)%.c
	$(COMPILE.c) $(OUTPUT_OPTION) $<

endif

# Rules for debug output:

$(OUTPUT_DIR_DBG)/%.o:	$(WORD1)%.cpp
	$(COMPILE.cc) $(OUTPUT_OPTION) $<

$(OUTPUT_DIR_DBG)/%.o:	$(WORD1)%.cc
	$(COMPILE.cc) $(OUTPUT_OPTION) $<

$(OUTPUT_DIR_DBG)/%.o:	$(WORD1)%.c
	$(COMPILE.c) $(OUTPUT_OPTION) $<

ifneq ($(OUTPUT_DIR_DBG),$(OUTPUT_DIR_A_DBG))

$(OUTPUT_DIR_A_DBG)/%.o:	$(WORD1)%.cpp
	$(COMPILE.cc) $(OUTPUT_OPTION) $<

$(OUTPUT_DIR_A_DBG)/%.o:	$(WORD1)%.cc
	$(COMPILE.cc) $(OUTPUT_OPTION) $<

$(OUTPUT_DIR_A_DBG)/%.o:	$(WORD1)%.c
	$(COMPILE.c) $(OUTPUT_OPTION) $<

endif

# Rules for STLport debug output:

$(OUTPUT_DIR_STLDBG)/%.o:	$(WORD1)%.cpp
	$(COMPILE.cc) $(OUTPUT_OPTION) $<

$(OUTPUT_DIR_STLDBG)/%.o:	$(WORD1)%.cc
	$(COMPILE.cc) $(OUTPUT_OPTION) $<

$(OUTPUT_DIR_STLDBG)/%.o:	$(WORD1)%.c
	$(COMPILE.c) $(OUTPUT_OPTION) $<

ifneq ($(OUTPUT_DIR_STLDBG),$(OUTPUT_DIR_A_STLDBG))

$(OUTPUT_DIR_A_STLDBG)/%.o:	$(WORD1)%.cpp
	$(COMPILE.cc) $(OUTPUT_OPTION) $<

$(OUTPUT_DIR_A_STLDBG)/%.o:	$(WORD1)%.cc
	$(COMPILE.cc) $(OUTPUT_OPTION) $<

$(OUTPUT_DIR_A_STLDBG)/%.o:	$(WORD1)%.c
	$(COMPILE.c) $(OUTPUT_OPTION) $<

endif
