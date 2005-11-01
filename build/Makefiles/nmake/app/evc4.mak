# -*- makefile -*- Time-stamp: <04/03/31 08:08:12 ptr>
# $Id$

LDFLAGS_COMMON = commctrl.lib coredll.lib corelibc.lib /nologo /base:"0x00010000" /stack:0x10000,0x1000 /entry:"WinMainCRTStartup" /incremental:no /subsystem:WINDOWSCE /align:"4096" /nodefaultlib:LIBC.lib /nodefaultlib:OLDNAMES.lib $(LDFLAGS_COMMON)

!if "$(TARGET_PROC)" == "arm"
LDFLAGS_COMMON = $(LDFLAGS_COMMON) /MACHINE:ARM
!if "$(PLATFORM)" == "POCKET PC 2003"
LDFLAGS_COMMON = $(LDFLAGS_COMMON) ccrtrtti.lib
!endif
!endif

!if "$(TARGET_PROC)" == "x86"
LDFLAGS_COMMON = $(LDFLAGS_COMMON) $(CEx86Corelibc) /MACHINE:IX86
!if "$(PLATFORM)" == "POCKET PC 2003"
LDFLAGS_COMMON = $(LDFLAGS_COMMON) ccrtrtti.lib
!endif
!endif

!if "$(TARGET_PROC)" == "mips"
LDFLAGS_COMMON = $(LDFLAGS_COMMON) /MACHINE:$(MIPS_MACHINE_TYPE)
!endif

!if "$(TARGET_PROC)" == "sh3"
LDFLAGS_COMMON = $(LDFLAGS_COMMON) /MACHINE:SH3
!endif

!if "$(TARGET_PROC)" == "sh4"
LDFLAGS_COMMON = $(LDFLAGS_COMMON) /MACHINE:SH4
!endif

!include evc-common.mak
