# -*- makefile -*- Time-stamp: <03/10/27 18:30:31 ptr>
# $Id$


# Oh, the commented below work for gmake 3.78.1 and above,
# but phrase without tag not work for it. Since gmake 3.79 
# tag with assignment fail, but work assignment for all tags
# (really that more correct).

LDLIBS ?=
LDSEARCH += /LIBPATH:"$(MSVC_LIB_DIR)"

dbg-shared:	OPT += /MDd
stldbg-shared:	OPT += /MDd
release-shared:	OPT += /MD
release-shared-dep:	OPT += /MD
dbg-static:	OPT += /MTd
stldbg-static:	OPT += /MTd
release-static:	OPT += /MT

release-static:	DEFS += /D_LIB
dbg-static:	DEFS += /D_LIB
stldbg-static:	DEFS += /D_LIB


dbg-shared:	LDFLAGS += /DLL ${LDSEARCH}
stldbg-shared:	LDFLAGS += /DLL ${LDSEARCH}
release-shared:	LDFLAGS += /DLL ${LDSEARCH}
dbg-static:	LDFLAGS += ${LDSEARCH}
stldbg-static:	LDFLAGS += ${LDSEARCH}
release-static:	LDFLAGS += ${LDSEARCH}

LDFLAGS += /VERSION:$(MAJOR).$(MINOR)
