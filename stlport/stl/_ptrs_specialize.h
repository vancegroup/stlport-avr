#ifndef __STL_PTRS_SPECIALIZE_H
# define __STL_PTRS_SPECIALIZE_H


// the following is a workaround for arrow operator problems
#  if defined  ( __SGI_STL_NO_ARROW_OPERATOR ) 

// Proxy -> operator workaround for compilers that produce
// type checking errors on unused ->() operators

template <class _Ref, class _Ptr>
struct __arrow_op_dispatch {
  _Ptr _M_ptr;
  __arrow_op_dispatch(_Ref __r) : _M_ptr(&__r) {}
  _Ptr operator ->() const { return _M_ptr; }
};

#   if defined (__STL_NO_PROXY_ARROW_OPERATOR)

// User wants to disable proxy -> operators
#    define __STL_DEFINE_ARROW_OPERATOR
#    define __STL_ARROW_SPECIALIZE_WITH_PTRS(_Tp)

#   else

struct __arrow_op_dummy { int _M_data ; };

#  define __STL_ARROW_SPECIALIZE(_Tp)  \
__STL_TEMPLATE_NULL struct __arrow_op_dispatch<_Tp&, _Tp*> { \
  __arrow_op_dispatch(_Tp&) {} \
  __arrow_op_dummy operator ->() const { return __arrow_op_dummy(); } \
};

# ifdef __SUNPRO_CC
#  define __STL_ARROW_SPECIALIZE_WITH_PTRS(_Tp) \
__STL_ARROW_SPECIALIZE(_Tp) \
__STL_ARROW_SPECIALIZE(const _Tp) \
__STL_ARROW_SPECIALIZE(_Tp*) \
__STL_ARROW_SPECIALIZE(_Tp* const) \
__STL_ARROW_SPECIALIZE(const _Tp*) \
__STL_ARROW_SPECIALIZE(_Tp**) \
__STL_ARROW_SPECIALIZE(const _Tp**) \
__STL_ARROW_SPECIALIZE(_Tp* const *) \
__STL_ARROW_SPECIALIZE(_Tp***) \
__STL_ARROW_SPECIALIZE(const _Tp***)
# else
#  define __STL_ARROW_SPECIALIZE_WITH_PTRS(_Tp) \
__STL_ARROW_SPECIALIZE(_Tp) \
__STL_ARROW_SPECIALIZE(const _Tp) \
__STL_ARROW_SPECIALIZE(_Tp*) \
__STL_ARROW_SPECIALIZE(const _Tp*) \
__STL_ARROW_SPECIALIZE(_Tp**) \
__STL_ARROW_SPECIALIZE(const _Tp**) \
__STL_ARROW_SPECIALIZE(_Tp* const *) \
__STL_ARROW_SPECIALIZE(_Tp***) \
__STL_ARROW_SPECIALIZE(const _Tp***)
# endif

#  define __STL_DEFINE_ARROW_OPERATOR __arrow_op_dispatch<reference, pointer> operator->() const \
 { return __arrow_op_dispatch<reference, pointer>(this->operator*()); }

#  endif /* __STL_NO_PROXY_ARROW_OPERATOR */
# else
// Compiler can handle generic -> operator.
#  define __STL_ARROW_SPECIALIZE_WITH_PTRS(_Tp)
#  ifdef __BORLANDC__
#   define __STL_DEFINE_ARROW_OPERATOR  pointer operator->() const { return &(*(*this)); }
#  elif defined ( __STL_WINCE )
#   define __STL_DEFINE_ARROW_OPERATOR pointer operator->() const { reference x = operator*(); return &x; }
#  else
#   define __STL_DEFINE_ARROW_OPERATOR  pointer operator->() const { return &(operator*()); }
#  endif

# endif /* __SGI_STL_NO_ARROW_OPERATOR */

// Important pointers specializations



# if 0
# define __STL_ITERATOR_TRAITS_SPECIALIZE(_Type, _ValType) \
__STL_TEMPLATE_NULL struct iterator_traits<_Type*> { \
  typedef random_access_iterator_tag iterator_category; \
  typedef _ValType                   value_type; \
  typedef ptrdiff_t                  difference_type; \
  typedef _Type*                     pointer; \
  typedef _Type&                     reference; \
};
# endif


# ifdef __STL_SIMULATE_PARTIAL_SPEC_FOR_TYPE_TRAITS
#  define __STL_TYPE_TRAITS_POD_SPECIALIZE_V(_Type)
#  define __STL_TYPE_TRAITS_POD_SPECIALIZE(_Type)
# else
#  define __STL_TYPE_TRAITS_POD_SPECIALIZE(_Type) __STL_TEMPLATE_NULL struct __type_traits<_Type> : __type_traits_aux<true> {};
#  define __STL_TYPE_TRAITS_POD_SPECIALIZE_V(_Type) \
__STL_TYPE_TRAITS_POD_SPECIALIZE(_Type*) \
__STL_TYPE_TRAITS_POD_SPECIALIZE(const _Type*) \
__STL_TYPE_TRAITS_POD_SPECIALIZE(_Type**) \
__STL_TYPE_TRAITS_POD_SPECIALIZE(_Type* const *) \
__STL_TYPE_TRAITS_POD_SPECIALIZE(const _Type**) \
__STL_TYPE_TRAITS_POD_SPECIALIZE(_Type***) \
__STL_TYPE_TRAITS_POD_SPECIALIZE(const _Type***)
# endif

# define __STL_POINTERS_SPECIALIZE(_Type) __STL_TYPE_TRAITS_POD_SPECIALIZE_V(_Type) __STL_ARROW_SPECIALIZE_WITH_PTRS(_Type)

#  if !defined ( __STL_NO_BOOL )
__STL_POINTERS_SPECIALIZE( bool )
#  endif
__STL_TYPE_TRAITS_POD_SPECIALIZE_V(void)
  __STL_ARROW_SPECIALIZE_WITH_PTRS(void*)
  __STL_ARROW_SPECIALIZE_WITH_PTRS(void* const)
# ifndef __STL_NO_SIGNED_BUILTINS
  __STL_POINTERS_SPECIALIZE( signed char )
# endif
  __STL_POINTERS_SPECIALIZE( char )
  __STL_POINTERS_SPECIALIZE( unsigned char )
  __STL_POINTERS_SPECIALIZE( short )
  __STL_POINTERS_SPECIALIZE( unsigned short )
  __STL_POINTERS_SPECIALIZE( int )
  __STL_POINTERS_SPECIALIZE( unsigned int )
  __STL_POINTERS_SPECIALIZE( long )
  __STL_POINTERS_SPECIALIZE( unsigned long )
  __STL_POINTERS_SPECIALIZE( float )
  __STL_POINTERS_SPECIALIZE( double )
#  if !defined ( __STL_NO_LONG_DOUBLE )
  __STL_POINTERS_SPECIALIZE( long double )
#  endif
#  if defined ( __STL_LONG_LONG)
  __STL_POINTERS_SPECIALIZE( __STL_LONG_LONG )
  __STL_POINTERS_SPECIALIZE( unsigned __STL_LONG_LONG )
#  endif
#if defined ( __STL_HAS_WCHAR_T ) && ! defined (__STL_WCHAR_T_IS_USHORT)
  __STL_POINTERS_SPECIALIZE( wchar_t )
#  endif

# undef __STL_ARROW_SPECIALIZE
# undef __STL_ARROW_SPECIALIZE_WITH_PTRS
  // # undef __STL_POINTERS_SPECIALIZE
  // # undef __STL_TYPE_TRAITS_POD_SPECIALIZE
# undef __STL_TYPE_TRAITS_POD_SPECIALIZE_V

#endif
