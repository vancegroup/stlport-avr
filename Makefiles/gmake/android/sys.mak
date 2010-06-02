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

INSTALL := /usr/bin/install

STRIP := /usr/bin/strip

INSTALL_SO := ${INSTALL} -c -m 0755 ${_INSTALL_STRIP_OPTION}
INSTALL_A := ${INSTALL} -c -m 0644
INSTALL_EXE := ${INSTALL} -c -m 0755
INSTALL_D := ${INSTALL} -d -m 0755
INSTALL_F := ${INSTALL} -c -p -m 0644

# bash's built-in test is like extern
# EXT_TEST := /usr/bin/test
EXT_TEST := test
