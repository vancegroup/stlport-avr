# -*- makefile -*- Time-stamp: 
# $Id: rules-so.mak

!message build\Makefiles\borland\lib\rules-so.mak

.AUTODEPEND

# Shared libraries tags

clean-out :
		@if exist $(SO_NAME_OUT) del /F /Q $(SO_NAME_OUT)
		@if exist $(LIB_NAME_OUT) del /F /Q $(LIB_NAME_OUT)

clean-out-dbg :
		@if exist $(SO_NAME_OUT_DBG) del /F /Q $(SO_NAME_OUT_DBG)
		@if exist $(LIB_NAME_OUT_DBG) del /F /Q $(LIB_NAME_OUT_DBG)

clean-out-stldbg :
		@if exist $(SO_NAME_OUT_STLDBG) del /F /Q $(SO_NAME_OUT_STLDBG)
		@if exist $(LIB_NAME_OUT_STLDBG) del /F /Q $(LIB_NAME_OUT_STLDBG)

release-shared: clean-out $(SO_NAME_OUT)

dbg-shared:     clean-out-dbg $(SO_NAME_OUT_DBG)

stldbg-shared:  clean-out-stldbg $(SO_NAME_OUT_STLDBG)

$(SO_NAME_OUT): $(OBJ)
		$(LINK_cpp_REL) $(STARTUPDLL) @$(SRCROOT_EXT)\$(USE_MAKE)\objs_srr.dep,$(SO_NAME_OUT),,$(LDLIBS),$(DEF_FILE),$(RES)
		@if exist $(OUTPUT_DIR)\*.tds del /F /Q $(OUTPUT_DIR)\*.tds

$(SO_NAME_OUT_DBG): $(OBJ_DBG)
		$(LINK_cpp_DBG) $(STARTUPDLL) @$(SRCROOT_EXT)\$(USE_MAKE)\objs_sdr.dep,$(SO_NAME_OUT_DBG),,$(LDLIBS),$(DEF_FILE_DBG),$(RES_DBG)
		@if exist $(OUTPUT_DIR_DBG)\*.tds del /F /Q $(OUTPUT_DIR_DBG)\*.tds

$(SO_NAME_OUT_STLDBG): $(OBJ_STLDBG) 
		$(LINK_cpp_STLDBG) $(STARTUPDLL) @$(SRCROOT_EXT)\$(USE_MAKE)\objs_sdd.dep,$(SO_NAME_OUT_STLDBG),,$(LDLIBS),$(DEF_FILE_STLDBG),$(RES_STLDBG)
		@if exist $(OUTPUT_DIR_STLDBG)\*.tds del /F /Q $(OUTPUT_DIR_STLDBG)\*.tds

