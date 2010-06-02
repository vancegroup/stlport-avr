// -*- C++ -*- Time-stamp: <10/06/02 15:17:35 ptr>

/*
 * Copyright (c) 2007
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
 */

#include <exam/suite.h>

int EXAM_IMPL(func)
{
  EXAM_CHECK(false);

  return EXAM_RESULT;
}

class test_x
{
  public:

    int EXAM_IMPL(f)
      {
        EXAM_CHECK(false);
        EXAM_CHECK(true);

        return EXAM_RESULT;
      }

    int EXAM_IMPL(f_good)
      {
        EXAM_CHECK(true);
        EXAM_CHECK(true);

        return EXAM_RESULT;
      }
};

int EXAM_IMPL(func_good)
{
  EXAM_CHECK(true);

  return EXAM_RESULT;
}

int EXAM_IMPL(func_good2)
{
  EXAM_CHECK(true);

  return EXAM_RESULT;
}

int EXAM_IMPL(func_good3)
{
  EXAM_CHECK(true);

  return EXAM_RESULT;
}

int EXAM_IMPL(loop)
{
  int j = 0;
  for ( int i = 0; i < 100000; ++i ) {
    j += 2;
  }

  return EXAM_RESULT;
}

