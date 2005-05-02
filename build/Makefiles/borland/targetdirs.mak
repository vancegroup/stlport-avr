# Time-stamp: 
# $Id: targetdirs.mak

!message build\Makefiles\borland\targetdirs.mak

!ifndef BCBX
BCBX = $(MAKEDIR)\..
!endif

!ifdef TARGET_PROC
TARGET_NAME=$(TARGET_PROC)_
!else
TARGET_NAME=
!endif

!ifndef STLPORT_DIR
!ifdef STLP_ROOT
STLPORT_DIR = $(STLP_ROOT:Directory of =)
!endif
!endif

OUTPUT_DIR          = obj\$(TARGET_NAME)$(COMPILER_NAME)\rel$(EXTRA_DIRS)
OUTPUT_DIR_DBG      = obj\$(TARGET_NAME)$(COMPILER_NAME)\dbg$(EXTRA_DIRS)
OUTPUT_DIR_STLDBG   = obj\$(TARGET_NAME)$(COMPILER_NAME)\stldbg$(EXTRA_DIRS)
OUTPUT_DIR_A        = obj\$(TARGET_NAME)$(COMPILER_NAME)\static$(EXTRA_DIRS)
OUTPUT_DIR_A_DBG    = obj\$(TARGET_NAME)$(COMPILER_NAME)\static_dbg$(EXTRA_DIRS)
OUTPUT_DIR_A_STLDBG = obj\$(TARGET_NAME)$(COMPILER_NAME)\static_stldbg$(EXTRA_DIRS)

DEPENDS_COLLECTION  = $(SRCROOT_EXT)\$(USE_MAKE)\depends.inc

INSTALL_LIB_DIR     = $(BCBX)\lib

INSTALL_DLL_DIR	    = $(WINSYSDIR)

INSTALL_BIN_DIR     = $(STLPORT_DIR)\bin

!ifdef ALL_TAGS
INSTALL_REL_TAGS    = $(ALL_TAGS:release=install-release)
INSTALL_DBG_TAGS    = $(INSTALL_REL_TAGS:dbg=install-dbg)
INSTALL_STLDBG_TAGS = $(INSTALL_DBG_TAGS:stlinstall-dbg=install-stldbg)
INSTALL_TAGS        = $(INSTALL_STLDBG_TAGS)
!endif

!ifndef INSTALL_TAGS
INSTALL_TAGS = install-release-shared install-dbg-shared install-stldbg-shared install-release-static install-dbg-static install-stldbg-static
!endif

system_msg :
	@echo BUILD_SYSTEM = $(BUILD_SYSTEM)

install: system_msg $(INSTALL_TAGS) del_tags
	@echo install done.

del_tags :
	@cd $(SRCROOT_EXT)\$(USE_MAKE)
	@if exist tag_srr.tmp del tag_srr.tmp
	@if exist tag_sdr.tmp del tag_sdr.tmp
	@if exist tag_sdd.tmp del tag_sdd.tmp
	@if exist tag_arr.tmp del tag_arr.tmp
	@if exist tag_adr.tmp del tag_adr.tmp
	@if exist tag_add.tmp del tag_add.tmp
	@cd $(SRCROOT_EXT)

SRR_TAGS = $(ALL_TAGS:release-shared=SRR)
SDD_TAGS = $(SRR_TAGS:stldbg-shared=SDD)
SDR_TAGS = $(SDD_TAGS:dbg-shared=SDR)
ARR_TAGS = $(SDR_TAGS:release-static=ARR)
ADD_TAGS = $(ARR_TAGS:stldbg-static=ADD)
ADR_TAGS = $(ADD_TAGS:dbg-static=ADR)
SET_TAGS = $(ADR_TAGS)

#!message SET_TAGS = $(SET_TAGS)

$(SET_TAGS) :
    @if not $& == SRR if not $& == SDR if not $& == SDD if not $& == ARR if not $& == ADR if not $& == ADD echo bad tag: $&

	@if $& == SRR echo tag: release-shared
	@if $& == SRR echo release-shared >> $(SRCROOT_EXT)\$(USE_MAKE)\tag_srr.tmp

	@if $& == SDR echo tag: dbg-shared
	@if $& == SDR echo dbg-shared >> $(SRCROOT_EXT)\$(USE_MAKE)\tag_sdr.tmp

	@if $& == SDD echo tag: stldbg-shared
	@if $& == SDD echo stldbg-shared >> $(SRCROOT_EXT)\$(USE_MAKE)\tag_sdd.tmp

	@if $& == ARR echo tag: release-static
	@if $& == ARR echo release-static >> $(SRCROOT_EXT)\$(USE_MAKE)\tag_arr.tmp

	@if $& == ADR echo tag: dbg-static
	@if $& == ADR echo dbg-static >> $(SRCROOT_EXT)\$(USE_MAKE)\tag_adr.tmp

	@if $& == ADD echo tag: stldbg-static
	@if $& == ADD echo stldbg-static >> $(SRCROOT_EXT)\$(USE_MAKE)\tag_add.tmp

OUTPUT_DIRS = \
		$(OUTPUT_DIR) \
        $(OUTPUT_DIR_DBG) \
		$(OUTPUT_DIR_STLDBG) \
		$(OUTPUT_DIR_A) \
		$(OUTPUT_DIR_A_DBG) \
		$(OUTPUT_DIR_A_STLDBG) 

dirs : $(OUTPUT_DIRS) depend_dir bin_dir

depend_dir :
	@if not exist .\$(USE_MAKE) mkdir .\$(USE_MAKE)

bin_dir:
	@if not exist $(STLPORT_DIR)\bin mkdir $(STLPORT_DIR)\bin

$(OUTPUT_DIRS) : del_tags $(SET_TAGS)

	@if not exist obj mkdir obj
	@if not exist obj\$(TARGET_NAME)$(COMPILER_NAME) mkdir obj\$(TARGET_NAME)$(COMPILER_NAME)

    @if $< == obj\$(TARGET_NAME)$(COMPILER_NAME)\rel if exist $(SRCROOT_EXT)\$(USE_MAKE)\tag_srr.tmp echo output dir: $<
	@if $< == obj\$(TARGET_NAME)$(COMPILER_NAME)\rel if exist $(SRCROOT_EXT)\$(USE_MAKE)\tag_srr.tmp if not exist obj\$(TARGET_NAME)$(COMPILER_NAME)\rel mkdir $<

    @if $< == obj\$(TARGET_NAME)$(COMPILER_NAME)\dbg if exist $(SRCROOT_EXT)\$(USE_MAKE)\tag_sdr.tmp echo output dir: $<
	@if $< == obj\$(TARGET_NAME)$(COMPILER_NAME)\dbg if exist $(SRCROOT_EXT)\$(USE_MAKE)\tag_sdr.tmp if not exist obj\$(TARGET_NAME)$(COMPILER_NAME)\dbg mkdir $<

    @if $< == obj\$(TARGET_NAME)$(COMPILER_NAME)\stldbg if exist $(SRCROOT_EXT)\$(USE_MAKE)\tag_sdd.tmp echo output dir: $<
	@if $< == obj\$(TARGET_NAME)$(COMPILER_NAME)\stldbg if exist $(SRCROOT_EXT)\$(USE_MAKE)\tag_sdd.tmp if not exist obj\$(TARGET_NAME)$(COMPILER_NAME)\stldbg mkdir $<

    @if $< == obj\$(TARGET_NAME)$(COMPILER_NAME)\static if exist $(SRCROOT_EXT)\$(USE_MAKE)\tag_arr.tmp echo output dir: $<
	@if $< == obj\$(TARGET_NAME)$(COMPILER_NAME)\static if exist $(SRCROOT_EXT)\$(USE_MAKE)\tag_arr.tmp if not exist obj\$(TARGET_NAME)$(COMPILER_NAME)\static mkdir $<

    @if $< == obj\$(TARGET_NAME)$(COMPILER_NAME)\static_dbg if exist $(SRCROOT_EXT)\$(USE_MAKE)\tag_adr.tmp echo output dir: $<
	@if $< == obj\$(TARGET_NAME)$(COMPILER_NAME)\static_dbg if exist $(SRCROOT_EXT)\$(USE_MAKE)\tag_adr.tmp if not exist obj\$(TARGET_NAME)$(COMPILER_NAME)\static_dbg mkdir $<

    @if $< == obj\$(TARGET_NAME)$(COMPILER_NAME)\static_stldbg if exist $(SRCROOT_EXT)\$(USE_MAKE)\tag_add.tmp echo output dir: $<
	@if $< == obj\$(TARGET_NAME)$(COMPILER_NAME)\static_stldbg if exist $(SRCROOT_EXT)\$(USE_MAKE)\tag_add.tmp if not exist obj\$(TARGET_NAME)$(COMPILER_NAME)\static_stldbg mkdir $<

STLP_ROOT :
	@cd $(RULESBASE)\$(USE_MAKE)
	@echo STLP_ROOT = \ > stlp_dir.inc
	@dir ..\..\..\.* | find /i "Directory of" >> stlp_dir.inc
	@cd $(RULESBASE)


