# Time-stamp: <03/10/27 18:42:41 ptr>
# $Id$

# shared library:
SO  := dll
LIB := lib
EXP := exp
# executable:
EXE := .exe

# static library extention:
ARCH := lib
AR := lib.exe /nologo
AR_INS_R := 
AR_EXTR := 
AR_OUT = /OUT:$(subst /,\,$@)

INSTALL := /usr/bin/install

INSTALL_SO := ${INSTALL} -c -m 0755
INSTALL_A := ${INSTALL} -c -m 0644
INSTALL_EXE := ${INSTALL} -c -m 0755

