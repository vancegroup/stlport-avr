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


// Trigonometric and hyperbolic functions for complex<float>, 
// complex<double>, and complex<long double>


#include "complex_impl.h"

#include <cfloat>
#include <cmath>

__STL_BEGIN_NAMESPACE

//----------------------------------------------------------------------
// sin

__STL_DECLSPEC complex<float>  __STL_CALL sin(const complex<float>& z) {
  return complex<float>(__STL_SINF(z._M_re) * __STL_COSHF(z._M_im),
                        __STL_COSF(z._M_re) * __STL_SINHF(z._M_im));
}

__STL_DECLSPEC complex<double> __STL_CALL sin(const complex<double>& z) {
  return complex<double>(__STL_SIN(z._M_re) * __STL_COSH(z._M_im),
                         __STL_COS(z._M_re) * __STL_SINH(z._M_im));
}

#ifndef __STL_NO_LONG_DOUBLE
__STL_DECLSPEC complex<long double> __STL_CALL sin(const complex<long double>& z) {
  return complex<long double>(__STL_SINL(z._M_re) * __STL_COSHL(z._M_im),
                              __STL_COSL(z._M_re) * __STL_SINHL(z._M_im));
}
#endif

//----------------------------------------------------------------------
// cos

__STL_DECLSPEC complex<float> __STL_CALL cos(const complex<float>& z) {
  return complex<float>(__STL_COSF(z._M_re) * __STL_COSHF(z._M_im),
                        -__STL_SINF(z._M_re) * __STL_SINHF(z._M_im));
}

__STL_DECLSPEC complex<double> __STL_CALL cos(const complex<double>& z) {
  return complex<double>(__STL_COS(z._M_re) * __STL_COSH(z._M_im),
                        -__STL_SIN(z._M_re) * __STL_SINH(z._M_im));
}
#ifndef __STL_NO_LONG_DOUBLE

__STL_DECLSPEC complex<long double> __STL_CALL cos(const complex<long double>& z) {
  return complex<long double>(__STL_COSL(z._M_re) * __STL_COSHL(z._M_im),
                              -__STL_SINL(z._M_re) * __STL_SINHL(z._M_im));
}
# endif

//----------------------------------------------------------------------
// tan

__STL_DECLSPEC complex<float> __STL_CALL tan(const complex<float>& z) {
  float re2 = 2.f * z._M_re;
  float im2 = 2.f * z._M_im;

#ifdef __sgi
  const union { unsigned int i; float f; } ulimit = { 0x42b2d4fc };
  const float limit = ulimit.f;
#else
  const float limit = __STL_LOGF(FLT_MAX);
#endif

  if (__STL_ABSF(im2) > limit)
    return complex<float>(0.f, (im2 > 0 ? 1.f : -1.f));
  else {
    float den = __STL_COSF(re2) + __STL_COSHF(im2);
    return complex<float>(__STL_SINF(re2) / den, __STL_SINHF(im2) / den);
  }
}

__STL_DECLSPEC complex<double> __STL_CALL tan(const complex<double>& z) {
  double re2 = 2. * z._M_re;
  double im2 = 2. * z._M_im;

#ifdef __sgi
  union {
    struct { unsigned int h; unsigned int l; } w;
    double d;
  } ulimit = { 0x408633ce, 0x8fb9f87d };
  const double limit = ulimit.d;
#else
  const double limit = __STL_DO_LOG(double)(DBL_MAX);
#endif

  if (fabs(float(im2)) > limit)
    return complex<double>(0., (im2 > 0 ? 1. : -1.));
  else {
    double den = __STL_COS(re2) + __STL_COSH(im2);
    return complex<double>(__STL_SIN(re2) / den, __STL_SINH(im2) / den);
  }
}

#ifndef __STL_NO_LONG_DOUBLE
__STL_DECLSPEC complex<long double> __STL_CALL tan(const complex<long double>& z) {
  long double re2 = 2.l * z._M_re;
  long double im2 = 2.l * z._M_im;

#ifdef __sgi
  union {
    struct { unsigned int h[2]; unsigned int l[2]; } w;
    long double ld;
  } ulimit = {0x408633ce, 0x8fb9f87e, 0xbd23b659, 0x4e9bd8b1};
  const long double limit = ulimit.ld;
#else
  const long double limit = __STL_LOGL(LDBL_MAX);
#endif

  if (__STL_ABSL(im2) > limit)
    return complex<long double>(0.l, (im2 > 0 ? 1.l : -1.l));
  else {
    long double den = __STL_COSL(re2) + __STL_COSHL(im2);
    return complex<long double>(__STL_SINL(re2) / den, __STL_SINHL(im2) / den);
  }
}

# endif

//----------------------------------------------------------------------
// sinh

__STL_DECLSPEC complex<float> __STL_CALL sinh(const complex<float>& z) {
  return complex<float>(__STL_SINHF(z._M_re) * __STL_COSF(z._M_im),
                        __STL_COSHF(z._M_re) * __STL_SINF(z._M_im));
}

__STL_DECLSPEC complex<double> __STL_CALL sinh(const complex<double>& z) {
  return complex<double>(__STL_SINH(z._M_re) * __STL_COS(z._M_im),
                         __STL_COSH(z._M_re) * __STL_SIN(z._M_im));
}

#ifndef __STL_NO_LONG_DOUBLE
__STL_DECLSPEC complex<long double> __STL_CALL sinh(const complex<long double>& z) {
  return complex<long double>(__STL_SINHL(z._M_re) * __STL_COSL(z._M_im),
                              __STL_COSHL(z._M_re) * __STL_SINL(z._M_im));
}
#endif

//----------------------------------------------------------------------
// cosh

__STL_DECLSPEC complex<float> __STL_CALL cosh(const complex<float>& z) {
  return complex<float>(__STL_COSHF(z._M_re) * __STL_COSF(z._M_im),
                        __STL_SINHF(z._M_re) * __STL_SINF(z._M_im));
}

__STL_DECLSPEC complex<double> __STL_CALL cosh(const complex<double>& z) {
  return complex<double>(__STL_COSH(z._M_re) * __STL_COS(z._M_im),
                         __STL_SINH(z._M_re) * __STL_SIN(z._M_im));
}

#ifndef __STL_NO_LONG_DOUBLE
__STL_DECLSPEC complex<long double> __STL_CALL cosh(const complex<long double>& z) {
  return complex<long double>(__STL_COSHL(z._M_re) * __STL_COSL(z._M_im),
                              __STL_SINHL(z._M_re) * __STL_SINL(z._M_im));
}
#endif

//----------------------------------------------------------------------
// tanh

__STL_DECLSPEC complex<float> __STL_CALL tanh(const complex<float>& z) {
  float re2 = 2.f * z._M_re;
  float im2 = 2.f * z._M_im;

#ifdef __sgi
  const union { unsigned int i; float f; } ulimit = { 0x42b2d4fc };
  const float limit = ulimit.f;
#else
  const float limit = __STL_LOGF(FLT_MAX);
#endif

  if (__STL_ABSF(re2) > limit)
    return complex<float>((re2 > 0 ? 1.f : -1.f), 0.f);
  else {
    float den = __STL_COSHF(re2) + __STL_COSF(im2);
    return complex<float>(__STL_SINHF(re2) / den, __STL_SINF(im2) / den);
  }
}

__STL_DECLSPEC complex<double> __STL_CALL tanh(const complex<double>& z) {
  double re2 = 2. * z._M_re;
  double im2 = 2. * z._M_im;

#ifdef __sgi
  union {
    struct { unsigned int h; unsigned int l; } w;
    double d;
  } ulimit = { 0x408633ce, 0x8fb9f87d };
  const double limit = ulimit.d;
#else
  const double limit = __STL_DO_LOG(double)(DBL_MAX);
#endif
  
  if (fabs(float(re2)) > limit)
    return complex<double>((re2 > 0 ? 1. : -1.), 0.);
  else {
    double den = __STL_COSH(re2) + __STL_COS(im2);
    return complex<double>(__STL_SINH(re2) / den, __STL_SIN(im2) / den);
  }
}

#ifndef __STL_NO_LONG_DOUBLE
__STL_DECLSPEC complex<long double> __STL_CALL tanh(const complex<long double>& z) {
  long double re2 = 2.l * z._M_re;
  long double im2 = 2.l * z._M_im;

#ifdef __sgi
  union {
    struct { unsigned int h[2]; unsigned int l[2]; } w;
    long double ld;
  } ulimit = {0x408633ce, 0x8fb9f87e, 0xbd23b659, 0x4e9bd8b1};
  const long double limit = ulimit.ld;
#else
  const long double limit = __STL_LOGL(LDBL_MAX);
#endif

  if (__STL_ABSL(re2) > limit)
    return complex<long double>((re2 > 0 ? 1.l : -1.l), 0.l);
  else {
    long double den = __STL_COSHL(re2) + __STL_COSL(im2);
    return complex<long double>(__STL_SINHL(re2) / den, __STL_SINL(im2) / den);
  }
}
#endif
__STL_END_NAMESPACE
