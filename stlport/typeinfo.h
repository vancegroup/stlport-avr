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

#ifndef __STLPORT_OLDSTD_typeinfo
# define __STLPORT_OLDSTD_typeinfo

# ifndef __STL_OUTERMOST_HEADER_ID
#  define __STL_OUTERMOST_HEADER_ID 0x874
#  include <stl/_prolog.h>
# endif

# ifndef __STL_NO_TYPEINFO

#if defined (__GNUC__)
# undef __STLPORT_OLDSTD_typeinfo
#  include <typeinfo>
# define __STLPORT_OLDSTD_typeinfo
#else
#  include __STL_NATIVE_CPP_RUNTIME_HEADER(typeinfo.h)
#endif

// if <typeinfo> already included, do not import anything
# if defined  (__STL_USE_OWN_NAMESPACE) && ! defined (__STLPORT_TYPEINFO)

__STL_BEGIN_NAMESPACE

using /*__STL_VENDOR_EXCEPT_STD */ :: type_info;
using __STL_VENDOR_EXCEPT_STD :: bad_typeid;
using __STL_VENDOR_EXCEPT_STD :: bad_cast;

__STL_END_NAMESPACE

#endif /* __STL_OWN_NAMESPACE */

# endif /* __STL_NO_TYPEINFO */

# if (__STL_OUTERMOST_HEADER_ID == 0x874)
#  include <stl/_epilog.h>
#  undef __STL_OUTERMOST_HEADER_ID
# endif

#endif /* __STLPORT_OLDSTD_typeinfo */

// Local Variables:
// mode:C++
// End:
