# Time-stamp: <10/06/02 15:17:35 ptr>
#
# Copyright (c) 1997-1999, 2002, 2003, 2005-2010
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

ifndef BUILD_DATE

ifndef TARGET_OS
OSNAME := $(shell uname -s | tr '[A-Z]' '[a-z]' | tr ', /\\()"' ',//////' | tr ',/' ',-')

ifeq ($(OSNAME),darwin)
OSREALNAME := $(shell sw_vers -productName | tr '[A-Z]' '[a-z]' | tr -d ', /\\()"')
endif

# RedHat use nonstandard options for uname at least in cygwin,
# macro should be overwritten:
ifeq (cygwin,$(findstring cygwin,$(OSNAME)))
OSNAME    := windows
OSREALNAME := $(shell uname -o | tr '[A-Z]' '[a-z]' | tr ', /\\()"' ',//////' | tr ',/' ',-')
endif

ifeq (mingw,$(findstring mingw,$(OSNAME)))
OSNAME    := windows
OSREALNAME := mingw
endif

OSREL  := $(shell uname -r | tr '[A-Z]' '[a-z]' | tr ', /\\()"' ',//////' | tr ',/' ',-')
ifeq ($(OSNAME),darwin)
OSREL  := $(shell sw_vers -productVersion | tr '[A-Z]' '[a-z]' | tr ', /\\()"' ',//////' | tr ',/' ',-')
endif
M_ARCH := $(shell uname -m | tr '[A-Z]' '[a-z]' | tr ', /\\()"' ',//////' | tr ',/' ',-')
ifeq ($(M_ARCH),power-macintosh)
M_ARCH := ppc
endif
ifeq ($(OSNAME),hp-ux)
P_ARCH := unknown
else
P_ARCH := $(shell uname -p | tr '[A-Z]' '[a-z]' | tr ', /\\()"' ',//////' | tr ',/' ',-')
endif

else
ifneq ($(TARGET_OS),arm-eabi)
OSNAME := $(shell echo ${TARGET_OS} | sed -e 's/^[a-z0-9_]\+-[a-z0-9]\+-\([a-z]\+\).*/\1/' -e 's/^[a-z0-9_]\+-\([a-z]\+\).*/\1/' )
OSREL  := $(shell echo ${TARGET_OS} | sed -e 's/^[[:alnum:]_]\+-[a-z0-9]\+-[a-z]\+\([a-zA-Z.0-9]*\).*/\1/' -e 's/^[a-z0-9_]\+-[a-z]\+\([a-zA-Z.0-9]*\).*/\1/' )
M_ARCH := $(shell echo ${TARGET_OS} | sed 's/^\([a-z0-9_]\+\)-.*/\1/' )
P_ARCH := unknown
else
# Assume android NDK 1.5 r1
OSNAME := android
# don't know, what OS release
# Known at this time:
#   Android 2.1 Release 1
#   Android 1.6 Release 2
#   Android 1.5 Release 3
# Older:
#   Android 2.0.1 Release 1
#   Android 2.0 Release 1
#   Android 1.1
OSREL  := 
M_ARCH := arm
# ARM v5TE
P_ARCH := ARM_5TE

_TMP := $(shell ${TARGET_OS}-c++ -mandroid -print-file-name=libgcc.a | xargs dirname | xargs dirname | xargs dirname | xargs dirname | xargs dirname | xargs dirname | xargs dirname | xargs dirname | xargs dirname | xargs dirname | xargs dirname)
# NDK 1.5 r1: android-1.5
# NDK 1.6 r1: android-3 or android-4
ANDROID_REV := 4
_TMP2 := $(shell echo $(_TMP) | grep -o -- '-.\..' | sed -e s/1\.6/$(ANDROID_REV)/)
SYSROOT ?= $(_TMP)/platforms/android$(_TMP2)/arch-arm
endif
# TARGET_OS
endif

NODENAME := $(shell uname -n | tr '[A-Z]' '[a-z]' )
SYSVER := $(shell uname -v )
USER := $(shell id -un )

ifeq ($(OSNAME),freebsd)
OSREL_MAJOR := $(shell echo ${OSREL} | tr '.-' ' ' | awk '{print $$1;}')
OSREL_MINOR := $(shell echo ${OSREL} | tr '.-' ' ' | awk '{print $$2;}')
endif

ifeq ($(OSNAME),darwin)
OSREL_MAJOR := $(shell echo ${OSREL} | tr '.-' ' ' | awk '{print $$1;}')
OSREL_MINOR := $(shell echo ${OSREL} | tr '.-' ' ' | awk '{print $$2;}')
MACOSX_TEN_FIVE := $(shell if [ ${OSREL_MAJOR} -lt 10 ]; then echo false; else if [ ${OSREL_MAJOR} -gt 10 ] ; then echo true; else if [ ${OSREL_MINOR} -lt 5 ]; then echo false; else echo true; fi; fi; fi)
endif

# OS_VER := $(shell uname -s | tr '[A-Z]' '[a-z]' | tr ', /\\()"' ',//////' | tr ',/' ',_')

BUILD_SYSTEM := $(shell { uname -n; uname -s; uname -r; uname -v; uname -m; id -un; } | tr '\n' ' ' )
BUILD_DATE := $(shell date +'%Y/%m/%d %T %Z')

BUILD_OSNAME := $(shell uname -s | tr '[A-Z]' '[a-z]' | tr ', /\\()"' ',//////' | tr ',/' ',-')

# RedHat use nonstandard options for uname at least in cygwin,
# macro should be overwritten:
ifeq (cygwin,$(findstring cygwin,$(BUILD_OSNAME)))
BUILD_OSNAME    := windows
BUILD_OSREALNAME := $(shell uname -o | tr '[A-Z]' '[a-z]' | tr ', /\\()"' ',//////' | tr ',/' ',-')
endif

ifeq (mingw,$(findstring mingw,$(BUILD_OSNAME)))
BUILD_OSNAME    := windows
BUILD_OSREALNAME := mingw
endif

BUILD_OSREL  := $(shell uname -r | tr '[A-Z]' '[a-z]' | tr ', /\\()"' ',//////' | tr ',/' ',-')
BUILD_M_ARCH := $(shell uname -m | tr '[A-Z]' '[a-z]' | tr ', /\\()"' ',//////' | tr ',/' ',-')
ifeq ($(OSNAME),hp-ux)
BUILD_P_ARCH := unknown
else
BUILD_P_ARCH := $(shell uname -p | tr '[A-Z]' '[a-z]' | tr ', /\\()"' ',//////' | tr ',/' ',-')
endif

# end of BUILD_DATE not defined
endif
