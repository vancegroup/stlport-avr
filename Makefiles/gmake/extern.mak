# Time-stamp: <10/06/02 15:17:35 ptr>
#
# Copyright (c) 1997-1999, 2002, 2003, 2005, 2006
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

# boost (http://www.boost.org, http://boost.sourceforge.net)

# ifdef BOOST_DIR
# BOOST_INCLUDE_DIR ?= ${BOOST_DIR}
# endif

ifdef STLP_BUILD_BOOST_PATH
BOOST_INCLUDE_DIR ?= ${STLP_BUILD_BOOST_PATH}
endif

# STLport library

ifndef WITHOUT_STLPORT
STLPORT_DIR ?= ${SRCROOT}/..
endif

ifdef STLPORT_DIR
# STLPORT_LIB_DIR ?= $(STLPORT_DIR)/${TARGET_NAME}lib
STLPORT_INCLUDE_DIR ?= $(STLPORT_DIR)/stlport
endif
