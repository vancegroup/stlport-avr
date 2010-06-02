// -*- C++ -*- Time-stamp: <10/06/02 15:17:35 ptr>

/*
 * Copyright (c) 2004-2008
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

#ifndef __TEST_DEQUE_TEST_H
#define __TEST_DEQUE_TEST_H

#define __FIT_EXAM

#include <exam/suite.h>

class deque_test
{
  public:
    int EXAM_DECL(deque1);
    int EXAM_DECL(at);
    int EXAM_DECL(insert);
    int EXAM_DECL(erase);
    int EXAM_DECL(auto_ref);
    int EXAM_DECL(allocator_with_state);
    int EXAM_DECL(optimizations_check);
};

class queue_test
{
  public:
    int EXAM_DECL(pqueue1);
    int EXAM_DECL(queue1);
};

class stack_test
{
  public:
    int EXAM_DECL(stack1);
    int EXAM_DECL(stack2);
};

#endif // __TEST_DEQUE_TEST_H
