#
#


#
# Tools
#

#Default tools

!IF "$(CC)" == ""
CC=cl.exe
!ENDIF
!IF "$(CXX)" == ""
CXX=cl.exe
!ENDIF
!IF "$(DYN_LINK)" == ""
DYN_LINK=link.exe
!ENDIF
!IF "$(LINK)" == ""
LINK=lib.exe
!ENDIF

#Files extension

OBJEXT=obj
DYNEXT=dll
STEXT=lib

PATH_SEP=\\

MKDIR=-mkdir
LINK_OUT=/out:
DYNLINK_OUT=/out:
STATIC_SUFFIX=_static
INSTALL_STEP=install_vc

!include common_macros_windows.mak

!IF "$(OS)" == "Windows_NT"
NULL=
RM=-rd /S /Q
!ELSE 
RM=-deltree /Y
NULL=nul
!ENDIF 


#
# Flags
#

FLAGS_COMMON =/nologo /c /W3 /D _WIN32_WCE=$(CEVERSION) /D "$(PLATFORM)" /D UNDER_CE=$(CEVERSION) /D "UNICODE" /D "_UNICODE" /I "$(STLPORT_DIR)" $(EXTRA_COMMON_FLAGS)
FLAGS_COMMON_static = $(FLAGS_COMMON) /D "_LIB" /D "_STLP_NO_FORCE_INSTANTIATE" /D _STLP_USE_STATIC_LIB
#FLAGS_COMMON_dynamic = $(FLAGS_COMMON) /D _STLP_USE_DYNAMIC_LIB

FLAGS_DEBUG=/Od /Zi /D "DEBUG" $(EXTRA_DEBUG_FLAGS)
FLAGS_NDEBUG=/O2 /D "NDEBUG"  $(EXTRA_NDEBUG_FLAGS)

LDFLAGS_COMMON=/nologo
LDFLAGS_DEBUG=
LDFLAGS_RELEASE=

LDFLAGS_COMMON_static=$(LDFLAGS_COMMON)
LDFLAGS_COMMON_dynamic=$(LDFLAGS_COMMON) /dll /incremental:no

# supply correct /M flags in EXTRA_COMMON_FLAGS
CXXFLAGS_DEBUG_static=$(FLAGS_COMMON_static) $(FLAGS_DEBUG) /Fo"$(DEBUG_OBJDIR_static)\\" /Fd"$(DEBUG_OBJDIR_static)\\"

CXXFLAGS_DEBUG_staticx=$(FLAGS_COMMON_static) $(FLAGS_DEBUG) /Fo"$(DEBUG_OBJDIR_staticx)\\" /Fd"$(DEBUG_OBJDIR_staticx)\\"

CXXFLAGS_DEBUG_dynamic=$(FLAGS_COMMON_dynamic) $(FLAGS_DEBUG) /Fo"$(DEBUG_OBJDIR_dynamic)\\" /Fd"$(DEBUG_OBJDIR_dynamic)\\"

CXXFLAGS_STLDEBUG_static=$(FLAGS_COMMON_static) $(FLAGS_DEBUG) /D "_STLP_DEBUG" /Fo"$(STLDEBUG_OBJDIR_static)\\" /Fd"$(STLDEBUG_OBJDIR_static)\\"

CXXFLAGS_STLDEBUG_staticx=$(FLAGS_COMMON_static) $(FLAGS_DEBUG) /D "_STLP_DEBUG" /Fo"$(STLDEBUG_OBJDIR_staticx)\\" /Fd"$(STLDEBUG_OBJDIR_staticx)\\"

CXXFLAGS_STLDEBUG_dynamic=$(FLAGS_COMMON_dynamic) $(FLAGS_DEBUG) /D "_STLP_DEBUG" /Fo"$(STLDEBUG_OBJDIR_dynamic)\\" /Fd"$(STLDEBUG_OBJDIR_dynamic)\\"


LDFLAGS_DEBUG_static=$(LDFLAGS_COMMON_static)
LDFLAGS_DEBUG_dynamic=$(LDFLAGS_COMMON_dynamic) $(LDFLAGS_DEBUG) /implib:"$(OUTDIR)\$(DEBUG_NAME).$(STEXT)"
LDFLAGS_STLDEBUG_static=$(LDFLAGS_COMMON_static)
LDFLAGS_STLDEBUG_dynamic=$(LDFLAGS_COMMON_dynamic) $(LDFLAGS_DEBUG) /implib:"$(OUTDIR)\$(STLDEBUG_NAME).$(STEXT)" 

# LDFLAGS_DEBUG_static=$(LDFLAGS_COMMON_static)  /DEBUGTYPE:CV
# LDFLAGS_DEBUG_dynamic=$(LDFLAGS_COMMON_dynamic) /DEBUG /DEBUGTYPE:CV /implib:"$(OUTDIR)\$(DEBUG_NAME).$(STEXT)" 
# LDFLAGS_STLDEBUG_static=$(LDFLAGS_COMMON_static)  /DEBUGTYPE:CV
# LDFLAGS_STLDEBUG_dynamic=$(LDFLAGS_COMMON_dynamic) /DEBUG /DEBUGTYPE:CV /implib:"$(OUTDIR)\$(STLDEBUG_NAME).$(STEXT)" 

CXXFLAGS_RELEASE_static=$(FLAGS_COMMON_static) $(FLAGS_NDEBUG) /Fo"$(RELEASE_OBJDIR_static)\\" /Fd"$(RELEASE_OBJDIR_static)\\"

CXXFLAGS_RELEASE_staticx=$(FLAGS_COMMON_static) $(FLAGS_NDEBUG) /Fo"$(RELEASE_OBJDIR_staticx)\\" /Fd"$(RELEASE_OBJDIR_staticx)\\"

CXXFLAGS_RELEASE_dynamic=$(FLAGS_COMMON_dynamic) $(FLAGS_NDEBUG) /Fo"$(RELEASE_OBJDIR_dynamic)\\" /Fd"$(RELEASE_OBJDIR_dynamic)\\"

LDFLAGS_RELEASE_static=$(LDFLAGS_COMMON_static)
LDFLAGS_RELEASE_dynamic=$(LDFLAGS_COMMON_dynamic) $(LDFLAGS_RELEASE) /implib:"$(OUTDIR)\$(RELEASE_NAME).$(STEXT)" 
# LDFLAGS_RELEASE_dynamic=$(LDFLAGS_COMMON_dynamic) /implib:"$(OUTDIR)\$(RELEASE_NAME).$(STEXT)" 

RESFILE=$(RELEASE_OBJDIR_dynamic)$(PATH_SEP)stlport.res
RESFILE_debug=$(DEBUG_OBJDIR_dynamic)$(PATH_SEP)stlport.res
RESFILE_stldebug=$(STLDEBUG_OBJDIR_dynamic)$(PATH_SEP)stlport.res


#
# Rules
#

!include common_rules.mak

!include nmake_common.mak

