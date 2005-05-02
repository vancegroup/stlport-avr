# -*- makefile -*- Time-stamp: 
# $Id: clean.mak

!message build\Makefiles\borland\clean.mak

clean:
	@echo BUILD_SYSTEM = $(BUILD_SYSTEM)

	@cd $(SRCROOT_EXT)\$(USE_MAKE)
	@if exist *.tmp del /F /Q *.tmp
	@if exist objs_srr.dep del objs_srr.dep
	@if exist objs_sdr.dep del objs_sdr.dep
	@if exist objs_sdd.dep del objs_sdd.dep
	@if exist objs_arr.dep del objs_arr.dep
	@if exist objs_adr.dep del objs_adr.dep
	@if exist objs_add.dep del objs_add.dep

	@cd $(SRCROOT_EXT)
	@if exist $(OUTPUT_DIR)\*.obj del /F /Q $(OUTPUT_DIR)\*.obj
	@if exist $(OUTPUT_DIR)\*.tds del /F /Q $(OUTPUT_DIR)\*.tds
	@if exist $(OUTPUT_DIR)\*.map del /F /Q $(OUTPUT_DIR)\*.map

	@if exist $(OUTPUT_DIR_DBG)\*.obj del /F /Q $(OUTPUT_DIR_DBG)\*.obj
	@if exist $(OUTPUT_DIR_DBG)\*.tds del /F /Q $(OUTPUT_DIR_DBG)\*.tds
	@if exist $(OUTPUT_DIR_DBG)\*.map del /F /Q $(OUTPUT_DIR_DBG)\*.map

	@if exist $(OUTPUT_DIR_STLDBG)\*.obj del /F /Q $(OUTPUT_DIR_STLDBG)\*.obj
	@if exist $(OUTPUT_DIR_STLDBG)\*.tds del /F /Q $(OUTPUT_DIR_STLDBG)\*.tds 
	@if exist $(OUTPUT_DIR_STLDBG)\*.map del /F /Q $(OUTPUT_DIR_STLDBG)\*.map 

	@if exist $(OUTPUT_DIR_A)\*.obj del /F /Q $(OUTPUT_DIR_A)\*.obj
	@if exist $(OUTPUT_DIR_A)\*.tds del /F /Q $(OUTPUT_DIR_A)\*.tds
	@if exist $(OUTPUT_DIR_A)\*.bak del /F /Q $(OUTPUT_DIR_A)\*.bak

	@if exist $(OUTPUT_DIR_A_DBG)\*.obj del /F /Q $(OUTPUT_DIR_A_DBG)\*.obj
	@if exist $(OUTPUT_DIR_A_DBG)\*.tds del /F /Q $(OUTPUT_DIR_A_DBG)\*.tds
	@if exist $(OUTPUT_DIR_A_DBG)\*.bak del /F /Q $(OUTPUT_DIR_A_DBG)\*.bak

	@if exist $(OUTPUT_DIR_A_STLDBG)\*.obj del /F /Q $(OUTPUT_DIR_A_STLDBG)\*.obj
	@if exist $(OUTPUT_DIR_A_STLDBG)\*.tds del /F /Q $(OUTPUT_DIR_A_STLDBG)\*.tds
	@if exist $(OUTPUT_DIR_A_STLDBG)\*.bak del /F /Q $(OUTPUT_DIR_A_STLDBG)\*.bak

	@if exist $(RULESBASE)\$(USE_MAKE)\cur_date.inc del /F /Q $(RULESBASE)\$(USE_MAKE)\cur_date.inc
	@if exist $(RULESBASE)\$(USE_MAKE)\cur_time.inc del /F /Q $(RULESBASE)\$(USE_MAKE)\cur_time.inc
	@if exist $(RULESBASE)\$(USE_MAKE)\timezone.inc del /F /Q $(RULESBASE)\$(USE_MAKE)\timezone.inc
	@if exist $(RULESBASE)\$(USE_MAKE)\os_rel.inc del /F /Q $(RULESBASE)\$(USE_MAKE)\os_rel.inc
	@if exist $(RULESBASE)\$(USE_MAKE)\hostname.inc del /F /Q $(RULESBASE)\$(USE_MAKE)\hostname.inc
	@if exist $(RULESBASE)\$(USE_MAKE)\sysver.inc del /F /Q $(RULESBASE)\$(USE_MAKE)\sysver.inc
	@if exist $(RULESBASE)\$(USE_MAKE)\windir.inc del /F /Q $(RULESBASE)\$(USE_MAKE)\windir.inc
	@if exist $(RULESBASE)\$(USE_MAKE)\stlp_dir.inc del /F /Q $(RULESBASE)\$(USE_MAKE)\stlp_dir.inc
	
#	@echo. > $(RULESBASE)\$(USE_MAKE)\sysid.inc
	@echo. > $(SRCROOT_EXT)\$(USE_MAKE)\depends.inc

	@echo clean done.
