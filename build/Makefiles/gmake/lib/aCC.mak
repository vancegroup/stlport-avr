# -*- makefile -*- Time-stamp: <05/03/24 11:33:35 ptr>
# $Id$

dbg-shared:	LDFLAGS += -b +nostl -Wl,+h$(SO_NAME_DBGxx) ${LDSEARCH}
stldbg-shared:	LDFLAGS += -b +nostl -Wl,+h$(SO_NAME_STLDBGxx) ${LDSEARCH}
release-shared:	LDFLAGS += -b +nostl -Wl,+h$(SO_NAMExx) ${LDSEARCH}
