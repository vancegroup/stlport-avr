# Time-stamp: <03/07/15 12:45:30 ptr>
# $Id$

ifndef BUILD_DATE

OSNAME := $(shell uname -s | tr '[A-Z]' '[a-z]' | tr ', /\\()"' ',//////' | tr ',/' ',-')

# RedHat use nonstandard options for uname at least in cygwin,
# macro should be overwritten:
ifeq (cygwin,$(findstring cygwin,$(OSNAME)))
OSNAME := $(shell uname -o | tr '[A-Z]' '[a-z]' | tr ', /\\()"' ',//////' | tr ',/' ',-')
endif

OSREL := $(shell uname -r | tr '[A-Z]' '[a-z]' | tr ', /\\()"' ',//////' | tr ',/' ',-')
M_ARCH := $(shell uname -m | tr '[A-Z]' '[a-z]' | tr ', /\\()"' ',//////' | tr ',/' ',-')
P_ARCH := $(shell uname -p | tr '[A-Z]' '[a-z]' | tr ', /\\()"' ',//////' | tr ',/' ',-')
NODENAME := $(shell uname -n | tr '[A-Z]' '[a-z]' )
SYSVER := $(shell uname -v )
USER := $(shell echo $$USER )

# OS_VER := $(shell uname -s | tr '[A-Z]' '[a-z]' | tr ', /\\()"' ',//////' | tr ',/' ',_')

BUILD_SYSTEM := $(shell echo `uname -n` `uname -s` `uname -r` `uname -v` `uname -m` $$USER)
BUILD_DATE := $(shell date +'%Y/%m/%d %T %Z')

endif
