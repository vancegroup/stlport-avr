/*
 * Copyright (c) 1999 
 * Boris Fomitchev
 *
 * This material is provided "as is", with absolutely no warranty expressed
 * or implied. Any use is at your own risk.
 *
 * Permission to use or copy this software for any purpose is hereby granted 
 * without fee, provided the above notices are retained on all copies.
 * Permission to modify the code and to distribute modified code is granted,
 * provided the above notices are retained, and a notice that the code was
 * modified is included with the above copyright notice.
 *
 */

#ifndef __STLPORT_IOSTREAM_H
# define __STLPORT_IOSTREAM_H

# ifndef __STL_OUTERMOST_HEADER_ID
#  define __STL_OUTERMOST_HEADER_ID 0x2035
#  include <stl/_prolog.h>
# endif

# ifdef __SGI_STL_OWN_IOSTREAMS

# include <iostream>

// Those should be included all separately, as they do contain using declarations
# include <streambuf.h>
# include <ostream.h>
# include <istream.h>


# ifndef __STL_HAS_NO_NAMESPACES

#  ifdef __STL_BROKEN_USING_DIRECTIVE
using namespace __STLPORT_STD;
#  else
using __STLPORT_STD::cin;
using __STLPORT_STD::cout;
using __STLPORT_STD::clog;
using __STLPORT_STD::cerr;
using __STLPORT_STD::iostream;

#   ifndef __STL_NO_WCHAR_T
using __STLPORT_STD::wcin;
using __STLPORT_STD::wcout;
using __STLPORT_STD::wclog;
using __STLPORT_STD::wcerr;
#   endif

#  endif

# endif /* __STL_HAS_NO_NAMESPACES */

// Obsolete classes for old-style backwards compatibility


class istream_withassign : public istream {
 public:
  istream_withassign() : istream((streambuf*)0) {}
  ~istream_withassign() {}
  
  istream_withassign& operator=(istream& __s) { 
    ios::init(__s.rdbuf()); 
    return *this; 
  }
  istream_withassign& operator=(streambuf* __s) {
    ios::init(__s); 
    return *this; 
  }
};

class ostream_withassign : public ostream {
 public:
  ostream_withassign() : ostream((streambuf*)0) {}
  ~ostream_withassign() {}
  
  ostream_withassign& operator=(ostream& __s) { 
    ios::init(__s.rdbuf()); 
    return *this; 
  }
  ostream_withassign& operator=(streambuf* __s) { 
    ios::init(__s); 
    return *this; 
  }
};

class iostream_withassign : public iostream {
 public:
  iostream_withassign() : iostream((streambuf*)0) {}
  ~iostream_withassign() {}
  iostream_withassign & operator=(ios& __i) {
    ios::init(__i.rdbuf());
    return *this; 
  }
  iostream_withassign & operator=(streambuf* __s) {
    ios::init(__s); 
    return *this; 
  }
} ;

# elif ! defined (__STL_USE_NO_IOSTREAMS)
#  include <wrap_std/h/iostream.h>
# endif

# if (__STL_OUTERMOST_HEADER_ID == 0x2035)
#  include <stl/_epilog.h>
#  undef __STL_OUTERMOST_HEADER_ID
# endif

#endif /* __STLPORT_IOSTREAM_H */

// Local Variables:
// mode:C++
// End:
