// -*- C++ -*- Time-stamp: <2011-04-21 16:39:22 ptr>

/*
 * Copyright (c) 2007-2011
 * Petr Ovtchenkov
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

#include "ratio_test.h"

#include <ratio>

int EXAM_IMPL(ratio_test::ratio)
{
  EXAM_CHECK( (std::ratio<1,1>::num == 1LL) && (std::ratio<1,1>::den == 1LL) );
  EXAM_CHECK( (std::ratio<2,1>::num == 2LL) && (std::ratio<2,1>::den == 1LL) );
  EXAM_CHECK( (std::ratio<1,2>::num == 1LL) && (std::ratio<1,2>::den == 2LL) );
  EXAM_CHECK( (std::ratio<2,2>::num == 1LL) && (std::ratio<2,2>::den == 1LL) );
  EXAM_CHECK( (std::ratio<100,5>::num == 20LL) && (std::ratio<100,5>::den == 1LL) );
  EXAM_CHECK( (std::ratio<-10,100>::num == -1LL) && (std::ratio<-10,100>::den == 10LL) );
  EXAM_CHECK( (std::ratio<3,-5>::num == -3LL) && (std::ratio<3,-5>::den == 5LL) );
  EXAM_CHECK( (std::ratio<7>::num == 7LL) && (std::ratio<7>::den == 1LL) );

  typedef std::ratio<3,5> three_five;
  typedef std::ratio<2,7> two_seven;

  EXAM_CHECK( (std::ratio_add<three_five,two_seven>::num == 31LL) && (std::ratio_add<three_five,two_seven>::den == 35LL) );

  EXAM_CHECK( (std::ratio_add<std::atto,std::atto>::num == 1LL) && (std::ratio_add<std::atto,std::atto>::den == 500000000000000000LL) );

  EXAM_CHECK( (std::ratio_subtract<std::femto,std::atto>::num == 999LL) && (std::ratio_subtract<std::femto,std::atto>::den == 1000000000000000000LL) );

  EXAM_CHECK( (std::ratio_multiply<std::femto,std::peta>::num == 1LL) && (std::ratio_multiply<std::femto,std::peta>::den == 1LL) );

  EXAM_CHECK( (std::ratio_divide<std::micro,std::nano>::num == 1000LL) && (std::ratio_divide<std::micro,std::nano>::den == 1LL) );

  EXAM_CHECK( (std::ratio_equal<std::milli,std::milli>::value) );

  EXAM_CHECK( (!std::ratio_equal<std::milli,std::kilo>::value) );

  EXAM_CHECK( (std::ratio_not_equal<std::milli,std::kilo>::value) );

  EXAM_CHECK( (std::ratio_less<std::mega,std::giga>::value) );

  return EXAM_RESULT;
}
