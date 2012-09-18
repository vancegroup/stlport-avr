# Time-stamp: <10/06/02 15:17:35 ptr>
#
# Copyright (c) 1997-1999, 2002, 2003, 2005-2010
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

WITHOUT_RTTI := 1
WITHOUT_EXCEPTIONS := 1
WITHOUT_THREAD := 1
WITHOUT_CHRONO := 1
WITHOUT_LOCALES := 1
_NO_SHARED_BUILD := 1
_STATIC_BUILD := 1
_NO_STLDBG_BUILD := 1
_NO_DBG_BUILD := 1


install-strip:	_INSTALL_STRIP_OPTION = -s

install-strip:	_SO_STRIP_OPTION = -S

install-strip-shared:	_INSTALL_STRIP_OPTION = -s

install-strip-shared:	_SO_STRIP_OPTION = -S

