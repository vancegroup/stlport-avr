# -*- Makefile -*- Time-stamp: <2011-05-02 11:32:37 ptr>

SRCROOT := ..
COMPILER_NAME := gcc
STLP_BUILD := 1

STLPORT_INCLUDE_DIR = ../stlport
HEADERS_BASE = ${STLPORT_INCLUDE_DIR}

ALL_TAGS := release-shared dbg-shared stldbg-shared

include Makefile.inc
include ${SRCROOT}/Makefiles/gmake/top.mak
include ${SRCROOT}/Makefiles/gmake/subdirs.mak

ifeq ($(OSNAME),linux)
DEFS += -D_GNU_SOURCE
STDLIBS = -Wl,--whole-archive -lsupc++ ${_LGCC_EH} -Wl,--no-whole-archive ${_LGCC_S} -lpthread -lc -lm -lrt
endif

ifeq ($(OSNAME),android)
DEFS += -D_GNU_SOURCE
STDLIBS = -Wl,--whole-archive ${_LGCC_EH} -Wl,--no-whole-archive ${_LGCC_S} -Wl,-Bstatic -lthread_db -Wl,-Bdynamic -lc -lm
endif

ifeq ($(OSNAME),openbsd)
STDLIBS = -Wl,--whole-archive -lsupc++ ${_LGCC_EH} -Wl,--no-whole-archive ${_LGCC_S} -lpthread -lc -lm
endif

ifeq ($(OSNAME),freebsd)
STDLIBS = -Wl,--whole-archive -lsupc++ ${_LGCC_EH} -Wl,--no-whole-archive ${_LGCC_S} -l${PTHR} -lc -lm
endif

ifeq ($(OSNAME),netbsd)
STDLIBS = -Wl,--whole-archive -lsupc++ ${_LGCC_EH} -Wl,--no-whole-archive ${_LGCC_S} -lpthread -lc -lm
endif

ifeq ($(OSNAME),sunos)
STDLIBS = -Wl,-zallextract -lsupc++ ${_LGCC_EH} -Wl,-zdefaultextract ${_LGCC_S} -lpthread -lc -lm -lrt
endif

ifeq ($(OSNAME),darwin)
# -all_load don't demonstrate any visible effect, looks like
# this is dummy option; but nevertheless, with _LSUPCPP_AUX_OBJ
# trick (as in static library) we can resolve problem, in potential
ifdef GCC_APPLE_CC
STDLIBS = ${_LGCC_S} -lc -lm -all_load ${_LSUPCPP} ${_LGCC_EH}
else
LDFLAGS += -single_module
STDLIBS = ${_LGCC_S} -lc -lm -all_load -lsupc++ ${_LGCC_EH}
endif
endif

ifneq ($(OSNAME),windows)
ifneq ($(CXX_VERSION_MAJOR),2)
ifneq ($(CXX_VERSION_MAJOR),3)
# Appears to be broken on SunOS through GCC 4.3
ifneq ($(OSNAME),sunos)
CXXFLAGS += -fvisibility=hidden
CFLAGS += -fvisibility=hidden
endif
endif
endif
else
# windows
ifeq ($(OSREALNAME),mingw)
STDLIBS = -lsupc++ ${_LGCC_S} -lm -lmoldname -lmingw32 -lmingwex -lmsvcrt -lkernel32
else
LIBSUPC++ := $(shell ${CXX} ${CXXFLAGS} -print-file-name=libsupc++.a)
LSUPC++DEF := $(PRE_OUTPUT_DIR)/libsupc++.def
$(LSUPC++DEF) : $(LIBSUPC++)
	dlltool --export-all-symbols --output-def=$(LSUPC++DEF) $(LIBSUPC++)
ifneq (,$(findstring no-cygwin,$(EXTRA_CXXFLAGS)))
STDLIBS = -Wl,-whole-archive -lsupc++ -Wl,-no-whole-archive ${_LGCC_S} -lm -lmoldname -lmingw32 -lmingwex -lmsvcrt -lkernel32
else
STDLIBS = -Wl,-whole-archive -lsupc++ -Wl,--no-whole-archive ${_LGCC_S} -lpthread -lm -lc -lkernel32
endif
endif
# eindows
endif

# options for build with boost support
ifdef STLP_BUILD_BOOST_PATH
INCLUDES += -I$(STLP_BUILD_BOOST_PATH)
endif

SUBDIRS := ${SRCROOT}/test/unit

check:	all
	+$(call doinsubdirs,${SUBDIRS})

clean::
	@rm -f $(_LSUPCPP_AUX_OBJ) $(_LSUPCPP_AUX_TSMP)
ifneq ($(OSREALNAME), mingw)
	@-rm -f ${LSUPC++DEF}
endif

ifneq ($(_LSUPCPP_OBJ),"")
$(_LSUPCPP_AUX_TSMP):	$(_LSUPCPP)
	if [ ! -d $(AUX_DIR) ]; then mkdir -p $(AUX_DIR); fi
	cd $(AUX_DIR); $(AR) xo $(_LSUPCPP) && touch -r $(_LSUPCPP) $(_LSUPCPP_TSMP)
endif

ifeq ($(TARGET_OS),avr)

SKETCHBOOK ?= $(HOME)/sketchbook

HEADER_DIR_PARENT := $(shell dirname $(HEADERS_BASE))
HEADER_DIR_NAME := $(shell basename $(HEADERS_BASE))
HEADER_RELDIRS := $(shell cd $(HEADER_DIR_PARENT) && find $(HEADER_DIR_NAME) -type d)
HEADER_FILES := $(shell cd $(HEADER_DIR_PARENT) && find $(HEADER_DIR_NAME) -type f)


LIBRARIES_INSTALL_DIR = $(SKETCHBOOK)/libraries

install-arduino:
	# Create directories
	$(INSTALL_D) $(patsubst %,$(LIBRARIES_INSTALL_DIR)/%,$(HEADER_RELDIRS))

	# Install headers
	for f in $(HEADER_FILES); do \
		$(INSTALL_F) -t $(LIBRARIES_INSTALL_DIR)/`dirname $$f` $(HEADER_DIR_PARENT)/$$f; done

	# Create dummy header for arduino
	touch $(LIBRARIES_INSTALL_DIR)/$(HEADER_DIR_NAME)/$(HEADER_DIR_NAME).h
endif

