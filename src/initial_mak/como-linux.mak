#
# Note : this makefile has been tested for como-4.3.0.1+gcc-2.96 on Redhat 7.3
#

#
# compiler
#
CC = como
CXX = como

#
# Basename for libraries
#
LIB_BASENAME = libstlport_como

#
# guts for common stuff
#
#
LINK=ar cr
DYN_LINK=gcc -shared -o 

OBJEXT=o
DYNEXT=so
STEXT=a
RM=rm -rf
PATH_SEP=/
MKDIR=mkdir -p
COMP=COMO_LINUX
INSTALL_STEP = install_unix 
TOUCH=touch

all: all_static symbolic_links

include common_macros.mak

WARNING_FLAGS= -DLIBCIO= --diag_suppress=68 -D_POSIX_SOURCE -D_SVID_SOURCE -D__null=0L -D__GNUG__

CXXFLAGS_COMMON = -I. -I${STLPORT_DIR} ${WARNING_FLAGS}

CXXFLAGS_RELEASE_static = $(CXXFLAGS_COMMON) -O2
CXXFLAGS_RELEASE_dynamic = $(CXXFLAGS_COMMON) -O2 -copt="-fPIC"

CXXFLAGS_DEBUG_static = $(CXXFLAGS_COMMON) -g -O
CXXFLAGS_DEBUG_dynamic = $(CXXFLAGS_COMMON) -g -O -copt="-fPIC"

CXXFLAGS_STLDEBUG_static = $(CXXFLAGS_DEBUG_static) -D_STLP_DEBUG
CXXFLAGS_STLDEBUG_dynamic = $(CXXFLAGS_DEBUG_dynamic) -D_STLP_DEBUG

include common_percent_rules.mak
include common_rules.mak

# rules for prelinking

$(OUTDIR)$(PATH_SEP)$(RELEASE_LIB): $(RELEASE_OBJDIR_static)$(PATH_SEP).prelink
$(RELEASE_OBJDIR_static)$(PATH_SEP).prelink: $(RELEASE_OBJDIR_static) $(RELEASE_OBJECTS_static)
	$(CXX) $(CXXFLAGS_RELEASE_static) --prelink_object $(RELEASE_OBJECTS_static)
	$(TOUCH) $(RELEASE_OBJDIR_static)$(PATH_SEP).prelink

$(OUTDIR)$(PATH_SEP)$(RELEASE_DYNLIB): $(RELEASE_OBJDIR_dynamic)$(PATH_SEP).prelink
$(RELEASE_OBJDIR_dynamic)$(PATH_SEP).prelink: $(RELEASE_OBJDIR_dynamic) $(RELEASE_OBJECTS_dynamic)
	$(CXX) $(CXXFLAGS_RELEASE_dynamic) --prelink_object $(RELEASE_OBJECTS_dynamic)
	$(TOUCH) $(RELEASE_OBJDIR_dynamic)$(PATH_SEP).prelink

$(OUTDIR)$(PATH_SEP)$(DEBUG_LIB): $(DEBUG_OBJDIR_static)$(PATH_SEP).prelink
$(DEBUG_OBJDIR_static)$(PATH_SEP).prelink: $(DEBUG_OBJDIR_static) $(DEBUG_OBJECTS_static)
	$(CXX) $(CXXFLAGS_DEBUG_static) --prelink_object $(DEBUG_OBJECTS_static)
	$(TOUCH) $(DEBUG_OBJDIR_static)$(PATH_SEP).prelink

$(OUTDIR)$(PATH_SEP)$(DEBUG_DYNLIB): $(DEBUG_OBJDIR_dynamic)$(PATH_SEP).prelink
$(DEBUG_OBJDIR_dynamic)$(PATH_SEP).prelink: $(DEBUG_OBJDIR_dynamic) $(DEBUG_OBJECTS_dynamic)
	$(CXX) $(CXXFLAGS_DEBUG_dynamic) --prelink_object $(DEBUG_OBJECTS_dynamic)
	$(TOUCH) $(DEBUG_OBJDIR_dynamic)$(PATH_SEP).prelink

$(OUTDIR)$(PATH_SEP)$(STLDEBUG_LIB): $(STLDEBUG_OBJDIR_static)$(PATH_SEP).prelink
$(STLDEBUG_OBJDIR_static)$(PATH_SEP).prelink: $(STLDEBUG_OBJDIR_static) $(STLDEBUG_OBJECTS_static)
	$(CXX) $(CXXFLAGS_STLDEBUG_static) --prelink_object $(STLDEBUG_OBJECTS_static)
	$(TOUCH) $(STLDEBUG_OBJDIR_static)$(PATH_SEP).prelink

$(OUTDIR)$(PATH_SEP)$(STLDEBUG_DYNLIB): $(STLDEBUG_OBJDIR_dynamic)$(PATH_SEP).prelink
$(STLDEBUG_OBJDIR_dynamic)$(PATH_SEP).prelink: $(STLDEBUG_OBJDIR_dynamic) $(STLDEBUG_OBJECTS_dynamic)
	$(CXX) $(CXXFLAGS_STLDEBUG_dynamic) --prelink_object $(STLDEBUG_OBJECTS_dynamic)
	$(TOUCH) $(STLDEBUG_OBJDIR_dynamic)$(PATH_SEP).prelink
