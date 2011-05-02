// -*- C++ -*- Time-stamp: <2011-05-02 11:20:43 ptr>

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

#ifndef __TEST_CHRONO_TEST_H
#define __TEST_CHRONO_TEST_H

#define FIT_EXAM

#include <exam/suite.h>

class chrono_test
{
  public:
    int EXAM_DECL(duration_ctor);
    int EXAM_DECL(duration_arithmetic);
    int EXAM_DECL(system_clock);
};

#endif // __TEST_CHRONO_TEST_H
