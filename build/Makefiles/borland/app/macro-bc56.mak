# -*- makefile -*- Time-stamp:
# $Id: macro-bc56.mak

!message build\Makefiles\borland\app\macro-bc56.mak

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

OPT_REL           = $(OPT_REL)           
OPT_DBG           = $(OPT_DBG)           
OPT_STLDBG        = $(OPT_STLDBG)        
OPT_STATIC        = $(OPT_STATIC)        
OPT_STATIC_DBG    = $(OPT_STATIC_DBG)    
OPT_STATIC_STLDBG = $(OPT_STATIC_STLDBG) 

LDFLAGS        = $(LDFLAGS)        
LDFLAGS_DBG    = $(LDFLAGS_DBG)    
LDFLAGS_STLDBG = $(LDFLAGS_STLDBG) 
