# -*- Makefile -*- Time-stamp: <2011-10-02 12:31:05 ptr>

LIBNAME = stlport
MAJOR = 6
MINOR = 0
PATCH = 0
SRC_CPP = dll_main.cpp \
          fstream.cpp \
          strstream.cpp \
          sstream.cpp \
          ios.cpp \
          stdio_streambuf.cpp \
          istream.cpp \
          ostream.cpp \
          iostream.cpp \
          codecvt.cpp \
          collate.cpp \
          ctype.cpp \
          monetary.cpp \
          num_get.cpp \
          num_put.cpp \
          num_get_float.cpp \
          num_put_float.cpp \
          numpunct.cpp \
          time_facets.cpp \
          messages.cpp \
          locale.cpp \
          locale_impl.cpp \
          locale_catalog.cpp \
          facets_byname.cpp \
          complex.cpp \
          complex_io.cpp \
          complex_trig.cpp \
          string.cpp \
          bitset.cpp \
          allocators.cpp

SRC_CC = chrono.cc \
         reachable.cc \
         except.cc

SRC_C = c_locale.c \
        cxa.c

SRC_RC = stlport.rc
