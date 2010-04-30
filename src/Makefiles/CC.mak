# -*- Makefile -*- Time-stamp: <03/10/12 20:35:49 ptr>

SRCROOT := ..
COMPILER_NAME := CC

# The Sun C++ compiler has a very special handling of standard C++ include
# files that don't have a ".h" extension.  It doesn't use the header name
# as a file name, but looks up the header name + ".SUNWCCh" in the file
# system.  The name + ".SUNWCCh" file is supposed to be a symlink to the
# real header file.
#
# The include path to the stlport header directory must be an absolute
# directory name.  Expansion of .SUNWCCh symbolic links seems to be broken
# if it's a relative name.
#
# The dependencies on create-sunwcch must come first to create the .SUNWCCh
# links before anything is compiled.  (The correct solution would be to make
# every compilation of a C++ source file depend on create-sunwcch.)

release-static:	create-sunwcch

dbg-static:	create-sunwcch

stldbg-static:	create-sunwcch

release-shared:	create-sunwcch

dbg-shared:	create-sunwcch

stldbg-shared:	create-sunwcch

STLPORT_ETC_DIR = ../etc
STLPORT_INCLUDE_DIR = ../stlport
STLPORT_ABS_INCLUDE_DIR := $(shell cd ../.. && pwd)/stlport

include Makefile.inc
include ${SRCROOT}/Makefiles/gmake/top.mak

INCLUDES += -I. -I$(STLPORT_ABS_INCLUDE_DIR)

# options for build with boost support
ifdef STLP_BUILD_BOOST_PATH
INCLUDES += -I$(STLP_BUILD_BOOST_PATH)
endif

STD_HEADER_LISTS = \
   $(STLPORT_ETC_DIR)/std_headers.txt \
   $(STLPORT_ETC_DIR)/std_headers_c.txt \
   $(STLPORT_ETC_DIR)/std_headers_cpp_runtime.txt

STD_HEADERS = $(shell cat $(STD_HEADER_LISTS))

SUNWCCH_HEADERS = $(patsubst %,$(STLPORT_INCLUDE_DIR)/%.SUNWCCh,$(STD_HEADERS))

create-sunwcch:	$(SUNWCCH_HEADERS)

%.SUNWCCh:
	ln -s $(basename $(notdir $@)) $@

PHONY += create-sunwcch
