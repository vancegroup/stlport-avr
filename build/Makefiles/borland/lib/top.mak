# -*- makefile -*- Time-stamp:
# $Id: top.mak

!message build\Makefiles\borland\lib\top.mak

.AUTODEPEND

!ifndef LDFLAGS
LDFLAGS =  -ap -D -Gn -Gi -Tpd -V4.00 -v -w -w-dup
!endif

LINK_cpp_REL           = $(LINK) $(LDFLAGS)
LINK_cpp_DBG           = $(LINK) $(LDFLAGS)
LINK_cpp_STLDBG        = $(LINK) $(LDFLAGS)
LINK_cpp_STATIC        = $(LINK) $(LDFLAGS)
LINK_cpp_STATIC_DBG    = $(LINK) $(LDFLAGS)
LINK_cpp_STATIC_STLDBG = $(LINK) $(LDFLAGS)

!include $(RULESBASE)\$(USE_MAKE)\lib\macro.mak
!include $(RULESBASE)\$(USE_MAKE)\lib\$(COMPILER_NAME).mak
!include $(RULESBASE)\$(USE_MAKE)\lib\rules-so.mak
!include $(RULESBASE)\$(USE_MAKE)\lib\rules-a.mak
!include $(RULESBASE)\$(USE_MAKE)\lib\rules-install-so.mak
!include $(RULESBASE)\$(USE_MAKE)\lib\rules-install-a.mak
!include $(RULESBASE)\$(USE_MAKE)\lib\clean.mak
