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

#include "stlport_prefix.h"

#ifdef _STLP_USE_UNIX_IO
# include "fstream_unistd.cpp"
#elif defined(_STLP_USE_STDIO_IO)
# include "fstream_stdio.cpp"
#elif defined(_STLP_USE_WIN32_IO)
# include "fstream_win32io.cpp"
#else
#  error "Can't recognize IO scheme to use"
#endif

_STLP_BEGIN_NAMESPACE

//----------------------------------------------------------------------
// Force instantiation of filebuf and fstream classes.
#if !defined(_STLP_NO_FORCE_INSTANTIATE)

template class basic_filebuf<char, char_traits<char> >;
template class basic_ifstream<char, char_traits<char> >;
template class basic_ofstream<char, char_traits<char> >;
template class basic_fstream<char, char_traits<char> >;

#  if !defined (_STLP_NO_WCHAR_T)
template class _Underflow<wchar_t, char_traits<wchar_t> >;
template class basic_filebuf<wchar_t, char_traits<wchar_t> >;
template class basic_ifstream<wchar_t, char_traits<wchar_t> >;
template class basic_ofstream<wchar_t, char_traits<wchar_t> >;
template class basic_fstream<wchar_t, char_traits<wchar_t> >;
#  endif /* _STLP_NO_WCHAR_T */

#endif

_STLP_END_NAMESPACE
