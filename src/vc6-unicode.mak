#
# Tools
#

CXX=cl.exe
CC=cl.exe
RC=rc

LIB_BASENAME=stlport_vc6_unicode
COMP=VC6_UNICODE

EXTRA_COMMON_FLAGS=/Zm800 /FI "vc_warning_disable.h" /D "_UNICODE" /D "UNICODE"
EXTRA_DEBUG_FLAGS=
EXTRA_NDEBUG_FLAGS=

all: all_dynamic all_static

!INCLUDE vc_common.mak

#
#



