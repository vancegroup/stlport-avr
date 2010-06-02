# -*- makefile -*- Time-stamp: <07/06/08 23:34:51 ptr>
#
# Copyright (c) 1997-1999, 2002, 2003, 2005-2007
# Petr Ovtchenkov
#
# This material is provided "as is", with absolutely no warranty expressed
# or implied. Any use is at your own risk.
#
# Permission to use or copy this software for any purpose is hereby granted
# without fee, provided the above notices are retained on all copies.
# Permission to modify the code and to distribute modified code is granted,
# provided the above notices are retained, and a notice that the code was
# modified is included with the above copyright notice.
#

LDFLAGS ?= 

ifneq ("$(findstring $(OSNAME),darwin windows)","")
include ${RULESBASE}/gmake/${OSNAME}/lib.mak
else
include ${RULESBASE}/gmake/unix/lib.mak
endif

include ${RULESBASE}/gmake/lib/${COMPILER_NAME}.mak

ifneq ("$(findstring $(OSNAME),windows)","")
include ${RULESBASE}/gmake/${OSNAME}/rules-so.mak
else
include ${RULESBASE}/gmake/unix/rules-so.mak
endif

include ${RULESBASE}/gmake/lib/rules-a.mak

ifneq ("$(findstring $(OSNAME),windows)","")
include ${RULESBASE}/gmake/${OSNAME}/rules-install-so.mak
else
include ${RULESBASE}/gmake/unix/rules-install-so.mak
endif

include ${RULESBASE}/gmake/lib/rules-install-a.mak
include ${RULESBASE}/gmake/lib/clean.mak
