# build/Makefiles/nmake/lib/evc8.mak



LDFLAGS_COMMON = coredll.lib corelibc.lib /nologo /incremental:no /subsystem:windowsce,5.00 /nodefaultlib:OLDNAMES.lib 
# LDFLAGS_COMMON = coredll.lib corelibc.lib ole32.lib oleaut32.lib uuid.lib commctrl.lib /verbose:lib /nologo /incremental:no /subsystem:windowsce,5.00 /nodefaultlib:OLDNAMES.lib /nodefaultlib:msvcrt.lib /nodefaultlib:msvcrtd.lib

!include evc-common.mak
