# build/Makefiles/nmake/app/evc8.mak

LDFLAGS_COMMON = commctrl.lib coredll.lib corelibc.lib /nologo /entry:"WinMainCRTStartup" /incremental:no /subsystem:WINDOWSCE /nodefaultlib:LIBC.lib /nodefaultlib:OLDNAMES.lib $(LDFLAGS_COMMON)

!include evc-common.mak
