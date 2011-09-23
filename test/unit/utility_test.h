// -*- C++ -*- Time-stamp: <2011-09-23 19:44:32 ptr>

/*
 * Copyright (c) 2004-2010
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

#ifndef __TEST_UTILITY_TEST_H
#define __TEST_UTILITY_TEST_H

#define __FIT_EXAM

#include <exam/suite.h>

class utility_test
{
  public:
    int EXAM_DECL(pair0);
    int EXAM_DECL(init);

    int EXAM_DECL(forward);
    int EXAM_DECL(move);
};

#endif // __TEST_UTILITY_TEST_H
