/*
 *
 * Copyright (c) 2004
 * Francois Dumont
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

#ifndef _STLP_BOOST_TYPE_TRAITS_H
#define _STLP_BOOST_TYPE_TRAITS_H

# include <boost/type_traits.hpp>

_STLP_BEGIN_NAMESPACE

template <class _Tp> struct _Is_integer {
  enum { is_integral = ::boost::is_integral<_Tp>::value };
  typedef typename __bool2type<is_integral>::_Ret _Integral;
};

template <class _Tp> struct _Is_rational {
  enum { is_float = ::boost::is_float<_Tp>::value };
  typedef typename __bool2type<is_float>::_Ret _Rational;
};

template <class _Tp>
struct __type_traits {
  enum { trivial_constructor = ::boost::has_trivial_constructor<_Tp>::value };
  typedef typename __bool2type<trivial_constructor>::_Ret has_trivial_default_constructor;

  enum { trivial_copy = ::boost::has_trivial_copy<_Tp>::value };
  typedef typename __bool2type<trivial_copy>::_Ret has_trivial_copy_constructor;

  enum { trivial_assign = ::boost::has_trivial_assign<_Tp>::value };
  typedef typename __bool2type<trivial_assign>::_Ret has_trivial_assignment_operator;

  enum { trivial_destructor = ::boost::has_trivial_destructor<_Tp>::value };
  typedef typename __bool2type<trivial_destructor>::_Ret has_trivial_destructor;

  enum { pod = ::boost::is_pod<_Tp>::value };
  typedef typename __bool2type<pod>::_Ret is_POD_type;
};

template <class _Tp1, class _Tp2>
struct _BothPtrType {
  enum { pointer1 = ::boost::is_pointer<_Tp1>::value };
  enum { pointer2 = ::boost::is_pointer<_Tp2>::value };
  typedef typename __bool2type<pointer1>::_Ret _Type1;
  typedef typename __bool2type<pointer2>::_Ret _Type2;
  
  typedef typename _Land2<_Type1, _Type2>::_Ret _Type;
  static _Type _Ret() { return _Type(); }
};


template <class _Tp1, class _Tp2>
struct _OKToMemCpy {
  typedef typename ::boost::remove_cv<_Tp1>::type uncv1;
  typedef typename ::boost::remove_cv<_Tp2>::type uncv2;

  enum { same = ::boost::is_same<uncv1, uncv2>::value };
  enum { trivial_assign = ::boost::has_trivial_assign<uncv1>::value };

  typedef typename __bool2type<same>::_Ret _Same;
  typedef typename __bool2type<trivial_assign>::_Ret _Trivial;

  typedef typename _Land2<_Same, _Trivial>::_Ret _Type;
  static _Type _Answer() { return _Type(); }
};

template <class _Tp>
struct _DefaultZeroValue {
  typedef typename _Is_integer<_Tp>::_Integral _Tr1;
  typedef typename _Is_rational<_Tp>::_Rational _Tr2;

  typedef typename _Lor2<_Tr1, _Tr2>::_Ret _Tr3;

  enum { pointer = ::boost::is_pointer<_Tp>::value };
  typedef typename __bool2type< pointer >::_Ret _Tr4;

  typedef typename _Lor2<_Tr3, _Tr4>::_Ret _Type;
  static _Type _Answer() { return _Type(); }
};

_STLP_END_NAMESPACE

#endif /* _STLP_BOOST_TYPE_TRAITS_H */
