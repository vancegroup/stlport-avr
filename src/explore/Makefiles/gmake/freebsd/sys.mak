# Time-stamp: <03/10/27 18:47:47 ptr>
# $Id$

SO := so

ARCH := a
AR := ar
AR_INS_R := -r
AR_EXTR := -x
AR_OUT = $@

INSTALL := /usr/bin/install

INSTALL_SO := ${INSTALL} -c -m 0755
INSTALL_A := ${INSTALL} -c -m 0644
INSTALL_EXE := ${INSTALL} -c -m 0755

