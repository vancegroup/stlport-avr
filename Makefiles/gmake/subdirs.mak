# Time-stamp: <08/06/16 16:31:11 yeti>
#
# Copyright (c) 2006-2008
# Petr Ovtchenkov
#
# Licensed under the Academic Free License version 3.0
#

# Do the same target in all catalogs specified in arg
define doinsubdirs
$(foreach d,$(1),${MAKE} -C ${d} $@;)
endef

# Do specified target (first arg) in all catalogs specified by second arg
define dotaginsubdirs
$(foreach d,$(2),${MAKE} -C ${d} $(1);)
endef
