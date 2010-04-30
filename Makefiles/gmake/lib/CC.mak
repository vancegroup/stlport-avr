# -*- makefile -*- Time-stamp: <08/06/12 14:58:49 ptr>
#
# Copyright (c) 1997-1999, 2002, 2003, 2005-2008
# Petr Ovtchenkov
#
# Portion Copyright (c) 1999-2001
# Parallel Graphics Ltd.
#
# Licensed under the Academic Free License version 3.0
#

OPT += -xcode=pic32

dbg-shared:	LDFLAGS += -G -Qoption ld -z,initfirst -h$(SO_NAME_DBGxx) ${NOSTDLIB}
stldbg-shared:	LDFLAGS += -G -Qoption ld -z,initfirst -h$(SO_NAME_STLDBGxx) ${NOSTDLIB}
release-shared:	LDFLAGS += -G -Qoption ld -z,initfirst -h$(SO_NAMExx) ${NOSTDLIB}
