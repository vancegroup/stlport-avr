# Time-stamp: <03/10/27 16:58:38 ptr>
# $Id$

OUTPUT_DIR             := obj/$(COMPILER_NAME)/shared$(EXTRA_DIRS)
OUTPUT_DIR_DBG         := obj/$(COMPILER_NAME)/shared-g$(EXTRA_DIRS)
OUTPUT_DIR_STLDBG      := obj/$(COMPILER_NAME)/shared-stlg$(EXTRA_DIRS)

# file to store generated dependencies for make:
DEPENDS_COLLECTION     := obj/$(COMPILER_NAME)/.make.depend

ifeq (cygwin,$(OSNAME))
OUTPUT_DIR_A           := obj/$(COMPILER_NAME)/static$(EXTRA_DIRS)
OUTPUT_DIR_A_DBG       := obj/$(COMPILER_NAME)/static-g$(EXTRA_DIRS)
OUTPUT_DIR_A_STLDBG    := obj/$(COMPILER_NAME)/static-stlg$(EXTRA_DIRS)
else
# I use the same catalog, as for shared:
OUTPUT_DIR_A           := $(OUTPUT_DIR)
OUTPUT_DIR_A_DBG       := $(OUTPUT_DIR_DBG)
OUTPUT_DIR_A_STLDBG    := $(OUTPUT_DIR_STLDBG)
endif

INSTALL_LIB_DIR        := ${SRCROOT}/../../lib
INSTALL_LIB_DIR_DBG    := ${SRCROOT}/../../lib
INSTALL_LIB_DIR_STLDBG := ${SRCROOT}/../../lib
INSTALL_BIN_DIR        := ${SRCROOT}/../../bin
INSTALL_BIN_DIR_DBG    := ${SRCROOT}/../../bin-g
INSTALL_BIN_DIR_STLDBG := ${SRCROOT}/../../bin_stl-g

OUTPUT_DIRS := $(OUTPUT_DIR) $(OUTPUT_DIR_DBG) $(OUTPUT_DIR_STLDBG) \
               $(OUTPUT_DIR_A) $(OUTPUT_DIR_A_DBG) $(OUTPUT_DIR_A_STLDBG)

# sort will remove duplicates:
OUTPUT_DIRS := $(sort $(OUTPUT_DIRS))

PHONY += dirs $(OUTPUT_DIRS)

dirs:	$(OUTPUT_DIRS)

$(OUTPUT_DIRS):
	@if [ ! -d $@ ] ; then \
	  mkdir -p $@ ; \
	fi

