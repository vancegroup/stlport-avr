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

#include "binary_test.h"

#include <algorithm>
#include "unary.h"

#if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)
using namespace std;
#endif

int EXAM_IMPL(bsearch_test::bsearch1)
{
  int vector[100];
  for (int i = 0; i < 100; i++) {
    vector[i] = i;
  }
  EXAM_CHECK(binary_search(vector, vector + 100, 42));

  return EXAM_RESULT;
}

int EXAM_IMPL(bsearch_test::bsearch2)
{
  char const* labels[] = { "aa", "dd", "ff", "jj", "ss", "zz" };
  const unsigned count = sizeof(labels) / sizeof(labels[0]);
  // DEC C++ generates incorrect template instatiation code
  // for "ff" so must cast
  EXAM_CHECK(binary_search(labels, labels + count, (const char *)"ff", str_compare));

  return EXAM_RESULT;
}

bool bsearch_test::str_compare(const char* a_, const char* b_)
{
  return strcmp(a_, b_) < 0 ? 1 : 0;
}

int EXAM_IMPL(bcompose_test::bcompose1)
{
#if defined (STLPORT) && !defined (_STLP_NO_EXTENSIONS)
  int array [6] = { -2, -1, 0, 1, 2, 3 };

  binary_compose<logical_and<bool>, odd, positive>
  b = binary_compose<logical_and<bool>, odd, positive>(logical_and<bool>(), odd(), positive());

  int* p = find_if((int*)array, (int*)array + 6, b);
  EXAM_CHECK(p != array + 6);
#else
  throw exam::skip_exception();
#endif
  return EXAM_RESULT;
}

int EXAM_IMPL(bcompose_test::bcompose2)
{
#if defined (STLPORT) && !defined (_STLP_NO_EXTENSIONS)
  int array [6] = { -2, -1 , 0, 1, 2, 3 };

  int* p = find_if((int*)array, (int*)array + 6,
  compose2(logical_and<bool>(), odd(), positive()));
  EXAM_CHECK(p != array + 6);
#else
  throw exam::skip_exception();
#endif
  return EXAM_RESULT;
}
