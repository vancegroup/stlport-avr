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

#ifndef __STLPORT_IOMANIP_H
# define __STLPORT_IOMANIP_H

# ifndef __STL_OUTERMOST_HEADER_ID
#  define __STL_OUTERMOST_HEADER_ID 0x2031
#  include <stl/_prolog.h>
# endif

# if defined ( __SGI_STL_OWN_IOSTREAMS )

#  include <iomanip>

#  ifndef __STL_HAS_NO_NAMESPACES
#  ifdef __STL_BROKEN_USING_DIRECTIVE
using namespace __STLPORT_STD;
#  else
using __STLPORT_STD::setiosflags;
using __STLPORT_STD::resetiosflags;
using __STLPORT_STD::setbase;
using __STLPORT_STD::setfill;
using __STLPORT_STD::setprecision;
using __STLPORT_STD::setw;
#  endif
#  endif /* __STL_HAS_NO_NAMESPACES */

# elif !defined (__STL_USE_NO_IOSTREAMS)

# include __STL_NATIVE_OLD_STREAMS_HEADER(iomanip.h)

# if defined  (__STL_USE_NAMESPACES) && ! defined (__STL_BROKEN_USING_DIRECTIVE)
__STL_BEGIN_NAMESPACE
# include <using/h/iomanip.h>
__STL_END_NAMESPACE
#  endif /* __STL_USE_NAMESPACES */

# endif

# if (__STL_OUTERMOST_HEADER_ID == 0x2031)
#  include <stl/_epilog.h>
#  undef __STL_OUTERMOST_HEADER_ID
# endif

#endif /* __STLPORT_IOMANIP_H */

// Local Variables:
// mode:C++
// End:
