/*
 * Copyright (c) 1999
 * Silicon Graphics Computer Systems, Inc.
 *
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
#ifndef __STLPORT_STREAMBUF_H
# define __STLPORT_STREAMBUF_H

# ifndef __STL_OUTERMOST_HEADER_ID
#  define __STL_OUTERMOST_HEADER_ID 0x2067
#  include <stl/_prolog.h>
# endif

# if defined ( __SGI_STL_OWN_IOSTREAMS )

# include <streambuf>
# include <ios.h>

# ifndef __STL_HAS_NO_NAMESPACES
#  ifdef __STL_BROKEN_USING_DIRECTIVE
   using namespace __STLPORT_STD;
#  else
using __STLPORT_STD::basic_streambuf;
using __STLPORT_STD::streambuf;
#   ifndef __STL_NO_WCHAR_T
using __STLPORT_STD::wstreambuf;
#   endif
#  endif
# endif /* __STL_HAS_NO_NAMESPACES */

# elif !defined (__STL_USE_NO_IOSTREAMS)

# include __STL_NATIVE_OLD_STREAMS_HEADER(streambuf.h)

# endif

# if (__STL_OUTERMOST_HEADER_ID == 0x2067)
#  include <stl/_epilog.h>
#  undef __STL_OUTERMOST_HEADER_ID
# endif

#endif /* __STLPORT_STREAMBUF_H */

// Local Variables:
// mode:C++
// End:
