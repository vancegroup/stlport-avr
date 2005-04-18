# -*- makefile -*- Time-stamp: <04/08/23 23:07:35 ptr>
# $Id$


# Oh, the commented below work for gmake 3.78.1 and above,
# but phrase without tag not work for it. Since gmake 3.79 
# tag with assignment fail, but work assignment for all tags
# (really that more correct).

OPT += -KPIC

#_USE_NOSTDLIB := 1

ifdef _USE_NOSTDLIB
NOSTDLIB :=

ifeq ($(CXX_VERSION_MAJOR),3)

# gcc before 3.3 (i.e. 3.0.x, 3.1.x, 3.2.x) has buggy libsupc++, so we should link with libstdc++ to avoid one

ifneq ($(CXX_VERSION_MINOR),0)
ifneq ($(CXX_VERSION_MINOR),1)
ifneq ($(CXX_VERSION_MINOR),2)
ifeq ($(OSNAME),linux)
START_OBJ := $(shell for o in crt{i,beginS}.o; do ${CXX} -print-file-name=$$o; done)
#START_A_OBJ := $(shell for o in crt{i,beginT}.o; do ${CXX} -print-file-name=$$o; done)
END_OBJ := $(shell for o in crt{endS,n}.o; do ${CXX} -print-file-name=$$o; done)
endif
ifeq ($(OSNAME),sunos)
#START_OBJ := $(shell for o in crti.o crtbegin.o; do ${CXX} -print-file-name=$$o; done)
#END_OBJ := $(shell for o in crtend.o crtn.o; do ${CXX} -print-file-name=$$o; done)
endif
#END_A_OBJ := $(shell for o in crtn.o; do ${CXX} -print-file-name=$$o; done)
STDLIBS := -lsupc++ -lgcc_s -lpthread -lc -lm
NOSTDLIB := -nostdlib
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

dbg-shared:	LDFLAGS += -shared -Wl,-h$(SO_NAME_DBGxx) ${LDSEARCH} ${NOSTDLIB}
stldbg-shared:	LDFLAGS += -shared -Wl,-h$(SO_NAME_STLDBGxx) ${LDSEARCH} ${NOSTDLIB}
release-shared:	LDFLAGS += -shared -Wl,-h$(SO_NAMExx) ${LDSEARCH} ${NOSTDLIB}
dbg-static:	LDFLAGS += ${LDSEARCH}
stldbg-static:	LDFLAGS += ${LDSEARCH}
release-static:	LDFLAGS += ${LDSEARCH}

