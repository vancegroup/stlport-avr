// -*- C++ -*- Time-stamp: <2012-03-26 19:35:56 ptr>

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
  void* p1 = nullptr;
  int* p2 = nullptr;
  int v = 1;
  int* p3 = &v;
  int* p4 = NULL;
  int (sample::*pm)() = &sample::method;
  int (sample::*pm0)() = nullptr;
  int (sample::*pm1)() = nullptr;

  EXAM_CHECK( nullptr == p );
  EXAM_CHECK( nullptr == p1 );
  EXAM_CHECK( p2 == nullptr );
  EXAM_CHECK( p3 != nullptr );
  EXAM_CHECK( p4 == nullptr );
  EXAM_CHECK( !nullptr );
  EXAM_CHECK( pm != pm0 );
  EXAM_CHECK( pm0 == pm1 );
  EXAM_CHECK( pm != nullptr );
  EXAM_CHECK( pm0 == nullptr );

  return EXAM_RESULT;
}
