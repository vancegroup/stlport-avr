# -*- makefile -*- Time-stamp: <03/11/30 11:41:22 ptr>
# $Id$


# Oh, the commented below work for gmake 3.78.1 and above,
# but phrase without tag not work for it. Since gmake 3.79 
# tag with assignment fail, but work assignment for all tags
# (really that more correct).

release-shared : OPT += -tWD
dbg-shared : OPT += -tWD
stldbg-shared : OPT += -tWD

release-shared : LDFLAGS += -Tpd c0d32.obj
dbg-shared : LDFLAGS += -Tpd -V4.00 -v -w -w-dup c0d32.obj
stldbg-shared : LDFLAGS += -Tpd c0d32.obj

