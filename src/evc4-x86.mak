#
# Tools
#

CXX=cl.exe
CC=cl.exe
RC=rc

LIB_BASENAME=stlport_x86
COMP=x86

CEVERSION=420

EXTRA_COMMON_FLAGS=/D "_i386_" /D "_X86_" /D "x86" /Gs8192 /GF
EXTRA_DEBUG_FLAGS=
#EXTRA_DEBUG_FLAGS=/D _STLP_REDIRECT_STDSTREAMS
EXTRA_NDEBUG_FLAGS=

#all: platform all_static all_dynamic 
all: platform all_static 

!INCLUDE evc4_common.mak

#
#



