# -*- Makefile -*- Time-stamp: <04/03/31 00:35:47 ptr>
# $Id$

COMPILER_NAME=evc4
CEVERSION=420

!include nmake-evc-common.mak

!if "$(COMPILER_NAME)" == "evc3"
!error Error: Configured for evc3 but compiling with evc4 makefiles!
!endif
