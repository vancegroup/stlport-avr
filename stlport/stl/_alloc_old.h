template<class _Tp, class _Alloc>
class __simple_alloc {
  typedef _Alloc __alloc_type;
public:
  typedef typename _Alloc::value_type __alloc_value_type;
  typedef _Tp value_type;
  static size_t  __STL_CALL __chunk(size_t __n) { 
    return (sizeof(__alloc_value_type)==sizeof(value_type)) ? __n : 
	    ((__n*sizeof(value_type)+sizeof(__alloc_value_type)-1)/sizeof(__alloc_value_type));
  }
  static _Tp*  __STL_CALL allocate(size_t __n) { return 0 == __n ? 0 : (_Tp*) __alloc_type::allocate(__chunk(__n)); }
  static void  __STL_CALL deallocate(_Tp * __p, size_t __n) { 
    __alloc_type::deallocate((__alloc_value_type*)__p, __chunk(__n)); }
};

// Allocator adaptor to turn an SGI-style allocator (e.g. alloc, malloc_alloc)
// into a standard-conforming allocator.   Note that this adaptor does
// *not* assume that all objects of the underlying alloc class are
// identical, nor does it assume that all of the underlying alloc's
// member functions are static member functions.  Note, also, that 
// __allocator<_Tp, alloc> is essentially the same thing as allocator<_Tp>.

template <class _Tp, class _Alloc>
struct __allocator : public _Alloc {
  typedef _Alloc __underlying_alloc;

  typedef size_t    size_type;
  typedef ptrdiff_t difference_type;
  typedef _Tp*       pointer;
  typedef const _Tp* const_pointer;
  typedef _Tp&       reference;
  typedef const _Tp& const_reference;
  typedef _Tp        value_type;

# if defined (__STL_MEMBER_TEMPLATE_CLASSES)
  template <class _Tp1> struct rebind {
    typedef __allocator<_Tp1, _Alloc> other;
  };
# endif
  __allocator() __STL_NOTHROW {}
  __allocator(const _Alloc& ) __STL_NOTHROW {}
  __allocator(const __allocator<_Tp, _Alloc>& __a) __STL_NOTHROW
    : _Alloc(__a) {}
# if defined (__STL_MEMBER_TEMPLATES) && defined (__STL_FUNCTION_TMPL_PARTIAL_ORDER)
  template <class _Tp1> 
  __allocator(const __allocator<_Tp1, _Alloc>& __a) __STL_NOTHROW
    : _Alloc(__a) {}
# endif
# ifdef __STL_TRIVIAL_DESTRUCTOR_BUG
  ~__allocator() __STL_NOTHROW {}
# endif
  pointer address(reference __x) const { return &__x; }

# if !defined (__WATCOM_CPLUSPLUS__)
  const_pointer address(const_reference __x) const { return &__x; }
# endif

  // __n is permitted to be 0.
  _Tp* allocate(size_type __n, const void* = 0) {
    return __n != 0 
        ? __STATIC_CAST(_Tp*,__underlying_alloc::allocate(__n * sizeof(_Tp))) 
        : 0;
  }

  // __p is not permitted to be a null pointer.
  void deallocate(pointer __p, size_type __n)
    { if (__p) __underlying_alloc::deallocate(__p, __n * sizeof(_Tp)); }

  size_type max_size() const __STL_NOTHROW 
    { return size_t(-1) / sizeof(_Tp); }

  void construct(pointer __p, const _Tp& __val) { __STLPORT_STD::construct(__p, __val); }
  void destroy(pointer __p) { __STLPORT_STD::destroy(__p); }

  const __underlying_alloc& __get_underlying_alloc() const { return *this; }
};

#ifdef __STL_CLASS_PARTIAL_SPECIALIZATION
template <class _Alloc>
class __allocator<void, _Alloc> {
  typedef size_t      size_type;
  typedef ptrdiff_t   difference_type;
  typedef void*       pointer;
  typedef const void* const_pointer;
  typedef void        value_type;
#ifdef __STL_MEMBER_TEMPLATE_CLASSES
  template <class _Tp1> struct rebind {
    typedef __allocator<_Tp1, _Alloc> other;
  };
#endif
};
#endif

template <class _Tp, class _Alloc>
inline bool  __STL_CALL operator==(const __allocator<_Tp, _Alloc>& __a1,
                                   const __allocator<_Tp, _Alloc>& __a2)
{
  return __a1.__get_underlying_alloc() == __a2.__get_underlying_alloc();
}

#ifdef __STL_USE_SEPARATE_RELOPS_NAMESPACE
template <class _Tp, class _Alloc>
inline bool  __STL_CALL operator!=(const __allocator<_Tp, _Alloc>& __a1,
                                   const __allocator<_Tp, _Alloc>& __a2)
{
  return __a1.__get_underlying_alloc() != __a2.__get_underlying_alloc();
}
#endif /* __STL_FUNCTION_TMPL_PARTIAL_ORDER */


// Comparison operators for all of the predifined SGI-style allocators.
// This ensures that __allocator<malloc_alloc> (for example) will
// work correctly.

#ifndef __STL_NON_TYPE_TMPL_PARAM_BUG
template <int inst>
inline bool  __STL_CALL operator==(const __malloc_alloc<inst>&,
                                   const __malloc_alloc<inst>&)
{
  return true;
}

#ifdef __STL_FUNCTION_TMPL_PARTIAL_ORDER
template <int __inst>
inline bool  __STL_CALL operator!=(const __malloc_alloc<__inst>&,
                                   const __malloc_alloc<__inst>&)
{
  return false;
}
#endif /* __STL_FUNCTION_TMPL_PARTIAL_ORDER */

inline bool __STL_CALL operator==(const __new_alloc&, const __new_alloc&) { return true; }

# ifdef __STL_USE_SEPARATE_RELOPS_NAMESPACE
inline bool __STL_CALL operator!=(const __new_alloc&, const __new_alloc&) { return false; }
# endif


template <bool __threads, int __inst>
inline bool  __STL_CALL operator==(const __node_alloc<__threads, __inst>&,
                                   const __node_alloc<__threads, __inst>&)
{
  return true;
}

#if defined( __STL_FUNCTION_TMPL_PARTIAL_ORDER )

template <bool __threads, int __inst>
inline bool  __STL_CALL operator!=(const __node_alloc<__threads, __inst>&,
                                   const __node_alloc<__threads, __inst>&)
{
  return false;
}
#endif /* __STL_FUNCTION_TMPL_PARTIAL_ORDER */

#endif /* __STL_NON_TYPE_TMPL_PARAM_BUG */

template <class _Alloc>
inline bool  __STL_CALL operator==(const __debug_alloc<_Alloc>&, const __debug_alloc<_Alloc>&) {  return true; }
# ifdef __STL_USE_SEPARATE_RELOPS_NAMESPACE
template <class _Alloc>
inline bool  __STL_CALL operator!=(const __debug_alloc<_Alloc>&, const __debug_alloc<_Alloc>&) {  return false; }
# endif

#if defined (__STL_CLASS_PARTIAL_SPECIALIZATION)

// Versions for the predefined SGI-style allocators.
template <class _Tp, int __inst>
struct _Alloc_traits<_Tp, __malloc_alloc<__inst> > {
  typedef __allocator<_Tp, __malloc_alloc<__inst> > allocator_type;
};


template <class _Tp, bool __threads, int __inst>
struct _Alloc_traits<_Tp, __node_alloc<__threads, __inst> > {
  typedef __allocator<_Tp, __node_alloc<__threads, __inst> > 
          allocator_type;
};

template <class _Tp, class _Alloc>
struct _Alloc_traits<_Tp, __debug_alloc<_Alloc> > {
  typedef __allocator<_Tp, __debug_alloc<_Alloc> > allocator_type;
};

// Versions for the __allocator adaptor used with the predefined
// SGI-style allocators.

template <class _Tp, class _Tp1, class _Alloc>
struct _Alloc_traits<_Tp, __allocator<_Tp1, _Alloc > > {
  typedef __allocator<_Tp, _Alloc > allocator_type;
};

#endif

#if !defined (__STL_MEMBER_TEMPLATE_CLASSES) 

// Versions for the predefined SGI-style allocators.


#  if defined (__STL_NON_TYPE_TMPL_PARAM_BUG)

typedef __malloc_alloc<0> __malloc_alloc_dfl;
typedef __node_alloc<false, 0> __single_client_node_alloc;
typedef __node_alloc<true, 0>  __multithreaded_node_alloc;

template <class _Tp>
inline __allocator<_Tp, __malloc_alloc_dfl >& __STL_CALL
__stl_alloc_rebind(__malloc_alloc_dfl& __a, const _Tp*) {
  return (__allocator<_Tp, __malloc_alloc_dfl >&)__a;
}

template <class _Tp>
inline __allocator<_Tp, __single_client_node_alloc >& __STL_CALL
__stl_alloc_rebind(__single_client_node_alloc& __a, const _Tp*) {
  return (__allocator<_Tp, __single_client_node_alloc >&)__a;
}

template <class _Tp>
inline __allocator<_Tp, __multithreaded_node_alloc >& __STL_CALL
__stl_alloc_rebind(__multithreaded_node_alloc& __a, const _Tp*) {
  return (__allocator<_Tp, __multithreaded_node_alloc >&)__a;
}

template <class _Tp>
inline __allocator<_Tp, __malloc_alloc_dfl > __STL_CALL
__stl_alloc_create(const __malloc_alloc_dfl&, const _Tp*) {
  return __allocator<_Tp, __malloc_alloc_dfl > ();
}

template <class _Tp>
inline __allocator<_Tp, __single_client_node_alloc > __STL_CALL
__stl_alloc_create(const __single_client_node_alloc&, const _Tp*) {
  return __allocator<_Tp, __single_client_node_alloc >();
}

template <class _Tp>
inline __allocator<_Tp, __multithreaded_node_alloc > __STL_CALL
__stl_alloc_create(const __multithreaded_node_alloc&, const _Tp*) {
  return __allocator<_Tp, __multithreaded_node_alloc >();
}

#  else

template <class _Tp, int __inst>
inline __allocator<_Tp, __malloc_alloc<__inst> >& __STL_CALL
__stl_alloc_rebind(__malloc_alloc<__inst>& __a, const _Tp*) {
  return (__allocator<_Tp, __malloc_alloc<__inst> >&)__a;
}

template <class _Tp, bool __threads, int __inst>
inline __allocator<_Tp, __node_alloc<__threads, __inst> >& __STL_CALL
__stl_alloc_rebind(__node_alloc<__threads, __inst>& __a, const _Tp*) {
  return (__allocator<_Tp, __node_alloc<__threads, __inst> >&)__a;
}

template <class _Tp, int __inst>
inline __allocator<_Tp, __malloc_alloc<__inst> > __STL_CALL
__stl_alloc_create(const __malloc_alloc<__inst>&, const _Tp*) {
  return __allocator<_Tp, __malloc_alloc<__inst> >();
}

template <class _Tp, bool __threads, int __inst>
inline __allocator<_Tp, __node_alloc<__threads, __inst> > __STL_CALL
__stl_alloc_create(const __node_alloc<__threads, __inst>&, const _Tp*) {
  return __allocator<_Tp, __node_alloc<__threads, __inst> >();
}

#  endif

template <class _Tp, class _Alloc>
inline __allocator<_Tp, __debug_alloc<_Alloc> > __STL_CALL
__stl_alloc_create(const __debug_alloc<_Alloc>&, const _Tp*) {
  return __allocator<_Tp, __debug_alloc<_Alloc> >();
}
template <class _Tp, class _Alloc>
inline __allocator<_Tp, __debug_alloc<_Alloc> >& __STL_CALL
__stl_alloc_rebind(__debug_alloc<_Alloc>& __a, const _Tp*) {
  return (__allocator<_Tp, __debug_alloc<_Alloc> >&)__a;
}

template <class _Tp>
inline __allocator<_Tp, __new_alloc > __STL_CALL
__stl_alloc_create(const __new_alloc&, const _Tp*) {
  return __allocator<_Tp, __new_alloc >();
}
template <class _Tp>
inline __allocator<_Tp, __new_alloc >&  __STL_CALL
__stl_alloc_rebind(__new_alloc& __a, const _Tp*) {
  return (__allocator<_Tp, __new_alloc >&)__a;
}

template <class _Tp1, class _Alloc, class _Tp2>
inline __allocator<_Tp2, _Alloc>& __STL_CALL
__stl_alloc_rebind(__allocator<_Tp1, _Alloc>& __a, const _Tp2*) {
  return (__allocator<_Tp2, _Alloc>&)__a;
}

template <class _Tp1, class _Alloc, class _Tp2>
inline __allocator<_Tp2, _Alloc> __STL_CALL
__stl_alloc_create(const __allocator<_Tp1, _Alloc>&, const _Tp2*) {
  return __allocator<_Tp2, _Alloc>();
}
#endif
