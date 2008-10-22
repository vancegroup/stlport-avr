# Time-stamp: <07/05/31 00:10:23 ptr>
#
# Copyright (c) 1997-1999, 2002, 2003, 2005-2007
# Petr Ovtchenkov
#
# Copyright (c) 2006, 2007
# Francois Dumont
#
# Portion Copyright (c) 1999-2001
# Parallel Graphics Ltd.
#
# Licensed under the Academic Free License version 3.0
#

RC := windres
INSTALL := install

INSTALL_SO := ${INSTALL} -m 0755
INSTALL_A := ${INSTALL} -m 0644
INSTALL_EXE := ${INSTALL} -m 0755

EXT_TEST := test
