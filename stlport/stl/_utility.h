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


/* NOTE: This is an internal header file, included by other STL headers.
 *   You should not attempt to use it directly.
 */

#ifndef _STLP_INTERNAL_UTILITY_H
#define _STLP_INTERNAL_UTILITY_H

#if defined (_STLP_CLASS_PARTIAL_SPECIALIZATION)
#  ifndef _STLP_TYPE_TRAITS
#    include <type_traits>
#  endif

#  if !defined (_STLP_MOVE_CONSTRUCT_FWK_H) && !defined (_STLP_NO_MOVE_SEMANTIC)
#    include <stl/_move_construct_fwk.h>
#  endif
#endif

_STLP_BEGIN_NAMESPACE

namespace rel_ops {
} // namespace rel_ops

template <class T>
struct identity
{
    typedef T type;
    const T& operator ()( const T& v ) const
      { return v; }
};

/*
template <class T>
T&& forward( typename identity<T>::type&& t )
{ return t; }
*/

// Well, forward is unuseful without rvalue reference
template <class T>
inline const T& forward( const typename identity<T>::type& t )
{ return t; }

template <class T>
inline T& forward( typename identity<T>::type& t )
{ return t; }

// template <class T>
// inline __move_source<T>& forward( __move_source<typename identity<T>::type>& t )
// { return t; }

/*
template <class T>
typename remove_reference<T>::type&& move( T&& t )
{ return t; }
*/

template <class T>
__move_source<typename remove_const<typename remove_reference<T>::type>::type> move( const T& t )
{ return __move_source<typename remove_const<typename remove_reference<T>::type>::type>( const_cast<T&>(t) ); }

template <class T>
__move_source<typename remove_reference<T>::type> move( T& t )
{ return __move_source<typename remove_reference<T>::type>( t ); }


template <class _T1, class _T2>
struct pair {
  typedef _T1 first_type;
  typedef _T2 second_type;

  _T1 first;
  _T2 second;
#if defined (_STLP_CONST_CONSTRUCTOR_BUG)
  pair() {}
#else
  pair() : first(_T1()), second(_T2()) {}
#endif
  pair(const _T1& __a, const _T2& __b) : first(__a), second(__b) {}

  template <class _U1, class _U2>
  pair(const pair<_U1, _U2>& __p) : first(__p.first), second(__p.second) {}

  pair(const pair<_T1,_T2>& __o) : first(__o.first), second(__o.second) {}

#if defined (_STLP_CLASS_PARTIAL_SPECIALIZATION) && !defined (_STLP_NO_MOVE_SEMANTIC)
  pair(__move_source<pair<_T1, _T2> > src) :
      first(src.get().first),
      second(src.get().second)
    { }
#endif

  __TRIVIAL_DESTRUCTOR(pair)
};

template <class _T1, class _T2>
inline bool _STLP_CALL operator==(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y)
{ return __x.first == __y.first && __x.second == __y.second; }

template <class _T1, class _T2>
inline bool _STLP_CALL operator<(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y) {
  return __x.first < __y.first ||
         (!(__y.first < __x.first) && __x.second < __y.second);
}

#if defined (_STLP_USE_SEPARATE_RELOPS_NAMESPACE)
template <class _T1, class _T2>
inline bool _STLP_CALL operator!=(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y)
{ return !(__x == __y); }

template <class _T1, class _T2>
inline bool _STLP_CALL operator>(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y)
{ return __y < __x; }

template <class _T1, class _T2>
inline bool _STLP_CALL operator<=(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y)
{ return !(__y < __x); }

template <class _T1, class _T2>
inline bool _STLP_CALL operator>=(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y)
{ return !(__x < __y); }
#endif /* _STLP_USE_SEPARATE_RELOPS_NAMESPACE */

#if defined (_STLP_FUNCTION_TMPL_PARTIAL_ORDER) && !defined (_STLP_NO_EXTENSIONS)
template <class _T1, class _T2, int _Sz>
inline pair<_T1, _T2 const*> make_pair(_T1 const& __x,
                                       _T2 const (&__y)[_Sz])
{ return pair<_T1, _T2 const*>(__x, static_cast<_T2 const*>(__y)); }

template <class _T1, class _T2, int _Sz>
inline pair<_T1 const*, _T2> make_pair(_T1 const (&__x)[_Sz],
                                       _T2 const& __y)
{ return pair<_T1 const*, _T2>(static_cast<_T1 const*>(__x), __y); }

template <class _T1, class _T2, int _Sz1, int _Sz2>
inline pair<_T1 const*, _T2 const*> make_pair(_T1 const (&__x)[_Sz1],
                                              _T2 const (&__y)[_Sz2]) {
  return pair<_T1 const*, _T2 const*>(static_cast<_T1 const*>(__x),
                                      static_cast<_T2 const*>(__y));
}
#endif

template <class _T1, class _T2>
inline pair<_T1, _T2> _STLP_CALL make_pair(_T1 __x, _T2 __y)
{ return pair<_T1, _T2>(__x, __y); }

_STLP_END_NAMESPACE

#if defined (_STLP_USE_NAMESPACES) || !defined (_STLP_USE_SEPARATE_RELOPS_NAMESPACE)
_STLP_BEGIN_RELOPS_NAMESPACE

template <class _Tp>
inline bool _STLP_CALL operator!=(const _Tp& __x, const _Tp& __y)
{ return !(__x == __y); }

template <class _Tp>
inline bool _STLP_CALL operator>(const _Tp& __x, const _Tp& __y)
{ return __y < __x; }

template <class _Tp>
inline bool _STLP_CALL operator<=(const _Tp& __x, const _Tp& __y)
{ return !(__y < __x); }

template <class _Tp>
inline bool _STLP_CALL  operator>=(const _Tp& __x, const _Tp& __y)
{ return !(__x < __y); }

_STLP_END_RELOPS_NAMESPACE
#endif

#if defined (_STLP_CLASS_PARTIAL_SPECIALIZATION)
_STLP_BEGIN_NAMESPACE

_STLP_BEGIN_TR1_NAMESPACE

template <class _T1, class _T2>
struct has_trivial_default_constructor<pair<_T1, _T2> > :
    public integral_constant<bool, has_trivial_default_constructor<_T1>::value && has_trivial_default_constructor<_T2>::value>
{ };

template <class _T1, class _T2>
struct has_trivial_copy_constructor<pair<_T1, _T2> > :
    public integral_constant<bool, has_trivial_copy_constructor<_T1>::value && has_trivial_copy_constructor<_T2>::value>
{ };

template <class _T1, class _T2>
struct has_trivial_assign<pair<_T1, _T2> > :
    public integral_constant<bool, has_trivial_assign<_T1>::value && has_trivial_assign<_T2>::value>
{ };

template <class _T1, class _T2>
struct has_trivial_destructor<pair<_T1, _T2> > :
    public integral_constant<bool, has_trivial_destructor<_T1>::value && has_trivial_destructor<_T2>::value>
{ };

_STLP_END_NAMESPACE

#  if !defined (_STLP_NO_MOVE_SEMANTIC)

_STLP_BEGIN_TR1_NAMESPACE

template <class _T1, class _T2>
struct __has_trivial_move<pair<_T1, _T2> > :
   public integral_constant<bool, __has_trivial_move<_T1>::value && __has_trivial_move<_T2>::value>
{ };

template <class _T1, class _T2>
struct __has_move_constructor<pair<_T1, _T2> > :
    public integral_constant<bool, __has_move_constructor<_T1>::value && __has_move_constructor<_T2>::value>
{ };

_STLP_END_NAMESPACE

#  endif

_STLP_END_NAMESPACE
#endif

#endif /* _STLP_INTERNAL_UTILITY_H */

// Local Variables:
// mode:C++
// End:
