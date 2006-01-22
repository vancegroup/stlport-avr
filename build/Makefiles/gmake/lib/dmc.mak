# -*- makefile -*- Time-stamp: <03/11/30 11:41:22 ptr>
# $Id$


dbg-shared:	LDFLAGS += ${LDSEARCH}
stldbg-shared:	LDFLAGS += ${LDSEARCH}
release-shared:	LDFLAGS += ${LDSEARCH}
dbg-static:	LDFLAGS += ${LDSEARCH}
stldbg-static:	LDFLAGS += ${LDSEARCH}
release-static:	LDFLAGS += ${LDSEARCH}

