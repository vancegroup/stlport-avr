// -*- C++ -*- Time-stamp: <07/09/03 22:22:09 ptr>

/*
 * Copyright (c) 2007
 * Petr Ovtchenkov
 *
 * Licensed under the Academic Free License Version 3.0
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

