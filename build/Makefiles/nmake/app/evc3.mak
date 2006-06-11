# -*- makefile -*- Time-stamp: <04/05/01 00:46:25 ptr>
# $Id$

LDFLAGS_COMMON = $(LDFLAGS_COMMON) /base:"0x00010000" /nodefaultlib:"OLDNAMES.lib" /entry:"mainACRTStartup"

# TODO: ../lib/evc3.mak excludes oldnames.lib and has machine=IX86, 
# double-check if that is right and merge them both into ../evc3.mak if not.
!if "$(TARGET_PROC)" == "x86"
LDFLAGS_COMMON = $(LDFLAGS_COMMON) /MACHINE:IX86
!endif

!include evc-common.mak
