/*
 * Copyright (c) 1998,1999
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

#ifndef _STLP_LIMITS_C
#define _STLP_LIMITS_C

#ifndef _STLP_INTERNAL_LIMITS
#  include <stl/_limits.h>
#endif

//==========================================================
//  numeric_limits static members
//==========================================================

_STLP_BEGIN_NAMESPACE

_STLP_MOVE_TO_PRIV_NAMESPACE

#if !defined (_STLP_STATIC_CONST_INIT_BUG) && !defined (_STLP_NO_STATIC_CONST_DEFINITION)

#  define __declare_numeric_base_member(__type, __mem) \
template <class __number> \
  const __type _Numeric_limits_base<__number>:: __mem

__declare_numeric_base_member(bool, is_specialized);
__declare_numeric_base_member(int, digits);
__declare_numeric_base_member(int, digits10);
__declare_numeric_base_member(bool, is_signed);
__declare_numeric_base_member(bool, is_integer);
__declare_numeric_base_member(bool, is_exact);
__declare_numeric_base_member(int, radix);
__declare_numeric_base_member(int, min_exponent);
__declare_numeric_base_member(int, max_exponent);
__declare_numeric_base_member(int, min_exponent10);
__declare_numeric_base_member(int, max_exponent10);
__declare_numeric_base_member(bool, has_infinity);
__declare_numeric_base_member(bool, has_quiet_NaN);
__declare_numeric_base_member(bool, has_signaling_NaN);
__declare_numeric_base_member(float_denorm_style, has_denorm);
__declare_numeric_base_member(bool, has_denorm_loss);
__declare_numeric_base_member(bool, is_iec559);
__declare_numeric_base_member(bool, is_bounded);
__declare_numeric_base_member(bool, is_modulo);
__declare_numeric_base_member(bool, traps);
__declare_numeric_base_member(bool, tinyness_before);
__declare_numeric_base_member(float_round_style, round_style);

#  undef __declare_numeric_base_member

#  define __declare_integer_limits_member(__type, __mem) \
template <class _Int, _STLP_LIMITS_MIN_TYPE __imin, _STLP_LIMITS_MAX_TYPE __imax, int __idigits, bool __ismod> \
  const __type _Integer_limits<_Int, __imin, __imax, __idigits, __ismod>:: __mem

__declare_integer_limits_member(bool, is_specialized);
__declare_integer_limits_member(int, digits);
__declare_integer_limits_member(int, digits10);
__declare_integer_limits_member(bool, is_signed);
__declare_integer_limits_member(bool, is_integer);
__declare_integer_limits_member(bool, is_exact);
__declare_integer_limits_member(int, radix);
__declare_integer_limits_member(bool, is_bounded);
__declare_integer_limits_member(bool, is_modulo);
#  undef __declare_integer_limits_member

#  if defined (__GNUC__) && (__GNUC__ != 2 || __GNUC_MINOR__ > 96) && (__GNUC__ != 3 || __GNUC_MINOR__ == 0) && (__GNUC__ <= 3)
_STLP_MOVE_TO_STD_NAMESPACE

#    define __declare_numeric_limits_member(__integer) \
  _STLP_TEMPLATE_NULL const int numeric_limits<__integer>::digits; \
  _STLP_TEMPLATE_NULL const int numeric_limits<__integer>::digits10; \
  _STLP_TEMPLATE_NULL const int numeric_limits<__integer>::radix; \
  _STLP_TEMPLATE_NULL const bool numeric_limits<__integer>::is_specialized; \
  _STLP_TEMPLATE_NULL const bool numeric_limits<__integer>::is_signed; \
  _STLP_TEMPLATE_NULL const bool numeric_limits<__integer>::is_integer; \
  _STLP_TEMPLATE_NULL const bool numeric_limits<__integer>::is_exact; \
  _STLP_TEMPLATE_NULL const bool numeric_limits<__integer>::is_bounded; \
  _STLP_TEMPLATE_NULL const bool numeric_limits<__integer>::is_modulo

__declare_numeric_limits_member(_STLP_LONG_LONG);
__declare_numeric_limits_member(unsigned _STLP_LONG_LONG);

#    undef __declare_numeric_limits_member

_STLP_MOVE_TO_PRIV_NAMESPACE
#  endif

#  define __declare_float_limits_member(__type, __mem) \
template <class __number,  \
         int __Digits, int __Digits10,    \
         int __MinExp, int __MaxExp,      \
         int __MinExp10, int __MaxExp10,  \
         bool __IsIEC559, \
         float_denorm_style __DenormStyle, \
         float_round_style __RoundStyle> \
const __type _Floating_limits< __number, __Digits, __Digits10,    \
         __MinExp, __MaxExp, __MinExp10, __MaxExp10,  \
         __IsIEC559, __DenormStyle, __RoundStyle>::\
         __mem

__declare_float_limits_member(bool, is_specialized);
__declare_float_limits_member(int, digits);
__declare_float_limits_member(int, digits10);
__declare_float_limits_member(bool, is_signed);
__declare_float_limits_member(int, radix);
__declare_float_limits_member(int, min_exponent);
__declare_float_limits_member(int, max_exponent);
__declare_float_limits_member(int, min_exponent10);
__declare_float_limits_member(int, max_exponent10);
__declare_float_limits_member(bool, has_infinity);
__declare_float_limits_member(bool, has_quiet_NaN);
__declare_float_limits_member(bool, has_signaling_NaN);
__declare_float_limits_member(float_denorm_style, has_denorm);
__declare_float_limits_member(bool, has_denorm_loss);
__declare_float_limits_member(bool, is_iec559);
__declare_float_limits_member(bool, is_bounded);
__declare_float_limits_member(bool, traps);
__declare_float_limits_member(bool, tinyness_before);
__declare_float_limits_member(float_round_style, round_style);
#  undef __declare_float_limits_member

#endif


// #if defined (_STLP_EXPOSE_GLOBALS_IMPLEMENTATION)


// #endif /* _STLP_EXPOSE_GLOBALS_IMPLEMENTATION */

#undef _STLP_LIMITS_MIN_TYPE
#undef _STLP_LIMITS_MAX_TYPE

_STLP_MOVE_TO_STD_NAMESPACE

_STLP_END_NAMESPACE

#endif /* _STLP_LIMITS_C_INCLUDED */

// Local Variables:
// mode:C++
// End:
