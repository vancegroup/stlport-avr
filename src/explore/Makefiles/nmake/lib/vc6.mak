# -*- makefile -*- Time-stamp: <03/10/17 14:09:57 ptr>
# $Id$


# Oh, the commented below work for gmake 3.78.1 and above,
# but phrase without tag not work for it. Since gmake 3.79 
# tag with assignment fail, but work assignment for all tags
# (really that more correct).

!ifndef LDLIBS
LDLIBS =
!endif

LDSEARCH = $(LDSEARCH) /LIBPATH:"$(MSVC_LIB_DIR)"

OPT_DBG = $(OPT_DBG) /MDd
OPT_STLDBG = $(OPT_STLDBG) /MDd
OPT_REL = $(OPT_REL) /MD
OPT_STATIC_DBG = $(OPT_STATIC_DBG) /MTd
OPT_STATIC_STLDBG = $(OPT_STATIC_STLDBG) /MTd
OPT_STATIC_REL = $(OPT_STATIC_REL) /MT

LDFLAGS_REL = $(LDFLAGS_REL) /DLL $(LDSEARCH)
LDFLAGS_DBG = $(LDFLAGS_DBG) /DLL $(LDSEARCH)
LDFLAGS_STLDBG = $(LDFLAGS_STLDBG) /DLL $(LDSEARCH)
# LDFLAGS_STATIC = $(LDSEARCH)

LDFLAGS_REL = $(LDFLAGS_REL) /VERSION:$(MAJOR).$(MINOR)
LDFLAGS_DBG = $(LDFLAGS_DBG) /VERSION:$(MAJOR).$(MINOR)
LDFLAGS_STLDBG = $(LDFLAGS_STLDBG) /VERSION:$(MAJOR).$(MINOR)
