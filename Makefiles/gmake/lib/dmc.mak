# -*- makefile -*- Time-stamp: <07/05/31 01:29:36 ptr>
#
# Copyright (c) 1997-1999, 2002, 2003, 2005-2007
# Petr Ovtchenkov
#
# Copyright (c) 2006, 2007
# Francois Dumont
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

release-shared: OPT += -WD
dbg-shared: OPT += -WD
stldbg-shared: OPT += -WD

release-shared: LDFLAGS += /DELEXECUTABLE/IMPLIB:$(subst /,\\,$(OUTPUT_DIR)/$(SO_NAME_BASE).lib)
dbg-shared: LDFLAGS += /CODEVIEW/DELEXECUTABLE/IMPLIB:$(subst /,\\,$(OUTPUT_DIR_DBG)/$(SO_NAME_DBG_BASE).lib)
stldbg-shared: LDFLAGS += /CODEVIEW/DELEXECUTABLE/IMPLIB:$(subst /,\\,$(OUTPUT_DIR_STLDBG)/$(SO_NAME_STLDBG_BASE).lib)

DEF_OPTION = $(OUTPUT_DIR)/$(SO_NAME_BASE).def
DEF_OPTION_DBG = $(OUTPUT_DIR_DBG)/$(SO_NAME_DBG_BASE).def
DEF_OPTION_STLDBG = $(OUTPUT_DIR_STLDBG)/$(SO_NAME_STLDBG_BASE).def
