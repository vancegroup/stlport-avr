# Time-stamp:
# $Id: targets.mak

!message build\Makefiles\borland\targets.mak

ALLORIG		 = $(SRC_CPP) $(SRC_CC) $(SRC_C)

!if $(PRGNAME) == stl_unit_test
ALLBASE_AUX  = $(ALLORIG:../../../test/unit/=)
ALLBASE      = $(ALLBASE_AUX:/=\)
SRC_CPP_A    = $(ALLBASE)
!else
ALLBASE      = $(ALLORIG)
!endif

!if $(LIBNAME) == stlp$(MAJOR)$(MINOR)
ALLBASE_A = $(SRC_CPP_A)
!else
ALLBASE_A = $(ALLBASE)
!endif

.precious: $(ALLORIG)
.precious: $(ALLBASE)

ALLORIG_OBJS = $(SRC_CPP:.cpp=.obj) $(SRC_CC:.cc=.obj) $(SRC_C:.c=.obj)
ALLBASE_OBJS = $(ALLORIG_OBJS:../../../test/unit/=)
ALLOBJS      = $(ALLBASE_OBJS:cppunit/=) 
ALLOBJS_A    = $(SRC_CPP_A:.cpp=.obj)
ALLRESS      = $(SRC_RC)

!ifdef $(SRC_RC) 
.precious: $(ALLRESS)
!endif

OBJ          = $(OBJ)
OBJ_DBG      = $(OBJ_DBG)
OBJ_STLDBG   = $(OBJ_STLDBG)

OBJ_A        = $(OBJ_A)
OBJ_A_DBG    = $(OBJ_A_DBG)
OBJ_A_STLDBG = $(OBJ_A_STLDBG)

RES          = $(ALLRESS) 
RES_DBG      = $(ALLRESS) 
RES_STLDBG   = $(ALLRESS) 

!ifdef SO_NOINIT
DEF_FILE        = $(SRCROOT_EXT)\$(USE_MAKE)\noinit.def
DEF_FILE_DBG    = $(SRCROOT_EXT)\$(USE_MAKE)\noinit.def
DEF_FILE_STLDBG = $(SRCROOT_EXT)\$(USE_MAKE)\noinit.def
!else
DEF_FILE        = 
DEF_FILE_DBG    = 
DEF_FILE_STLDBG = 
!endif

!ifdef A_NOINIT
DEF_FILE_A        = $(SRCROOT_EXT)\$(USE_MAKE)\noinit.def
DEF_FILE_A_DBG    = $(SRCROOT_EXT)\$(USE_MAKE)\noinit.def
DEF_FILE_A_STLDBG = $(SRCROOT_EXT)\$(USE_MAKE)\noinit.def
!else
DEF_FILE_A        = 
DEF_FILE_A_DBG    = 
DEF_FILE_A_STLDBG = 
!endif
