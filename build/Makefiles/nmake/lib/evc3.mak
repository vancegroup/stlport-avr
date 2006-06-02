# -*- makefile -*- Time-stamp: <04/05/01 00:34:42 ptr>
# $Id$

LDFLAGS_COMMON = $(LDFLAGS_COMMON) /base:"0x00100000"

# TODO: ../app/evc3.mak doesn't exclude oldnames.lib and has machine=IX86, 
# double-check if that is right and merge them both into ../evc3.mak if not.
!if "$(TARGET_PROC)" == "x86"
LDFLAGS_COMMON = $(LDFLAGS_COMMON) /nodefaultlib:"OLDNAMES.lib" /MACHINE:X86
!endif

!include evc-common.mak
