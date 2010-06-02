// -*- C++ -*- Time-stamp: <10/06/02 15:17:35 ptr>

/*
 * Copyright (c) 2004-2009
 * Petr Ovtchenkov
 *
 * Copyright (c) 2004-2008
 * Francois Dumont
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

#include "ptr2_test.h"

#include <vector>
#include <algorithm>
#include <functional>

#if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)
using namespace std;
#endif

static int sum(int x_, int y_)
{
  return x_ + y_;
}

bool even(int n_)
{
  return(n_ % 2) == 0;
}

int EXAM_IMPL(ptr2_test::ptrbin1)
{
  int input1 [4] = { 7, 2, 3, 5 };
  int input2 [4] = { 1, 5, 5, 8 };

  int output [4];
  transform((int*)input1, (int*)input1 + 4, (int*)input2, (int*)output, pointer_to_binary_function<int, int, int>(sum));

  EXAM_CHECK(output[0]==8);
  EXAM_CHECK(output[1]==7);
  EXAM_CHECK(output[2]==8);
  EXAM_CHECK(output[3]==13);

  return EXAM_RESULT;
}

int EXAM_IMPL(ptr2_test::ptrbin2)
{
  int input1 [4] = { 7, 2, 3, 5 };
  int input2 [4] = { 1, 5, 5, 8 };

  int output [4];
  transform((int*)input1, (int*)input1 + 4, (int*)input2, (int*)output, ptr_fun(sum));

  EXAM_CHECK(output[0]==8);
  EXAM_CHECK(output[1]==7);
  EXAM_CHECK(output[2]==8);
  EXAM_CHECK(output[3]==13);

  return EXAM_RESULT;
}

int EXAM_IMPL(ptr2_test::ptrun1)
{
  int array [3] = { 1, 2, 3 };

  int* p = find_if((int*)array, (int*)array + 3, pointer_to_unary_function<int, bool>(even));
  EXAM_CHECK(p != array+3);
  EXAM_CHECK(*p==2);

  return EXAM_RESULT;
}

int EXAM_IMPL(ptr2_test::ptrun2)
{
  int array [3] = { 1, 2, 3 };

  int* p = find_if((int*)array, (int*)array + 3, ptr_fun(even));
  EXAM_CHECK(p != array+3);
  EXAM_CHECK(*p==2);

  return EXAM_RESULT;
}
