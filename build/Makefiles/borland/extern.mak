# Time-stamp: 
# $Id: extern.mak

!message build\Makefiles\borland\extern.mak

.AUTODEPEND

!ifndef BCBX
BCBX = $(MAKEDIR)\..
!endif

!ifndef BCBX_LIB_DIR
BCBX_LIB_DIR = $(BCBX)\lib
!endif

!ifndef BCBX_INCLUDE_DIR
BCBX_INCLUDE_DIR = $(BCBX)\include
!endif

!ifndef STLPORT_DIR
STLPORT_DIR = $(BCBX)\STLport-5.0.0
!endif

# This file reflect versions of third-party libraries that
# used in projects

# STLport library
!ifndef STLPORT_LIB_DIR
STLPORT_LIB_DIR = $(STLPORT_DIR)\lib
!endif

!ifndef STLPORT_INCLUDE_DIR
STLPORT_INCLUDE_DIR = $(STLPORT_DIR)\stlport
!endif

!ifndef STLPORT_VER
STLPORT_VER = 5.0.0
!endif

