# Time-stamp: 
# $Id: bc56.mak

!message build\Makefiles\borland\bc56.mak

.AUTODEPEND

!ifndef BCBX
BCBX = $(MAKEDIR)\..
!endif

!ifndef STLPORT_INCLUDE_DIR
STLPORT_INCLUDE_DIR = $(STLPORT_DIR)\stlport
!endif

!ifndef BCBX_INCLUDE_DIR
BCBX_INCLUDE_DIR = $(STLPORT_DIR)\..\include
!endif

INCLUDES = -I$(STLPORT_INCLUDE_DIR);$(STLPORT_DIR);$(BCBX_INCLUDE_DIR);$(INCLUDES)

CXX  = bcc32 -P
CC   = bcc32 -P
LINK = ilink32
RC   = brc32

!ifdef DEFS
DEFS_REL           = $(DEFS) $(DEFS_REL)
DEFS_DBG           = $(DEFS) $(DEFS_DBG)
DEFS_STLDBG        = $(DEFS) $(DEFS_STLDBG)
DEFS_STATIC        = $(DEFS) $(DEFS_STATIC)
DEFS_STATIC_DBG    = $(DEFS) $(DEFS_STATIC_DBG)
DEFS_STATIC_STLDBG = $(DEFS) $(DEFS_STATIC_STLDBG)
!endif

!ifdef OPT
OPT_REL           = $(OPT) $(OPT_REL)
OPT_DBG           = $(OPT) $(OPT_DBG)
OPT_STLDBG        = $(OPT) $(OPT_STLDBG)
OPT_STATIC        = $(OPT) $(OPT_STATIC)
OPT_STATIC_DBG    = $(OPT) $(OPT_STATIC_DBG)
OPT_STATIC_STLDBG = $(OPT) $(OPT_STATIC_STLDBG)
!endif

OUTPUT_OPTION               =
OUTPUT_OPTION_DBG           =
OUTPUT_OPTION_STLDBG        =
OUTPUT_OPTION_STATIC        =
OUTPUT_OPTION_STATIC_DBG    =
OUTPUT_OPTION_STATIC_STLDBG =

RC_OUTPUT_OPTION               = 
RC_OUTPUT_OPTION_DBG           = 
RC_OUTPUT_OPTION_STLDBG        = 
RC_OUTPUT_OPTION_STATIC        = 
RC_OUTPUT_OPTION_STATIC_DBG    = 
RC_OUTPUT_OPTION_STATIC_STLDBG = 

# option flags
OPT_REL           = $(OPT_REL)           -xd -xp -Od
OPT_DBG           = $(OPT_DBG)           -xd -xp -Od -k -y -v
OPT_STLDBG        = $(OPT_STLDBG)        -xd -xp -Od -k -y -v
OPT_STATIC        = $(OPT_STATIC)        -xd -xp -Od
OPT_STATIC_DBG    = $(OPT_STATIC_DBG)    -xd -xp -Od -k -y -v
OPT_STATIC_STLDBG = $(OPT_STATIC_STLDBG) -xd -xp -Od -k -y -v

# STLport release, debug, and stldebug mode specific defines
DEFS_REL           = $(DEFS_REL)           
DEFS_DBG           = $(DEFS_DBG)           -D_DEBUG -D__DEBUG=1
DEFS_STLDBG        = $(DEFS_STLDBG)        -D_DEBUG -D__DEBUG=2 -D_STLP_DEBUG

DEFS_STATIC        = $(DEFS_STATIC)
DEFS_STATIC_DBG    = $(DEFS_STATIC_DBG)    -D_DEBUG -D__DEBUG=1 
DEFS_STATIC_STLDBG = $(DEFS_STATIC_STLDBG) -D_DEBUG -D__DEBUG=2 -D_STLP_DEBUG

CPPFLAGS_REL           = $(DEFS_REL)           $(INCLUDES) -D_RTLDLL
CPPFLAGS_DBG           = $(DEFS_DBG)           $(INCLUDES) -D_RTLDLL
CPPFLAGS_STLDBG        = $(DEFS_STLDBG)        $(INCLUDES) -D_RTLDLL
CPPFLAGS_STATIC        = $(DEFS_STATIC)        $(INCLUDES)
CPPFLAGS_STATIC_DBG    = $(DEFS_STATIC_DBG)    $(INCLUDES)
CPPFLAGS_STATIC_STLDBG = $(DEFS_STATIC_STLDBG) $(INCLUDES)

CFLAGS_COMMON          = -c -g0 -He- -Hs- -j3  -K -R -r- -q -vi- -ff -xf- -RT -tWM \
                         -w-sig -w-inl -w-use -w-pch -w-msg -w-aus -w-par \ 
                         -w-rch -w-ccc -w-csu -w-ngu -w-nst -w-eff

CFLAGS_REL           = $(CFLAGS_COMMON) $(OPT_REL)
CFLAGS_DBG           = $(CFLAGS_COMMON) $(OPT_DBG)
CFLAGS_STLDBG        = $(CFLAGS_COMMON) $(OPT_STLDBG)
CFLAGS_STATIC        = $(CFLAGS_COMMON) $(OPT_STATIC)
CFLAGS_STATIC_DBG    = $(CFLAGS_COMMON) $(OPT_STATIC_DBG)
CFLAGS_STATIC_STLDBG = $(CFLAGS_COMMON) $(OPT_STATIC_STLDBG)

CXXFLAGS_COMMON        = -c -g0 -He- -Hs- -j3  -K -R -r- -q -vi- -ff -xf- -RT -tWM \
                         -w-sig -w-inl -w-use -w-pch -w-msg -w-aus -w-par \ 
                         -w-rch -w-ccc -w-csu -w-ngu -w-nst -w-eff

CXXFLAGS_REL           = $(CXXFLAGS_COMMON) $(OPT_REL)
CXXFLAGS_DBG           = $(CXXFLAGS_COMMON) $(OPT_DBG)
CXXFLAGS_STLDBG        = $(CXXFLAGS_COMMON) $(OPT_STLDBG)
CXXFLAGS_STATIC        = $(CXXFLAGS_COMMON) $(OPT_STATIC)
CXXFLAGS_STATIC_DBG    = $(CXXFLAGS_COMMON) $(OPT_STATIC_DBG)
CXXFLAGS_STATIC_STLDBG = $(CXXFLAGS_COMMON) $(OPT_STATIC_STLDBG)

CDEPFLAGS  = 
CCDEPFLAGS = 
TARGET_ARCH = -4

COMPILE_c_REL             = $(CC)  $(CFLAGS_REL)             $(CPPFLAGS_REL)           $(TARGET_ARCH)
COMPILE_c_DBG             = $(CC)  $(CFLAGS_DBG)             $(CPPFLAGS_DBG)           $(TARGET_ARCH) 
COMPILE_c_STLDBG          = $(CC)  $(CFLAGS_STLDBG)          $(CPPFLAGS_STLDBG)        $(TARGET_ARCH) 
COMPILE_c_STATIC          = $(CC)  $(CFLAGS_STATIC)          $(CPPFLAGS_STATIC)        $(TARGET_ARCH) 
COMPILE_c_STATIC_DBG      = $(CC)  $(CFLAGS_STATIC_DBG)      $(CPPFLAGS_STATIC_DBG)    $(TARGET_ARCH) 
COMPILE_c_STATIC_STLDBG   = $(CC)  $(CFLAGS_STATIC_STLDBG)   $(CPPFLAGS_STATIC_STLDBG) $(TARGET_ARCH) 

COMPILE_cpp_REL           = $(CXX) $(CXXFLAGS_REL)           $(CPPFLAGS_REL)           $(TARGET_ARCH)
COMPILE_cpp_DBG           = $(CXX) $(CXXFLAGS_DBG)           $(CPPFLAGS_DBG)           $(TARGET_ARCH) 
COMPILE_cpp_STLDBG        = $(CXX) $(CXXFLAGS_STLDBG)        $(CPPFLAGS_STLDBG)        $(TARGET_ARCH) 
COMPILE_cpp_STATIC        = $(CXX) $(CXXFLAGS_STATIC)        $(CPPFLAGS_STATIC)        $(TARGET_ARCH) 
COMPILE_cpp_STATIC_DBG    = $(CXX) $(CXXFLAGS_STATIC_DBG)    $(CPPFLAGS_STATIC_DBG)    $(TARGET_ARCH) 
COMPILE_cpp_STATIC_STLDBG = $(CXX) $(CXXFLAGS_STATIC_STLDBG) $(CPPFLAGS_STATIC_STLDBG) $(TARGET_ARCH) 

RC_FLAGS_REL =
RC_FLAGS_DBG =
RC_FLAGS_STLDBG =
RC_FLAGS_STATIC =
RC_FLAGS_STATIC_DBG =
RC_FLAGS_STATIC_STLDBG =

COMPILE_rc_REL           = $(RC) $(RC_FLAGS_REL)
COMPILE_rc_DBG           = $(RC) $(RC_FLAGS_DBG)
COMPILE_rc_STLDBG        = $(RC) $(RC_FLAGS_STLDBG)
COMPILE_rc_STATIC        = $(RC) $(RC_FLAGS_STATIC)
COMPILE_rc_STATIC_DBG    = $(RC) $(RC_FLAGS_STATIC_DBG)
COMPILE_rc_STATIC_STLDBG = $(RC) $(RC_FLAGS_STATIC_STLDBG)


