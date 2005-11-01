# -*- Makefile -*- Time-stamp: <04/03/31 08:14:15 ptr>
# $Id$

COMPILER_NAME=evc3
CEVERSION=300

!include nmake-evc-common.mak

!if "$(COMPILER_NAME)" == "evc4"
!error Error: Configured for evc4 but compiling with evc3 makefiles!
!endif
