/*
 *
 * Copyright (c) 2003
 * François Dumont
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


#ifndef _STLP_TYPE_MANIPS_H
#define _STLP_TYPE_MANIPS_H

_STLP_BEGIN_NAMESPACE

struct __true_type {};
struct __false_type {};

//bool to type
template <int _Is> struct __bool2type {
  typedef __false_type _Ret; 
};

_STLP_TEMPLATE_NULL
struct __bool2type<1> { typedef __true_type _Ret; };

_STLP_TEMPLATE_NULL
struct __bool2type<0> { typedef __false_type _Ret; };

//type to bool
template <class __bool_type>
struct __type2bool {
  enum {_Ret = 1};
};

_STLP_TEMPLATE_NULL
struct __type2bool<__true_type> {
  enum {_Ret = 1};
};

_STLP_TEMPLATE_NULL
struct __type2bool<__false_type> {
  enum {_Ret = 0};
};

// logical and of 2 predicated
template <class _P1, class _P2>
struct _Land2 {
  typedef __false_type _Ret;
};

_STLP_TEMPLATE_NULL
struct _Land2<__true_type, __true_type> {
  typedef __true_type _Ret;
};

// logical and of 3 predicated
template <class _P1, class _P2, class _P3>
struct _Land3 {
  typedef __false_type _Ret;
};

_STLP_TEMPLATE_NULL
struct _Land3<__true_type, __true_type, __true_type> {
  typedef __true_type _Ret;
};

//logical or of 2 predicated
template <class _P1, class _P2>
struct _Lor2 {
	typedef __true_type _Ret;
};

template<>
struct _Lor2<__false_type, __false_type> {
	typedef __false_type _Ret;
};

// logical or of 3 predicated
template <class _P1, class _P2, class _P3>
struct _Lor3 {
  typedef __true_type _Ret;
};

_STLP_TEMPLATE_NULL
struct _Lor3<__false_type, __false_type, __false_type> {
  typedef __false_type _Ret;
};

////////////////////////////////////////////////////////////////////////////////
// class template __select
// Selects one of two types based upon a boolean constant
// Invocation: __select<_Cond, T, U>::Result
// where:
// flag is a compile-time boolean constant
// T and U are types
// Result evaluates to T if flag is true, and to U otherwise.
////////////////////////////////////////////////////////////////////////////////
// BEWARE: If the compiler do not support partial template specialization or nested template
//classes the default behavior of the __select is to concider the condition as false and so return 
//the second template type!!

#ifdef _STLP_CLASS_PARTIAL_SPECIALIZATION
template <int _Cond, class _Tp1, class _Tp2>
struct __select {
  typedef _Tp1 _Ret;
};

template <class _Tp1, class _Tp2>
struct __select<0, _Tp1, _Tp2> {
  typedef _Tp2 _Ret;
};

#else /* _STLP_CLASS_PARTIAL_SPECIALIZATION */

#  ifdef _STLP_MEMBER_TEMPLATE_CLASSES
template <int _Cond>
struct __select_aux {
  template <class _Tp1, class _Tp2>
  struct _In {
    typedef _Tp1 _Ret;
  };
};

_STLP_TEMPLATE_NULL
struct __select_aux<0> {
  template <class _Tp1, class _Tp2>
  struct _In {
    typedef _Tp2 _Ret;
  };
};

template <int _Cond, class _Tp1, class _Tp2>
struct __select {
  typedef typename __select_aux<_Cond>::_STLP_TEMPLATE _In<_Tp1, _Tp2>::_Ret _Ret;
};
#  else /* _STLP_MEMBER_TEMPLATE_CLASSES */
//default behavior
template <int _Cond, class _Tp1, class _Tp2>
struct __select {
  typedef _Tp2 _Ret;
};
#  endif /* _STLP_MEMBER_TEMPLATE_CLASSES */

#endif /* _STLP_CLASS_PARTIAL_SPECIALIZATION */

# ifdef _STLP_SIMULATE_PARTIAL_SPEC_FOR_TYPE_TRAITS
// Boris : simulation technique is used here according to Adobe Open Source License Version 1.0.
// Copyright 2000 Adobe Systems Incorporated and others. All rights reserved.
// Authors: Mat Marcus and Jesse Jones
// The original version of this source code may be found at
// http://opensource.adobe.com.

// These are the discriminating functions
template <class _Tp>
char _STLP_CALL _IsSameFun(bool, _Tp*, _Tp*); // no implementation is required
char* _STLP_CALL _IsSameFun(bool, ...);       // no implementation is required

template <class _Tp1, class _Tp2>
struct _IsSame {
  static _Tp1* __null_rep1();
  static _Tp2* __null_rep2();
  enum { _Ret = (sizeof(_IsSameFun(false,__null_rep1(),__null_rep2())) == sizeof(char)) };
};

# else /* _STLP_SIMULATE_PARTIAL_SPEC_FOR_TYPE_TRAITS */

template <class _Tp1, class _Tp2>
struct _IsSame { enum { _Ret = 0 }; };

// template <class _Tp1, class _Tp2>
// struct _IsSameType {   static __false_type _Ret() { return __false_type(); }  };

#  ifdef _STLP_CLASS_PARTIAL_SPECIALIZATION

template <class _Tp>
struct _IsSame<_Tp, _Tp> { enum { _Ret = 1 }; };

#  endif /* _STLP_CLASS_PARTIAL_SPECIALIZATION */

# endif /* _STLP_SIMULATE_PARTIAL_SPEC_FOR_TYPE_TRAITS */

#if defined(_STLP_USE_PARTIAL_SPEC_WORKAROUND)

template <class _Derived, class _Base>
struct _ConversionHelper {
  static char _Test(bool, _Base*);
  static _Derived* _MakeDerived();
  
  static char* _Test(bool, ...);
};

template <class _Derived, class _Base>
struct _IsConvertible
{
  typedef _ConversionHelper<_Derived, _Base> _H;
  enum {exists = (sizeof(char) == sizeof(_H::_Test(false, _H::_MakeDerived()))) };
};


template <class _Derived, class _Base>
struct _IsConvertibleType {
  enum {exists = _IsConvertible<_Derived, _Base>::exists};
  typedef __bool2type< exists > _BT;
  typedef typename _BT::_Ret _Type;
};

#endif /* _STLP_USE_PARTIAL_SPEC_WORKAROUND */

_STLP_END_NAMESPACE

#endif /* _STLP_TYPE_MANIPS_H */
