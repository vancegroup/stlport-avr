#
# Tools
#

CXX=cl.exe
CC=cl.exe
RC=rc

LIB_BASENAME=stlport_vc5
COMP=VC5

# EXTRA_COMMON_FLAGS=/D "_MBCS" /D "__STL_NO_FORCE_INSTANTIATE"
EXTRA_COMMON_FLAGS=/Zm800 /FI "vc_warning_disable.h" /D "_MBCS"
EXTRA_DEBUG_FLAGS=
EXTRA_NDEBUG_FLAGS=

all: all_static

!INCLUDE vc_common.mak

#
#



