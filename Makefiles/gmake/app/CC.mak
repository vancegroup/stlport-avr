# -*- Makefile -*- Time-stamp: <07/03/08 21:53:08 ptr>
#
# Copyright (c) 1997-1999, 2002, 2003, 2005-2007
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

ifndef WITHOUT_STLPORT
ifeq (${STLPORT_LIB_DIR},)
release-shared:	STLPORT_LIB = -lstlport
release-static:	STLPORT_LIB = -Bstatic -lstlport -Bdynamic
dbg-shared:	STLPORT_LIB = -lstlportg
dbg-static:	STLPORT_LIB = -Bstatic -lstlportg -Bdynamic
stldbg-shared:	STLPORT_LIB = -lstlportstlg
stldbg-static:	STLPORT_LIB = -Bstatic -lstlportstlg -Bdynamic
else
# STLPORT_LIB_DIR not empty
release-shared: STLPORT_LIB = -L${STLPORT_LIB_DIR} -R${STLPORT_LIB_DIR} -lstlport
release-static: STLPORT_LIB = -L${STLPORT_LIB_DIR} -Bstatic -lstlport -Bdynamic
dbg-shared:     STLPORT_LIB = -L${STLPORT_LIB_DIR} -R${STLPORT_LIB_DIR} -lstlportg
dbg-static:     STLPORT_LIB = -L${STLPORT_LIB_DIR} -Bstatic -lstlportg -Bdynamic
stldbg-shared:  STLPORT_LIB = -L${STLPORT_LIB_DIR} -R${STLPORT_LIB_DIR} -lstlportstlg
stldbg-static:  STLPORT_LIB = -L${STLPORT_LIB_DIR} -Bstatic -lstlportstlg -Bdynamic
endif
endif

STDLIBS = $(STLPORT_LIB) -lCrun -lm -lc
