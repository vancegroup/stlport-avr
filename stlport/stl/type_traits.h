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

#ifndef _STLP_TYPE_TRAITS_H
#define _STLP_TYPE_TRAITS_H

/*
This header file provides a framework for allowing compile time dispatch
based on type attributes. This is useful when writing template code.
For example, when making a copy of an array of an unknown type, it helps
to know if the type has a trivial copy constructor or not, to help decide
if a memcpy can be used.

The class template __type_traits provides a series of typedefs each of
which is either __true_type or __false_type. The argument to
__type_traits can be any type. The typedefs within this template will
attain their correct values by one of these means:
    1. The general instantiation contain conservative values which work
       for all types.
    2. Specializations may be declared to make distinctions between types.
    3. Some compilers (such as the Silicon Graphics N32 and N64 compilers)
       will automatically provide the appropriate specializations for all
       types.

EXAMPLE:

//Copy an array of elements which have non-trivial copy constructors
template <class T> void copy(T* source, T* destination, int n, __false_type);
//Copy an array of elements which have trivial copy constructors. Use memcpy.
template <class T> void copy(T* source, T* destination, int n, __true_type);

//Copy an array of any type by using the most efficient copy mechanism
template <class T> inline void copy(T* source,T* destination,int n) {
   copy(source, destination, n,
        typename __type_traits<T>::has_trivial_copy_constructor());
}
*/

#ifdef __WATCOMC__
#  include <stl/_mbstate_t.h>
#endif

#ifndef _STLP_TYPE_MANIPS_H
#  include <stl/type_manips.h>
#endif

#ifdef _STLP_USE_BOOST_SUPPORT
#  include <stl/boost_type_traits.h>
#  include <boost/type_traits/add_reference.hpp>
#  include <boost/type_traits/add_const.hpp>
#endif /* _STLP_USE_BOOST_SUPPORT */

_STLP_BEGIN_NAMESPACE

#if !defined (_STLP_USE_BOOST_SUPPORT)

// The following could be written in terms of numeric_limits.
// We're doing it separately to reduce the number of dependencies.

template <class _Tp> struct _Is_integer {
  typedef __false_type _Integral;
};

#  ifndef _STLP_NO_BOOL
_STLP_TEMPLATE_NULL struct _Is_integer<bool> {
  typedef __true_type _Integral;
};
#  endif /* _STLP_NO_BOOL */

_STLP_TEMPLATE_NULL struct _Is_integer<char> {
  typedef __true_type _Integral;
};

#  ifndef _STLP_NO_SIGNED_BUILTINS
_STLP_TEMPLATE_NULL struct _Is_integer<signed char> {
  typedef __true_type _Integral;
};
#  endif

_STLP_TEMPLATE_NULL struct _Is_integer<unsigned char> {
  typedef __true_type _Integral;
};

#  if defined ( _STLP_HAS_WCHAR_T ) && ! defined (_STLP_WCHAR_T_IS_USHORT)
_STLP_TEMPLATE_NULL struct _Is_integer<wchar_t> {
  typedef __true_type _Integral;
};
#  endif /* _STLP_HAS_WCHAR_T */

_STLP_TEMPLATE_NULL struct _Is_integer<short> {
  typedef __true_type _Integral;
};

_STLP_TEMPLATE_NULL struct _Is_integer<unsigned short> {
  typedef __true_type _Integral;
};

_STLP_TEMPLATE_NULL struct _Is_integer<int> {
  typedef __true_type _Integral;
};

_STLP_TEMPLATE_NULL struct _Is_integer<unsigned int> {
  typedef __true_type _Integral;
};

_STLP_TEMPLATE_NULL struct _Is_integer<long> {
  typedef __true_type _Integral;
};

_STLP_TEMPLATE_NULL struct _Is_integer<unsigned long> {
  typedef __true_type _Integral;
};

#  ifdef _STLP_LONG_LONG
_STLP_TEMPLATE_NULL struct _Is_integer<_STLP_LONG_LONG> {
  typedef __true_type _Integral;
};

_STLP_TEMPLATE_NULL struct _Is_integer<unsigned _STLP_LONG_LONG> {
  typedef __true_type _Integral;
};
#  endif /* _STLP_LONG_LONG */

template <class _Tp> struct _Is_rational {
  typedef __false_type _Rational;
};

_STLP_TEMPLATE_NULL struct _Is_rational<float> {
  typedef __true_type _Rational;
};

_STLP_TEMPLATE_NULL struct _Is_rational<double> {
  typedef __true_type _Rational;
};

#  if !defined ( _STLP_NO_LONG_DOUBLE )
_STLP_TEMPLATE_NULL struct _Is_rational<long double> {
  typedef __true_type _Rational;
};
#  endif

// Forward declarations.
template <class _Tp> struct __type_traits;
template <class _IsPOD> struct __type_traits_aux {
   typedef __false_type    has_trivial_default_constructor;
   typedef __false_type    has_trivial_copy_constructor;
   typedef __false_type    has_trivial_assignment_operator;
   typedef __false_type    has_trivial_destructor;
   typedef __false_type    is_POD_type;
};

_STLP_TEMPLATE_NULL
struct __type_traits_aux<__false_type> {
   typedef __false_type    has_trivial_default_constructor;
   typedef __false_type    has_trivial_copy_constructor;
   typedef __false_type    has_trivial_assignment_operator;
   typedef __false_type    has_trivial_destructor;
   typedef __false_type    is_POD_type;
};

_STLP_TEMPLATE_NULL
struct __type_traits_aux<__true_type> {
  typedef __true_type    has_trivial_default_constructor;
  typedef __true_type    has_trivial_copy_constructor;
  typedef __true_type    has_trivial_assignment_operator;
  typedef __true_type    has_trivial_destructor;
  typedef __true_type    is_POD_type;
};

template <class _Tp>
struct _IsRef {
  typedef __false_type _Ret;
};

#  if defined (_STLP_SIMULATE_PARTIAL_SPEC_FOR_TYPE_TRAITS)
/*
 * Boris : simulation technique is used here according to Adobe Open Source License Version 1.0.
 * Copyright 2000 Adobe Systems Incorporated and others. All rights reserved.
 * Authors: Mat Marcus and Jesse Jones
 * The original version of this source code may be found at
 * http://opensource.adobe.com.
 */

struct _PointerShim {
  /*
   * Since the compiler only allows at most one non-trivial
   * implicit conversion we can make use of a shim class to
   * be sure that IsPtr below doesn't accept classes with
   * implicit pointer conversion operators
   */
  _PointerShim(const volatile void*); // no implementation
};

// These are the discriminating functions
char _STLP_CALL _IsP(bool, _PointerShim);  // no implementation is required
char* _STLP_CALL _IsP(bool, ...);          // no implementation is required

template <class _Tp>
struct _IsPtr {
  /*
   * This template meta function takes a type T
   * and returns true exactly when T is a pointer.
   * One can imagine meta-functions discriminating on
   * other criteria.
   */
  static _Tp& __null_rep();
  enum { _Ptr = (sizeof(_IsP(false,__null_rep())) == sizeof(char)) };
  typedef typename __bool2type<_Ptr>::_Ret _Ret;

};

template <class _Tp>
struct _IsPtrType {
  typedef typename _IsPtr<_Tp>::_Ret _Type;
  static _Type _Ret() { return _Type(); }
};

template <class _Tp1, class _Tp2>
struct _BothPtrType {
  typedef typename _IsPtr<_Tp1>::_Ret _Type1;
  typedef typename _IsPtr<_Tp2>::_Ret _Type2;

  typedef typename _Land2<_Type1, _Type2>::_Ret _Type;
  static _Type _Ret() { return _Type(); }
};

// we make general case dependant on the fact the type is actually a pointer.
template <class _Tp>
struct __type_traits : __type_traits_aux<typename _IsPtr<_Tp>::_Ret> {};

#  else /* _STLP_SIMULATE_PARTIAL_SPEC_FOR_TYPE_TRAITS */

template <class _Tp>  struct _IsPtr {
  typedef __false_type _Ret;
};

template <class _Tp>
struct __type_traits {
   typedef __true_type     this_dummy_member_must_be_first;
                   /* Do not remove this member. It informs a compiler which
                      automatically specializes __type_traits that this
                      __type_traits template is special. It just makes sure that
                      things work if an implementation is using a template
                      called __type_traits for something unrelated. */

   /* The following restrictions should be observed for the sake of
      compilers which automatically produce type specific specializations
      of this class:
          - You may reorder the members below if you wish
          - You may remove any of the members below if you wish
          - You must not rename members without making the corresponding
            name change in the compiler
          - Members you add will be treated like regular members unless

            you add the appropriate support in the compiler. */
#  if !defined (_STLP_HAS_TYPE_TRAITS_INTRINSICS)
   typedef __false_type    has_trivial_default_constructor;
   typedef __false_type    has_trivial_copy_constructor;
   typedef __false_type    has_trivial_assignment_operator;
   typedef __false_type    has_trivial_destructor;
   typedef __false_type    is_POD_type;
#  else
   typedef typename __bool2type<_STLP_HAS_TRIVIAL_CONSTRUCTOR(_Tp)>::_Ret has_trivial_default_constructor;
   typedef typename __bool2type<_STLP_HAS_TRIVIAL_COPY(_Tp)>::_Ret has_trivial_copy_constructor;
   typedef typename __bool2type<_STLP_HAS_TRIVIAL_ASSIGN(_Tp)>::_Ret has_trivial_assignment_operator;
   typedef typename __bool2type<_STLP_HAS_TRIVIAL_DESTRUCTOR(_Tp)>::_Ret has_trivial_destructor;
   typedef typename __bool2type<_STLP_IS_POD(_Tp)>::_Ret is_POD_type;
#  endif
};

#    if defined (_STLP_CLASS_PARTIAL_SPECIALIZATION)
template <class _Tp> struct _IsPtr<_Tp*> {
  typedef __true_type _Ret;
};
template <class _Tp> struct _IsRef<_Tp&> {
  typedef __true_type _Ret;
};

template <class _Tp> struct __type_traits<_Tp*> : __type_traits_aux<__true_type> {};
#    endif /* _STLP_CLASS_PARTIAL_SPECIALIZATION */

template <class _Tp>  struct _IsPtrType {
  typedef typename _IsPtr<_Tp>::_Ret _Type;
  static _Type _Ret() { return _Type();}
};
template <class _Tp1, class _Tp2>  struct _BothPtrType {
  typedef typename _IsPtr<_Tp1>::_Ret _IsPtr1;
  typedef typename _IsPtr<_Tp2>::_Ret _IsPtr2;
  typedef typename _Land2<_IsPtr1, _IsPtr2>::_Ret _Type;
  static _Type _Ret() { return _Type();}
};

#  endif /* _STLP_SIMULATE_PARTIAL_SPEC_FOR_TYPE_TRAITS */

// Provide some specializations.  This is harmless for compilers that
//  have built-in __types_traits support, and essential for compilers
//  that don't.
#if !defined (_STLP_QUALIFIED_SPECIALIZATION_BUG)
#  define _STLP_DEFINE_TYPE_TRAITS_FOR(Type) \
_STLP_TEMPLATE_NULL struct __type_traits< Type > : __type_traits_aux<__true_type> {}; \
_STLP_TEMPLATE_NULL struct __type_traits< const Type > : __type_traits_aux<__true_type> {}; \
_STLP_TEMPLATE_NULL struct __type_traits< volatile Type > : __type_traits_aux<__true_type> {}; \
_STLP_TEMPLATE_NULL struct __type_traits< const volatile Type > : __type_traits_aux<__true_type> {}
#else
#  define _STLP_DEFINE_TYPE_TRAITS_FOR(Type) \
_STLP_TEMPLATE_NULL struct __type_traits< Type > : __type_traits_aux<__true_type> {};
#endif

#  ifndef _STLP_NO_BOOL
_STLP_DEFINE_TYPE_TRAITS_FOR(bool);
#  endif /* _STLP_NO_BOOL */
_STLP_DEFINE_TYPE_TRAITS_FOR(char);
#  ifndef _STLP_NO_SIGNED_BUILTINS
_STLP_DEFINE_TYPE_TRAITS_FOR(signed char);
#  endif
_STLP_DEFINE_TYPE_TRAITS_FOR(unsigned char);
#  if defined ( _STLP_HAS_WCHAR_T ) && ! defined (_STLP_WCHAR_T_IS_USHORT)
_STLP_DEFINE_TYPE_TRAITS_FOR(wchar_t);
#  endif /* _STLP_HAS_WCHAR_T */

_STLP_DEFINE_TYPE_TRAITS_FOR(short);
_STLP_DEFINE_TYPE_TRAITS_FOR(unsigned short);
_STLP_DEFINE_TYPE_TRAITS_FOR(int);
_STLP_DEFINE_TYPE_TRAITS_FOR(unsigned int);
_STLP_DEFINE_TYPE_TRAITS_FOR(long);
_STLP_DEFINE_TYPE_TRAITS_FOR(unsigned long);

#  ifdef _STLP_LONG_LONG
_STLP_DEFINE_TYPE_TRAITS_FOR(_STLP_LONG_LONG);
_STLP_DEFINE_TYPE_TRAITS_FOR(unsigned _STLP_LONG_LONG);
#  endif /* _STLP_LONG_LONG */

_STLP_DEFINE_TYPE_TRAITS_FOR(float);
_STLP_DEFINE_TYPE_TRAITS_FOR(double);

#  if !defined ( _STLP_NO_LONG_DOUBLE )
_STLP_DEFINE_TYPE_TRAITS_FOR(long double);
#  endif

template <class _Tp1, class _Tp2>
struct _OKToMemCpy {
  typedef typename __type_traits<_Tp1>::has_trivial_assignment_operator _Tr1;
  typedef typename _AreSameUnCVTypes<_Tp1, _Tp2>::_Ret _Tr2;
  typedef typename _Land2<_Tr1, _Tr2>::_Ret _Type;
  static _Type _Answer() { return _Type(); }
};

template <class _Tp>
struct _TrivialUCopy {
  typedef typename __type_traits<_Tp>::has_trivial_copy_constructor _Tr1;
  typedef typename __type_traits<_Tp>::has_trivial_assignment_operator _Tr2;
  typedef typename _Land2<_Tr1, _Tr2>::_Ret _Ret;
};

template <class _Tp1, class _Tp2>
struct _TrivialUCopyAux {
  typedef typename _TrivialUCopy<_Tp1>::_Ret _Tr1;
  typedef typename _AreSameUnCVTypes<_Tp1, _Tp2>::_Ret _Tr2;
  typedef typename _Land2<_Tr1, _Tr2>::_Ret _Type;
  static _Type _Answer() { return _Type(); }
};

#if defined (_STLP_DEF_CONST_DEF_PARAM_BUG) || defined (_STLP_DEF_CONST_PLCT_NEW_BUG)
template <class _Tp>
struct _DefaultZeroValue {
  typedef typename _Is_integer<_Tp>::_Integral _Tr1;
  typedef typename _Is_rational<_Tp>::_Rational _Tr2;

  typedef typename _Lor2<_Tr1, _Tr2>::_Ret _Tr3;
  typedef typename _IsPtr<_Tp>::_Ret _Tr4;

  typedef typename _Lor2<_Tr3, _Tr4>::_Ret _Type;
  static _Type _Answer() { return _Type(); }
};
#endif

#endif /* !_STLP_USE_BOOST_SUPPORT */

template <class _Tp>
struct _IsRefType {
  typedef typename _IsRef<_Tp>::_Ret _Type;
  static _Type _Ret() { return _Type();}
};

template <class _Tp>
struct __call_traits {
#if defined(_STLP_USE_BOOST_SUPPORT) && !defined(_STLP_NO_EXTENSIONS)
  typedef typename __select< ::boost::is_reference<_Tp>::value,
                             _Tp, typename ::boost::add_reference< typename ::boost::add_const<_Tp>::type >::type>::_Ret param_type;
#else
  typedef const _Tp& param_type;
#endif /* _STLP_USE_BOOST_SUPPORT */
};

#if !defined(_STLP_USE_BOOST_SUPPORT) && !defined(_STLP_NO_EXTENSIONS) && defined(_STLP_CLASS_PARTIAL_SPECIALIZATION)
template <class _Tp>
struct __call_traits<_Tp&> {
  typedef _Tp& param_type;
};
#endif

template <class _Tp1, class _Tp2>
inline _OKToMemCpy<_Tp1, _Tp2> _IsOKToMemCpy(_Tp1*, _Tp2*) {
  return _OKToMemCpy<_Tp1, _Tp2>();
}

template <class _Tp1, class _Tp2, class _IsRef1, class _IsRef2>
struct _OKToSwap {
  typedef typename _AreSameUnCVTypes<_Tp1, _Tp2>::_Ret _Same;
  typedef typename _Land3<_Same, _IsRef1, _IsRef2>::_Ret _Type;
  static _Type _Answer() { return _Type(); }
};

template <class _Tp1, class _Tp2, class _IsRef1, class _IsRef2>
inline _OKToSwap<_Tp1, _Tp2, _IsRef1, _IsRef2>
_IsOKToSwap(_Tp1*, _Tp2*, const _IsRef1&, const _IsRef2&) {
  return _OKToSwap<_Tp1, _Tp2, _IsRef1, _IsRef2>();
}

template <class _Tp1, class _Tp2>
inline _TrivialUCopyAux<_Tp1, _Tp2> _UseTrivialUCopy(_Tp1*, _Tp2*)  {
  return _TrivialUCopyAux<_Tp1, _Tp2>();
}

template <class _Tp>
struct _IsPOD {
  typedef typename __type_traits<_Tp>::is_POD_type _Type;
  static _Type _Answer() { return _Type(); }
};

template <class _Tp>
inline _IsPOD<_Tp>  _Is_POD (_Tp*) { return _IsPOD<_Tp>(); }

#if defined (_STLP_DEF_CONST_DEF_PARAM_BUG) || defined (_STLP_DEF_CONST_PLCT_NEW_BUG)
template <class _Tp>
inline _DefaultZeroValue<_Tp> _HasDefaultZeroValue(_Tp*) {
  return _DefaultZeroValue<_Tp>();
}
#endif

/*
 * Base class used:
 * - to simulate partial template specialization
 * - to simulate partial function ordering
 * - to recognize STLport class from user specialized one
 */
template <class _Tp>
struct __stlport_class {
  typedef _Tp _Type;
};

template <class _Tp>
struct _IsSTLportClass {
  typedef typename _IsConvertibleType<_Tp, __stlport_class<_Tp> >::_Type _Ret;
};

#if defined (_STLP_USE_PARTIAL_SPEC_WORKAROUND) && !defined (_STLP_FUNCTION_TMPL_PARTIAL_ORDER)
template <class _Tp>
struct _SwapImplemented {
  typedef typename _IsSTLportClass<_Tp>::_Ret _Ret;
};
#endif /* _STLP_USE_PARTIAL_SPEC_WORKAROUND */

_STLP_END_NAMESPACE

#ifdef _STLP_CLASS_PARTIAL_SPECIALIZATION
#  if defined (__BORLANDC__) || \
      defined (__SUNPRO_CC) ||  \
     (defined (__MWERKS__) && (__MWERKS__ <= 0x2303)) || \
     (defined (__sgi) && defined (_COMPILER_VERSION)) || \
      defined (__DMC__)
#    define _STLP_IS_POD_ITER(_It, _Tp) __type_traits< typename iterator_traits< _Tp >::value_type >::is_POD_type()
#  else
#    define _STLP_IS_POD_ITER(_It, _Tp) typename __type_traits< typename iterator_traits< _Tp >::value_type >::is_POD_type()
#  endif
#else
#  define _STLP_IS_POD_ITER(_It, _Tp) _Is_POD( _STLP_VALUE_TYPE( _It, _Tp ) )._Answer()
#endif

#endif /* _STLP_TYPE_TRAITS_H */

// Local Variables:
// mode:C++
// End:
