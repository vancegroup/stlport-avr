# Time-stamp: <04/04/30 23:41:02 ptr>
# $Id$

!ifdef TARGET_PROC
TARGET_NAME=$(TARGET_PROC)-
!else
TARGET_NAME=
!endif

OUTPUT_DIR             = obj\$(TARGET_NAME)$(COMPILER_NAME)\shared$(EXTRA_DIRS)
OUTPUT_DIR_DBG         = obj\$(TARGET_NAME)$(COMPILER_NAME)\shared-g$(EXTRA_DIRS)
OUTPUT_DIR_STLDBG      = obj\$(TARGET_NAME)$(COMPILER_NAME)\shared-stlg$(EXTRA_DIRS)

# file to store generated dependencies for make:
DEPENDS_COLLECTION     = obj/$(TARGET_NAME)$(COMPILER_NAME)/.make.depend

# I use the same catalog, as for shared:
OUTPUT_DIR_A           = obj\$(TARGET_NAME)$(COMPILER_NAME)\static$(EXTRA_DIRS)
OUTPUT_DIR_A_DBG       = obj\$(TARGET_NAME)$(COMPILER_NAME)\static-g$(EXTRA_DIRS)
OUTPUT_DIR_A_STLDBG    = obj\$(TARGET_NAME)$(COMPILER_NAME)\static-stlg$(EXTRA_DIRS)

INSTALL_LIB_DIR        = $(SRCROOT)\..\..\$(TARGET_NAME)lib
INSTALL_LIB_DIR_DBG    = $(SRCROOT)\..\..\$(TARGET_NAME)lib
INSTALL_LIB_DIR_STLDBG = $(SRCROOT)\..\..\$(TARGET_NAME)lib
INSTALL_STATIC_LIB_DIR = $(SRCROOT)\..\..\$(TARGET_NAME)lib
INSTALL_STATIC_LIB_DIR_DBG    = $(SRCROOT)\..\..\$(TARGET_NAME)lib
INSTALL_STATIC_LIB_DIR_STLDBG = $(SRCROOT)\..\..\$(TARGET_NAME)lib
INSTALL_BIN_DIR        = $(SRCROOT)\build\$(TARGET_NAME)bin
INSTALL_BIN_DIR_DBG    = $(SRCROOT)\build\$(TARGET_NAME)bin-g
INSTALL_BIN_DIR_STLDBG = $(SRCROOT)\build\$(TARGET_NAME)bin_stl-g

OUTPUT_DIRS = $(OUTPUT_DIR) $(OUTPUT_DIR_DBG) $(OUTPUT_DIR_STLDBG)
!if "$(OUTPUT_DIR_A)" != "$(OUTPUT_DIR)"
OUTPUT_DIRS = $(OUTPUT_DIRS) $(OUTPUT_DIR_A)
!endif
!if "$(OUTPUT_DIR_A_DBG)" != "$(OUTPUT_DIR_DBG)"
OUTPUT_DIRS = $(OUTPUT_DIRS) $(OUTPUT_DIR_A_DBG)
!endif
!if "$(OUTPUT_DIR_A_STLDBG)" != "$(OUTPUT_DIR_STLDBG)"
OUTPUT_DIRS = $(OUTPUT_DIRS) $(OUTPUT_DIR_A_STLDBG)
!endif

# sort will remove duplicates:
#OUTPUT_DIRS := $(sort $(OUTPUT_DIRS))

dirs:	$(OUTPUT_DIRS)

$(OUTPUT_DIRS):
	@if not exist $@ mkdir $@

