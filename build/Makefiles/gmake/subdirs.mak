# Time-stamp: <10/06/02 14:09:24 ptr>
#
# Copyright (c) 2006, 2007
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

# Do the same target in all catalogs as arg
define doinsubdirs
$(foreach d,$(1),${MAKE} -C ${d} $@;)
endef
