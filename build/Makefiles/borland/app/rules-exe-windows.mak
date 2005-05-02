# -*- makefile -*- Time-stamp: 
# $Id: rules-exe-windows.mak

!message build\Makefiles\borland\app\rules-exe-windows.mak

.AUTODEPEND

clean-prg :
		@if exist $(PRG) del /F /Q $(PRG)

clean-prg-dbg :
		@if exist $(PRG_DBG) del /F /Q $(PRG_DBG)

clean-prg-stldbg :
		@if exist $(PRG_STLDBG) del /F /Q $(PRG_STLDBG)

clean-prga :
		@if exist $(PRG_A) del /F /Q $(PRG_A)

clean-prga-dbg :
		@if exist $(PRG_A_DBG) del /F /Q $(PRG_A_DBG)

clean-prga-stldbg :
		@if exist $(PRG_A_STLDBG) del /F /Q $(PRG_A_STLDBG)

release-shared : clean-prg $(PRG) 

dbg-shared     : clean-prg-dbg $(PRG_DBG)

stldbg-shared  : clean-prg-stldbg $(PRG_STLDBG)

release-static : clean-prga $(PRG_A) 

dbg-static     : clean-prga-dbg $(PRG_A_DBG)

stldbg-static  : clean-prga-stldbg $(PRG_A_STLDBG)


$(PRG) : $(OBJ)
		@echo $(PRG) (release-shared)
        $(LINK_cpp_REL) $(STARTUPCON) @$(SRCROOT_EXT)\$(USE_MAKE)\objs_srr.dep,$(PRG),,$(LDLIBS),$(DEF_FILE),$(RES)
		@if exist $(OUTPUT_DIR)\*.tds del /F /Q $(OUTPUT_DIR)\*.tds

$(PRG_DBG) : $(OBJ_DBG)
		@echo $(PRG_DBG) (dbg-shared)
        $(LINK_cpp_DBG) $(STARTUPCON) @$(SRCROOT_EXT)\$(USE_MAKE)\objs_sdr.dep,$(PRG_DBG),,$(LDLIBS),$(DEF_FILE_DBG),$(RES_DBG)
		@if exist $(OUTPUT_DIR_DBG)\*.tds del /F /Q $(OUTPUT_DIR_DBG)\*.tds

$(PRG_STLDBG) : $(OBJ_STLDBG) 
		@echo $(PRG_STLDBG) (stldbg-shared)
        $(LINK_cpp_STLDBG) $(STARTUPCON) @$(SRCROOT_EXT)\$(USE_MAKE)\objs_sdd.dep,$(PRG_STLDBG),,$(LDLIBS),$(DEF_FILE_STLDBG),$(RES_STLDBG)
		@if exist $(OUTPUT_DIR_STLDBG)\*.tds del /F /Q $(OUTPUT_DIR_STLDBG)\*.tds

$(PRG_A) : $(OBJ_A)
		@echo $(PRG_A) (release-static)
        $(LINK_cpp_STATIC) $(STARTUPCON) @$(SRCROOT_EXT)\$(USE_MAKE)\objs_arr.dep,$(SRCROOT_EXT)\$(PRG_A),,$(LDLIBS_STATIC),$(DEF_FILE_A),$(RES)
		@if exist $(OUTPUT_DIR_A)\*.tds del /F /Q $(OUTPUT_DIR_A)\*.tds

$(PRG_A_DBG) : $(OBJ_A_DBG)
		@echo $(PRG_A_DBG) (dbg-static)
        $(LINK_cpp_STATIC_DBG) $(STARTUPCON) @$(SRCROOT_EXT)\$(USE_MAKE)\objs_adr.dep,$(SRCROOT_EXT)\$(PRG_A_DBG),,$(LDLIBS_STATIC),$(DEF_FILE_A_DBG),$(RES_DBG)
		@if exist $(OUTPUT_DIR_A_DBG)\*.tds del /F /Q $(OUTPUT_DIR_A_DBG)\*.tds

$(PRG_A_STLDBG) : $(OBJ_A_STLDBG)
		@echo $(PRG_A_STLDBG) (stldbg-static)
        $(LINK_cpp_STATIC_STLDBG) $(STARTUPCON) @$(SRCROOT_EXT)\$(USE_MAKE)\objs_add.dep,$(SRCROOT_EXT)\$(PRG_A_STLDBG),,$(LDLIBS_STATIC),$(DEF_FILE_A_STLDBG),$(RES_STLDBG)
		@if exist $(OUTPUT_DIR_A_STLDBG)\*.tds del /F /Q $(OUTPUT_DIR_A_STLDBG)\*.tds

