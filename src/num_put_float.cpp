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

#include "stlport_prefix.h"

#include <cmath>
#include <ios>
#include <locale>

#if defined (__DECCXX)
#  define NDIG 400
#else
#  define NDIG 82
#endif

#define todigit(x) ((x)+'0')

#if defined (_STLP_UNIX)

#  if defined (__sun)
#    include <floatingpoint.h>
#  endif

#  if defined (__sun) || defined (__digital__) || defined (__sgi) || defined (_STLP_SCO_OPENSERVER) || defined (__NCR_SVR)
// DEC, SGI & Solaris need this
#    include <values.h>
#    include <nan.h>
#  endif

#  if defined (__QNXNTO__) || ( defined(__GNUC__) && defined(__APPLE__) ) || defined(_STLP_USE_UCLIBC) /* 0.9.26 */ || \
      defined(__FreeBSD__)
#    define USE_SPRINTF_INSTEAD
#  endif

#  if defined( _AIX ) // JFA 3-Aug-2000
#    include <math.h>
#    include <float.h>
#  endif

#  include <math.h>
#endif

#include <cstdio>
#include <cstdlib>

//#if defined(_CRAY)
//# include <stdlib.h>
//#endif

#if defined (_STLP_MSVC_LIB) || defined (__MINGW32__) || defined (__BORLANDC__) || defined (__DJGPP) || \
    defined (_STLP_SCO_OPENSERVER) || defined (__NCR_SVR)
#  include <float.h>
#endif

#if defined(__MRC__) || defined(__SC__)  || defined(_CRAY)  //*TY 02/24/2000 - added support for MPW
#  include <fp.h>
#endif

#if defined (__CYGWIN__)
#  include <ieeefp.h>
#endif

#if defined (__MSL__)
#  include <cstdlib>  // for atoi
#  include <cstdio>  // for snprintf
#  include <algorithm>
#  include <cassert>
#endif

#if defined (__ISCPP__)
#  include <cfloat>
#endif

#include <algorithm>

#if defined (__DMC__)
#  define snprintf _snprintf
#endif

#if defined (__hpux) && defined (__GNUC__)
#  include "system_api.h"
#  define isfinite stlp_isfinite
#  define isnan stlp_isnan
#  define isinf stlp_isinf
#endif

_STLP_BEGIN_NAMESPACE
_STLP_MOVE_TO_PRIV_NAMESPACE

#if defined (__MWERKS__) || defined(__BEOS__)
#  define USE_SPRINTF_INSTEAD
#endif

template <int N>
struct _Dig
{
    enum { dig = _Dig<N/10>::dig + 1 };
};

_STLP_TEMPLATE_NULL
struct _Dig<0>
{
    enum { dig = 0 };
};

#ifdef _STLP_NO_LONG_DOUBLE
# define MAXEDIGITS int(_Dig<DBL_MAX_10_EXP>::dig)
# define MAXFSIG DBL_DIG
# define MAXFCVT (DBL_DIG + 1)
#else
# define MAXEDIGITS int(_Dig<LDBL_MAX_10_EXP>::dig)
# define MAXFSIG LDBL_DIG
# define MAXFCVT (LDBL_DIG + 1)
#endif


#if defined (_AIX) || defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__)
// Some OS'es only provide non-reentrant primitives, so we have to use additional synchronization here

#  if !defined(_REENTRANT) && !defined(_THREAD_SAFE) && !(defined(_POSIX_THREADS) && defined(__OpenBSD__))
#    define LOCK_CVT
#    define RETURN_CVT(ecvt, x, n, pt, sign, buf) return ecvt(x, n, pt, sign);
#  else
static _STLP_STATIC_MUTEX __put_float_mutex _STLP_MUTEX_INITIALIZER;
#    define LOCK_CVT _STLP_auto_lock lock(__put_float_mutex);
#    define RETURN_CVT(ecvt, x, n, pt, sign, buf) strcpy(buf, ecvt(x, n, pt, sign)); return buf;
#  endif // !_REENTRANT
#endif // _AIX || __FreeBSD__ || __NetBSD__ || __OpenBSD__

// Tests for infinity and NaN differ on different OSs.  We encapsulate
// these differences here.

#if !defined (USE_SPRINTF_INSTEAD)
#  if defined (__hpux) || defined (__DJGPP) || (defined (_STLP_USE_GLIBC) && ! defined (__MSL__)) || \
      defined (__FreeBSD__) || defined (__NetBSD__) || defined (__OpenBSD__)
static inline bool _Stl_is_nan_or_inf(double x)
#    if defined (isfinite)
{ return !isfinite(x); }
#    else
{ return !finite(x); }
#    endif
static inline bool _Stl_is_neg_nan(double x)    { return isnan(x) && ( copysign(1., x) < 0 ); }
static inline bool _Stl_is_inf(double x)        { return isinf(x); }
// inline bool _Stl_is_neg_inf(double x)    { return isinf(x) < 0; }
static inline bool _Stl_is_neg_inf(double x)    { return isinf(x) && x < 0; }
#  elif (defined (__unix) || defined (__unix__)) && \
         !defined (__APPLE__) && !defined (__DJGPP) && !defined(__osf__) && \
         !defined (_CRAY)
static inline bool _Stl_is_nan_or_inf(double x) { return IsNANorINF(x); }
static inline bool _Stl_is_inf(double x)        { return IsNANorINF(x) && IsINF(x); }
static inline bool _Stl_is_neg_inf(double x)    { return (IsINF(x)) && (x < 0.0); }
static inline bool _Stl_is_neg_nan(double x)    { return IsNegNAN(x); }
#  elif defined (__BORLANDC__) && ( __BORLANDC__ >= 0x580 )
static inline bool _Stl_is_nan_or_inf(double x) {  return !_finite(x); }
static inline bool _Stl_is_inf(double x)        {  return _Stl_is_nan_or_inf(x) && ! _isnan(x);}
static inline bool _Stl_is_neg_inf(double x)    {  return _Stl_is_inf(x) && x < 0 ; }
static inline bool _Stl_is_neg_nan(double x)    { return _isnan(x) && _copysign(1., x) < 0 ; }
#  elif defined (_STLP_MSVC_LIB) || defined (__MINGW32__) || defined (__BORLANDC__)
static inline bool _Stl_is_nan_or_inf(double x) { return !_finite(x); }
static inline bool _Stl_is_inf(double x)        {
  int fclass = _fpclass(x);
  return fclass == _FPCLASS_NINF || fclass == _FPCLASS_PINF;
}
static inline bool _Stl_is_neg_inf(double x)    { return _fpclass(x) == _FPCLASS_NINF; }
static inline bool _Stl_is_neg_nan(double x)    { return _isnan(x) && _copysign(1., x) < 0 ; }
#  elif defined (__MRC__) || defined (__SC__)    //*TY 02/24/2000 - added support for MPW
static bool _Stl_is_nan_or_inf(double x) { return isnan(x) || !isfinite(x); }
static bool _Stl_is_inf(double x)        { return !isfinite(x); }
static bool _Stl_is_neg_inf(double x)    { return !isfinite(x) && signbit(x); }
static bool _Stl_is_neg_nan(double x)    { return isnan(x) && signbit(x); }
#  elif /* defined(__FreeBSD__) || defined(__OpenBSD__) || */ (defined(__GNUC__) && defined(__APPLE__))
static inline bool _Stl_is_nan_or_inf(double x) { return !finite(x); }
static inline bool _Stl_is_inf(double x)        {   return _Stl_is_nan_or_inf(x) && ! isnan(x); }
static inline bool _Stl_is_neg_inf(double x)    {   return _Stl_is_inf(x) && x < 0 ; }
static inline bool _Stl_is_neg_nan(double x)    { return isnan(x) && copysign(1., x) < 0 ; }
#  elif defined( _AIX ) // JFA 11-Aug-2000
static bool _Stl_is_nan_or_inf(double x) { return isnan(x) || !finite(x); }
static bool _Stl_is_inf(double x)        { return !finite(x); }
// bool _Stl_is_neg_inf(double x)    { return _class(x) == FP_MINUS_INF; }
static bool _Stl_is_neg_inf(double x)    { return _Stl_is_inf(x) && ( copysign(1., x) < 0 );  }
static bool _Stl_is_neg_nan(double x)    { return isnan(x) && ( copysign(1., x) < 0 );  }
#  elif defined (__ISCPP__)
static inline bool _Stl_is_nan_or_inf  (double x) { return _fp_isINF(x) || _fp_isNAN(x); }
static inline bool _Stl_is_inf         (double x) { return _fp_isINF(x); }
static inline bool _Stl_is_neg_inf     (double x) { return _fp_isINF(x) && x < 0; }
static inline bool _Stl_is_neg_nan     (double x) { return _fp_isNAN(x) && x < 0; }
#  elif defined (_CRAY)
#    if defined (_CRAYIEEE)
static inline bool _Stl_is_nan_or_inf(double x) { return isnan(x) || isinf(x); }
static inline bool _Stl_is_inf(double x)        { return isinf(x); }
static inline bool _Stl_is_neg_inf(double x)    { return isinf(x) && signbit(x); }
static inline bool _Stl_is_neg_nan(double x)    { return isnan(x) && signbit(x); }
#    else
static inline bool _Stl_is_nan_or_inf(double x) { return false; }
static inline bool _Stl_is_inf(double x)        { return false; }
static inline bool _Stl_is_neg_inf(double x)    { return false; }
static inline bool _Stl_is_neg_nan(double x)    { return false; }
#    endif
#  else // nothing from above
#    define USE_SPRINTF_INSTEAD
#  endif
#endif // !USE_SPRINTF_INSTEAD

#if !defined (USE_SPRINTF_INSTEAD)
// Reentrant versions of floating-point conversion functions.  The argument
// lists look slightly different on different operating systems, so we're
// encapsulating the differences here.

#  if defined (__CYGWIN__) || defined(__DJGPP)
static inline char* _Stl_ecvtR(double x, int n, int* pt, int* sign, char* buf)
{ return ecvtbuf(x, n, pt, sign, buf); }
static inline char* _Stl_fcvtR(double x, int n, int* pt, int* sign, char* buf)
{ return fcvtbuf(x, n, pt, sign, buf); }
#    if !defined (_STLP_NO_LONG_DOUBLE)
static inline char* _Stl_qecvtR(long double x, int n, int* pt, int* sign, char* buf)
{ return ecvtbuf(x, n, pt, sign, buf); }
static inline char* _Stl_qfcvtR(long double x, int n, int* pt, int* sign, char* buf)
{ return fcvtbuf(x, n, pt, sign, buf); }
#    endif
#  elif defined (_STLP_USE_GLIBC)
static inline char* _Stl_ecvtR(double x, int n, int* pt, int* sign, char* buf, size_t bsize)
{ return ecvt_r(x, n, pt, sign, buf, bsize) == 0 ? buf : 0; }
static inline char* _Stl_fcvtR(double x, int n, int* pt, int* sign, char* buf, size_t bsize)
{ return fcvt_r(x, n, pt, sign, buf, bsize) == 0 ? buf : 0; }
#    ifndef _STLP_NO_LONG_DOUBLE
static inline char* _Stl_qecvtR(long double x, int n, int* pt, int* sign, char* buf, size_t bsize)
{ return qecvt_r(x, n, pt, sign, buf, bsize) == 0 ? buf : 0; }
static inline char* _Stl_qfcvtR(long double x, int n, int* pt, int* sign, char* buf, size_t bsize)
{ return qfcvt_r(x, n, pt, sign, buf, bsize) == 0 ? buf : 0; }
#    endif
#    define _STLP_NEED_CVT_BUFFER_SIZE
#  elif defined (_STLP_SCO_OPENSERVER) || defined (__NCR_SVR)
static inline char* _Stl_ecvtR(double x, int n, int* pt, int* sign, char* buf)
{ return ecvt(x, n, pt, sign); }
static inline char* _Stl_fcvtR(double x, int n, int* pt, int* sign, char* buf)
{ return fcvt(x, n, pt, sign); }
#    if !defined (_STLP_NO_LONG_DOUBLE)
static inline char* _Stl_qecvtR(long double x, int n, int* pt, int* sign, char* buf)
{ return ecvtl(x, n, pt, sign); }
static inline char* _Stl_qfcvtR(long double x, int n, int* pt, int* sign, char* buf)
{ return fcvtl(x, n, pt, sign); }
#    endif
#  elif defined (__sun)
static inline char* _Stl_ecvtR(double x, int n, int* pt, int* sign, char* buf)
{ return econvert(x, n, pt, sign, buf); }
static inline char* _Stl_fcvtR(double x, int n, int* pt, int* sign, char* buf)
{ return fconvert(x, n, pt, sign, buf); }
#    ifndef _STLP_NO_LONG_DOUBLE
static inline char* _Stl_qecvtR(long double x, int n, int* pt, int* sign, char* buf)
{ return qeconvert(&x, n, pt, sign, buf); }
static inline char* _Stl_qfcvtR(long double x, int n, int* pt, int* sign, char* buf)
{ return qfconvert(&x, n, pt, sign, buf); }
#    endif
#  elif defined (__DECCXX)
static inline char* _Stl_ecvtR(double x, int n, int* pt, int* sign, char* buf, size_t bsize)
{ return (ecvt_r(x, n, pt, sign, buf, bsize) == 0 ? buf : 0); }
static inline char* _Stl_fcvtR(double x, int n, int* pt, int* sign, char* buf, size_t bsize)
{ return (fcvt_r(x, n, pt, sign, buf, bsize) == 0 ? buf : 0); }
#    ifndef _STLP_NO_LONG_DOUBLE
// fbp : no "long double" conversions !
static inline char* _Stl_qecvtR(long double x, int n, int* pt, int* sign, char* buf, size_t bsize)
{ return (ecvt_r((double)x, n, pt, sign, buf, bsize) == 0 ? buf : 0) ; }
static inline char* _Stl_qfcvtR(long double x, int n, int* pt, int* sign, char* buf, size_t bsize)
{ return (fcvt_r((double)x, n, pt, sign, buf, bsize) == 0 ? buf : 0); }
#    endif
#    define _STLP_NEED_CVT_BUFFER_SIZE
#  elif defined (__hpux)
static inline char* _Stl_ecvtR(double x, int n, int* pt, int* sign, char* buf)
{ return ecvt(x, n, pt, sign); }
static inline char* _Stl_fcvtR(double x, int n, int* pt, int* sign, char* buf)
{ return fcvt(x, n, pt, sign); }
#    if !defined (_STLP_NO_LONG_DOUBLE)
#      if defined( _REENTRANT ) && (defined(_PTHREADS_DRAFT4) || defined(PTHREAD_THREADS_MAX))
static inline char* _Stl_qecvtR(long double x, int n, int* pt, int* sign, char* buf)
{ return (_ldecvt_r(*(long_double*)&x, n, pt, sign, buf, LDBL_MAX_10_EXP + 6)==0 ? buf : 0); }
static inline char* _Stl_qfcvtR(long double x, int n, int* pt, int* sign, char* buf)
{ return (_ldfcvt_r(*(long_double*)&x, n, pt, sign, buf, LDBL_MAX_10_EXP + 6)==0 ? buf : 0); }
#      else
static inline char* _Stl_qecvtR(long double x, int n, int* pt, int* sign, char* buf)
{ return _ldecvt(*(long_double*)&x, n, pt, sign); }
static inline char* _Stl_qfcvtR(long double x, int n, int* pt, int* sign, char* buf)
{ return _ldfcvt(*(long_double*)&x, n, pt, sign); }
#      endif
#    endif
#  elif defined (_AIX) || defined (__FreeBSD__) || defined (__NetBSD__) || defined (__OpenBSD__)
static inline char* _Stl_ecvtR(double x, int n, int* pt, int* sign, char* buf)
{ LOCK_CVT RETURN_CVT(ecvt, x, n, pt, sign, buf) }
static inline char* _Stl_fcvtR(double x, int n, int* pt, int* sign, char* buf)
{ LOCK_CVT RETURN_CVT(fcvt, x, n, pt, sign, buf) }
#    if !defined (_STLP_NO_LONG_DOUBLE)
static inline char* _Stl_qecvtR(long double x, int n, int* pt, int* sign, char* buf)
{ LOCK_CVT RETURN_CVT(ecvt, x, n, pt, sign, buf) }
static inline char* _Stl_qfcvtR(long double x, int n, int* pt, int* sign, char* buf)
{ LOCK_CVT RETURN_CVT(fcvt, x, n, pt, sign, buf) }
#    endif
#  elif defined (__unix) && !defined (__APPLE__) && !defined (_CRAY)
static inline char* _Stl_ecvtR(double x, int n, int* pt, int* sign, char* buf)
{ return ecvt_r(x, n, pt, sign, buf); }
static inline char* _Stl_fcvtR(double x, int n, int* pt, int* sign, char* buf)
{ return fcvt_r(x, n, pt, sign, buf); }
#    if !defined (_STLP_NO_LONG_DOUBLE)
static inline char* _Stl_qecvtR(long double x, int n, int* pt, int* sign, char* buf)
{ return qecvt_r(x, n, pt, sign, buf); }
static inline char* _Stl_qfcvtR(long double x, int n, int* pt, int* sign, char* buf)
{ return qfcvt_r(x, n, pt, sign, buf); }
#    endif
#  elif defined (_STLP_MSVC_LIB) || defined (__MINGW32__) || defined (__BORLANDC__)
// those guys claim _cvt functions being reentrant.
#    if defined (_STLP_USE_SAFE_STRING_FUNCTIONS)
#      define _STLP_APPEND(a, b) a##b
#      define _STLP_BUF_PARAMS char* buf, size_t bsize
#      define _STLP_SECURE_FUN(F, X, N, PT, SIGN) _STLP_APPEND(F, _s)(buf, bsize, X, N, PT, SIGN); return buf
#    else
#      define _STLP_CVT_DONT_NEED_BUF
#      define _STLP_BUF_PARAMS char *
#      define _STLP_SECURE_FUN(F, X, N, PT, SIGN) return F(X, N, PT, SIGN)
#    endif
static inline char* _Stl_ecvtR(double x, int n, int* pt, int* sign, _STLP_BUF_PARAMS)
{ _STLP_SECURE_FUN(_ecvt, x, n, pt, sign); }
static inline char* _Stl_fcvtR(double x, int n, int* pt, int* sign, _STLP_BUF_PARAMS)
{ _STLP_SECURE_FUN(_fcvt, x, n, pt, sign); }
#    if !defined (_STLP_NO_LONG_DOUBLE)
static inline char* _Stl_qecvtR(long double x, int n, int* pt, int* sign, _STLP_BUF_PARAMS)
{ _STLP_SECURE_FUN(_ecvt, (double)x, n, pt, sign); }
static inline char* _Stl_qfcvtR(long double x, int n, int* pt, int* sign, _STLP_BUF_PARAMS)
{ _STLP_SECURE_FUN(_fcvt, (double)x, n, pt, sign); }
#    endif
#    undef _STLP_SECURE_FUN
#    undef _STLP_BUF_PARAMS
#    undef _STLP_APPEND
#  elif defined (__ISCPP__)
static inline char* _Stl_ecvtR(double x, int n, int* pt, int* sign, char* buf)
{ return _fp_ecvt( x, n, pt, sign, buf); }
static inline char* _Stl_fcvtR(double x, int n, int* pt, int* sign, char* buf)
{ return _fp_fcvt(x, n, pt, sign, buf); }
#    if !defined (_STLP_NO_LONG_DOUBLE)
static inline char* _Stl_qecvtR(long double x, int n, int* pt, int* sign, char* buf)
{ return _fp_ecvt( x, n, pt, sign, buf); }
static inline char* _Stl_qfcvtR(long double x, int n, int* pt, int* sign, char* buf)
{ return _fp_fcvt(x, n, pt, sign, buf); }
#    endif
#  elif defined (__MRC__) || defined (__SC__) || defined (_CRAY)
static inline char* _Stl_ecvtR(double x, int n, int* pt, int* sign, char* )
{ return ecvt( x, n, pt, sign ); }
static inline char* _Stl_fcvtR(double x, int n, int* pt, int* sign, char* )
{ return fcvt(x, n, pt, sign); }
#    if !defined (_STLP_NO_LONG_DOUBLE)
static inline char* _Stl_qecvtR(long double x, int n, int* pt, int* sign, char* )
{ return ecvt( x, n, pt, sign ); }
static inline char* _Stl_qfcvtR(long double x, int n, int* pt, int* sign, char* )
{ return fcvt(x, n, pt, sign); }
#    endif
#  endif

#  ifdef _STLP_CVT_DONT_NEED_BUF
#    define _STLP_CVT_BUFFER(B) 0
#  elif !defined (_STLP_USE_SAFE_STRING_FUNCTIONS) && !defined (_STLP_NEED_CVT_BUFFER_SIZE)
#    define _STLP_CVT_BUFFER(B) B
#  else
#    define _STLP_CVT_BUFFER(B) _STLP_ARRAY_AND_SIZE(B)
#  endif

//----------------------------------------------------------------------
// num_put

// __format_float formats a mantissa and exponent as returned by
// one of the conversion functions (ecvt_r, fcvt_r, qecvt_r, qfcvt_r)
// according to the specified precision and format flags.  This is
// based on doprnt but is much simpler since it is concerned only
// with floating point input and does not consider all formats.  It
// also does not deal with blank padding, which is handled by
// __copy_float_and_fill.

static size_t __format_float_scientific( __iostring& buf, const char *bp,
                                         int decpt, int sign, bool is_zero,
                                         ios_base::fmtflags flags,
                                         int precision) {
  // sign if required
  if (sign)
    buf += '-';
  else if (flags & ios_base::showpos)
    buf += '+';

  // first digit of mantissa
  buf += *bp++;

  // start of grouping position, grouping won't occur in scientific notation
  // as it is impossible to have something like 1234.0e04 but we return a correct
  // group position for coherency with __format_float_fixed.
  size_t __group_pos = buf.size();

  // decimal point if required
  if (precision != 0 || flags & ios_base::showpoint) {
    buf += '.';
  }

  // rest of mantissa
  int rz = precision;
  while (rz-- > 0 && *bp != 0)
    buf += *bp++;

  // exponent size = number of digits + exponent sign + exponent symbol + trailing zero
  char expbuf[MAXEDIGITS + 3];
  //We start filling at the buffer end
  char *suffix = expbuf + MAXEDIGITS + 2;
  *suffix = 0;
  if (!is_zero) {
    int nn = decpt - 1;
    if (nn < 0)
      nn = -nn;
    for (; nn > 9; nn /= 10)
      *--suffix = (char) todigit(nn % 10);
    *--suffix = (char) todigit(nn);
  }

  // prepend leading zeros to exponent
  // C89 Standard says that it should be at least 2 digits, C99 Standard says that
  // we stop prepend zeros if more than 3 digits. To repect both STLport prepend zeros
  // until it is 2 digits.
  while (suffix > &expbuf[MAXEDIGITS])
    *--suffix = '0';

  // put in the exponent sign
  *--suffix = (char) ((decpt > 0 || is_zero ) ? '+' : '-');

  // put in the e
  *--suffix = flags & ios_base::uppercase ? 'E' : 'e';

  // copy the suffix
  buf += suffix;
  return __group_pos;
}

static size_t __format_float_fixed( __iostring &buf, const char *bp,
                                    int decpt, int sign,
                                    ios_base::fmtflags flags,
                                    int precision, int maxfsig) {
  if ( sign && (decpt > -precision) && (*bp != 0) )
    buf += '-';
  else if ( flags & ios_base::showpos )
    buf += '+';

  int k = 0;

  // digits before decimal point
  int nnn = decpt;
  do {
    buf += ((nnn <= 0 || *bp == 0 || k >= maxfsig) ? '0' : (++k, *bp++));
  } while ( --nnn > 0 );

  // start of grouping position
  size_t __group_pos = buf.size();

  // decimal point if needed
  if ( flags & ios_base::showpoint || precision > 0 ) {
    buf += '.';
  }

  // digits after decimal point if any
  nnn = (min) (precision, maxfsig + 1);

  while ( --nnn >= 0 ) {
    buf += (++decpt <= 0 || *bp == 0 || k >= maxfsig) ? '0' : (++k, *bp++);
  }

  // trailing zeros if needed
  if ( precision > (maxfsig + 1) ) {
    buf.append( precision - (maxfsig + 1), '0' );
  }

  return __group_pos;
}

template <class _FloatT>
static void __format_nan_or_inf(__iostring& buf, _FloatT x, ios_base::fmtflags flags)
{
  static const char* inf[2] = { "inf", "Inf" };
  static const char* nan[2] = { "nan", "NaN" };
  const char** inf_or_nan;
  if (_Stl_is_inf(x)) {            // Infinity
    inf_or_nan = inf;
    if (_Stl_is_neg_inf(x))
      buf += '-';
    else if (flags & ios_base::showpos)
      buf += '+';
  } else {                      // NaN
    inf_or_nan = nan;
    if (_Stl_is_neg_nan(x))
      buf += '-';
    else if (flags & ios_base::showpos)
      buf += '+';
  }
  buf += inf_or_nan[flags & ios_base::uppercase ? 1 : 0];
}

template <class _FloatT>
static inline size_t __format_float( __iostring &buf, const char * bp,
                                     int decpt, int sign, _FloatT x,
                                     ios_base::fmtflags flags,
                                     int precision)
{
  typedef numeric_limits<_FloatT> _FLimits;
  //If numeric_limits support is correct we use the exposed values to detect NaN and infinity:
  if (_FLimits::has_infinity && _FLimits::has_quiet_NaN) {
    if (!(x == x) || // NaN check
        (x == _FLimits::infinity() || x == -_FLimits::infinity())) {
      __format_nan_or_inf(buf, x, flags);
      return 0;
    }
  }
  // numeric_limits support is not good enough, we rely on platform dependent function
  // _Stl_is_nan_or_inf that do not support long double.
  else if (_Stl_is_nan_or_inf(x)) {
    __format_nan_or_inf(buf, x, flags);
    return 0;
  }

  // representable number
  size_t __group_pos = 0;
  switch (flags & ios_base::floatfield) {
    case ios_base::scientific:
      __group_pos = __format_float_scientific( buf, bp, decpt, sign, x == 0.0,
                                               flags, precision);
      break;
    case ios_base::fixed:
      __group_pos = __format_float_fixed( buf, bp, decpt, sign,
                                          flags, precision, _FLimits::digits10);
      break;
    default: // g format
      // establish default precision
      if (flags & ios_base::showpoint || precision > 0) {
        if (precision == 0) precision = 1;
      } else
        precision = 6;

      // reset exponent if value is zero
      if (x == 0)
        decpt = 1;

      int kk = precision;
      if (!(flags & ios_base::showpoint)) {
        size_t n = strlen(bp);
        if (n < (size_t)kk)
          kk = (int)n;
        while (kk >= 1 && bp[kk-1] == '0')
          --kk;
      }

      if (decpt < -3 || decpt > precision) {
        precision = kk - 1;
        __group_pos = __format_float_scientific( buf, bp, decpt, sign, x == 0,
                                                 flags, precision);
      } else {
        precision = kk - decpt;
        __group_pos = __format_float_fixed( buf, bp, decpt, sign,
                                            flags, precision, _FLimits::digits10);
      }
      break;
  } /* switch */
  return __group_pos;
}

#else /* USE_SPRINTF_INSTEAD */

struct GroupPos {
  bool operator () (char __c) const {
    return __c == '.' ||
           __c == 'e' || __c == 'E';
  }
};

// Creates a format string for sprintf()
static int __fill_fmtbuf(char* fmtbuf, ios_base::fmtflags flags, char long_modifier) {
  fmtbuf[0] = '%';
  int i = 1;

  if (flags & ios_base::showpos)
    fmtbuf[i++] = '+';

  if (flags & ios_base::showpoint)
    fmtbuf[i++] = '#';

  fmtbuf[i++] = '.';
  fmtbuf[i++] = '*';

  if (long_modifier)
    fmtbuf[i++] = long_modifier;

  switch (flags & ios_base::floatfield)
    {
    case ios_base::scientific:
      fmtbuf[i++] = (flags & ios_base::uppercase) ?  'E' : 'e';
      break;
    case ios_base::fixed:
#  if defined (__FreeBSD__)
      fmtbuf[i++] = 'f';
#  else
      fmtbuf[i++] = (flags & ios_base::uppercase) ? 'F' : 'f';
#  endif
      break;
    default:
      fmtbuf[i++] = (flags & ios_base::uppercase) ?  'G' : 'g';
      break;
    }

  fmtbuf[i] = 0;
  return i;
}

#endif  /* USE_SPRINTF_INSTEAD */

size_t  _STLP_CALL
__write_float(__iostring &buf, ios_base::fmtflags flags, int precision,
              double x) {
  /* In theory, if we want 'arbitrary' precision, we should use 'arbitrary'
   * buffer size below, but really we limited by exponent part in double.
   *    - ptr
   */
#ifdef USE_SPRINTF_INSTEAD
  char static_buf[DBL_MAX_10_EXP+6]; // 6: -xxx.yyyE-zzz (sign, dot, E, exp sign, \0)
  char fmtbuf[32];
  __fill_fmtbuf(fmtbuf, flags, 0);
  snprintf(_STLP_ARRAY_AND_SIZE(static_buf), fmtbuf, precision, x);
  buf = static_buf;
  return find_if(buf.begin(), buf.end(), GroupPos()) - buf.begin();
#else
#ifndef _STLP_CVT_DONT_NEED_BUF
  char cvtbuf[DBL_MAX_10_EXP+6]; // 6: -xxx.yyyE-zzz (sign, dot, E, exp sign, \0)
#endif
  char *bp;
  int decpt, sign;

  switch (flags & ios_base::floatfield) {
  case ios_base::fixed:
    bp = _Stl_fcvtR(x, (min) (precision, DBL_MAX_10_EXP), &decpt, &sign, _STLP_CVT_BUFFER(cvtbuf) );
    break;
  case ios_base::scientific :
    bp = _Stl_ecvtR(x, (min) (precision, DBL_MAX_10_EXP), &decpt, &sign, _STLP_CVT_BUFFER(cvtbuf) );
    break;
  default :
    bp = _Stl_ecvtR(x, (min) (precision, DBL_MAX_10_EXP), &decpt, &sign, _STLP_CVT_BUFFER(cvtbuf) );
    break;
  }
  return __format_float(buf, bp, decpt, sign, x, flags, precision);
#endif
}

#if !defined (_STLP_NO_LONG_DOUBLE)
size_t _STLP_CALL
__write_float(__iostring &buf, ios_base::fmtflags flags, int precision,
              long double x) {
  /* In theory, if we want 'arbitrary' precision, we should use 'arbitrary'
   * buffer size below, but really we limited by exponent part in long double.
   *    - ptr
   */
#  ifdef USE_SPRINTF_INSTEAD
  char static_buf[LDBL_MAX_10_EXP+6]; // 6: -xxx.yyyE-zzz (sign, dot, E, exp sign, \0)
  char fmtbuf[64];
  int i = __fill_fmtbuf(fmtbuf, flags, 'L');
  snprintf(_STLP_ARRAY_AND_SIZE(static_buf), fmtbuf, precision, x);
  // we should be able to return buf + sprintf(), but we do not trust'em...
  buf = static_buf;
  return find_if(buf.begin(), buf.end(), GroupPos()) - buf.begin();
#  else
#ifndef _STLP_CVT_DONT_NEED_BUF
  char cvtbuf[LDBL_MAX_10_EXP+6]; // 6: -xxx.yyyE-zzz (sign, dot, E, exp sign, \0)
#endif
  char * bp;
  int decpt, sign;

  switch (flags & ios_base::floatfield) {
  case ios_base::fixed:
    bp = _Stl_qfcvtR(x, (min) (precision, LDBL_MAX_10_EXP), &decpt, &sign, _STLP_CVT_BUFFER(cvtbuf) );
    break;
  case ios_base::scientific:
    bp = _Stl_qecvtR(x, (min) (precision, LDBL_MAX_10_EXP), &decpt, &sign, _STLP_CVT_BUFFER(cvtbuf) );
    break;
  default :
    bp = _Stl_qecvtR(x, (min) (precision, LDBL_MAX_10_EXP), &decpt, &sign, _STLP_CVT_BUFFER(cvtbuf) );
    break;
  }
  return __format_float(buf, bp, decpt, sign, x, flags, precision);
#  endif /* USE_SPRINTF_INSTEAD */
}
#endif /* _STLP_NO_LONG_DOUBLE */

void _STLP_CALL __get_floor_digits(__iostring &out, _STLP_LONGEST_FLOAT_TYPE __x) {
#if defined (USE_SPRINTF_INSTEAD)
  char cvtbuf[LDBL_MAX_10_EXP+6];
#  if !defined (_STLP_NO_LONG_DOUBLE)
  snprintf(_STLP_ARRAY_AND_SIZE(cvtbuf), "%Lf", __x); // check for 1234.56!
#  else
  snprintf(_STLP_ARRAY_AND_SIZE(cvtbuf), "%f", __x);  // check for 1234.56!
#  endif
  char *p = strchr( cvtbuf, '.' );
  if ( p == 0 ) {
    out.append( cvtbuf );
  } else {
    out.append( cvtbuf, p );
  }
#else
#  ifndef _STLP_CVT_DONT_NEED_BUF
  char cvtbuf[LDBL_MAX_10_EXP+6];
#  endif
  char * bp;
  int decpt, sign;
#  if !defined (_STLP_NO_LONG_DOUBLE)
  bp = _Stl_qfcvtR(__x, 0, &decpt, &sign, _STLP_CVT_BUFFER(cvtbuf));
#  else
  bp = _Stl_fcvtR(__x, 0, &decpt, &sign, _STLP_CVT_BUFFER(cvtbuf));
#  endif

  if (sign) {
    out += '-';
  }
  out.append(bp, bp + decpt);
#endif // USE_PRINTF_INSTEAD
}


#if !defined (_STLP_NO_WCHAR_T)
void _STLP_CALL __convert_float_buffer( __iostring const& str, __iowstring &out,
                                        const ctype<wchar_t>& ct, wchar_t dot, bool __check_dot)
{
  string::const_iterator str_ite(str.begin()), str_end(str.end());

  //First loop, check the dot char
  if (__check_dot) {
    while (str_ite != str_end) {
      if (*str_ite != '.') {
        out += ct.widen(*str_ite++);
      } else {
        out += dot;
        break;
      }
    }
  } else {
    if (str_ite != str_end) {
      out += ct.widen(*str_ite);
    }
  }

  if (str_ite != str_end) {
    //Second loop, dot has been found, no check anymore
    while (++str_ite != str_end) {
      out += ct.widen(*str_ite);
    }
  }
}

#endif

void _STLP_CALL
__adjust_float_buffer(__iostring &str, char dot) {
  if ('.' != dot) {
    size_t __dot_pos = str.find('.');
    if (__dot_pos != string::npos) {
      str[__dot_pos] = dot;
    }
  }
}

_STLP_MOVE_TO_STD_NAMESPACE
_STLP_END_NAMESPACE

// Local Variables:
// mode:C++
// End:
