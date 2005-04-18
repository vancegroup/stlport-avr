# -*- Makefile -*- Time-stamp: <04/08/23 23:07:09 ptr>
# $Id$

#_USE_NOSTDLIB := 1

ifdef _USE_NOSTDLIB

ifeq ($(CXX_VERSION_MAJOR),3)

# gcc before 3.3 (i.e. 3.0.x, 3.1.x, 3.2.x) has buggy libsupc++, so we should link with libstdc++ to avoid one

ifneq ($(CXX_VERSION_MINOR),0)
ifneq ($(CXX_VERSION_MINOR),1)
ifneq ($(CXX_VERSION_MINOR),2)
ifeq ($(OSNAME),linux)
START_OBJ := $(shell for o in crt{1,i,begin}.o; do ${CXX} -print-file-name=$$o; done)
END_OBJ := $(shell for o in crt{end,n}.o; do ${CXX} -print-file-name=$$o; done)
endif
ifeq ($(OSNAME),sunos)
START_OBJ := $(shell for o in crt1.o crti.o crtbegin.o; do ${CXX} -print-file-name=$$o; done)
END_OBJ := $(shell for o in crtend.o crtn.o; do ${CXX} -print-file-name=$$o; done)
endif
LDFLAGS += -nostdlib
STDLIBS := -lsupc++ -lgcc_s -lpthread -lc -lm
endif
endif
endif

else
# i.e. gcc before 3.x.x: 2.95, etc.
# gcc before 3.x don't had libsupc++.a and libgcc_s.so
# exceptions and operators new are in libgcc.a
#  Unfortunatly gcc before 3.x has a buggy C++ language support outside stdc++, so line below is commented
#STDLIBS := $(shell ${CXX} -print-file-name=libgcc.a) -lpthread -lc -lm
endif
endif

# workaround for gcc 2.95.x bug:
ifeq ($(CXX_VERSION_MAJOR),2)
OPT += -KPIC
endif
