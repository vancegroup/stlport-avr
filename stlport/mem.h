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

// Boris : highly questionable header for BC++

#ifndef __STLPORT_mem_h

# if !defined (__STL_OUTERMOST_HEADER_ID)
#  define __STL_OUTERMOST_HEADER_ID 0x245
#  include <stl/_prolog.h>
# elif (__STL_OUTERMOST_HEADER_ID == 0x245) && ! defined (__STL_DONT_POP_0x245)
#  define __STL_DONT_POP_0x245
# endif

# if (__BORLANDC__ > 0x530) && !defined(__linux__)
#  include <rw/stddefs.h>
# endif

#   undef __USING_CNAME__

#   include __STL_NATIVE_C_HEADER(mem.h)

# define __STLPORT_mem_h 1

# if (__STL_OUTERMOST_HEADER_ID == 0x245)
#  if ! defined (__STL_DONT_POP_0x245)
#   include <stl/_epilog.h>
#   undef  __STL_OUTERMOST_HEADER_ID
#   endif
#   undef  __STL_DONT_POP_0x245
# endif

#endif /* __STLPORT_mem_h */

// #endif /* NATIVE */
// Local Variables:
// mode:C++
// End:

