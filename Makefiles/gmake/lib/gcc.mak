# -*- makefile -*- Time-stamp: <10/03/05 23:16:47 ptr>
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

# Oh, the commented below work for gmake 3.78.1 and above,
# but phrase without tag not work for it. Since gmake 3.79 
# tag with assignment fail, but work assignment for all tags
# (really that more correct).

ifneq ($(OSNAME), windows)
OPT += -fPIC
endif

ifndef NOT_USE_NOSTDLIB

ifeq ($(CXX_VERSION_MAJOR),2)
# i.e. gcc before 3.x.x: 2.95, etc.
# gcc before 3.x don't had libsupc++.a and libgcc_s.so
# exceptions and operators new are in libgcc.a
#  Unfortunatly gcc before 3.x has a buggy C++ language support outside stdc++, so definition of STDLIBS below is commented
NOT_USE_NOSTDLIB := 1
#STDLIBS := $(shell ${CXX} -print-file-name=libgcc.a) -lpthread -lc -lm
endif

ifeq ($(CXX_VERSION_MAJOR),3)
# gcc before 3.3 (i.e. 3.0.x, 3.1.x, 3.2.x) has buggy libsupc++, so we should link with libstdc++ to avoid one
ifeq ($(CXX_VERSION_MINOR),0)
NOT_USE_NOSTDLIB := 1
endif
ifeq ($(CXX_VERSION_MINOR),1)
NOT_USE_NOSTDLIB := 1
endif
ifeq ($(CXX_VERSION_MINOR),2)
NOT_USE_NOSTDLIB := 1
endif
endif

# Android NDK 1.5 r1, in pre-build gcc 4.2.1 no libsupc++, is we should link with libstdc++?
#ifeq ($(OSNAME),android)
#NOT_USE_NOSTDLIB := 1
#endif

endif

ifndef NOT_USE_NOSTDLIB
ifeq ($(OSNAME),linux)
_USE_NOSTDLIB := 1
endif

ifeq ($(OSNAME),android)
_USE_NOSTDLIB := 1
endif

ifeq ($(OSNAME),openbsd)
_USE_NOSTDLIB := 1
endif

ifeq ($(OSNAME),freebsd)
_USE_NOSTDLIB := 1
endif

ifeq ($(OSNAME),netbsd)
_USE_NOSTDLIB := 1
endif

ifeq ($(OSNAME),sunos)
_USE_NOSTDLIB := 1
endif

ifeq ($(OSNAME),darwin)
_USE_NOSTDLIB := 1
endif

ifeq ($(OSNAME),windows)
_USE_NOSTDLIB := 1
endif
endif

ifndef WITHOUT_STLPORT

ifeq (${STLPORT_LIB_DIR},)
ifneq ($(OSNAME),windows)
release-shared:	STLPORT_LIB = -lstlport
dbg-shared:	STLPORT_LIB = -lstlportg
stldbg-shared:	STLPORT_LIB = -lstlportstlg
else
LIB_VERSION = ${LIBMAJOR}.${LIBMINOR}
release-shared:	STLPORT_LIB = -lstlport.${LIB_VERSION}
dbg-shared:	STLPORT_LIB = -lstlportg.${LIB_VERSION}
stldbg-shared:	STLPORT_LIB = -lstlportstlg.${LIB_VERSION}
endif
else
# STLPORT_LIB_DIR not empty
ifneq ($(OSNAME),windows)
release-shared:	STLPORT_LIB = -L${STLPORT_LIB_DIR} -lstlport
dbg-shared:	STLPORT_LIB = -L${STLPORT_LIB_DIR} -lstlportg
stldbg-shared:	STLPORT_LIB = -L${STLPORT_LIB_DIR} -lstlportstlg
else
LIB_VERSION = ${LIBMAJOR}.${LIBMINOR}
release-shared:	STLPORT_LIB = -L${STLPORT_LIB_DIR} -lstlport.${LIB_VERSION}
dbg-shared:	STLPORT_LIB = -L${STLPORT_LIB_DIR} -lstlportg.${LIB_VERSION}
stldbg-shared:	STLPORT_LIB = -L${STLPORT_LIB_DIR} -lstlportstlg.${LIB_VERSION}
endif
endif

endif

ifdef _USE_NOSTDLIB
NOSTDLIB :=

# Check whether gcc builded with --disable-shared
ifeq ($(shell ${CXX} ${CXXFLAGS} -print-file-name=libgcc_eh.a),libgcc_eh.a)
# gcc builded with --disable-shared, (no library libgcc_eh.a); all exception support in libgcc.a
_LGCC_EH :=
_LGCC_S := -lgcc
else
# gcc builded with --enable-shared (default)
ifdef USE_STATIC_LIBGCC
# if force usage of static libgcc, then exceptions support should be taken from libgcc_eh
_LGCC_EH := -lgcc_eh
_LGCC_S := -lgcc
else
# otherwise, exceptions support is in libgcc_s.so
_LGCC_EH :=
ifneq ($(OSNAME),darwin)
_LGCC_S := -lgcc_s
else
ifeq ($(MACOSX_TEN_FIVE),true)
_LGCC_S := -lgcc_s.10.5
else
_LGCC_S := -lgcc_s.10.4
endif
# end of Darwin
endif
# end of !USE_STATIC_LIBGCC
endif
# end of present libgcc_eh.a
endif

_LSUPCPP := $(shell ${CXX} ${CXXFLAGS} -print-file-name=libsupc++.a)
ifeq (${OSNAME},darwin)
ifdef GCC_APPLE_CC
_LSUPCPP := $(shell mkdir -p $(PRE_OUTPUT_DIR) && lipo ${_LSUPCPP} -thin ${M_ARCH} -output $(PRE_OUTPUT_DIR)/libsupc++.a && echo $(PRE_OUTPUT_DIR)/libsupc++.a)
endif
endif

ifneq (${_LSUPCPP},libsupc++.a)
_LSUPCPP_OBJ     := $(shell $(AR) t ${_LSUPCPP})
_LSUPCPP_AUX_OBJ := $(addprefix $(AUX_DIR)/,${_LSUPCPP_OBJ})
_LSUPCPP_TSMP    := .supc++
_LSUPCPP_AUX_TSMP:= $(AUX_DIR)/$(_LSUPCPP_TSMP)
endif

# ifeq ($(CXX_VERSION_MAJOR),3)
# Include whole language support archive (libsupc++.a) into libstlport:
# all C++ issues are in libstlport now.
ifeq ($(OSNAME),linux)
#START_OBJ := $(shell for o in crti.o crtbeginS.o; do ${CXX} ${CXXFLAGS} -print-file-name=$$o; done)
#START_A_OBJ := $(shell for o in crti.o crtbeginT.o; do ${CXX} -print-file-name=$$o; done)
#END_OBJ := $(shell for o in crtendS.o crtn.o; do ${CXX} ${CXXFLAGS} -print-file-name=$$o; done)
STDLIBS = ${STLPORT_LIB} ${_LGCC_S} -lpthread -lc -lm
endif

ifeq ($(OSNAME),android)
#START_OBJ := $(shell for o in crti.o crtbegin.o; do ${CXX} ${CXXFLAGS} -print-file-name=$$o; done)
#START_A_OBJ := $(shell for o in crti.o crtbeginT.o; do ${CXX} -print-file-name=$$o; done)
#END_OBJ := $(shell for o in crtend.o crtn.o; do ${CXX} ${CXXFLAGS} -print-file-name=$$o; done)
# Android's libthread_db has undefined symbol:
#   libthread_db.so: undefined reference to `ps_pglobal_lookup'
#  U ps_pglobal_lookup
# that never defined in shipout runtime (*.o, *.a, *.so).
# Checked for Android NDK 1.5 r1 and 1.6 r1.
STDLIBS = ${_LGCC_S} -Wl,-Bstatic -lthread_db -Wl,-Bdynamic -lc -lm
# STDLIBS = ${_LGCC_S} -Wl,--whole-archive -lthread_db -Wl,--no-whole-archive -lc -lm
endif

ifeq ($(OSNAME),openbsd)
#START_OBJ := $(shell for o in crtbeginS.o; do ${CXX} ${CXXFLAGS} -print-file-name=$$o; done)
#END_OBJ := $(shell for o in crtendS.o; do ${CXX} ${CXXFLAGS} -print-file-name=$$o; done)
STDLIBS = ${STLPORT_LIB} ${_LGCC_S} -lpthread -lc -lm
endif

ifeq ($(OSNAME),freebsd)
# FreeBSD < 5.3 should use -lc_r, while FreeBSD >= 5.3 use -lpthread
PTHR := $(shell if [ ${OSREL_MAJOR} -gt 5 ] ; then echo "pthread" ; else if [ ${OSREL_MAJOR} -lt 5 ] ; then echo "c_r" ; else if [ ${OSREL_MINOR} -lt 3 ] ; then echo "c_r" ; else echo "pthread"; fi ; fi ; fi)
#START_OBJ := $(shell for o in crti.o crtbeginS.o; do ${CXX} ${CXXFLAGS} -print-file-name=$$o; done)
#END_OBJ := $(shell for o in crtendS.o crtn.o; do ${CXX} ${CXXFLAGS} -print-file-name=$$o; done)
STDLIBS = ${STLPORT_LIB} ${_LGCC_S} -l${PTHR} -lc -lm
endif

ifeq ($(OSNAME),netbsd)
#START_OBJ := $(shell for o in crti.o crtbeginS.o; do ${CXX} ${CXXFLAGS} -print-file-name=$$o; done)
#END_OBJ := $(shell for o in crtendS.o crtn.o; do ${CXX} ${CXXFLAGS} -print-file-name=$$o; done)
STDLIBS = ${STLPORT_LIB} ${_LGCC_S} -lpthread -lc -lm
endif

ifeq ($(OSNAME),sunos)
#START_OBJ := $(shell for o in crti.o crtbegin.o; do ${CXX} ${CXXFLAGS} -print-file-name=$$o; done)
#END_OBJ := $(shell for o in crtend.o crtn.o; do ${CXX} ${CXXFLAGS} -print-file-name=$$o; done)
STDLIBS = ${STLPORT_LIB} ${_LGCC_S} -lpthread -lc -lm -lrt
endif

ifeq ($(OSNAME),darwin)
ifndef USE_STATIC_LIBGCC
# MacOS X, shared-libgcc
ifeq ($(MACOSX_TEN_FIVE),true)
# MacOS X >= 10.5
#START_OBJ :=
else
# MacOS X < 10.5
#START_OBJ :=
endif
else
# MacOS X, not shared-libgcc
#START_OBJ :=
endif
#END_OBJ :=
ifdef GCC_APPLE_CC
STDLIBS = ${STLPORT_LIB} ${_LGCC_S} -lc -lm
else
LDFLAGS += -single_module
STDLIBS = ${STLPORT_LIB} ${_LGCC_S} -lc -lm
endif
endif
#END_A_OBJ := $(shell for o in crtn.o; do ${CXX} -print-file-name=$$o; done)
NOSTDLIB := -nodefaultlibs
ifeq ($(OSNAME),windows)

ifndef USE_STATIC_LIBGCC
ifeq ($(shell ${CXX} ${CXXFLAGS} -print-file-name=libgcc_s.a),libgcc_s.a)
_LGCC_S := -lgcc
else
_LGCC_S := -lgcc_s
endif
else
_LGCC_S := -lgcc
endif

endif
# endif
else
ifndef WITHOUT_STLPORT
STDLIBS = ${STLPORT_LIB}
else
STDLIBS = 
endif
endif

ifeq ($(OSNAME),hp-ux)
dbg-shared:	LDFLAGS += -shared -Wl,-dynamic -Wl,+h$(SO_NAME_DBGxx)
stldbg-shared:	LDFLAGS += -shared -Wl,-dynamic -Wl,+h$(SO_NAME_STLDBGxx)
release-shared:	LDFLAGS += -shared -Wl,-dynamic -Wl,+h$(SO_NAMExx)
endif

ifeq ($(OSNAME),sunos)
dbg-shared:	LDFLAGS += -shared -Wl,-h$(SO_NAME_DBGxx) ${NOSTDLIB}
stldbg-shared:	LDFLAGS += -shared -Wl,-h$(SO_NAME_STLDBGxx) ${NOSTDLIB}
release-shared:	LDFLAGS += -shared -Wl,-h$(SO_NAMExx) ${NOSTDLIB}
endif

ifeq ($(OSNAME),linux)
dbg-shared:	LDFLAGS += -shared -Wl,-h$(SO_NAME_DBGxx) ${NOSTDLIB}
stldbg-shared:	LDFLAGS += -shared -Wl,-h$(SO_NAME_STLDBGxx) ${NOSTDLIB}
release-shared:	LDFLAGS += -shared -Wl,-h$(SO_NAMExx) ${NOSTDLIB}
endif

ifeq ($(OSNAME),android)
dbg-shared:	LDFLAGS += -shared -Wl,-h$(SO_NAME_DBGxx) ${NOSTDLIB}
stldbg-shared:	LDFLAGS += -shared -Wl,-h$(SO_NAME_STLDBGxx) ${NOSTDLIB}
release-shared:	LDFLAGS += -shared -Wl,-h$(SO_NAMExx) ${NOSTDLIB}
endif

ifeq ($(OSNAME),windows)
ifndef USE_STATIC_LIBGCC
dbg-shared:	LDFLAGS += -shared-libgcc
stldbg-shared:	LDFLAGS += -shared-libgcc
release-shared:	LDFLAGS += -shared-libgcc
endif
dbg-shared:	LDFLAGS += -Wl,--out-implib=${LIB_NAME_OUT_DBG},--enable-auto-image-base
stldbg-shared:	LDFLAGS += -Wl,--out-implib=${LIB_NAME_OUT_STLDBG},--enable-auto-image-base
release-shared:	LDFLAGS += -Wl,--out-implib=${LIB_NAME_OUT},--enable-auto-image-base
dbg-static:	LDFLAGS += -static
stldbg-static:	LDFLAGS += -static
release-static:	LDFLAGS += -static
endif

ifeq ($(OSNAME),freebsd)
dbg-shared:	LDFLAGS += -shared -Wl,-h$(SO_NAME_DBGxx) ${NOSTDLIB}
stldbg-shared:	LDFLAGS += -shared -Wl,-h$(SO_NAME_STLDBGxx) ${NOSTDLIB}
release-shared:	LDFLAGS += -shared -Wl,-h$(SO_NAMExx) ${NOSTDLIB}
endif

ifeq ($(OSNAME),darwin)
CURRENT_VERSION := ${MAJOR}.${MINOR}.${PATCH}
COMPATIBILITY_VERSION := $(CURRENT_VERSION)

dbg-shared:	LDFLAGS += -dynamic -dynamiclib -compatibility_version $(COMPATIBILITY_VERSION) -current_version $(CURRENT_VERSION) -install_name $(SO_NAME_DBGxx) ${NOSTDLIB}
stldbg-shared:	LDFLAGS += -dynamic -dynamiclib -compatibility_version $(COMPATIBILITY_VERSION) -current_version $(CURRENT_VERSION) -install_name $(SO_NAME_STLDBGxx) ${NOSTDLIB}
release-shared:	LDFLAGS += -dynamic -dynamiclib -compatibility_version $(COMPATIBILITY_VERSION) -current_version $(CURRENT_VERSION) -install_name $(SO_NAMExx) ${NOSTDLIB}
dbg-static:	LDFLAGS += -staticlib
stldbg-static:	LDFLAGS += -staticlib
release-static:	LDFLAGS += -staticlib
endif

ifeq ($(OSNAME),openbsd)
dbg-shared:	LDFLAGS += -shared -Wl,-soname -Wl,$(SO_NAME_DBGxx) ${NOSTDLIB}
stldbg-shared:	LDFLAGS += -shared -Wl,-soname -Wl,$(SO_NAME_STLDBGxx) ${NOSTDLIB}
release-shared:	LDFLAGS += -shared -Wl,-soname -Wl,$(SO_NAMExx) ${NOSTDLIB}
endif
