# Time-stamp: <04/03/16 17:18:08 ptr>
# $Id$

ifdef TARGET_OS
TARGET_NAME := ${TARGET_OS}-
else
TARGET_NAME :=
endif

OUTPUT_DIR             := obj/$(TARGET_NAME)$(COMPILER_NAME)/shared$(EXTRA_DIRS)
OUTPUT_DIR_DBG         := obj/$(TARGET_NAME)$(COMPILER_NAME)/shared-g$(EXTRA_DIRS)
OUTPUT_DIR_STLDBG      := obj/$(TARGET_NAME)$(COMPILER_NAME)/shared-stlg$(EXTRA_DIRS)

# file to store generated dependencies for make:
DEPENDS_COLLECTION     := obj/$(TARGET_NAME)$(COMPILER_NAME)/.make.depend

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

INSTALL_LIB_DIR        := ${SRCROOT}/../../$(TARGET_NAME)lib
INSTALL_LIB_DIR_DBG    := ${SRCROOT}/../../$(TARGET_NAME)lib
INSTALL_LIB_DIR_STLDBG := ${SRCROOT}/../../$(TARGET_NAME)lib
INSTALL_BIN_DIR        := ${SRCROOT}/../../$(TARGET_NAME)bin
INSTALL_BIN_DIR_DBG    := ${SRCROOT}/../../$(TARGET_NAME)bin-g
INSTALL_BIN_DIR_STLDBG := ${SRCROOT}/../../$(TARGET_NAME)bin-stlg

OUTPUT_DIRS := $(OUTPUT_DIR) $(OUTPUT_DIR_DBG) $(OUTPUT_DIR_STLDBG) \
               $(OUTPUT_DIR_A) $(OUTPUT_DIR_A_DBG) $(OUTPUT_DIR_A_STLDBG)

INSTALL_LIB_DIRS := $(INSTALL_LIB_DIR) $(INSTALL_LIB_DIR_DBG) $(INSTALL_LIB_DIR_STLDBG)
INSTALL_BIN_DIRS := $(INSTALL_BIN_DIR) $(INSTALL_BIN_DIR_DBG) $(INSTALL_BIN_DIR_STLDBG)

# sort will remove duplicates:
OUTPUT_DIRS := $(sort $(OUTPUT_DIRS))
INSTALL_LIB_DIRS := $(sort $(INSTALL_LIB_DIRS))
INSTALL_BIN_DIRS := $(sort $(INSTALL_BIN_DIRS))

PHONY += dirs $(OUTPUT_DIRS) $(INSTALL_LIB_DIRS) $(INSTALL_BIN_DIRS)

dirs:	$(OUTPUT_DIRS)

install-lib-dirs:	$(INSTALL_LIB_DIRS)
install-bin-dirs:	$(INSTALL_BIN_DIRS)

$(OUTPUT_DIRS):
	@if [ ! -d $@ ] ; then \
	  mkdir -p $@ ; \
	fi

$(INSTALL_LIB_DIRS):
	@if [ ! -d $@ ] ; then \
	  mkdir -p $@ ; \
	fi

$(INSTALL_BIN_DIRS):
	@if [ ! -d $@ ] ; then \
	  mkdir -p $@ ; \
	fi
