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

#ifndef __STLPORT_STRSTREAM_H
# define __STLPORT_STRSTREAM_H

# ifndef __STL_OUTERMOST_HEADER_ID
#  define __STL_OUTERMOST_HEADER_ID 0x2071
#  include <stl/_prolog.h>
# endif

# if defined ( __STL_USE_NEW_IOSTREAMS )

// fbp - if we are going to use that consistently, let's do it
# include  <strstream>
# include  <iostream.h>


# ifndef __STL_HAS_NO_NAMESPACES

#  ifdef __STL_BROKEN_USING_DIRECTIVE

using namespace __STLPORT_STD;

#  else

using __STLPORT_STD::strstreambuf;
using __STLPORT_STD::istrstream;
using __STLPORT_STD::ostrstream;
using __STLPORT_STD::strstream;

#  endif /* __STL_BROKEN_USING_DIRECTIVE */

# endif /* __STL_HAS_NO_NAMESPACES */

# else


// just include old-style strstream.h
#  if defined (_MSC_VER) && (_MSC_VER < 1200)
#   include __STL_NATIVE_OLD_STREAMS_HEADER(strstrea.h)
#  else
#   include __STL_NATIVE_OLD_STREAMS_HEADER(strstream.h)
#  endif

# endif

# if (__STL_OUTERMOST_HEADER_ID == 0x2071)
#  include <stl/_epilog.h>
#  undef __STL_OUTERMOST_HEADER_ID
# endif

#endif /* __STLPORT_STRSTREAM_H */

// Local Variables:
// mode:C++
// End:

