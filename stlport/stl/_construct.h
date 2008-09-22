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

#ifndef _STLP_INTERNAL_CONSTRUCT_H
#define _STLP_INTERNAL_CONSTRUCT_H

#if !defined (_STLP_DEBUG_UNINITIALIZED) && !defined (_STLP_INTERNAL_CSTRING)
#  include <stl/_cstring.h>
#endif

#ifndef _STLP_INTERNAL_NEW
#  include <stl/_new.h>
#endif

#ifndef _STLP_INTERNAL_ITERATOR_BASE_H
#  include <stl/_iterator_base.h>
#endif

#ifndef _STLP_TYPE_TRAITS
#  include <type_traits>
#endif

#if !defined (_STLP_MOVE_CONSTRUCT_FWK_H) && !defined (_STLP_NO_MOVE_SEMANTIC)
#  include <stl/_move_construct_fwk.h>
#endif

_STLP_BEGIN_NAMESPACE

template <class _Tp>
inline void __destroy_aux(_Tp* __pointer, const false_type& /*_Trivial_destructor*/)
{ __pointer->~_Tp(); }

template <class _Tp>
inline void __destroy_aux(_Tp*, const true_type& /*_Trivial_destructor*/)
{ }

template <class _Tp>
inline void _Destroy(_Tp* __pointer)
{
  __destroy_aux(__pointer, typename has_trivial_destructor<_Tp>::type() );
#if defined (_STLP_DEBUG_UNINITIALIZED)
  memset(__REINTERPRET_CAST(char*, __pointer), _STLP_SHRED_BYTE, sizeof(_Tp));
#endif
}

template <class _Tp>
inline void _Destroy_Moved(_Tp* __pointer) {
#if !defined (_STLP_NO_MOVE_SEMANTIC)
  __destroy_aux(__pointer, typename __has_trivial_move<_Tp>::type() );
#  if defined (_STLP_DEBUG_UNINITIALIZED)
  memset((char*)__pointer, _STLP_SHRED_BYTE, sizeof(_Tp));
#  endif
#else
  _Destroy(__pointer);
#endif
}

#if defined (new)
#  define _STLP_NEW_REDEFINE new
#  undef new
#endif

template <class _T1>
inline void _Construct_aux (_T1* __p, const false_type&) {
  new(__p) _T1();
}

template <class _T1>
inline void _Construct_aux (_T1* __p, const true_type&) {
#if defined (_STLP_DEF_CONST_PLCT_NEW_BUG)
  *__p = _T1(0);
#else
  // We use binary copying for POD types since it results
  // in a considerably better code at least on MSVC.
  *__p = _T1();
#endif /* _STLP_DEF_CONST_PLCT_NEW_BUG */
}

template <class _T1>
inline void _Construct(_T1* __p) {
#if defined (_STLP_DEBUG_UNINITIALIZED)
  memset((char*)__p, _STLP_SHRED_BYTE, sizeof(_T1));
#endif
  _Construct_aux (__p, typename is_fundamental<_T1>::type() );
}

template <class _Tp>
inline void _Copy_Construct_aux( _Tp* __p, const _Tp& __val, const false_type& /* is_fundamental */ )
{
  new(__p) _Tp(__val);
}

template <class _Tp>
inline void _Copy_Construct_aux( _Tp* __p, const _Tp& __val, const true_type& /* is_fundamental */ )
{
  // We use binary copying for POD types since it results
  // in a considerably better code at least on MSVC.
  *__p = __val;
}

template <class _Tp>
inline void _Copy_Construct(_Tp* __p, const _Tp& __val)
{
#if defined (_STLP_DEBUG_UNINITIALIZED)
  memset((char*)__p, _STLP_SHRED_BYTE, sizeof(_Tp));
#endif
  _Copy_Construct_aux(__p, __val, typename is_fundamental<_Tp>::type() );
}

template <class _T1, class _T2>
inline void _Param_Construct_aux(_T1* __p, const _T2& __val, const false_type& /* is_fundamental */ )
{
  new(__p) _T1(__val);
}

template <class _T1, class _T2>
inline void _Param_Construct_aux(_T1* __p, const _T2& __val, const true_type& /* is_fundamental */ )
{
  // We use binary copying for POD types since it results
  // in a considerably better code at least on MSVC.
  *__p = _T1(__val);
}

template <class _T1, class _T2>
inline void _Param_Construct(_T1* __p, const _T2& __val)
{
#if defined (_STLP_DEBUG_UNINITIALIZED)
  memset((char*)__p, _STLP_SHRED_BYTE, sizeof(_T1));
#endif
  _Param_Construct_aux(__p, __val, typename is_fundamental<_T1>::type() );
}

template <class _T1, class _T2>
inline void _Move_Construct_Aux2(_T1* __p, _T2& __val, const false_type& /* move ctor */)
{ new(__p) _T1(__val); }

template <class _T1, class _T2>
inline void _Move_Construct_Aux2(_T1* __p, _T2& __val, const true_type& /* move ctor */)
{ new(__p) _T1( move( __val ) ); }

template <class _T1, class _T2>
inline void _Move_Construct_Aux(_T1* __p, _T2& __val, const false_type& /* is_fundamental */)
{ _Move_Construct_Aux2( __p, __val, integral_constant<bool,is_same<_T1,_T2>::value &&  __has_move_constructor<_T1>::value>() ); }

template <class _T1, class _T2>
inline void _Move_Construct_Aux(_T1* __p, _T2& __val, const true_type& /* is_fundamental */)
{
  // We use binary copying for POD types since it results
  // in a considerably better code at least on MSVC.
  *__p = _T1(__val);
}

template <class _T1, class _T2>
inline void _Move_Construct(_T1* __p, _T2& __val)
{
#if defined (_STLP_DEBUG_UNINITIALIZED)
  memset((char*)__p, _STLP_SHRED_BYTE, sizeof(_T1));
#endif
  _Move_Construct_Aux(__p, __val, typename is_fundamental<_T1>::type() );
}

#if defined(_STLP_NEW_REDEFINE)
#  if defined (DEBUG_NEW)
#    define new DEBUG_NEW
#  endif
#  undef _STLP_NEW_REDEFINE
#endif

template <class _ForwardIterator, class _Tp>
_STLP_INLINE_LOOP void
__destroy_range_aux(_ForwardIterator __first, _ForwardIterator __last, _Tp*, const false_type& /*_Trivial_destructor*/) {
  for ( ; __first != __last; ++__first) {
    __destroy_aux(&(*__first), false_type());
#if defined (_STLP_DEBUG_UNINITIALIZED)
    memset((char*)&(*__first), _STLP_SHRED_BYTE, sizeof(_Tp));
#endif
  }
}

template <class _ForwardIterator, class _Tp>
#if defined (_STLP_DEBUG_UNINITIALIZED)
_STLP_INLINE_LOOP void __destroy_range_aux( _ForwardIterator __first, _ForwardIterator __last,
                                            _Tp*, const true_type& /*_Trivial_destructor*/)
{
  for ( ; __first != __last; ++__first) {
    memset((char*)&(*__first), _STLP_SHRED_BYTE, sizeof(_Tp));
  }
}
#else
inline void __destroy_range_aux( _ForwardIterator, _ForwardIterator, _Tp*,
                                 const true_type& /*_Trivial_destructor*/)
{ }
#endif

template <class _ForwardIterator, class _Tp>
inline void __destroy_range( _ForwardIterator __first, _ForwardIterator __last, _Tp *__ptr )
{
  typedef typename has_trivial_destructor<_Tp>::type _Trivial_destructor;
  __destroy_range_aux(__first, __last, __ptr, _Trivial_destructor());
}

template <class _ForwardIterator>
inline void _Destroy_Range(_ForwardIterator __first, _ForwardIterator __last)
{
  __destroy_range(__first, __last, _STLP_VALUE_TYPE(__first, _ForwardIterator));
}

inline void _Destroy_Range(char*, char*) {}
#if defined (_STLP_HAS_WCHAR_T) // dwa 8/15/97
inline void _Destroy_Range(wchar_t*, wchar_t*) {}
inline void _Destroy_Range(const wchar_t*, const wchar_t*) {}
#endif

#if !defined (_STLP_NO_MOVE_SEMANTIC)
template <class _ForwardIterator, class _Tp>
inline void __destroy_mv_srcs(_ForwardIterator __first, _ForwardIterator __last, _Tp *__ptr)
{
  __destroy_range_aux(__first, __last, __ptr, integral_constant<bool, __has_trivial_move<_Tp>::value>() );
}
#endif

template <class _ForwardIterator>
inline void _Destroy_Moved_Range(_ForwardIterator __first, _ForwardIterator __last)
#if !defined (_STLP_NO_MOVE_SEMANTIC)
{ __destroy_mv_srcs(__first, __last, _STLP_VALUE_TYPE(__first, _ForwardIterator)); }
#else
{ _Destroy_Range(__first, __last); }
#endif

#if defined (_STLP_DEF_CONST_DEF_PARAM_BUG)
// Those adaptors are here to fix common compiler bug regarding builtins:
// expressions like int k = int() should initialize k to 0
template <class _Tp>
inline _Tp __default_constructed_aux(_Tp*, const false_type&) {
  return _Tp();
}
template <class _Tp>
inline _Tp __default_constructed_aux(_Tp*, const true_type&) {
  return _Tp(0);
}

template <class _Tp>
inline _Tp __default_constructed(_Tp* __p) {
  return __default_constructed_aux(__p, _HasDefaultZeroValue(__p)._Answer());
}

#  define _STLP_DEFAULT_CONSTRUCTED(_TTp) __default_constructed((_TTp*)0)
#else
#  define _STLP_DEFAULT_CONSTRUCTED(_TTp) _TTp()
#endif /* _STLP_DEF_CONST_DEF_PARAM_BUG */


#if !defined (_STLP_NO_ANACHRONISMS)
// --------------------------------------------------
// Old names from the HP STL.

template <class _T1, class _T2>
inline void construct(_T1* __p, const _T2& __val) {_Param_Construct(__p, __val); }
template <class _T1>
inline void construct(_T1* __p) { _STLP_STD::_Construct(__p); }
template <class _Tp>
inline void destroy(_Tp* __pointer) {  _STLP_STD::_Destroy(__pointer); }
template <class _ForwardIterator>
inline void destroy(_ForwardIterator __first, _ForwardIterator __last) { _STLP_STD::_Destroy_Range(__first, __last); }
#endif /* _STLP_NO_ANACHRONISMS */

_STLP_END_NAMESPACE

#endif /* _STLP_INTERNAL_CONSTRUCT_H */

// Local Variables:
// mode:C++
// End:
