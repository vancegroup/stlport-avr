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
# include "stlport_prefix.h"
// Complex division and square roots.

#include "complex_impl.h"

__STL_BEGIN_NAMESPACE

// Absolute value
__STL_DECLSPEC float __STL_CALL abs(const complex<float>& __z)
{
  return __STL_HYPOTF(__z._M_re, __z._M_im);
}

__STL_DECLSPEC double __STL_CALL abs(const complex<double>& __z)
{
  return __STL_HYPOT(__z._M_re, __z._M_im);
}

__STL_DECLSPEC long double __STL_CALL abs(const complex<long double>& __z)
{
  return __STL_HYPOTL(__z._M_re, __z._M_im);
}

// Phase

__STL_DECLSPEC float __STL_CALL arg(const complex<float>& __z) 
{
  return __STL_ATAN2F(__z._M_im, __z._M_re);
}

__STL_DECLSPEC double __STL_CALL arg(const complex<double>& __z) 
{
  return __STL_ATAN2(__z._M_im, __z._M_re);
}

__STL_DECLSPEC long double __STL_CALL arg(const complex<long double>& __z) 
{
  return __STL_ATAN2L(__z._M_im, __z._M_re);
}

// Construct a complex number from polar representation

__STL_DECLSPEC complex<float> __STL_CALL polar(const float& __rho, const float& __phi) 
{
  return complex<float>(__rho * __STL_COSF(__phi), __rho * __STL_SINF(__phi));
}

__STL_DECLSPEC complex<double> __STL_CALL polar(const double& __rho, const double& __phi) 
{
  return complex<double>(__rho * __STL_COS(__phi), __rho * __STL_SIN(__phi));
}

__STL_DECLSPEC complex<long double> __STL_CALL polar(const long double& __rho, const long double& __phi)
{
  return complex<long double>(__rho * __STL_COSL(__phi), __rho * __STL_SINL(__phi));
}


// Division

void  __STL_CALL
complex<float>::_div(const float& __z1_r, const float& __z1_i,
		     const float& __z2_r, const float& __z2_i,
		     float& __res_r, float& __res_i) {
  float __ar = __z2_r >= 0 ? __z2_r : -__z2_r;
  float __ai = __z2_i >= 0 ? __z2_i : -__z2_i;

  if (__ar <= __ai) {
    float __ratio = __z2_r / __z2_i;
    float __denom = __z2_i * (1 + __ratio * __ratio);
    __res_r = (__z1_r * __ratio + __z1_i) / __denom;
    __res_i = (__z1_i * __ratio - __z1_r) / __denom;
  }
  else {
    float __ratio = __z2_i / __z2_r;
    float __denom = __z2_r * (1 + __ratio * __ratio);
    __res_r = (__z1_r + __z1_i * __ratio) / __denom;
    __res_i = (__z1_i - __z1_r * __ratio) / __denom;
  }
}

void  __STL_CALL
complex<float>::_div(const float& __z1_r,
                     const float& __z2_r, const float& __z2_i,
                     float& __res_r, float& __res_i) {
  float __ar = __z2_r >= 0 ? __z2_r : -__z2_r;
  float __ai = __z2_i >= 0 ? __z2_i : -__z2_i;

  if (__ar <= __ai) {
    float __ratio = __z2_r / __z2_i;
    float __denom = __z2_i * (1 + __ratio * __ratio);
    __res_r = (__z1_r * __ratio) / __denom;
    __res_i = - __z1_r / __denom;
  }
  else {
    float __ratio = __z2_i / __z2_r;
    float __denom = __z2_r * (1 + __ratio * __ratio);
    __res_r = __z1_r / __denom;
    __res_i = - (__z1_r * __ratio) / __denom;
  }
}


void  __STL_CALL
complex<double>::_div(const double& __z1_r, const double& __z1_i,
                      const double& __z2_r, const double& __z2_i,
                      double& __res_r, double& __res_i) {
  double __ar = __z2_r >= 0 ? __z2_r : -__z2_r;
  double __ai = __z2_i >= 0 ? __z2_i : -__z2_i;

  if (__ar <= __ai) {
    double __ratio = __z2_r / __z2_i;
    double __denom = __z2_i * (1 + __ratio * __ratio);
    __res_r = (__z1_r * __ratio + __z1_i) / __denom;
    __res_i = (__z1_i * __ratio - __z1_r) / __denom;
  }
  else {
    double __ratio = __z2_i / __z2_r;
    double __denom = __z2_r * (1 + __ratio * __ratio);
    __res_r = (__z1_r + __z1_i * __ratio) / __denom;
    __res_i = (__z1_i - __z1_r * __ratio) / __denom;
  }
}

void __STL_CALL
complex<double>::_div(const double& __z1_r,
                      const double& __z2_r, const double& __z2_i,
                      double& __res_r, double& __res_i) {
  double __ar = __z2_r >= 0 ? __z2_r : -__z2_r;
  double __ai = __z2_i >= 0 ? __z2_i : -__z2_i;

  if (__ar <= __ai) {
    double __ratio = __z2_r / __z2_i;
    double __denom = __z2_i * (1 + __ratio * __ratio);
    __res_r = (__z1_r * __ratio) / __denom;
    __res_i = - __z1_r / __denom;
  }
  else {
    double __ratio = __z2_i / __z2_r;
    double __denom = __z2_r * (1 + __ratio * __ratio);
    __res_r = __z1_r / __denom;
    __res_i = - (__z1_r * __ratio) / __denom;
  }
}


void  __STL_CALL
complex<long double>::_div(const long double& __z1_r, const long double& __z1_i,
                           const long double& __z2_r, const long double& __z2_i,
                           long double& __res_r, long double& __res_i) {
  long double __ar = __z2_r >= 0 ? __z2_r : -__z2_r;
  long double __ai = __z2_i >= 0 ? __z2_i : -__z2_i;

  if (__ar <= __ai) {
    long double __ratio = __z2_r / __z2_i;
    long double __denom = __z2_i * (1 + __ratio * __ratio);
    __res_r = (__z1_r * __ratio + __z1_i) / __denom;
    __res_i = (__z1_i * __ratio - __z1_r) / __denom;
  }
  else {
    long double __ratio = __z2_i / __z2_r;
    long double __denom = __z2_r * (1 + __ratio * __ratio);
    __res_r = (__z1_r + __z1_i * __ratio) / __denom;
    __res_i = (__z1_i - __z1_r * __ratio) / __denom;
  }
}


void __STL_CALL
complex<long double>::_div(const long double& __z1_r,
                           const long double& __z2_r, const long double& __z2_i,
                           long double& __res_r, long double& __res_i) {
  long double __ar = __z2_r >= 0 ? __z2_r : -__z2_r;
  long double __ai = __z2_i >= 0 ? __z2_i : -__z2_i;

  if (__ar <= __ai) {
    long double __ratio = __z2_r / __z2_i;
    long double __denom = __z2_i * (1 + __ratio * __ratio);
    __res_r = (__z1_r * __ratio) / __denom;
    __res_i = - __z1_r / __denom;
  }
  else {
    long double __ratio = __z2_i / __z2_r;
    long double __denom = __z2_r * (1 + __ratio * __ratio);
    __res_r = __z1_r / __denom;
    __res_i = - (__z1_r * __ratio) / __denom;
  }
}

//----------------------------------------------------------------------
// Square root


complex<float> __STL_CALL
sqrt(const complex<float>& z) {
  float re = z._M_re;
  float im = z._M_im;
  float mag = __STL_HYPOTF(re, im);
  complex<float> result;

  if (mag == 0.) {
    result._M_re = result._M_im = 0.f;
  } else if (re > 0.f) {
    result._M_re = __STL_SQRTF(0.5f * (mag + re));
    result._M_im = im/result._M_re/2.f;
  } else {
    result._M_im = __STL_SQRTF(0.5f * (mag - re));
    if (im < 0.f)
      result._M_im = - result._M_im;
    result._M_re = im/result._M_im/2.f;
  }
  return result;
}


complex<double>  __STL_CALL
sqrt(const complex<double>& z) {
  double re = z._M_re;
  double im = z._M_im;
  double mag = __STL_HYPOT(re, im);
  complex<double> result;

  if (mag == 0.) {
    result._M_re = result._M_im = 0.;
  } else if (re > 0.) {
    result._M_re = __STL_SQRT(0.5 * (mag + re));
    result._M_im = im/result._M_re/2;
  } else {
    result._M_im = __STL_SQRT(0.5 * (mag - re));
    if (im < 0.)
      result._M_im = - result._M_im;
    result._M_re = im/result._M_im/2;
  }
  return result;
}


complex<long double> __STL_CALL
sqrt(const complex<long double>& z) {
  long double re = z._M_re;
  long double im = z._M_im;
  long double mag = __STL_HYPOTL(re, im);
  complex<long double> result;

  if (mag == 0.L) {
    result._M_re = result._M_im = 0.L;
  } else if (re > 0.L) {
    result._M_re = __STL_SQRTL(0.5L * (mag + re));
    result._M_im = (im/result._M_re) * .5L;
  } else {
    result._M_im = __STL_SQRTL(0.5L * (mag - re));
    if (im < 0.L)
      result._M_im = - result._M_im;
    result._M_re = (im/result._M_im) * .5L;
  }
  return result;
}

__STL_END_NAMESPACE
