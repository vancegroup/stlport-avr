// -*- C++ -*- Time-stamp: <2011-09-19 20:18:01 ptr>

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

#include "null_ptr.h"

#include <cstddef>

struct sample
{
    int method()
      { return 0; }
};

int EXAM_IMPL(null_ptr_test::convert)
{
  void* p = 0;
  void* p1 = std::nullptr;
  int* p2 = std::nullptr;
  int v = 1;
  int* p3 = &v;
  int (sample::*pm)() = &sample::method;
  int (sample::*pm0)() = std::nullptr;
  int (sample::*pm1)() = std::nullptr;

  EXAM_CHECK( std::nullptr == p );
  EXAM_CHECK( std::nullptr == p1 );
  EXAM_CHECK( p2 == std::nullptr );
  EXAM_CHECK( p3 != std::nullptr );
  EXAM_CHECK( !std::nullptr );
  EXAM_CHECK( pm != pm0 );
  EXAM_CHECK( pm0 == pm1 );
  EXAM_CHECK( pm != std::nullptr );
  EXAM_CHECK( pm0 == std::nullptr );

  return EXAM_RESULT;
}
