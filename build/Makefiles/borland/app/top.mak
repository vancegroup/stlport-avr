# -*- makefile -*- Time-stamp:
# $Id: top.mak

!message build\Makefiles\borland\app\top.mak

.AUTODEPEND

!ifndef LDFLAGS
LDFLAGS = -ap -Gn -Tpe -V4.00 -w -w-dup -x
!endif                                      

LINK_cpp_REL           = $(LINK) $(LDFLAGS) 
LINK_cpp_DBG           = $(LINK) $(LDFLAGS) -v
LINK_cpp_STLDBG        = $(LINK) $(LDFLAGS) -v
LINK_cpp_STATIC        = $(LINK) $(LDFLAGS)
LINK_cpp_STATIC_DBG    = $(LINK) $(LDFLAGS) -v
LINK_cpp_STATIC_STLDBG = $(LINK) $(LDFLAGS) -v

!include $(RULESBASE)\$(USE_MAKE)\app\macro.mak
!include $(RULESBASE)\$(USE_MAKE)\app\$(COMPILER_NAME).mak
!include $(RULESBASE)\$(USE_MAKE)\app\macro-$(COMPILER_NAME).mak
!include $(RULESBASE)\$(USE_MAKE)\app\rules-exe-$(OSNAME).mak
!include $(RULESBASE)\$(USE_MAKE)\app\rules-install.mak
!include $(RULESBASE)\$(USE_MAKE)\app\clean.mak

