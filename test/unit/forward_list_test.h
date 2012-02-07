// -*- C++ -*- Time-stamp: <2012-02-07 14:40:27 ptr>

/*
 * Copyright (c) 2004-2012
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

#ifndef __TEST_SLIST_TEST_H
#define __TEST_SLIST_TEST_H

#define __FIT_EXAM

#include <exam/suite.h>

class forward_list_test
{
  public:
    int EXAM_DECL(forward_list1);
    int EXAM_DECL(erase);
    int EXAM_DECL(insert);
    int EXAM_DECL(splice);
    int EXAM_DECL(allocator_with_state);
    int EXAM_DECL(move);
    int EXAM_DECL(assign);
};

#endif // __TEST_SLIST_TEST_H
