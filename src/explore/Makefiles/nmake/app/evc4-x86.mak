# -*- makefile -*- Time-stamp: <04/03/31 08:08:35 ptr>
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

LDFLAGS_COMMON = commctrl.lib coredll.lib $(CEx86Corelibc) corelibc.lib ccrtrtti.lib /nologo /base:"0x00010000" /stack:0x10000,0x1000 /entry:"WinMainCRTStartup" /incremental:yes /nodefaultlib:"OLDNAMES.lib" /nodefaultlib:"libc.lib" /subsystem:WINDOWSCE /MACHINE:IX86 
LDFLAGS_REL = $(LDFLAGS_REL) $(LDFLAGS_COMMON) $(LDSEARCH)
LDFLAGS_DBG = $(LDFLAGS_DBG) $(LDFLAGS_COMMON) $(LDSEARCH)
LDFLAGS_STLDBG = $(LDFLAGS_STLDBG) $(LDFLAGS_COMMON) $(LDSEARCH)
