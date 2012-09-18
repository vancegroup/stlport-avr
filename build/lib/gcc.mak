# -*- Makefile -*- Time-stamp: <08/06/06 10:50:42 yeti>

SRCROOT := ..
COMPILER_NAME := gcc
STLP_BUILD := 1

STLPORT_INCLUDE_DIR = ../../stlport
HEADERS_BASE = ${STLPORT_INCLUDE_DIR}

include Makefile.inc
include ${SRCROOT}/Makefiles/gmake/top.mak
include ${SRCROOT}/Makefiles/gmake/subdirs.mak

ifeq ($(OSNAME),linux)
DEFS += -D_GNU_SOURCE
endif

# options for build with boost support
ifdef STLP_BUILD_BOOST_PATH
INCLUDES += -I$(STLP_BUILD_BOOST_PATH)
endif

SUBDIRS := ${SRCROOT}/test/unit

check:	all
	+$(call doinsubdirs,${SUBDIRS})

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
