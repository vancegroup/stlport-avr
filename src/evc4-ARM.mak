#
# Tools
#

CXX=clarm.exe
CC=clarm.exe
RC=rc

LIB_BASENAME=stlport_ARM
COMP=ARMV4

CEVERSION=420

EXTRA_COMMON_FLAGS=/D "ARM" /D "_ARM_" /D "ARMV4"
EXTRA_DEBUG_FLAGS=/D _STLP_REDIRECT_STDSTREAMS
EXTRA_NDEBUG_FLAGS=

#all: platform all_static all_dynamic 
all: platform all_static 

!INCLUDE evc4_common.mak

#
#



