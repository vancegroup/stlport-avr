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
// #include <iterator>
#include <complex>
#include <istream>


__STL_BEGIN_NAMESPACE

// Force instantiation of complex I/O functions

#if !(defined (__STL_NO_FORCE_INSTANTIATE) || defined (__STL_NO_WCHAR_T))

#if defined(__MRC__)||defined(__SC__)							//*TY 04/29/2000 - added workaround for mpw
template class basic_istream<wchar_t, char_traits<wchar_t> >;	//*TY 04/29/2000 - they confuse on the nested class sentry of basic_istream if the class is not instantiated before it is used.
template class basic_ostream<wchar_t, char_traits<wchar_t> >;	//*TY 04/29/2000 - 
#endif															//*TY 04/29/2000 - 

__STL_OPERATOR_SPEC basic_istream<wchar_t, char_traits<wchar_t> >&  __STL_CALL
operator>>(basic_istream<wchar_t, char_traits<wchar_t> >&, complex<float>&);

__STL_OPERATOR_SPEC basic_istream<wchar_t, char_traits<wchar_t> >&  __STL_CALL
operator>>(basic_istream<wchar_t, char_traits<wchar_t> >&, complex<double>&);

__STL_OPERATOR_SPEC basic_istream<wchar_t, char_traits<wchar_t> >&  __STL_CALL
operator>>(basic_istream<wchar_t, char_traits<wchar_t> >&, complex<long double>&);

__STL_OPERATOR_SPEC basic_ostream<wchar_t, char_traits<wchar_t> >&  __STL_CALL
operator<<(basic_ostream<wchar_t, char_traits<wchar_t> >&, const complex<float>&);

__STL_OPERATOR_SPEC basic_ostream<wchar_t, char_traits<wchar_t> >&  __STL_CALL
operator<<(basic_ostream<wchar_t, char_traits<wchar_t> >&, const complex<double>&);

__STL_OPERATOR_SPEC basic_ostream<wchar_t, char_traits<wchar_t> >&  __STL_CALL
operator<<(basic_ostream<wchar_t, char_traits<wchar_t> >&, const complex<long double>&);

# endif /* __STL_NO_WCHAR_T */

__STL_END_NAMESPACE

// Local Variables:
// mode:C++
// End:
