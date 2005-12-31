# -*- makefile -*- Time-stamp: <03/11/30 11:41:22 ptr>
# $Id$


release-shared : OPT += -tWD
dbg-shared : OPT += -tWD
stldbg-shared : OPT += -tWD

release-shared : LDFLAGS += -Tpd -V4.00 -v -w-dup
dbg-shared : LDFLAGS += -Tpd -V4.00 -v -w -w-dup
stldbg-shared : LDFLAGS += -Tpd -V4.00 -v -w -w-dup

START_OBJ := c0d32.obj

release-static : AR += /P32
dbg-static : AR += /P128
stldbg-static : AR += /P256

