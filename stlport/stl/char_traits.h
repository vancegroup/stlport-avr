/*
 * Copyright (c) 1996,1997
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

#ifndef __SGI_STL_CHAR_TRAITS_H
#define __SGI_STL_CHAR_TRAITS_H


// Define char_traits

# if defined (__SGI_STL_OWN_IOSTREAMS) || ! defined (__STL_USE_NEW_IOSTREAMS)

# if ! defined (__STLPORT_CSTDDEF)
#  include <cstddef>
# endif

# if defined (__STL_HAS_WCHAR_T) && !defined (__STLPORT_CWCHAR)
#  include <cwchar>
# endif			

#if ! defined (__STLPORT_CSTRING)
#  include <cstring>
#endif

#ifndef __TYPE_TRAITS_H
# include <stl/type_traits.h>
#endif

#if defined (__STL_UNIX) && defined (__STL_HAS_NO_NEW_C_HEADERS)
#include <sys/types.h>          // For off_t
#endif /* __unix */

__STL_BEGIN_NAMESPACE

# ifdef __SGI_STL_OWN_IOSTREAMS

template <class _Tp> class allocator;

#define __STL_NULL_CHAR_INIT(_ChT) __STL_DEFAULT_CONSTRUCTED(_ChT)

// template <class _CharT> class char_traits;

#if defined (__sgi) && defined (__STL_HAS_NO_NEW_C_HEADERS) /* IRIX */
typedef off64_t   streamoff;
#elif defined (__unix) && defined (__STL_HAS_NO_NEW_C_HEADERS) /* Other version of UNIX */
typedef off_t     streamoff;
#else /* __unix */
typedef ptrdiff_t streamoff;
#endif /* __STL_HAS_NO_NEW_C_HEADERS */

typedef ptrdiff_t streamsize;

// dwa 12/22/99 - gcc 2.95.2 bug workaround
#ifdef __GNUC__
template <class _StateT> class fpos;
template <class _StateT>
inline bool  __STL_CALL operator==(const fpos<_StateT>& __x, const fpos<_StateT>& __y)
    { return __x._M_pos == __y._M_pos; }
template <class _StateT>
inline bool  __STL_CALL operator!=(const fpos<_StateT>& __x, const fpos<_StateT>& __y)
    { return __x._M_pos != __y._M_pos; }
#endif

// Class fpos, which represents a position within a file.  (The C++
// standard calls for it to be defined in <ios>.  This implementation
// moves it to <iosfwd>, which is included by <ios>.)
template <class _StateT> class fpos
{
public:                         // From table 88 of the C++ standard.
  fpos(streamoff __pos) : _M_pos(__pos), _M_st(__STL_NULL_CHAR_INIT(_StateT)) {}
  fpos() : _M_pos(0), _M_st(__STL_NULL_CHAR_INIT(_StateT)) {}

  operator streamoff() const { return _M_pos; }

// dwa 12/22/99 - gcc 2.95.2 bug workaround
#ifdef __GNUC__
  friend bool operator==<>(const fpos<_StateT>& __x, const fpos<_StateT>& __y);
  friend bool operator!=<>(const fpos<_StateT>& __x, const fpos<_StateT>& __y);
#else
  friend bool  __STL_CALL operator==(const fpos<_StateT>& __x, const fpos<_StateT>& __y)
    { return __x._M_pos == __y._M_pos; }
  friend bool __STL_CALL operator!=(const fpos<_StateT>& __x, const fpos<_StateT>& __y)
    { return __x._M_pos != __y._M_pos; }
#endif
  fpos<_StateT>& operator+=(streamoff __off) {
    _M_pos += __off;
    return *this;
  }
  fpos<_StateT>& operator-=(streamoff __off) {
    _M_pos -= __off;
    return *this;
  }

  fpos<_StateT> operator+(streamoff __off) {
    fpos<_StateT> __tmp(*this);
    __tmp += __off;
    return __tmp;
  }
  fpos<_StateT> operator-(streamoff __off) {
    fpos<_StateT> __tmp(*this);
    __tmp -= __off;
    return __tmp;
  }

public:                         // Manipulation of the state member.
  _StateT state() const { return _M_st; }
  void state(_StateT __st) { _M_st = __st; }
private:
  streamoff _M_pos;
  _StateT _M_st;
};

typedef fpos<mbstate_t> streampos;
typedef fpos<mbstate_t> wstreampos;
# endif

// Class __char_traits_base.

template <class _CharT, class _IntT> class __char_traits_base {
public:
  typedef _CharT char_type;
  typedef _IntT int_type;
#ifdef __STL_USE_NEW_IOSTREAMS
  typedef streamoff off_type;
  typedef streampos pos_type;
# ifdef __STL_NO_MBSTATE_T
  typedef char      state_type;
# else
  typedef mbstate_t state_type;
# endif
#endif /* __STL_USE_NEW_IOSTREAMS */

  static void __STL_CALL assign(char_type& __c1, const char_type& __c2) { __c1 = __c2; }
  static bool __STL_CALL eq(const _CharT& __c1, const _CharT& __c2) 
    { return __c1 == __c2; }
  static bool __STL_CALL lt(const _CharT& __c1, const _CharT& __c2) 
    { return __c1 < __c2; }

  static int __STL_CALL compare(const _CharT* __s1, const _CharT* __s2, size_t __n) {
    for (size_t __i = 0; __i < __n; ++__i)
      if (!eq(__s1[__i], __s2[__i]))
        return __s1[__i] < __s2[__i] ? -1 : 1;
    return 0;
  }

  static size_t __STL_CALL length(const _CharT* __s) {
    const _CharT _NullChar = __STL_DEFAULT_CONSTRUCTED(_CharT);
    size_t __i;
    for (__i = 0; !eq(__s[__i], _NullChar); ++__i)
      {}
    return __i;
  }

  static const _CharT* __STL_CALL find(const _CharT* __s, size_t __n, const _CharT& __c) {
    for ( ; __n > 0 ; ++__s, --__n)
      if (eq(*__s, __c))
        return __s;
    return 0;
  }


  static _CharT* __STL_CALL move(_CharT* __s1, const _CharT* __s2, size_t _Sz) {    
    return (_Sz == 0 ? __s1 : (_CharT*)memmove(__s1, __s2, _Sz * sizeof(_CharT)));
  }
  
  static _CharT* __STL_CALL copy(_CharT* __s1, const _CharT* __s2, size_t __n) {
    return (__n == 0 ? __s1 :
	    (_CharT*)memcpy(__s1, __s2, __n * sizeof(_CharT)));
    } 

  static _CharT* __STL_CALL assign(_CharT* __s, size_t __n, _CharT __c) {
    for (size_t __i = 0; __i < __n; ++__i)
      __s[__i] = __c;
    return __s;
  }

  static int_type __STL_CALL not_eof(const int_type& __c) {
    return !eq_int_type(__c, eof()) ? __c : 0;
  }

  static char_type __STL_CALL to_char_type(const int_type& __c) {
    return (char_type)__c;
  }

  static int_type __STL_CALL to_int_type(const char_type& __c) {
    return (int_type)__c;
  }

  static bool __STL_CALL eq_int_type(const int_type& __c1, const int_type& __c2) {
    return __c1 == __c2;
  }

  static int_type __STL_CALL eof() {
    return (int_type)-1;
    //    return __STATIC_CAST(int_type,-1);
  }
};

// Generic char_traits class.  Note that this class is provided only
//  as a base for explicit specialization; it is unlikely to be useful
//  as is for any particular user-defined type.  In particular, it 
//  *will not work* for a non-POD type.

template <class _CharT> class char_traits
  : public __char_traits_base<_CharT, _CharT>
{};

// Specialization for char.

__STL_TEMPLATE_NULL class __STL_CLASS_DECLSPEC char_traits<char> 
  : public __char_traits_base<char, int>
{
public:
  typedef char char_type;
  typedef int int_type;
#ifdef __STL_USE_NEW_IOSTREAMS
  typedef streamoff off_type;
# ifndef __STL_NO_MBSTATE_T
  typedef streampos pos_type;
  typedef mbstate_t state_type;
# endif
#endif /* __STL_USE_NEW_IOSTREAMS */

  static char __STL_CALL to_char_type(const int& __c) {
    return (char)(unsigned char)__c;
  }

  static int __STL_CALL to_int_type(const char& __c) {
    return (unsigned char)__c;
  }

  static int __STL_CALL compare(const char* __s1, const char* __s2, size_t __n) 
    { return memcmp(__s1, __s2, __n); }
  
  static size_t __STL_CALL length(const char* __s) { return strlen(__s); }

  static void __STL_CALL assign(char& __c1, const char& __c2) { __c1 = __c2; }

  static char* __STL_CALL assign(char* __s, size_t __n, char __c)
    { memset(__s, __c, __n); return __s; }
};

# if defined (__STL_HAS_WCHAR_T)
// Specialization for wchar_t.
__STL_TEMPLATE_NULL class __STL_CLASS_DECLSPEC char_traits<wchar_t>
  : public __char_traits_base<wchar_t, wint_t>
{};
# endif

__STL_END_NAMESPACE

# else /* OWN_IOSTREAMS */

#  include <wrap_std/iosfwd>

# endif /* OWN_IOSTREAMS */

#endif /* __SGI_STL_CHAR_TRAITS_H */

// Local Variables:
// mode:C++
// End:

