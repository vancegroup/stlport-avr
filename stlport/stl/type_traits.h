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
# include <stl/_cwchar.h>
#endif

#ifndef _STLP_TYPE_MANIPS_H
# include <stl/type_manips.h>
#endif

_STLP_BEGIN_NAMESPACE

// The following could be written in terms of numeric_limits.  
// We're doing it separately to reduce the number of dependencies.

template <class _Tp> struct _Is_integer {
  typedef __false_type _Integral;
};

#ifndef _STLP_NO_BOOL

_STLP_TEMPLATE_NULL struct _Is_integer<bool> {
  typedef __true_type _Integral;
};

#endif /* _STLP_NO_BOOL */

_STLP_TEMPLATE_NULL struct _Is_integer<char> {
  typedef __true_type _Integral;
};

#ifndef _STLP_NO_SIGNED_BUILTINS

_STLP_TEMPLATE_NULL struct _Is_integer<signed char> {
  typedef __true_type _Integral;
};
#endif

_STLP_TEMPLATE_NULL struct _Is_integer<unsigned char> {
  typedef __true_type _Integral;
};

#if defined ( _STLP_HAS_WCHAR_T ) && ! defined (_STLP_WCHAR_T_IS_USHORT)

_STLP_TEMPLATE_NULL struct _Is_integer<wchar_t> {
  typedef __true_type _Integral;
};

#endif /* _STLP_HAS_WCHAR_T */

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

#ifdef _STLP_LONG_LONG

_STLP_TEMPLATE_NULL struct _Is_integer<_STLP_LONG_LONG> {
  typedef __true_type _Integral;
};

_STLP_TEMPLATE_NULL struct _Is_integer<unsigned _STLP_LONG_LONG> {
  typedef __true_type _Integral;
};

#endif /* _STLP_LONG_LONG */

template <class _Tp> struct _Is_rational {
  typedef __false_type _Rational;
};

_STLP_TEMPLATE_NULL struct _Is_rational<float> {
  typedef __true_type _Rational;
};

_STLP_TEMPLATE_NULL struct _Is_rational<double> {
  typedef __true_type _Rational;
};

# if !defined ( _STLP_NO_LONG_DOUBLE )
_STLP_TEMPLATE_NULL struct _Is_rational<long double> {
  typedef __true_type _Rational;
};
# endif

// Forward declarations.
template <class _Tp> struct __type_traits; 
template <int _IsPOD> struct __type_traits_aux {
   typedef __false_type    has_trivial_default_constructor;
   typedef __false_type    has_trivial_copy_constructor;
   typedef __false_type    has_trivial_assignment_operator;
   typedef __false_type    has_trivial_destructor;
   typedef __false_type    is_POD_type;
};

_STLP_TEMPLATE_NULL
struct __type_traits_aux<0> {
   typedef __false_type    has_trivial_default_constructor;
   typedef __false_type    has_trivial_copy_constructor;
   typedef __false_type    has_trivial_assignment_operator;
   typedef __false_type    has_trivial_destructor;
   typedef __false_type    is_POD_type;
};

_STLP_TEMPLATE_NULL
struct __type_traits_aux<1> { 
   typedef __true_type    has_trivial_default_constructor;
   typedef __true_type    has_trivial_copy_constructor;
   typedef __true_type    has_trivial_assignment_operator;
   typedef __true_type    has_trivial_destructor;
   typedef __true_type    is_POD_type;
};

# ifdef _STLP_SIMULATE_PARTIAL_SPEC_FOR_TYPE_TRAITS
// Boris : simulation technique is used here according to Adobe Open Source License Version 1.0.
// Copyright 2000 Adobe Systems Incorporated and others. All rights reserved.
// Authors: Mat Marcus and Jesse Jones
// The original version of this source code may be found at
// http://opensource.adobe.com.

struct _PointerShim {
  // Since the compiler only allows at most one non-trivial
  // implicit conversion we can make use of a shim class to
  // be sure that IsPtr below doesn't accept classes with
  // implicit pointer conversion operators
  _PointerShim(const volatile void*); // no implementation
};

// These are the discriminating functions
char _STLP_CALL _IsP(bool, _PointerShim);  // no implementation is required
char* _STLP_CALL _IsP(bool, ...);          // no implementation is required

template <class _Tp>
struct _IsPtr {
  
  // This template meta function takes a type T
  // and returns true exactly when T is a pointer.
  // One can imagine meta-functions discriminating on
  // other criteria.
  static _Tp& __null_rep();
  enum { _Ret = (sizeof(_IsP(false,__null_rep())) == sizeof(char)) };
};

#if defined (_STLP_MEMBER_TEMPLATE_CLASSES)
//This class avoid instanciation of the more complex class _IsPtr when _BoolType is __false_type
template <class _CondT>
struct _IsPtrCondAux { /*__false_type*/
  template <class _Tp>
  struct _In {
    enum { _Ret = 0 };
  };
};

_STLP_TEMPLATE_NULL
struct _IsPtrCondAux <__true_type> {
  template <class _Tp>
  struct _In {
    enum { _Ret = _IsPtr<_Tp>::_Ret };
  };
};

template <class _CondT, class _Tp>
struct _IsPtrCond {
  enum { _Ret = _IsPtrCondAux<_CondT>::_STLP_TEMPLATE _In<_Tp>::_Ret };
};

//Idem _IsPtrAux but won't instanciate _IsPtr if _BoolType is __true_type
template <typename _CondT>
struct _IsPtrCondNotAux { /*__true_type*/
  template <class _Tp>
  struct _In {
    enum { _Ret = 1 };
  };
};

_STLP_TEMPLATE_NULL
struct _IsPtrCondNotAux <__false_type> {
  template <class _Tp>
  struct _In {
    enum { _Ret = _IsPtr<_Tp>::_Ret };
  };
};

template <class _CondT, class _Tp>
struct _IsPtrCondNot {
  enum { _Ret = _IsPtrCondNotAux<_CondT>::_STLP_TEMPLATE _In<_Tp>::_Ret };
};

#else /* _STLP_MEMBER_TEMPLATE_CLASSES */
template <class _CondT, class _Tp>
struct _IsPtrCond {
  enum { _Ret = _IsPtr<_Tp>::_Ret };
};

template <class _CondT, class _Tp>
struct _IsPtrCondNot {
  enum { _Ret = _IsPtr<_Tp>::_Ret };
};
#endif /* _STLP_MEMBER_TEMPLATE_CLASSES */

template <class _Tp>
struct _IsPtrType {
#if defined (_STLP_MEMBER_TEMPLATE_CLASSES)
  typedef typename _Is_integer<_Tp>::_Integral _Tr1;
  typedef typename _Is_rational<_Tp>::_Rational _Tr2;

  typedef typename _Lor2<_Tr1, _Tr2>::_Ret _Tr3;

  enum { _Is = _IsPtrCond<_Tr3, _Tp>::_Ret } ;
#else
  enum { _Is =  _IsPtr<_Tp>::_Ret } ;
#endif /* _STLP_MEMBER_TEMPLATE_CLASSES */
  typedef __bool2type< _Is > _BT;
  typedef typename _BT::_Ret _Type;
  static _Type _Ret() { return _Type(); }
};

template <class _Tp1, class _Tp2>
struct _BothPtrType {
#if defined (_STLP_MEMBER_TEMPLATE_CLASSES)
  typedef typename _Is_integer<_Tp1>::_Integral _Tr11;
  typedef typename _Is_rational<_Tp1>::_Rational _Tr12;

  typedef typename _Lor2<_Tr11, _Tr12>::_Ret _Tr13;

  enum { _Is1 = _IsPtrCond<_Tr13, _Tp1>::_Ret } ;
#else
  enum { _Is1 =  _IsPtr<_Tp1>::_Ret } ;
#endif /* _STLP_MEMBER_TEMPLATE_CLASSES */
  typedef __bool2type<_Is1> _B1;
  typedef typename _B1::_Ret _Type1;

#if defined (_STLP_MEMBER_TEMPLATE_CLASSES)
  typedef typename _Is_integer<_Tp2>::_Integral _Tr21;
  typedef typename _Is_rational<_Tp2>::_Rational _Tr22;

  typedef typename _Lor2<_Tr21, _Tr22>::_Ret _Tr23;
  typedef typename _Land2<_Tr23, _Type1>::_Ret _Tr24;

  enum { _Is2 = _IsPtrCond<_Tr24, _Tp2>::_Ret } ;
#else
  enum { _Is2 =  _IsPtrCond<_Type1, _Tp2>::_Ret } ;
#endif /* _STLP_MEMBER_TEMPLATE_CLASSES */
  typedef __bool2type< _IsPtr<_Tp2>::_Ret> _B2;
  typedef typename _B2::_Ret _Type2;

  typedef typename _Land2<_Type1, _Type2>::_Ret _Type;
  static _Type _Ret() { return _Type(); }
};

// we make general case dependant on the fact the type is actually a pointer.
template <class _Tp>
struct __type_traits : __type_traits_aux<_IsPtr<_Tp>::_Ret> {};

# else /* _STLP_SIMULATE_PARTIAL_SPEC_FOR_TYPE_TRAITS */

template <class _Tp>  struct _IsPtr { enum { _Ret = 0 }; };
template <class _Tp>  struct _IsPtrType { 
  static __false_type _Ret() { return __false_type();} 
};
template <class _Tp1, class _Tp2>  struct _BothPtrType { 
  static __false_type _Ret() { return __false_type();} 
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
   typedef __false_type    has_trivial_default_constructor;
   typedef __false_type    has_trivial_copy_constructor;
   typedef __false_type    has_trivial_assignment_operator;
   typedef __false_type    has_trivial_destructor;
   typedef __false_type    is_POD_type;
};

#  ifdef _STLP_CLASS_PARTIAL_SPECIALIZATION
template <class _Tp>  struct _IsPtr<_Tp*> { enum { _Ret = 1 }; };
template <class _Tp>  struct _IsPtrType<_Tp*> { 
  static __true_type _Ret() { return __true_type();} 
};
template <class _Tp1, class _Tp2>  struct _BothPtrType<_Tp1*, _Tp2*> { 
  static __true_type _Ret() { return __true_type();} 
};

template <class _Tp> struct __type_traits<_Tp*> : __type_traits_aux<1> {};
#  endif /* _STLP_CLASS_PARTIAL_SPECIALIZATION */

# endif /* _STLP_SIMULATE_PARTIAL_SPEC_FOR_TYPE_TRAITS */

// Provide some specializations.  This is harmless for compilers that
//  have built-in __types_traits support, and essential for compilers
//  that don't.
#ifndef _STLP_NO_BOOL
_STLP_TEMPLATE_NULL struct __type_traits<bool> : __type_traits_aux<1> {};
#endif /* _STLP_NO_BOOL */
_STLP_TEMPLATE_NULL struct __type_traits<char> : __type_traits_aux<1> {};
#ifndef _STLP_NO_SIGNED_BUILTINS
_STLP_TEMPLATE_NULL struct __type_traits<signed char> : __type_traits_aux<1> {};
# endif
_STLP_TEMPLATE_NULL struct __type_traits<unsigned char> : __type_traits_aux<1> {};
#if defined ( _STLP_HAS_WCHAR_T ) && ! defined (_STLP_WCHAR_T_IS_USHORT)
_STLP_TEMPLATE_NULL struct __type_traits<wchar_t> : __type_traits_aux<1> {};
#endif /* _STLP_HAS_WCHAR_T */

_STLP_TEMPLATE_NULL struct __type_traits<short> : __type_traits_aux<1> {};
_STLP_TEMPLATE_NULL struct __type_traits<unsigned short> : __type_traits_aux<1> {};
_STLP_TEMPLATE_NULL struct __type_traits<int> : __type_traits_aux<1> {};
_STLP_TEMPLATE_NULL struct __type_traits<unsigned int> : __type_traits_aux<1> {};
_STLP_TEMPLATE_NULL struct __type_traits<long> : __type_traits_aux<1> {};
_STLP_TEMPLATE_NULL struct __type_traits<unsigned long> : __type_traits_aux<1> {};

#ifdef _STLP_LONG_LONG
_STLP_TEMPLATE_NULL struct __type_traits<_STLP_LONG_LONG> : __type_traits_aux<1> {};
_STLP_TEMPLATE_NULL struct __type_traits<unsigned _STLP_LONG_LONG> : __type_traits_aux<1> {};
#endif /* _STLP_LONG_LONG */

_STLP_TEMPLATE_NULL struct __type_traits<float> : __type_traits_aux<1> {};
_STLP_TEMPLATE_NULL struct __type_traits<double> : __type_traits_aux<1> {};

# if !defined ( _STLP_NO_LONG_DOUBLE )
_STLP_TEMPLATE_NULL struct __type_traits<long double> : __type_traits_aux<1> {};
# endif

template <class _Tp1, class _Tp2>
struct _OKToMemCpy {
  enum { _Same = _IsSame<_Tp1,_Tp2>::_Ret } ;
  typedef typename __type_traits<_Tp1>::has_trivial_assignment_operator _Tr1;
  typedef typename __type_traits<_Tp2>::has_trivial_assignment_operator _Tr2;
  typedef typename __bool2type< _Same >::_Ret _Tr3;
  typedef typename _Land3<_Tr1, _Tr2, _Tr3>::_Ret _Type;
  static _Type _Answer() { return _Type(); }
};

template <class _Tp1, class _Tp2>
inline _OKToMemCpy<_Tp1, _Tp2> _IsOKToMemCpy(_Tp1*, _Tp2*)  {
  return _OKToMemCpy<_Tp1, _Tp2>();
}

template <class _Tp> 
struct _IsPOD {
  typedef typename __type_traits<_Tp>::is_POD_type _Type;
  static _Type _Answer() { return _Type(); }
};

template <class _Tp> 
inline _IsPOD<_Tp>  _Is_POD (_Tp*) { return _IsPOD<_Tp>(); } 

template <class _Tp>
struct _DefaultZeroValue {
  typedef typename _Is_integer<_Tp>::_Integral _Tr1;
  typedef typename _Is_rational<_Tp>::_Rational _Tr2;

  typedef typename _Lor2<_Tr1, _Tr2>::_Ret _Tr3;

#if defined (_STLP_SIMULATE_PARTIAL_SPEC_FOR_TYPE_TRAITS)
  typedef typename __bool2type< _IsPtrCondNot<_Tr3, _Tp>::_Ret>::_Ret _Tr4;
#else
  typedef typename __bool2type< _IsPtr<_Tp>::_Ret>::_Ret _Tr4;
#endif /* !_STLP_CLASS_PARTIAL_SPECIALIZATION && _STLP_MEMBER_TEMPLATE_CLASSES*/

  typedef typename _Lor2<_Tr3, _Tr4>::_Ret _Type;
  static _Type _Answer() { return _Type(); }
};

template <class _Tp>
inline _DefaultZeroValue<_Tp> _HasDefaultZeroValue(_Tp*) {
  return _DefaultZeroValue<_Tp>();
}

/*
 * Base class used for internal purpose to simulate partial template specialization
 * and partial function ordering
 */
#ifdef _STLP_USE_PARTIAL_SPEC_WORKAROUND
class __stlport_class {};
#define _STLP_STLPORT_CLASS_1 : public __stlport_class
#define _STLP_STLPORT_CLASS_N , public __stlport_class

#if defined (_STLP_MEMBER_TEMPLATE_CLASSES)
template <class _CondT>
struct _IsConvertibleCondNotAux { /*__true_type*/
  template <class _Derived, class _Base>
  struct _In {
    typedef __false_type _Ret;
  };
};

_STLP_TEMPLATE_NULL
struct _IsConvertibleCondNotAux<__false_type> {
  template <class _Derived, class _Base>
  struct _In {
    typedef typename _IsConvertibleType<_Derived, _Base>::_Type _Ret;
  };
};

template <class _CondT, class _Derived, class _Base>
struct _IsConvertibleCondNot {
  typedef typename _IsConvertibleCondNotAux<_CondT>::_STLP_TEMPLATE _In<_Derived, _Base>::_Ret _Ret;
};
#endif /* _STLP_MEMBER_TEMPLATE_CLASSES */

template <class _Tp>
struct _IsStlportClass {
#if defined (_STLP_MEMBER_TEMPLATE_CLASSES)
  typedef typename _Is_integer<_Tp>::_Integral _Tr1;
  typedef typename _Is_rational<_Tp>::_Rational _Tr2;
  typedef typename _Lor2<_Tr1, _Tr2>::_Ret _Tr3;

  typedef typename _IsConvertibleCondNot<_Tr3, _Tp, __stlport_class>::_Ret _Ret;
#else
  typedef typename _IsConvertible<_Tp, __stlport_class>::_Type _Ret;
#endif /* _STLP_MEMBER_TEMPLATE_CLASSES */
};

#if defined (_STLP_MEMBER_TEMPLATE_CLASSES)
template <class _CondT>
struct _IsStlportClassCondNotAux { /*__true_type*/
  template <class _Tp>
  struct _In {
    typedef __true_type _Ret;
  };
};

_STLP_TEMPLATE_NULL
struct _IsStlportClassCondNotAux<__false_type> {
  template <class _Tp>
  struct _In {
    typedef typename _IsStlportClass<_Tp>::_Ret _Ret;
  };
};

template <class _CondT, class _Tp>
struct _IsStlportClassCondNot {
  typedef typename _IsStlportClassCondNotAux<_CondT>::_STLP_TEMPLATE _In<_Tp>::_Ret _Ret;
};
#else
template <class _DummyCondT, class _Tp>
struct _IsStlportClassCondNot {
  typedef typename _IsStlportClass<_Tp>::_Ret _Ret;
};
#endif /* _STLP_MEMBER_TEMPLATE_CLASSES */

#else
#define _STLP_STLPORT_CLASS_1
#define _STLP_STLPORT_CLASS_N
#endif /* _STLP_USE_PARTIAL_SPEC_WORKAROUND */

#if defined(_STLP_USE_PARTIAL_SPEC_WORKAROUND) && !defined(_STLP_FUNCTION_TMPL_PARTIAL_ORDER)
template <class _Tp>
struct _SwapImplemented {
  typedef typename _IsStlportClass<_Tp>::_Ret _Ret;
};
#endif /* _STLP_USE_PARTIAL_SPEC_WORKAROUND */

template <class _Tp>
struct __action_on_move {
	typedef __false_type swap;
};

template <class _Tp1, class _Tp2> 
struct _SwapOnMove {
	typedef typename __action_on_move<_Tp1>::swap _Enabled1;
#if defined(_STLP_USE_PARTIAL_SPEC_WORKAROUND) && !defined(_STLP_CLASS_PARTIAL_SPECIALIZATION)
  typedef typename _IsStlportClassCondNot<_Enabled1, _Tp1>::_Ret _Enabled2;
#else
  typedef __false_type _Enabled2;
#endif /* _STLP_USE_PARTIAL_SPEC_WORKAROUND */
	typedef typename _Lor2<_Enabled1, _Enabled2>::_Ret _Enabled;

  enum { _Same = _IsSame<_Tp1,_Tp2>::_Ret };
  typedef typename __bool2type< _Same >::_Ret _SameTypes;

  typedef typename _Land3<_Enabled, _SameTypes, __true_type>::_Ret _Type;
	static _Type _Answer() {return _Type();}
};

template<class _Tp1, class _Tp2>
_SwapOnMove<_Tp1, _Tp2> _DoSwapOnMove (_Tp1*, _Tp2*)
{return _SwapOnMove<_Tp1, _Tp2>();}

#  ifdef _STLP_CLASS_PARTIAL_SPECIALIZATION
#   if defined (__BORLANDC__) || defined (__SUNPRO_CC) || ( defined (__MWERKS__) && (__MWERKS__ <= 0x2303)) || ( defined (__sgi) && defined (_COMPILER_VERSION)) || defined (__DMC__)
#   define _IS_POD_ITER(_It, _Tp) __type_traits< typename iterator_traits< _Tp >::value_type >::is_POD_type()
#   else
#   define _IS_POD_ITER(_It, _Tp) typename __type_traits< typename iterator_traits< _Tp >::value_type >::is_POD_type()
#   endif
#  else
#   define _IS_POD_ITER(_It, _Tp) _Is_POD( _STLP_VALUE_TYPE( _It, _Tp ) )._Answer()
#  endif

_STLP_END_NAMESPACE

#endif /* __TYPE_TRAITS_H */

// Local Variables:
// mode:C++
// End:

