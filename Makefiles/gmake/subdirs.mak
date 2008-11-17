# Time-stamp: <08/11/17 21:12:11 ptr>
#
# Copyright (c) 2006-2008
# Petr Ovtchenkov
#
# Licensed under the Academic Free License version 3.0
#

# Do the same target in all catalogs specified in arg
define doinsubdirs
$(foreach d,$(1),${MAKE} -C ${d} $(2) $@;)
endef

# Do specified target (first arg) in all catalogs specified by second arg
define dotaginsubdirs
$(foreach d,$(2),${MAKE} -C ${d} $(2) $(1);)
endef
