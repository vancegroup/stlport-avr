# -*- makefile -*- Time-stamp: 
# $Id: bc56.mak,

!message build\Makefiles\borland\app\bc56.mak

.AUTODEPEND

!ifndef LDLIBS
LDLIBS        = import32.lib cw32mti.lib
LDLIBS_STATIC = import32.lib cw32mt.lib
STARTUPCON    = c0x32.obj
STARTUPDLL    = c0d32.obj
STARTUPWIN    = c0w32.obj
!endif

!ifndef LDSEARCH
LDSEARCH = -L$(BCBX_LIB_DIR)
!endif

OPT_REL           = $(OPT_REL)           -tWC
OPT_DBG           = $(OPT_DBG)           -tWC
OPT_STLDBG        = $(OPT_STLDBG)        -tWC
OPT_STATIC        = $(OPT_STATIC)        -tWC
OPT_STATIC_DBG    = $(OPT_STATIC_DBG)    -tWC
OPT_STATIC_STLDBG = $(OPT_STATIC_STLDBG) -tWC

LDFLAGS        = $(LDFLAGS)        $(LDSEARCH)
LDFLAGS_DBG    = $(LDFLAGS_DBG)    $(LDSEARCH)
LDFLAGS_STLDBG = $(LDFLAGS_STLDBG) $(LDSEARCH)
