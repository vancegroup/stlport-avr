# Time-stamp: <10/02/16 10:45:45 ptr>
#
# Copyright (c) 1997-1999, 2002, 2003, 2005-2010
# Petr Ovtchenkov
#
# Portion Copyright (c) 1999-2001
# Parallel Graphics Ltd.
#
# Licensed under the Academic Free License version 3.0
#

SO := so

ARCH := a
ifdef TARGET_OS
AR := ${TARGET_OS}-ar
STRIP := $(TARGET_OS)-strip
else
AR := ar
STRIP := strip
endif
AR_INS_R := -rs
AR_EXTR := -x
AR_OUT = $@

install-strip:	_INSTALL_STRIP_OPTION = -s

install-strip:	_SO_STRIP_OPTION = -S

install-strip-shared:	_INSTALL_STRIP_OPTION = -s

install-strip-shared:	_SO_STRIP_OPTION = -S

