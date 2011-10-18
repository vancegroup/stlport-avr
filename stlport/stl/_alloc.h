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

#ifndef _STLP_CSTDDEF
#  include <cstddef>
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

template <class T>
inline T* addressof(T& r) /* noexcept */
{ return reinterpret_cast<T*>( &const_cast<char&>( reinterpret_cast<const volatile char&>(r) ) ); }

// 20.6.3, pointer traits
template <class Ptr> struct pointer_traits;
// template <class T> struct pointer_traits<T*>;

namespace detail {

struct __has_type_selector
{
    // T::element_type?
    template <class T>
    static decltype( declval<typename T::element_type*>(), declval<true_type>()) __test( int );

    template <class>
    static false_type __test( ... );

    // T::difference_type?
    template <class T>
    static typename T::difference_type __test_d( int );

    template <class>
    static typename _STLP_STD::ptrdiff_t __test_d( ... );

    // T::rebind<U>?
    template <class T, class U>
    static decltype( declval<typename T::template rebind<U>::type*>(), declval<true_type>()) __test_r( int );

    template <class, class>
    static false_type __test_r( ... );

    // T::allocator_type?
    template <class T>
    static decltype( declval<typename T::allocator_type>(), declval<true_type>()) __test_a( int );

    template <class>
    static false_type __test_a( ... );

    // T::pointer?
    template <class T>
    static decltype( declval<typename T::pointer>(), declval<true_type>()) __test_p( int );

    template <class>
    static false_type __test_p( ... );

    // T::const_pointer?
    template <class T>
    static decltype( declval<typename T::const_pointer>(), declval<true_type>()) __test_cp( int );

    template <class>
    static false_type __test_cp( ... );

    // T::void_pointer?
    template <class T>
    static decltype( declval<typename T::void_pointer>(), declval<true_type>()) __test_vp( int );

    template <class>
    static false_type __test_vp( ... );

    // T::const_void_pointer?
    template <class T>
    static decltype( declval<typename T::const_void_pointer>(), declval<true_type>()) __test_cvp( int );

    template <class>
    static false_type __test_cvp( ... );

    // T::difference_type, another?
    template <class T>
    static decltype( declval<typename T::difference_type>(), declval<true_type>()) __test_dp( int );

    template <class>
    static false_type __test_dp( ... );

    // T::size_type?
    template <class T>
    static decltype( declval<typename T::size_type>(), declval<true_type>()) __test_sz( int );

    template <class>
    static false_type __test_sz( ... );

    // T::propagate_on_container_copy_assignment?
    template <class T>
    static decltype( declval<typename T::propagate_on_container_copy_assignment>() ) __test_pcca( int );

    template <class>
    static false_type __test_pcca( ... );

    // T::propagate_on_container_move_assignment?
    template <class T>
    static decltype( declval<typename T::propagate_on_container_move_assignment>() ) __test_pcma( int );

    template <class>
    static false_type __test_pcma( ... );

    // T::propagate_on_container_swap?
    template <class T>
    static decltype( declval<typename T::propagate_on_container_swap>() ) __test_pcs( int );

    template <class>
    static false_type __test_pcs( ... );

    // T::rebind<U>::other?
    template <class T, class U>
    static decltype( declval<typename T::template rebind<U>::other>(), declval<true_type>()) __test_ro( int );

    template <class, class>
    static false_type __test_ro( ... );
};

template <bool, class T>
struct __element_type
{
};

template <class T>
struct __element_type<true,T>
{
    typedef typename T::element_type element_type;
};

template <bool, class T, class U>
struct __rebind_type
{
};

template <class T, class U>
struct __rebind_type<true,T,U>
{
    typedef typename T::template rebind<U>::type type;
};

} // detail

template <class Ptr>
struct pointer_traits
{
    typedef Ptr pointer;
    // typedef typename Ptr::element_type element_type;
    typedef typename detail::__element_type<is_same<true_type,decltype(detail::__has_type_selector::__test<Ptr>(0))>::value,Ptr>::element_type element_type;
    // typedef typename Ptr::difference_type difference_type;
    typedef decltype(detail::__has_type_selector::__test_d<Ptr>(0)) difference_type;
    // template <class U> using rebind = see below;
    template <class U>
    struct rebind
    {
        // typedef typename Ptr::template rebind<U>::type type;
        typedef typename detail::__rebind_type<is_same<true_type,decltype(detail::__has_type_selector::__test_r<Ptr,U>(0))>::value,Ptr,U>::type type;
    };

    static pointer pointer_to( element_type& r )
      { return Ptr::pointer_to(r); }
};

template <class T>
struct pointer_traits<T*>
{
    typedef T* pointer;
    typedef T element_type;
    typedef ptrdiff_t difference_type;
    // template <class U> using rebind = U*;
    template <class U>
    struct rebind
    {
        typedef U* type;
    };

    static pointer pointer_to( T& r ) /* noexcept */
      { return _STLP_STD::addressof(r); }
};

template <>
struct pointer_traits<void*>
{
    typedef void* pointer;
    typedef void element_type;
    typedef ptrdiff_t difference_type;
    // template <class U> using rebind = U*;
    template <class U>
    struct rebind
    {
        typedef U* type;
    };

    // static pointer pointer_to( void ) /* noexcept */ // unspecified
    //  { return NULL; }
};

enum class pointer_safety
{ relaxed, preferred, strict };

_STLP_DECLSPEC void declare_reachable(void *p);

namespace detail {

_STLP_DECLSPEC void* __undeclare_reachable( void* ) /* noexcept */;

} // detail

template <class T>
T *undeclare_reachable( T* p ) /* noexcept */
{ return reinterpret_cast<T*>( detail::__undeclare_reachable(reinterpret_cast<void*>(p)) ); }

_STLP_DECLSPEC void declare_no_pointers(char *p, size_t n) /* noexcept */;
_STLP_DECLSPEC void undeclare_no_pointers(char *p, size_t n) /* noexcept */;
_STLP_DECLSPEC pointer_safety get_pointer_safety() /* noexcept */;

_STLP_DECLSPEC void *align( _STLP_STD::size_t alignment, _STLP_STD::size_t size, void *&ptr, _STLP_STD::size_t& space );

namespace detail {

//template <class T>
//struct __has_allocator_type :
//        integral_constant<bool,is_same<true_type,decltype(detail::__has_type_selector::__test_a<T>(0))>::value>
//{
//};

template <class T, class Alloc, bool>
struct __uses_allocator_aux :
    public false_type
{
};

template <class T, class Alloc>
struct __uses_allocator_aux<T,Alloc,true> :
    public integral_constant<bool,is_convertible<Alloc,typename T::allocator_type>::value>
{
};

template <bool, class Alloc>
struct __pointer_type
{
    typedef typename Alloc::value_type* pointer;
};

template <class Alloc>
struct __pointer_type<true,Alloc>
{
    typedef typename Alloc::pointer pointer;
};

template <bool, class Alloc>
struct __const_pointer_type
{
    typedef typename pointer_traits<typename __pointer_type<is_same<true_type,decltype(detail::__has_type_selector::__test_p<Alloc>(0))>::value,Alloc>::pointer>::template rebind<typename add_const<typename Alloc::value_type>::type>::type const_pointer;
};

template <class Alloc>
struct __const_pointer_type<true,Alloc>
{
    typedef typename Alloc::const_pointer const_pointer;
};

template <bool, class Alloc>
struct __void_pointer_type
{
    typedef typename pointer_traits<typename __pointer_type<is_same<true_type,decltype(detail::__has_type_selector::__test_p<Alloc>(0))>::value,Alloc>::pointer>::template rebind<void>::type void_pointer;
};

template <class Alloc>
struct __void_pointer_type<true,Alloc>
{
    typedef typename Alloc::void_pointer void_pointer;
};

template <bool, class Alloc>
struct __const_void_pointer_type
{
    typedef typename pointer_traits<typename __pointer_type<is_same<true_type,decltype(detail::__has_type_selector::__test_p<Alloc>(0))>::value,Alloc>::pointer>::template rebind<const void>::type const_void_pointer;
};

template <class Alloc>
struct __const_void_pointer_type<true,Alloc>
{
    typedef typename Alloc::const_void_pointer const_void_pointer;
};

template <bool, class Alloc>
struct __difference_pointer_type
{
    typedef typename pointer_traits<typename __pointer_type<is_same<true_type,decltype(detail::__has_type_selector::__test_p<Alloc>(0))>::value,Alloc>::pointer>::difference_type difference_type;
};

template <class Alloc>
struct __difference_pointer_type<true,Alloc>
{
    typedef typename Alloc::difference_type difference_type;
};

template <bool, class Alloc>
struct __pointer_size_type
{
    typedef typename make_unsigned<typename detail::__difference_pointer_type<is_same<true_type,decltype(detail::__has_type_selector::__test_dp<Alloc>(0))>::value,Alloc>::difference_type>::type size_type;
};

template <class Alloc>
struct __pointer_size_type<true,Alloc>
{
    typedef typename Alloc::size_type size_type;
};

template <class ToF, class Alloc, class U, class ... Args>
class __rebind_other_type
{
//  private:
//    template <template <class V, class ... XArgs> class T, class V, class ... XArgs>
//    static T<V,XArgs...> __test( int );

//  public:
//    typedef decltype(__test<Alloc<U,Args> >(0))::type type;
};

template <template <class U, class ... Args> class Alloc, class U, class ... Args>
struct __rebind_other_type<false_type,Alloc<U,Args...>,U,Args... >
{
//  private:
//    template <template <class V, class ... XArgs> class T, class V, class ... XArgs>
//    static T<V,XArgs...> __test( int );

//  public:
    typedef Alloc<U,Args...> type;
};

template <class Alloc, class U, class ... Args>
struct __rebind_other_type<true_type,Alloc,U,Args...>
{
    typedef typename Alloc::template rebind<U>::other type;
};

} // namespace detail

template <class T, class Alloc>
struct uses_allocator :
    public detail::__uses_allocator_aux<T,Alloc,is_same<true_type,decltype(detail::__has_type_selector::__test_a<T>(0))>::value>
{
};

struct allocator_arg_t
{ };

constexpr allocator_arg_t allocator_arg = allocator_arg_t();

//namespace detail {
//struct _alloc_dummy {};
//}

template <class Alloc /* , class = detail::_alloc_dummy, class ... */ >
struct allocator_traits
{
    typedef Alloc allocator_type;
    typedef typename Alloc::value_type value_type;
    typedef typename detail::__pointer_type<is_same<true_type,decltype(detail::__has_type_selector::__test_p<Alloc>(0))>::value,Alloc>::pointer pointer;
    typedef typename detail::__const_pointer_type<is_same<true_type,decltype(detail::__has_type_selector::__test_cp<Alloc>(0))>::value,Alloc>::const_pointer const_pointer;
    typedef typename detail::__void_pointer_type<is_same<true_type,decltype(detail::__has_type_selector::__test_vp<Alloc>(0))>::value,Alloc>::void_pointer void_pointer;
    typedef typename detail::__const_void_pointer_type<is_same<true_type,decltype(detail::__has_type_selector::__test_cvp<Alloc>(0))>::value,Alloc>::const_void_pointer const_void_pointer;

    typedef typename detail::__difference_pointer_type<is_same<true_type,decltype(detail::__has_type_selector::__test_dp<Alloc>(0))>::value,Alloc>::difference_type difference_type;
    typedef typename detail::__pointer_size_type<is_same<true_type,decltype(detail::__has_type_selector::__test_sz<Alloc>(0))>::value,Alloc>::size_type size_type;
    typedef decltype(detail::__has_type_selector::__test_pcca<Alloc>(0)) propagate_on_container_copy_assignment;
    typedef decltype(detail::__has_type_selector::__test_pcma<Alloc>(0)) propagate_on_container_move_assignment;
    typedef decltype(detail::__has_type_selector::__test_pcs<Alloc>(0)) propagate_on_container_swap;
    // template <class T> using rebind_alloc = see below;
    template <class T>
    struct rebind_alloc
    {
        typedef typename detail::__rebind_other_type<decltype(detail::__has_type_selector::__test_ro<Alloc,T>(0)),Alloc,T>::type type;
    };
    // template <class T> using rebind_traits = allocator_traits<rebind_alloc<T> >;
    template <class T>
    struct rebind_traits
    {
        typedef allocator_traits<typename rebind_alloc<T>::type> type;
    };

    static pointer allocate( Alloc& a, size_type n );
    static pointer allocate( Alloc& a, size_type n, const_void_pointer hint );
    static void deallocate( Alloc& a, pointer p, size_type n ) /* noexcept */;

    template <class T, class... Args>
    static void construct( Alloc& a, T* p, Args&&... args );

    template <class T>
    static void destroy( Alloc& a, T* p );

    static size_type max_size( const Alloc& a );
    static Alloc select_on_container_copy_construction( const Alloc& rhs );
};

#if 0
template <template <class U, class ... Args> class Alloc, class U, class ... Args>
struct allocator_traits<Alloc<U,Args...> >
{
    typedef Alloc<U,Args...> allocator_type;
    typedef typename Alloc<U,Args...>::value_type value_type;
    typedef typename detail::__pointer_type<is_same<true_type,decltype(detail::__has_type_selector::__test_p<Alloc<U,Args...>>(0))>::value,Alloc<U,Args...>>::pointer pointer;
    typedef typename detail::__const_pointer_type<is_same<true_type,decltype(detail::__has_type_selector::__test_cp<Alloc<U,Args...>>(0))>::value,Alloc<U,Args...>>::const_pointer const_pointer;
    typedef typename detail::__void_pointer_type<is_same<true_type,decltype(detail::__has_type_selector::__test_vp<Alloc<U,Args...>>(0))>::value,Alloc<U,Args...>>::void_pointer void_pointer;
    typedef typename detail::__const_void_pointer_type<is_same<true_type,decltype(detail::__has_type_selector::__test_cvp<Alloc<U,Args...>>(0))>::value,Alloc<U,Args...>>::const_void_pointer const_void_pointer;

    typedef typename detail::__difference_pointer_type<is_same<true_type,decltype(detail::__has_type_selector::__test_dp<Alloc<U,Args...>>(0))>::value,Alloc<U,Args...>>::difference_type difference_type;
    typedef typename detail::__pointer_size_type<is_same<true_type,decltype(detail::__has_type_selector::__test_sz<Alloc<U,Args...>>(0))>::value,Alloc<U,Args...>>::size_type size_type;
    typedef decltype(detail::__has_type_selector::__test_pcca<Alloc<U,Args...>>(0)) propagate_on_container_copy_assignment;
    typedef decltype(detail::__has_type_selector::__test_pcma<Alloc<U,Args...>>(0)) propagate_on_container_move_assignment;
    typedef decltype(detail::__has_type_selector::__test_pcs<Alloc<U,Args...>>(0)) propagate_on_container_swap;
    // template <class T> using rebind_alloc = see below;
    template <class T>
    struct rebind_alloc
    {
        typedef typename detail::__rebind_other_type<decltype(detail::__has_type_selector::__test_ro<Alloc<T,Args...>,T,Args...>(0)),Alloc<T,Args...>,T,Args...>::type type;
    };
    // template <class T> using rebind_traits = allocator_traits<rebind_alloc<T> >;
    template <class T>
    struct rebind_traits
    {
        typedef allocator_traits<typename rebind_alloc<T>::type> type;
    };

    static pointer allocate( Alloc<U,Args...>& a, size_type n );
    static pointer allocate( Alloc<U,Args...>& a, size_type n, const_void_pointer hint );
    static void deallocate( Alloc<U,Args...>& a, pointer p, size_type n ) /* noexcept */;

    template <class T, class... Args2>
    static void construct( Alloc<U,Args...>& a, T* p, Args2&&... args );

    template <class T>
    static void destroy( Alloc<U,Args...>& a, T* p );

    static size_type max_size( const Alloc<U,Args...>& a );
    static Alloc<U,Args...> select_on_container_copy_construction( const Alloc<U,Args...>& rhs );
};
#endif

namespace detail {

template <bool>
struct __destroy_selector
{
    template <class U>
    static void destroy( U* p )
      {
        p->~U();
#if defined (_STLP_DEBUG_UNINITIALIZED)
        memset( reinterpret_cast<char*>(p), _STLP_SHRED_BYTE, sizeof(U) );
#endif
      }

    template <class _ForwardIterator>
    static void destroy( _ForwardIterator __first, _ForwardIterator __last )
      {
        for_each( __first, __last, []( typename iterator_traits<_ForwardIterator>::value_type& i ){
            _STLP_STD::detail::__destroy_selector<false>::destroy( &i );
          } );
      }
};

template <>
struct __destroy_selector<true>
{
    template <class U>
    static void destroy( U* p )
      {
#if defined (_STLP_DEBUG_UNINITIALIZED)
        memset( reinterpret_cast<char*>(p), _STLP_SHRED_BYTE, sizeof(U) );
#endif
      }

    template <class _ForwardIterator>
    static void destroy( _ForwardIterator __first, _ForwardIterator __last )
      {
#if defined (_STLP_DEBUG_UNINITIALIZED)
        for_each( __first, __last, []( typename iterator_traits<_ForwardIterator>::value_type& i ){
            destroy( &i );
          } );
#endif
      }
};

template <class _ForwardIterator>
inline void _Destroy_Range(_ForwardIterator __first, _ForwardIterator __last)
{
  _STLP_STD::detail::__destroy_selector<has_trivial_destructor<typename iterator_traits<_ForwardIterator>::value_type>::value>::destroy( __first, __last );
}

} // namespace detail

#if defined (new)
#  define _STLP_NEW_REDEFINE new
#  undef new
#endif

#if defined(_STLP_NEW_REDEFINE)
#  if defined (DEBUG_NEW)
#    define new DEBUG_NEW
#  endif
#  undef _STLP_NEW_REDEFINE
#endif

//inline void _Destroy_Range(char*, char*) {}
//#if defined (_STLP_HAS_WCHAR_T) // dwa 8/15/97
//inline void _Destroy_Range(wchar_t*, wchar_t*) {}
//inline void _Destroy_Range(const wchar_t*, const wchar_t*) {}
//#endif

//template <class _ForwardIterator>
//inline void _Destroy_Moved_Range(_ForwardIterator __first, _ForwardIterator __last)
//{ _Destroy_Range(__first, __last); }

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

template <class _Tp> class allocator;

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
    ~allocator()
      { }
    pointer address( reference __x ) const _STLP_NOTHROW
      { return addressof(__x); }
    const_pointer address( const_reference __x ) const _STLP_NOTHROW
      { return addressof(__x); }
    // __n is permitted to be 0.  The C++ standard says nothing about what the return value is when __n == 0.
    pointer allocate(size_type __n, allocator<void>::const_pointer /* hint */ = 0)
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

    template<class U, class... Args>
    void construct( U* p, Args&&... args )
      { ::new((void*)p) U( _STLP_STD::forward<Args>(args)... ); }

    template <class U>
    void destroy( U* p )
      { _STLP_STD::detail::__destroy_selector<has_trivial_destructor<_Tp>::value>::destroy( p ); }
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

template <class T>
struct __is_stateless_alloc :
    public integral_constant<bool,is_trivial<T>::value || is_empty<T>::value>
{ };

#endif

#if !defined (_STLP_FORCE_ALLOCATORS)
#  define _STLP_FORCE_ALLOCATORS(a,y)
#endif

template <class _Tp> void swap(_Tp&, _Tp&);

template <class _Tp>
inline void swap(allocator<_Tp>&, allocator<_Tp>&)
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

