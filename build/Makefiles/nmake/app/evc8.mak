# build/Makefiles/nmake/app/evc8.mak

LDFLAGS_COMMON = $(LDFLAGS_COMMON) /entry:"WinMainCRTStartup"

!include evc-common.mak
