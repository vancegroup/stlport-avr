# Time-stamp: <03/10/27 18:42:41 ptr>
# $Id$

# shared library:
SO  := dll

ifeq ($(OSREALNAME), mingw)
LIB := lib
else
# the default import library extension under cygwin using gcc
LIB := dll.a
endif

EXP := exp
# executable:
EXE := .exe

# static library extention:
ifeq ($(OSREALNAME), mingw)
ARCH := lib
else
# the default library extension under cygwin using gcc
ARCH := a
endif

#ifeq ($(COMPILER_NAME), vc6)
#AR := lib.exe /nologo
#AR_INS_R := 
#AR_EXTR := 
#AR_OUT = /OUT:$(subst /,\,$@)
#else
AR := ar
AR_INS_R := -rs
AR_EXTR := -x
AR_OUT = $@
#endif

INSTALL := install

INSTALL_SO := ${INSTALL} -m 0755
INSTALL_A := ${INSTALL} -m 0644
INSTALL_EXE := ${INSTALL} -m 0755

