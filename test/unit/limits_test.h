// -*- C++ -*- Time-stamp: <10/01/23 02:17:01 ptr>

/*
 * Copyright (c) 2004-2010
 * Petr Ovtchenkov
 *
 * Copyright (c) 2004-2008
 * Francois Dumont
 *
 * Licensed under the Academic Free License Version 3.0
 *
 */

#ifndef __TEST_LIMITS_TEST_H
#define __TEST_LIMITS_TEST_H

#define __FIT_EXAM

#include <exam/suite.h>

#include <limits>
#include <type_traits>
#include <ieee754.h>

class limits_test
{
  public:
    int EXAM_DECL(limits);


    template <class _Tp>
    int EXAM_DECL(qNaN);

    template <class _Tp>
    int EXAM_DECL(sNaN);
};

template <class _Tp>
int EXAM_IMPL(limits_test::qNaN)
{
  typedef std::numeric_limits<_Tp> lim;

  if ( !lim::has_quiet_NaN ) {
    throw exam::skip_exception();
  }

#if defined (__BORLANDC__)
  /* Ignore FPU exceptions, set FPU precision to 64 bits */
  unsigned int _float_control_word = _control87(0, 0);
  _control87(PC_64|MCW_EM|IC_AFFINE, MCW_PC|MCW_EM|MCW_IC);
#endif

  const volatile _Tp qnan = lim::quiet_NaN();

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

  if ( std::is_same<float,_Tp>::value ) {
    ieee754_float v;
    v.f = qnan;
    EXAM_CHECK( v.ieee_nan.quiet_nan == 1 );
  }

  if ( std::is_same<double,_Tp>::value ) {
    ieee754_double v;
    v.d = qnan;
    EXAM_CHECK( v.ieee_nan.quiet_nan == 1 );
  }

#if !defined ( _STLP_NO_LONG_DOUBLE )
  if ( std::is_same<long double,_Tp>::value ) {
    ieee854_long_double v;
    v.d = qnan;
    EXAM_CHECK( v.ieee_nan.quiet_nan == 1 );
  }
#endif

#if defined (__BORLANDC__)
  /* Reset floating point control word */
  _clear87();
  _control87(_float_control_word, MCW_PC|MCW_EM|MCW_IC);
#endif

  return EXAM_RESULT;
}

template <class _Tp>
int EXAM_IMPL(limits_test::sNaN)
{
  typedef std::numeric_limits<_Tp> lim;

  if ( !lim::has_signaling_NaN ) {
    throw exam::skip_exception();
  }

#if defined (__BORLANDC__)
  /* Ignore FPU exceptions, set FPU precision to 64 bits */
  unsigned int _float_control_word = _control87(0, 0);
  _control87(PC_64|MCW_EM|IC_AFFINE, MCW_PC|MCW_EM|MCW_IC);
#endif

  const volatile _Tp snan = lim::signaling_NaN();

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

  if ( std::is_same<float,_Tp>::value ) {
    ieee754_float v;
    v.f = snan;
    EXAM_CHECK( v.ieee_nan.quiet_nan == 0 );
  }

#if (defined (__amd64__) || defined (_M_AMD64) || defined (__x86_64__)) || \
     !(defined (__i386) || defined (_M_IX86) || defined (_M_ARM))
  // It's known, that for 32-bit mode of x86 return
  // via FP register convert sNaN into qNaN,
  // so skip this check.
  if ( std::is_same<double,_Tp>::value ) {
    ieee754_double v;
    v.d = snan;
    EXAM_CHECK( v.ieee_nan.quiet_nan == 0 );
  }
#endif

#if !defined ( _STLP_NO_LONG_DOUBLE )
  if ( std::is_same<long double,_Tp>::value ) {
    ieee854_long_double v;
    v.d = snan;
    EXAM_CHECK( v.ieee_nan.quiet_nan == 0 );
  }
#endif

#if defined (__BORLANDC__)
  /* Reset floating point control word */
  _clear87();
  _control87(_float_control_word, MCW_PC|MCW_EM|MCW_IC);
#endif

  return EXAM_RESULT;
}

#endif // __TEST_LIMITS_TEST_H
