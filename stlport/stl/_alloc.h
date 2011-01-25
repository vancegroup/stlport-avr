/*
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

#ifndef _STLP_INTERNAL_ALLOC_H
#define _STLP_INTERNAL_ALLOC_H

#include <stdint.h>

#ifndef _STLP_INTERNAL_CSTDDEF
#  include <stl/_cstddef.h>
#endif

#ifndef _STLP_INTERNAL_CSTDLIB
#  include <stl/_cstdlib.h>
#endif

#ifndef _STLP_CSTRING
#  include <cstring>
#endif

#ifndef _STLP_INTERNAL_NEW_HEADER
#  include <stl/_new.h>
#endif

#ifndef __STLP_TYPE_TRAITS
#  include <type_traits>
#endif

#ifndef _STLP_UTILITY
#  include <utility>
#endif

#ifndef _STLP_INTERNAL_ITERATOR_BASE_H
#  include <stl/_iterator_base.h>
#endif

_STLP_BEGIN_NAMESPACE

template <class _Tp>
inline void __destroy_aux(_Tp* __pointer, const false_type& /*_Trivial_destructor*/)
{ __pointer->~_Tp(); }

template <class _Tp>
inline void __destroy_aux(_Tp*, const true_type& /*_Trivial_destructor*/)
{ }

template <class _Tp>
inline void _Destroy( _Tp* __pointer )
{
  __destroy_aux(__pointer, typename has_trivial_destructor<_Tp>::type() );
#if defined (_STLP_DEBUG_UNINITIALIZED)
  memset( __REINTERPRET_CAST(char*, __pointer), _STLP_SHRED_BYTE, sizeof(_Tp) );
#endif
}

template <class _Tp>
inline void _Destroy_Moved( _Tp* __pointer )
{
#if !defined (_STLP_NO_MOVE_SEMANTIC)
  __destroy_aux( __pointer, typename __has_trivial_move<_Tp>::type() );
#  if defined (_STLP_DEBUG_UNINITIALIZED)
  memset( (char*)__pointer, _STLP_SHRED_BYTE, sizeof(_Tp) );
#  endif
#else
  _Destroy( __pointer );
#endif
}

#if defined (new)
#  define _STLP_NEW_REDEFINE new
#  undef new
#endif

template <class _T1>
inline void _Construct_aux( _T1* __p, const false_type& )
{ new(__p) _T1(); }

template <class _T1>
inline void _Construct_aux( _T1* __p, const true_type& )
{
#if defined (_STLP_DEF_CONST_PLCT_NEW_BUG)
  *__p = _T1(0);
#else
  // We use binary copying for POD types since it results
  // in a considerably better code at least on MSVC.
  *__p = _T1();
#endif /* _STLP_DEF_CONST_PLCT_NEW_BUG */
}

template <class _T1>
inline void _Construct( _T1* __p )
{
#if defined (_STLP_DEBUG_UNINITIALIZED)
  memset((char*)__p, _STLP_SHRED_BYTE, sizeof(_T1));
#endif
  _Construct_aux( __p, typename is_fundamental<_T1>::type() );
}

template <class T1, class T2>
inline void _Copy_Construct_aux( T1* __p, const T2& __val, const false_type& /* is_fundamental */ )
{
  new(__p) T1(__val);
}

template <class T1, class T2>
inline void _Copy_Construct_aux( T1* __p, const T2& __val, const true_type& /* is_fundamental */ )
{
  // We use binary copying for POD types since it results
  // in a considerably better code at least on MSVC.
  *__p = __val;
}

template <class T1, class T2>
inline void _Copy_Construct( T1* __p, const T2& __val )
{
#if defined (_STLP_DEBUG_UNINITIALIZED)
  memset((char*)__p, _STLP_SHRED_BYTE, sizeof(T1));
#endif
  _Copy_Construct_aux( __p, __val, integral_constant<bool,is_fundamental<T1>::value && is_fundamental<T2>::value>() );
}

template <class _T1, class _T2>
inline void _Move_Construct_Aux2( _T1* __p, _T2& __val, const false_type& /* move ctor */)
{ new(__p) _T1(__val); }

template <class _T1, class _T2>
inline void _Move_Construct_Aux2( _T1* __p, _T2& __val, const true_type& /* move ctor */)
{ new(__p) _T1( move( __val ) ); }

template <class _T1, class _T2>
inline void _Move_Construct_Aux( _T1* __p, _T2& __val, const false_type& /* is_fundamental */)
{ _Move_Construct_Aux2( __p, __val, integral_constant<bool,is_same<_T1,_T2>::value &&  __has_move_constructor<_T1>::value>() ); }

template <class _T1, class _T2>
inline void _Move_Construct_Aux(_T1* __p, _T2& __val, const true_type& /* is_fundamental */)
{
  // We use binary copying for POD types since it results
  // in a considerably better code at least on MSVC.
  *__p = _T1(__val);
}

template <class _T1, class _T2>
inline void _Move_Construct( _T1* __p, _T2& __val )
{
#if defined (_STLP_DEBUG_UNINITIALIZED)
  memset( (char*)__p, _STLP_SHRED_BYTE, sizeof(_T1) );
#endif
  _Move_Construct_Aux( __p, __val, typename is_fundamental<_T1>::type() );
}

#if defined(_STLP_NEW_REDEFINE)
#  if defined (DEBUG_NEW)
#    define new DEBUG_NEW
#  endif
#  undef _STLP_NEW_REDEFINE
#endif

template <class _ForwardIterator, class _Tp>
inline void __destroy_range_aux( _ForwardIterator __first, _ForwardIterator __last, _Tp*, const false_type& /*_Trivial_destructor*/)
{
  for ( ; __first != __last; ++__first ) {
    __destroy_aux(&(*__first), false_type());
#if defined (_STLP_DEBUG_UNINITIALIZED)
    memset((char*)&(*__first), _STLP_SHRED_BYTE, sizeof(_Tp));
#endif
  }
}

template <class _ForwardIterator, class _Tp>
#if defined (_STLP_DEBUG_UNINITIALIZED)
inline void __destroy_range_aux( _ForwardIterator __first, _ForwardIterator __last,
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
inline void __destroy_range( _ForwardIterator __first, _ForwardIterator __last, _Tp* __ptr )
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
inline _Tp __default_constructed_aux( _Tp*, const false_type& )
{ return _Tp(); }
template <class _Tp>
inline _Tp __default_constructed_aux( _Tp*, const true_type& )
{ return _Tp(0); }

template <class _Tp>
inline _Tp __default_constructed( _Tp* __p )
{ return __default_constructed_aux(__p, _HasDefaultZeroValue(__p)._Answer()); }

#  define _STLP_DEFAULT_CONSTRUCTED(_TTp) __default_constructed((_TTp*)0)
#else
#  define _STLP_DEFAULT_CONSTRUCTED(_TTp) _TTp()
#endif /* _STLP_DEF_CONST_DEF_PARAM_BUG */

// Malloc-based allocator.

typedef void (* __oom_handler_type)();

class _STLP_CLASS_DECLSPEC __malloc_alloc
{
  public:
    // this one is needed for proper simple_alloc wrapping
    typedef char value_type;
    static void* _STLP_CALL allocate(size_t __n);
    static void _STLP_CALL deallocate(void* __p, size_t /* __n */)
      { free((char*)__p); }
    static __oom_handler_type _STLP_CALL set_malloc_handler(__oom_handler_type __f);
};

// New-based allocator.

class _STLP_CLASS_DECLSPEC __new_alloc
{
  public:
    // this one is needed for proper simple_alloc wrapping
    typedef char value_type;
    static void* _STLP_CALL allocate(size_t __n)
      { return __stl_new(__n); }
    static void _STLP_CALL deallocate(void* __p, size_t)
      { __stl_delete(__p); }
};

// Allocator adaptor to check size arguments for debugging.
// Reports errors using assert.  Checking can be disabled with
// NDEBUG, but it's far better to just use the underlying allocator
// instead when no checking is desired.
// There is some evidence that this can confuse Purify.
// This adaptor can only be applied to raw allocators

template <class _Alloc>
class __debug_alloc :
    public _Alloc
{
  public:
    typedef _Alloc __allocator_type;
    typedef typename _Alloc::value_type value_type;

  private:
    struct __alloc_header
    {
        uint32_t __magic:16;
        uint32_t __type_size:16;
        uint32_t _M_size;
    }; // that is 8 bytes for sure

    // Sunpro CC has bug on enums, so extra_before/after set explicitly
    enum
    {
      __pad = 8,
      __magic = 0xdeba,
      __deleted_magic = 0xdebd,
      __shred_byte = _STLP_SHRED_BYTE
    };

    enum
    {
      __extra_before = 16,
      __extra_after = 8
    };

    // Size of space used to store size.  Note
    // that this must be large enough to preserve alignment.
    static size_t _STLP_CALL __extra_before_chunk()
      {
        return (long)__extra_before / sizeof(value_type) +
          (size_t)((long)__extra_before % sizeof(value_type) > 0);
      }
    static size_t _STLP_CALL __extra_after_chunk()
      {
        return (long)__extra_after / sizeof(value_type) +
          (size_t)((long)__extra_after % sizeof(value_type) > 0);
      }

  public:
    __debug_alloc()
      { }
    ~__debug_alloc()
      { }

    static void* _STLP_CALL allocate(size_t);
    static void _STLP_CALL deallocate(void *, size_t);
};

#  if defined (__OS400__)
// dums 02/05/2007: is it really necessary ?
enum { _MAX_BYTES = 256 };
#  else
enum { _MAX_BYTES = 32 * sizeof(void*) };
#  endif

// node allocator.

class _STLP_CLASS_DECLSPEC __node_alloc
{
    static void * _STLP_CALL _M_allocate(size_t& __n);
    /* __p may not be 0 */
    static void _STLP_CALL _M_deallocate(void *__p, size_t __n);

  public:
    // this one is needed for proper simple_alloc wrapping
    typedef char value_type;
    /* __n must be > 0      */
    static void* _STLP_CALL allocate(size_t& __n)
      { return (__n > (size_t)_MAX_BYTES) ? __stl_new(__n) : _M_allocate(__n); }
    /* __p may not be 0 */
    static void _STLP_CALL deallocate(void *__p, size_t __n)
      { if (__n > (size_t)_MAX_BYTES) __stl_delete(__p); else _M_deallocate(__p, __n); }
};

#  if defined (_STLP_USE_TEMPLATE_EXPORT)
_STLP_EXPORT_TEMPLATE_CLASS __debug_alloc<__node_alloc>;
#  endif

#if defined (_STLP_USE_TEMPLATE_EXPORT)
_STLP_EXPORT_TEMPLATE_CLASS __debug_alloc<__new_alloc>;
_STLP_EXPORT_TEMPLATE_CLASS __debug_alloc<__malloc_alloc>;
#endif

// Another allocator adaptor: _Alloc_traits.  This serves two
// purposes.  First, make it possible to write containers that can use
// either SGI-style allocators or standard-conforming allocator.

// The fully general version.
template <class _Tp, class _Allocator>
struct _Alloc_traits
{
    typedef _Allocator _Orig;
    typedef typename _Allocator::_STLP_TEMPLATE rebind<_Tp> _Rebind_type;
    typedef typename _Rebind_type::other  allocator_type;

    static allocator_type create_allocator(const _Orig& __a)
      { return allocator_type(__a); }
};

#if defined (_STLP_USE_PERTHREAD_ALLOC)
_STLP_END_NAMESPACE
#  include <stl/_pthread_alloc.h>
_STLP_BEGIN_NAMESPACE
#endif

// This implements allocators as specified in the C++ standard.
//
// Note that standard-conforming allocators use many language features
// that are not yet widely implemented.  In particular, they rely on
// member templates, partial specialization, partial ordering of function
// templates, the typename keyword, and the use of the template keyword
// to refer to a template member of a dependent type.

template <class _Tp>
class allocator
{
  private:
    // underlying allocator implementation
#if defined (_STLP_USE_PERTHREAD_ALLOC)
#ifdef _STLP_DEBUG_ALLOC
    typedef __debug_alloc<__pthread_alloc> __alloc_type;
#else
    typedef __pthread_alloc __alloc_type;
#endif

#elif defined (_STLP_USE_NEWALLOC)

#ifdef _STLP_DEBUG_ALLOC
    typedef __debug_alloc<__new_alloc> __alloc_type;
#else
    typedef __new_alloc __alloc_type;
#endif

#elif defined (_STLP_USE_MALLOC)

#ifdef _STLP_DEBUG_ALLOC
    typedef __debug_alloc<__malloc_alloc> __alloc_type;
#else
    typedef __malloc_alloc __alloc_type;
#endif

#else // then use __node_alloc

#ifdef _STLP_DEBUG_ALLOC
    typedef __debug_alloc<__node_alloc> __alloc_type;
#else
    typedef __node_alloc __alloc_type;
#endif

#endif

  public:
    typedef _Tp        value_type;
    typedef _Tp*       pointer;
    typedef const _Tp* const_pointer;
    typedef _Tp&       reference;
    typedef const _Tp& const_reference;
    typedef size_t     size_type;
    typedef ptrdiff_t  difference_type;

    template <class _Tp1>
    struct rebind
    {
        typedef allocator<_Tp1> other;
    };

    allocator() _STLP_NOTHROW
      { }
    template <class _Tp1>
    allocator(const allocator<_Tp1>&) _STLP_NOTHROW
      { }
    allocator(const allocator<_Tp>&) _STLP_NOTHROW
      { }
#if !defined (_STLP_NO_MOVE_SEMANTIC)
    allocator(__move_source<allocator<_Tp> > src) _STLP_NOTHROW
      { }
#endif
    ~allocator() _STLP_NOTHROW
      { }
    pointer address( reference __x ) const
      { return &__x; }
    const_pointer address( const_reference __x ) const
      { return &__x; }
    // __n is permitted to be 0.  The C++ standard says nothing about what the return value is when __n == 0.
    _Tp* allocate(size_type __n, const void* = 0)
      {
        if (__n > max_size()) {
          _STLP_THROW_BAD_ALLOC;
        }
        if (__n != 0) {
          size_type __buf_size = __n * sizeof(value_type);
          _Tp* __ret = __REINTERPRET_CAST(_Tp*, __alloc_type::allocate(__buf_size));
#if defined (_STLP_DEBUG_UNINITIALIZED) && !defined (_STLP_DEBUG_ALLOC)
          memset((char*)__ret, _STLP_SHRED_BYTE, __buf_size);
#endif
          return __ret;
        }

    return 0;
  }

  // __p is permitted to be a null pointer, only if n==0.
    void deallocate(pointer __p, size_type __n)
      {
        _STLP_ASSERT( (__p == 0) == (__n == 0) )
          if (__p != 0) {
#if defined (_STLP_DEBUG_UNINITIALIZED) && !defined (_STLP_DEBUG_ALLOC)
            memset((char*)__p, _STLP_SHRED_BYTE, __n * sizeof(value_type));
#endif
            __alloc_type::deallocate((void*)__p, __n * sizeof(value_type));
          }
      }
#if !defined (_STLP_NO_ANACHRONISMS)
    // backwards compatibility
    void deallocate(pointer __p) const
      {
        if (__p != 0)
          __alloc_type::deallocate((void*)__p, sizeof(value_type));
      }
#endif

    size_type max_size() const _STLP_NOTHROW
      { return size_t(-1) / sizeof(value_type); }
    void construct(pointer __p, const_reference __val)
      { _STLP_STD::_Copy_Construct(__p, __val); }
    void destroy(pointer __p)
      { _STLP_STD::_Destroy(__p); }
};

_STLP_TEMPLATE_NULL
class _STLP_CLASS_DECLSPEC allocator<void>
{
  public:
    typedef size_t      size_type;
    typedef ptrdiff_t   difference_type;
    typedef void*       pointer;
    typedef const void* const_pointer;
#if defined (_STLP_CLASS_PARTIAL_SPECIALIZATION)
    typedef void        value_type;
#endif
    template <class _Tp1>
    struct rebind
    {
        typedef allocator<_Tp1> other;
    };
};

template <class _T1, class _T2>
inline bool _STLP_CALL operator ==(const allocator<_T1>&, const allocator<_T2>&) _STLP_NOTHROW
{ return true; }

template <class _T1, class _T2>
inline bool _STLP_CALL operator!=(const allocator<_T1>&, const allocator<_T2>&) _STLP_NOTHROW
{ return false; }

#if defined (_STLP_USE_TEMPLATE_EXPORT)
_STLP_EXPORT_TEMPLATE_CLASS allocator<char>;
#  if defined (_STLP_HAS_WCHAR_T)
_STLP_EXPORT_TEMPLATE_CLASS allocator<wchar_t>;
#  endif
#  if defined (_STLP_USE_PTR_SPECIALIZATIONS)
_STLP_EXPORT_TEMPLATE_CLASS allocator<void*>;
#  endif
#endif

_STLP_MOVE_TO_PRIV_NAMESPACE

_STLP_MOVE_TO_STD_NAMESPACE

#if defined (_STLP_CLASS_PARTIAL_SPECIALIZATION)

_STLP_BEGIN_TR1_NAMESPACE

template <class T>
struct __is_stateless_alloc :
    public integral_constant<bool,is_trivial<T>::value || is_empty<T>::value>
{ };

_STLP_END_NAMESPACE

#endif

#if !defined (_STLP_FORCE_ALLOCATORS)
#  define _STLP_FORCE_ALLOCATORS(a,y)
#endif

template <class _Tp> void swap(_Tp& __a, _Tp& __b);

template <class _Tp>
inline void swap(allocator<_Tp>& __a, allocator<_Tp>& __b)
{ }

_STLP_MOVE_TO_PRIV_NAMESPACE

// inheritance is being used for EBO optimization
template <class _Value, class _Tp, class _MaybeReboundAlloc>
class _STLP_alloc_proxy :
    public _MaybeReboundAlloc
{
  private:
    typedef _MaybeReboundAlloc _Base;
    typedef typename _Base::size_type size_type;
    typedef _STLP_alloc_proxy<_Value, _Tp, _MaybeReboundAlloc> _Self;

  public:
    _Value _M_data;

    _STLP_alloc_proxy (const _MaybeReboundAlloc& __a, _Value __p) :
        _MaybeReboundAlloc(__a),
        _M_data(__p)
      { }

#if !defined (_STLP_NO_MOVE_SEMANTIC)
    _STLP_alloc_proxy (__move_source<_Self> src) :
        _Base(src.get()._M_base()),
        _M_data(src.get()._M_data)
      { }

    _Base& _M_base()
      { return *this; }
#endif
    void swap( _Self& r )
      {
        _STLP_STD::swap( static_cast<_Base&>(*this), static_cast<_Base&>(r) );
        _STLP_STD::swap( _M_data, r._M_data );
      }
};

#if defined (_STLP_USE_TEMPLATE_EXPORT)
_STLP_EXPORT_TEMPLATE_CLASS _STLP_alloc_proxy<char*, char, allocator<char> >;
#  if defined (_STLP_HAS_WCHAR_T)
_STLP_EXPORT_TEMPLATE_CLASS _STLP_alloc_proxy<wchar_t*, wchar_t, allocator<wchar_t> >;
#  endif
#  if defined (_STLP_USE_PTR_SPECIALIZATIONS)
_STLP_EXPORT_TEMPLATE_CLASS _STLP_alloc_proxy<void**, void*, allocator<void*> >;
#  endif
#endif

_STLP_MOVE_TO_STD_NAMESPACE

template <class _Value, class _Tp, class _MaybeReboundAlloc>
inline void swap( _STLP_PRIV _STLP_alloc_proxy<_Value,_Tp,_MaybeReboundAlloc>& __a, _STLP_PRIV _STLP_alloc_proxy<_Value,_Tp,_MaybeReboundAlloc>& __b)
{ __a.swap( __b ); }

_STLP_END_NAMESPACE

#if defined (_STLP_EXPOSE_GLOBALS_IMPLEMENTATION)
#  include <stl/_alloc.c>
#endif

#endif /* _STLP_INTERNAL_ALLOC_H */

// Local Variables:
// mode:C++
// End:

