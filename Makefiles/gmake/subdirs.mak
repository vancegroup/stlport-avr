# Time-stamp: <10/06/02 15:17:35 ptr>
#
# Copyright (c) 2006-2008
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

# Do the same target in all catalogs specified in arg
define doinsubdirs
$(foreach d,$(1),${MAKE} -C ${d} $(2) $@;)
endef

# Do specified target (first arg) in all catalogs specified by second arg
define dotaginsubdirs
$(foreach d,$(2),${MAKE} -C ${d} $(3) $(1);)
endef
