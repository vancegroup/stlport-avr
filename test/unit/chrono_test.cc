// -*- C++ -*- Time-stamp: <2011-05-02 11:57:58 ptr>

/*
 * Copyright (c) 2011
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

#include "chrono_test.h"

#include <chrono>

using namespace std;

int EXAM_IMPL(chrono_test::duration_ctor)
{
  chrono::nanoseconds ns;

  // EXAM_CHECK( ns.count() == 1 );

  chrono::nanoseconds ns30( 30 );

  EXAM_CHECK( ns30.count() == 30 );

  chrono::nanoseconds ns30_1( ns30 );

  EXAM_CHECK( ns30_1.count() == 30 );

  ns = ns30;

  EXAM_CHECK( ns.count() == 30 );

  int v50 = 50;

  chrono::nanoseconds ns50( v50 );

  EXAM_CHECK( ns50.count() == 50 );

  chrono::duration<double,nano> d_ns( 10 );

  return EXAM_RESULT;
}

int EXAM_IMPL(chrono_test::duration_arithmetic)
{
  chrono::nanoseconds ns( 1 );

  EXAM_CHECK( ns.count() == 1 );

  ns *= 2;

  EXAM_CHECK( ns.count() == 2 );

  chrono::nanoseconds ns10( 10 );

  ns += ns10;

  EXAM_CHECK( ns.count() == 12 );

  chrono::microseconds mc10( 2 );

  EXAM_CHECK( (mc10 + ns).count() == 2012 );
  EXAM_CHECK( (ns + mc10).count() == 2012 );

  // cerr << (mc10 + ns).count() << endl;

  return EXAM_RESULT;
}

int EXAM_IMPL(chrono_test::system_clock)
{
  chrono::system_clock::time_point t( chrono::system_clock::now() );

  // cerr << t.time_since_epoch().count() << endl;

  // cerr << chrono::system_clock::to_time_t( t ) << endl;
  chrono::system_clock::time_point t2( chrono::system_clock::now() );

  EXAM_CHECK( t <= t2 );

  return EXAM_RESULT;
}
