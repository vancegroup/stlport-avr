/* boost limits_test.cpp   test your <limits> file for important
 *
 * Copyright Jens Maurer 2000
 * Permission to use, copy, modify, sell, and distribute this software
 * is hereby granted without fee provided that the above copyright notice
 * appears in all copies and that both that copyright notice and this
 * permission notice appear in supporting documentation,
 *
 * Jens Maurer makes no representations about the suitability of this
 * software for any purpose. It is provided "as is" without express or
 * implied warranty.
 *
 */

#include "limits_test.h"

#include <limits>

#include <ieee754.h>

using namespace std;

bool valid_sign_info(bool, bool)
{ return true; }

template <class _Tp>
bool valid_sign_info(bool limit_is_signed, const _Tp &) {
  return (limit_is_signed && _Tp(-1) < 0) ||
         (!limit_is_signed && _Tp(-1) > 0);
}

template <class _Tp>
bool test_integral_limits_base(const _Tp &, bool unknown_sign = true, bool is_signed = true) {
  typedef numeric_limits<_Tp> lim;

  EXAM_CHECK_ASYNC(lim::is_specialized);
  EXAM_CHECK_ASYNC(lim::is_exact);
  EXAM_CHECK_ASYNC(lim::is_integer);
  EXAM_CHECK_ASYNC(!lim::is_iec559);
  EXAM_CHECK_ASYNC(lim::min() < lim::max());
  EXAM_CHECK_ASYNC((unknown_sign && ((lim::is_signed && (lim::min() != 0)) || (!lim::is_signed && (lim::min() == 0)))) ||
             (!unknown_sign && ((lim::is_signed && is_signed) || (!lim::is_signed && !is_signed))));

  if (unknown_sign) {
    EXAM_CHECK_ASYNC(valid_sign_info(lim::is_signed, _Tp()));
  }
  return true;
}

template <class _Tp>
bool test_integral_limits(const _Tp &val, bool unknown_sign = true, bool is_signed = true) {
  if (!test_integral_limits_base(val, unknown_sign, is_signed))
    return false;

  typedef numeric_limits<_Tp> lim;

  EXAM_CHECK_ASYNC(lim::is_modulo);

  if (lim::is_bounded ||
     (!lim::is_bounded && !lim::is_signed)) {
    _Tp tmp = lim::min();
    EXAM_CHECK_ASYNC( --tmp > lim::min() );
  }

  if (lim::is_bounded) {
    _Tp tmp = lim::max();
    EXAM_CHECK_ASYNC( ++tmp < lim::max() );
  }

  return true;
}

template <class _Tp>
bool test_signed_integral_limits(const _Tp &__val) {
  return test_integral_limits(__val, false, true);
}
template <class _Tp>
bool test_unsigned_integral_limits(const _Tp &__val) {
  return test_integral_limits(__val, false, false);
}

template <class _Tp>
bool test_float_values(_Tp lhs, _Tp rhs)
{ return lhs == rhs; }

template <class _Tp>
int EXAM_IMPL(test_float_limits)
{
  typedef numeric_limits<_Tp> lim;

  EXAM_CHECK(lim::is_specialized);
  EXAM_CHECK(!lim::is_modulo);
  EXAM_CHECK(!lim::is_integer);
  EXAM_CHECK(lim::is_signed);

  EXAM_CHECK(lim::max() > 1000);
  EXAM_CHECK(lim::min() > 0);
  EXAM_CHECK(lim::min() < 0.001);
  EXAM_CHECK(lim::epsilon() > 0);

  if (lim::is_iec559) {
    EXAM_CHECK(lim::has_infinity);
    EXAM_CHECK(lim::has_quiet_NaN);
    EXAM_CHECK(lim::has_signaling_NaN);
    EXAM_CHECK(lim::has_denorm == denorm_present);
  }

  if (lim::has_denorm == denorm_absent) {
    EXAM_CHECK(lim::denorm_min() == lim::min());
    volatile _Tp tmp = lim::min();
    tmp /= 2;
    if (tmp > 0 && tmp < lim::min()) {
      // has_denorm could be denorm_present
      EXAM_MESSAGE("It looks like your compiler/platform supports denormalized floating point representation.");
    }
  } else if (lim::has_denorm == denorm_present) {
    EXAM_CHECK(lim::denorm_min() > 0);
    EXAM_CHECK(lim::denorm_min() < lim::min());

    volatile _Tp tmp = lim::min();
    while (tmp != 0) {
      _Tp old_tmp = tmp;
      tmp /= 2;
      EXAM_CHECK(tmp < old_tmp);
      EXAM_CHECK(tmp >= lim::denorm_min() || tmp == (_Tp)0);
      //ostringstream str;
      //str << "denorm_min = " << lim::denorm_min() << ", tmp = " << tmp;
      //EXAM_MESSAGE(str.str().c_str());
    }
  }

  if (lim::has_infinity) {
    const volatile _Tp infinity = lim::infinity();
    /* Make sure those values are not 0 or similar nonsense.
     * Infinity must compare as if larger than the maximum representable value. */

    volatile _Tp val = lim::max();
    val *= 2;

    EXAM_CHECK( val == infinity);

    /*
    ostringstream str;
    str << "lim::max() = " << lim::max() << ", val = " << val << ", infinity = " << infinity;
    EXAM_MESSAGE( str.str().c_str() );
    str.str(string());
    str << "sizeof(_Tp) = " << sizeof(_Tp);
    EXAM_MESSAGE( str.str().c_str() );
    if (sizeof(_Tp) == 4) {
      str.str(string());
      str << "val in hexa: " << showbase << hex << *((const unsigned int*)&val);
      str << ", infinity in hexa: " << showbase << hex << *((const unsigned int*)&infinity);
    }
#if defined (_STLP_LONG_LONG)
    else if (sizeof(_Tp) == sizeof(_STLP_LONG_LONG)) {
      str.str(string());
      str << "val in hexa: " << showbase << hex << *((const unsigned _STLP_LONG_LONG*)&val);
      str << ", infinity in hexa: " << showbase << hex << *((const unsigned _STLP_LONG_LONG*)&infinity);
    }
#endif
    else {
      str.str(string());
      str << "val: ";
      for (int i = 0; i != sizeof(_Tp) /  sizeof(unsigned short); ++i) {
        if (i != 0) str << ' ';
        str << showbase << hex << setw(4) << setfill('0') << *((const unsigned short*)&val + i);
      }
      str << ", infinity: ";
      for (int i = 0; i != sizeof(_Tp) /  sizeof(unsigned short); ++i) {
        if (i != 0) str << ' ';
        str << showbase << hex << setw(4) << setfill('0') << *((const unsigned short*)&infinity + i);
      }
    }
    EXAM_MESSAGE( str.str().c_str() );
    str.str(string());
    str << dec;
    str << "lim::digits = " << lim::digits << ", lim::digits10 = " << lim::digits10 << endl;
    str << "lim::min_exponent = " << lim::min_exponent << ", lim::min_exponent10 = " << lim::min_exponent10 << endl;
    str << "lim::max_exponent = " << lim::max_exponent << ", lim::max_exponent10 = " << lim::max_exponent10 << endl;
    EXAM_MESSAGE( str.str().c_str() );
    */

    EXAM_CHECK(infinity == infinity);
    EXAM_CHECK(infinity > lim::max());
    EXAM_CHECK(-infinity < -lim::max());
  }

  return EXAM_RESULT;
}

//float generate_nan(float f) {
//  return 0.0f / f;
//}
template <class _Tp>
int EXAM_IMPL(test_qnan)
{
  typedef numeric_limits<_Tp> lim;

  if (lim::has_quiet_NaN) {
    const volatile _Tp qnan = lim::quiet_NaN();

    //if (sizeof(_Tp) == 4) {
    //  ostringstream str;
    //  str << "qnan " << qnan << ", in hexa: " << showbase << hex << *((unsigned int*)&qnan);
    //  EXAM_MESSAGE( str.str().c_str() );
    //  str.str("");
    //  float val = generate_nan(0.0f);
    //  str << "val " << val << ", in hexa: " << showbase << hex << *((unsigned int*)&val);
    //  EXAM_MESSAGE( str.str().c_str() );
    //  str.str("");
    //  val = -qnan;
    //  str << "-qnan " << val << ", in hexa: " << showbase << hex << *((unsigned int*)&val);
    //  EXAM_MESSAGE( str.str().c_str() );
    //}
    /* NaNs shall always compare "false" when compared for equality
    * If one of these fail, your compiler may be optimizing incorrectly,
    * or the STLport is incorrectly configured.
    */
    EXAM_CHECK( !(qnan == 42));
    EXAM_CHECK( !(qnan == qnan));
    EXAM_CHECK( qnan != 42);
    EXAM_CHECK( qnan != qnan);

    /* The following tests may cause arithmetic traps.
    * EXAM_CHECK_ASYNC(! (qnan < 42));
    * EXAM_CHECK_ASYNC(! (qnan > 42));
    * EXAM_CHECK_ASYNC(! (qnan <= 42));
    * EXAM_CHECK_ASYNC(! (qnan >= 42));
    */

    if ( is_same<float,_Tp>::value ) {
      ieee754_float v;
      v.f = qnan;
      EXAM_CHECK( v.ieee_nan.quiet_nan == 1 );
    }

    if ( is_same<double,_Tp>::value ) {
      ieee754_double v;
      v.d = qnan;
      EXAM_CHECK( v.ieee_nan.quiet_nan == 1 );
    }

#  if !defined ( _STLP_NO_LONG_DOUBLE )
    if ( is_same<long double,_Tp>::value ) {
      ieee854_long_double v;
      v.d = qnan;
      EXAM_CHECK( v.ieee_nan.quiet_nan == 1 );
    }
#  endif
  }

  return EXAM_RESULT;
}

volatile const double& fdbl()
{
  volatile static ieee754_double v1;

  v1.ieee.negative = 0;
  v1.ieee.exponent = 0x7ff;
  v1.ieee.mantissa0 = 0x40000;
  v1.ieee.mantissa1 = 0x0;

  return v1.d;
}

template <class _Tp>
int EXAM_IMPL(test_snan)
{
  typedef numeric_limits<_Tp> lim;

  if (lim::has_signaling_NaN) {
    const volatile _Tp snan = lim::signaling_NaN();

    //if (sizeof(_Tp) == 4) {
    //  ostringstream str;
    //  str << "qnan " << qnan << ", in hexa: " << showbase << hex << *((unsigned int*)&qnan);
    //  EXAM_MESSAGE( str.str().c_str() );
    //  str.str("");
    //  float val = generate_nan(0.0f);
    //  str << "val " << val << ", in hexa: " << showbase << hex << *((unsigned int*)&val);
    //  EXAM_MESSAGE( str.str().c_str() );
    //  str.str("");
    //  val = -qnan;
    //  str << "-qnan " << val << ", in hexa: " << showbase << hex << *((unsigned int*)&val);
    //  EXAM_MESSAGE( str.str().c_str() );
    //}
    /* NaNs shall always compare "false" when compared for equality
    * If one of these fail, your compiler may be optimizing incorrectly,
    * or the STLport is incorrectly configured.
    */
    EXAM_CHECK( !(snan == 42));
    EXAM_CHECK( !(snan == snan));
    EXAM_CHECK( snan != 42);
    EXAM_CHECK( snan != snan);

    /* The following tests may cause arithmetic traps.
    * EXAM_CHECK_ASYNC(! (snan < 42));
    * EXAM_CHECK_ASYNC(! (snan > 42));
    * EXAM_CHECK_ASYNC(! (snan <= 42));
    * EXAM_CHECK_ASYNC(! (snan >= 42));
    */

    if ( is_same<float,_Tp>::value ) {
      ieee754_float v;
      v.f = snan;
      EXAM_CHECK( v.ieee_nan.quiet_nan == 0 );
    }

    if ( is_same<double,_Tp>::value ) {
      ieee754_double v;
      v.d = snan;
      printf( "%1x %03x %05x %08x\n", v.ieee.negative, v.ieee.exponent, v.ieee.mantissa0, v.ieee.mantissa1 );

      ieee754_double v1;

      v1.ieee.negative = 0;
      v1.ieee.exponent = 0x7ff;
      v1.ieee.mantissa0 = 0x40000;
      v1.ieee.mantissa1 = 0x0;

      printf( "%1x %03x %05x %08x\n", v1.ieee.negative, v1.ieee.exponent, v1.ieee.mantissa0, v1.ieee.mantissa1 );

      // double db = v1.d;

      v1.d = fdbl();

      printf( "%1x %03x %05x %08x\n", v1.ieee.negative, v1.ieee.exponent, v1.ieee.mantissa0, v1.ieee.mantissa1 );

      EXAM_CHECK( v.ieee_nan.quiet_nan == 0 );
    }

#  if !defined ( _STLP_NO_LONG_DOUBLE )
    if ( is_same<long double,_Tp>::value ) {
      ieee854_long_double v;
      v.d = snan;
      EXAM_CHECK( v.ieee_nan.quiet_nan == 0 );
    }
#  endif
  }

  return EXAM_RESULT;
}

class ArbitraryType
{};

int EXAM_IMPL(limits_test::limits) {
#  if defined (__BORLANDC__)
  /* Ignore FPU exceptions, set FPU precision to 64 bits */
  unsigned int _float_control_word = _control87(0, 0);
  _control87(PC_64|MCW_EM|IC_AFFINE, MCW_PC|MCW_EM|MCW_IC);
#  endif

  EXAM_CHECK(test_integral_limits_base(bool()));
  EXAM_CHECK(test_integral_limits(char()));
  typedef signed char signed_char;
  EXAM_CHECK(test_signed_integral_limits(signed_char()));
  typedef unsigned char unsigned_char;
  EXAM_CHECK(test_unsigned_integral_limits(unsigned_char()));
#  if defined (_STLP_HAS_WCHAR_T) && !defined (_STLP_WCHAR_T_IS_USHORT)
  EXAM_CHECK(test_integral_limits(wchar_t()));
#  endif
  EXAM_CHECK(test_signed_integral_limits(short()));
  typedef unsigned short unsigned_short;
  EXAM_CHECK(test_unsigned_integral_limits(unsigned_short()));
  EXAM_CHECK(test_signed_integral_limits(int()));
  typedef unsigned int unsigned_int;
  EXAM_CHECK(test_unsigned_integral_limits(unsigned_int()));
  EXAM_CHECK(test_signed_integral_limits(long()));
  typedef unsigned long unsigned_long;
  EXAM_CHECK(test_unsigned_integral_limits(unsigned_long()));
#  if defined (_STLP_LONG_LONG)
  typedef _STLP_LONG_LONG long_long;
  EXAM_CHECK(test_signed_integral_limits(long_long()));
  typedef unsigned _STLP_LONG_LONG unsigned_long_long;
  EXAM_CHECK(test_unsigned_integral_limits(unsigned_long_long()));
#endif

  EXAM_RESULT |= test_float_limits<float>( __exam_ts, 0 );
  EXAM_RESULT |= test_float_limits<double>( __exam_ts, 0 );
#  if !defined ( _STLP_NO_LONG_DOUBLE )
  EXAM_RESULT |= test_float_limits<long double>( __exam_ts, 0 );
#  endif

  EXAM_CHECK( !numeric_limits<ArbitraryType>::is_specialized );

#  if defined (__BORLANDC__)
  /* Reset floating point control word */
  _clear87();
  _control87(_float_control_word, MCW_PC|MCW_EM|MCW_IC);
#  endif

  return EXAM_RESULT;
}

int EXAM_IMPL(limits_test::qnan_test)
{
#  if defined (__BORLANDC__)
  /* Ignore FPU exceptions, set FPU precision to 64 bits */
  unsigned int _float_control_word = _control87(0, 0);
  _control87(PC_64|MCW_EM|IC_AFFINE, MCW_PC|MCW_EM|MCW_IC);
#  endif

  EXAM_RESULT |= test_qnan<float>( __exam_ts, 0 );
  EXAM_RESULT |= test_qnan<double>( __exam_ts, 0 );
#  if !defined ( _STLP_NO_LONG_DOUBLE )
  EXAM_RESULT |= test_qnan<long double>( __exam_ts, 0 );
#  endif

  EXAM_RESULT |= test_snan<float>( __exam_ts, 0 );
  EXAM_RESULT |= test_snan<double>( __exam_ts, 0 );
#  if !defined ( _STLP_NO_LONG_DOUBLE )
  EXAM_RESULT |= test_snan<long double>( __exam_ts, 0 );
#  endif

#  if defined (__BORLANDC__)
  /* Reset floating point control word */
  _clear87();
  _control87(_float_control_word, MCW_PC|MCW_EM|MCW_IC);
#  endif

  return EXAM_RESULT;
}
