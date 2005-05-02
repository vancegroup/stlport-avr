# Time-stamp: <03/07/15 12:20:52 ptr>
# $Id$

depend: dirs DEP_INIT $(ALLBASE) $(ALLBASE_A) DEP_END CUR_DATE CUR_TIME GMT_OFFSET OSREL IP_HOSTNAME WINSYSDIR SYSVER STLP_ROOT
#depend: dirs DEP_INIT DEP_END CUR_DATE CUR_TIME GMT_OFFSET OSREL IP_HOSTNAME WINSYSDIR SYSVER STLP_ROOT
	@cd $(RULESBASE)\$(USE_MAKE)
	@copy cur_date.inc + cur_time.inc + timezone.inc + os_rel.inc + hostname.inc + sysver.inc + windir.inc + stlp_dir.inc + stlp_ver.inc sysid.inc > NUL
	@cd $(SRCROOT_EXT)
!ifdef $(SYSVER)
	@echo BUILD_SYSTEM = $(BUILD_SYSTEM)
!endif
	@echo depend done.

.precious: depend

DEP_INIT :
	@cd $(SRCROOT_EXT)\$(USE_MAKE)
	@if exist dep_srr.tmp del dep_srr.tmp
	@if exist dep_sdr.tmp del dep_sdr.tmp
	@if exist dep_sdd.tmp del dep_sdd.tmp
	@if exist dep_arr.tmp del dep_arr.tmp
	@if exist dep_adr.tmp del dep_adr.tmp
	@if exist dep_add.tmp del dep_add.tmp
	@if exist objs_srr.dep del objs_srr.dep
	@if exist objs_sdr.dep del objs_sdr.dep
	@if exist objs_sdd.dep del objs_sdd.dep
	@if exist objs_arr.dep del objs_arr.dep
	@if exist objs_adr.dep del objs_adr.dep
	@if exist objs_add.dep del objs_add.dep
	@echo OBJ          = \ > dep_srr.tmp
	@echo OBJ_DBG      = \ > dep_sdr.tmp
	@echo OBJ_STLDBG   = \ > dep_sdd.tmp
	@echo OBJ_A        = \ > dep_arr.tmp
	@echo OBJ_A_DBG    = \ > dep_adr.tmp
	@echo OBJ_A_STLDBG = \ > dep_add.tmp
	@cd $(SRCROOT_EXT)

DEP_END :
	@cd $(SRCROOT_EXT)\$(USE_MAKE)
	@echo. >> dep_srr.tmp
	@echo. >> dep_sdr.tmp
	@echo. >> dep_sdd.tmp
	@echo. >> dep_arr.tmp
	@echo. >> dep_adr.tmp
	@echo. >> dep_add.tmp
	@copy dep_srr.tmp + dep_sdr.tmp + dep_sdd.tmp + dep_arr.tmp + dep_adr.tmp + dep_add.tmp depends.inc > NUL
	@cd $(SRCROOT_EXT)

$(ALLBASE) :

	@cd $(SRCROOT_EXT)\$(USE_MAKE)
	@echo $&.obj
	@echo $(SRCROOT_EXT)\$(OUTPUT_DIR)\$&.obj \ >> dep_srr.tmp
	@echo $(SRCROOT_EXT)\$(OUTPUT_DIR_DBG)\$&.obj \ >> dep_sdr.tmp
	@echo $(SRCROOT_EXT)\$(OUTPUT_DIR_STLDBG)\$&.obj \ >> dep_sdd.tmp
	@echo $(SRCROOT_EXT)\$(OUTPUT_DIR)\$&.obj + >> objs_srr.dep
	@echo $(SRCROOT_EXT)\$(OUTPUT_DIR_DBG)\$&.obj + >> objs_sdr.dep
	@echo $(SRCROOT_EXT)\$(OUTPUT_DIR_STLDBG)\$&.obj + >> objs_sdd.dep


#!if $(LIBNAME) == stlp$(MAJOR)$(MINOR)
#	@cd $(SRCROOT_EXT)

#$(ALLBASE_A):
#	@cd $(SRCROOT_EXT)\$(USE_MAKE)
#	@echo $&.obj
#!endif

	@echo $(SRCROOT_EXT)\$(OUTPUT_DIR_A)\$&.obj \ >> dep_arr.tmp
	@echo $(SRCROOT_EXT)\$(OUTPUT_DIR_A_DBG)\$&.obj \ >> dep_adr.tmp
	@echo $(SRCROOT_EXT)\$(OUTPUT_DIR_A_STLDBG)\$&.obj \ >> dep_add.tmp
	@echo $(SRCROOT_EXT)\$(OUTPUT_DIR_A)\$&.obj + >> objs_arr.dep
	@echo $(SRCROOT_EXT)\$(OUTPUT_DIR_A_DBG)\$&.obj + >> objs_adr.dep
	@echo $(SRCROOT_EXT)\$(OUTPUT_DIR_A_STLDBG)\$&.obj + >> objs_add.dep
	@cd $(SRCROOT_EXT)

!if $(LIBNAME) != stlp$(MAJOR)$(MINOR)
#$(ALLBASE_A):
!endif

!include $(DEPENDS_COLLECTION)

NULLTARGET3 :
	@echo dollar-sign star
	@echo $*
	@echo.
	@echo dollar-sign less-than
	@echo $<
	@echo.
	@echo dollar-sign colon
	@echo $:
	@echo.
	@echo dollar-sign period
	@echo $.
	@echo.
	@echo dollar-sign ampersand
	@echo $&
	@echo.
	@echo dollar-sign 'at' symbol
	@echo $@
	@echo.

info: CUR_DATE CUR_TIME GMT_OFFSET OSREL IP_HOSTNAME WINSYSDIR SYSVER STLP_ROOT
	@cd $(RULESBASE)\$(USE_MAKE)
	@copy cur_date.inc + cur_time.inc + timezone.inc + os_rel.inc + hostname.inc + sysver.inc + windir.inc + stlp_dir.inc + stlp_ver.inc sysid.inc > NUL
	@cd $(SRCROOT_EXT)
	@echo STLP_SNAPSHOT = $(STLP_SNAPSHOT)
	@echo STLP_PUB_DATE = $(STLP_PUB_DATE)
	@echo STLPORT_DIR = $(STLPORT_DIR)
	@echo BUILD_DATE = $(BUILD_DATE)
	@echo M_ARCH = $(M_ARCH)
	@echo OSNAME = $(OSNAME)
	@echo OSREL = $(OSREL)
	@echo SYSVER = $(SYSVER)
	@echo WINSYSDIR = $(WINSYSDIR)
	@echo NODENAME = $(NODENAME)
	@echo USER = $(USER)
	@echo BUILD_SYSTEM = $(BUILD_SYSTEM)
