/*
 *
 * Copyright (c) 1994
 * Hewlett-Packard Company
 *
 * Copyright (c) 1996,1997
 * Silicon Graphics Computer Systems, Inc.
 *
 * Copyright (c) 1997
 * Moscow Center for SPARC Technology
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

#ifndef __SGI_STL_PAIR_H
#define __SGI_STL_PAIR_H

# ifndef __STL_OUTERMOST_HEADER_ID
#  define __STL_OUTERMOST_HEADER_ID 0xa020
#  include <stl/_prolog.h>
# endif

#if defined  (__STL_DEBUG) || defined (__STL_ASSERTIONS) && !defined (__STLPORT_DEBUG_H)
# include <stl/debug/_debug.h>
#endif

#ifndef __SGI_STL_INTERNAL_RELOPS
#include <stl/_relops.h>
#endif

#ifndef __TYPE_TRAITS_H
# include <stl/type_traits.h>
#endif

#ifndef __SGI_STL_INTERNAL_PAIR_H
#  include <stl/_pair.h>
#endif

#ifdef __STL_USE_NAMESPACES

# ifdef __STL_BROKEN_USING_DIRECTIVE
using namespace STLPORT;
# else
using __STLPORT_STD::pair;
using __STLPORT_STD::make_pair;
# endif

#endif /* __STL_USE_NAMESPACES */

# if (__STL_OUTERMOST_HEADER_ID == 0xa020)
#  include <stl/_epilog.h>
#  undef __STL_OUTERMOST_HEADER_ID
# endif

#endif /* __SGI_STL_PAIR_H */

// Local Variables:
// mode:C++
// End:

