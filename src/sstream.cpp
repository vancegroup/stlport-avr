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
# include "stlport_prefix.h"
#include <stl/_sstream.h>

__STL_BEGIN_NAMESPACE

# ifndef __STL_NO_FORCE_INSTANTIATE

// Force instantiation of stringstream classes.

template class __STL_CLASS_DECLSPEC basic_stringbuf<char, char_traits<char>, allocator<char> >;
template class __STL_CLASS_DECLSPEC basic_ostringstream<char, char_traits<char>, allocator<char> >;
template class __STL_CLASS_DECLSPEC basic_istringstream<char, char_traits<char>, allocator<char> >;
template class __STL_CLASS_DECLSPEC basic_stringstream<char, char_traits<char>, allocator<char> >;

#ifndef __STL_NO_WCHAR_T
template class __STL_CLASS_DECLSPEC basic_stringbuf<wchar_t, char_traits<wchar_t>, allocator<wchar_t> >;
template class __STL_CLASS_DECLSPEC basic_ostringstream<wchar_t, char_traits<wchar_t>, allocator<wchar_t> >;
template class __STL_CLASS_DECLSPEC basic_istringstream<wchar_t, char_traits<wchar_t>, allocator<wchar_t> >;
template class __STL_CLASS_DECLSPEC basic_stringstream<wchar_t, char_traits<wchar_t>, allocator<wchar_t> >;
#endif /* INSTANTIATE_WIDE_STREAMS */

# endif


__STL_END_NAMESPACE

// Local Variables:
// mode:C++
// End:
