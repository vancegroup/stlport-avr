# -*- Makefile -*- Time-stamp: 
# $Id: bc56.mak

!message lib\bc56.mak

.AUTODEPEND

COMPILER_NAME = bc56

!ifndef BCBX
BCBX          = \CBuilderX
!endif

STLPORT_DIR   = $(BCBX)\STLport-500-RC2-edited
SRCROOT       = $(STLPORT_DIR)\build
SRCROOT_EXT   = $(SRCROOT)\lib
SRCDIR        = $(STLPORT_DIR)\src
SRCDIR_A      = $(SRCROOT_EXT)\borland

ALL_TAGS     = release-shared dbg-shared stldbg-shared release-static dbg-static stldbg-static

SO_NOINIT     = 1
A_NOINIT     = 1

!include .\borland\Make_O.inc
!include .\borland\Make_A.inc

INCLUDES      = 

DEFS          = -D__BUILDING_STLPORT=1;__BUILDING_STLPORT_LIBS

!include $(SRCROOT)\Makefiles\borland\top.mak
