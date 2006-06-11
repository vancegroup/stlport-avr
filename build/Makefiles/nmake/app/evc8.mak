# build/Makefiles/nmake/app/evc8.mak

LDFLAGS_COMMON = $(LDFLAGS_COMMON) /entry:"mainACRTStartup"

!include evc-common.mak
