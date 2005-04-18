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
// exp, log, pow for complex<float>, complex<double>, and complex<long double>

#include <numeric>
#include <cmath>
#include <complex>

_STLP_BEGIN_NAMESPACE

//----------------------------------------------------------------------
// exp

_STLP_DECLSPEC complex<float>  _STLP_CALL
exp(const complex<float>& z) {
  float expx = exp(z._M_re);
  return complex<float>(expx * cos(z._M_im),
                        expx * sin(z._M_im));
}

_STLP_DECLSPEC complex<double> _STLP_CALL exp(const complex<double>& z) {
  double expx = exp(z._M_re);
  return complex<double>(expx * cos(z._M_im),
                         expx * sin(z._M_im));
}

# ifndef _STLP_NO_LONG_DOUBLE
_STLP_DECLSPEC complex<long double> _STLP_CALL exp(const complex<long double>& z) {
  long double expx = exp(z._M_re);
  return complex<long double>(expx * cos(z._M_im),
                              expx * sin(z._M_im));
}
# endif

//----------------------------------------------------------------------
// log10

_STLP_DECLSPEC complex<float> _STLP_CALL log10(const complex<float>& z) {
  complex<float> r;
  static float ln10_inv = 1.f / log(10.f);

  r._M_im = atan2(z._M_im, z._M_re) * ln10_inv;
  r._M_re = log10(hypot(z._M_re, z._M_im));
  return r;
}

_STLP_DECLSPEC complex<double> _STLP_CALL log10(const complex<double>& z) {
  complex<double> r;
  static double ln10_inv = 1. / log10(10.);

  r._M_im = atan2(z._M_im, z._M_re) * ln10_inv;
  r._M_re = log10(hypot(z._M_re, z._M_im));
  return r;
}

#ifndef _STLP_NO_LONG_DOUBLE
_STLP_DECLSPEC complex<long double> _STLP_CALL log10(const complex<long double>& z) {
  complex<long double> result;
  static long double ln10_inv = 1.l / log(10.l);

  result._M_im = atan2(z._M_im, z._M_re) * ln10_inv;
  result._M_re = log10(hypot(z._M_re, z._M_im));
  return result;
}
# endif

//----------------------------------------------------------------------
// log

_STLP_DECLSPEC complex<float> _STLP_CALL log(const complex<float>& z) {
  complex<float> r;

  r._M_im = atan2(z._M_im, z._M_re);
  r._M_re = log(hypot(z._M_re, z._M_im));
  return r;
}

_STLP_DECLSPEC complex<double> _STLP_CALL log(const complex<double>& z) {
  complex<double> r;

  r._M_im = atan2(z._M_im, z._M_re);
  r._M_re = log(hypot(z._M_re, z._M_im));
  return r;
}

#ifndef _STLP_NO_LONG_DOUBLE
_STLP_DECLSPEC complex<long double> _STLP_CALL log(const complex<long double>& z) {
  complex<long double> result;

  result._M_im = atan2(z._M_im, z._M_re);
  result._M_re = log(hypot(z._M_re, z._M_im));
  return result;
}
# endif

//----------------------------------------------------------------------
// pow

_STLP_DECLSPEC complex<float> _STLP_CALL pow(const float& a, const complex<float>& b) {
  float logr = log(a);
  float x = exp(logr*b._M_re);
  float y = logr*b._M_im;

  return complex<float>(x * cos(y), x * sin(y));
}

_STLP_DECLSPEC complex<float> _STLP_CALL pow(const complex<float>& z_in, int n) {
  complex<float> z = z_in;
  z = __power(z, (n < 0 ? -n : n), multiplies< complex<float> >());
  if (n < 0)
    return 1.f / z;
  else
    return z;
}

_STLP_DECLSPEC complex<float> _STLP_CALL pow(const complex<float>& a, const float& b) {
  float logr = log(hypot(a._M_re,a._M_im));
  float logi = atan2(a._M_im, a._M_re);
  float x = exp(logr * b);
  float y = logi * b;

  return complex<float>(x * cos(y), x * sin(y));
}  

_STLP_DECLSPEC complex<float> _STLP_CALL pow(const complex<float>& a, const complex<float>& b) {
  float logr = log(hypot(a._M_re,a._M_im));
  float logi = atan2(a._M_im, a._M_re);
  float x = exp(logr*b._M_re - logi*b._M_im);
  float y = logr*b._M_im + logi*b._M_re;

  return complex<float>(x * cos(y), x * sin(y));
}


_STLP_DECLSPEC complex<double> _STLP_CALL pow(const double& a, const complex<double>& b) {
  double logr = log(a);
  double x = exp(logr*b._M_re);
  double y = logr*b._M_im;

  return complex<double>(x * cos(y), x * sin(y));
}

_STLP_DECLSPEC complex<double> _STLP_CALL pow(const complex<double>& z_in, int n) {
  complex<double> z = z_in;
  z = __power(z, (n < 0 ? -n : n), multiplies< complex<double> >());
  if (n < 0)
#if !defined(__SC__)      //*TY 04/15/2000 - 
    return 1. / z;
#else                     //*TY 04/15/2000 - added workaround for SCpp compiler
  return double(1.0) / z; //*TY 04/15/2000 - it incorrectly assign long double attribute to floating point literals
#endif                    //*TY 04/15/2000 - 
  else
    return z;
}

_STLP_DECLSPEC complex<double> _STLP_CALL pow(const complex<double>& a, const double& b) {
  double logr = log(hypot(a._M_re,a._M_im));
  double logi = atan2(a._M_im, a._M_re);
  double x = exp(logr * b);
  double y = logi * b;

  return complex<double>(x * cos(y), x * sin(y));
}  

_STLP_DECLSPEC complex<double> _STLP_CALL pow(const complex<double>& a, const complex<double>& b) {
  double logr = log(hypot(a._M_re,a._M_im));
  double logi = atan2(a._M_im, a._M_re);
  double x = exp(logr*b._M_re - logi*b._M_im);
  double y = logr*b._M_im + logi*b._M_re;

  return complex<double>(x * cos(y), x * sin(y));
}

# ifndef _STLP_NO_LONG_DOUBLE
_STLP_DECLSPEC complex<long double> _STLP_CALL pow(const long double& a,
                                                   const complex<long double>& b) {
  long double logr = log(a);
  long double x = exp(logr*b._M_re);
  long double y = logr*b._M_im;

  return complex<long double>(x * cos(y), x * sin(y));
}

_STLP_DECLSPEC complex<long double> _STLP_CALL pow(const complex<long double>& z_in, int n) {
  complex<long double> z = z_in;
  z = __power(z, (n < 0 ? -n : n), multiplies< complex<long double> >());
  if (n < 0)
    return 1.l / z;
  else
    return z;
}

_STLP_DECLSPEC complex<long double> _STLP_CALL pow(const complex<long double>& a,
                                                   const long double& b) {
  long double logr = log(hypot(a._M_re,a._M_im));
  long double logi = atan2(a._M_im, a._M_re);
  long double x = exp(logr * b);
  long double y = logi * b;

  return complex<long double>(x * cos(y), x * sin(y));
}  

_STLP_DECLSPEC complex<long double> _STLP_CALL pow(const complex<long double>& a,
                                                   const complex<long double>& b) {
  long double logr = log(hypot(a._M_re,a._M_im));
  long double logi = atan2(a._M_im, a._M_re);
  long double x = exp(logr*b._M_re - logi*b._M_im);
  long double y = logr*b._M_im + logi*b._M_re;

  return complex<long double>(x * cos(y), x * sin(y));
}

#endif

_STLP_END_NAMESPACE
