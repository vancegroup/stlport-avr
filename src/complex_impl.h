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

# ifndef COMPLEX_IMPL_H
#  define  COMPLEX_IMPL_H

#include <complex>

# if (defined (__sgi) && !defined(__GNUC__)) || defined (__DECCXX)

# define __STL_ABSF   __STL_VENDOR_CSTD::fabsf
# define __STL_ATAN2F __STL_VENDOR_CSTD::atan2f
# define __STL_SINF   __STL_VENDOR_CSTD::sinf
# define __STL_COSF   __STL_VENDOR_CSTD::cosf
# define __STL_SQRTF  __STL_VENDOR_CSTD::sqrtf
# define __STL_EXPF   __STL_VENDOR_CSTD::expf
# define __STL_LOG10F __STL_VENDOR_CSTD::log10f
# define __STL_LOGF   __STL_VENDOR_CSTD::logf
# define __STL_SINHF  __STL_VENDOR_CSTD::sinhf
# define __STL_COSHF  __STL_VENDOR_CSTD::coshf
# define __STL_HYPOTF __STL_VENDOR_CSTD::hypotf


# define __STL_ABSL   __STL_VENDOR_CSTD::fabsl
# define __STL_ATAN2L __STL_VENDOR_CSTD::atan2l
# define __STL_SINL   __STL_VENDOR_CSTD::sinl
# define __STL_COSL   __STL_VENDOR_CSTD::cosl
# define __STL_SQRTL  __STL_VENDOR_CSTD::sqrtl
# define __STL_EXPL   __STL_VENDOR_CSTD::expl
# define __STL_LOG10L __STL_VENDOR_CSTD::log10l
# define __STL_LOGL   __STL_VENDOR_CSTD::logl
# define __STL_SINHL  __STL_VENDOR_CSTD::sinhl
# define __STL_COSHL  __STL_VENDOR_CSTD::coshl
// # define __STL_HYPOT  ::hypot
# define __STL_HYPOTL __STL_VENDOR_CSTD::hypotl

#else
# define __STL_ABSF (float)__STL_DO_ABS(double)
# define __STL_ABSL (long double)__STL_DO_ABS(double)
# define __STL_ATAN2F (float)__STL_DO_ATAN2(double)
# define __STL_ATAN2L (long double)__STL_DO_ATAN2(double)
# define __STL_SINF   (float)__STL_DO_SIN(double)
# define __STL_SINL   (long double)__STL_DO_SIN(double)
# define __STL_COSF   (float)__STL_DO_COS(double)
# define __STL_COSL   (long double)__STL_DO_COS(double)
# define __STL_SQRTF  (float)__STL_DO_SQRT(double)
# define __STL_SQRTL  (long double)__STL_DO_SQRT(double)
# define __STL_EXPF   (float)__STL_DO_EXP(double)
# define __STL_EXPL   (long double)__STL_DO_EXP(double)
# define __STL_LOG10F   (float)__STL_DO_LOG10(double)
# define __STL_LOG10L   (long double)__STL_DO_LOG10(double)
# define __STL_LOGF   (float)__STL_DO_LOG(double)
# define __STL_LOGL   (long double)__STL_DO_LOG(double)
# define __STL_SINHF   (float)__STL_DO_SINH(double)
# define __STL_SINHL   (long double)__STL_DO_SINH(double)
# define __STL_COSHF   (float)__STL_DO_COSH(double)
# define __STL_COSHL   (long double)__STL_DO_COSH(double)
# define __STL_HYPOTF   (float)__STL_DO_HYPOT(double)
# define __STL_HYPOTL   (long double)__STL_DO_HYPOT(double)
#endif

# define __STL_ABS      (double)__STL_DO_ABS(double)
# define __STL_ATAN2    (double)__STL_DO_ATAN2(double)
# define __STL_SIN      (double)__STL_DO_SIN(double)
# define __STL_COS      (double)__STL_DO_COS(double)
# define __STL_SQRT     (double)__STL_DO_SQRT(double)
# define __STL_EXP      (double)__STL_DO_EXP(double)
# define __STL_LOG10    (double)__STL_DO_LOG10(double)
# define __STL_LOG      (double)__STL_DO_LOG(double)
# define __STL_SINH     (double)__STL_DO_SINH(double)
# define __STL_COSH     (double)__STL_DO_COSH(double)
# define __STL_HYPOT    __STL_DO_HYPOT(double)

#endif
