/*
 * Copyright (c) 1997
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

/* NOTE: This may be not portable code. Parts of numeric_limits<> are
 * inherently machine-dependent.  At present this file is suitable
 * for the MIPS, SPARC, Alpha and ia32 architectures.
 */

#ifndef __STLPORT_LIMITS_H
# define __STLPORT_LIMITS_H

#ifndef __STLPORT_CLIMITS
# include <climits>
#endif

#ifndef __STLPORT_CFLOAT
# include <cfloat>
#endif

#if !defined (__STL_NO_WCHAR_T)
# include <cwchar>
#endif

#define __SGI_CPP_LIMITS

__STL_BEGIN_NAMESPACE

enum float_round_style {
  round_indeterminate       = -1,
  round_toward_zero         =  0,
  round_to_nearest          =  1,
  round_toward_infinity     =  2,
  round_toward_neg_infinity =  3
};

enum float_denorm_style {
  denorm_indeterminate = -1,
  denorm_absent        =  0,
  denorm_present       =  1
};

// Base class for all specializations of numeric_limits.

template <class __number>
class _Numeric_limits_base {
public:
  static const bool is_specialized __STL_INLINE_STATIC_INIT ( false );

  static __number (__STL_CALL min)() __STL_NOTHROW { return __number(); }
  static __number (__STL_CALL max)() __STL_NOTHROW { return __number(); }

  static const int digits   __STL_INLINE_STATIC_INIT( 0 );
  static const int digits10 __STL_INLINE_STATIC_INIT ( 0 );

  static const bool is_signed  __STL_INLINE_STATIC_INIT ( false );
  static const bool is_integer __STL_INLINE_STATIC_INIT ( false );
  static const bool is_exact   __STL_INLINE_STATIC_INIT ( false );

  static const int  radix __STL_INLINE_STATIC_INIT ( 0 );

  static __number __STL_CALL epsilon() __STL_NOTHROW     { return __number(); }
  static __number __STL_CALL round_error() __STL_NOTHROW { return __number(); }

  static const int min_exponent  __STL_INLINE_STATIC_INIT ( 0 );
  static const int min_exponent10 __STL_INLINE_STATIC_INIT ( 0 );
  static const int max_exponent   __STL_INLINE_STATIC_INIT ( 0 );
  static const int max_exponent10 __STL_INLINE_STATIC_INIT ( 0 );

  static const bool has_infinity      __STL_INLINE_STATIC_INIT ( false );
  static const bool has_quiet_NaN     __STL_INLINE_STATIC_INIT ( false );
  static const bool has_signaling_NaN __STL_INLINE_STATIC_INIT ( false );
  static const float_denorm_style has_denorm __STL_INLINE_STATIC_INIT ( denorm_absent );
  static const bool has_denorm_loss   __STL_INLINE_STATIC_INIT ( false );

  static __number __STL_CALL infinity() __STL_NOTHROW      { return __number(); }
  static __number __STL_CALL quiet_NaN() __STL_NOTHROW     { return __number(); }
  static __number __STL_CALL signaling_NaN() __STL_NOTHROW { return __number(); }
  static __number __STL_CALL denorm_min() __STL_NOTHROW    { return __number(); }

  static const bool is_iec559  __STL_INLINE_STATIC_INIT( false );
  static const bool is_bounded __STL_INLINE_STATIC_INIT( false );
  static const bool is_modulo  __STL_INLINE_STATIC_INIT( false );

  static const bool traps           __STL_INLINE_STATIC_INIT( false);
  static const bool tinyness_before __STL_INLINE_STATIC_INIT( false);
  static const float_round_style round_style __STL_INLINE_STATIC_INIT( round_toward_zero );
};

// Base class for integers.

# ifdef __STL_LIMITED_DEFAULT_TEMPLATES
#  ifdef __STL_LONG_LONG
#   define __STL_LIMITS_MIN_TYPE __STL_LONG_LONG
#   define __STL_LIMITS_MAX_TYPE unsigned __STL_LONG_LONG
#  else
#   define __STL_LIMITS_MIN_TYPE long
#   define __STL_LIMITS_MAX_TYPE unsigned long
#  endif
# else
#   define __STL_LIMITS_MIN_TYPE _Int
#   define __STL_LIMITS_MAX_TYPE _Int
# endif /* __STL_LIMITED_DEFAULT_TEMPLATES */

template <class _Int,
          __STL_LIMITS_MIN_TYPE __imin,
          __STL_LIMITS_MAX_TYPE __imax,
          int __idigits, bool __ismod>
class _Integer_limits : public _Numeric_limits_base<_Int> 
{
public:
  static const bool is_specialized __STL_INLINE_STATIC_INIT( true );

  static _Int (__STL_CALL min) () __STL_NOTHROW { return (_Int)__imin; }
  static _Int (__STL_CALL max) () __STL_NOTHROW { return (_Int)__imax; }

  static const int digits __STL_INLINE_STATIC_INIT((__idigits < 0) ? \
			    ((int)((sizeof(_Int) * (CHAR_BIT))) - ((__imin == 0) ? 0 : 1)) \
                            : (__idigits));

  static const int digits10  __STL_INLINE_STATIC_INIT( (digits * 301UL) / 1000 ); 
                                // log 2 = 0.301029995664...

  static const bool is_signed __STL_INLINE_STATIC_INIT(  __imin != 0 );
  static const bool is_integer __STL_INLINE_STATIC_INIT(  true );
  static const bool is_exact __STL_INLINE_STATIC_INIT(  true );
  static const int radix __STL_INLINE_STATIC_INIT(  2 );


  static const bool is_bounded __STL_INLINE_STATIC_INIT(  true );
  static const bool is_modulo __STL_INLINE_STATIC_INIT(  __ismod );
};

// Base class for floating-point numbers.
template <class __number,
         int __Digits, int __Digits10,
         int __MinExp, int __MaxExp,
         int __MinExp10, int __MaxExp10,
         bool __IsIEC559,
         float_round_style __RoundStyle>
class _Floating_limits : public _Numeric_limits_base<__number>
{
public:
  static const bool is_specialized __STL_INLINE_STATIC_INIT( true );

  static const int digits   __STL_INLINE_STATIC_INIT(  __Digits );
  static const int digits10 __STL_INLINE_STATIC_INIT(  __Digits10 );

  static const bool is_signed __STL_INLINE_STATIC_INIT(  true );

  static const int radix __STL_INLINE_STATIC_INIT(  FLT_RADIX /* 2 */ );

  static const int min_exponent   __STL_INLINE_STATIC_INIT(  __MinExp );
  static const int max_exponent   __STL_INLINE_STATIC_INIT(  __MaxExp );
  static const int min_exponent10 __STL_INLINE_STATIC_INIT(  __MinExp10 );
  static const int max_exponent10 __STL_INLINE_STATIC_INIT(  __MaxExp10 );

  static const bool has_infinity      __STL_INLINE_STATIC_INIT(  true );
  static const bool has_quiet_NaN     __STL_INLINE_STATIC_INIT(  true );
  static const bool has_signaling_NaN __STL_INLINE_STATIC_INIT(  true );
  static const float_denorm_style has_denorm __STL_INLINE_STATIC_INIT(  denorm_indeterminate );
  static const bool has_denorm_loss   __STL_INLINE_STATIC_INIT(  false );

  static const bool is_iec559       __STL_INLINE_STATIC_INIT(  __IsIEC559 );
  static const bool is_bounded      __STL_INLINE_STATIC_INIT(  true );
  static const bool traps           __STL_INLINE_STATIC_INIT(  true );
  static const bool tinyness_before __STL_INLINE_STATIC_INIT(  false );

  static const float_round_style round_style __STL_INLINE_STATIC_INIT(  __RoundStyle );
};

// Class numeric_limits

// The unspecialized class.

template<class _Tp> 
class numeric_limits : public _Numeric_limits_base<_Tp> {};

// Specializations for all built-in integral types.

#ifndef __STL_NO_BOOL

__STL_TEMPLATE_NULL
class   numeric_limits<bool>
  : public _Integer_limits<bool, false, true, 0, false>
{};

#endif /* __STL_NO_BOOL */

__STL_TEMPLATE_NULL
class   numeric_limits<char>
  : public _Integer_limits<char, CHAR_MIN, CHAR_MAX, -1, true>
{};

# ifndef __STL_NO_SIGNED_BUILTINS
__STL_TEMPLATE_NULL
class   numeric_limits<signed char>
  : public _Integer_limits<signed char, SCHAR_MIN, SCHAR_MAX, -1, true>
{};
# endif

__STL_TEMPLATE_NULL
class   numeric_limits<unsigned char>
  : public _Integer_limits<unsigned char, 0, UCHAR_MAX, -1, true>
{};

#if !(defined ( __STL_NO_WCHAR_T ) || defined (__STL_WCHAR_T_IS_USHORT))

__STL_TEMPLATE_NULL
class   numeric_limits<wchar_t>
  : public _Integer_limits<wchar_t, WCHAR_MIN, WCHAR_MAX, -1, true>
{};

#endif

__STL_TEMPLATE_NULL
class   numeric_limits<short>
  : public _Integer_limits<short, SHRT_MIN, SHRT_MAX, -1, true>
{};

__STL_TEMPLATE_NULL
class   numeric_limits<unsigned short>
  : public _Integer_limits<unsigned short, 0, USHRT_MAX, -1, true>
{};

__STL_TEMPLATE_NULL
class   numeric_limits<int>
  : public _Integer_limits<int, INT_MIN, INT_MAX, -1, true>
{};

__STL_TEMPLATE_NULL
class   numeric_limits<unsigned int>
  : public _Integer_limits<unsigned int, 0, UINT_MAX, -1, true>
{};

__STL_TEMPLATE_NULL
class   numeric_limits<long>
  : public _Integer_limits<long, LONG_MIN, LONG_MAX, -1, true>
{};

__STL_TEMPLATE_NULL
class   numeric_limits<unsigned long>
  : public _Integer_limits<unsigned long, 0, ULONG_MAX, -1, true>
{};

#ifdef __STL_LONG_LONG

# if defined (__STL_MSVC) || defined (__BORLANDC__)

#    define LONGLONG_MAX     0x7fffffffffffffffi64
#    define LONGLONG_MIN     (-LONGLONG_MAX-1i64)
#    define ULONGLONG_MAX    0xffffffffffffffffUi64

# else

#  ifndef   LONGLONG_MAX
#    define LONGLONG_MAX     0x7fffffffffffffffLL
#  endif
#  ifndef   LONGLONG_MIN
#    define LONGLONG_MIN     (-LONGLONG_MAX-1LL)
#  endif
#  ifndef   ULONGLONG_MAX
#    define ULONGLONG_MAX    0xffffffffffffffffULL
#  endif

# endif

__STL_TEMPLATE_NULL
class   numeric_limits<__STL_LONG_LONG>
  : public _Integer_limits<__STL_LONG_LONG, LONGLONG_MIN, LONGLONG_MAX, -1, true>
{};

__STL_TEMPLATE_NULL
class   numeric_limits<unsigned __STL_LONG_LONG>
  : public _Integer_limits<unsigned __STL_LONG_LONG, 0, ULONGLONG_MAX, -1, true>
{};

#endif /* __STL_LONG_LONG */

// Specializations for all built-in floating-point types.

union _F_rep
{
  unsigned short rep[2];
  float val;
};
union _D_rep
{
  unsigned short rep[4];
  double val;
};
union _L_rep
{
  unsigned short rep[8];
  long double val;
};

template <class __dummy>
class _LimG 
{
public:  
  static const _F_rep _F_inf;
  static const _F_rep _F_qNaN;
  static const _F_rep _F_sNaN;
  static const _D_rep _D_inf;
  static const _D_rep _D_qNaN;
  static const _D_rep _D_sNaN;
  
# ifndef __STL_NO_LONG_DOUBLE
  static const _L_rep _L_inf;
  static const _L_rep _L_qNaN;
  static const _L_rep _L_sNaN;
# endif
};

# if defined (__STL_USE_TEMPLATE_EXPORT) 
__STL_EXPORT_TEMPLATE_CLASS _LimG<bool>;
# endif

__STL_TEMPLATE_NULL class   numeric_limits<float>
  : public _Floating_limits<float, 
                            FLT_MANT_DIG,   // Binary digits of precision
                            FLT_DIG,        // Decimal digits of precision
                            FLT_MIN_EXP,    // Minimum exponent
                            FLT_MAX_EXP,    // Maximum exponent
                            FLT_MIN_10_EXP, // Minimum base 10 exponent
                            FLT_MAX_10_EXP, // Maximum base 10 exponent
                            true,           // conforms to iec559
                            round_to_nearest>
{
public:
  static float (__STL_CALL min) () __STL_NOTHROW { return FLT_MIN; }
  static float __STL_CALL denorm_min() __STL_NOTHROW { return FLT_MIN; }
  static float (__STL_CALL max) () __STL_NOTHROW { __STL_USING_VENDOR_CSTD return FLT_MAX; }
  static float __STL_CALL epsilon() __STL_NOTHROW { return FLT_EPSILON; }
  static float __STL_CALL round_error() __STL_NOTHROW { return 0.5f; } // Units: ulps.
  static  float __STL_CALL infinity() { return _LimG<bool>::_F_inf.val; }
  static  float __STL_CALL quiet_NaN() { return _LimG<bool>::_F_qNaN.val; }
  static  float __STL_CALL signaling_NaN() { return _LimG<bool>::_F_sNaN.val; }
};

__STL_TEMPLATE_NULL class   numeric_limits<double>
  : public _Floating_limits<double, 
                            DBL_MANT_DIG,   // Binary digits of precision
                            DBL_DIG,        // Decimal digits of precision
                            DBL_MIN_EXP,    // Minimum exponent
                            DBL_MAX_EXP,    // Maximum exponent
                            DBL_MIN_10_EXP, // Minimum base 10 exponent
                            DBL_MAX_10_EXP, // Maximum base 10 exponent
                            true,           // conforms to iec559
                            round_to_nearest>
{
public:
  static double (__STL_CALL min)() __STL_NOTHROW { return DBL_MIN; }
  static double __STL_CALL denorm_min() __STL_NOTHROW { return DBL_MIN; }
  static double (__STL_CALL max)() __STL_NOTHROW { __STL_USING_VENDOR_CSTD return DBL_MAX; }
  static double __STL_CALL epsilon() __STL_NOTHROW { return DBL_EPSILON; }
  static double __STL_CALL round_error() __STL_NOTHROW { return 0.5; } // Units: ulps.
  static  double __STL_CALL infinity() { return _LimG<bool>::_D_inf.val; }
  static  double __STL_CALL quiet_NaN(){ return _LimG<bool>::_D_qNaN.val; }
  static  double __STL_CALL signaling_NaN() { return _LimG<bool>::_D_sNaN.val; }
};

# ifndef __STL_NO_LONG_DOUBLE

__STL_TEMPLATE_NULL 
class   numeric_limits<long double>
  : public _Floating_limits<long double, 
                            LDBL_MANT_DIG,  // Binary digits of precision
                            LDBL_DIG,       // Decimal digits of precision
                            LDBL_MIN_EXP,   // Minimum exponent
                            LDBL_MAX_EXP,   // Maximum exponent
                            LDBL_MIN_10_EXP,// Minimum base 10 exponent
                            LDBL_MAX_10_EXP,// Maximum base 10 exponent
                            false,          // Doesn't conform to iec559
                            round_to_nearest>
{
public:
  static long double (__STL_CALL min) () __STL_NOTHROW { __STL_USING_VENDOR_CSTD return LDBL_MIN; }
  static long double __STL_CALL denorm_min() __STL_NOTHROW { __STL_USING_VENDOR_CSTD return LDBL_MIN; }
  static long double (__STL_CALL max) () __STL_NOTHROW { __STL_USING_VENDOR_CSTD return LDBL_MAX; }
  static long double __STL_CALL epsilon() __STL_NOTHROW { return LDBL_EPSILON; }
  static long double __STL_CALL round_error() __STL_NOTHROW { return 4; } // Units: ulps.
  static long double __STL_CALL infinity() { return _LimG<bool>::_L_inf.val; } 
  static long double __STL_CALL quiet_NaN() { return _LimG<bool>::_L_qNaN.val; }
  static long double __STL_CALL signaling_NaN() { return _LimG<bool>::_L_sNaN.val; }
};

# endif

// We write special values (Inf and NaN) as bit patterns and 
// cast the the appropriate floating-point types. 
__STL_END_NAMESPACE

# if !defined (__STL_LINK_TIME_INSTANTIATION)
#  include <stl/_limits.c>
# endif

#endif /* __SGI_CPP_LIMITS */

// Local Variables:
// mode:C++
// End:
