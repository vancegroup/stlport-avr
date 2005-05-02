# Time-stamp: 
# $Id: sys.mak

!message build\Makefiles\borland\sys.mak

.AUTODEPEND

# shared library:
SO  = dll
LIB = lib
# executable:
EXE = exe

# static library extention:
ARCH     = lib
AR       = tlib
AR_INS_R = 
AR_EXTR  = /C /E /P64
AR_OUT   = 

INSTALL = copy

INSTALL_SO  = $(INSTALL)
INSTALL_A   = $(INSTALL)
INSTALL_EXE = $(INSTALL)

# compiler, compiler options
!include $(RULESBASE)\$(USE_MAKE)\$(COMPILER_NAME).mak
