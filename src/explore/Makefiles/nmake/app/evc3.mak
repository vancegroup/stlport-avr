# -*- makefile -*- Time-stamp: <04/05/01 00:46:25 ptr>
# $Id$

!ifndef LDLIBS
LDLIBS =
!endif

LDSEARCH = $(LDSEARCH)

OPT_DBG = $(OPT_DBG)
OPT_STLDBG = $(OPT_STLDBG)
OPT_REL = $(OPT_REL)
OPT_DBG_STATIC = $(OPT_DBG_STATIC)
OPT_STLDBG_STATIC = $(OPT_STLDBG_STATIC)
OPT_REL_STATIC = $(OPT_REL_STATIC)

LDFLAGS_COMMON = commctrl.lib coredll.lib corelibc.lib /nologo /base:"0x00010000" /stack:0x10000,0x1000 /entry:"WinMainCRTStartup" /incremental:yes /nodefaultlib:"libc.lib" /subsystem:WINDOWSCE /align:"4096" /MACHINE:ARM
!if "$(TARGET_PROC)" == "arm"
LDFLAGS_COMMON = $(LDFLAGS_COMMON) /nodefaultlib:"OLDNAMES.lib" /MACHINE:ARM
!else
LDFLAGS_COMMON = $(LDFLAGS_COMMON) $(CEx86Corelibc) /nodefaultlib:"OLDNAMES.lib" /MACHINE:IX86
!endif
LDFLAGS_REL = $(LDFLAGS_REL) $(LDFLAGS_COMMON) $(LDSEARCH)
LDFLAGS_DBG = $(LDFLAGS_DBG) $(LDFLAGS_COMMON) $(LDSEARCH)
LDFLAGS_STLDBG = $(LDFLAGS_STLDBG) $(LDFLAGS_COMMON) $(LDSEARCH)
