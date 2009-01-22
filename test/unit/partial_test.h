// -*- C++ -*- Time-stamp: <09/01/23 01:05:02 ptr>

/*
 * Copyright (c) 2004-2009
 * Petr Ovtchenkov
 *
 * Copyright (c) 2004-2008
 * Francois Dumont
 *
 * Licensed under the Academic Free License Version 3.0
 *
 */

#ifndef __TEST_PARTIAL_TEST_H
#define __TEST_PARTIAL_TEST_H

#define FIT_EXAM

#include <exam/suite.h>

class partial_test
{
  public:
    int EXAM_DECL(parsrt0);
    int EXAM_DECL(parsrt1);
    int EXAM_DECL(parsrt2);
    int EXAM_DECL(parsrtc0);
    int EXAM_DECL(parsrtc1);
    int EXAM_DECL(parsrtc2);
    int EXAM_DECL(bad_predicate_detected);

  protected:
    static bool str_compare(const char* a_, const char* b_)
    {
      return strcmp(a_, b_) < 0 ? 1 : 0;
    }
};

#endif // __TEST_PARTIAL_TEST_H
