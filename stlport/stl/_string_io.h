/*
 * Copyright (c) 1997-1999
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

#ifndef __SGI_STL_STRING_IO_H
#define __SGI_STL_STRING_IO_H

// this is for link-time instantiation
#if !defined  ( __STLPORT_STRING )
# include <string>
# endif

# ifdef __STL_DEBUG
#  define basic_string _Nondebug_string
# endif

// I/O.  
__STL_BEGIN_NAMESPACE

#if defined (__STL_USE_NEW_IOSTREAMS)

template <class _CharT, class _Traits, class _Alloc>
basic_ostream<_CharT, _Traits>& __STL_CALL
operator<<(basic_ostream<_CharT, _Traits>& __os, 
           const basic_string<_CharT,_Traits,_Alloc>& __s);

template <class _CharT, class _Traits, class _Alloc>
basic_istream<_CharT, _Traits>&  __STL_CALL
operator>>(basic_istream<_CharT, _Traits>& __is,
           basic_string<_CharT,_Traits,_Alloc>& __s);

template <class _CharT, class _Traits, class _Alloc>    
basic_istream<_CharT, _Traits>& __STL_CALL 
getline(basic_istream<_CharT, _Traits>& __is,
        basic_string<_CharT,_Traits,_Alloc>& __s,
        _CharT __delim);

# if !(defined (__BORLANDC__) && ! defined (__STL_USE_OWN_NAMESPACE))

template <class _CharT, class _Traits, class _Alloc>    
inline basic_istream<_CharT, _Traits>& __STL_CALL 
getline(basic_istream<_CharT, _Traits>& __is,
        basic_string<_CharT,_Traits,_Alloc>& __s)
{
  return getline(__is, __s, __is.widen('\n'));
}
# endif

#if !(defined(__MRC__)||defined(__SC__))		//*TY 02/27/2000 - mpw compilers can not handle complex template arguments
template <class _CharT, class _Traits>
bool __STL_CALL
__sgi_string_fill(basic_ostream<_CharT, _Traits>& __os,
                  basic_streambuf<_CharT, _Traits>* __buf,
                  size_t __n);
#else											//*TY 02/27/2000 - added workaround for MPW compilers
template <class _CharT, class _Traits, class _Buf>		//*TY 02/27/2000 - added _Buf
bool __STL_CALL
__sgi_string_fill(basic_ostream<_CharT, _Traits>& __os,
                  _Buf* __buf,		//*TY 02/27/2000 - simplified parameter type
                  size_t __n);
#endif											//*TY 02/27/2000 - 

#elif ! defined ( __STL_USE_NO_IOSTREAMS )

// (reg) For Watcom IO, this tells if ostream class is in .exe or in .dll
# ifdef _WPRTLINK
typedef _WPRTLINK ostream _OSTREAM_DLL;
typedef _WPRTLINK istream _ISTREAM_DLL;
#else
typedef           ostream _OSTREAM_DLL;
typedef           istream _ISTREAM_DLL;
#endif

template <class _CharT, class _Traits, class _Alloc>
_OSTREAM_DLL& __STL_CALL operator<<(_OSTREAM_DLL& __os, 
                    const basic_string<_CharT,_Traits,_Alloc>& __s);

template <class _CharT, class _Traits, class _Alloc>
_ISTREAM_DLL& __STL_CALL operator>>(_ISTREAM_DLL& __is, basic_string<_CharT,_Traits,_Alloc>& __s);

template <class _CharT, class _Traits, class _Alloc>    
_ISTREAM_DLL& __STL_CALL getline(_ISTREAM_DLL& __is,
                 basic_string<_CharT,_Traits,_Alloc>& __s,
                 _CharT __delim);


template <class _CharT, class _Traits, class _Alloc>    
inline _ISTREAM_DLL& __STL_CALL 
getline(_ISTREAM_DLL& __is, basic_string<_CharT,_Traits,_Alloc>& __s)
{
  return getline(__is, __s, '\n');
}

inline void  __STL_CALL
__sgi_string_fill(_OSTREAM_DLL& __os, streambuf* __buf, size_t __n)
{
  char __f = __os.fill();
  size_t __i;

  for (__i = 0; __i < __n; ++__i) __buf->sputc(__f);
}

#endif /* __STL_USE_NEW_IOSTREAMS */

__STL_END_NAMESPACE

# undef basic_string

# if !defined (__STL_LINK_TIME_INSTANTIATION)
#  include <stl/_string_io.c>
# endif

#endif /* __SGI_STL_STRING_IO_H */
