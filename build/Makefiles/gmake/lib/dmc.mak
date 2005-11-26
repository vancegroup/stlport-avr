# -*- makefile -*- Time-stamp: <03/11/30 11:41:22 ptr>
# $Id$


# Oh, the commented below work for gmake 3.78.1 and above,
# but phrase without tag not work for it. Since gmake 3.79 
# tag with assignment fail, but work assignment for all tags
# (really that more correct).

#OPT += -KPIC

dbg-shared:	LDFLAGS += -L/DE -L/DEBUG ${LDSEARCH} kernel32.lib user32.lib
stldbg-shared:	LDFLAGS += ${LDSEARCH}
release-shared:	LDFLAGS += ${LDSEARCH}
dbg-static:	LDFLAGS += ${LDSEARCH}
stldbg-static:	LDFLAGS += ${LDSEARCH}
release-static:	LDFLAGS += ${LDSEARCH}

