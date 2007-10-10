# -*- makefile -*- Time-stamp: <07/03/08 21:39:22 ptr>
#
# Copyright (c) 1997-1999, 2002, 2003, 2005-2007
# Petr Ovtchenkov
#
# Portion Copyright (c) 1999-2001
# Parallel Graphics Ltd.
#
# Licensed under the Academic Free License version 3.0
#

OPT += -xcode=pic32

dbg-shared:	LDFLAGS += -G -Qoption ld -z,initfirst -h$(SO_NAME_DBGxx) ${LDSEARCH} ${NOSTDLIB}
stldbg-shared:	LDFLAGS += -G -Qoption ld -z,initfirst -h$(SO_NAME_STLDBGxx) ${LDSEARCH} ${NOSTDLIB}
release-shared:	LDFLAGS += -G -Qoption ld -z,initfirst -h$(SO_NAMExx) ${LDSEARCH} ${NOSTDLIB}
dbg-static:	LDFLAGS += ${LDSEARCH}
stldbg-static:	LDFLAGS += ${LDSEARCH}
release-static:	LDFLAGS += ${LDSEARCH}

DEPENDS_COLLECTION_SUNPRO := $(DEPENDS_COLLECTION).sunpro

compiler-dep :: $(DEPENDS_COLLECTION_SUNPRO)

STD_HEADER_LISTS = $(STLPORT_ETC_DIR)/std_headers.txt \
                   $(STLPORT_ETC_DIR)/std_headers_cpp_runtime_h.txt \
                   $(STLPORT_ETC_DIR)/std_headers_c.txt \
                   $(STLPORT_ETC_DIR)/std_headers_c_h.txt \
                   $(STLPORT_ETC_DIR)/std_headers_classic_iostreams.txt \
                   $(STLPORT_ETC_DIR)/std_headers_cpp_runtime.txt

$(DEPENDS_COLLECTION_SUNPRO) : $(STD_HEADER_LISTS)
	@echo "Linking header files required for SunPro compiler"
	@for file in `cat $(STD_HEADER_LISTS)`; do \
	  echo "." | awk '{printf("%s", $$0)}' ; \
	  (cd $(STLPORT_INCLUDE_DIR) ; rm -f $$file.SUNWCCh; ln -s ./$$file $$file.SUNWCCh) ; \
        done; echo ""
	@cat $(STD_HEADER_LISTS) | awk '{print "$(STLPORT_INCLUDE_DIR)/" $$0 ".SUNWCCh : $(STLPORT_INCLUDE_DIR)/" $$0 }'  > $@
