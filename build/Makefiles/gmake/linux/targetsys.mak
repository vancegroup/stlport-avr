# Time-stamp: <05/09/09 20:59:42 ptr>
# $Id$

SO := so

ARCH := a
ifdef TARGET_OS
AR := ${TARGET_OS}-ar
else
AR := ar
endif
AR_INS_R := -rs
AR_EXTR := -x
AR_OUT = $@
