# -*- makefile -*- Time-stamp: 
# $Id: rules-a.mak

!message build\Makefiles\borland\lib\rules-a.mak

# static libraries tags

.AUTODEPEND

clean-outa :
		@if exist $(A_NAME_OUT) del /F /Q $(A_NAME_OUT)
		@if exist $(OUTPUT_DIR_A)\stlp500.obj del /F /Q $(OUTPUT_DIR_A)\stlp500.obj

clean-outa-dbg :
		@if exist $(A_NAME_OUT_DBG) del /F /Q $(A_NAME_OUT_DBG)
		@if exist $(OUTPUT_DIR_A_DBG)\stlp500.obj del /F /Q $(OUTPUT_DIR_A_DBG)\stlp500.obj

clean-outa-stldbg :
		@if exist $(A_NAME_OUT_STLDBG) del /F /Q $(A_NAME_OUT_STLDBG)
		@if exist $(OUTPUT_DIR_A_STLDBG)\stlp500.obj del /F /Q $(OUTPUT_DIR_A_STLDBG)\stlp500.obj

release-static: clean-outa $(A_NAME_OUT)

dbg-static:     clean-outa-dbg $(A_NAME_OUT_DBG)

stldbg-static:  clean-outa-stldbg $(A_NAME_OUT_STLDBG)

$(A_NAME_OUT) : $(OBJ_A)  
		@echo $(A_NAME_OUT) (release-static)
		@cd $(OUTPUT_DIR_A)
		$(AR) $(A_NAME) $(AR_EXTR) +-$(ALLOBJS_A) > $(SRCROOT_EXT)\$(USE_MAKE)\tlib_arr.tmp
		@cd $(SRCROOT_EXT)
		@if exist $(OUTPUT_DIR_A)\*.tds del /F /Q $(OUTPUT_DIR_A)\*.tds

$(A_NAME_OUT_DBG) : $(OBJ_A_DBG) 
		@echo $(A_NAME_OUT_DBG) (dbg-static)
		@cd $(OUTPUT_DIR_A_DBG)
		$(AR) $(A_NAME_DBG) $(AR_EXTR) +-$(ALLOBJS_A) > $(SRCROOT_EXT)\$(USE_MAKE)\tlib_adr.tmp
		@cd $(SRCROOT_EXT)
		@if exist $(OUTPUT_DIR_A_DBG)\*.tds del /F /Q $(OUTPUT_DIR_A_DBG)\*.tds

$(A_NAME_OUT_STLDBG) : $(OBJ_A_STLDBG) 
		@echo $(A_NAME_OUT_STLDBG) (stldbg-static)
		@cd $(OUTPUT_DIR_A_STLDBG)
		$(AR) $(A_NAME_STLDBG) $(AR_EXTR) +-$(ALLOBJS_A) > $(SRCROOT_EXT)\$(USE_MAKE)\tlib_add.tmp
		@cd $(SRCROOT_EXT)
		@if exist $(OUTPUT_DIR_A_STLDBG)\*.tds del /F /Q $(OUTPUT_DIR_A_STLDBG)\*.tds

