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

#ifndef __SGI_STL_ITERATOR_H
#define __SGI_STL_ITERATOR_H

# ifndef __STL_OUTERMOST_HEADER_ID
#  define __STL_OUTERMOST_HEADER_ID 0xa013
#  include <stl/_prolog.h>
# endif

#if defined  (__STL_DEBUG) || defined (__STL_ASSERTIONS) && !defined (__STLPORT_DEBUG_H)
# include <stl/debug/_debug.h>
#endif

#if defined (__STL_USE_NEW_STYLE_HEADERS)
# include <cstddef>
#else
# include <stddef.h>
#endif

# ifndef __STLPORT_NEW
#  include <new>
# endif

# ifndef __TYPE_TRAITS_H
#  include <stl/type_traits.h>
# endif

#ifndef __SGI_STL_FUNCTION_H
#include <function.h>
#endif

# ifndef __STLPORT_IOSFWD
#  include <iosfwd>
# endif

# ifndef __SGI_STL_INTERNAL_ITERATOR_BASE_H
#  include <stl/_iterator_base.h>
# endif

# ifndef __SGI_STL_INTERNAL_ITERATOR_H
#  include <stl/_iterator.h>
# endif

#ifndef __SGI_STL_INTERNAL_CONSTRUCT_H
#include <stl/_construct.h>
#endif

#ifndef __SGI_STL_INTERNAL_RAW_STORAGE_ITERATOR_H
#include <stl/_raw_storage_iter.h>
#endif

# ifndef __SGI_STL_INTERNAL_STREAM_ITERATOR_H
#  include <stl/_stream_iterator.h>
# endif

#ifdef __STL_USE_NAMESPACES


# if 0 // defined (__STL_USE_OWN_NAMESPACE) && defined (__STL_IMPORT_VENDOR_STD) && !defined (__STL_BROKEN_USING_DIRECTIVE)

__STL_BEGIN_NAMESPACE

using __STL_VENDOR_STD::istream_iterator;
using __STL_VENDOR_STD::ostream_iterator;

__STL_END_NAMESPACE

# endif

// Names from stl_iterator.h

# ifdef __STL_BROKEN_USING_DIRECTIVE
using namespace STLPORT;
# else

using STLPORT::input_iterator_tag;
using STLPORT::output_iterator_tag;
using STLPORT::forward_iterator_tag;
using STLPORT::bidirectional_iterator_tag;
using STLPORT::random_access_iterator_tag;

using STLPORT::input_iterator;
using STLPORT::output_iterator;
using STLPORT::forward_iterator;
using STLPORT::bidirectional_iterator;
using STLPORT::random_access_iterator;

#ifdef __STL_CLASS_PARTIAL_SPECIALIZATION
using STLPORT::iterator_traits;
#endif

# ifdef __STL_USE_OLD_HP_ITERATOR_QUERIES
using STLPORT::iterator_category;
using STLPORT::distance_type;
using STLPORT::value_type;
# endif

using STLPORT::distance; 
using STLPORT::advance; 

using STLPORT::insert_iterator;
using STLPORT::front_insert_iterator;
using STLPORT::back_insert_iterator;
using STLPORT::inserter;
using STLPORT::front_inserter;
using STLPORT::back_inserter;

using STLPORT::reverse_iterator;
using STLPORT::reverse_bidirectional_iterator;

using STLPORT::istream_iterator;
using STLPORT::ostream_iterator;

// Names from stl_construct.h
using STLPORT::construct;
using STLPORT::destroy;

// Names from stl_raw_storage_iter.h
using STLPORT::raw_storage_iterator;
# endif

#endif /* __STL_USE_NAMESPACES */

# if (__STL_OUTERMOST_HEADER_ID == 0xa013)
#  include <stl/_epilog.h>
#  undef __STL_OUTERMOST_HEADER_ID
# endif

#endif /* __SGI_STL_ITERATOR_H */

// Local Variables:
// mode:C++
// End:

