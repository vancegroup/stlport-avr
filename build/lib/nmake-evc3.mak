# -*- Makefile -*- Time-stamp: <04/05/01 00:46:11 ptr>
# $Id$

COMPILER_NAME=evc3
CEVERSION=300

!include nmake-evc-common.mak

!if "$(COMPILER_NAME)" == "evc4"
!error Error: Configured for evc4 but compiling with evc3 makefiles!
!endif
