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
#include "complex_impl.h"

__STL_BEGIN_NAMESPACE


//----------------------------------------------------------------------
// exp

__STL_DECLSPEC complex<float>  __STL_CALL
exp(const complex<float>& z)
{
  float expx = __STL_EXPF(z._M_re);
  return complex<float>(expx * __STL_COSF(z._M_im),
                        expx * __STL_SINF(z._M_im));
}

__STL_DECLSPEC complex<double> __STL_CALL exp(const complex<double>& z)
{
  double expx = __STL_EXP(z._M_re);
  return complex<double>(expx * __STL_COS(z._M_im),
                         expx * __STL_SIN(z._M_im));
}

__STL_DECLSPEC complex<long double> __STL_CALL exp(const complex<long double>& z)
{
  long double expx = __STL_EXPL(z._M_re);
  return complex<long double>(expx * __STL_COSL(z._M_im),
                              expx * __STL_SINL(z._M_im));
}

//----------------------------------------------------------------------
// log10

__STL_DECLSPEC complex<float> __STL_CALL log10(const complex<float>& z)
{
  complex<float> r;
  static float ln10_inv = 1.f / __STL_LOGF(10.f);

  r._M_im = __STL_ATAN2F(z._M_im, z._M_re) * ln10_inv;
  r._M_re = __STL_LOG10F(__STL_HYPOTF(z._M_re, z._M_im));
  return r;
}

__STL_DECLSPEC complex<double> __STL_CALL log10(const complex<double>& z)
{
  complex<double> r;
  static double ln10_inv = 1. / __STL_LOG(10.);

  r._M_im = __STL_ATAN2(z._M_im, z._M_re) * ln10_inv;
  r._M_re = __STL_LOG10(__STL_HYPOT(z._M_re, z._M_im));
  return r;
}

__STL_DECLSPEC complex<long double> __STL_CALL log10(const complex<long double>& z)
{
  complex<long double> result;
  static long double ln10_inv = 1.l / __STL_LOGL(10.l);

  result._M_im = __STL_ATAN2L(z._M_im, z._M_re) * ln10_inv;
  result._M_re = __STL_LOG10L(__STL_HYPOTL(z._M_re, z._M_im));
  return result;
}


//----------------------------------------------------------------------
// log

__STL_DECLSPEC complex<float> __STL_CALL log(const complex<float>& z)
{
  complex<float> r;

  r._M_im = __STL_ATAN2F(z._M_im, z._M_re);
  r._M_re = __STL_LOGF(__STL_HYPOTF(z._M_re, z._M_im));
  return r;
}

__STL_DECLSPEC complex<double> __STL_CALL log(const complex<double>& z)
{
  complex<double> r;

  r._M_im = __STL_ATAN2(z._M_im, z._M_re);
  r._M_re = __STL_LOG(__STL_HYPOT(z._M_re, z._M_im));
  return r;
}

__STL_DECLSPEC complex<long double> __STL_CALL log(const complex<long double>& z)
{
  complex<long double> result;

  result._M_im = __STL_ATAN2L(z._M_im, z._M_re);
  result._M_re = __STL_LOGL(__STL_HYPOTL(z._M_re, z._M_im));
  return result;
}


//----------------------------------------------------------------------
// pow

__STL_DECLSPEC complex<float> __STL_CALL pow(const float& a, const complex<float>& b) {
  float logr = __STL_LOGF(a);
  float x = __STL_EXPF(logr*b._M_re);
  float y = logr*b._M_im;

  return complex<float>(x * __STL_COSF(y), x * __STL_SINF(y));
}

__STL_DECLSPEC complex<float> __STL_CALL pow(const complex<float>& z_in, int n) {
  complex<float> z = z_in;
  z = __power(z, (n < 0 ? -n : n), multiplies< complex<float> >());
  if (n < 0)
    return 1.f / z;
  else
    return z;
}

__STL_DECLSPEC complex<float> __STL_CALL pow(const complex<float>& a, const float& b) {
  float logr = __STL_LOGF(__STL_HYPOTF(a._M_re,a._M_im));
  float logi = __STL_ATAN2F(a._M_im, a._M_re);
  float x = __STL_EXPF(logr * b);
  float y = logi * b;

  return complex<float>(x * __STL_COSF(y), x * __STL_SINF(y));
}  

__STL_DECLSPEC complex<float> __STL_CALL pow(const complex<float>& a, const complex<float>& b) {
  float logr = __STL_LOGF(__STL_HYPOTF(a._M_re,a._M_im));
  float logi = __STL_ATAN2F(a._M_im, a._M_re);
  float x = __STL_EXPF(logr*b._M_re - logi*b._M_im);
  float y = logr*b._M_im + logi*b._M_re;

  return complex<float>(x * __STL_COSF(y), x * __STL_SINF(y));
}


__STL_DECLSPEC complex<double> __STL_CALL pow(const double& a, const complex<double>& b) {
  double logr = __STL_LOG(a);
  double x = __STL_EXP(logr*b._M_re);
  double y = logr*b._M_im;

  return complex<double>(x * __STL_COS(y), x * __STL_SIN(y));
}

__STL_DECLSPEC complex<double> __STL_CALL pow(const complex<double>& z_in, int n) {
  complex<double> z = z_in;
  z = __power(z, (n < 0 ? -n : n), multiplies< complex<double> >());
  if (n < 0)
#if !defined(__SC__)			//*TY 04/15/2000 - 
    return 1. / z;
#else							//*TY 04/15/2000 - added workaround for SCpp compiler
	return double(1.0) / z;		//*TY 04/15/2000 - it incorrectly assign long double attribute to floating point literals
#endif							//*TY 04/15/2000 - 
  else
    return z;
}

__STL_DECLSPEC complex<double> __STL_CALL pow(const complex<double>& a, const double& b) {
  double logr = __STL_LOG(__STL_HYPOT(a._M_re,a._M_im));
  double logi = __STL_ATAN2(a._M_im, a._M_re);
  double x = __STL_EXP(logr * b);
  double y = logi * b;

  return complex<double>(x * __STL_COS(y), x * __STL_SIN(y));
}  

__STL_DECLSPEC complex<double> __STL_CALL pow(const complex<double>& a, const complex<double>& b) {
  double logr = __STL_LOG(__STL_HYPOT(a._M_re,a._M_im));
  double logi = __STL_ATAN2(a._M_im, a._M_re);
  double x = __STL_EXP(logr*b._M_re - logi*b._M_im);
  double y = logr*b._M_im + logi*b._M_re;

  return complex<double>(x * __STL_COS(y), x * __STL_SIN(y));
}


__STL_DECLSPEC complex<long double> __STL_CALL pow(const long double& a,
                                                   const complex<long double>& b) {
  long double logr = __STL_LOGL(a);
  long double x = __STL_EXPL(logr*b._M_re);
  long double y = logr*b._M_im;

  return complex<long double>(x * __STL_COSL(y), x * __STL_SINL(y));
}

__STL_DECLSPEC complex<long double> __STL_CALL pow(const complex<long double>& z_in, int n) {
  complex<long double> z = z_in;
  z = __power(z, (n < 0 ? -n : n), multiplies< complex<long double> >());
  if (n < 0)
    return 1.l / z;
  else
    return z;
}

__STL_DECLSPEC complex<long double> __STL_CALL pow(const complex<long double>& a,
                         const long double& b) {
  long double logr = __STL_LOGL(__STL_HYPOTL(a._M_re,a._M_im));
  long double logi = __STL_ATAN2L(a._M_im, a._M_re);
  long double x = __STL_EXPL(logr * b);
  long double y = logi * b;

  return complex<long double>(x * __STL_COSL(y), x * __STL_SINL(y));
}  

__STL_DECLSPEC complex<long double> __STL_CALL pow(const complex<long double>& a,
                         const complex<long double>& b) {
  long double logr = __STL_LOGL(__STL_HYPOTL(a._M_re,a._M_im));
  long double logi = __STL_ATAN2L(a._M_im, a._M_re);
  long double x = __STL_EXPL(logr*b._M_re - logi*b._M_im);
  long double y = logr*b._M_im + logi*b._M_re;

  return complex<long double>(x * __STL_COSL(y), x * __STL_SINL(y));
}

__STL_END_NAMESPACE
