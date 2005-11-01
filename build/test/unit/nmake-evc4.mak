# -*- Makefile -*- Time-stamp: <04/03/31 08:14:15 ptr>
# $Id$

COMPILER_NAME=evc4
CEVERSION=420

!if "$(TARGET_PROC)" == "arm"
OPT_STATIC_STLDBG = /Zm800
!endif

!include nmake-evc-common.mak

!if "$(COMPILER_NAME)" == "evc3"
!error Error: Configured for evc3 but compiling with evc4 makefiles!
!endif
