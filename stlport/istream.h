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

#ifndef __STLPORT_ISTREAM_H
# define __STLPORT_ISTREAM_H

# ifndef __STL_OUTERMOST_HEADER_ID
#  define __STL_OUTERMOST_HEADER_ID 0x2037
#  include <stl/_prolog.h>
# endif

# if defined (__SGI_STL_OWN_IOSTREAMS)

# include <istream>

# ifndef __STL_HAS_NO_NAMESPACES
#  ifdef __STL_BROKEN_USING_DIRECTIVE
using namespace __STLPORT_STD;
#  else
using __STLPORT_STD::basic_istream;
using __STLPORT_STD::basic_iostream;
using __STLPORT_STD::istream;
using __STLPORT_STD::iostream;
#   ifndef __STL_NO_WCHAR_T
using __STLPORT_STD::wistream;
using __STLPORT_STD::wiostream;
#   endif
using __STLPORT_STD::ws;
#  endif
# endif

# elif !defined (__STL_USE_NO_IOSTREAMS)

# include __STL_NATIVE_OLD_STREAMS_HEADER(istream.h)

# if defined (__STL_USE_NAMESPACES) && !defined (__STL_BROKEN_USING_DIRECTIVE)
__STL_BEGIN_NAMESPACE
using __STL_OLD_IO_NAMESPACE::istream;
__STL_END_NAMESPACE
# endif /* __STL_USE_OWN_NAMESPACE */

# endif /* __SGI_STL_OWN_IOSTREAMS */

# if (__STL_OUTERMOST_HEADER_ID == 0x2037)
#  include <stl/_epilog.h>
#  undef __STL_OUTERMOST_HEADER_ID
# endif

#endif /* __STLPORT_ISTREAM_H */

