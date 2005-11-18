# -*- makefile -*- Time-stamp: <04/08/23 23:07:35 ptr>
# $Id$

OPT += -xcode=pic32

dbg-shared:	LDFLAGS += -G -Qoption ld -z,initfirst -h$(SO_NAME_DBGxx) ${LDSEARCH} ${NOSTDLIB}
stldbg-shared:	LDFLAGS += -G -Qoption ld -z,initfirst -h$(SO_NAME_STLDBGxx) ${LDSEARCH} ${NOSTDLIB}
release-shared:	LDFLAGS += -G -Qoption ld -z,initfirst -h$(SO_NAMExx) ${LDSEARCH} ${NOSTDLIB}
dbg-static:	LDFLAGS += ${LDSEARCH}
stldbg-static:	LDFLAGS += ${LDSEARCH}
release-static:	LDFLAGS += ${LDSEARCH}
