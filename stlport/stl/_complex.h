/*
 * Copyright (c) 1999
 * Silicon Graphics Computer Systems, Inc.
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
#ifndef __sgi_internal_complex_h
#define __sgi_internal_complex_h

// This header declares the template class complex, as described in 
// in the draft C++ standard.  Single-precision complex numbers
// are complex<float>, double-precision are complex<double>, and
// quad precision are complex<long double>.

// Note that the template class complex is declared within namespace
// std, as called for by the draft C++ standard.  

#include <cmath>
#include <iosfwd>

__STL_BEGIN_NAMESPACE

#if !defined(__STL_NO_COMPLEX_SPECIALIZATIONS)		//*TY 02/25/2000 - added for MPW compiler workaround

template <class _Tp> struct complex;

__STL_TEMPLATE_NULL  struct __STL_CLASS_DECLSPEC complex<float>;
__STL_TEMPLATE_NULL  struct __STL_CLASS_DECLSPEC complex<double>;
__STL_TEMPLATE_NULL  struct __STL_CLASS_DECLSPEC complex<long double>;

# endif

template <class _Tp>
struct complex {
  typedef _Tp value_type;
  typedef complex<_Tp> _Self;

  // Constructors, destructor, assignment operator.
  complex() : _M_re(0), _M_im(0) {}
  complex(const value_type& __x)
    : _M_re(__x), _M_im(0) {}
  complex(const value_type& __x, const value_type& __y)
    : _M_re(__x), _M_im(__y) {}
  complex(const _Self& __z)
    : _M_re(__z._M_re), _M_im(__z._M_im) {}

  _Self& operator=(const _Self& __z) {
    _M_re = __z._M_re;
    _M_im = __z._M_im;
    return *this;
  }

#if defined (__STL_MEMBER_TEMPLATES) && ( defined (__STL_FUNCTION_TMPL_PARTIAL_ORDER) || defined(__STL_NO_COMPLEX_SPECIALIZATIONS))
  template <class _Tp2>
  explicit complex(const complex<_Tp2>& __z)
    : _M_re(__z._M_re), _M_im(__z._M_im) {}

  template <class _Tp2>
  _Self& operator=(const complex<_Tp2>& __z) {
    _M_re = __z._M_re;
    _M_im = __z._M_im;
    return *this;
  }
#endif /* __STL_MEMBER_TEMPLATES */

  // Element access.
  value_type real() const { return _M_re; }
  value_type imag() const { return _M_im; }

  // Arithmetic op= operations involving one real argument.

  _Self& operator= (const value_type& __x) {
    _M_re = __x;
    _M_im = 0;
    return *this;
  }
  _Self& operator+= (const value_type& __x) {
    _M_re += __x;
    return *this;
  }
  _Self& operator-= (const value_type& __x) {
    _M_re -= __x;
    return *this;
  }
  _Self& operator*= (const value_type& __x) {
    _M_re *= __x;
    _M_im *= __x;
    return *this;
  }
  _Self& operator/= (const value_type& __x) {
    _M_re /= __x;
    _M_im /= __x;
    return *this;
  }

  // Arithmetic op= operations involving two complex arguments.

  static void  __STL_CALL _div(const value_type& __z1_r, const value_type& __z1_i,
                   const value_type& __z2_r, const value_type& __z2_i,
                   value_type& __res_r, value_type& __res_i);

  static void __STL_CALL _div(const value_type& __z1_r, 
                   const value_type& __z2_r, const value_type& __z2_i,
                   value_type& __res_r, value_type& __res_i);

#if defined ( __STL_MEMBER_TEMPLATES ) // && defined (__STL_FUNCTION_TMPL_PARTIAL_ORDER)

  template <class _Tp2> _Self& operator+= (const complex<_Tp2>& __z) {
    _M_re += __z._M_re;
    _M_im += __z._M_im;
    return *this;
  }

  template <class _Tp2> _Self& operator-= (const complex<_Tp2>& __z) {
    _M_re -= __z._M_re;
    _M_im -= __z._M_im;
    return *this;
  }

  template <class _Tp2> _Self& operator*= (const complex<_Tp2>& __z) {
    value_type __r = _M_re * __z._M_re - _M_im * __z._M_im;
    value_type __i = _M_re * __z._M_im + _M_im * __z._M_re;
    _M_re = __r;
    _M_im = __i;
    return *this;
  }

  template <class _Tp2> _Self& operator/= (const complex<_Tp2>& __z) {
    value_type __r;
    value_type __i;
    _div(_M_re, _M_im, __z._M_re, __z._M_im, __r, __i);
    _M_re = __r;
    _M_im = __i;
    return *this;
  }

#endif /* __STL_MEMBER_TEMPLATES */

  _Self& operator+= (const _Self& __z) {
    _M_re += __z._M_re;
    _M_im += __z._M_im;
    return *this;
  }

  _Self& operator-= (const _Self& __z) {
    _M_re -= __z._M_re;
    _M_im -= __z._M_im;
    return *this;
  }
  
  _Self& operator*= (const _Self& __z) {
    value_type __r = _M_re * __z._M_re - _M_im * __z._M_im;
    value_type __i = _M_re * __z._M_im + _M_im * __z._M_re;
    _M_re = __r;
    _M_im = __i;
    return *this;
  }

  _Self& operator/= (const _Self& __z) {
    value_type __r;
    value_type __i;
    _div(_M_re, _M_im, __z._M_re, __z._M_im, __r, __i);
    _M_re = __r;
    _M_im = __i;
    return *this;
  }

  // Data members.
  value_type _M_re;
  value_type _M_im;
};

#if !defined(__STL_NO_COMPLEX_SPECIALIZATIONS)		//*TY 02/25/2000 - added for MPW compiler workaround
// Explicit specializations for float, double, long double.  The only
// reason for these specializations is to enable automatic conversions
// from complex<float> to complex<double>, and complex<double> to
// complex<long double>.


__STL_TEMPLATE_NULL
struct __STL_CLASS_DECLSPEC complex<float> {
  typedef float value_type;
  typedef complex<float> _Self;
  // Constructors, destructor, assignment operator.

  complex(value_type __x = 0.0, value_type __y = 0.0)
    : _M_re(__x), _M_im(__y) {}

  complex(const complex<float>& __z)    : _M_re(__z._M_re), _M_im(__z._M_im) {} 

  inline explicit complex(const complex<double>& __z);
  inline explicit complex(const complex<long double>& __z);

  // Element access.
  value_type real() const { return _M_re; }
  value_type imag() const { return _M_im; }

  // Arithmetic op= operations involving one real argument.

  _Self& operator= (value_type __x) {
    _M_re = __x;
    _M_im = 0;
    return *this;
  }
  _Self& operator+= (value_type __x) {
    _M_re += __x;
    return *this;
  }
  _Self& operator-= (value_type __x) {
    _M_re -= __x;
    return *this;
  }
  _Self& operator*= (value_type __x) {
    _M_re *= __x;
    _M_im *= __x;
    return *this;
  }
  _Self& operator/= (value_type __x) {
    _M_re /= __x;
    _M_im /= __x;
    return *this;
  }

  // Arithmetic op= operations involving two complex arguments.

  static void __STL_CALL _div(const float& __z1_r, const float& __z1_i,
                              const float& __z2_r, const float& __z2_i,
                              float& __res_r, float& __res_i);
    
  static void __STL_CALL _div(const float& __z1_r, 
                              const float& __z2_r, const float& __z2_i,
                              float& __res_r, float& __res_i);
    
#if defined (__STL_MEMBER_TEMPLATES)

  template <class _Tp2>
  complex<float>& operator=(const complex<_Tp2>& __z) {
    _M_re = __z._M_re;
    _M_im = __z._M_im;
    return *this;
  }

  template <class _Tp2>
  complex<float>& operator+= (const complex<_Tp2>& __z) {
    _M_re += __z._M_re;
    _M_im += __z._M_im;
    return *this;
  }

  template <class _Tp2>
  complex<float>& operator-= (const complex<_Tp2>& __z) {
    _M_re -= __z._M_re;
    _M_im -= __z._M_im;
    return *this;
  }

  template <class _Tp2>
  complex<float>& operator*= (const complex<_Tp2>& __z) {
    float __r = _M_re * __z._M_re - _M_im * __z._M_im;
    float __i = _M_re * __z._M_im + _M_im * __z._M_re;
    _M_re = __r;
    _M_im = __i;
    return *this;
  }

  template <class _Tp2>
  complex<float>& operator/= (const complex<_Tp2>& __z) {
    float __r;
    float __i;
    _div(_M_re, _M_im, __z._M_re, __z._M_im, __r, __i);
    _M_re = __r;
    _M_im = __i;
    return *this;
  }

#endif /* __STL_MEMBER_TEMPLATES */

  _Self& operator=(const _Self& __z) {
    _M_re = __z._M_re;
    _M_im = __z._M_im;
    return *this;
  }

  _Self& operator+= (const _Self& __z) {
    _M_re += __z._M_re;
    _M_im += __z._M_im;
    return *this;
  }

  _Self& operator-= (const _Self& __z) {
    _M_re -= __z._M_re;
    _M_im -= __z._M_im;
    return *this;
  }
  
  _Self& operator*= (const _Self& __z) {
    value_type __r = _M_re * __z._M_re - _M_im * __z._M_im;
    value_type __i = _M_re * __z._M_im + _M_im * __z._M_re;
    _M_re = __r;
    _M_im = __i;
    return *this;
  }

  _Self& operator/= (const _Self& __z) {
    value_type __r;
    value_type __i;
    _div(_M_re, _M_im, __z._M_re, __z._M_im, __r, __i);
    _M_re = __r;
    _M_im = __i;
    return *this;
  }

  // Data members.
  value_type _M_re;
  value_type _M_im;
};

__STL_TEMPLATE_NULL struct __STL_CLASS_DECLSPEC complex<double> {
  typedef double value_type;
  typedef complex<double> _Self;

  // Constructors, destructor, assignment operator.

  complex(value_type __x = 0.0, value_type __y = 0.0)
    : _M_re(__x), _M_im(__y) {}

  complex(const complex<double>& __z)
    : _M_re(__z._M_re), _M_im(__z._M_im) {}
  inline complex(const complex<float>& __z);
  explicit inline complex(const complex<long double>& __z);

  // Element access.
  value_type real() const { return _M_re; }
  value_type imag() const { return _M_im; }

  // Arithmetic op= operations involving one real argument.

  _Self& operator= (value_type __x) {
    _M_re = __x;
    _M_im = 0;
    return *this;
  }
  _Self& operator+= (value_type __x) {
    _M_re += __x;
    return *this;
  }
  _Self& operator-= (value_type __x) {
    _M_re -= __x;
    return *this;
  }
  _Self& operator*= (value_type __x) {
    _M_re *= __x;
    _M_im *= __x;
    return *this;
  }
  _Self& operator/= (value_type __x) {
    _M_re /= __x;
    _M_im /= __x;
    return *this;
  }

  // Arithmetic op= operations involving two complex arguments.

  static void __STL_CALL _div(const double& __z1_r, const double& __z1_i,
                              const double& __z2_r, const double& __z2_i,
                              double& __res_r, double& __res_i);
  static void __STL_CALL _div(const double& __z1_r, 
                              const double& __z2_r, const double& __z2_i,
                              double& __res_r, double& __res_i);
    
#if defined (__STL_MEMBER_TEMPLATES) && defined (__STL_FUNCTION_TMPL_PARTIAL_ORDER)

  template <class _Tp2>
  complex<double>& operator=(const complex<_Tp2>& __z) {
    _M_re = __z._M_re;
    _M_im = __z._M_im;
    return *this;
  }

  template <class _Tp2>
  complex<double>& operator+= (const complex<_Tp2>& __z) {
    _M_re += __z._M_re;
    _M_im += __z._M_im;
    return *this;
  }

  template <class _Tp2>
  complex<double>& operator-= (const complex<_Tp2>& __z) {
    _M_re -= __z._M_re;
    _M_im -= __z._M_im;
    return *this;
  }

  template <class _Tp2>
  complex<double>& operator*= (const complex<_Tp2>& __z) {
    double __r = _M_re * __z._M_re - _M_im * __z._M_im;
    double __i = _M_re * __z._M_im + _M_im * __z._M_re;
    _M_re = __r;
    _M_im = __i;
    return *this;
  }

  template <class _Tp2>
  complex<double>& operator/= (const complex<_Tp2>& __z) {
    double __r;
    double __i;
    _div(_M_re, _M_im, __z._M_re, __z._M_im, __r, __i);
    _M_re = __r;
    _M_im = __i;
    return *this;
  }

#endif /* __STL_MEMBER_TEMPLATES */

  _Self& operator=(const _Self& __z) {
    _M_re = __z._M_re;
    _M_im = __z._M_im;
    return *this;
  }

  _Self& operator+= (const _Self& __z) {
    _M_re += __z._M_re;
    _M_im += __z._M_im;
    return *this;
  }

  _Self& operator-= (const _Self& __z) {
    _M_re -= __z._M_re;
    _M_im -= __z._M_im;
    return *this;
  }
  
  _Self& operator*= (const _Self& __z) {
    value_type __r = _M_re * __z._M_re - _M_im * __z._M_im;
    value_type __i = _M_re * __z._M_im + _M_im * __z._M_re;
    _M_re = __r;
    _M_im = __i;
    return *this;
  }

  _Self& operator/= (const _Self& __z) {
    value_type __r;
    value_type __i;
    _div(_M_re, _M_im, __z._M_re, __z._M_im, __r, __i);
    _M_re = __r;
    _M_im = __i;
    return *this;
  }

  // Data members.
  value_type _M_re;
  value_type _M_im;
};


__STL_TEMPLATE_NULL struct __STL_CLASS_DECLSPEC complex<long double> {
  typedef long double value_type;
  typedef complex<long double> _Self;

  // Constructors, destructor, assignment operator.
  complex(value_type __x = 0.0, value_type __y = 0.0)
    : _M_re(__x), _M_im(__y) {}

  complex(const complex<long double>& __z)
    : _M_re(__z._M_re), _M_im(__z._M_im) {}
  inline complex(const complex<float>& __z);
  inline complex(const complex<double>& __z);

  // Element access.
  value_type real() const { return _M_re; }
  value_type imag() const { return _M_im; }

  // Arithmetic op= operations involving one real argument.

  _Self& operator= (value_type __x) {
    _M_re = __x;
    _M_im = 0;
    return *this;
  }
  _Self& operator+= (value_type __x) {
    _M_re += __x;
    return *this;
  }
  _Self& operator-= (value_type __x) {
    _M_re -= __x;
    return *this;
  }
  _Self& operator*= (value_type __x) {
    _M_re *= __x;
    _M_im *= __x;
    return *this;
  }
  _Self& operator/= (value_type __x) {
    _M_re /= __x;
    _M_im /= __x;
    return *this;
  }

  // Arithmetic op= operations involving two complex arguments.

  static void __STL_CALL _div(const long double& __z1_r, const long double& __z1_i,
                              const long double& __z2_r, const long double& __z2_i,
                              long double& __res_r, long double& __res_i);

  static void __STL_CALL _div(const long double& __z1_r, 
                              const long double& __z2_r, const long double& __z2_i,
                              long double& __res_r, long double& __res_i);

#if defined (__STL_MEMBER_TEMPLATES) && defined (__STL_FUNCTION_TMPL_PARTIAL_ORDER)

  template <class _Tp2>
  complex<long double>& operator=(const complex<_Tp2>& __z) {
    _M_re = __z._M_re;
    _M_im = __z._M_im;
    return *this;
  }

  template <class _Tp2>
  complex<long double>& operator+= (const complex<_Tp2>& __z) {
    _M_re += __z._M_re;
    _M_im += __z._M_im;
    return *this;
  }

  template <class _Tp2>
  complex<long double>& operator-= (const complex<_Tp2>& __z) {
    _M_re -= __z._M_re;
    _M_im -= __z._M_im;
    return *this;
  }

  template <class _Tp2>
  complex<long double>& operator*= (const complex<_Tp2>& __z) {
    long double __r = _M_re * __z._M_re - _M_im * __z._M_im;
    long double __i = _M_re * __z._M_im + _M_im * __z._M_re;
    _M_re = __r;
    _M_im = __i;
    return *this;
  }

  template <class _Tp2>
  complex<long double>& operator/= (const complex<_Tp2>& __z) {
    long double __r;
    long double __i;
    _div(_M_re, _M_im, __z._M_re, __z._M_im, __r, __i);
    _M_re = __r;
    _M_im = __i;
    return *this;
  }

#endif /* __STL_MEMBER_TEMPLATES */

  _Self& operator=(const _Self& __z) {
    _M_re = __z._M_re;
    _M_im = __z._M_im;
    return *this;
  }

  _Self& operator+= (const _Self& __z) {
    _M_re += __z._M_re;
    _M_im += __z._M_im;
    return *this;
  }

  _Self& operator-= (const _Self& __z) {
    _M_re -= __z._M_re;
    _M_im -= __z._M_im;
    return *this;
  }
  
  _Self& operator*= (const _Self& __z) {
    value_type __r = _M_re * __z._M_re - _M_im * __z._M_im;
    value_type __i = _M_re * __z._M_im + _M_im * __z._M_re;
    _M_re = __r;
    _M_im = __i;
    return *this;
  }

  _Self& operator/= (const _Self& __z) {
    value_type __r;
    value_type __i;
    _div(_M_re, _M_im, __z._M_re, __z._M_im, __r, __i);
    _M_re = __r;
    _M_im = __i;
    return *this;
  }

  // Data members.
  value_type _M_re;
  value_type _M_im;
};

// Converting constructors from one of these three specialized types
// to another.

inline complex<float>::complex(const complex<double>& __z)
  : _M_re(__z._M_re), _M_im(__z._M_im) {}
inline complex<float>::complex(const complex<long double>& __z)
  : _M_re(__z._M_re), _M_im(__z._M_im) {}
inline complex<double>::complex(const complex<float>& __z)
  : _M_re(__z._M_re), _M_im(__z._M_im) {}
inline complex<double>::complex(const complex<long double>& __z)
  : _M_re(__z._M_re), _M_im(__z._M_im) {}
inline complex<long double>::complex(const complex<float>& __z)
  : _M_re(__z._M_re), _M_im(__z._M_im) {}
inline complex<long double>::complex(const complex<double>& __z)
  : _M_re(__z._M_re), _M_im(__z._M_im) {}

# endif /* SPECIALIZATIONS */

// Unary non-member arithmetic operators.

template <class _Tp>
inline complex<_Tp> __STL_CALL operator+(const complex<_Tp>& __z) {
  return __z;
}

template <class _Tp>
inline complex<_Tp> __STL_CALL  operator-(const complex<_Tp>& __z) {
  return complex<_Tp>(-__z._M_re, -__z._M_im);
}

// Non-member arithmetic operations involving one real argument.

template <class _Tp> 
inline complex<_Tp> __STL_CALL operator+(const _Tp& __x, const complex<_Tp>& __z) {
  return complex<_Tp>(__x + __z._M_re, __z._M_im);
}

template <class _Tp> 
inline complex<_Tp> __STL_CALL operator+(const complex<_Tp>& __z, const _Tp& __x) {
  return complex<_Tp>(__z._M_re + __x, __z._M_im);
}

template <class _Tp> 
inline complex<_Tp> __STL_CALL operator-(const _Tp& __x, const complex<_Tp>& __z) {
  return complex<_Tp>(__x - __z._M_re, -__z._M_im);
}

template <class _Tp> 
inline complex<_Tp> __STL_CALL operator-(const complex<_Tp>& __z, const _Tp& __x) {
  return complex<_Tp>(__z._M_re - __x, __z._M_im);
}

template <class _Tp> 
inline complex<_Tp> __STL_CALL operator*(const _Tp& __x, const complex<_Tp>& __z) {
  return complex<_Tp>(__x * __z._M_re, __x * __z._M_im);
}

template <class _Tp> 
inline complex<_Tp> __STL_CALL operator*(const complex<_Tp>& __z, const _Tp& __x) {
  return complex<_Tp>(__z._M_re * __x, __z._M_im * __x);
}

template <class _Tp> 
inline complex<_Tp> __STL_CALL operator/(const _Tp& __x, const complex<_Tp>& __z) {
  complex<_Tp> __result;
  complex<_Tp>::_div(__x,
                     __z._M_re, __z._M_im,
                     __result._M_re, __result._M_im);
  return __result;
}

template <class _Tp> 
inline complex<_Tp> __STL_CALL operator/(const complex<_Tp>& __z, const _Tp& __x) {
  return complex<_Tp>(__z._M_re / __x, __z._M_im / __x);
}

// Non-member arithmetic operations involving two complex arguments

template <class _Tp> 
inline complex<_Tp> __STL_CALL 
operator+(const complex<_Tp>& __z1, const complex<_Tp>& __z2) {
  return complex<_Tp>(__z1._M_re + __z2._M_re, __z1._M_im + __z2._M_im);
}

template <class _Tp> 
inline complex<_Tp> __STL_CALL 
operator-(const complex<_Tp>& __z1, const complex<_Tp>& __z2) {
  return complex<_Tp>(__z1._M_re - __z2._M_re, __z1._M_im - __z2._M_im);
}

template <class _Tp> 
inline complex<_Tp> __STL_CALL 
operator*(const complex<_Tp>& __z1, const complex<_Tp>& __z2) {
  return complex<_Tp>(__z1._M_re * __z2._M_re - __z1._M_im * __z2._M_im,
                      __z1._M_re * __z2._M_im + __z1._M_im * __z2._M_re);
}

template <class _Tp> 
inline complex<_Tp> __STL_CALL 
operator/(const complex<_Tp>& __z1, const complex<_Tp>& __z2) {
  complex<_Tp> __result;
  complex<_Tp>::_div(__z1._M_re, __z1._M_im,
                     __z2._M_re, __z2._M_im,
                     __result._M_re, __result._M_im);
  return __result;
}

// Comparison operators.

template <class _Tp> 
inline bool __STL_CALL operator==(const complex<_Tp>& __z1, const complex<_Tp>& __z2) {
  return __z1._M_re == __z2._M_re && __z1._M_im == __z2._M_im;
}

template <class _Tp> 
inline bool __STL_CALL operator==(const complex<_Tp>& __z, const _Tp& __x) {
  return __z._M_re == __x && __z._M_im == 0;
}

template <class _Tp> 
inline bool __STL_CALL operator==(const _Tp& __x, const complex<_Tp>& __z) {
  return __x == __z._M_re && 0 == __z._M_im;
}

#ifdef __STL_FUNCTION_TMPL_PARTIAL_ORDER

template <class _Tp> 
inline bool __STL_CALL operator!=(const complex<_Tp>& __z1, const complex<_Tp>& __z2) {
  return __z1._M_re != __z2._M_re || __z1._M_im != __z2._M_im;
}

#endif /* __STL_FUNCTION_TMPL_PARTIAL_ORDER */

template <class _Tp> 
inline bool __STL_CALL operator!=(const complex<_Tp>& __z, const _Tp& __x) {
  return __z._M_re != __x || __z._M_im != 0;
}

template <class _Tp> 
inline bool __STL_CALL operator!=(const _Tp& __x, const complex<_Tp>& __z) {
  return __x != __z._M_re || 0 != __z._M_im;
}

// Other basic arithmetic operations

template <class _Tp> 
inline _Tp __STL_CALL real(const complex<_Tp>& __z) {
  return __z._M_re;
}

template <class _Tp> 
inline _Tp __STL_CALL imag(const complex<_Tp>& __z) {
  return __z._M_im;
}

__STL_DECLSPEC float  __STL_CALL abs(const complex<float>&);
__STL_DECLSPEC double  __STL_CALL abs(const complex<double>&);
__STL_DECLSPEC float  __STL_CALL arg(const complex<float>&);
__STL_DECLSPEC double  __STL_CALL arg(const complex<double>&);
__STL_DECLSPEC complex<float> __STL_CALL polar(const float& __rho, const float& __phi);
__STL_DECLSPEC complex<double> __STL_CALL polar(const double& __rho, const double& __phi);


# ifdef __STL_LONG_DOUBLE
__STL_DECLSPEC long double  __STL_CALL arg(const complex<long double>&);
__STL_DECLSPEC long double  __STL_CALL abs(const complex<long double>&);
__STL_DECLSPEC complex<long double>  __STL_CALL polar(const long double&, const long double&);
# endif

template <class _Tp>
_Tp __STL_CALL abs(const complex<_Tp>& __z) {
  return _Tp(abs(complex<double>(double(__z.real()), double(__z.imag()))));
}

template <class _Tp>
_Tp __STL_CALL arg(const complex<_Tp>& __z) {
  return _Tp(arg(complex<double>(double(__z.real()), double(__z.imag()))));
}

template <class _Tp>
inline _Tp __STL_CALL norm(const complex<_Tp>& __z) {
  return __z._M_re * __z._M_re + __z._M_im * __z._M_im;
}

template <class _Tp>
inline complex<_Tp> __STL_CALL conj(const complex<_Tp>& __z) {
  return complex<_Tp>(__z._M_re, -__z._M_im);
}

template <class _Tp>
complex<_Tp> __STL_CALL polar(const _Tp& __rho) {
  return complex<_Tp>(__rho, 0);
}

template <class _Tp>
complex<_Tp> __STL_CALL polar(const _Tp& __rho, const _Tp& __phi) {
  complex<double> __tmp = polar(double(__rho), double(__phi));
  return complex<_Tp>(_Tp(__tmp.real()), _Tp(__tmp.imag()));
}

#ifdef __STL_USE_NEW_IOSTREAMS

// Complex output, in the form (re,im).  We use a two-step process 
// involving stringstream so that we get the padding right.  
template <class _Tp, class _CharT, class _Traits>
basic_ostream<_CharT, _Traits>&  __STL_CALL 
operator<<(basic_ostream<_CharT, _Traits>& __os, const complex<_Tp>& __z);

template <class _Tp, class _CharT, class _Traits>
basic_istream<_CharT, _Traits>& __STL_CALL 
operator>>(basic_istream<_CharT, _Traits>& __is, complex<_Tp>& __z);

// Specializations for narrow characters; lets us avoid widen.

__STL_OPERATOR_TEMPLATE
__STL_DECLSPEC basic_istream<char, char_traits<char> >& __STL_CALL 
operator>>(basic_istream<char, char_traits<char> >& __is, complex<float>& __z);

__STL_OPERATOR_TEMPLATE
__STL_DECLSPEC basic_istream<char, char_traits<char> >& __STL_CALL 
operator>>(basic_istream<char, char_traits<char> >& __is, complex<double>& __z);


__STL_OPERATOR_TEMPLATE
__STL_DECLSPEC basic_ostream<char, char_traits<char> >& __STL_CALL 
operator<<(basic_ostream<char, char_traits<char> >& __is, const complex<float>& __z);

__STL_OPERATOR_TEMPLATE
__STL_DECLSPEC basic_ostream<char, char_traits<char> >& __STL_CALL 
operator<<(basic_ostream<char, char_traits<char> >& __is, const complex<double>& __z);

#  ifdef __STL_LONG_DOUBLE

__STL_OPERATOR_TEMPLATE
__STL_DECLSPEC basic_ostream<char, char_traits<char> >& __STL_CALL 
operator>>(basic_istream<char, char_traits<char> >& __is, const complex<long double>& __z);

__STL_OPERATOR_TEMPLATE
__STL_DECLSPEC basic_istream<char, char_traits<char> >& __STL_CALL 
operator<<(basic_ostream<char, char_traits<char> >& __is, complex<long double>& __z);

# endif

# if defined (__STL_USE_TEMPLATE_EXPORT) && ! defined (__STL_NO_WCHAR_T)

__STL_EXPORT_TEMPLATE basic_istream<wchar_t, char_traits<wchar_t> >& __STL_CALL operator>>(
        basic_istream<wchar_t, char_traits<wchar_t> >&, complex<double>&);
__STL_EXPORT_TEMPLATE basic_ostream<wchar_t, char_traits<wchar_t> >& __STL_CALL operator<<(
        basic_ostream<wchar_t, char_traits<wchar_t> >&, const complex<double>&);
__STL_EXPORT_TEMPLATE basic_istream<wchar_t, char_traits<wchar_t> >& __STL_CALL operator>>(
        basic_istream<wchar_t, char_traits<wchar_t> >&, complex<float>&);
__STL_EXPORT_TEMPLATE basic_ostream<wchar_t, char_traits<wchar_t> >& __STL_CALL operator<<(
        basic_ostream<wchar_t, char_traits<wchar_t> >&, const complex<float>&);

#  ifdef __STL_LONG_DOUBLE
__STL_EXPORT_TEMPLATE basic_istream<wchar_t, char_traits<wchar_t> >& __STL_CALL operator>>(
        basic_istream<wchar_t, char_traits<wchar_t> >&, complex<long double>&);
__STL_EXPORT_TEMPLATE basic_ostream<wchar_t, char_traits<wchar_t> >& __STL_CALL operator<<(
        basic_ostream<wchar_t, char_traits<wchar_t> >&, const complex<long double>&);
#  endif

# endif /* USE_TEMPLATE_EXPORT */

#else /* __STL_USE_NEW_IOSTREAMS */

template <class _Tp>
ostream& __STL_CALL operator<<(ostream& s, const complex<_Tp>& __z);

template <class _Tp>
istream& __STL_CALL  operator>>(istream& s, complex<_Tp>& a);

#endif /* __STL_USE_NEW_IOSTREAMS */


// Transcendental functions.  These are defined only for float, 
//  double, and long double.  (Sqrt isn't transcendental, of course,
//  but it's included in this section anyway.)

__STL_DECLSPEC complex<float> __STL_CALL sqrt(const complex<float>&);

__STL_DECLSPEC complex<float> __STL_CALL exp(const complex<float>&);
__STL_DECLSPEC complex<float> __STL_CALL  log(const complex<float>&);
__STL_DECLSPEC complex<float> __STL_CALL log10(const complex<float>&);

__STL_DECLSPEC complex<float> __STL_CALL pow(const complex<float>&, int);
__STL_DECLSPEC complex<float> __STL_CALL pow(const complex<float>&, const float&);
__STL_DECLSPEC complex<float> __STL_CALL pow(const float&, const complex<float>&);
__STL_DECLSPEC complex<float> __STL_CALL pow(const complex<float>&, const complex<float>&);

__STL_DECLSPEC complex<float> __STL_CALL sin(const complex<float>&);
__STL_DECLSPEC complex<float> __STL_CALL cos(const complex<float>&);
__STL_DECLSPEC complex<float> __STL_CALL tan(const complex<float>&);

__STL_DECLSPEC complex<float> __STL_CALL sinh(const complex<float>&);
__STL_DECLSPEC complex<float> __STL_CALL cosh(const complex<float>&);
__STL_DECLSPEC complex<float> __STL_CALL tanh(const complex<float>&);

__STL_DECLSPEC complex<double> __STL_CALL sqrt(const complex<double>&);

__STL_DECLSPEC complex<double> __STL_CALL exp(const complex<double>&);
__STL_DECLSPEC complex<double> __STL_CALL log(const complex<double>&);
__STL_DECLSPEC complex<double> __STL_CALL log10(const complex<double>&);

__STL_DECLSPEC complex<double> __STL_CALL pow(const complex<double>&, int);
__STL_DECLSPEC complex<double> __STL_CALL pow(const complex<double>&, const double&);
__STL_DECLSPEC complex<double> __STL_CALL pow(const double&, const complex<double>&);
__STL_DECLSPEC complex<double> __STL_CALL pow(const complex<double>&, const complex<double>&);

__STL_DECLSPEC complex<double> __STL_CALL sin(const complex<double>&);
__STL_DECLSPEC complex<double> __STL_CALL cos(const complex<double>&);
__STL_DECLSPEC complex<double> __STL_CALL tan(const complex<double>&);

__STL_DECLSPEC complex<double> __STL_CALL sinh(const complex<double>&);
__STL_DECLSPEC complex<double> __STL_CALL cosh(const complex<double>&);
__STL_DECLSPEC complex<double> __STL_CALL tanh(const complex<double>&);



__STL_DECLSPEC complex<long double> __STL_CALL sqrt(const complex<long double>&);

__STL_DECLSPEC complex<long double> __STL_CALL exp(const complex<long double>&);
__STL_DECLSPEC complex<long double> __STL_CALL log(const complex<long double>&);
__STL_DECLSPEC complex<long double> __STL_CALL log10(const complex<long double>&);

__STL_DECLSPEC complex<long double> __STL_CALL pow(const complex<long double>&, int);
__STL_DECLSPEC complex<long double> __STL_CALL pow(const complex<long double>&, const long double&);
__STL_DECLSPEC complex<long double> __STL_CALL pow(const long double&, const complex<long double>&);
__STL_DECLSPEC complex<long double> __STL_CALL pow(const complex<long double>&,
                                                   const complex<long double>&);

__STL_DECLSPEC complex<long double> __STL_CALL sin(const complex<long double>&);
__STL_DECLSPEC complex<long double> __STL_CALL cos(const complex<long double>&);
__STL_DECLSPEC complex<long double> __STL_CALL tan(const complex<long double>&);

__STL_DECLSPEC complex<long double> __STL_CALL sinh(const complex<long double>&);
__STL_DECLSPEC complex<long double> __STL_CALL cosh(const complex<long double>&);
__STL_DECLSPEC complex<long double> __STL_CALL tanh(const complex<long double>&);

__STL_END_NAMESPACE


# ifndef __STL_LINK_TIME_INSTANTIATION
#  include <stl/_complex.c>
# endif

#endif /* __sgi_template_complex */

// Local Variables:
// mode:C++
// End:
